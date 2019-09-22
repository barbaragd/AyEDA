/*Implementar un programa principal que declare variables a partir de la plantilla ​Number
para representar dos números en cualquiera de las siguientes bases: binaria, decimal y
hexadecimal. El programa solicitará por teclado valores para ambos números y mostrará por
pantalla el resultado de las operaciones implementadas entre ambos números.*/

#include "Number_t.hpp"
#include <iostream>


using namespace std;

  template<size_t N, size_t B>
  void test_number(){

    int num1, num2;

    cout << endl << "Introduzca el primer número: ";
    cin >> num1;
    cout << endl << "Introduzca el segundo número: ";
    cin >> num2;
    cout << endl << endl;

    Number_t<N,B,char> n1(num1);
    Number_t<N,B,char> n2(num2);
    Number_t<N,B,char> operaciones;

    cout << "El primer número: ";
    n1.write(cout);
    cout << endl;

    cout << "El segundo número: ";
    n2.write(cout);

    cout << endl << "Suma: ";
    operaciones = n1 + n2;
    operaciones.write(cout);

    cout << endl << "Resta: ";
    operaciones = n1 - n2;
    operaciones.write(cout);

    cout << endl << "Menor: ";
    (n1.menor(n1,n2)).write(cout);
    
    cout << endl << "Mayor: ";
    (n1.mayor(n1,n2)).write(cout);


  }



int main(){

  // cout << endl << "BINARIO: " << endl;
  // test_number<5,2> ();

  // cout << endl << "OCTAL: " << endl;
  // test_number<5,8> ();

  cout << endl << "DECIMAL: " << endl;
  test_number<5,10> ();

  cout << endl << "HEXADECIMAL: " << endl;
  test_number<5,16> ();

}