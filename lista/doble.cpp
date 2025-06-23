#include <iostream>
using namespace std;

template <typename T>
class DobleList
{
  struct Node
  {
    T data;
    Node *next;
    Node *prev; // Puntero al nodo anterior
    Node(const T &d, Node *n = nullptr, Node *p = nullptr) : data(d), next(n), prev(p) {}
  };
  Node *head;
  Node *tail;
  int size;

public:
  typedef Node *tPosition;
  // Consturctor default para inicialilzar la lista vacia
  DobleList() : size(0)
  {
    tail = new Node(T());
    head = new Node(T(), tail);
    tail->prev = head;
    head->prev = nullptr;
    tail->next = nullptr;
  }

  // constructor para inicializar la lista con un valor
  // DobleList(const T &value)
  // {
  //   tail = new Node(value);
  //   head = new Node(value, tail);
  //   size = 1;
  // }

  ~DobleList()
  {
    Clear();
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

  // Directiva 4.5(Prev): Retrocede al nodo anterior

  void Prev(tPosition &pValue)
  {
    if (pValue->prev != head)
    {
      pValue = pValue->prev;
    }
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
      tPosition newNode = new Node(d, v, current);
      current->next = newNode;
      if (v != tail)
      {
        v->prev = newNode;
      }
      else
      {
        tail->prev = newNode;
      }
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
    tPosition current = head;
    while (current != tail)
    {
      // cout << current->data << endl;
      cout << Get(current) << endl;
      Next(current);
    }
  }
};
