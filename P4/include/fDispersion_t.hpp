#pragma once

#include <iostream>
#include <cstdlib>

#include "DNI_t.hpp"


template <class CLAVE>
class fDispersion_t{
    public:
        virtual int dispersion (const CLAVE& c) = 0; 
};




template <class CLAVE>
class fDispersion_modulo_t : public fDispersion_t<CLAVE>{

    private:
        int nCeldas;

    public:
        fDispersion_modulo_t(int n): nCeldas(n){} 

        int dispersion (const CLAVE& c){
            return (c % nCeldas);
        };
};


template <class CLAVE>
class fDispersion_suma_t : public fDispersion_t<CLAVE>{

    private:
        int nCeldas;

    public:
        fDispersion_suma_t(int n): nCeldas(n){} 

        int dispersion (const CLAVE& c){
            int d = 0, x, y;
            x = c;
            while(x > 0){
              y = x % 10;
              d = d + y;
              x = x / 10;
            }
            return(d % nCeldas);
        }; 
};


template <class CLAVE>
class fDispersion_rand_t : public fDispersion_t<CLAVE>{

    private:
        int nCeldas;

    public:
        fDispersion_rand_t(int n): nCeldas(n){} 

        int dispersion (const CLAVE& c){
            srand(c.get_numdni());
            return (rand() % nCeldas);
        };
};