#pragma once

#include <iostream>
#include "DNI_t.hpp"

template <class CLAVE>
class celda_t{
    private:
        unsigned nBloques;
        CLAVE *v; 
        unsigned fin=0;

    public:
        celda_t(int n): nBloques(n){
          v = new CLAVE[n];
          fin = 0;
        } // dimension de la celda, tamaño del vector_t

        ~celda_t(){
          if (v != NULL) {
                delete [] v;
                v = NULL;
          }
          nBloques = 0;
        }

        bool buscar(CLAVE c) const{
          for(unsigned i=0; i<nBloques; i++){
            if(v[i] == c){
              return true;
            }
          }
          return false;
        }// devuelve si lo ha encontrado o no , se puede devolver la posición por referencia

        bool insertar(CLAVE c){
          if((!llena()) && (!buscar(c))){ // si esta vacía la celda y si no esta la clave ya dentro
            v[fin] = c;
            fin++;
            return true;
          }
          return false;
        } // true -> lo inserta; false -> no lo inserta
        
        bool llena() const{
          if(fin==nBloques){
            return true;
          }
          return false;
        } // devuelve si la celda en la que hemos buscado está llena o no

        int get_dato(int i){
            return v[i].get_numdni();
        }
};