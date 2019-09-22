/*Implementar un programa principal que declare variables a partir de la plantilla ​Number
para representar dos números en cualquiera de las siguientes bases: binaria, decimal y
hexadecimal. El programa solicitará por teclado valores para ambos números y mostrará por
pantalla el resultado de las operaciones implementadas entre ambos números.*/

#include "Number_t.hpp"
#include <iostream>


using namespace std;

int main(){

  bool overflow=0;

  int n1;
  int n2;


  cout << endl << "Introduzca el primer número: ";
  cin >> n1;
  cout << "Introduzca el segundo número: ";
  cin >> n2;
  cout << endl << endl;

  // template<int N, B>
  // int test(){
    //crear los objetos de las clases
  //}



  cout << "HEXADECIMAL" << endl;

  Number_t<5,16,char> num_a_hex(overflow, n1);
  if(overflow==1){
    return -1;
  }
  overflow = 0;
  Number_t<5,16,char> num_b_hex(overflow, n2);
  if(overflow==1){
    return -1;
  }
  overflow = 0;
  Number_t<5,16,char> resultado_hex(overflow);
  
  cout << endl << "Primer número:\t\t";
  num_a_hex.write(cout);
  cout << endl;

  cout << "Segundo número:\t\t";
  num_b_hex.write(cout);
  cout << endl;

  cout << "Suma:\t\t\t";
  resultado_hex = num_a_hex.sumar(num_b_hex, overflow);
  if(overflow==0){
    resultado_hex.write(cout);
  }
  cout << endl;
  overflow = 0;
  cout << "Resta:\t\t\t";
  resultado_hex = num_a_hex.restar(num_b_hex, overflow);
  if(overflow==0){
    resultado_hex.write(cout);
  }
  cout << endl;

  cout << "El número mayor es:\t";
  resultado_hex = num_a_hex.mayor(num_a_hex, num_b_hex);
  resultado_hex.write(cout);
  cout << endl;

  cout << "El número menor es:\t";
  resultado_hex = num_a_hex.menor(num_a_hex, num_b_hex);
  resultado_hex.write(cout);
  cout << endl;


  overflow = 0;



  cout << endl << "DECIMAL" << endl;

  Number_t<5,10,char> num_a_dec(overflow, n1);
  if(overflow==1){
    return -1;
  }
  else{
    overflow = 0;
  }
  Number_t<5,10,char> num_b_dec(overflow, n2);
  if(overflow==1){
    return -1;
  }
  else{
    overflow = 0;
  }
  Number_t<5,10,char> resultado_dec(overflow);

  cout << endl << "Primer número:\t\t";
  num_a_dec.write(cout);
  cout << endl;

  cout << "Segundo número:\t\t";
  num_b_dec.write(cout);
  cout << endl;

  cout << "Suma:\t\t\t";
  resultado_dec = num_a_dec.sumar(num_b_dec, overflow);
  if(overflow==0){
    resultado_dec.write(cout);
  }
  cout << endl;
  overflow = 0;
  cout << "Resta:\t\t\t";
  resultado_dec = num_a_dec.restar(num_b_dec, overflow);
  if(overflow==0){
    resultado_dec.write(cout);
  }
  cout << endl;

  cout << "El número mayor es:\t";
  resultado_dec = num_a_dec.mayor(num_a_dec, num_b_dec);
  resultado_dec.write(cout);
  cout << endl;

  cout << "El número menor es:\t";
  resultado_dec = num_a_dec.menor(num_a_dec, num_b_dec);
  resultado_dec.write(cout);
  cout << endl;


  overflow = 0;



  cout << endl << "BINARIO" << endl;

  Number_t<5,2,char> num_a_bin(overflow, n1);
  if(overflow==1){
    return -1;
  }
  else{
    overflow = 0;
  }
  Number_t<5,2,char> num_b_bin(overflow, n2);
  if(overflow==1){
    return -1;
  }
  else{
    overflow = 0;
  } 
  Number_t<5,2,char> resultado_bin(overflow);

  cout << endl << "Primer número:\t\t";
  num_a_bin.write(cout);
  cout << endl;

  cout << "Segundo número:\t\t";
  num_b_bin.write(cout);
  cout << endl;

  cout << "Suma:\t\t\t";
  resultado_bin = num_a_bin.sumar(num_b_bin, overflow);
  if(overflow==0){
    resultado_bin.write(cout);
  }
  cout << endl;
  overflow=0;
  cout << "Resta:\t\t\t";
  resultado_bin = num_a_bin.restar(num_b_bin, overflow);
  if(overflow==0){
    resultado_bin.write(cout);
  }
  cout << endl;

  cout << "El número mayor es:\t";
  resultado_bin = num_a_bin.mayor(num_a_bin, num_b_bin);
  resultado_bin.write(cout);
  cout << endl;

  cout << "El número menor es:\t";
  resultado_bin = num_a_bin.menor(num_a_bin, num_b_bin);
  resultado_bin.write(cout);
  cout << endl;

}


