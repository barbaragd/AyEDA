#pragma once

#include <iostream>
#include <algorithm>


using namespace std;


template <class T>
class ordenacion_t {

    public:
        ordenacion_t<T>* crear(int m, float x);
        virtual void ordenacion(T*v, int n) = 0;
        void write(T* v,int n){
            for(int i=0; i<n; i++){
                v[i].write();
                cout << "\t";
            }
        }
};


template <class T>
class fSeleccion_t : public ordenacion_t<T>{
    public:
        fSeleccion_t(){
            cout << "[!]    Método de ordenación: Seleccion" << endl;
        }

        void write(T* v,int n){
            for(int i=0; i<n; i++){
                v[i].write();
                cout << "\t";
            }
        }

        void ordenacion(T* v, int n){
            int min;
            T x;

            for (int i = 0; i < n; i++){ 
                min = i ;
                for (int j = i+1; j < n; j++){
                    if (v[j].get_numdni() < v[min].get_numdni()){
                        #ifdef DEMOSTRACION
                        cout << "min = " << v[j] << ", ";
                        #endif
                        min = j ;
                    }
                }
                if(min!=i){
                    x = v[i] ;
                    v[i] = v[min] ;
                    v[min] = x ;
                    #ifdef DEMOSTRACION
                    cout <<  endl <<"Intercambio de posiciones " << min << " y " << i << endl;
                    write(v, n);
                    cout << endl << endl;
                    #endif
                }
            }

        }
};




template <class T>
class fSacudida_t : public ordenacion_t<T>{
    public:
        fSacudida_t(){
            cout << "[!]    Método de ordenación: Sacudida" << endl;
        }

        void write(T* v, int n){
            for(int i=0; i<n; i++){
                v[i].write();
                cout << "\t";
            }
        }

        void ordenacion(T* v, int n){
            int ini = 0;
            int fin = n - 1;
            int cam = n;
            T x;
            while(ini <= fin){
                for(int j = fin; j>=ini; j--){
                    if(v[j] < v[j-1]){
                        x = v[j-1];
                        v[j-1] = v[j];
                        v[j] = x;
                        cam = j;
                        #ifdef DEMOSTRACION
						cout << "\nIntercambio de pos " << j << " y pos " << j-1 << "\n";
						write(v,n);
                        cout << endl;
						#endif
                    }
                }
                ini = cam+1;
                for(int j=ini; j<=fin; j++){
                    if(v[j] < v[j-1]){
                        x = v[j-1];
                        v[j-1] = v[j];
                        v[j] = x;
                        cam = j;
                        #ifdef DEMOSTRACION
						cout << "\nIntercambio de pos " << j << " y pos " << j-1 << "\n";
						write(v,n);
                        cout << endl;
						#endif
                    }
                }
                fin = cam-1;
                #if DEMOSTRACION
                cout << endl;
                #endif
            }
        }
};




template <class T>
class fHeapSort_t : public ordenacion_t<T>{
    public:
        fHeapSort_t(){
            cout << "[!]    Método de ordenación: HeapSort" << endl;
        }


        void write(T* v, int n){
            for(int i=0; i<n; i++){
                v[i].write();
                cout << "\t";
            }
        }


        void ordenacion(T* v, int n){
            T x;
            for(int i=n/2-1; i>=0; i--){
                baja(i,v,n);
            }
            #ifdef DEMOSTRACION
            cout << endl;
            #endif
            for(int i=n-1; i>=0; i--){
                x = v[0];
                v[0] = v[i];
                v[i] = x;
                baja(0,v,i-1);
            }
        }

        void baja(int i, T* v, int n){
            T x = v[i];
            int h, h1, h2;
            while((2*i) < n){
                h1 = 2*i+1;
                h2 = h1 + 1;
                if(h1==n){
                    h = h1;
                }
                else if( (h1 < n) && (v[h1] > v[h2])){
                    h = h1;
                }
                else h = h2;

                if(v[h] <= x) break;
                else{
                    #ifdef DEMOSTRACION
					cout << endl << "Intercambio entre pos " << i << " y pos " << h << endl;
					#endif
                    v[i] = v[h];
                    v[h] = x;
                    #ifdef DEMOSTRACION
					write(v,n);
                    cout << endl;
					#endif
                    i = h;
                }
            }
        }
};



template <class T>
class fMergeSort_t : public ordenacion_t<T>{
    public:
        fMergeSort_t(){
            cout << "[!]    Método de ordenación: MergeSort" << endl;
        }


        void write(T* v, int n){
            for(int i=0; i<n; i++){
                v[i].write();
                cout << "\t";
            }
        }

        void ordenacion(T* v, int n){
            Msort(v, 0, n-1);
        }

        void Msort (T* v, int ini, int fin){ 
            int cen;
            if (ini < fin){ 
                cen = (ini + fin) / 2 ;
                #ifdef DEMOSTRACION
				cout << endl << "Subvector: " << endl;
				write(v,fin-ini+1);
                cout << endl;
				#endif
                Msort (v, ini, cen) ;
                Msort (v, cen+1, fin) ;
                Mezcla (v, ini, cen, fin) ;
            }
        }

        void Mezcla (T*v, int ini, int cen, int fin){
            int i = ini; 
            int j = cen + 1; 
            int k = ini;
            T aux[fin+1];
            while ((i <= cen) && (j <= fin)){ 
                if (v[i] < v[j]){ 
                    aux[k] = v[i] ;
                    i++ ;
                }
                else{ 
                    aux[k] = v[j] ;
                    j++ ;
                }
                k++ ;
            }
            if (i > cen){
                while (j <= fin){
                    aux[k] = v[j] ;
                    j++ ; k++ ;
                }
            }
            else{
                while (i <= cen){
                    aux[k] = v[i] ;
                    i++ ; k++ ;
                }
            }
            for (int k = ini; k <= fin; k++){
                v[k] = aux[k];
            }
            #ifdef DEMOSTRACION
			cout << endl << "Subvector ordenado: " << endl;
			write(v, fin-ini + 1);
            cout << endl;
			#endif
        }
};



template <class T>
class fShellsort_t: public ordenacion_t<T>{
    private:
        float alfa;

    public:
        fShellsort_t(float a): alfa(a){
            cout << "[!]    Método de ordenación: ShellSort" << endl;
        }


        void write(T* v, int n){
            for(int i=0; i<n; i++){
                v[i].write();
                cout << "\t";
            }
        }

        void ordenacion(T* v, int n){
            int del = n * alfa;
            while(del > 0){
                del = del / 2;
                #ifdef DEMOSTRACION
                cout << endl << "Alfa= " << del << endl;
                #endif
                deltasort(del, v, n);
            }
        }

        void deltasort(int d, T* v, int n){
            T x;
            int j;
            bool flag;
            for(int i=d; i<n; i++){
                flag = 0;
                x = v[i];
                j = i;
                while((j >= d) && (x<v[j-d])){
                    v[j] = v[j-d];
                    j = j - d;
                    flag = 1;
                }
                if(flag==1){
                    v[j] = x;
                    #ifdef DEMOSTRACION
                    cout << "Intercambio entre posiciones " <<  i << " y " << j << " \n";
                    write(v, n);
                    cout << endl;
                    #endif
                }
            }
        }
};










template <class T>
ordenacion_t<T>* ordenacion_t<T>::crear(int m, float x){
    ordenacion_t<T>* h;

    switch(m){
        case 1: 
            h = new fSeleccion_t<T>();
            break;
        case 2:
            h = new fSacudida_t<T>();
            break;
        case 3:
            h = new fHeapSort_t<T>();                    
            break;
        case 4:
            h = new fMergeSort_t<T>();
            break;
        case 5:
            h = new fShellsort_t<T>(x);
            break;
    }
    return h;

}