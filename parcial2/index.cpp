#include <iostream>
#include <string>
using namespace std;

// Objeto con tipo y peso
struct Objeto
{
  int tipo;
  int peso;
  Objeto(int t = 0, int p = 0) : tipo(t), peso(p) {}
  // Comparador por peso (para orden)
  bool operator<(const Objeto &other) const
  {
    return peso < other.peso;
  }
  bool operator==(const Objeto &other) const
  {
    return tipo == other.tipo && peso == other.peso;
  }
};

// Lista enlazada simple para Inventario
class Inventario
{
  struct Nodo
  {
    Objeto dato;
    Nodo *sig;
    Nodo(const Objeto &d, Nodo *s = nullptr) : dato(d), sig(s) {}
  };
  Nodo *head;
  int cantidad;

  // Copia profunda de la lista
  void copiar(const Inventario &otro)
  {
    head = nullptr;
    cantidad = 0;
    if (!otro.head)
      return;
    Nodo *actualOtro = otro.head;
    Nodo *ultimo = nullptr;
    while (actualOtro)
    {
      Nodo *nuevo = new Nodo(actualOtro->dato);
      if (!head)
      {
        head = nuevo;
      }
      else
      {
        ultimo->sig = nuevo;
      }
      ultimo = nuevo;
      actualOtro = actualOtro->sig;
      cantidad++;
    }
  }

public:
  // Constructor vacío
  Inventario() : head(nullptr), cantidad(0) {}

  // Constructor copia
  Inventario(const Inventario &inventario)
  {
    copiar(inventario);
  }

  // Destructor
  ~Inventario()
  {
    limpiar();
  }

  // Limpia la lista
  void limpiar()
  {
    Nodo *actual = head;
    while (actual)
    {
      Nodo *temp = actual;
      actual = actual->sig;
      delete temp;
    }
    head = nullptr;
    cantidad = 0;
  }

  // Agrega un objeto en orden ascendente por peso (permite duplicados)
  void agregar(const Objeto &elemento)
  {
    Nodo *nuevo = new Nodo(elemento);
    if (!head || elemento.peso < head->dato.peso)
    {
      nuevo->sig = head;
      head = nuevo;
    }
    else
    {
      Nodo *actual = head;
      while (actual->sig && actual->sig->dato.peso <= elemento.peso)
      {
        actual = actual->sig;
      }
      nuevo->sig = actual->sig;
      actual->sig = nuevo;
    }
    cantidad++;
  }

  // Agrega todos los elementos de otro inventario (manteniendo orden)
  void agregar(const Inventario &inventario)
  {
    Nodo *actual = inventario.head;
    while (actual)
    {
      agregar(actual->dato);
      actual = actual->sig;
    }
  }

  // Elimina el primer objeto igual al dado (si existe)
  void eliminar(const Objeto &objeto)
  {
    Nodo *actual = head;
    Nodo *anterior = nullptr;
    while (actual)
    {
      if (actual->dato == objeto)
      {
        if (anterior)
        {
          anterior->sig = actual->sig;
        }
        else
        {
          head = actual->sig;
        }
        delete actual;
        cantidad--;
        return;
      }
      anterior = actual;
      actual = actual->sig;
    }
  }

  // Retorna el peso total
  int pesoTotal() const
  {
    int total = 0;
    Nodo *actual = head;
    while (actual)
    {
      total += actual->dato.peso;
      actual = actual->sig;
    }
    return total;
  }

  // Retorna los objetos en una lista enlazada simple (ordenados)
  Inventario objetos() const
  {
    return Inventario(*this);
  }

  // Imprime el inventario
  void imprimir() const
  {
    Nodo *actual = head;
    cout << "[";
    while (actual)
    {
      cout << "(" << actual->dato.tipo << "," << actual->dato.peso << ")";
      if (actual->sig)
        cout << ", ";
      actual = actual->sig;
    }
    cout << "]" << endl;
  }
};

// Ejemplo de uso
int main()
{
  Inventario inv;
  inv.agregar(Objeto(1, 10));
  inv.agregar(Objeto(2, 5));
  inv.agregar(Objeto(3, 20));
  inv.agregar(Objeto(1, 10)); // Duplicado permitido
  cout << "Inventario original: ";
  inv.imprimir();

  Inventario copia(inv); // Constructor copia
  cout << "Inventario copia: ";
  copia.imprimir();

  Inventario otro;
  otro.agregar(Objeto(4, 7));
  otro.agregar(Objeto(5, 15));
  inv.agregar(otro); // Agrega todos los de otro
  cout << "Inventario tras agregar otro: ";
  inv.imprimir();

  inv.eliminar(Objeto(1, 10)); // Elimina uno de los duplicados
  cout << "Inventario tras eliminar (1,10): ";
  inv.imprimir();

  cout << "Peso total: " << inv.pesoTotal() << endl;

  Inventario listaObjetos = inv.objetos();
  cout << "Lista de objetos (copia): ";
  listaObjetos.imprimir();

  return 0;
}

/*
Pregunta 5) Mecanismos para manejo eficiente de memoria:
- Usar destructores para liberar memoria de nodos al destruir el inventario.
- Implementar correctamente el constructor copia y el operador de asignación (no incluido aquí, pero recomendable).
- Evitar fugas de memoria eliminando nodos al eliminar objetos o limpiar el inventario.
- Usar punteros inteligentes si se permite (no en este caso).
*/