#include "AVL_t.hpp"
#include "DNI_t.hpp"
#include <vector>

using namespace std;

#ifdef DEMOSTRACION

int main(){

    system("clear");
    AVL_t<DNI_t> arbol;

    cout << "-- MODO DEMOSTRACIÓN --" << endl;    

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
    
    system("clear");
    cout << "\t\t-- MODO ESTADÍSTICA --" << endl << endl;

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

    vector<DNI_t> banco;
    for(unsigned j=0; j<2*N; j++){
        banco.push_back(DNI_t((seed + 10000000) + (rand() % 60000000)));    
    }

    AVL_t<DNI_t> arbol;
    for(unsigned i=0; i<N; i++){
        arbol.insertar(banco[i]);
    }

   // arbol.write();
    cout << "\t\tN\tnPruebas\tMínimo\tMedio\tMáximo" << endl;


    contador.reset(); 
    for(unsigned i=0; i<nPruebas; i++){
        contador.start();
        arbol.buscar(banco[i]);
        contador.end();
    }

    cout << "Búsqueda: " << "\t" << N << "\t" << nPruebas << "\t\t" << contador.get_min() << "\t" ;
    cout << contador.get_medio() << "\t" << contador.get_max() << endl;


    contador.reset();
    for(unsigned i=0; i<nPruebas; i++){
        contador.start();
        arbol.buscar(banco[i+N]);
        contador.end();
    }

    cout << "Insercción: " << "\t" << N << "\t" << nPruebas << "\t\t" << contador.get_min() << "\t" ;
    cout << contador.get_medio() << "\t" << contador.get_max() << endl;
}

#endif