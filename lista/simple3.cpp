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

  void printl()
  {
    tPosition current = first();
    while (current != tail)
    {
      cout << Get(current) << endl;
      next(current);
    }
  }

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

int main()
{
  SimpleList<int> lista;
  lista.insert(1, lista.last());
  lista.insert(2, lista.last());
  lista.insert(3, lista.last());
  lista.insert(4, lista.last());
  lista.insert(5, lista.last());
  lista.insert(6, lista.last());
  lista.insert(7, lista.last());
  lista.insert(8, lista.last());
  lista.insert(9, lista.last());
  lista.insert(10, lista.last());

  lista.printHeadTail();

  lista.printl();

  cout << "first: " << lista.first()->data << endl;
  cout << "last: " << lista.last()->data << endl;
  // // Ejemplo con otro tipo
  // SimpleList<string> slist;
  // slist.insert("hola", slist.last());
  // slist.insert("mundo", slist.last());
  // slist.printl();

  return 0;
}