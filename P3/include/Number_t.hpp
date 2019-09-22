#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <exception>
#include "../include/NumberBase_t.hpp"

using namespace std;

template <size_t N, size_t B, class T=char> 
class Number_t: public NumberBase_t{

    private:
        T* digitos_;
        int signo_; 


        void to_base(const int dato);
        char set_char(int entero) const;
        unsigned set_int(char letra) const;

        void reservar();
        void liberar();

        int v_absoluto() const;

        Number_t<N,B,T> sumar(const Number_t<N,B,T>& sumando, Number_t<N,B,T>& resultado) const;
        Number_t<N,B,T> restar(const Number_t<N,B,T>& restando, Number_t<N,B,T>& resultado) const;
        Number_t<N,B,T> multiplicar(const Number_t<N,B,T>& multiplicador, Number_t<N,B,T>& resultado) const;

        bool check_overflow(int n1, int n2, bool op) const;
        bool check_underflow(int n1, int n2) const;


    public:

        Number_t(int dato=0);
        Number_t(const Number_t<N,B,T>& n);

        ~Number_t();

        int get_signo() const;
        unsigned get_digito(int i) const;

        void set_signo(int x);
        void set_digito(unsigned i, char x);

        ostream& write(ostream& os) const;

        Number_t<N,B,T>  mayor(const Number_t<N,B,T>& a, const Number_t<N,B,T>& b) const;
        Number_t<N,B,T>  menor(const Number_t<N,B,T>& a, const Number_t<N,B,T>& b) const;

        Number_t<N,B,T>& operator =(const Number_t<N,B,T>& n);
        Number_t<N,B,T> operator +(const Number_t<N,B,T>& n) const;
        Number_t<N,B,T> operator -(const Number_t<N,B,T>& n) const;
        Number_t<N,B,T> operator *(const Number_t<N,B,T>& n) const;

        NumberBase_t& operator +(const NumberBase_t& n) const;
        NumberBase_t& operator -(const NumberBase_t& n) const;
        NumberBase_t& operator *(const NumberBase_t& n) const;

        NumberBase_t* duplicate() const;

        // Number_t<N+1,B,T> overflow ();

};


class numberexception_t: public std::exception{};

class overflow: public numberexception_t{
    public:
        virtual const char *what(void) const throw(){
            return "Se ha producido overflow";
        }
};

class underflow: public numberexception_t{
    public:
        virtual const char *what(void) const throw(){
            return "Se ha producido underflow";
        }
};



template<class T>
class BinaryNumber: public Number_t<8,2,T>{
    public:
        BinaryNumber(int dato): Number_t<8,2,T>(dato){}
};



template<class T>
class OctalNumber: public Number_t<8,8,T>{
    public:
        OctalNumber(int dato): Number_t<8,8,T>(dato){}
};



template<class T>
class DecimalNumber: public Number_t<8,10,T>{
    public: DecimalNumber(int dato): Number_t<8,10,T>(dato){}
};



template<class T>
class HexadecimalNumber: public Number_t<8,16,T>{
    public:
        HexadecimalNumber(int dato): Number_t<8,16,T>(dato){}
};







// todos los métodos (prototipos) tienen que coincidir con la clase base

template <size_t N, size_t B, class T> 
Number_t<N,B,T>::Number_t(int dato): NumberBase_t(N,B), digitos_(NULL){
    if(dato < 0)
        signo_ = -1;
    else
        signo_ = 1;
    reservar();
    dato = dato * signo_;
    to_base(dato);
}


template <size_t N, size_t B, class T> 
Number_t<N,B,T>::Number_t(const Number_t<N,B,T>& n): NumberBase_t(N,B), digitos_(NULL), signo_(n.signo_){
    reservar();
    for(unsigned i = 0; i < N; i++){
        digitos_[i] = n.digitos_[i];
    }
}


template <size_t N, size_t B, class T> 
Number_t<N,B,T>::~Number_t(){
    liberar();
}


template <size_t N, size_t B, class T> 
ostream& Number_t<N,B,T>::write(ostream& os) const{
    if(signo_<0){
        os << "- ";
    }
    else{
        os << "+ ";
    }
    try{
        for(unsigned k=0; k<N; k++){
            os <<  digitos_[k];
        }
    }
    catch (exception& e){
        cout << e.what() << endl;
    }
    os << endl;
    return os;
}

template <size_t N, size_t B, class T> 
void Number_t<N,B,T>::reservar(){
    try{
        digitos_ = new T[N];
    }
    catch (exception& e){
        cout << e.what() << endl;
    }
}


template <size_t N, size_t B, class T> 
void Number_t<N,B,T>::liberar(){
    try{
        delete[] digitos_;
    }
    catch (exception& e){
        cout << e.what() << endl;
    }
}


template <size_t N, size_t B, class T> 
int Number_t<N,B,T>::get_signo() const{
    return signo_;
}


template <size_t N, size_t B, class T>
int Number_t<N,B,T>::v_absoluto() const{ 
    int v=0;
    for (unsigned i = 0; i < N; i++){
        v += (get_digito(N-1-i) * int(pow(B, i)));
    }
    return v;
}


template <size_t N, size_t B, class T>
unsigned Number_t<N,B,T>::get_digito(int i) const{
    char letra = digitos_[i];
    unsigned valor = set_int(letra);
    return valor;
}


// OPERADORES
template <size_t N, size_t B, class T> 
Number_t<N,B,T>& Number_t<N,B,T>::operator=(const Number_t<N,B,T>& n){
    liberar();
    reservar();

    for(unsigned i = 0; i<N; i++){
        digitos_[i] = n.digitos_[i];
    }

    signo_ = n.signo_;

    return *this;
}


template <size_t N, size_t B, class T> 
Number_t<N,B,T> Number_t<N,B,T>::operator+(const Number_t<N,B,T>& n) const{
    Number_t<N,B,T> resultado(0);
    if(signo_ == n.signo_){
        if(check_overflow(v_absoluto(), n.v_absoluto(), false)==true){
            throw overflow();
        }
        resultado.signo_ = signo_;
        return sumar(n, resultado);
    }
    else{
        if(v_absoluto() > n.v_absoluto()){
            resultado.signo_ = signo_;
        }
        else{
            resultado.signo_ = n.signo_;
        }
        return restar(n, resultado);
    }
}

template <size_t N, size_t B, class T> 
NumberBase_t& Number_t<N,B,T>::operator+(const NumberBase_t& n) const{
    auto sumando = dynamic_cast<const Number_t<N,B,T>&> (n);
    auto resultado = dynamic_cast<Number_t<N,B,T>*> (duplicate());
    *resultado = *this + sumando;
    return *resultado;
}


template <size_t N, size_t B, class T> 
Number_t<N,B,T> Number_t<N,B,T>::operator-(const Number_t<N,B,T>& n) const{
    
    Number_t<N,B,T> resultado(0);
    if(signo_ == n.signo_){
        if(check_underflow(v_absoluto(), n.v_absoluto())==true){
            throw underflow();
        }
        if(v_absoluto() > n.v_absoluto()){
            resultado.signo_ = signo_;
        }
        else{
            resultado.signo_ = -1;
        }
        return restar(n, resultado);
    }
    else{
        resultado.signo_ = signo_;
        return sumar(n, resultado);
    }
}


template <size_t N, size_t B, class T> 
NumberBase_t& Number_t<N,B,T>::operator-(const NumberBase_t& n) const{
    auto sumando = dynamic_cast<const Number_t<N,B,T>&> (n);
    auto resultado = dynamic_cast<Number_t<N,B,T>*> (duplicate());
    *resultado = *this - sumando;
    return *resultado;
}


template <size_t N, size_t B, class T> 
Number_t<N,B,T> Number_t<N,B,T>::operator*(const Number_t<N,B,T>& n) const{

    if(check_overflow(v_absoluto(), n.v_absoluto(), true)==true){
        throw overflow();
    }

    Number_t<N,B,T> resultado(0);
    if(signo_ == n.signo_){
        resultado.signo_ = 1;
    }
    else{
        resultado.signo_ = -1;
    }
    return multiplicar(n, resultado);
}


template <size_t N, size_t B, class T> 
NumberBase_t& Number_t<N,B,T>::operator*(const NumberBase_t& n) const{
    auto sumando = dynamic_cast<const Number_t<N,B,T>&> (n);
    auto resultado = dynamic_cast<Number_t<N,B,T>*> (duplicate());
    *resultado = *this * sumando;
    return *resultado;
}


////////


template <size_t N, size_t B, class T> 
void Number_t<N,B,T>::to_base(const int dato){ // se genera una excepción cuando el valor a representar se sale de los N dígitos
    unsigned d = dato;
    unsigned resto;
    unsigned cociente = dato;
    vector<char> aux;

    while(cociente >= B){

        cociente = d / B;
        resto = d%B;
        d = cociente;

        aux.push_back(set_char(resto));
    }
    // tengo que meter el cociente en el vector tmb, el cociente de la ultima division
    aux.push_back(set_char(cociente));

    while(aux.size() < N){
        aux.push_back('0'); // relleno el resto del vector auxiliar con 0
    }

    unsigned i = N-1;
    unsigned j = 0;
    char valor;

    while(i>=0 && j<N){ // lo introduzco en mi vector digitos, el atributo de mi clase
        valor = aux[i];
        digitos_[j] = valor;
        i--;
        j++;
    }

}


template <size_t N, size_t B, class T> 
char Number_t<N,B,T>::set_char(int entero) const{
    int c=10;
    char l='A';
    char letra;
    if(entero>=10){
        while(entero!=c){
            c++;
            l++;
        }
        letra = l;
    }

    else {
        letra = entero + '0'; // convertir de int a char
    }

    return letra;
}


template <size_t N, size_t B, class T> 
unsigned Number_t<N,B,T>::set_int(char letra) const{
    unsigned c=10;
    char l='A';
    unsigned entero;

    while(letra!=l && c<B){
        c++;
        l++;
    }
    if(letra==l){
        return c;
    }
    else{
        entero = letra - '0'; // convertir de int a char
        return entero;
    }

}



template <size_t N, size_t B, class T> 
Number_t<N,B,T>  Number_t<N,B,T>::mayor(const Number_t<N,B,T>& a, const Number_t<N,B,T>& b) const{

    unsigned valor1, valor2;

    if((a.signo_ == b.signo_) && (a.signo_ == 1)){ // si son del mismo signo (positivo) , devolver el de mayor valor absoluto
        for(unsigned i=0; i<N; i++){
            valor1 = a.digitos_[i] - '0';
            valor2 = b.digitos_[i] - '0';
            if(valor1 > valor2){
                return a;
            }
            else if(valor1 < valor2){
                return b;
            }
        }
        return a;
    }
    else if((a.signo_ == b.signo_) && (a.signo_ == -1)){ // si son del mismo signo (negativo), devolver el de menor valor absoluto
        for(unsigned i=0; i<N; i++){
            valor1 = a.digitos_[i] - '0';
            valor2 = b.digitos_[i] - '0';
            if(valor1 > valor2){
                return b;
            }
            else if(valor1 < valor2){
                return a;
            }
        }
        return a;
    }
    else{ // si no son del mismo signo, devolver el de signo positivo (el mayor)
        if(a.signo_ == 1){
            return a;
        }
        else{
            return b;
        }
    }
}


template <size_t N, size_t B, class T> 
Number_t<N,B,T>  Number_t<N,B,T>::menor(const Number_t<N,B,T>& a, const Number_t<N,B,T>& b) const{

    unsigned valor1, valor2;

    if((a.signo_ == b.signo_) && (a.signo_ == 1)){ // si son del mismo signo (positivo)
        for(unsigned i=0; i<N; i++){
            valor1 = a.digitos_[i] - '0';
            valor2 = b.digitos_[i] - '0';
            if(valor1 < valor2){
                return a;
            }
            else if(valor1 > valor2){
                return b;
            }
        }
        return a;
    }
    else if((a.signo_ == b.signo_) && (a.signo_ == -1)){ // si son del mismo signo (negativo), devolver el de mayor v absoluto
        for(unsigned i=0; i<N; i++){
            valor1 = a.digitos_[i] - '0';
            valor2 = b.digitos_[i] - '0';
            if(valor1 < valor2){
                return b;
            }
            else if(valor1 > valor2){
                return a;
            }
        }
        return a;
    }
    else{ // si no son del mismo signo, devolver el de signo negativo
        if(a.signo_ == -1){
            return a;
        }
        else{
            return b;
        }
    }

}


template <size_t N, size_t B, class T> 
Number_t<N,B,T> Number_t<N,B,T>::sumar(const Number_t<N,B,T>& sumando, Number_t<N,B,T>& resultado) const{

    unsigned suma=0; // resultados que voy obteniendo
    unsigned ac=0; // carry
    unsigned valor1, valor2; // valores que voy a sumar
    vector<char> resultado_suma; // vector donde guardo el resultado de la suma

    int i = N-1; // posición de los vectores en Number_t que voy a sumar

    while(i>=0){ // Mientras la pos no llegue a 0
        valor1 = set_int(digitos_[i]);
        valor2 = sumando.set_int(sumando.digitos_[i]); // tomo el valor de sumando en una variable char
        suma = valor1 + valor2 + ac; // guardo en r la suma de los valores anteriores mas el caryy
        ac=0; // pongo el acumulador a cero otra vez

        if(suma>=B){ // si el resultado de la suma es mayor que la base
            while(suma>=B){
                ac = 1; // me llevo una
                suma = suma - B; // al resultado le quito la base, y ese será mi r
            }
        }
        resultado_suma.push_back(set_char(suma));

        i--;
    }
    i = N-1;
    int j = 0;
    while(i>=0){
        resultado.digitos_[j] = resultado_suma[i];
        i--;
        j++;
    }

    return resultado;
    
}


template <size_t N, size_t B, class T> 
Number_t<N,B,T> Number_t<N,B,T>::restar(const Number_t<N,B,T>& restando, Number_t<N,B,T>& resultado) const{
    //Number_t<N,B,T> resultado; // para guardar el resultado

    int r=0; // resultados que voy obteniendo
    unsigned ac=0; // carry
    unsigned valor1, valor2; // valores que voy a sumar
    vector<char> resultado_resta; // vector donde guardo el resultado de la resta

    int i = N-1; // posición de los vectores en Number_t que voy a restar

    while(i>=0){ // Mientras la pos no llegue a 0
        valor1 = set_int(digitos_[i]);
        valor2 = restando.set_int(restando.digitos_[i]); // tomo el valor de sumando en una variable char
        r = valor1 - valor2 - ac; // guardo en r la resta de los valores anteriores menos el carry
        if(r<0){
            r = r + B;
            ac = 1;
        }
        else{
            ac=0; // pongo el acumulador a cero otra vez
        }

        resultado_resta.push_back(set_char(r));

        i--;
    }


    i = N-1;
    int j = 0;
    while(i>=0){
        resultado.digitos_[j] = resultado_resta[i];
        i--;
        j++;
    }

    if(ac!=0){
        int a = int(pow(B, N)); // tengo en a = [B]00..0 del tamaño de N+1
        int v = a - resultado.v_absoluto();
        resultado.to_base(v);
    }


    return resultado;
}


template <size_t N, size_t B, class T> 
Number_t<N,B,T> Number_t<N,B,T>::multiplicar(const Number_t<N,B,T>& multiplicador, Number_t<N,B,T>& resultado) const{
    for(int i=0; i<multiplicador.v_absoluto(); i++){
        resultado = sumar(resultado, resultado);
    }
    return resultado;
}


template <size_t N, size_t B, class T> 
NumberBase_t* Number_t<N,B,T>::duplicate() const{  
    return new Number_t; 
}




template <size_t N, size_t B, class T> 
bool Number_t<N,B,T>::check_overflow(int n1, int n2, bool op) const{
    // false para la suma
    // true para la multiplicación 
    size_t a = pow(B,N) - 1;
    size_t b;
    if (op==false)
        b = n1 + n2;
    else
        b = n1 * n2;

    if(a < b) return true;
    else return false;
}



template <size_t N, size_t B, class T> 
bool Number_t<N, B, T>::check_underflow(int n1, int n2) const{
    size_t a = pow(B,N);
    size_t b = n1 + n2;

    if(a < b) return true;
    else return false;
}


// modificación
// template <size_t N, size_t B, class T> 
// Number_t<N+1,B,T> Number_t<N,B,T>::overflow(){
//     Number_t<N+1,B,T> a;
//     a.set_signo(signo_);
//     a.set_digito(0, '0');
//     for(unsigned i=1; i<N; i++){
//         a.set_digito(i, digitos_[i-1]);
//     }
//     a.set_digito(N, digitos_[N-1]);
//     return a;
// }


template <size_t N, size_t B, class T> 
void Number_t<N,B,T>::set_signo(int x){
    signo_ = x;
}


template <size_t N, size_t B, class T> 
void Number_t<N,B,T>::set_digito(unsigned i, char x){
    digitos_[i] = x;
}