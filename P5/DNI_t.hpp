#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h> 
#include <time.h>
#include <string>

#include "contador_t.hpp"
static contador_t contador;

using namespace std;

class DNI_t{ // esta clase la vamos a utilizar como CLAVE
    private:
        unsigned dni[8];
        
    public:
        inline DNI_t(){
            srand(time(NULL));
            for(int i=0; i<8; i++){
                dni[i]= rand() % 10;
            }
            // string abc="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            // dni[8]= abc[rand()% 27];
        }

        inline DNI_t(int seed){
            srand(seed);
            for(int i=0; i<8; i++){
                dni[i]= rand() % 10;
            }
            // string abc="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            // dni[8]= abc[rand()% 27];
        }
        inline ~DNI_t() {}

        int get_numdni() const{
            int x = 1;
            int numdni = 0;
            for(int i=7; i>=0; i--){
                numdni +=  dni[i] * x;
                x = x * 10;
            }
            return numdni;
        }

        operator unsigned long() const{
            // cout << get_numdni() << endl;
            return get_numdni();
        }


        bool operator == (const DNI_t& otrodni) const{ // devolver si son iguales o no lo son
            ++contador;
            return (get_numdni() == otrodni.get_numdni());
        } 

        void operator = (const int n){
            unsigned aux = n;
            unsigned i = 0;
            while(aux<10){
                dni[i] = (aux%10);
                aux = aux / 10;
                i++;
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