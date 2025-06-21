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
    tPosition current = First();
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
    tPosition current = First();
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
    tPosition current = First();
    while (current != tail)
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
    while (current != tail)
    {
      // cout << current->data << endl;
      cout << Get(current) << endl;
      Next(current);
    }
  }
};

int main(int argc, char const *argv[])
{
  SimpleList<int> lista;
  lista.Insert(10, lista.Last());
  lista.Insert(20, lista.Last());
  lista.Insert(30, lista.Last());
  lista.Print();
  cout << "Size: " << lista.IsEmpty() << endl;
  lista.Clear();
  cout << "Size after clear: " << lista.IsEmpty() << endl;
  lista.Insert(40, lista.Last());
  lista.Print();
  lista.Insert(50, lista.Last());
  lista.Print();
  lista.Insert(60, lista.Last());
  lista.Print();
  lista.Insert(70, lista.Last());
  lista.Print();
  lista.Insert(80, lista.Last());
  lista.Print();
  lista.Insert(90, lista.Last());
  lista.Print();
  lista.Insert(100, lista.Last());
  lista.Print();
  cout << "Size after insertions: " << lista.IsEmpty() << endl;
  lista.Clear();
  cout << "Size after clear: " << lista.IsEmpty() << endl;
  lista.Print();
  return 0;
}
