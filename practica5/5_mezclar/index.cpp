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

  tPosition first() const
  {
    return (head->next != tail) ? head->next : tail;
  }

  tPosition last() const
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

IntList mezcla2(const IntList &a, const IntList &b)
{
  IntList resultado;
  IntList::tPosition pa = a.first();
  IntList::tPosition pb = b.first();

  while (pa != a.last() && pb != b.last())
  {
    if (pa->data <= pb->data)
    {
      resultado.insert(pa->data, resultado.last());
      pa = pa->next;
    }
    else
    {
      resultado.insert(pb->data, resultado.last());
      pb = pb->next;
    }
  }
  // Agregar los elementos restantes de a
  while (pa != a.last())
  {
    resultado.insert(pa->data, resultado.last());
    pa = pa->next;
  }
  // Agregar los elementos restantes de b
  while (pb != b.last())
  {
    resultado.insert(pb->data, resultado.last());
    pb = pb->next;
  }
  return resultado;
}

int main()
{

  IntList lista1, lista2;
  lista1.insert(1, lista1.last());
  lista1.insert(3, lista1.last());
  lista1.insert(5, lista1.last());
  lista1.insert(7, lista1.last());
  lista1.insert(9, lista1.last());

  lista2.insert(2, lista2.last());
  lista2.insert(4, lista2.last());
  lista2.insert(6, lista2.last());
  lista2.insert(8, lista2.last());
  lista2.insert(10, lista2.last());

  cout << "Lista 1:" << endl;
  lista1.printl();
  cout << "Lista 2:" << endl;
  lista2.printl();

  IntList resultado = mezcla2(lista1, lista2);
  cout << "Lista mezclada:" << endl;
  resultado.printl();

  return 0;

  return 0;
}