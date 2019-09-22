#pragma once

#include <iostream>
#include <vector>

using namespace std;

template <size_t N, size_t B, class T=char> 
class Number_t{

    private:
        T* digitos_;
        int signo_; 


        void to_base(const int dato);
        char set_char(int entero);
        unsigned set_int(char letra);

        int get_signo() const;
        unsigned get_digito(int i);

        void reservar();
        void liberar();

        int v_absoluto();

        Number_t<N,B,T> sumar(Number_t<N,B,T>& sumando, Number_t<N,B,T>& resultado);
        Number_t<N,B,T> restar(Number_t<N,B,T>& restando, Number_t<N,B,T>& resultado);


    public:

        Number_t(int dato=0);
        Number_t(const Number_t<N,B,T>& n);

        ~Number_t();

        ostream& write(ostream& os);

        Number_t<N,B,T>  mayor(Number_t<N,B,T>& a, Number_t<N,B,T>& b);
        Number_t<N,B,T>  menor(Number_t<N,B,T>& a, Number_t<N,B,T>& b);

        Number_t<N,B,T> operator =(Number_t<N,B,T> n);
        Number_t<N,B,T> operator +(Number_t<N,B,T> n);
        Number_t<N,B,T> operator -(Number_t<N,B,T> n);

};
// Especialización de la template para numeros en binario
template<size_t N, class T>
class Number_t<N,2,T> {
    private:
        T* digitos_;


        void to_base(const int dato);
        char set_char(int entero);
        unsigned set_int(char letra);

        unsigned get_digito(int i);

        void reservar();
        void liberar();

        int v_absoluto();
        void complemento2();

        Number_t<N,2,T> sumar(Number_t<N,2,T>& sumando);
        //Number_t<N,2,T> restar(Number_t<N,2,T>& restando);

    public:
        Number_t(int dato=0);
        Number_t(const Number_t<N,2,T>& n);

        ~Number_t();

        ostream& write(ostream& os);

        Number_t<N,2,T>  mayor(Number_t<N,2,T>& a, Number_t<N,2,T>& b);
        Number_t<N,2,T>  menor(Number_t<N,2,T>& a, Number_t<N,2,T>& b);

        Number_t<N,2,T> operator =(Number_t<N,2,T> n);
        Number_t<N,2,T> operator +(Number_t<N,2,T> n);
        Number_t<N,2,T> operator -(Number_t<N,2,T> n);
};

#include "../src/Number_t.tpp"