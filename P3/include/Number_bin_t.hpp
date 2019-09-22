#pragma once
#include "../include/Number_t.hpp"
#include <vector>
#include <math.h>

using namespace std;

// Especialización de la template para numeros en binario
template<size_t N, class T>
class Number_t<N,2,T> : public NumberBase_t {
    private:
        T* digitos_;

        void to_base(const int dato);
        char set_char(int entero) const;
        unsigned set_int(char letra) const;

        unsigned get_digito(int i) const;
        void set_digito(unsigned i, char x) const;


        void reservar();
        void liberar();

        int v_absoluto() const;
        void complemento2() const;

        Number_t<N,2,T> sumar(const Number_t<N,2,T>& sumando) const;
        Number_t<N,2,T> multiplicar(const Number_t<N,2,T>& multiplicador) const;

        bool check_underflow(int n1, int n2) const;
        bool check_overflow(int n1, int n2, bool op) const;

    public:
        Number_t(int dato=0);
        Number_t(const Number_t<N,2,T>& n);

        ~Number_t();

        ostream& write(ostream& os) const;

        Number_t<N,2,T>  mayor(const Number_t<N,2,T>& a, const Number_t<N,2,T>& b) const;
        Number_t<N,2,T>  menor(const Number_t<N,2,T>& a, const Number_t<N,2,T>& b) const;

        Number_t<N,2,T> operator =(Number_t<N,2,T> n);
        Number_t<N,2,T> operator +(const Number_t<N,2,T> n) const;
        Number_t<N,2,T> operator -(const Number_t<N,2,T> n) const;
        Number_t<N,2,T> operator *(const Number_t<N,2,T> n) const;

        NumberBase_t& operator +(const NumberBase_t& n) const;
        NumberBase_t& operator -(const NumberBase_t& n) const;
        NumberBase_t& operator *(const NumberBase_t& n) const;


        NumberBase_t* duplicate() const;

        friend ostream& operator<<(ostream& os, NumberBase_t& n){
            n.write(os);
            return os;
        }

        Number_t<N+1,2,T> overflow();

};


template<size_t N, class T>
Number_t<N,2,T>::Number_t(int dato){
    reservar();
    to_base(dato);
}


template<size_t N, class T>
Number_t<N,2,T>::Number_t(const Number_t<N,2,T>& n){
    reservar();
    for(unsigned i = 0; i < N; i++){
        digitos_[i] = n.digitos_[i];
    }
}


template <size_t N,class T> 
Number_t<N,2,T>::~Number_t(){
    try{
        liberar();
    }
    catch (exception& e){
        cout << e.what() << endl;
    }
}


template <size_t N, class T> 
ostream& Number_t<N,2,T>::write(ostream& os) const{
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


template <size_t N, class T> 
void Number_t<N,2,T>::reservar(){
    digitos_ = new T[N];
}


template <size_t N, class T> 
void Number_t<N,2,T>::liberar(){
    if(digitos_ != NULL){
        delete[] digitos_;
    }
}

template <size_t N, class T>
unsigned Number_t<N,2,T>::get_digito(int i) const{
    char letra = digitos_[i];
    unsigned valor = set_int(letra);
    return valor;
}


template <size_t N, class T> 
Number_t<N,2,T> Number_t<N,2,T>::operator=(Number_t<N,2,T> n){
    liberar();
    reservar();
    for(unsigned i = 0; i<N; i++){
        digitos_[i] = n.digitos_[i];
    }
    return *this;
}


template <size_t N, class T> 
void Number_t<N,2,T>::complemento2() const{
    // copiar el número en un vector auxiliar
    vector<char> aux;
    aux.resize(N);
    for(unsigned i = 0; i<N; i++){
        aux[i] = digitos_[i];
    }

    bool uno=0;
    for(int i = N-1; i>=0; i--){
        if(uno==0){
            digitos_[i] = aux[i];
            if(digitos_[i] == '1'){
                uno = 1;
            }
        }
        else{
            if(aux[i] == '1'){
                digitos_[i] = '0';
            }
            else{
                digitos_[i] = '1';
            }
        }
    }
}


template <size_t N, class T> 
void Number_t<N,2,T>::to_base(const int dato){ 
    unsigned d = dato;
    unsigned resto;
    unsigned cociente = dato;
    vector<char> aux;
    unsigned B = 2;

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


template <size_t N,  class T>
int Number_t<N,2,T>::v_absoluto() const{ 
    int v=0;
    for (unsigned i = 0; i < N; i++){
        v += (get_digito(N-1-i) * int(pow(2, i)));
    }
    return v;
}

template <size_t N, class T> 
char Number_t<N,2,T>::set_char(int entero) const{
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


template <size_t N, class T> 
unsigned Number_t<N,2,T>::set_int(char letra) const{
    unsigned c=10;
    char l='A';
    unsigned entero;

    while(letra!=l && c<2){
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



template <size_t N, class T> 
Number_t<N,2,T>  Number_t<N,2,T>::mayor(const Number_t<N,2,T>& a, const Number_t<N,2,T>& b) const{
    unsigned valor1, valor2;
    if(a.digitos_[0] == b.digitos_[0]){
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
    else{
        if(a.digitos_[0] == '0'){
            return a;
        }
        else{
            return b;
        }
    }
}


template <size_t N, class T> 
Number_t<N,2,T>  Number_t<N,2,T>::menor(const Number_t<N,2,T>& a, const Number_t<N,2,T>& b) const{
    unsigned valor1, valor2;
    if(a.digitos_[0] == b.digitos_[0]){
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
    else{
        if(a.digitos_[0] == '0'){
            return b;
        }
        else{
            return a;
        }
    }
}

template <size_t N, class T> 
NumberBase_t* Number_t<N,2,T>::duplicate() const{  
    return new Number_t; 
}



template <size_t N, class T> 
Number_t<N,2,T> Number_t<N,2,T>::operator+(const Number_t<N,2,T> n) const{
    if(digitos_[N-1] == n.digitos_[N-1]){ // si los signos son iguales, comprobar el overflow
        if(check_overflow(v_absoluto(), n.v_absoluto(), false)==true){
            throw overflow();
        }
    }
    return sumar(n);
}


template <size_t N,  class T> 
NumberBase_t& Number_t<N,2,T>::operator+(const NumberBase_t& n) const{
    auto sumando = dynamic_cast<const Number_t<N,2,T>&> (n);
    auto resultado = dynamic_cast<Number_t<N,2,T>*> (duplicate());
    *resultado = *this + sumando;
    return *resultado;
}


template <size_t N, class T> 
Number_t<N,2,T> Number_t<N,2,T>::operator-(const Number_t<N,2,T> n) const{
    if(digitos_[N-1] == n.digitos_[N-1]){ // si los signos son iguales, comprobar el undererflow
        if(check_underflow(v_absoluto(), n.v_absoluto())==true){
            throw underflow();
        }
    }
    n.complemento2();
    return sumar(n);
}


template <size_t N, class T> 
NumberBase_t& Number_t<N,2,T>::operator-(const NumberBase_t& n) const{
    auto restando = dynamic_cast<const Number_t<N,2,T>&>(n);
    auto resultado = dynamic_cast<Number_t<N,2,T>*> (duplicate());
    *resultado = *this - restando;
    return *resultado;
}


template <size_t N, class T> 
Number_t<N,2,T> Number_t<N,2,T>::operator*(const Number_t<N,2,T> n) const{
    if(digitos_[N-1] == n.digitos_[N-1]){ // si los signos son iguales, comprobar el overflow
        if(check_overflow(v_absoluto(), n.v_absoluto(), true)==true){
            throw overflow();
        }
    }
    return multiplicar(n);
}


template <size_t N, class T> 
NumberBase_t& Number_t<N,2,T>::operator*(const NumberBase_t& n) const{
    auto multiplicando = dynamic_cast<const Number_t<N,2,T>&>(n);
    auto resultado = dynamic_cast<Number_t<N,2,T>*> (duplicate());
    *resultado = *this * multiplicando;
    return *resultado;
}


template <size_t N, class T> 
Number_t<N,2,T> Number_t<N,2,T>::sumar(const Number_t<N,2,T>& sumando) const{
    Number_t<N,2,T> resultado(0); // para guardar el resultado
    unsigned r=0; // resultados que voy obteniendo
    unsigned ac=0; // carry
    unsigned valor1, valor2; // valores que voy a sumar
    vector<char> resultado_suma; // vector donde guardo el resultado de la suma
    unsigned B = 2;

    int i = N-1; // posición de los vectores en Number_t que voy a sumar

    while(i>=0){ // Mientras la pos no llegue a 0
        valor1 = set_int(digitos_[i]);
        valor2 = sumando.set_int(sumando.digitos_[i]); // tomo el valor de sumando en una variable char
        r = valor1 + valor2 + ac; // guardo en r la suma de los valores anteriores mas el caryy
        ac=0; // pongo el acumulador a cero otra vez

        if(r>=B){ // si el resultado de la suma es mayor que la base
            while(r>=B){
                ac = 1; // me llevo una
                r = r - B; // al resultado le quito la base, y ese será mi r
            }
        }
        resultado_suma.push_back(set_char(r));

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



template <size_t N, class T> 
Number_t<N,2,T> Number_t<N,2,T>::multiplicar(const Number_t<N,2,T>& multiplicador) const{
    Number_t<N,2,T> resultado(0);
    for(int i=0; i<multiplicador.v_absoluto(); i++){
        resultado = sumar(resultado);
    }
    return resultado;
}


template <size_t N, class T> 
bool Number_t<N,2,T>::check_overflow(int n1, int n2, bool op) const{
    // false para la suma
    // true para la multiplicación 
    int a = pow(2,N) - 1;
    int b;
    if (op==false)
        b = n1 + n2;
    else
        b = n1 * n2;

    if(a < b) return true;
    else return false;
}


template <size_t N, class T> 
bool Number_t<N, 2, T>::check_underflow(int n1, int n2) const{
    int a = pow(2,N);
    int b = n1 + n2;

    if(a < b) return true;
    else return false;
}



// // modificación
// template <size_t N, class T> 
// Number_t<N+1,2,T> Number_t<N,2,T>::overflow(){
//     Number_t<N+1,2,T> a;
//     a.set_digito(0, '0');
//     for(unsigned i=1; i<N; i++){
//         a.set_digito(i, digitos_[i-1]);
//     }
//     a.set_digito(N, digitos_[N-1]);
//     return a;
// }


template <size_t N, class T> 
void Number_t<N,2,T>::set_digito(unsigned i, char x) const{
    digitos_[i] = x;
}

