#pragma once
#include <iostream>
#include <vector>

#include <cmath>

#include "nodoBB_t.hpp"
#include <deque>

using namespace std;

template<class T>
class ABB_t{
    private:

        nodoBB_t<T>* raiz;

    public:

        ABB_t(): raiz(nullptr) { }
        ~ABB_t(){
            Podar(raiz);
        }

        bool esVacio(nodoBB_t<T>* nodo){
            return nodo == nullptr;
        }

        void Podar(nodoBB_t<T>* nodo) {
            if (nodo == nullptr) return;
            Podar(nodo->izdo);
            Podar(nodo->dcho);
            delete nodo;
            nodo = nullptr;
        }

        bool EsHoja(nodoBB_t<T>* nodo){
            return (!nodo->dcho && !nodo->izdo);
        }

        const int size(){
            return rama_size(raiz);
        }

        const int rama_size(nodoBB_t<T>* nodo){
            if (nodo == nullptr) return 0;
            return (1 + rama_size(nodo->izdo) + rama_size(nodo->dcho));
        }

        const int altura_total(){
            return altura(raiz);
        }

        const int altura(nodoBB_t<T>* nodo){
            if(nodo == nullptr) return 0;
            int alt_i = altura(nodo->izdo);
            int alt_d = altura(nodo->dcho);
            if(alt_d > alt_i) return alt_d++;
            else return alt_i++;
        }

        bool buscar(T dato){
            return buscar_rama(raiz, dato);
        }

        void insertar(T dato){
            if(!buscar(dato)){
                insertar_rama(raiz, dato);
            }
        }

        void eliminar(T dato){
            if(!buscar(dato)){
                cout << "El dato a eliminar no está en el árbol" << endl << endl;
            }
            else eliminar_rama(raiz, dato);
        }

        void inorden(nodoBB_t<T>* nodo){
            if (nodo == nullptr){
                return;
            } 
            inorden(nodo->izdo);
            imprimir(nodo);
            inorden(nodo->dcho);
        }

        void postorden(nodoBB_t<T>* nodo){
            if(nodo == nullptr) return;
            postorden(nodo->izdo) ;
            postorden(nodo->dcho) ;
            imprimir(nodo);
        }

        void preorden(nodoBB_t<T>* nodo){
            if(nodo == nullptr) return;
            imprimir(nodo);
            preorden(nodo->izdo);
            preorden(nodo->dcho);
        }

        void imprimir(nodoBB_t<T>* n){
            if(n == nullptr){
                cout << "[.]";
            }
            else{
                cout << "[";
                n->get_dato().write();
                cout << "]";
            }
        }

        void rec_niveles(nodoBB_t<T>* nodo){

            deque<pair<nodoBB_t<T>*, int>> cola;  // Cola para guardar los nodos por niveles
            nodoBB_t<T>* aux;  // Nodo auxiliar
            int nivel = 0;  // Nivel auxiliar
            int nivel_actual = 0;  // Nivel actual
            cola.push_back(pair<nodoBB_t<T>*, int>(nodo,0));  // Se inserta el primer nodo y nivel (nodo raíz y nivel 0)
            cout << "Nivel 0: ";
            
            while (!cola.empty()){
                aux = cola.front().first;
                nivel = cola.front().second;
                cola.pop_front(); 
                if (nivel > nivel_actual){
                    nivel_actual = nivel;
                    cout << "\nNivel " << nivel_actual << ": ";
                }
                imprimir(aux);
                if (aux != nullptr){
                    cola.push_back(pair<nodoBB_t<T>*,int>(aux->izdo, nivel+1));
                    cola.push_back(pair<nodoBB_t<T>*,int>(aux->dcho, nivel+1));
                }
            }

        }

        void write(){ // implementar recorrido inorden y por niveles
            cout << "Recorrido inorden: " << endl;
            inorden(raiz);
            cout << endl << endl;
            cout << "Recorrido postorden: " << endl;
            postorden(raiz);
            cout << endl << endl;
            cout << "Recorrido preorden: " << endl,
            preorden(raiz);
            cout << endl << endl;
            cout << "Recorrido por niveles: " << endl;
            rec_niveles(raiz);
            cout << endl << endl;
        }

    private:
        unsigned niveles(nodoBB_t<T>* nodo, unsigned n){
            if(nodo == nullptr) return n;
            n = niveles(nodo->izdo, n);
            n = niveles(nodo->dcho, n);
            n++;
            return n;
        }

        bool buscar_rama(nodoBB_t<T>* &nodo, T dato){
            if (nodo == nullptr) return false;
            if (dato == nodo->get_dato()) return true;
            if (dato < nodo->get_dato()) return buscar_rama(nodo->izdo, dato);
            return buscar_rama(nodo->dcho, dato);
        }

        void insertar_rama(nodoBB_t<T>* &nodo, T dato){
            if(nodo == nullptr){
                nodo = new nodoBB_t<T>(dato);
            }
            else{ 
                if (dato < nodo->get_dato())
                    insertar_rama(nodo->izdo, dato);
                else if(dato > nodo->get_dato())
                    insertar_rama(nodo->dcho, dato);
            }   
        }

        void eliminar_rama(nodoBB_t<T>* &nodo, T dato){
            if (nodo == nullptr) return;
            if (dato < nodo->get_dato())
                eliminar_rama(nodo->izdo, dato);
            else if(dato > nodo->get_dato())
                eliminar_rama(nodo->dcho, dato);
            else {
                nodoBB_t<T>* Eliminado = nodo;
                if(nodo->dcho == nullptr)
                    nodo = nodo->izdo;
                else if(nodo->izdo == nullptr)
                    nodo = nodo->dcho;
                else
                    sustituir(Eliminado, nodo->izdo);

                delete Eliminado;
            }
        }


        void sustituir(nodoBB_t<T>* &eliminado, nodoBB_t<T>* &sust){
            if(sust->dcho !=nullptr)
                sustituir(eliminado, sust->dcho);
            else{
                eliminado->set_dato(sust->get_dato());
                eliminado = sust;
                sust = sust->izdo;
            }
        }
};




