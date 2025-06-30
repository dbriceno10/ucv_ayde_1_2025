#include <iostream>
using namespace std;

template <typename T>
class SimpleCircularList
{
  struct Node
  {
    T data;
    Node *next;
    Node(const T &d) : data(d), next(nullptr) {}
  };
  Node *head;
  int size;

public:
  typedef Node *tPosition;

  SimpleCircularList() : head(nullptr), size(0) {}

  ~SimpleCircularList()
  {
    Clear();
  }

  bool IsEmpty() const { return size == 0; }

  tPosition First() const { return head; }

  tPosition Last() const { return head ? GetLast() : nullptr; }

  void Insert(const T &d, tPosition pos = nullptr)
  {
    Node *newNode = new Node(d);
    if (IsEmpty())
    {
      newNode->next = newNode;
      head = newNode;
    }
    else if (pos == nullptr || pos == head)
    {
      // Insertar al principio
      Node *last = GetLast();
      newNode->next = head;
      last->next = newNode;
      head = newNode;
    }
    else
    {
      // Insertar antes de pos
      Node *prev = head;
      while (prev->next != pos && prev->next != head)
        prev = prev->next;
      newNode->next = pos;
      prev->next = newNode;
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
      Node *prev = head;
      while (prev->next != pos && prev->next != head)
        prev = prev->next;
      prev->next = pos->next;
      if (pos == head)
        head = pos->next;
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

private:
  Node* GetLast() const
  {
    Node *current = head;
    while (current->next != head)
      current = current->next;
    return current;
  }
};

// Ejemplo de uso
int main()
{
  SimpleCircularList<int> lista;
  lista.Insert(1);
  lista.Insert(2);
  lista.Insert(3);
  lista.Print(); // 3 2 1

  lista.Delete(lista.First());
  lista.Print(); // 2 1

  return 0;
}