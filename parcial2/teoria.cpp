#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
  int a = 6;
  int *b = &a;
  *b = 3;
  int **c = new int *[a];
  for (int i = 0; i < a; i++)
  {
    c[i] = new int[2];
    for (int j = 0; j < 2; j++)
    {
      c[i][j] = i + j;
    }
  }
  cout << a << endl;
  cout << *b << endl;
  for (int i = 0; i < a; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      cout << c[i][j] << "";
    }
    cout << endl;
  }
  int *d = &c[0][1];
  cout << *d << endl;
  delete[] c;
  cout << endl
       << *d << endl;
  return 0;
}
