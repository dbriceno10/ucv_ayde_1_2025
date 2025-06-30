#include <iostream>
using namespace std;

// Suma recursiva de los elementos de un arreglo, llamando la función n/2 veces
int sumaRecursiva(int *arr, int inicio, int fin)
{
  if (inicio > fin)
    return 0;
  if (inicio == fin)
    return arr[inicio];
  int mid = (inicio + fin) / 2;
  // Solo dos llamadas recursivas por nivel, así la profundidad es log2(n)
  return sumaRecursiva(arr, inicio, mid) + sumaRecursiva(arr, mid + 1, fin);
}

// int main()
// {
//   int n;
//   cout << "Ingrese el tamaño del arreglo: ";
//   cin >> n;
//   int *arr = new int[n];
//   cout << "Ingrese los elementos:" << endl;
//   for (int i = 0; i < n; ++i)
//     cin >> arr[i];

//   int suma = sumaRecursiva(arr, 0, n - 1);
//   cout << "La suma de los elementos es: " << suma << endl;

//   delete[] arr;
//   return 0;
// }

int main()
{
  int n = 10;
  int arr[10];
  // Pre-cargar con los valores del 1 al 10
  for (int i = 0; i < n; ++i)
    arr[i] = i + 1;

  cout << "Elementos del arreglo: ";
  for (int i = 0; i < n; ++i)
    cout << arr[i] << " ";
  cout << endl;

  int suma = sumaRecursiva(arr, 0, n - 1);
  cout << "La suma de los elementos es: " << suma << endl;

  return 0;
}