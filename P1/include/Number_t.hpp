#pragma once

#include <iostream>
#include <vector>

using namespace std;

template <size_t N, size_t B, class T=char> // creamos claese diferentes
class Number_t{
    //private:
        vector<T> digitos_;
        //bool signo; // para los negativos

    public:

        Number_t(bool &overflow, const int dato=0){
            digitos_.resize(N);
            to_base(dato, overflow);
        }

        ~Number_t(){
            digitos_.clear();
        }

        char get_digito(unsigned i){
            return digitos_[i];
        }
        
        void set_digito(unsigned i, char d){
            digitos_[i] = d;
        }

        ostream& write(ostream& os) const{
            for(unsigned k=0; k<N; k++){
                os <<  digitos_[k];
            }
            os << endl;
            return os;
        }


        Number_t<N,B,T> sumar(Number_t<N,B,T>& sumando) const{
            bool overflow = 0;
            Number_t<N,B,T> resultado(overflow); // para guardar el resultado

            unsigned r=0; // resultados que voy obteniendo
            unsigned ac=0; // carry
            unsigned valor1, valor2; // valores que voy a sumar
            vector<char> resultado_suma; // vector donde guardo el resultado de la suma

            int i = N-1; // posición de los vectores en Number_t que voy a sumar
            
            while(i>=0){ // Mientras la pos no llegue a 0
                    valor1 = set_int(digitos_[i]);
                    valor2 = sumando.set_int(sumando.get_digito(i)); // tomo el valor de sumando en una variable char
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
                    resultado.set_digito(j, resultado_suma[i]);
                    i--; 
                    j++;
                }
            }

            return resultado;
        } 

        Number_t<N,B,T> restar(Number_t<N,B,T>& restando) const{
            bool overflow = 0;
            Number_t<N,B,T> resultado(overflow); // para guardar el resultado

            int r=0; // resultados que voy obteniendo
            unsigned ac=0; // carry
            unsigned valor1, valor2; // valores que voy a sumar
            vector<char> resultado_resta; // vector donde guardo el resultado de la resta

            int i = N-1; // posición de los vectores en Number_t que voy a restar
    
            while(i>=0){ // Mientras la pos no llegue a 0
                valor1 = set_int(digitos_[i]);
                valor2 = restando.set_int(restando.get_digito(i)); // tomo el valor de sumando en una variable char
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
                resultado.set_digito(j, resultado_resta[i]);
                i--; 
                j++;
            }
            

            return resultado;
        } 

        
        Number_t<N,B,T>  mayor(Number_t<N,B,T>& a, Number_t<N,B,T>& b) const{
            
            unsigned valor1, valor2;

            for(unsigned i=0; i<digitos_.size(); i++){
                valor1 = digitos_[i] - '0';
                valor2 = b.get_digito(i) - '0';
                if(valor1 > valor2){
                    return a;
                }
                else if(valor1 < valor2){
                    return b;
                }

            }
            return a;

        }

        Number_t<N,B,T>  menor(Number_t<N,B,T>& a, Number_t<N,B,T>& b) const{
            
            unsigned valor1, valor2;

            for(unsigned i=0; i<digitos_.size(); i++){
                valor1 = digitos_[i] - '0';
                valor2 = b.get_digito(i) - '0';
                if(valor1 < valor2){
                    return a;
                }
                else if(valor1 > valor2){
                    return b;
                }

            }
            return a;

        }

    private:
        void to_base(const int dato, bool &overflow){
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
            if (cociente >= 10){ // si el cociente es mayor que 10, para meter el número en el vector tengo que separar los digitos
                int var=0;
                while(cociente >= 10){
                    cociente = cociente - 10;
                    aux.push_back(set_char(cociente));
                    var++;  
                }
                aux.push_back(set_char(var));
            }

            else{ // si el cociente es menor que 10, solo lo paso a char 
                aux.push_back(set_char(cociente)); 
            }


            if(aux.size() > N){
                cerr << "El número a representar se sale del espacio disponible para representarlo." << endl;
                overflow = 1;
            }
            else{
                overflow = 0;
            }


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

        
        char set_char(int entero) const{
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

        unsigned set_int(char letra) const{
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

};







