#include <iostream>

using namespace std;

int main()
{
  cout << "Punteros y memoria dinamica" << endl;
  cout << "Este es un ejemplo de uso de punteros en C++." << endl;

  // Ejemplo simple de puntero
  int a = 10;
  int *p = &a; // p apunta a la dirección de memoria de a
  int *q = new int(20); // q apunta a un nuevo entero con valor 20
  int *r = new int; // r apunta a un nuevo entero sin inicializar
  *r = 30; // Asignamos un valor a la dirección de memoria a la que apunta r

  cout << "Valor de a: " << a << endl;
  cout << "Valor apuntado por p: " << *p << endl; // Desreferencia el puntero
  cout << "Dirección de memoria de a: " << &a << endl;
  cout << "Dirección de memoria de p: " << p << endl; // M
  cout << "Valor apuntado por q: " << *q << endl; // Desreferencia el puntero q
  cout << "Dirección de memoria de q: " << q << endl; // Dirección de memoria a la que apunta q
  cout << "Valor apuntado por r: " << *r << endl; // Desreferencia el puntero r
  cout << "Dirección de memoria de r: " << r << endl; // Dirección de memoria a la que apunta r

  return 0;
}