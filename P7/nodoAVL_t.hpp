#pragma once
#include <iostream>

template<class T>
class nodoAVL_t{
    private:
        T dato;
        int bal;

    public:
        nodoAVL_t(T dato, int b, nodoAVL_t<T>* iz=NULL, nodoAVL_t<T>* de=NULL):
        dato(dato), izdo(iz), dcho(de), bal(b)
        {}

        T get_dato(){ return dato; }
        void set_dato(T d){ dato = d; }

        int get_bal(){ return bal; }
        void set_bal(int b){ bal = b; }

        nodoAVL_t<T> *izdo;
        nodoAVL_t<T> *dcho;

};