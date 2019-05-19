#include <iostream>
#include <stdlib.h> 
#include "../include/TablaHash_t.hpp"
#include "../include/DNI_t.hpp"
#include "../include/contador_t.hpp"
#define EPS 10E-2


using namespace std;


int main (){
    // apartado 1
    /**********************************
     * TABLA *
    ***********************************/
    int nC, nB, fd, fe;

    cout << "------------------------------------------" << endl;

    cout << "[!]    Crear Tabla Hash: " << endl;
    cout << "Introduzca número de celdas: ";
    cin >> nC;
    cout << "Introduzca número de bloques por celda: ";
    cin >> nB;

    cout << "------------------------------------------" << endl;

    cout << "[!]    Seleccione función de Dispersión: "<< endl;
    cout << "1\t\tSuma"<< endl;
    cout << "2\t\tPseudo-aleatoria"<< endl;
    cout << "3\t\tMódulo" << endl;
    cout << "Opción: ";
    cin >> fd;

    cout << "------------------------------------------" << endl;

    cout << "[!]    Selecciones función de Exploración: "<< endl;
    cout << "1\t\tLineal"<< endl;
    cout << "2\t\tCuadrática"<< endl;
    cout << "3\t\tDoble Dispersión"<< endl;
    cout << "4\t\tRedispersión"<< endl;
    cout << "Opción: ";
    cin >> fe;


    TablaHash_t<DNI_t>* tabla = new TablaHash_t<DNI_t>(nC, nB, fd, fe);
   

    
    /**********************************
     * PRUEBAS *
    ***********************************/
    // apartado 2

    double factor;
    unsigned N;
    unsigned nPruebas; 
    cout << "---------------------------------------------------" << endl;
    cout << "Indique el factor de carga (valor entre 0 y 1): ";
    cin >> factor;
    cout << "---------------------------------------------------" << endl;
    cout << "Indique el número de pruebas: ";
    cin >> nPruebas;
    cout << "---------------------------------------------------" << endl << endl;

    // apartado 3
    // BANCO DE PRUEBA
    N = (factor * nC * nB);
    DNI_t** banco = new DNI_t*[2*N];
    for(unsigned i =0; i<2*N; i++){
        banco[i] = new DNI_t(rand()%10000000 + 99999999);
    }

    
    // apartado 4
    // insertar en la tabla hash los N primeros valores sacados del banco de prueba hasta alcanzar el factor indicado
    unsigned i = 0;
    double fac = 0;
    while((tabla->insertar(*banco[i])) && (fabs(fac - factor)>EPS)){
        i++;
        fac = (double(i) / double(nC * nB));
    }
    tabla->write();



    // // apartado 5
    i=0;
    int x;

    // Realizar la búsqueda de las nPruebas claves extraídas de forma aleatoria de las
    // primeras N claves del banco de prueba, o sea, de las claves que están guardadas
    // en la tabla hash. Para cada búsqueda se cuenta el número de comparaciones
    // realizadas, y se actualizan los valores mínimo, máximo y acumulado.

    cout << endl;

    contador.reset();
    while(i<nPruebas){
        x = rand()%(N-1);
        contador.start();
        tabla->buscar(*banco[x]); 
        i++;
        contador.end();
    }

    cout << endl;

    cout << endl << "BÚSQUEDAS" << endl;
    contador.show();


    // apartado 6
    

    // // Realizar la búsqueda de las nPruebas claves extraídas de forma aleatoria de las N
    // // últimas claves del banco de prueba, las que no están guardadas en la tabla hash.
    // // Para cada búsqueda se cuenta el número de comparaciones realizadas, y se
    // // actualizan los valores mínimo, máximo y acumulado.

    i = 0;
    contador.reset();
    while(i<nPruebas){
        x = rand()%(N-1);
        contador.start();
        tabla->insertar(*banco[x+N]); 
        i++;
        contador.end();
    }

    cout << endl << "INSERCCIÓN" << endl;
    contador.show();





    // mostrar por pantalla
    cout << endl << "-------------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "Número de celdas\tNúmero de bloques\tF. Dispersión\tF. Exploración\tFactor de carga\t\tNúmero de Pruebas" << endl;
    cout << nC << "\t\t\t" << nB << "\t\t\t" << fd << "\t\t" << fe << "\t\t" << factor << "\t\t\t" << nPruebas << endl;

    cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    
}