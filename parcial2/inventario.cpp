#include <iostream>
#include <string>

using namespace std;

struct Objeto
{
  int tipo;
  float peso;
};

class Inventario
{
  struct Node
  {
    Objeto data;
    Node *next;
    Node(Objeto obj, Node *n = nullptr) : data(obj), next(n) {}
  };
  Node *head;
  Node *tail;
  int count;

public:
  typedef Node *tPosition;
  Inventario() : head(nullptr), tail(nullptr), count(0) {}

  Inventario(const Inventario &other)
  {
    Agregar(other);
  }

  tPosition First()
  {
    if (head->next != tail)
    {
      return head->next;
    }
    else
    {
      return tail;
    }
  }
  tPosition Last()
  {
    return tail;
  }

  ~Inventario()
  {
    Clear();
    delete head;
    delete tail;
  }

  bool IsEmpty()
  {
    return count == 0;
  }

  // agrega un objeto al final de la lista
  void Agregar(Objeto d, tPosition v)
  {
    tPosition current = head;
    while (current->next != v)
    {
      current = current->next;
    }
    current->next = new Node(d, v);
    count++;
  }

  // agrega un inventario
  void Agregar(const Inventario &other)
  {
    tPosition current = other.head;
    if (current->next == nullptr)
    {
      return;
    }
    current = current->next;
    do
    {
      AgregarOrdenado(current->data);
    } while (current->next != nullptr);
  }

  void AgregarOrdenado(Objeto d)
  {
    tPosition current = head;
    tPosition newNode = new Node(d);
    // Buscar la posición correcta para insertar el nuevo nodo
    while (current->next != tail && current->next->data.peso < d.peso)
    {
      current = current->next;
    }
    // Insertar el nuevo nodo
    newNode->next = current->next;
    current->next = newNode;
    count++;
  }

  int pesoTotal()
  {
    int total = 0;
    tPosition current = First();
    while (current->next != tail)
    {
      total += current->data.peso;
      current = current->next;
    }
    return total;
  }

  void Clear()
  {
    tPosition current = head->next;
    while (current->next != tail)
    {
      tPosition toDelete = current;
      current = current->next;
      delete toDelete;
    }
    head->next = tail;
    count = 0;
  }
};

/*
Pregunta 5) Mecanismos para manejo eficiente de memoria:
- Usar destructores para liberar memoria de nodos al destruir el inventario.
- Implementar correctamente el constructor copia y el operador de asignación (no incluido aquí, pero recomendable).
- Evitar fugas de memoria eliminando nodos al eliminar objetos o limpiar el inventario.
- Usar punteros inteligentes si se permite (no en este caso).
*/