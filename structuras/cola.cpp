#include <string>
using namespace std;

struct Nodo
{
  int valor;
  Nodo *siguiente;
  Nodo(int v) : valor(v), siguiente(nullptr) {}
};

class Cola
{
  Nodo *frente;
  Nodo *final;

public:
  Cola() : frente(nullptr), final(nullptr) {}

  // Encolar (agregar al final)
  void encolar(int valor)
  {
    Nodo *nuevo = new Nodo(valor);
    if (!final)
    {
      frente = final = nuevo;
    }
    else
    {
      final->siguiente = nuevo;
      final = nuevo;
    }
  }

  // Desencolar (quitar del frente)
  int desencolar()
  {
    if (!frente)
      return -1; // Cola vacía
    Nodo *tmp = frente;
    int val = tmp->valor;
    frente = frente->siguiente;
    if (!frente)
      final = nullptr;
    delete tmp;
    return val;
  }

  // Ver si está vacía
  bool vacia()
  {
    return frente == nullptr;
  }

  // Liberar memoria
  void liberar()
  {
    while (frente)
    {
      Nodo *tmp = frente;
      frente = frente->siguiente;
      delete tmp;
    }
    final = nullptr;
  }

  ~Cola()
  {
    liberar();
  }
};

// Ejemplo de uso
int main()
{
  Cola cola;
  cola.encolar(10);
  cola.encolar(20);
  cola.encolar(30);
  while (!cola.vacia())
  {
    // cout << cola.desencolar() << " ";
  }
  // cout << endl;
  return 0;
}