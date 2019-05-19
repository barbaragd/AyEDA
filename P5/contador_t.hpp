#pragma once

#define MAX 999999

using namespace std;
class contador_t{

    public:
        int min;
        int max;
        int medio;
        int acumulador;
        int numP;

    public:
        contador_t(){
            reset();
        }
        ~contador_t(){}

        void reset(){
            min = MAX;
            max = 0;
            medio = 0;
            acumulador = 0;
            numP = 0;
        }

        void start(){
            acumulador = 0;
        }

        void end(){
            if(acumulador < min) min = acumulador;
            if(acumulador > max) max = acumulador;
            medio += acumulador;
            numP++;
        }

        int operator ++ (){
            return acumulador++;
        }

        void show(){
            cout << "Mínimo:\t" << min << endl;
            cout << "Máximo:\t" << max << endl;
            cout << "Medio:\t" << medio/numP << endl;
        }

};