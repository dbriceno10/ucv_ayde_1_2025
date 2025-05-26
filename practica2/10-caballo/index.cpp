#include <iostream>
using namespace std;

const int N = 8;
int tablero[N][N];

// Movimientos posibles del caballo
int movX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int movY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

void imprimirTablero()
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
      cout << tablero[i][j] << "\t";
    cout << endl;
  }
  cout << endl;
}

bool esValido(int x, int y)
{
  return (x >= 0 && x < N && y >= 0 && y < N && tablero[x][y] == 0);
}

bool recorridoCaballo(int x, int y, int mov)
{
  tablero[x][y] = mov;
  if (mov == N * N)
  {
    imprimirTablero();
    return true; // Si quieres solo una solución, retorna aquí
  }
  for (int i = 0; i < 8; i++)
  {
    int nx = x + movX[i];
    int ny = y + movY[i];
    if (esValido(nx, ny))
    {
      if (recorridoCaballo(nx, ny, mov + 1))
        return true; // Si quieres solo una solución, retorna aquí
    }
  }
  tablero[x][y] = 0; // backtrack
  return false;
}

int main()
{
  // Inicializar tablero
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      tablero[i][j] = 0;

  // Comenzar desde la esquina superior derecha (0,7)
  if (!recorridoCaballo(0, 7, 1))
    cout << "No existe recorrido completo desde la esquina superior derecha." << endl;
  return 0;
}