#include <iostream>
using namespace std;

class CircularArrayList
{
  char *data;
  int n;

public:
  CircularArrayList(int n) : n(n)
  {
    data = new char[n];
  }
  ~CircularArrayList()
  {
    delete[] data;
  }
  void set(int idx, char value)
  {
    if (idx >= 0 && idx < n)
      data[idx] = value;
  }
  void printFrom(int i, int m) const
  {
    int pos = i % n;
    for (int count = 0; count < m; ++count)
    {
      cout << data[pos] << " ";
      pos = (pos + 1) % n;
    }
    cout << endl;
  }
};

int main()
{
  int n = 5;
  CircularArrayList lista(n);

  // Ejemplo: llenar la lista con letras A, B, C, D, E
  for (int i = 0; i < n; ++i)
  {
    lista.set(i, 'A' + i);
  }

  int m, i0;
  cout << "Ingrese m (cantidad a imprimir): ";
  cin >> m;
  cout << "Ingrese i (posicion inicial, desde 0): ";
  cin >> i0;

  cout << "Imprimiendo " << m << " valores desde la posicion " << i0 << ":" << endl;
  lista.printFrom(i0, m);

  return 0;
}