#include <iostream>
#include <string>
using namespace std;

int main()
{
  int a = 20;
  int *b = new int;
  // *b = 12;
  // cout << "Valor de a: " << a << endl;
  // cout << "Dirección de memoria de &a: " << &a << endl;
  // cout << "Valor apuntado por *b: " << *b << endl;
  // cout << "Dirección de memoria a la que apunta b: " << b << endl;
  // cout << "Dirección de memoria de la variable puntero &b: " << &b << endl;
  // cout << "Dirección de memoria del entero apuntado por b (usando &*b): " << &*b << endl;
  // cout << "Dirección de memoria del entero apuntado por b (usando *&b): " << *&b << endl;

  int *c = &a; // c apunta a la dirección de memoria de a
  // int *c = new int(a); // c apunta a un nuevo entero con el valor de a

  // cout << *c << endl; // Imprime la dirección de memoria de a

  delete b;
  // delete c;
}