#include <iostream>
using namespace std;

template <typename T>
class DobleCircularList
{
  struct Node
  {
    T data;
    Node *next;
    Node *prev;
    Node(const T &d) : data(d), next(nullptr), prev(nullptr) {}
  };
  Node *head;
  int size;

public:
  typedef Node *tPosition;

  DobleCircularList() : head(nullptr), size(0) {}

  ~DobleCircularList()
  {
    Clear();
  }

  bool IsEmpty() const { return size == 0; }

  tPosition First() const { return head; }

  tPosition Last() const { return head ? head->prev : nullptr; }

  void Insert(const T &d, tPosition pos = nullptr)
  {
    Node *newNode = new Node(d);
    if (IsEmpty())
    {
      newNode->next = newNode->prev = newNode;
      head = newNode;
    }
    else if (pos == nullptr || pos == head)
    {
      // Insertar al principio
      Node *last = head->prev;
      newNode->next = head;
      newNode->prev = last;
      last->next = newNode;
      head->prev = newNode;
      head = newNode;
    }
    else
    {
      // Insertar antes de pos
      Node *prevNode = pos->prev;
      newNode->next = pos;
      newNode->prev = prevNode;
      prevNode->next = newNode;
      pos->prev = newNode;
    }
    size++;
  }

  void Delete(tPosition pos)
  {
    if (IsEmpty() || !pos)
      return;
    if (size == 1)
    {
      delete pos;
      head = nullptr;
    }
    else
    {
      Node *prevNode = pos->prev;
      Node *nextNode = pos->next;
      prevNode->next = nextNode;
      nextNode->prev = prevNode;
      if (pos == head)
        head = nextNode;
      delete pos;
    }
    size--;
  }

  void Clear()
  {
    while (!IsEmpty())
      Delete(head);
  }

  void Print() const
  {
    if (IsEmpty())
      return;
    Node *current = head;
    do
    {
      cout << current->data << " ";
      current = current->next;
    } while (current != head);
    cout << endl;
  }
};

// Ejemplo de uso
int main()
{
  DobleCircularList<int> lista;
  lista.Insert(1);
  lista.Insert(2);
  lista.Insert(3);
  lista.Print(); // 3 2 1

  lista.Delete(lista.First());
  lista.Print(); // 2 1

  return 0;
}