#include "modelos_graficos.hpp"
#include "vars.hpp"


cadena::cadena(mat_int &databse):grafo(){
    mat_db minfo=mutual_information(databse);
    get_porbs_dist_bin(databse,this->proba0,this->proba1);
    this->find_model(minfo);
}



void cadena::find_model(mat_db &mutual_information){
    int n=mutual_information.size(),nodos=0;
    this->set_graf_size(n);
    nodo temp_nod;
    std::unordered_map<int,int> listed,unlisted;
    int root=-1,extremo1,extremo2;
    double max=0;
        for(int i=0;i<n;i++){
            unlisted.insert(std::make_pair(i,i));
            for(int j=i+1;j<n;j++){
                if(mutual_information[i][j]>max){
                    max=mutual_information[i][j];
                    extremo1=i;extremo2=j;
                }
            }
        }
    unlisted.erase(extremo1);
    unlisted.erase(extremo2);
    listed.insert(std::make_pair(extremo1,extremo1));
    listed.insert(std::make_pair(extremo2,extremo2));
    this->set_node(extremo1,nodo(extremo1,vec_int(1,extremo2),0,0));
    this->set_node(extremo2,nodo(extremo1,vec_int(0),0,0));
    nodos=2;
    while(nodos<n){
        double  max1=0,max2=0;
        int ex1=extremo1,ex2=extremo2;
        for(auto i=unlisted.begin();i!=unlisted.end();i++){
            int j=i->second;
            if(max1<mutual_information[extremo1][j]){
                ex1=j;
                max1=mutual_information[extremo1][j];
            }
            if(max2<mutual_information[extremo2][j]){
                ex2=j;
                max2=mutual_information[extremo2][j];
            }

        }
        if(max1>max2){
            //se cambia extremo 1
            this->set_node(extremo1,nodo(ex1,this->get_hijos(extremo1),0,0));
            this->set_node(ex1,nodo(ex1,vec_int(1,extremo1),0,0));
            unlisted.erase(ex1);
            listed.insert(std::make_pair(ex1,ex1));
            nodos++;
            extremo1=ex1;
        }else{
            //se cambia extremo 2
            this->set_node(extremo2,nodo(this->get_padre(extremo2),vec_int(1,ex2),0,0));
            this->set_node(ex2,nodo(extremo2,vec_int(0),0,0));
            unlisted.erase(ex2);
            listed.insert(std::make_pair(ex2,ex2));
            nodos++;
            extremo2=ex2;
        }

    }
    this->set_root(extremo1);
    for(int i=0;i<n;i++){
        int p=this->get_padre(i);
        this->set_probs(i,this->proba0[p][i],this->proba1[p][i]);
    }
}


mat_int cadena::generate_dataset(int n){
    int nvars=this->get_nvars();
    std::queue<int> pendientes;
    std::unordered_map<int,int> visited;
    pendientes.push(this->get_root());
    nodo *ptn;
    mat_int res(n,vec_int(nvars));
    printf("Result dimensions is %dx%d\n",n,nvars);
    while(!pendientes.empty()){
        int idx=pendientes.front();
        pendientes.pop();
        visited.insert(std::make_pair(idx,idx));
        ptn=&this->graf[idx];
        //printf("Ando viendo a %d, su papa es %d y es la variable %d\n",idx,ptn->get_padre(),ptn->varnum);
        vec_int hijos=ptn->get_hijos();
        for(int x:hijos)
            pendientes.push(x);
       for(auto i=res.begin();i!=res.end();i++){
                ptn->crea(*i);
            }
    }
    return res;
}





arbol::arbol(mat_int &databse):grafo(){
    mat_db minfo=mutual_information(databse);
    get_porbs_dist_bin(databse,this->proba0,this->proba1);
    this->find_model(minfo);
}


void  arbol::find_model(mat_db &mutual_information){
    int n=mutual_information.size(),nodos=0;
    this->set_graf_size(n);
    nodo temp_nod;
    std::unordered_map<int,int> listed,unlisted;
    int root=-1,extremo1,extremo2;
    double max=0;
        for(int i=0;i<n;i++){
            unlisted.insert(std::make_pair(i,i));
            for(int j=i+1;j<n;j++){
                if(mutual_information[i][j]>max){
                    max=mutual_information[i][j];
                    extremo1=i;extremo2=j;
                }
            }
        }
    unlisted.erase(extremo1);
    unlisted.erase(extremo2);
    listed.insert(std::make_pair(extremo1,extremo1));
    listed.insert(std::make_pair(extremo2,extremo2));
    this->set_root(extremo1);
    this->set_node(extremo1,nodo(extremo1,vec_int(1,extremo2),0,0));
    this->set_node(extremo2,nodo(extremo1,vec_int(0),0,0));
    while(unlisted.size()!=0){
        int exn=0,pap=0;
        float max=0;
        for(auto l:listed){
            int i=l.second;
            for(auto k:unlisted){
                int j=k.second;
                if(max<mutual_information[i][j]){
                    max=mutual_information[i][j];
                    exn=j;
                    pap=i;
                }
            }
        }
        //agregar hijos al padre
        vec_int vect=this->get_hijos(pap);
        vect.push_back(exn);
        this->set_node(pap,nodo(get_padre(pap),vect,0,0));
        this->set_node(exn,nodo(pap,vec_int(0),0,0));
        listed.insert(std::make_pair(exn,exn));
        unlisted.erase(exn);
    }

    for(int i=0;i<n;i++){
        int p=this->get_padre(i);
        this->set_probs(i,this->proba0[p][i],this->proba1[p][i]);
    }


 }

mat_int arbol::generate_dataset(int n){
    int nvars=this->get_nvars();
    std::queue<int> pendientes;
    std::unordered_map<int,int> visited;
    pendientes.push(this->get_root());
    nodo *ptn;
    mat_int res(n,vec_int(nvars));
    while(!pendientes.empty()){
        int idx=pendientes.front();
        pendientes.pop();
        visited.insert(std::make_pair(idx,idx));
        ptn=&this->graf[idx];
        vec_int hijos=ptn->get_hijos();
        for(int x:hijos)
            pendientes.push(x);
        for(int i=0;i<n;i++){
            ptn->crea(res[i]);
        }
    }
    return res;
}

tc::tc(mat_int &database){
    int n=database[0].size(),nodos=0;
    this->nvars=n;
    this->set_graf_size(n);
    get_porbs_dist_bin(database,this->proba0,this->proba1);
}
       
vec_db tc::existance(mat_int &dataset){
    int n=dataset.size();
    vec_db probs(n,0);
    for(int i=0;i<n;i++){ 
        double tmp=1;
        for(int j=0;j<dataset[i].size();j++){
            for(int k=j-1;k>=0;k--){
                double proval=(dataset[i][j]==1)?this->proba1[j][k]:this->proba0[j][k];
                tmp*=(dataset[i][j]==1)?proval:1-proval;
            }
            if(j==0){
                double proval=proba1[j][j];
                tmp*=(dataset[i][j]==1)?proval:1-proval;
            }
        }
        probs[i]=tmp;
    }
    return probs;
}
#define randf rand()/(float)RAND_MAX
mat_int tc::generate_dataset(int n){
    mat_int dataset(n,vec_int(this->get_nvars()));
     for(int i=0;i<n;i++){ 
        double tmp=1;
        for(int j=0;j<dataset[i].size();j++){
            for(int k=j;k>=0;k--){
                double proval=(dataset[i][j]==1)?this->proba1[j][k]:this->proba0[j][k];
                tmp*=(dataset[i][j]==1)?proval:1-proval;
            }
            dataset[i][j]=(randf<=tmp)?1:0;
        }
    }
    return dataset;
}

indep_mod::indep_mod(mat_int &database){
    int n=database[0].size();
    this->set_graf_size(n);this->nvars=n;
    get_porbs_dist_bin(database,this->proba0,this->proba1);
}

vec_db indep_mod::existance(mat_int &database){
    int n=database.size();
    vec_db probs(n,1);
    for(int i=0;i<n;i++){
        for(int j=0;j<database[i].size();j++){ 
            probs[i]*=(database[i][j]==1)?proba1[j][j]:proba0[j][j];
        }
    }
    return probs;
}

mat_int indep_mod::generate_dataset(int n){ 
    mat_int dataset(n,vec_int(this->get_nvars()));
    for(int i=0;i<n;i++){ 
        for(int j=0;j<this->get_nvars();i++){ 
            dataset[i][j]=(randf<=proba1[j][j])?1:0;
        }
    }
    return dataset;
}