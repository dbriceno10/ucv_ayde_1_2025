#include <iostream>
using namespace std;

template <typename T>
class MyVector
{
  T *data;
  int _size;
  int _capacity;

  void resize(int new_capacity)
  {
    T *new_data = new T[new_capacity];
    for (int i = 0; i < _size; ++i)
      new_data[i] = data[i];
    delete[] data;
    data = new_data;
    _capacity = new_capacity;
  }

public:
  MyVector() : data(nullptr), _size(0), _capacity(0) {}

  ~MyVector()
  {
    delete[] data;
  }

  int size() const { return _size; }
  int capacity() const { return _capacity; }
  bool empty() const { return _size == 0; }

  void push_back(const T &value)
  {
    if (_size == _capacity)
    {
      int new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
      resize(new_capacity);
    }
    data[_size++] = value;
  }

  void pop_back()
  {
    if (_size > 0)
      _size--;
  }

  T &operator[](int idx)
  {
    return data[idx];
  }

  const T &operator[](int idx) const
  {
    return data[idx];
  }

  void clear()
  {
    _size = 0;
  }

  void insert(int pos, const T &value)
  {
    if (pos < 0 || pos > _size)
      return;
    if (_size == _capacity)
    {
      int new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
      resize(new_capacity);
    }
    for (int i = _size; i > pos; --i)
      data[i] = data[i - 1];
    data[pos] = value;
    _size++;
  }

  void erase(int pos)
  {
    if (pos < 0 || pos >= _size)
      return;
    for (int i = pos; i < _size - 1; ++i)
      data[i] = data[i + 1];
    _size--;
  }

  int findIndex(const T &value) const
  {
    for (int i = 0; i < _size; ++i)
    {
      if (data[i] == value)
        return i;
    }
    return -1; // Not found
  }

  T &front() { return data[0]; }
  T &back() { return data[_size - 1]; }
};

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

  int getIndex(int *arr, int n, int element, int &count)
  {
    int index = -1;
    for (int i = 0; i < n; i++)
    {
      count++;
      if (arr[i] == element)
      {
        index = i;
        break;
      }
    }
    return index;
  }

public:
  typedef Node *tPosition;
  IntList() : size(0)
  {
    tail = new Node(0);
    head = new Node(0, tail);
  }
  ~IntList()
  {
    // Clear();
    delete head;
    delete tail;
  }

  bool IsEmpty()
  {
    return size == 0;
  }

  tPosition First()
  {
    return (head->next != tail) ? head->next : tail;
  }

  tPosition Last()
  {
    return tail;
  }

  void Next(tPosition &pValue)
  {
    if (pValue != tail)
    {
      pValue = pValue->next;
    }
  }

  int &Get(tPosition v)
  {
    return v->data;
  }

  void Insert(int d, tPosition v)
  {
    tPosition current = head;
    while (current->next != v && current->next != nullptr)
    {
      Next(current);
    }
    if (current->next == v)
    {
      current->next = new Node(d, v);
      size++;
    }
  }

  void Delete(tPosition v)
  {
    tPosition current = head;
    while (current->next != v && current->next != tail)
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

  void PrintList()
  {
    tPosition current = First();
    while (current != tail)
    {
      cout << Get(current) << endl;
      Next(current);
    }
  }

  void Clear()
  {
    tPosition current = First();
    while (current != tail)
    {
      tPosition toDelete = current;
      Next(current);
      delete toDelete;
    }
    head->next = tail; // Reset the list
    size = 0;
  }

  void suprimeRepeats()
  {
    tPosition current = First();
    MyVector<int> values;
    while (current != tail)
    {
      if (values.empty())
      {
        values.push_back(current->data);
        Next(current);
      }
      else
      {
        int index = values.findIndex(current->data);
        if (index == -1)
        {
          values.push_back(current->data);
          Next(current);
        }
        else
        {
          tPosition toDelete = current;
          Next(current);
          Delete(toDelete);
        }
      }
    }
  };

  IntList sortEvenOdd(IntList a)
  {
    IntList result;
    // Insertar pares al inicio
    IntList::tPosition pos = a.First();
    while (pos != a.Last())
    {
      if (a.Get(pos) % 2 == 0)
        result.Insert(a.Get(pos), result.Last());
      a.Next(pos);
    }
    // Insertar impares al final
    pos = a.First();
    while (pos != a.Last())
    {
      if (a.Get(pos) % 2 != 0)
        result.Insert(a.Get(pos), result.Last());
      a.Next(pos);
    }
    return result;
  }
};

int main()
{
  IntList lista;
  // Insertar elementos con repeticiones
  lista.Insert(1, lista.Last());
  lista.Insert(2, lista.Last());
  lista.Insert(2, lista.Last());
  lista.Insert(3, lista.Last());
  lista.Insert(1, lista.Last());
  lista.Insert(4, lista.Last());
  lista.Insert(3, lista.Last());
  lista.Insert(5, lista.Last());

  cout << "Lista original (con repeticiones):" << endl;
  lista.PrintList();

  lista.suprimeRepeats();

  cout << "Lista sin repeticiones:" << endl;
  lista.PrintList();

  return 0;
}