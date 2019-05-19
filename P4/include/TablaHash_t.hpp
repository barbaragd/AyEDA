#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "celda_t.hpp"
#include "fDispersion_t.hpp"
#include "fExplorar_t.hpp"

using namespace std;



template <class CLAVE>
class TablaHash_t{
    private: //tmño es nCeldas-1 x nBloques-1
        unsigned nCeldas; // las celdas son un vector de claves
        unsigned nBloques;
        celda_t<CLAVE> **vCeldas; // puntero a la primera de las celdas de la tabla
        fDispersion_t<CLAVE> *h;
        fExploracion_t<CLAVE> *g;

        unsigned i;

    public:
        TablaHash_t(int c, int b, int fd, int fe): nCeldas(c), nBloques(b){ // en fd esta el 1,2,3,... que indica la fdisp
            vCeldas = new celda_t<CLAVE>* [nCeldas]; 
            for(unsigned i=0; i<nCeldas; i++){
                vCeldas[i] = new celda_t<CLAVE>(nBloques);
            }
            switch(fd){
                case 1:
                    h = new fDispersion_suma_t<CLAVE>(c);
                break;
                case 2:
                    h = new fDispersion_rand_t<CLAVE>(c);
                break;
                case 3:
                    h = new fDispersion_modulo_t<CLAVE>(c);
                break;
                default:
                    cout << "Función de dispersión errónea. Se pondrá la suma por defecto." << endl;
                    h = new fDispersion_suma_t<CLAVE>(c);
            }

            switch(fe){
                case 1:
                    g = new fExploracion_lineal_t<CLAVE>(c, h);
                break;
                case 2:
                    g = new fExploracion_cuadratica_t<CLAVE>(c, h);
                break;
                case 3:
                    g = new fExploracion_doble_dispersion_t<CLAVE>(c, h);
                break;
                case 4:
                    g = new fExploracion_redispersion_t<CLAVE>(c, h);
                break;
                default:
                    cout << "Función de exploración errónea. Se pondrá la lineal por defecto." << endl;
                    g = new fExploracion_lineal_t<CLAVE>(c, h);
            }
        }

        ~TablaHash_t(){
        	if (vCeldas!=NULL){
        		for (int i=0;i<nCeldas;i++){
        			if (vCeldas[i]!=NULL){
        				delete vCeldas[i];
        				vCeldas[i]=NULL;
        			}
        		}
        		delete [] vCeldas;
        	}
        }

        unsigned get_i (){
            return i;
        }

        bool buscar(const CLAVE& c) {
            i = 1;
            bool b=0;
            int pos = h->dispersion(c);

            if(!vCeldas[pos]->buscar(c)){ // si no lo encuentro con la f de dispersión
                while(!b && i<nCeldas){ // mientras no lo encuentre con la f de expl y el num de intentos < num de celdas
                    pos = g->exploracion(c, i);
                    b = vCeldas[pos]->buscar(c);
                    i++;
                }
                return b; // devuelvo si lo he encontrado o no
            }

            else{
                return true; // si lo he encontrado con la f de dispersión
            }

            

          //llamar a la fDispersion para obtener la posición
          // en mi vector vCeldas y en la pos obtenida anteriormente, buscar c
          // si me devuelve un false, llamar a la f de exploración para obtener otra pos
          // al obtener la otra pos, buscar c en mi vector vCeldas
        }
        
        bool insertar(const CLAVE& c){
            i = 1;
            bool b=false;
            int pos = h->dispersion(c);


            if(!vCeldas[pos]->insertar(c)){ // si no lo encuentro con la f de dispersión
                while(!b && i<=nCeldas){ // mientras no lo encuentre con la f de expl y el num de intentos < num de celdas
                    pos = g->exploracion(c, i);
                    b = vCeldas[pos]->insertar(c);
                    i++;
                }
                return b; // devuelvo si lo he encontrado o no
            }

            else{
                return true; // si lo he encontrado con la f de dispersión
            }


          //llamar a la fDispersion para obtener la posición
          // en mi vector vCeldas y en la pos obtenida anteriormente, insertar c
          // si me devuelve un false, llamar a la f de exploración para obtener otra pos
          // al obtener la otra pos, insertar c en mi vector vCeldas
          
        }

        void write(){
            for(unsigned it=0; it<nCeldas; it++){
                for(unsigned j = 0; j<nBloques; j++){
                    cout << setw(10) << vCeldas[it]->get_dato(j) << "|";
                }
                cout << endl;
            }
        }

};