#include <iostream>
using namespace std;

template <typename T>
class Queue
{
  struct Node
  {
    T data;
    Node *next;

    Node(const T &d, Node *n = nullptr) : data(d), next(n) {}
  };

  Node *front; // primer elemeto
  Node *rear;  // ultimo elemento
  int count;   // tamaño de la pila

public:
  // Constructor para inicializar la cola
  Queue() : front(nullptr), rear(nullptr), count(0) {}
  // Destructor para liberar memoria
  ~Queue()
  {
    while (!IsEmpty())
    {
      Dequeue();
    }
  }
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
      Dequeue();
    }
    count = 0;
  }
  // saca al elemento del frente de la cola, y lo elimina
  void Dequeue()
  {
    if (IsEmpty())
    {
      throw std::out_of_range("Queue is empty");
    }
    Node *temp = front;
    front = front->next;
    delete temp;
    count--;
    // if (IsEmpty())
    if (front == nullptr)
    {
      rear = nullptr; // Si la cola queda vacía, rear también debe ser nullptr
    }
  }
  // inserta un elemento al final de la cola
  void Enqueue(const T &value)
  {
    Node *newNode = new Node(value);
    if (IsEmpty())
    {
      front = rear = newNode; // Si la cola está vacía, front y rear apuntan al nuevo nodo, basicamente soy el primero y el ultimo a la vez
      //Alternativa
      // fornt = rear // Apunta front al nuevo nodo
      // rear = newNode; // Actualiza rear al nuevo nodo
    }
    else
    {
      rear->next = newNode; // Enlaza el nuevo nodo al final de la cola
      rear = newNode;       // Actualiza rear al nuevo nodo
    }
    count++;
  }
  // obtiene el elemento del frente de la cola sin eliminarlo
  T Front() const
  {
    if (IsEmpty())
    {
      throw std::out_of_range("Queue is empty");
    }
    return front->data;
  }
  // obtiene el elemento del final de la cola sin eliminarlo
  T Back() const
  {
    if (IsEmpty())
    {
      throw std::out_of_range("Queue is empty");
    }
    return rear->data;
  }
  // imprime los elementos de la cola
};