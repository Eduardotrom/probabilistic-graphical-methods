#include<vector>
#include<iostream>
#include "vars.hpp"
#include "modelos_graficos.hpp"
using namespace std;
int main(){
    //srand(time(NULL));
    srand(3);
    mat_int debe,dbd;
    int n=60000;
    //std::cout<<"El primer modelo en cadena  es :"<<std::endl;
    debe=db1(n);
    {   
    cadena c1(debe);
    //c1.print_model();
    vec_db prb1=c1.exist_prob(debe), org_p=db1_p(debe);
    printf("La probabilidad de la secuencia: ");
    int i=0;
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 1 es: %e y para el primer modelo de cadena es de %e\n",org_p[i],prb1[i]);
    i=1;
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 1 es: %e y para el primer modelo de cadena es de %e\n",org_p[i],prb1[i]);
    i=2;
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 1 es: %e y para el primer modelo de cadena es de %e\n",org_p[i],prb1[i]);
    printf("La divergencia KL entre estos 2 modelos es de: %e \n",kullback_leibler(org_p, prb1));
    printf("Sus respectivas log-verosimilitudes son : Distribucion tabla %e  Distribucion modelo %e \n",loglike(org_p),loglike(prb1));
    std::cout<<"Y en arbol es :"<<std::endl;
    arbol a1(debe);
    vec_db a1p=a1.exist_prob(debe);
    i=0;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 1 es: %e y para el primer modelo de arbol es de %e\n",org_p[i],a1p[i]);
    i=1;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 1 es: %e y para el primer modelo de arbol es de %e\n",org_p[i],a1p[i]);
    i=2;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 1 es: %e y para el primer modelo de arbol es de %e\n",org_p[i],a1p[i]);
    
    printf("La divergencia KL entre estos 2 modelos es de: %e \n",kullback_leibler(org_p, a1p));
    printf("Sus respectivas log-verosimilitudes son : Distribucion tabla %e  Distribucion modelo %e \n",loglike(org_p),loglike(a1p));
    printf("\n\n\n");
    printf("El modelo independiente:\n");
    indep_mod ind(debe);
    vec_db indep_p=ind.existance(debe);
    i=0;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 1 es: %e y para el primer modelo de arbol es de %e\n",org_p[i],indep_p[i]);
    i=1;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 1 es: %e y para el primer modelo de arbol es de %e\n",org_p[i],indep_p[i]);
    i=2;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 1 es: %e y para el primer modelo de arbol es de %e\n",org_p[i],indep_p[i]);
    printf("La divergencia KL entre estos 2 modelos es de: %e \n",kullback_leibler(org_p, indep_p));
    printf("Sus respectivas log-verosimilitudes son : Distribucion tabla %e  Distribucion modelo %e \n",loglike(org_p),loglike(indep_p));
    printf("\n\n\n");

    printf("El modelo todo conectado:\n");
    tc todo(debe);
    vec_db todo_p=todo.existance(debe);
    i=0;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 1 es: %e y para el primer modelo de arbol es de %e\n",org_p[i],todo_p[i]);
    i=1;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 1 es: %e y para el primer modelo de arbol es de %e\n",org_p[i],todo_p[i]);
    i=2;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 1 es: %e y para el primer modelo de arbol es de %e\n",org_p[i],todo_p[i]);
    printf("La divergencia KL entre estos 2 modelos es de: %e \n",kullback_leibler(org_p, todo_p));
    printf("Sus respectivas log-verosimilitudes son : Distribucion tabla %e  Distribucion modelo %e \n",loglike(org_p),loglike(todo_p));
    printf("\n\n\n");
    }
    
   

   printf("Para el segundo dataset:\n");
    debe=db2(n);
    {   
    cadena c1(debe);
    vec_db prb1=c1.exist_prob(debe), org_p=db2_p(debe);
    int i=0;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el Dataset 2 es: %e y para el primer modelo de cadena es de %e\n",org_p[i],prb1[i]);
    i=1;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el Dataset 2 es: %e y para el primer modelo de cadena es de %e\n",org_p[i],prb1[i]);
    i=2;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el Dataset 2 es: %e y para el primer modelo de cadena es de %e\n",org_p[i],prb1[i]);
    printf("La divergencia KL entre estos 2 modelos es de: %e \n",kullback_leibler(org_p, prb1));
    printf("Sus respectivas log-verosimilitudes son : Distribucion tabla %e  Distribucion modelo %e \n",loglike(org_p),loglike(prb1));
    std::cout<<"Y en arbol es :"<<std::endl;
    arbol a1(debe);
    //a1.print_model();
    vec_db a1p=a1.exist_prob(debe);
    printf("La probabilidad de la secuencia: ");
    i=0;
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el modelo 2 es: %e y para el primer modelo de arbol es de %e\n",org_p[i],a1p[i]);
    i=1;
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el modelo 2 es: %e y para el primer modelo de arbol es de %e\n",org_p[i],a1p[i]);
    i=2;
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el modelo 2 es: %e y para el primer modelo de arbol es de %e\n",org_p[i],a1p[i]);
    printf("La divergencia KL entre estos 2 modelos es de: %e \n",kullback_leibler(org_p, a1p));
    printf("Sus respectivas log-verosimilitudes son : Distribucion tabla %e  Distribucion modelo %e \n",loglike(org_p),loglike(a1p));
    printf("\n\n\n");
    printf("El modelo independiente:\n");
    indep_mod ind(debe);
    vec_db indep_p=ind.existance(debe);
    i=0;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 2 es: %e y para el primer modelo independiente es de %e\n",org_p[i],indep_p[i]);
    i=1;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 2 es: %e y para el primer modelo independiente es de %e\n",org_p[i],indep_p[i]);
    i=2;
    printf("La probabilidad de la secuencia: ");
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 2 es: %e y para el primer modelo independiente es de %e\n",org_p[i],indep_p[i]);
    printf("La divergencia KL entre estos 2 modelos es de: %e \n",kullback_leibler(org_p, indep_p));
    printf("Sus respectivas log-verosimilitudes son : Distribucion tabla %e  Distribucion modelo %e \n",loglike(org_p),loglike(indep_p));
    printf("\n\n\n");

    printf("El modelo todo conectado:\n");
    tc todo(debe);
    vec_db todo_p=todo.existance(debe);
    printf("La probabilidad de la secuencia: ");
    i=0;
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 2 es: %e y para el primer modelo de todo conectado es de %e\n",org_p[i],todo_p[i]);
    i=1;
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 2 es: %e y para el primer modelo de todo conectado es de %e\n",org_p[i],todo_p[i]);
    i=2;
    for(int x:debe[i])
        printf("%d",x);
    printf("\nPara el dataset 2 es: %e y para el primer modelo de todo conectado es de %e\n",org_p[i],todo_p[i]);
    printf("La divergencia KL entre estos 2 modelos es de: %e \n",kullback_leibler(org_p, todo_p));
    printf("Sus respectivas log-verosimilitudes son : Distribucion tabla %e  Distribucion modelo %e \n",loglike(org_p),loglike(todo_p));
    printf("\n\n\n");
    }


    return 0;
}