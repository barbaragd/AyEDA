#pragma once

#include <iostream>
#include <math.h>

#include "DNI_t.hpp"
#include "fDispersion_t.hpp"

template <class CLAVE>
class fExploracion_t{
    public:
        virtual int exploracion (const CLAVE& c, int i) = 0;
};

template <class CLAVE>
class fExploracion_lineal_t : public fExploracion_t<CLAVE>{
    private:
        int nCeldas;
        fDispersion_t<CLAVE> *h_;
    
    public:
        fExploracion_lineal_t(int n, fDispersion_t<CLAVE>* x): nCeldas(n), h_(x){}
        int exploracion (const CLAVE& c, int i){
            int aux = h_->dispersion(c);
            return ((aux+i)%nCeldas);
        }
};


template <class CLAVE>
class fExploracion_cuadratica_t : public fExploracion_t<CLAVE>{
    private:
        int nCeldas;
        fDispersion_t<CLAVE> *h_;

    public:
        fExploracion_cuadratica_t(int n, fDispersion_t<CLAVE>* x): nCeldas(n), h_(x){}
        int exploracion (const CLAVE& c, int i){
            int aux = h_->dispersion(c);
            return ((aux+(i*i)) % nCeldas);
        }

};


template<class CLAVE>
class fExploracion_doble_dispersion_t : public fExploracion_t<CLAVE>{
    private:
        int nCeldas;
        fDispersion_t<CLAVE> *h_;
        fDispersion_t<CLAVE> *hx_;

    public:
        fExploracion_doble_dispersion_t(int n, fDispersion_t<CLAVE>* x): nCeldas(n), h_(x){}

        int exploracion(const CLAVE&c, int i){
            int auxa = h_->dispersion(c);

            hx_ = new fDispersion_modulo_t<CLAVE> (c); // otra función de dispersión
            int auxb = hx_->dispersion(c);
            return ((auxa+(i*auxb))%nCeldas);
        }
};


template<class CLAVE>
class fExploracion_redispersion_t : public fExploracion_t<CLAVE>{
    private:
        int nCeldas;
        fDispersion_t<CLAVE> *h_;
        fDispersion_t<CLAVE> *hx_;

    public:
        fExploracion_redispersion_t(int n, fDispersion_t<CLAVE>* x): nCeldas(n), h_(x){}

        int exploracion(const CLAVE&c, int i){
            int auxa = h_->dispersion(c);
            switch(i%3){ // 3 es el número de diferentes dispersiones que tengo implementadas, a parte de este
                case 1:
                    hx_ = new fDispersion_modulo_t<CLAVE>(c);
                    break;
                case 2:
                    hx_ = new fDispersion_suma_t<CLAVE>(c);
                    break;
                case 3:
                    hx_ = new fDispersion_rand_t<CLAVE>(c);
                    break;
            }
            int auxb = hx_->dispersion(c);

            return ((auxa+(i*auxb))%nCeldas);
        }
};