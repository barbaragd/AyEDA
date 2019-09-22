#include "ABB_t.hpp"
#include "DNI_t.hpp"
#include <vector>

using namespace std;

#ifdef DEMOSTRACION

int main(){

    ABB_t<DNI_t> arbol;
    int opcion=1;
    int dato = 0;
    DNI_t dni;
    while(opcion!=0){
        cout << endl << "[!]\t\tMenú" << endl;
        cout << "[0]\tSalir" << endl;
        cout << "[1]\tInsertar Clave" << endl;
        cout << "[2]\tEliminar Clave" << endl;
        cout << "Opción: ";
        cin >> opcion;
        switch (opcion)
        {
            case 1:
                cout << "Dato a introducir: ";
                cin >> dato;
                dni = dato;
                cout << endl;
                arbol.insertar(dni);

                arbol.write();
                break;

            case 2:
                cout << "Dato a eliminar: ";
                cin >> dato;
                dni = dato;
                cout << endl;
                arbol.eliminar(dni);

                arbol.write();                
                break;

            case 0:
                cout << "Saliendo..." << endl;
                break;
        
            default:
                cout << "Opción Incorrecta" << endl;
                break;
        }
    }

}

#endif

#ifdef ESTADISTICA


int main(int argc, char *argv[]){ // ./a.out    N       nPruebas    seed
    // 1. Solicitar los parámetros para el experimento: 
    // a. N: Tamaño del árbol.
    // b. Número de pruebas, nPruebas: Número de repeticiones de la operación,
    // inserción o búsqueda, que se realiza en el experimento.
    
    // Estos parámetros se piden por la línea de comandos

    if(argc!=4){
        cerr << "Error en la línea de comandos" << endl;
        cerr << "./a.out\t\tN\tnPruebas\tseed" << endl;
        return -1;
    }

    int N = atoi(argv[1]);
    int nPruebas = atoi(argv[2]);
    int seed = atoi(argv[3]);

    if(nPruebas > N){
        cerr << "El número de pruebas no puede ser mayor que el tamaño del árbol" << endl;
        return -1;
    }

    // 2. Crear un banco de prueba con 2*N valores de tipo DNI generados de forma
    // aleatoria. El banco de pruebas se guarda en un vector.
    vector<DNI_t> banco;
    for(unsigned j=0; j<2*N; j++){
        banco.push_back(DNI_t(seed*j));    // me peta aquí
    }

    // 3. Generar un árbol binario de búsqueda e insertar los N primeros valores del banco
    // de prueba.
    ABB_t<DNI_t> arbol;
    for(unsigned i=0; i<N; i++){
        arbol.insertar(banco[i]);
    }

    //arbol.write();
    cout << "\t\tN\tnPruebas\tMínimo\tMedio\tMáximo" << endl;

    // 4. El experimento para estudiar el comportamiento de la OPERACIÓN DE BÚSQUEDA
    // consiste en:

    // a. Inicializar a cero los contadores de comparaciones de claves: valores
    // mínimo, acumulado y máximo.
    contador.reset(); 

    // b. Realizar la búsqueda de las nPruebas claves extraídas de forma aleatoria
    // de las primeras N claves del banco de prueba, o sea, de las claves ya
    // insertadas en el ABB. Para cada búsqueda se cuenta el número de
    // comparaciones realizadas, y se actualizan los valores mínimo, máximo y
    // acumulado.
    for(unsigned i=0; i<nPruebas; i++){
        contador.start();
        arbol.buscar(banco[i]);
        contador.end();
    }

    // c. Al finalizar el experimento se presentan los valores mínimo, máximo y medio
    // del número de comparaciones de claves contabilizados.
    cout << "Búsqueda: " << "\t" << N << "\t" << nPruebas << "\t\t" << contador.get_min() << "\t" ;
    cout << contador.get_medio() << "\t" << contador.get_max() << endl;
    //contador.show();


    // 5. El experimento para estudiar el comportamiento de la operación de inserción se
    // basa en contar el número de comparaciones realizado para buscar claves que no
    // se encuentran en el árbol. Consiste en:

    // a. Inicializar a cero los contadores de comparaciones de claves. Valores
    // mínimo, acumulado y máximo.
    contador.reset();

    // b. Realizar la búsqueda de las nPruebas claves extraídas de forma aleatoria
    // de las últimas N claves del banco de prueba, o sea, de las claves que no
    // están insertadas en el ABB. Para cada búsqueda se cuenta el número de
    // comparaciones realizadas, y se actualizan los valores mínimo, máximo y
    // acumulado.
    for(unsigned i=0; i<nPruebas; i++){
        contador.start();
        arbol.buscar(banco[i+N]);
        contador.end();
    }

    // c. Al finalizar el experimento se presentan los valores mínimo, máximo y medio
    // del número de comparaciones de claves contabilizados.
    cout << "Insercción: " << "\t" << N << "\t" << nPruebas << "\t\t" << contador.get_min() << "\t" ;
    cout << contador.get_medio() << "\t" << contador.get_max() << endl;
    // contador.show();

}

#endif