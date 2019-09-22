/*Implementar un programa principal que declare variables a partir de la plantilla ​Number
para representar dos números en cualquiera de las siguientes bases: binaria, decimal y
hexadecimal. El programa solicitará por teclado valores para ambos números y mostrará por
pantalla el resultado de las operaciones implementadas entre ambos números.*/

#include "../include/Number_t.hpp"
#include <iostream>

using namespace std;


int main(){

    int num1, num2, base;

    cout << "Primer número: ";
    cin >> num1;
    cout << "Segundo número: ";
    cin >> num2;
    NumberBase_t *n1;
    NumberBase_t *n2;

    cout << "Base: ";
    cin >> base;

    switch(base){
        case 2:
            n1 = new BinaryNumber<char>(num1);
            n2 = new BinaryNumber<char>(num2);
            break;

        case 8:
            n1 = new OctalNumber<char>(num1);
            n2 = new OctalNumber<char>(num2);
            break;

        case 10:
            n1 = new DecimalNumber<char>(num1);
            n2 = new DecimalNumber<char>(num2);
            break;

        case 16:
            n1 = new HexadecimalNumber<char>(num1);
            n2 = new HexadecimalNumber<char>(num2);
            break;
    }

    cout << endl;

    cout << "Primer número: " << (*n1);;
    cout << "Segundo número: " << (*n2);

    try{
        cout << "Suma: " << (*n1) + (*n2);
    }
    catch(overflow &e){
        cout << e.what() << endl;
    }

    try{
        cout << "Resta: ";
        cout << (*n1) - (*n2);
    }
    catch(underflow &e){
        cout << e.what() << endl;
    }

    try{
        cout << "Multiplicación: ";
        cout << (*n1) * (*n2);
    }
    catch(overflow &e){
        cout << e.what() << endl;
    }

    delete n1;
    delete n2;
}