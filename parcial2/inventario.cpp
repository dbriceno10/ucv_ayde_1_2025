#include <iostream>
#include <string>

using namespace std;

template <typename T>
class SimpleList
{
  struct Node
  {
    T data;
    Node *next;
    Node(const T &d, Node *n = nullptr) : data(d), next(n) {}
  };
  Node *head = nullptr;
  Node *tail = nullptr;
  int size = 0;

public:
  typedef Node *tPosition;

  SimpleList() : size(0)
  {
    tail = new Node(T());
    head = new Node(T(), tail);
  }

  ~SimpleList()
  {
    clear();
    delete head;
    delete tail;
  }

  bool IsEmpty()
  {
    return size == 0;
  }

  tPosition first()
  {
    return (head->next != tail) ? head->next : tail;
  }

  tPosition last()
  {
    return tail;
  }

  void next(tPosition &pValue)
  {
    if (pValue != tail)
      pValue = pValue->next;
  }

  T &Get(tPosition v)
  {
    return v->data;
  }

  void insert(const T &d, tPosition v)
  {
    tPosition current = head;
    while (current->next != v)
    {
      current = current->next;
    }
    current->next = new Node(d, v);
    size++;
  }

  void Delete(tPosition v)
  {
    if (v == tail)
      return;
    tPosition current = head;
    while (current->next != v)
    {
      current = current->next;
    }
    current->next = v->next;
    delete v;
    size--;
  }

  // void printl()
  // {
  //   tPosition current = first();
  //   while (current != tail)
  //   {
  //     cout << Get(current) << endl;
  //     next(current);
  //   }
  // }

  void clear()
  {
    tPosition current = first();
    while (current != tail)
    {
      tPosition toDelete = current;
      next(current);
      delete toDelete;
    }
    head->next = tail;
    size = 0;
  }

  void printHeadTail()
  {
    cout << "Head: " << head->data << ", Tail: " << tail->data << endl;
  }
};

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
  // Inventario() : head(nullptr), tail(nullptr), count(0) {}
  Inventario() : count(0)
  {
    tail = new Node({0, 0.0f});
    head = new Node({0, 0.0f}, tail);
  }

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
    if (current->next == tail) // nullptr
    {
      return;
    }
    current = current->next;
    do
    {
      AgregarOrdenado(current->data);
    } while (current->next != tail); // nullptr
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

  SimpleList<Objeto> ObtenerObjetos()
  {
    SimpleList<Objeto> objetos;
    tPosition current = First();
    while (current->next != tail)
    {
      objetos.insert(current->data, objetos.last());
      current = current->next;
    }
    return objetos;
  }
};

/*
Pregunta 5) Mecanismos para manejo eficiente de memoria:
- Usar destructores para liberar memoria de nodos al destruir el inventario.
- Implementar correctamente el constructor copia y el operador de asignación (no incluido aquí, pero recomendable).
- Evitar fugas de memoria eliminando nodos al eliminar objetos o limpiar el inventario.
- Usar punteros inteligentes si se permite (no en este caso).
*/

int main(int argc, char const *argv[])
{

  Inventario inventario;
  Objeto obj1 = {1, 2.5};
  Objeto obj2 = {2, 3.0};
  Objeto obj3 = {3, 1.5};
  inventario.AgregarOrdenado(obj1);
  inventario.AgregarOrdenado(obj2);
  inventario.AgregarOrdenado(obj3);
  cout << "Peso total: " << inventario.pesoTotal() << endl;
  // SimpleList<Objeto> objetos = inventario.ObtenerObjetos();
  // objetos.printl();
  // inventario.Clear();
  return 0;
}
