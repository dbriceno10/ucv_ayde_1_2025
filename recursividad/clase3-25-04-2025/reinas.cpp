#include <iostream>

using namespace std;

const int MAX_N = 20;

bool esSeguro(int tablero[MAX_N][MAX_N], int fila, int col, int N)
{

  // horizontal
  for (int i = 0; i < col; ++i)
  {
    if (tablero[fila][i])
    {
      return false;
    }
  }

  // vertical
  for (int i = 0; i < N; ++i)
  {
    if (tablero[i][col])
    {
      return false;
    }
  }
  // Diagonal
  for (int i = fila, j = col; i >= 0 && j >= 0; --i, --j)
  {
    if (tablero[i][j])
    {
      return false;
    }
  }
  // Diagonal Invertida
  for (int i = fila, j = col; i < N && j >= 0; ++i, --j)
  {
    if (tablero[i][j])
    {
      return false;
    }
  }

  return true;
}

bool resolverNReinas(int tablero[MAX_N][MAX_N], int col, int N)
{
  if (col >= N)
  {
    return true;
  }

  for (int i = 0; i < N; i++)
  {
    if (esSeguro(tablero, i, col, N))
    {
      tablero[i][col] = 1; // 0,0,

      if (resolverNReinas(tablero, col + 1, N))
      {
        return true;
      }

      tablero[i][col] = 0;
    }
  }

  return false;
}

void imprimirTablero(int tablero[MAX_N][MAX_N], int N)
{
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      cout << (tablero[i][j] ? " Q " : " . ");
    }
    cout << endl;
  }
}

int main()
{
  int N = 0;
  int tablero[MAX_N][MAX_N] = {0};

  cout << "inegrese el numero de reinas: N <=" << MAX_N << endl;
  cin >> N;
  if (N > MAX_N)
  {
    cout << "N es demasiado grande" << endl;
    return 1;
  }

  if (resolverNReinas(tablero, 0, N))
  {
    cout << "Solucion encontrada" << endl;
    imprimirTablero(tablero, N);
  }
  else
  {
    cout << "Solucion no encontrada" << endl;
  }

  return 0;
}