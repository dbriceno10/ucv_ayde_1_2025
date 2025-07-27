#include <string>
using namespace std;

struct Nodo
{
  int valor;
  Nodo *siguiente;
  Nodo(int v) : valor(v), siguiente(nullptr) {}
};

class ListaSimple
{
  Nodo *inicio;
  Nodo *fin;

public:
  ListaSimple() : inicio(nullptr), fin(nullptr) {}

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
      fin = nuevo;
    }
  }

  // Mostrar la lista
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

  ~ListaSimple()
  {
    liberar();
  }
};

// Ejemplo de uso
int main()
{
  ListaSimple lista;
  lista.agregar(10);
  lista.agregar(20);
  lista.agregar(30);
  lista.mostrar();
  return 0;
}