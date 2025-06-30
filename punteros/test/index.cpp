#include <iostream>

using namespace std;

int main()
{
  cout << "Punteros y memoria dinamica" << endl;
  cout << "Este es un ejemplo de uso de punteros en C++." << endl;

  // Ejemplo simple de puntero
  int a = 10;
  int *p = &a; // p apunta a la dirección de memoria de a

  cout << "Valor de a: " << a << endl;
  cout << "Valor apuntado por p: " << *p << endl; // Desreferencia el puntero
  cout << "Dirección de memoria de a: " << &a << endl;
  cout << "Dirección de memoria de p: " << p << endl; // M

  return 0;
}