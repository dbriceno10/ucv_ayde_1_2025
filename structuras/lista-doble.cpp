#include <string>
using namespace std;

struct Nodo
{
  int valor;
  Nodo *siguiente;
  Nodo *anterior;
  Nodo(int v) : valor(v), siguiente(nullptr), anterior(nullptr) {}
};

class ListaDoble
{
  Nodo *inicio;
  Nodo *fin;

public:
  ListaDoble() : inicio(nullptr), fin(nullptr) {}

  // Agregar al final
  void agregar(int valor)
  {
    Nodo *nuevo = new Nodo(valor);
    if (!inicio)
    {
      inicio = fin = nuevo;
    }
    else
    {
      fin->siguiente = nuevo;
      nuevo->anterior = fin;
      fin = nuevo;
    }
  }

  // Mostrar desde el inicio
  void mostrar()
  {
    Nodo *actual = inicio;
    while (actual)
    {
      // cout << actual->valor << " ";
      actual = actual->siguiente;
    }
    // cout << endl;
  }

  // Mostrar desde el final
  void mostrarReversa()
  {
    Nodo *actual = fin;
    while (actual)
    {
      // cout << actual->valor << " ";
      actual = actual->anterior;
    }
    // cout << endl;
  }

  // Liberar memoria
  void liberar()
  {
    Nodo *actual = inicio;
    while (actual)
    {
      Nodo *sig = actual->siguiente;
      delete actual;
      actual = sig;
    }
    inicio = fin = nullptr;
  }

  ~ListaDoble()
  {
    liberar();
  }
};

// Ejemplo de uso
int main()
{
  ListaDoble lista;
  lista.agregar(10);
  lista.agregar(20);
  lista.agregar(30);
  lista.mostrar();
  lista.mostrarReversa();
  return 0;
}