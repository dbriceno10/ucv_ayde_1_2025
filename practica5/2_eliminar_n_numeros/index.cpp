#include <iostream>
using namespace std;

class IntList
{
  struct Node
  {
    int data;
    Node *next;
    Node(int d, Node *n = nullptr) : data(d), next(n) {}
  };
  Node *head;
  Node *tail;
  int size;

public:
  typedef Node *tPosition;

  IntList() : size(0)
  {
    tail = new Node(0);
    head = new Node(0, tail);
  }

  ~IntList()
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

  void insert(int d, tPosition v)
  {
    tPosition current = head;
    while (current->next != v && current->next != nullptr)
    {
      current = current->next;
    }
    if (current->next == v)
    {
      current->next = new Node(d, v);
      size++;
    }
  }

  void Delete(tPosition v)
  {
    if (v == tail)
      return;
    tPosition current = head;
    while (current->next != v && current->next != tail)
    {
      current = current->next;
    }
    if (current->next == v)
    {
      current->next = v->next;
      delete v;
      size--;
    }
  }

  // void removeAll(int n)
  // {
  //   tPosition current = head;
  //   while (current->next != tail)
  //   {
  //     if (current->next->data == n)
  //     {
  //       tPosition toDelete = current->next;
  //       current->next = toDelete->next;
  //       delete toDelete;
  //       size--;
  //     }
  //     else
  //     {
  //       current = current->next;
  //     }
  //   }
  // }

  void removeAll(int n)
  {
    Node *current = head;
    while (current->next != nullptr)
    {
      if (current->next->data == n)
      {
        tPosition toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;
        size--;
      }
      else
      {
        next(current);
      }
    }
  }

  void printl()
  {
    tPosition current = first();
    int count = 1;
    while (current != tail)
    {
      cout << "Elemento " << count << ": " << current->data << endl;
      current = current->next;
      count++;
    }
  }

  void clear()
  {
    tPosition current = first();
    while (current != tail)
    {
      tPosition toDelete = current;
      current = current->next;
      delete toDelete;
    }
    head->next = tail;
    size = 0;
  }
};

int main()
{
  IntList lista;
  lista.insert(1, lista.last());
  lista.insert(2, lista.last());
  lista.insert(3, lista.last());
  lista.insert(2, lista.last());
  lista.insert(4, lista.last());
  lista.insert(2, lista.last());

  cout << "Lista original:" << endl;
  lista.printl();

  int n;
  cout << "Ingrese el número a eliminar de la lista: ";
  cin >> n;
  lista.removeAll(n);

  cout << "Lista después de eliminar todas las ocurrencias de " << n << ":" << endl;
  lista.printl();

  return 0;
}