#include <iostream>
using namespace std;

// Lista circular simple
template <typename T>
class CircularList
{
  struct Node
  {
    T data;
    Node *next;
    Node(const T &d) : data(d), next(nullptr) {}
  };
  Node *tail;

public:
  CircularList() : tail(nullptr) {}
  ~CircularList() { Clear(); }

  // Elimina todos los nodos
  void Clear()
  {
    if (!tail)
      return;
    Node *curr = tail->next;
    do
    {
      Node *temp = curr;
      curr = curr->next;
      delete temp;
    } while (curr != tail->next);
    tail = nullptr;
  }

  // Inserta al final
  void Insert(const T &value)
  {
    Node *newNode = new Node(value);
    if (!tail)
    {
      tail = newNode;
      tail->next = tail;
    }
    else
    {
      newNode->next = tail->next;
      tail->next = newNode;
      tail = newNode;
    }
  }

  // Inserta después de un nodo dado (p debe ser un puntero a Node)
  void InsertAfter(Node *p, const T &value)
  {
    if (!p) return;
    Node *newNode = new Node(value);
    newNode->next = p->next;
    p->next = newNode;
    if (p == tail)
      tail = newNode;
  }

  // Elimina el nodo después de p (p debe ser un puntero a Node)
  void DeleteAfter(Node *p)
  {
    if (!tail || !p || !p->next) return;
    Node *toDelete = p->next;
    if (toDelete == tail)
    {
      if (tail == tail->next) // Solo un nodo
      {
        delete tail;
        tail = nullptr;
        return;
      }
      tail = p;
    }
    p->next = toDelete->next;
    delete toDelete;
  }

  // Imprime la lista
  void Print() const
  {
    if (!tail)
      return;
    Node *curr = tail->next;
    do
    {
      cout << curr->data << " ";
      curr = curr->next;
    } while (curr != tail->next);
    cout << endl;
  }

  // Devuelve el puntero al primer nodo
  Node* Head() const { return tail ? tail->next : nullptr; }
  // Devuelve el puntero al último nodo
  Node* Tail() const { return tail; }
};

// Lista circular doble
template <typename T>
class CircularDoublyList
{
  struct Node
  {
    T data;
    Node *next;
    Node *prev;
    Node(const T &d) : data(d), next(nullptr), prev(nullptr) {}
  };
  Node *tail;

public:
  CircularDoublyList() : tail(nullptr) {}
  ~CircularDoublyList() { Clear(); }

  // Elimina todos los nodos
  void Clear()
  {
    if (!tail)
      return;
    Node *curr = tail->next;
    do
    {
      Node *temp = curr;
      curr = curr->next;
      delete temp;
    } while (curr != tail->next);
    tail = nullptr;
  }

  // Inserta al final
  void Insert(const T &value)
  {
    Node *newNode = new Node(value);
    if (!tail)
    {
      tail = newNode;
      tail->next = tail;
      tail->prev = tail;
    }
    else
    {
      Node *head = tail->next;
      newNode->next = head;
      newNode->prev = tail;
      head->prev = newNode;
      tail->next = newNode;
      tail = newNode;
    }
  }

  // Inserta después de un nodo dado (p debe ser un puntero a Node)
  void InsertAfter(Node *p, const T &value)
  {
    if (!p) return;
    Node *newNode = new Node(value);
    Node *nextNode = p->next;
    newNode->next = nextNode;
    newNode->prev = p;
    p->next = newNode;
    nextNode->prev = newNode;
    if (p == tail)
      tail = newNode;
  }

  // Elimina el nodo después de p (p debe ser un puntero a Node)
  void DeleteAfter(Node *p)
  {
    if (!tail || !p || !p->next) return;
    Node *toDelete = p->next;
    if (toDelete == tail)
    {
      if (tail == tail->next) // Solo un nodo
      {
        delete tail;
        tail = nullptr;
        return;
      }
      tail = p;
    }
    Node *nextNode = toDelete->next;
    p->next = nextNode;
    nextNode->prev = p;
    delete toDelete;
  }

  // Imprime hacia adelante
  void PrintForward() const
  {
    if (!tail)
      return;
    Node *curr = tail->next;
    do
    {
      cout << curr->data << " ";
      curr = curr->next;
    } while (curr != tail->next);
    cout << endl;
  }

  // Imprime hacia atrás
  void PrintBackward() const
  {
    if (!tail)
      return;
    Node *curr = tail;
    do
    {
      cout << curr->data << " ";
      curr = curr->prev;
    } while (curr != tail);
    cout << endl;
  }

  // Devuelve el puntero al primer nodo
  Node* Head() const { return tail ? tail->next : nullptr; }
  // Devuelve el puntero al último nodo
  Node* Tail() const { return tail; }
};

int main()
{
  cout << "Lista circular simple: ";
  CircularList<int> clist;
  clist.Insert(1);
  clist.Insert(2);
  clist.Insert(3);
  clist.Print();

  // Insertar después del primer nodo
  auto head = clist.Head();
  clist.InsertAfter(head, 99);
  clist.Print();

  // Eliminar el nodo después del primer nodo
  clist.DeleteAfter(head);
  clist.Print();

  // Limpiar la lista
  clist.Clear();
  clist.Print();

  cout << "Lista circular doble (adelante): ";
  CircularDoublyList<int> cdlist;
  cdlist.Insert(10);
  cdlist.Insert(20);
  cdlist.Insert(30);
  cdlist.PrintForward();

  // Insertar después del primer nodo
  auto dhead = cdlist.Head();
  cdlist.InsertAfter(dhead, 77);
  cdlist.PrintForward();

  // Eliminar el nodo después del primer nodo
  cdlist.DeleteAfter(dhead);
  cdlist.PrintForward();

  // Limpiar la lista
  cdlist.Clear();
  cdlist.PrintForward();

  cout << "Lista circular doble (atrás): ";
  cdlist.Insert(100);
  cdlist.Insert(200);
  cdlist.Insert(300);
  cdlist.PrintBackward();

  return 0;
}