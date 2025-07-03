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
  Node *head;
  Node *tail;
  int size;

public:
  typedef Node *tPosition;
  // Consturctor default para inicialilzar la lista vacia
  SimpleList() : size(0)
  {
    tail = new Node(T());
    head = new Node(T(), tail);
  }

  // constructor para inicializar la lista con un valor
  SimpleList(const T &value)
  {
    tail = new Node(value);
    head = new Node(T(), tail);
    size = 1;
  }

  ~SimpleList()
  {
    // Clear();
    delete head;
    delete tail;
  }

  //*Directiva 1(IsEmpty): Verifica si la lita esta vacia
  bool IsEmpty()
  {
    return size == 0;
  }

  //*Directiva 2(First): Obtiene el primer nodo de la lista
  tPosition First()
  {
    if (head->next != tail)
    {
      return head->next;
    }
    else
    {
      return tail;
    }
  }

  //*Directiva 3(Last): Obtiene el ultimo nodo de la lista
  tPosition Last()
  {
    // if (tail->next != nullptr)
    // {
    //   return tail;
    // }
    // else
    // {
    //   return head;
    // }
    return tail;
  }

  // Directiva 4(Next): Avanza al siguiente nodo
  void Next(tPosition &pValue)
  {
    // if (pValue->next != tail)
    if (pValue->next != nullptr)
    {
      pValue = pValue->next;
    }
    // else
    // {
    //   pValue = tail; // Si ya es el último nodo, se mantiene en tail
    // }
  }
  tPosition GetXNode(int index)
  {
    if (IsEmpty())
    {
      throw std::out_of_range("List is empty");
    }
    if (index < 1 || index > size)
    {
      throw std::out_of_range("Index out of range");
    }
    tPosition current = First();
    int currentIndex = 1;
    while (current != tail && currentIndex < index)
    {
      Next(current);
      currentIndex++;
    }
    return current;
  }
  // Directiva 5(Get): Obtiene el valor del nodo
  T &Get(tPosition v)
  {
    return v->data;
  }

  // Directiva 6(Insert): Inserta un nuevo nodo con el valor d antes del nodo v
  void Insert(const T &d, tPosition v)
  {
    if (IsEmpty())
    {
      tail = new Node(d);
      head->next = tail;
      size++;
    }
    else
    {
      tPosition current = head;
      while (current->next != v && current->next != nullptr) // o tambien current ! tail
      {
        Next(current);
      }
      if (current->next == v)
      {
        current->next = new Node(d, v);
        size++;
      }
    }
  }

  // Directiva 7(Delete): Elimina el nodo v de la lista
  void Delete(tPosition v)
  {
    // if (v == tail)
    // {
    //   delete v;
    //   size--;
    //   return;
    // }
    tPosition current = head;
    while (current->next != v && current->next != nullptr)
    {
      Next(current);
    }
    if (current->next == v)
    {
      current->next = v->next;
      delete v;
      size--;
    }
  }
  // Directiva 8(Clear): Elimina todos los nodos de la lista
  void Clear()
  {
    tPosition current = head;
    while (current->next != tail)
    {
      tPosition toDelete = current;
      Next(current);
      delete toDelete;
    }
    head->next = tail;
    size = 0;
  }

  void Print()
  {
    tPosition current = First();
    while (current->next != nullptr)
    {
      // cout << current->data << endl;
      cout << Get(current) << endl;
      Next(current);
    }
  }

  int Size() const
  {
    return size;
  }

  void PrintHeadTail()
  {
    cout << "Head: " << head->data << ", Tail: " << tail->data << endl;
  }

  void BubbleSortList()
  {
    if (IsEmpty() || size == 1)
      return;
    for (int i = 0; i < size - 1; ++i)
    {
      tPosition p = First();
      for (int j = 0; j < size - i - 1; ++j)
      {
        tPosition q = p->next;
        if (q != tail && p->data > q->data)
        {
          // Intercambia los valores de los nodos
          int temp = p->data;
          p->data = q->data;
          q->data = temp;
        }
        p = p->next;
      }
    }
  }
};

void printArray(int *array, int size)
{
  cout << "[";
  for (int i = 0; i < size; i++)
  {
    if (i == size - 1)
    {
      cout << array[i];
    }
    else
    {
      cout << array[i] << ", ";
    }
  }
  cout << "]";
  cout << endl;
}

void swap(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

void bubleSort(int *array, int size)
{
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = 0; j < size - i - 1; j++)
    {
      if (array[j] > array[j + 1])
      {
        // Intercambiar los elementos
        // int temp = array[j];
        // array[j] = array[j + 1];
        // array[j + 1] = temp;
        // Intercambiar los elementos
        swap(array[j], array[j + 1]);
      }
    }
  }
}

int main(int argc, char const *argv[])
{
  // SimpleList<int> lista = SimpleList<int>(800);
  SimpleList<int> lista;
  // lista = SimpleList<int>(21, 1); // Inicializar la lista vacia
  // Insertar elementos
  lista.Insert(32, lista.Last());
  lista.Insert(22, lista.Last());
  lista.Insert(4, lista.Last());
  lista.Insert(1, lista.Last());
  lista.Insert(64, nullptr);
  lista.Insert(23, lista.Last());
  SimpleList<int>::tPosition current = lista.First();
  SimpleList<int>::tPosition last = lista.Last();
  // cout << "curret " << current->data << endl;
  // lista.Next(current);
  // cout << "curret " << current->data << endl;
  // lista.Next(current);
  // cout << "curret " << current->data << endl;
  // lista.Next(current);
  // cout << "curret " << current->data << endl;
  // lista.Next(current);
  // cout << "curret " << current->data << endl;
  // lista.Next(current);
  // cout << "curret " << current->data << endl;
  // lista.Next(current);
  // cout << "curret " << current->data << endl;
  // lista.Next(current);
  // cout << "curret " << current->data << endl;
  // lista.Next(current);
  // cout << "curret " << current->data << endl;
  cout << "Tamaño de la lista: " << lista.Size() << endl;
  int *array = new int[lista.Size()];
  int index = 0;
  // while (current->next != nullptr)
  // {
  //   cout << lista.Get(current) << endl;
  //   current = current->next;
  // }

  // for (int i = 0; i < lista.Size(); i++)
  // {
  //   array[i] = lista.GetXNode(i + 1)->data;
  // }

  // while (current->next != nullptr && index < lista.Size())
  // {
  //   array[index] = current->data;
  //   cout << array[index] << endl;
  //   current = current->next;
  //   index++;
  // }

  // while (index < lista.Size())
  // {
  //   if (current->next == last && index == lista.Size() - 1)
  //   {
  //     array[index] = lista.Get(current);
  //   }
  //   else
  //   {
  //     array[index] = lista.Get(current);
  //   }
  //   lista.Next(current);
  //   index++;
  // }

  while (current->next != nullptr)
  {
    array[index] = lista.Get(current);
    index++;
    lista.Next(current);
  }
  cout << "list size " << lista.Size() << endl;
  cout << "index " << index << endl;
  array[index] = last->data; // Asignar el último elemento

  cout << "Last: " << last->data << endl;
  cout << "Array original: ";
  printArray(array, lista.Size());
  bubleSort(array, lista.Size());
  cout << "Array ordenado: ";
  printArray(array, lista.Size());
  lista.PrintHeadTail();
  // lista.Print();

  return 0;
}
