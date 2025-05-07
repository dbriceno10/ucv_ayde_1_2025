#include <iostream>
using namespace std;

const int MAX_N = 10; // Tamaño máximo del arreglo

// Función para intercambiar dos caracteres
void swap(char &a, char &b)
{
  char temp = a;
  a = b;
  b = temp;
}

// Función para calcular la suma de los valores ASCII de un arreglo
int calcularSuma(char arr[], int n)
{
  int suma = 0;
  for (int i = 0; i < n; i++)
  {
    suma += arr[i];
  }
  return suma;
}

// Función recursiva para generar todas las permutaciones
void generarPermutaciones(char arr[], int n, int index)
{
  if (index == n)
  {
    // Imprimir la permutación
    for (int i = 0; i < n; i++)
    {
      cout << arr[i];
    }
    cout << endl;
    return;
  }

  for (int i = index; i < n; i++)
  {
    swap(arr[index], arr[i]);                // Intercambiar
    generarPermutaciones(arr, n, index + 1); // Llamada recursiva
    swap(arr[index], arr[i]);                // Deshacer el intercambio
  }
}

// Función recursiva para generar permutaciones cuya suma sea par
void generarPermutacionesSumaPar(char arr[], int n, int index)
{
  if (index == n)
  {
    // Validar si la suma es par
    if (calcularSuma(arr, n) % 2 == 0)
    {
      // Imprimir la permutación
      for (int i = 0; i < n; i++)
      {
        cout << arr[i];
      }
      cout << endl;
    }
    return;
  }

  for (int i = index; i < n; i++)
  {
    swap(arr[index], arr[i]);                       // Intercambiar
    generarPermutacionesSumaPar(arr, n, index + 1); // Llamada recursiva
    swap(arr[index], arr[i]);                       // Deshacer el intercambio
  }
}

int main()
{
  char arr[MAX_N] = {'A', 'd', 'w', 'F', 'm', 'l', 'R', 'W', 'p', 'y'};
  int n = 10;

  // cout << "Ingrese el tamaño del arreglo (N <= " << MAX_N << "): ";
  // cin >> n;

  // if (n > MAX_N || n <= 0) {
  //     cout << "Tamaño inválido." << endl;
  //     return 1;
  // }

  // cout << "Ingrese los " << n << " caracteres del arreglo:" << endl;
  // for (int i = 0; i < n; i++)
  // {
  //   cin >> arr[i];
  // }

  cout << "\nTodas las permutaciones posibles:" << endl;
  generarPermutaciones(arr, n, 0);

  cout << "\nPermutaciones cuya suma sea par:" << endl;
  generarPermutacionesSumaPar(arr, n, 0);

  return 0;
}