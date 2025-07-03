#include <iostream>
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
  Node *head;
  Node *tail;
  int size;

public:
  typedef Node *tPosition;
  // Consturctor default para inicialilzar la lista vacia
  SimpleList() : size(0)
  {
    tail = new Node(T());
    head = new Node(T(), tail);
  }

  // constructor para inicializar la lista con un valor
  SimpleList(const T &value)
  {
    tail = new Node(value);
    head = new Node(value, tail);
    size = 1;
  }

  ~SimpleList()
  {
    // Clear();
    delete head;
    delete tail;
  }

  //*Directiva 1(IsEmpty): Verifica si la lita esta vacia
  bool IsEmpty()
  {
    return size == 0;
  }

  //*Directiva 2(First): Obtiene el primer nodo de la lista
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

  //*Directiva 3(Last): Obtiene el ultimo nodo de la lista
  tPosition Last()
  {
    // if (tail->next != nullptr)
    // {
    //   return tail;
    // }
    // else
    // {
    //   return head;
    // }
    return tail;
  }

  // Directiva 4(Next): Avanza al siguiente nodo
  void Next(tPosition &pValue)
  {
    if (pValue->next != tail)
    {
      pValue = pValue->next;
    }
    // else
    // {
    //   pValue = tail; // Si ya es el último nodo, se mantiene en tail
    // }
  }
  tPosition GetXNode(int index)
  {
    if (IsEmpty())
    {
      throw std::out_of_range("List is empty");
    }
    if (index < 1 || index > size)
    {
      throw std::out_of_range("Index out of range");
    }
    tPosition current = First();
    int currentIndex = 1;
    while (current != tail && currentIndex < index)
    {
      Next(current);
      currentIndex++;
    }
    return current;
  }
  // Directiva 5(Get): Obtiene el valor del nodo
  T &Get(tPosition v)
  {
    return v->data;
  }

  // Directiva 6(Insert): Inserta un nuevo nodo con el valor d antes del nodo v
  void Insert(const T &d, tPosition v)
  {
    tPosition current = head;
    while (current->next != v && current->next != nullptr) // o tambien current ! tail
    {
      Next(current);
    }
    if (current->next == v)
    {
      current->next = new Node(d, v);
      size++;
    }
  }

  // Directiva 7(Delete): Elimina el nodo v de la lista
  void Delete(tPosition v)
  {
    // if (v == tail)
    // {
    //   delete v;
    //   size--;
    //   return;
    // }
    tPosition current = head;
    while (current->next != v && current->next != tail)
    {
      Next(current);
    }
    if (current->next == v)
    {
      current->next = v->next;
      delete v;
      size--;
    }
  }
  // Directiva 8(Clear): Elimina todos los nodos de la lista
  void Clear()
  {
    tPosition current = head;
    while (current->next != tail)
    {
      tPosition toDelete = current;
      Next(current);
      delete toDelete;
    }
    head->next = tail;
    size = 0;
  }

  void Print()
  {
    tPosition current = First();
    while (current->next != tail)
    {
      // cout << current->data << endl;
      cout << Get(current) << endl;
      Next(current);
    }
  }

  int Size() const
  {
    return size;
  }
};

int main(int argc, char const *argv[])
{
  SimpleList<int> lista;
  // Insertar elementos
  lista.Insert(1, lista.Last());
  lista.Insert(2, lista.Last());
  lista.Insert(3, lista.Last());
  lista.Insert(4, lista.Last());
  lista.Insert(5, lista.Last());
  lista.Insert(6, lista.Last());
  // lista.Print();
  // cout << "Tamaño de la lista: " << lista.Size() << endl;
  // cout << "Primer elemento: " << lista.Get(lista.First()) << endl;
  // cout << "Ultimo elemento: " << lista.Get(lista.Last()) << endl;
  // cout << "Elemento en la posicion 3: " << lista.Get(lista.GetXNode(3)) << endl;
  // lista.Delete(lista.GetXNode(3));
  // cout << "Lista despues de eliminar el elemento en la posicion 3:" << endl;
  // lista.Print();
  // cout << "Tamaño de la lista: " << lista.Size() << endl;
  // lista.Clear();
  SimpleList<int>::tPosition current = lista.First();
  while (current->next)
  {
    /* code */
  }
  
  return 0;
}
