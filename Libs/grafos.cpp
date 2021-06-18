#include "grafos.hpp"

nodo::nodo(int pad, vec_int hijos,double ppad_0, double ppad_1){
        this->padre=pad;
        this->hijos=hijos;
        this->pad0=ppad_0;
        this->pad1=ppad_1;
    }
    void nodo::crea(vec_int &muestra){
        float tmp=rand()/(float)RAND_MAX;
        if(this->varnum!=this->padre){
            if(muestra[this->padre]==1){
                muestra[this->varnum]=(tmp<=this->pad1)?1:0;
            }else
            {
                muestra[this->varnum]=(tmp<=this->pad0)?1:0;
            }
        }else{
            muestra[this->varnum]=(tmp<=this->pad1)?1:0;
        }
    }
    vec_int nodo::get_hijos(){
        return this->hijos;
    }


void nodo::set_probs(double prob0,double prob1){
    this->pad0=prob0;
    this->pad1=prob1;
}


double nodo::prob_existence(vec_int &muestra){
    if(this->padre!=this->varnum){
        if(muestra[padre]==1)return (muestra[varnum]==1)?this->pad1:1-this->pad1;
        return (muestra[varnum]==1)?this->pad0:1-this->pad0;
    }else{
        return (muestra[this->varnum]==1)?this->pad1:this->pad0;
    }
}

int grafo::get_nvars(){
    return this->nvars;
}

void grafo::set_probs(int n,double prob0,double prob1){
    this->graf[n].set_probs(prob0,prob1);
}




void grafo::set_node(int index,nodo node){
    if(this->graf.size()<=index)graf.resize(index+1);
    this->graf[index]=node;
    this->graf[index].varnum=index;
}

int nodo::get_padre(){
    return this->padre;
}

grafo::grafo(int r,int vars,std::vector<nodo>grafo){
    this->raiz=r;
    this->nvars=vars;
    this->graf=grafo;
}

void grafo::set_graf_size(int size){
    this->graf.resize(size);
    this->nvars=size;
}
int grafo::get_root(){
    return this->raiz;
}
mat_int grafo::generate_dataset(int set_size){
    std::queue<int> pendientes;
    std::unordered_map<int,int> visited;
    pendientes.push(this->raiz);
    nodo *ptn;
    mat_int res(set_size,vec_int(this->nvars));
    while(!pendientes.empty()){
        int idx=pendientes.front();
        pendientes.pop();
        visited.insert(std::make_pair(idx,idx));
        ptn=&this->graf[idx];
        vec_int hijos=ptn->get_hijos();
        for(int x:hijos)
            pendientes.push(x);
        for(int i=0;i<set_size;i++){
            ptn->crea(res[i]);
        }
    }
    return res;
}

vec_int grafo::get_hijos(int indx){
    return this->graf[indx].get_hijos();
}

int grafo::get_padre(int indx){
    return this->graf[indx].get_padre();
}

void grafo::set_root(int r){
    this->raiz=r;
}

vec_db grafo::exist_prob(mat_int &database){
    int n=database.size();
    std::queue<int> pendientes;
    vec_db probs(n,1);
    pendientes.push(this->raiz);
    while(!pendientes.empty()){
        int actual=pendientes.front();
        pendientes.pop();
        vec_int hijos=this->graf[actual].get_hijos();
        for(int x:hijos)
            pendientes.push(x);
        for(int i=0;i<n;i++){ 
            probs[i]*=this->graf[actual].prob_existence(database[i]);
        }
    }
    return probs;
}

void grafo::print_model(){
    printf("El modelo comienza en el nodo %d \n",this->raiz);
    int i=0,actual=0;
    std::queue<int> pendientes;
    pendientes.emplace(this->raiz);
    while(!pendientes.empty()){
        actual=pendientes.front();
        pendientes.pop();
        printf("nodo actual %d \n",actual);
        double proba1=this->graf[actual].pad0,proba2=this->graf[actual].pad1;
        
        printf("Las probas son P(1|0)=%.2lf P(1|1)=%.2lf\n",proba1,proba2);
        printf("El papa es %d \n",this->graf[actual].get_padre());
        printf("Sus hijos son: ");
        for(auto w:this->graf[actual].get_hijos()){
            pendientes.emplace(w);
            printf("%d ",w);
        }printf("\n\n\n");
    }
}

#define randf rand()/(float)RAND_MAX

void show(mat_db &mat){
    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[i].size();j++){
            printf("%.3lf\t",mat[i][j]);
        }std::cout<<std::endl;
    }
}

void show(mat_int &mat){
    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[i].size();j++){
            printf("%d\t",mat[i][j]);
        }std::cout<<std::endl;
    }
}


std::pair<int,int> get_corr(vec_int &modelo,int i,int j){
    return std::make_pair(modelo[i]*(modelo[j]==1),modelo[i]*(modelo[j]==0));
}

void get_porbs_dist_bin(mat_int &dataset,mat_db &probs0,mat_db &probs1){
    int varnum=dataset[0].size(),n=dataset.size();
    probs0=mat_db(varnum,vec_db(varnum,0.0));
    probs1=mat_db(varnum,vec_db(varnum,0.0));
    for(auto x=dataset.begin();x!=dataset.end();x++){
        for(int i=0;i<varnum;i++){
            for(int j=0;j<varnum;j++){
                auto tmp=get_corr(*x,j,i);
                probs1[i][j]+=tmp.first;
                probs0[i][j]+=tmp.second;
            }
        }
    }
    //completas la matriz
    for(int i=0;i<varnum;i++)
        probs0[i][i]=n-probs1[i][i];
    //aqui ya calculas probas
    for(int i=0;i<varnum;i++){
        probs0[i][i]=abs(probs1[i][i]-n);
        for(int j=0;j<varnum;j++){
            if(j==i)continue;
            probs0[i][j]/=probs0[i][i];
            probs1[i][j]/=probs1[i][i];
        }
    }
    for(int i=0;i<varnum;i++){
        probs0[i][i]/=n;
        probs1[i][i]/=n;
    }

}

mat_int joint_c_bin(mat_int const & x,int i,int j){
    mat_int m(2,vec_int(2,0));
    for(vec_int it:x){
        m[0][0]+=(it[i]==0&&it[j]==0);
        m[0][1]+=(it[i]==0&&it[j]==1);
        m[1][0]+=(it[i]==1&&it[j]==0);
        m[1][1]+=(it[i]==1&&it[j]==1);
    }
    return m;
}



void get_joint_probs_dist_bin(mat_int &dataset, mat_db &jointprobs){
    int varnum=dataset[0].size(),n=dataset.size();
    jointprobs=mat_db(varnum*2,vec_db(varnum*2,0));
        for(int i=0;i<varnum*2;i=i+2){
            for(int j=i/2;j<varnum;j++){ 
                auto tmp=joint_c_bin(dataset,i/2,j);
                jointprobs[i][2*j]  +=tmp[0][0];
                jointprobs[i][2*j+1]+=tmp[0][1]; 
                jointprobs[i+1][2*j]  +=tmp[1][0];
                jointprobs[i+1][2*j+1]+=tmp[1][1]; 
            }
        }
        for(int i=0;i<varnum*2;i++){
            for(int j=0;j<i;j++){
                jointprobs[i][j]=jointprobs[j][i];
            }
        }
        for(int i=0;i<jointprobs.size();i++){
            for(int j=0;j<jointprobs[i].size();j++){
                jointprobs[i][j]/=n;
            }
        }


    }


mat_db entropy(mat_db &joint){
        int vars=joint.size()/2;
        mat_db entropy(vars,vec_db(vars,0));
        for(int i=0;i<vars;i++){
            for(int j=i;j<vars;j++){
                if(i==j){
                    double p=joint[i*2][i*2];
                    entropy[i][j]+=-p*log(p);
                    p=1-p;
                    entropy[i][j]+=-p*log(p);
                }else{
                    for(int k=0;k<2;k++){
                        for(int l=0;l<2;l++){
                            double p=joint[k+2*i][l+2*j];
                            p=(p==0)?1:p;
                            entropy[i][j]+=-p*log(p);
                    }
                }
            }
        }
    }
    for(int i=0;i<vars;i++){
        for(int j=0;j<i;j++){
            entropy[i][j]=entropy[j][i];
        }
    }
    return entropy;
}
mat_db mutual_information(mat_int & database){
    int n=database[0].size();
    mat_db MI(n,vec_db(n,0)),ent,join;
    get_joint_probs_dist_bin(database,join);
    ent=entropy(join);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j){
                MI[i][j]=ent[i][i];
            }else{
                MI[i][j]=ent[i][i]+ent[j][j]-ent[i][j];
            }
        }
    }
    return MI;
}


mat_int db1(int n){
    mat_int db(n,vec_int(6,0));
    vec_int x(6,0);
    for(int i=0;i<n;i++){
           x[0]=(randf<0.2)?1:0;
        if(x[0]==1){
            x[1]=(randf<0.31)?1:0;
        }else{
            x[1]=(randf<0.92)?1:0;
        }
        if(x[1]==1){
            x[2]=(randf<0.15)?1:0;
        }else{
            x[2]=(randf<0.42)?1:0;
        }
        if(x[2]==1){
            x[3]=(randf<0.75)?1:0;
        }else{
            x[3]=(randf<0.28)?1:0;
        }
        if(x[3]==1){
            x[4]=(randf<0.43)?1:0;
        }else{
            x[4]=(randf<0.67)?1:0;
        }
        if(x[4]==1){
            x[5]=(randf<0.82)?1:0;
        }else{
            x[5]=(randf<0.35)?1:0;
        }
    db[i]=x;
    }
    return db;
}

vec_db db1_p(mat_int &database){
    int n=database.size();
    vec_db probs(n,0);
    for(int i=0;i<n;i++){ 
        double tmp=1;
        tmp*=(database[i][0]==1)?0.2:0.8;
        if(database[i][0]==1){
            tmp*=(database[i][1]==1)?0.31:1-0.31;
        }else{
            tmp*=(database[i][1]==1)?0.92:1-0.92;
        }
        if(database[i][1]==1){
            tmp*=(database[i][2]==1)?0.15:1-0.15;
        }else{
            tmp*=(database[i][2]==1)?0.42:1-0.42;
        }
        if(database[i][2]==1){
            tmp*=(database[i][3]==1)?0.75:1-0.75;
        }else{
            tmp*=(database[i][3]==1)?0.28:1-0.28;
        }
        if(database[i][3]==1){
            tmp*=(database[i][4]==1)?0.43:1-0.43;
        }else{
            tmp*=(database[i][4]==1)?0.67:1-0.67;
        }
        if(database[i][4]==1){
            tmp*=(database[i][5]==1)?0.82:1-0.82;
        }else{
            tmp*=(database[i][5]==1)?0.35:1-0.35;
        }
        probs[i]=tmp;
    }
    return probs;
}


mat_int db2(int n){
    mat_int db(n,vec_int(6,0));
    vec_int x(6,0);
    for(int i=0;i<n;i++){
        x[0]=(randf<0.2)?1:0;
        if(x[0]==0){
            x[1]=(randf<0.92)?1:0;
            x[3]=(randf<0.42)?1:0;
        }else{
            x[1]=(randf<0.31)?1:0;
            x[3]=(randf<0.15)?1:0;
        }
        if(x[1]==0){
            x[4]=(randf<0.28)?1:0;
            x[5]=(randf<0.67)?1:0;
        }else{
            x[4]=(randf<0.75)?1:0;
            x[5]=(randf<0.43)?1:0;
        }
        if(x[5]==1){
            x[2]=(randf<0.82)?1:0;
        }else{
            x[2]=(randf<0.35)?1:0;
        }
        db[i]=x;
    }
    return db;
}

vec_db  db2_p(mat_int &database){
    int n=database.size();
    vec_db probs(n,0);
    for(int i=0;i<n;i++){ 
        double tmp=1;
        tmp*=(database[i][0]==1)?0.2:0.8;
        if(database[i][0]==1){
            tmp*=(database[i][1]==1)?0.31:1-0.31;
            tmp*=(database[i][3]==1)?0.15:1-0.15;
        }else{
            tmp*=(database[i][1]==1)?0.92:1-0.92;
            tmp*=(database[i][3]==1)?0.42:1-0.42;
        }
        if(database[i][1]==1){
            tmp*=(database[i][4]==1)?0.75:1-0.75;
            tmp*=(database[i][5]==1)?0.43:1-0.43;
        }else{
            tmp*=(database[i][4]==1)?0.28:1-0.28;
            tmp*=(database[i][5]==1)?0.67:1-0.67;
        }
        if(database[i][5]==1){
            tmp*=(database[i][2]==1)?0.82:1-0.82;
        }else{
            tmp*=(database[i][2]==1)?0.35:1-0.35;
        }
        probs[i]=tmp;
    }
    return probs;
}







double kullback_leibler(vec_db p,vec_db q){
    double dkl=0;
    for(int i=0;i<p.size();i++)
        dkl+=q[i]*log(q[i]/p[i]);
    return dkl;
}

double loglike(vec_db p){
    double like=0;
    for(double x:p)
        like+=log(x);
}


