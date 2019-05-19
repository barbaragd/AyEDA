#include <iostream>
#include "ordenacion_t.hpp"
#include <stdlib.h>
#include "DNI_t.hpp"


using namespace std;

int main(int argc, char *argv[]) { // tamaño de la secuencia y el algoritmo. Y el modo del main
    #ifdef DEMOSTRACION

    int m = atoi(argv[2]);
    if((m==5) && (argc!=4)){
        cout << "[!]    Algoritmo: ShellSort" << endl;
        cout << "Introduzca las opciones correctamente por la línea de comandos" << endl;
        cout << "./main    tamaño de la secuencia      5    alfa" << endl;  return 0;
    }
    
    else if((m!=5) && ((argc != 3) || (*argv[1]=='h'))){
        cout << "Introduzca las opciones por la línea de comandos" << endl;
        cout << "./main    tamaño de la secuencia      algoritmo" << endl;

        cout << "[!]    Para el tamaño de la secuencia, introducir un número entero (máximo 25)" << endl;
        
        cout << "[!]    Selección del algoritmo: " << endl;
        cout << "\t\t [1]   Seleccion" << endl;
        cout << "\t\t [2]   Sacudida" << endl;
        cout << "\t\t [3]   HeapSort" << endl;
        cout << "\t\t [4]   MergeSort" << endl;
        cout << "\t\t [5]   ShellSort" << endl;     return 0;
    }
    else{
        if((m > 6) || (m <= 0)){
            cout << "Algoritmo erróneo" << endl;
            cout << "[!]    Selección del algoritmo: " << endl;
            cout << "\t\t [1]   Seleccion" << endl;
            cout << "\t\t [2]   Sacudida" << endl;
            cout << "\t\t [3]   HeapSort" << endl;
            cout << "\t\t [4]   MergeSort" << endl;
            cout << "\t\t [5]   ShellSort" << endl;
            return 0;
        }

        int N=atoi(argv[1]);
        if(N >= 25)  N = 25;
        float x=0;

        if(m == 5){
            x = atof(argv[3]);
        }

        DNI_t* v = new DNI_t[N];
        for(unsigned i =0; i<N; i++){
            v[i] = DNI_t(i*10);
        }

        cout << "Vector desordenado: " << endl;
        for(unsigned i=0; i<N; i++){
            v[i].write();
            cout << "\t";
        }

        cout << endl << endl;

        ordenacion_t<DNI_t>* metodo;

        metodo = metodo->crear(m, x);
        
        cout << endl;
        metodo->ordenacion(v, N);

        cout << endl << endl << "Vector ordenado: " << endl;
        metodo->write(v, N);
        cout << endl;
    }
    #endif



    #ifdef ESTADISTICA // pedir N (num elementos del vector) y nPruebas
    if(argc!=3){
        cout << "Introduzca correctamente los parámetros por la línea de comandos" << endl;
        cout << "./main     tamaño de la secuencia      nPruebas" << endl;
        return 0;
    }

    int N=atoi(argv[1]);
    // if(N >= 25)  N = 25;

    int nPruebas=atoi(argv[2]);

    float x = 0.8;
    ordenacion_t<DNI_t>* metodo;
    for(int m=1; m<=5; m++){
        metodo = metodo->crear(m, x);

        contador.reset();
        for(int i=1; i<=nPruebas; i++){
            DNI_t* v = new DNI_t[N];
            for(unsigned j=0; j<N; j++){
                v[j] = DNI_t(i*j*10);
            }

            // cout << endl << "Vector desordenado: " << endl;
            // for(unsigned j=0; j<N; j++){
            //     v[j].write();
            //     cout << "\t";
            // }
            contador.start();
            // cout << endl;
            metodo->ordenacion(v, N);
            contador.end();

            // cout << endl << "Vector ordenado: " << endl;
            // metodo->write(v, N);
            // cout << endl << endl << endl;
        }
        contador.show();
        cout << endl;
    }


    #endif


}