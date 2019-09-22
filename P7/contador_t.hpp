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
            // cout << "Mínimo: " << min << endl;
            // cout << "Máximo: " << max << endl;

            min = (acumulador < min)? acumulador : min;
            max = (acumulador > max)? acumulador : max;
            medio += acumulador;
            numP++;
        }

        int operator ++ (){
            // cout << "Estoy por aquí, con valor: " << acumulador << endl;
            acumulador++;
            return acumulador;
        }

        int get_min(){
            return min;
        }

        int get_max(){
            return max;
        }

        int get_medio(){
            return medio/numP;
        }

        void show(){
            cout << "Mínimo: " << min << endl;
            cout << "Máximo: " << max << endl;
            cout << "Medio: " << medio/numP << endl;
        }

};