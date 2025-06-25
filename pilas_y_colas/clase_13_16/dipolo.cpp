#include <iostream>

using namespace std;

// Dipolo: Clase que representa un dipolo con dos cargas

#include <iostream>
using namespace std;

template <typename T>
class Dipolo
{
  struct Node
  {
    T data;
    Node *next;
    Node *prev;
    Node(const T &d) : data(d), next(nullptr), prev(nullptr) {}
  };
  Node *topNode;    // Tope de la estructura
  Node *bottomNode; // Fondo de la estructura
  int count;

public:
  Dipolo() : topNode(nullptr), bottomNode(nullptr), count(0) {}

  ~Dipolo() { Clear(); }

  // Inserta en el tope (como Push)
  void Push(const T &value)
  {
    Node *newNode = new Node(value);
    if (IsEmpty())
    {
      topNode = bottomNode = newNode;
    }
    else
    {
      newNode->next = topNode;
      topNode->prev = newNode;
      topNode = newNode;
    }
    count++;
  }

  // Saca del tope (como Pop)
  void PopTop()
  {
    if (IsEmpty())
      throw out_of_range("Dipolo vacío");
    Node *temp = topNode;
    if (topNode == bottomNode)
    {
      topNode = bottomNode = nullptr;
    }
    else
    {
      topNode = topNode->next;
      topNode->prev = nullptr;
    }
    delete temp;
    count--;
  }

  // Saca del fondo (como Dequeue)
  void PopBottom()
  {
    if (IsEmpty())
      throw out_of_range("Dipolo vacío");
    Node *temp = bottomNode;
    if (topNode == bottomNode)
    {
      topNode = bottomNode = nullptr;
    }
    else
    {
      bottomNode = bottomNode->prev;
      bottomNode->next = nullptr;
    }
    delete temp;
    count--;
  }

  // Accede al tope
  T Top() const
  {
    if (IsEmpty())
      throw out_of_range("Dipolo vacío");
    return topNode->data;
  }

  // Accede al fondo
  T Bottom() const
  {
    if (IsEmpty())
      throw out_of_range("Dipolo vacío");
    return bottomNode->data;
  }

  int Size() const { return count; }
  bool IsEmpty() const { return count == 0; }

  void Clear()
  {
    while (!IsEmpty())
      PopTop();
  }

  void Print() const
  {
    Node *current = topNode;
    cout << "[";
    while (current)
    {
      cout << current->data;
      if (current->next)
        cout << ", ";
      current = current->next;
    }
    cout << "]" << endl;
  }
};

// Ejemplo de uso
int main()
{
  Dipolo<int> d;
  d.Push(1);
  d.Push(2);
  d.Push(3);
  d.Print(); // [3, 2, 1]

  d.PopTop();
  d.Print(); // [2, 1]

  d.PopBottom();
  d.Print(); // [2]

  return 0;
}