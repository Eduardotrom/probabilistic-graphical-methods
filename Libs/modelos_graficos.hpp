#ifndef MODELOS_GRAFICOS_HPP
#define MODELOS_GRAFICOS_HPP

#include "grafos.hpp"
#include "vars.hpp"

class cadena:public grafo{
    private:
        mat_db proba0,proba1;
    public:
        cadena(){};
        cadena(mat_int &databse);
        void find_model(mat_db &mutual_information);
        mat_int generate_dataset(int n);
};


class arbol:public grafo{
    private:
        mat_db proba0,proba1;
    public: 
        arbol(){};
        arbol(mat_int &databse);
        void find_model(mat_db &mutual_information);
        mat_int generate_dataset(int n);
};


class tc:public grafo{
    private:
        mat_db proba0,proba1;
    public:
        tc(){};
        tc(mat_int &database);
        void find_model(mat_db &mutual_information);
        mat_int generate_dataset(int n);
        vec_db existance(mat_int &dataset);

};

class indep_mod:public grafo{
    private:
        mat_db proba0,proba1;
    public:
        indep_mod(){};
        indep_mod(mat_int &database);
        mat_int generate_dataset(int n);
        vec_db existance(mat_int &dataset);
};

#endif