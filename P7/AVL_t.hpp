#pragma once
#include <iostream>
#include <deque>

#include "nodoAVL_t.hpp"

using namespace std;

template<class T>
class AVL_t {
    private:
        nodoAVL_t<T>* raiz;
    
    public:
        AVL_t(): raiz(nullptr) {}
        ~AVL_t(){ podar(raiz); }

        void podar(nodoAVL_t<T>* nodo);
        void write();
        bool buscar(T dato);
        void insertar(T dato);
        void eliminar(T dato);

    private:
        // Imprimir datos por pantalla
        void rec_niveles(nodoAVL_t<T>* nodo);
        void imprimir(nodoAVL_t<T>* n);
        
        // Buscar
        bool buscar_rama(nodoAVL_t<T>* &nodo, T dato);

        // Insertar
        void insertar_bal(nodoAVL_t<T>* &nodo, nodoAVL_t<T>* nuevo, bool& crece);
        void insert_re_balancea_izda(nodoAVL_t<T>* &nodo, bool& crece);
        void insert_re_balancea_dcha(nodoAVL_t<T>* &nodo, bool& crece);

        // Eliminar
        void eliminar_rama(nodoAVL_t<T>* &nodo, T dato, bool& decrece); ////////////
        void sustituir(nodoAVL_t<T>* &eliminado, nodoAVL_t<T>* &sust, bool &decrece);
        void eliminar_re_balancea_izda(nodoAVL_t<T>* &nodo, bool& decrece);
        void eliminar_re_balancea_dcha(nodoAVL_t<T>* &nodo, bool& decrece);

        // Rotaciones
        void rotacion_DD(nodoAVL_t<T>* &nodo);
        void rotacion_ID(nodoAVL_t<T>* &nodo);
        void rotacion_DI(nodoAVL_t<T>* &nodo);
        void rotacion_II(nodoAVL_t<T>* &nodo);
};

template<class T>
void AVL_t<T>::podar(nodoAVL_t<T>* nodo){
    if (nodo == nullptr) return;
    podar(nodo->izdo);
    podar(nodo->dcho);
    delete nodo;
    nodo = nullptr;
}


// BÚSQUEDA
template<class T>
bool AVL_t<T>::buscar(T dato){
    return buscar_rama(raiz, dato);
}

template<class T>
bool AVL_t<T>::buscar_rama(nodoAVL_t<T>* &nodo, T dato){
    if (nodo == nullptr) return false;
    if (dato == nodo->get_dato()) return true;
    if (dato < nodo->get_dato()) return buscar_rama(nodo->izdo, dato);
    return buscar_rama(nodo->dcho, dato);
}



// INSERCCIÓN
template <class T>
void AVL_t<T>::insertar(T dato){
    nodoAVL_t<T>* nuevo = new nodoAVL_t<T>(dato, 0);
    bool crece = false;
    insertar_bal(raiz, nuevo, crece);
}

template <class T>
void AVL_t<T>::insertar_bal(nodoAVL_t<T>* &nodo, nodoAVL_t<T>* nuevo, bool& crece){
    if(nodo == nullptr){
        nodo = nuevo;
        crece = true;
    }
    else if (nuevo->get_dato() < nodo->get_dato()){
        insertar_bal(nodo->izdo, nuevo, crece);
        if(crece) insert_re_balancea_izda(nodo, crece);
    } 
    else{
        insertar_bal(nodo->dcho, nuevo, crece); 
        if(crece) insert_re_balancea_dcha(nodo, crece);
    }
}

template <class T>
void AVL_t<T>::insert_re_balancea_izda(nodoAVL_t<T>* &nodo, bool& crece){
    switch (nodo->get_bal()){
    case -1:
        nodo->set_bal(0);
        crece = false;
        break;
    
    case 0: 
        nodo->set_bal(1);
        break;

    case 1:
        nodoAVL_t<T>* nnodo = nodo->izdo;
        if(nnodo->get_bal() == 1) rotacion_II(nodo);
        else rotacion_ID(nodo);
        crece = false;
        break;
    }
}

template <class T>
void AVL_t<T>::insert_re_balancea_dcha(nodoAVL_t<T>* &nodo, bool& crece){
    switch (nodo->get_bal()){
    case 1:
        nodo->set_bal(0);
        crece = false;
        break;
    
    case 0: 
        nodo->set_bal(-1);
        break;

    case -1:
        nodoAVL_t<T>* nnodo = nodo->dcho;
        if(nnodo->get_bal() == -1) rotacion_DD(nodo);
        else rotacion_DI(nodo);
        crece = false;
        break;

    }
}



// ELIMINAR
template <class T>
void AVL_t<T>::eliminar(T dato){
    bool decrece = false;
    eliminar_rama(raiz, dato, decrece);
}

template <class T>
void AVL_t<T>::eliminar_rama(nodoAVL_t<T>* &nodo, T dato, bool& decrece){
    if (nodo == nullptr) return;
    if (dato < nodo->get_dato()){
        eliminar_rama(nodo->izdo, dato, decrece);
        if(decrece) eliminar_re_balancea_izda(nodo, decrece);
    }
    else if(dato > nodo->get_dato()){
        eliminar_rama(nodo->dcho, dato, decrece);
        if(decrece) eliminar_re_balancea_dcha(nodo, decrece);
    }
    else {
        nodoAVL_t<T>* Eliminado = nodo;
        if(nodo->izdo == nullptr){
            nodo = nodo->dcho;
            decrece = true;
        }
        else if(nodo->dcho == nullptr){
            nodo = nodo->izdo;
            decrece = true;
        }
        else{
            sustituir(Eliminado, nodo->izdo, decrece);
            if(decrece) eliminar_re_balancea_izda(nodo, decrece);
        }
        delete Eliminado;
    }
}

template <class T>
void AVL_t<T>::sustituir(nodoAVL_t<T>* &eliminado, nodoAVL_t<T>* &sust, bool &decrece){
    if(sust->dcho !=nullptr){
        sustituir(eliminado, sust->dcho, decrece);
        if(decrece) eliminar_re_balancea_dcha(sust, decrece);
    }
    else{
        eliminado->set_dato(sust->get_dato());
        eliminado = sust;
        sust = sust->izdo;
        decrece = true;
    }
}

template<class T>
void AVL_t<T>::eliminar_re_balancea_izda(nodoAVL_t<T>* &nodo, bool& decrece){
    nodoAVL_t<T>* nnodo = nodo->dcho;
    switch (nodo->get_bal()){
    case -1:
        if(nnodo->get_bal() > 0) rotacion_DI(nodo);
        else if (nnodo->get_bal() == 0){
            decrece = false;
            rotacion_DD(nodo);
        }
        break;
    case 0: 
        nodo->set_bal(-1);
        decrece = false;
        break;
    case 1:
        nodo->set_bal(0);  
        break;  
    }
}

template<class T>
void AVL_t<T>::eliminar_re_balancea_dcha(nodoAVL_t<T>* &nodo, bool& decrece){
    nodoAVL_t<T>* nnodo = nodo->izdo;
    switch (nodo->get_bal()){
    case 1:
        if(nnodo->get_bal() < 0) rotacion_ID(nodo);
        else if (nnodo->get_bal() == 0){
            decrece = false;
            rotacion_II(nodo);
        }
        break;
    case 0: 
        nodo->set_bal(1);
        decrece = false;
        break;
    case -1:
        nodo->set_bal(0);    
        break;
    }
}



// ROTACIONES
template <class T>
void AVL_t<T>::rotacion_II(nodoAVL_t<T>* &nodo){
    nodoAVL_t<T>* nnodo = nodo->izdo;
    nodo->izdo = nnodo->dcho;
    nnodo->dcho = nodo;

    if(nnodo->get_bal() == 1){
        nodo->set_bal(0);
        nnodo->set_bal(0);
    }
    else{
        nodo->set_bal(1);
        nnodo->set_bal(-1);
    }
    nodo = nnodo;
}

template <class T>
void AVL_t<T>::rotacion_DD (nodoAVL_t<T>* &nodo) {
    nodoAVL_t<T>* nnodo = nodo->dcho;
    nodo->dcho = nnodo->izdo;
    nnodo->izdo = nodo;

    if(nnodo->get_bal() == -1){
        nodo->set_bal(0);
        nnodo->set_bal(0);
    }
    else{
        nodo->set_bal(-1);
        nnodo->set_bal(1);
    }
    nodo = nnodo;
}

template <class T>
void AVL_t<T>::rotacion_ID (nodoAVL_t<T>* &nodo) {
    nodoAVL_t<T>* nnodo1 = nodo->izdo;
    nodoAVL_t<T>* nnodo2 = nnodo1->dcho;
    nodo->izdo = nnodo2->dcho;
    nnodo2->dcho = nodo;
    nnodo1->dcho = nnodo2->izdo;
    nnodo2->izdo = nnodo1;

    if(nnodo2->get_bal() == -1) nnodo1->set_bal(1);
    else nnodo1->set_bal(0);

    if(nnodo2->get_bal() == 1) nodo->set_bal(-1);
    else nodo->set_bal(0);
    
    nnodo2->set_bal(0);
    nodo = nnodo2;
}

template <class T>
void AVL_t<T>::rotacion_DI (nodoAVL_t<T>* &nodo) {
    nodoAVL_t<T>* nnodo1 = nodo->dcho;
    nodoAVL_t<T>* nnodo2 = nnodo1->izdo;
    nodo->dcho = nnodo2->izdo;
    nnodo2->izdo = nodo;
    nnodo1->izdo = nnodo2->dcho;
    nnodo2->dcho = nnodo1;

    if(nnodo2->get_bal() == 1) nnodo1->set_bal(-1);
    else nnodo1->set_bal(0);

    if(nnodo2->get_bal() == -1) nodo->set_bal(1);
    else nodo->set_bal(0);
    
    nnodo2->set_bal(0);
    nodo = nnodo2;
}


// Mostrar por pantalla
template <class T>
void AVL_t<T>::write(){
    cout << "Recorrido por niveles: " << endl;
    rec_niveles(raiz);
    cout << endl ;
}

template <class T>
void AVL_t<T>::rec_niveles(nodoAVL_t<T>* nodo){

    deque<pair<nodoAVL_t<T>*, int>> cola;  // Cola para guardar los nodos por niveles
    nodoAVL_t<T>* aux;  // Nodo auxiliar
    int nivel = 0;  // Nivel auxiliar
    int nivel_actual = 0;  // Nivel actual
    cola.push_back(pair<nodoAVL_t<T>*, int>(nodo,0));  // Se inserta el primer nodo y nivel (nodo raíz y nivel 0)
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
            cola.push_back(pair<nodoAVL_t<T>*,int>(aux->izdo, nivel+1));
            cola.push_back(pair<nodoAVL_t<T>*,int>(aux->dcho, nivel+1));
        }
    }
}

template <class T>
void AVL_t<T>::imprimir(nodoAVL_t<T>* n){
    if(n == nullptr){
        cout << "[.]";
    }
    else{
        cout << "[";
        n->get_dato().write();
        cout << "]";
    }   
}