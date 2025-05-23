#include <iostream>
using namespace std;
const int MAX_N = 10; // Tamaño máximo de la matriz
// Función para imprimir la matriz
void imprimirMatriz(int mat[][MAX_N], int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cout << mat[i][j] << " ";
    }
    cout << endl;
  }
}

void generarMatriz(int mat[][MAX_N])
{
  int valor = 1;
  for (int i = 0; i < MAX_N; i++)
    for (int j = 0; j < MAX_N; j++)
      mat[i][j] = valor++;
}

void recorrerPorFilas(int mat[][MAX_N], int n)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cout << mat[i][j] << " ";
  cout << endl;
}
// Recorre la matriz de izquierda a derecha, fila por fila.

void recorrerPorColumnas(int mat[][MAX_N], int n)
{
  for (int j = 0; j < n; j++)
    for (int i = 0; i < n; i++)
      cout << mat[i][j] << " ";
  cout << endl;
}
// Recorre la matriz de arriba a abajo, columna por columna.

void recorrerDiagonalPrincipal(int mat[][MAX_N], int n)
{
  for (int i = 0; i < n; i++)
    cout << mat[i][i] << " ";
  cout << endl;
}
// Recorre los elementos donde fila == columna.

void recorrerDiagonalSecundaria(int mat[][MAX_N], int n)
{
  for (int i = 0; i < n; i++)
    cout << mat[i][n - 1 - i] << " ";
  cout << endl;
}
// Recorre los elementos donde fila + columna == n - 1.

void recorrerEspiral(int mat[][MAX_N], int n)
{
  int inicio = 0, fin = n - 1;
  while (inicio <= fin)
  {
    for (int j = inicio; j <= fin; j++)
      cout << mat[inicio][j] << " "; // Arriba
    for (int i = inicio + 1; i <= fin; i++)
      cout << mat[i][fin] << " "; // Derecha
    for (int j = fin - 1; j >= inicio; j--)
      if (inicio != fin)
        cout << mat[fin][j] << " "; // Abajo
    for (int i = fin - 1; i > inicio; i--)
      if (inicio != fin)
        cout << mat[i][inicio] << " "; // Izquierda
    inicio++;
    fin--;
  }
  cout << endl;
}
// Recorre la matriz en espiral desde la esquina superior izquierda hacia el centro.

void recorrerZigZag(int mat[][MAX_N], int n)
{
  for (int i = 0; i < n; i++)
  {
    if (i % 2 == 0)
    {
      for (int j = 0; j < n; j++)
        cout << mat[i][j] << " ";
    }
    else
    {
      for (int j = n - 1; j >= 0; j--)
        cout << mat[i][j] << " ";
    }
  }
  cout << endl;
}
// Recorre la matriz en zigzag, alternando entre izquierda a derecha y derecha a izquierda en cada fila.

void recorrerEnFormaDeZ(int mat[][MAX_N], int n)
{
  for (int i = 0; i < n; i++)
  {
    if (i == 0)
    {
      for (int j = 0; j < n; j++)
        cout << mat[i][j] << " "; // Primera fila
    }
    else if (i == n - 1)
    {
      for (int j = n - 1; j >= 0; j--)
        cout << mat[i][j] << " "; // Última fila
    }
    else
    {
      cout << mat[i][0] << " "; // Primer elemento de la fila
      for (int j = 1; j < n - 1; j++)
        cout << " ";                // Espacios en blanco
      cout << mat[i][n - 1] << " "; // Último elemento de la fila
    }
  }
  cout << endl;
}
// Recorre la matriz en forma de Z, imprimiendo la primera fila, la última fila y los extremos de las filas intermedias.

void recorrerEnFormaDeX(int mat[][MAX_N], int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (j == i || j == n - 1 - i)
        cout << mat[i][j] << " "; // Elementos de la diagonal principal y secundaria
      else
        cout << " "; // Espacios en blanco
    }
    cout << endl;
  }
}
// Recorre la matriz en forma de X, imprimiendo los elementos de las diagonales principal y secundaria.

int main(int argc, char const *argv[])
{
  int matriz[10][10] = {
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
      {11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
      {21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
      {31, 32, 33, 34, 35, 36, 37, 38, 39, 40},
      {41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
      {51, 52, 53, 54, 55, 56, 57, 58, 59, 60},
      {61, 62, 63, 64, 65, 66, 67, 68, 69, 70},
      {71, 72, 73, 74, 75, 76, 77, 78, 79, 80},
      {81, 82, 83, 84, 85, 86, 87, 88, 89, 90},
      {91, 92, 93, 94, 95, 96, 97, 98, 99, 100}};
      recorrerEspiral(matriz, 10);
  return 0;
}
