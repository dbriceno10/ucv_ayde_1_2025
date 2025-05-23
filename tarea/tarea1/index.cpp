#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char wall = '#', trail = '.', exitChar = 'S', entrance = 'E';
int actualRow = 0, actualCol = 0;

bool isLimt(int row, int col, int n)
{
  // return (row >= 0 && row < n && col >= 0 && col < n);
  return (row < 0 || row >= n || col < 0 || col >= n);
}

bool isWall(char **M, int row, int col)
{
  return (M[row][col] == wall);
}

bool isExitFound(char **M, int row, int col)
{
  return (M[row][col] == exitChar);
}

void printMatriz(char **M, int n)
{
  for (int i = 0; i < n; i++)
  {
    cout << "|";
    for (int j = 0; j < n; j++)
    {
      // cout << "(" << i << "," << j << "): " << " " << M[i][j] << " ";
      cout << " " << M[i][j] << " ";
    }
    cout << "|" << endl;
  }
  cout << endl;
}

void printMatrizActual(char **M, int n, int col, int row)
{
  for (int i = 0; i < n; i++)
  {
    cout << "|";
    for (int j = 0; j < n; j++)
    {
      // cout << "(" << i << "," << j << "): " << " " << M[i][j] << " ";
      // cout << " " << M[i][j] << " ";
      if (i == row && j == col)
      {
        cout << "(" << i << "," << j << "): " << " " << M[i][j] << " ";
      }
      else
      {
        cout << " " << M[i][j] << " ";
      }
    }
    cout << "|" << endl;
  }
  cout << endl;
}

void printBoolMatriz(bool **M, int n)
{
  for (int i = 0; i < n; i++)
  {
    cout << "|";
    for (int j = 0; j < n; j++)
    {
      cout << "(" << i << "," << j << "): " << " " << M[i][j] << " ";
      // cout << " " << M[i][j] << " ";
    }
    cout << "|" << endl;
  }
  cout << endl;
}

void initializeMatriz(char **&matriz, int n)
{
  matriz = new char *[n];
  for (int i = 0; i < n; i++)
  {
    matriz[i] = new char[n];
  }
}

void initializeBoolMatriz(bool **&matriz, int n)
{
  matriz = new bool *[n];
  for (int i = 0; i < n; i++)
  {
    matriz[i] = new bool[n];
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      matriz[i][j] = false;
    }
  }
}

void deleteMatriz(char **&matriz, int n)
{
  for (int i = 0; i < n; i++)
  {
    delete[] matriz[i];
  }
  delete[] matriz;
}

void deleteBoolMatriz(bool **&matriz, int n)
{
  for (int i = 0; i < n; i++)
  {
    delete[] matriz[i];
  }
  delete[] matriz;
}

int readMaze(string filename, char **&matriz)
{
  ifstream file;
  file.open(filename, ios::in);
  if (file.is_open())
  {
    int dimention = 0;
    file >> dimention;
    initializeMatriz(matriz, dimention);
    for (int i = 0; i < dimention; i++)
    {
      for (int j = 0; j < dimention; j++)
      {
        char value;
        file >> value;
        matriz[i][j] = value;
      }
    }
    file.close();
    return dimention;
  }
  else
  {
    cout << "Error al abrir el archivo " << filename << endl;
    return -1;
  }
}

// backtracking
bool goRowByColumn(char **&matriz, bool **&visited, int n, int row, int col, int &calls, int &steps, bool &isExit)
{
  printMatrizActual(matriz, n, col, row);
  if (isExit)
  {
    return true;
  }
  calls++;
  if (isExitFound(matriz, row, col))
  {
    isExit = true;
    cout << "Salida encontrada en la fila " << row << ", columna " << col << endl;
    return true;
  }

  visited[row][col] = true;
  steps++;
  // derecha
  if (!isLimt(row, col + 1, n) && !isWall(matriz, row, col + 1) && !visited[row][col + 1])
  {
    if (goRowByColumn(matriz, visited, n, row, col + 1, calls, steps, isExit))
    {
      return true;
    }
  }
  // izquierda
  if (!isLimt(row, col - 1, n) && !isWall(matriz, row, col - 1) && !visited[row][col - 1])
  {
    if (goRowByColumn(matriz, visited, n, row, col - 1, calls, steps, isExit))
    {
      return true;
    }
  }
  // arriba
  if (!isLimt(row + 1, col, n) && !isWall(matriz, row + 1, col) && !visited[row + 1][col])
  {
    if (goRowByColumn(matriz, visited, n, row + 1, col, calls, steps, isExit))
    {
      return true;
    }
  }
  // abajo
  if (!isLimt(row - 1, col, n) && !isWall(matriz, row - 1, col) && !visited[row - 1][col])
  {
    if (goRowByColumn(matriz, visited, n, row - 1, col, calls, steps, isExit))
    {
      return true;
    }
  }
  visited[row][col] = false;
  steps--;
  return false;
}

int main()
{
  char **maze10x10;
  bool **visited10x10;
  int calls = 0, steps = 0;
  bool isExit = false;
  int D10x10 = readMaze("maze50x50.txt", maze10x10);
  if (D10x10 == -1)
  {
    return 0;
  }
  else
  {
    printMatriz(maze10x10, D10x10);
    initializeBoolMatriz(visited10x10, D10x10);
  }
  // printBoolMatriz(visited10x10, D10x10);
  goRowByColumn(maze10x10, visited10x10, D10x10, 0, 0, calls, steps, isExit);
  // deleteMatriz(maze10x10, D10x10);
  // deleteBoolMatriz(visited10x10, D10x10);
  // printBoolMatriz(visited10x10, D10x10);
  cout << "Llamadas: " << calls << endl;
  cout << "Pasos: " << steps << endl;
  return 0;
}
