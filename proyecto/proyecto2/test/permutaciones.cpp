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
bool include(string *array, string string, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (array[i] == string)
    {
      return true;
    }
  }
  return false;
}

// imprimir premutacion
void imprimirPermutacion(char arr[], int n, string *array, int &size)
{
  string perm = "";
  for (int i = 0; i < n; i++)
  {
    perm += arr[i];
  }
  if (size == 0)
  {
    array[size] = perm;
    size++;
  }
  else
  {
    if (!include(array, perm, size))
    {
      array[size] = perm;
      size++;
    }
  }
}

// Función recursiva para generar todas las permutaciones
void generarPermutaciones(char arr[], int n, int index, string *array, int &size)
{
  // cout << "index: " << index << endl;
  // cout << "n: " << n << endl;
  // imprimirPermutacion(arr, n);
  if (index == n)
  {
    // cout << "index == n" << endl;
    // Imprimir la permutación
    imprimirPermutacion(arr, n, array, size);
    // cout << "suma: " << calcularSuma(arr, n) << endl;
    return;
  }

  for (int i = index; i < n; i++)
  {
    swap(arr[index], arr[i]);                             // Intercambiar
    generarPermutaciones(arr, n, index + 1, array, size); // Llamada recursiva
    swap(arr[index], arr[i]);                             // Deshacer el intercambio
  }
}

// Función recursiva para generar permutaciones cuya suma sea par
// void generarPermutacionesSumaPar(char arr[], int n, int index)
// {
//   if (index == n)
//   {
//     // Validar si la suma es par
//     if (calcularSuma(arr, n) % 2 == 0)
//     {
//       // Imprimir la permutación
//       imprimirPermutacion(arr, n, );
//     }
//     return;
//   }

//   for (int i = index; i < n; i++)
//   {
//     swap(arr[index], arr[i]);                       // Intercambiar
//     generarPermutacionesSumaPar(arr, n, index + 1); // Llamada recursiva
//     swap(arr[index], arr[i]);                       // Deshacer el intercambio
//   }
// }

bool isDigit(char c)
{
  return c >= '0' && c <= '9';
}

string readInput()
{
  string input;
  cout << "Enter a string: ";
  cin >> input;
  char prev = '\0';
  int size = input.size();
  string dna = "";
  for (int i = 0; i < size; i++)
  {
    if (i == 0)
    {
      prev = input[0];
      dna += input[0];
      continue;
    }
    if (isDigit(input[i]))
    {
      int repeats = input[i] - '0';
      for (int j = 1; j < repeats; j++)
      {
        dna += prev;
      }
    }
    else
    {
      dna += input[i];
      prev = input[i];
    }
  }
  return dna;
}

int factorial(int n)
{
  if (n <= 1)
    return 1;
  return n * factorial(n - 1);
}

int main()
{
  char arr[MAX_N] = {'H', 'H', 'E', 'E', 'E'};
  int n = 5;

  int combinaciones = factorial(n);

  string *array = new string[combinaciones];
  int size = 0;

  cout << "\nTodas las permutaciones posibles:" << endl;
  generarPermutaciones(arr, n, 0, array, size);

  cout << "Total de permutaciones: " << size << endl;
  cout << "Permutaciones:" << endl;
  for (int i = 0; i < size; i++)
  {
    cout << array[i] << endl;
  }

  return 0;
}