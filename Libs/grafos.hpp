#ifndef GRAFOS_HPP
#define GRAFOS_HPP
#include<vector>
#include<iostream>
#include<queue>
#include "vars.hpp"
#include<unordered_map>
#include <cmath>
#include <queue>

class nodo{
    //private:
    public:
        int varnum,padre;
        double pad0,pad1;
        vec_int hijos;
    //public:
        nodo(){};
        nodo(int padre, vec_int hijos,double ppad_0, double ppad_1);
        void crea(vec_int &muestra);
        vec_int get_hijos();
        int get_padre();
        void set_probs(double prob0,double prob1);
        double prob_existence(vec_int &muestra);
};

class grafo{
    //private:
    public:
        int raiz,nvars;
        std::vector<nodo> graf; 
        grafo(){};
        grafo(int r,int vars,std::vector<nodo>grafo);
        virtual mat_int generate_dataset(int set_size);
        void set_node(int index,nodo node);
        void set_graf_size(int size);
        vec_int get_hijos(int indx);
        int get_padre(int indx);
        void set_root(int r);
        void print_model();
        void set_probs(int n,double prob0,double prob1);
        int get_nvars();
        int get_root();
        vec_db exist_prob(mat_int &database);
};

mat_int db1(int n);
vec_db  db1_p(mat_int &database);
mat_int db2(int n);
vec_db  db2_p(mat_int &database);
mat_db mutual_information(mat_int & database);
mat_db entropy(mat_db &joint);
void get_joint_probs_dist_bin(mat_int &dataset, mat_db &jointprobs);
mat_int joint_c_bin(mat_int const & x,int i,int j);
void get_porbs_dist_bin(mat_int &dataset,mat_db &probs0,mat_db &probs1);
std::pair<int,int> get_corr(vec_int &modelo,int i,int j);
void show(mat_int &mat);
void show(mat_db &mat);
double kullback_leibler(vec_db p,vec_db q);
double loglike(vec_db p);

#endif