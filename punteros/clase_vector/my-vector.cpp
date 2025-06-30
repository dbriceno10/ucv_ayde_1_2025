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

  T &front() { return data[0]; }
  T &back() { return data[_size - 1]; }
};

int main()
{
  MyVector<int> v;
  v.push_back(10);
  v.push_back(20);
  v.push_back(30);
  v.insert(1, 15); // [10, 15, 20, 30]
  v.erase(2);      // [10, 15, 30]
  for (int i = 0; i < v.size(); ++i)
    cout << v[i] << " ";
  cout << endl;
  v.pop_back();
  cout << "Front: " << v.front() << ", Back: " << v.back() << endl;
  v.clear();
  cout << "Empty? " << (v.empty() ? "Yes" : "No") << endl;
  return 0;
}