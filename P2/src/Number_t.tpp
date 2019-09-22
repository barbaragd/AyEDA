#include "../include/Number_t.hpp"
#include <vector>
#include <math.h>

using namespace std;

template <size_t N, size_t B, class T> 
Number_t<N,B,T>::Number_t(int dato): digitos_(NULL){
    if(dato < 0){
        signo_ = -1;
    }
    else{
        signo_ = 1;
    }
    reservar();
    dato = dato * signo_;
    to_base(dato);
}


template <size_t N, size_t B, class T> 
Number_t<N,B,T>::Number_t(const Number_t<N,B,T>& n): digitos_(NULL), signo_(n.signo_){
    reservar();
    for(unsigned i = 0; i < N; i++){
        digitos_[i] = n.digitos_[i];
    }
}


template <size_t N, size_t B, class T> 
Number_t<N,B,T>::~Number_t(){
    try{
        liberar();
    }
    catch (exception& e){
        cout << e.what() << endl;
    }
}


template <size_t N, size_t B, class T> 
ostream& Number_t<N,B,T>::write(ostream& os){
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
    digitos_ = new T[N];
}


template <size_t N, size_t B, class T> 
void Number_t<N,B,T>::liberar(){
    if(digitos_ != NULL){
        delete[] digitos_;
    }
}


template <size_t N, size_t B, class T> 
int Number_t<N,B,T>::get_signo() const{
    return signo_;
}


template <size_t N, size_t B, class T>
int Number_t<N,B,T>::v_absoluto(){ 
    int v=0;
    for (unsigned i = 0; i < N; i++){
        v += (get_digito(N-1-i) * int(pow(B, i)));
    }
    return v;
}


template <size_t N, size_t B, class T>
unsigned Number_t<N,B,T>::get_digito(int i){
    char letra = digitos_[i];
    unsigned valor = set_int(letra);
    return valor;
}


// OPERADORES
template <size_t N, size_t B, class T> 
Number_t<N,B,T> Number_t<N,B,T>::operator=(Number_t<N,B,T> n){
    liberar();
    reservar();

    for(unsigned i = 0; i<N; i++){
        digitos_[i] = n.digitos_[i];
    }

    signo_ = n.signo_;

    return *this;
}


template <size_t N, size_t B, class T> 
Number_t<N,B,T> Number_t<N,B,T>::operator+(Number_t<N,B,T> n){
    Number_t<N,B,T> resultado(0);
    if(signo_ == n.signo_){
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
Number_t<N,B,T> Number_t<N,B,T>::operator-(Number_t<N,B,T> n){
    Number_t<N,B,T> resultado(0);
    if(signo_ == n.signo_){
        if(v_absoluto() > n.v_absoluto()){
            resultado.signo_ = signo_;
        }
        else{
            resultado.signo_ = n.signo_;
        }
        return restar(n, resultado);
    }
    else{
        if(v_absoluto() > n.v_absoluto()){
            resultado.signo_ = signo_;
        }
        else{
            resultado.signo_ = n.signo_;
        }
        return sumar(n, resultado);
    }
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
char Number_t<N,B,T>::set_char(int entero){
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
unsigned Number_t<N,B,T>::set_int(char letra){
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
Number_t<N,B,T>  Number_t<N,B,T>::mayor(Number_t<N,B,T>& a, Number_t<N,B,T>& b){
    unsigned valor1, valor2;
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


template <size_t N, size_t B, class T> 
Number_t<N,B,T>  Number_t<N,B,T>::menor(Number_t<N,B,T>& a, Number_t<N,B,T>& b){
    unsigned valor1, valor2;
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


template <size_t N, size_t B, class T> 
Number_t<N,B,T> Number_t<N,B,T>::sumar(Number_t<N,B,T>& sumando, Number_t<N,B,T>& resultado){
    //Number_t<N,B,T> resultado(0); // para guardar el resultado

    unsigned r=0; // resultados que voy obteniendo
    unsigned ac=0; // carry
    unsigned valor1, valor2; // valores que voy a sumar
    vector<char> resultado_suma; // vector donde guardo el resultado de la suma

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

    if(ac!=0){
        cerr << "No se puede representar en N digitos." << endl;
    }

    else{
        int i = N-1;
        int j = 0;
        while(i>=0){
            resultado.digitos_[j] = resultado_suma[i];
            i--;
            j++;
        }
    }

    // if(v_absoluto() > sumando.v_absoluto()){
    //     resultado.signo_ = signo_;
    // }
    // else{
    //     if(signo_ == sumando.signo_) // si son signos iguales, el sumando es de mayor valor absoluto, pues el resultado sería positivo.
    //         resultado.signo_ = 1;
    //     else{ 
    //         resultado.signo_ = signo_; 
    //     }
    // }
    return resultado;
}


template <size_t N, size_t B, class T> 
Number_t<N,B,T> Number_t<N,B,T>::restar(Number_t<N,B,T>& restando, Number_t<N,B,T>& resultado){
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
        int a = int(pow(10, N)); // tengo en a = 1000..0 del tamaño de N
        int v = a - resultado.v_absoluto();
        resultado.to_base(v);
    }


    if(v_absoluto() > restando.v_absoluto()){
        resultado.signo_ = signo_;
    }
    else{
        if(signo_ == restando.signo_) // si son signos iguales, el restando es de mayor valor absoluto, pues el resultado sería positivo.
            resultado.signo_ = 1;
        else{ 
            resultado.signo_ = signo_; 
        }
    }

    return resultado;
}









// Para números en binario:
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
ostream& Number_t<N,2,T>::write(ostream& os){
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
unsigned Number_t<N,2,T>::get_digito(int i){
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
void Number_t<N,2,T>::complemento2(){
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
void Number_t<N,2,T>::to_base(const int dato){ // se genera una excepción cuando el valor a representar se sale de los N dígitos
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
int Number_t<N,2,T>::v_absoluto(){ 
    int v=0;
    for (unsigned i = 0; i < N; i++){
        v += (get_digito(N-1-i) * int(pow(2, i)));
    }
    return v;
}

template <size_t N, class T> 
char Number_t<N,2,T>::set_char(int entero){
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
unsigned Number_t<N,2,T>::set_int(char letra){
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
Number_t<N,2,T>  Number_t<N,2,T>::mayor(Number_t<N,2,T>& a, Number_t<N,2,T>& b){
    unsigned valor1, valor2;
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


template <size_t N, class T> 
Number_t<N,2,T>  Number_t<N,2,T>::menor(Number_t<N,2,T>& a, Number_t<N,2,T>& b){
    unsigned valor1, valor2;
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


// SUMA Y RESTA
template <size_t N, class T> 
Number_t<N,2,T> Number_t<N,2,T>::operator+(Number_t<N,2,T> n){
    return sumar(n);
}


template <size_t N, class T> 
Number_t<N,2,T> Number_t<N,2,T>::operator-(Number_t<N,2,T> n){
    //n.write(cout);
    n.complemento2();
    return sumar(n);
}


template <size_t N, class T> 
Number_t<N,2,T> Number_t<N,2,T>::sumar(Number_t<N,2,T>& sumando){
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

    // if(ac!=0){
    //     cerr << "No se puede representar en N digitos." << endl;
    // }

    //else{
        i = N-1;
        int j = 0;
        while(i>=0){
            resultado.digitos_[j] = resultado_suma[i];
            i--;
            j++;
        }
   // }

    return resultado;
}