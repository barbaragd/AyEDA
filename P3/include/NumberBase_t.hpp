#pragma once

#include <iostream>

using namespace std;

class NumberBase_t{
    private:
        int base_;
        int n_digits_;

    public:
        NumberBase_t(int n, int b): base_(b), n_digits_(n){}
        NumberBase_t(NumberBase_t& n): base_(n.base_), n_digits_(n.n_digits_){}
        virtual ~NumberBase_t()=default;
        virtual NumberBase_t& operator +(const NumberBase_t& n) const = 0;
        virtual NumberBase_t& operator -(const NumberBase_t& n) const = 0;
        virtual NumberBase_t& operator *(const NumberBase_t& n) const = 0;
        friend ostream& operator<<(ostream& os, NumberBase_t& n){
            n.write(os);
            return os;
        }

        // para saber si dos num son del mismo tipo, utilizo un typecast, si no me da error, 
        // es que todo chachi. Si me da problema, es que no son del mismo tipo.
        // si ponmos static, sumamos un num en un tipo y el otro de otro tipo => MAL

    protected:
        virtual void to_base(const int dato) = 0;
        virtual ostream& write(ostream& os) const = 0;
        virtual NumberBase_t* duplicate() const = 0;
        // duplicate => copia (clon) en mem dinamica del objto del mismo tipo del objeto q lo sta llamando
                    // esta reserva en mem dinamica no la estamos liberando -> responsabilidad del programa 
                    // principal (desde el main)
};