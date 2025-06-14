#include <iostream>
using namespace std;

template <typename T>
class Stack
{
  struct Node
  {
    T data;
    Node *next;

    Node(const T &d, Node *n = nullptr) : data(d), next(n) {}
  };

  Node *topNode; // puntero al tope de la pila
  int count;     // tamaño de la pila
public:
  // Constructor para inicializar la pila
  Stack() : topNode(nullptr), count(0) {}
  // Destructor para liberar memoria

  int Size() const
  {
    return count;
  }
  bool IsEmpty() const
  {
    return count == 0;
  }
  void Clear()
  {
    while (!IsEmpty())
    {
      Pop();
    }
    // {
    //   Node *temp = topNode;
    //   topNode = topNode->next;
    //   delete temp;
    // }
    count = 0;
  }
  // saca al elementro del tope de la pila, y lo elimina
  void Pop()
  {
    if (IsEmpty())
    {
      // throw runtime_error("Stack is empty");
      throw std::out_of_range("Stack is empty");
    }
    Node *temp = topNode;
    topNode = topNode->next;
    delete temp;
    count--;
  }
  // inserta un elemento al tope de la pila
  void Push(const T &value)
  {
    // Node *newNode = new Node(value, topNode);
    topNode = new Node(value, topNode);

    // topNode = newNode;
    count++;
  }

  T Top() const
  {
    if (IsEmpty())
    {
      // throw runtime_error("Stack is empty");
      throw out_of_range("Stack is empty");
    }
    return topNode->data;
  }
};