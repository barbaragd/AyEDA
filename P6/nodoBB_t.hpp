#pragma once
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class nodoBB_t{
    private:
        T dato;

    public:
        nodoBB_t(T dato, nodoBB_t* iz=nullptr, nodoBB_t* de=nullptr): 
        dato(dato), izdo(iz), dcho(de){
        }

        T get_dato(){ return dato; }
        void set_dato(T d){ dato = d; }

        nodoBB_t *izdo;
        nodoBB_t *dcho;
};