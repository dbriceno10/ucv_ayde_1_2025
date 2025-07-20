#include <iostream>
using namespace std;

template <typename T>
class historyDNA
{
private:
  struct Node
  {
    T data;
    Node *next;
    Node(const T &d, Node *n = nullptr) : data(d), next(n) {}
  };

  Node *topNode; // Puntero al tope
  int count;     // Contador de elementos

public:
  // Constructor
  historyDNA() : topNode(nullptr), count(0) {}

  // Destructor
  ~historyDNA()
  {
    Clear();
  }

  // Vacía la pila
  void Clear()
  {
    while (!IsEmpty())
    {
      Pop();
    }
    topNode = nulptr;
    count = 0;
  }

  // Verifica si está vacía
  bool IsEmpty() const
  {
    return count == 0;
  }

  // Agrega elemento al tope
  void Push(const T &x)
  {
    topNode = new Node(x, topNode);
    count++;
  }

  // Elimina el elemento del tope
  void Pop()
  {
    // if (IsEmpty())
    // {
    //   cout << "Pila vacía" << endl;
    // }
    Node *temp = topNode;
    topNode = topNode->next;
    delete temp;
    count--;
  }

  // Tamaño de la pila
  int Size() const
  {
    return count;
  }

  // Acceso al elemento tope
  T Top() const
  {
    // if (IsEmpty())
    // {
    //   cout << "Pila vacía" << endl;
    // }
    return topNode->data;
  }

  bool Include(T element)
  {
    if (IsEmpty())
      return false;
    bool flag = false;
    Node *current = topNode;
    while (current && !flag)
    {
      if (current->data == element)
      {
        flag = true;
      }
      else
      {
        current = current->next;
      }
    }
    return flag;
  }
};

int main(int argc, char const *argv[])
{
  historyDNA<int> stack;

  for (int i = 0; i < 20; i++)
  {
    cout << "push " << i + 1 << endl;
    stack.Push(i + 1);
  }
  cout << "esta el 15? " << (stack.Include(15) ? "SI" : "NO") << endl;
  cout << "esta el 30? " << (stack.Include(30) ? "SI" : "NO") << endl;
  for (int i = 0; i < 20; i++)
  {
    cout << "pop " << stack.Top() << endl;
    stack.Pop();
  }
  return 0;
}
