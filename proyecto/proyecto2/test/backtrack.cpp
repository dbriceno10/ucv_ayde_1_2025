#include <iostream>
using namespace std;

const int N = 3; // Tamaño de la matriz
bool matrix[N][N];

void printMatrix()
{
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
      cout << matrix[i][j] << " ";
    cout << endl;
  }
  cout << "------" << endl;
}

void backtrack(int i, int j)
{
  if (i == N)
  {
    printMatrix();
    return;
  }
  int nextI = i, nextJ = j + 1;
  if (nextJ == N)
  {
    nextI++;
    nextJ = 0;
  }

  // Opción 1: no marcar la casilla
  backtrack(nextI, nextJ);

  // Opción 2: marcar la casilla si no está marcada
  if (!matrix[i][j])
  {
    matrix[i][j] = true;
    backtrack(nextI, nextJ);
    matrix[i][j] = false; // desmarcar (backtrack)
  }
}

int main()
{
  // Inicializar matriz en falso
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      matrix[i][j] = false;

  backtrack(0, 0);
  return 0;
}