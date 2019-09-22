#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h> 
#include "contador_t.hpp"

using namespace std;

    static contador_t contador;

    class DNI_t{ // esta clase la vamos a utilizar como CLAVE
        private:
            int dni[8];
            
        public:
            inline DNI_t(){

            #ifdef DEMOSTRACION
            unsigned i = 0;
            while(i<8){
                dni[i] = 0;
                i++;
            }
            #endif

            #ifdef ESTADISTICA
            srand(time(NULL));
            for(int i=0; i<8; i++){
                dni[i]= rand() % 10;
            }
            #endif

        }
        inline DNI_t(unsigned value){
            #ifdef DESMOSTRACION
            unsigned aux = value;
            unsigned i = 7;
            while(i>=0){
                dni[i] = (aux%10);
                aux = aux / 10;
                i--;
            }
            #endif
            #ifdef ESTADISTICA
            srand(value);
            for(int i=0; i<8; i++){
                dni[i]= rand() % 10;
            }
            #endif
        }
        inline ~DNI_t() {}

        int get_numdni() const{
            int numdni=0;
            for(int i=0; i<7; i++){
                numdni+=dni[i];
                numdni*=10;
            }
            numdni+=dni[7];

            return numdni;
        }

        operator int long() const{
            return get_numdni();
        }


        bool operator == (const DNI_t& otrodni) const{ // devolver si son iguales o no lo son
            ++contador;
            return (get_numdni() == otrodni.get_numdni());
        } 

        void operator = (const int n){
            unsigned aux = n;
            int i = 7;
            while(i>=0){
                dni[i] = (aux%10);
                aux = aux / 10;
                i--;
            }
        }

        unsigned operator % (const int n) const{ 
            return get_numdni()%n; 
        }

        bool operator > (const DNI_t& otrodni) const { 
            ++contador;
            return (get_numdni() > otrodni.get_numdni()); 
        }

        bool operator < (const DNI_t& otrodni) const{ 
            ++contador;
            return (get_numdni() < otrodni.get_numdni()); 
        }

        void write(){
            for(int i=0; i<8; i++){
                cout << dni[i];
            }
        }
        
};