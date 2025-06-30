#include <iostream>
using namespace std;

int suma(int *arr, int n)
{
  int total = 0;
  for (int i = 0; i < n; ++i)
  {
    total += arr[i];
  }
  return total;
}

int main(int argc, char const *argv[])
{
  int n = 10;
  int *arr = new int[n];
  // Pre-cargar con los valores del 1 al 10
  for (int i = 0; i < n; ++i)
  {
    arr[i] = i + 1;
  }

  cout << "suma " << suma(arr, n) << endl;
  delete[] arr;
  return 0;
}
