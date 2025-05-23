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
      cout << "(" << i << "," << j << "): " << " " << M[i][j] << " ";
      // cout << " " << M[i][j] << " ";
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
        // cout << value << endl;
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
  // cout << "estamos en la fila " << row << ", columna " << col << endl;
  // cout << "estamos en: " << "(" << row << "," << col << ")" << endl;

  calls++;
  if (isLimt(row, col, n))
  {
    cout << "isLimt: " << isLimt(row, col, n) << endl;
    cout << "No se puede avanzar a la fila " << row << ", columna " << col << endl;

    // visited[row][col] = false;
    return false;
  }
  if (isExit)
  {
    // encontramos la salida
    return true;
  }
  if (isExitFound(matriz, row, col))
  {
    isExit = true;
    cout << "Salida encontrada en la fila " << row << ", columna " << col << endl;
    return true;
  }
  if (isWall(matriz, row, col))
  {
    cout << "isWall: " << isWall(matriz, row, col) << endl;
    cout << "No se puede avanzar a la fila " << row << ", columna " << col << endl;

    // visited[row][col] = false;
    return false;
  }

  // if (col >= n )
  // {
  //   // no hay salida
  //   return false;
  // }
  // contamos esta llamada
  // for (int i = row; i < n; i++)
  // {
  //   for (int j = col; j < n; j++)
  //   {
  //     // cout << "(" << i << "," << j << "): " << " " << matriz[i][j] << " ";
  //     cout << "(" << i << "," << j << "): " << endl;

  //     // if (!visited[i][j])
  //     // {
  //     // visited[i][j] = true;
  //     steps++;
  //     if (goRowByColumn(matriz, visited, n, i, j, calls, steps, isExit))
  //     {
  //       return true;
  //     }
  //     // visited[i][j] = false;
  //     // }
  //   }
  // }
  if (visited[row][col])
  {
    cout << "visited: " << visited[row][col] << endl;
    cout << "No se puede avanzar a la fila " << row << ", columna " << col << endl;
    return false;
  }
  // if (row != 0 && col != 0)
  // {
    visited[row][col] = true;
  // }
  steps++;

  // Prioridad: filas (derecha), luego columnas (abajo)
  // Derecha
  if (goRowByColumn(matriz, visited, n, row, col + 1, calls, steps, isExit))
  {
    return true;
  }
  // Izquierda
  if (goRowByColumn(matriz, visited, n, row, col - 1, calls, steps, isExit))
  {
    return true;
  }
  // Arriba
  if (goRowByColumn(matriz, visited, n, row - 1, col, calls, steps, isExit))
  {
    return true;
  }
  // Abajo
  if (goRowByColumn(matriz, visited, n, row + 1, col, calls, steps, isExit))
  {
    return true;
  }

  // Si quieres marcar retroceso, puedes descomentar:
  // visited[row][col] = false;
  steps--;
  return false;
  // priorizar moverse en filas
  // if (!isLimt(row + 1, col, n) && !isWall(matriz, row + 1, col) && !visited[row + 1][col])
  // {
  //   if(isExitFound(matriz, row + 1, col))
  //   {
  //     isExit = true;
  //     cout << "Salida encontrada en la fila " << row + 1 << ", columna " << col << endl;
  //     return;
  //   }
  // }
  // if(!isLimt(row + 1, col, n) && !isWall(matriz, row + 1, col) && !visited[row + 1][col])
  // {
  //   visited[row + 1][col] = true;
  //   steps++;
  //   calls++;
  //   cout << "Llamada #" << calls << ": Moverse a la fila " << row + 1 << ", columna " << col << endl;
  //   if (isExit(matriz, row + 1, col))
  //   {
  //     isExit = true;
  //     cout << "Salida encontrada en la fila " << row + 1 << ", columna " << col << endl;
  //     return;
  //   }
  //   goRowByColumn(matriz, visited, n, row + 1, col, calls, steps, isExit);
  // }
  // else if (!isLimt(row, col + 1, n) && !isWall(matriz, row, col + 1) && !visited[row][col + 1])
  // {
  //   visited[row][col + 1] = true;
  //   steps++;
  //   calls++;
  //   cout << "Llamada #" << calls << ": Moverse a la fila " << row << ", columna " << col + 1 << endl;
  //   if (isExit(matriz, row, col + 1))
  //   {
  //     isExit = true;
  //     cout << "Salida encontrada en la fila " << row << ", columna " << col + 1 << endl;
  //     return;
  //   }
  //   goRowByColumn(matriz, visited, n, row, col + 1, calls, steps, isExit);
  // }
}

int main()
{
  char **maze10x10;
  bool **visited10x10;
  int calls = 0, steps = 0;
  bool isExit = false;
  int D10x10 = readMaze("maze5x5.txt", maze10x10);
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
