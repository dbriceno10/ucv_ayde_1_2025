#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

const char wall = '#', trail = '.', exitChar = 'S';

bool isLimt(int row, int col, int n)
{
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

// printMatrizActual si se usa permite ver el recorrido, indica la posición actual i j del recorrido
void printMatrizActual(char **M, int n, int col, int row)
{
  for (int i = 0; i < n; i++)
  {
    cout << "|";
    for (int j = 0; j < n; j++)
    {
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
  // printMatrizActual(matriz, n, col, row);
  if (isExit)
  {
    return true;
  }
  calls++;
  if (isExitFound(matriz, row, col))
  {
    isExit = true;
    // cout << "Salida encontrada en la fila " << row << ", columna " << col << endl;
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

bool goColumnByRow(char **&matriz, bool **&visited, int n, int row, int col, int &calls, int &steps, bool &isExit)
{
  // printMatrizActual(matriz, n, col, row);
  if (isExit)
  {
    return true;
  }
  calls++;
  if (isExitFound(matriz, row, col))
  {
    isExit = true;
    // cout << "Salida encontrada en la fila " << row << ", columna " << col << endl;
    return true;
  }

  visited[row][col] = true;
  steps++;
  // arriba
  if (!isLimt(row + 1, col, n) && !isWall(matriz, row + 1, col) && !visited[row + 1][col])
  {
    if (goColumnByRow(matriz, visited, n, row + 1, col, calls, steps, isExit))
    {
      return true;
    }
  }
  // abajo
  if (!isLimt(row - 1, col, n) && !isWall(matriz, row - 1, col) && !visited[row - 1][col])
  {
    if (goColumnByRow(matriz, visited, n, row - 1, col, calls, steps, isExit))
    {
      return true;
    }
  }
  // derecha
  if (!isLimt(row, col + 1, n) && !isWall(matriz, row, col + 1) && !visited[row][col + 1])
  {
    if (goColumnByRow(matriz, visited, n, row, col + 1, calls, steps, isExit))
    {
      return true;
    }
  }
  // izquierda
  if (!isLimt(row, col - 1, n) && !isWall(matriz, row, col - 1) && !visited[row][col - 1])
  {
    if (goColumnByRow(matriz, visited, n, row, col - 1, calls, steps, isExit))
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
  const int K10 = 10;
  const int K100 = 100;
  char **maze;
  bool **visited;
  int callsFxC = 0, stepsFxC = 0, callsCxF = 0, stepsCxF = 0;
  bool isExit = false;
  int dimention = readMaze("maze10x10.txt", maze);
  if (dimention == -1)
  {
    return 0;
  }
  else
  {
    cout << "Laberinto 10x10" << endl;
    printMatriz(maze, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  cout << "Recorrido FilasxColumnas 1 vez" << endl;
  auto startFxC = high_resolution_clock::now();
  goRowByColumn(maze, visited, dimention, 0, 0, callsFxC, stepsFxC, isExit);
  auto stopFxC = high_resolution_clock::now();
  duration<float, milli> durationFxC = stopFxC - startFxC;
  double timeFxC = durationFxC.count();
  cout << "Tiempo de ejecución: " << timeFxC << " ms" << endl;
  cout << "Llamadas: " << callsFxC << endl;
  cout << "Pasos: " << stepsFxC << endl;
  deleteBoolMatriz(visited, dimention);
  initializeBoolMatriz(visited, dimention);
  isExit = false;
  auto startCxF = high_resolution_clock::now();
  cout << "Recorrido ColumnasxFilas 1 vez" << endl;
  goColumnByRow(maze, visited, dimention, 0, 0, callsCxF, stepsCxF, isExit);
  auto stopCxF = high_resolution_clock::now();
  duration<float, milli> durationCxF = stopCxF - startCxF;
  double timeCxF = durationCxF.count();
  cout << "Tiempo de ejecución: " << timeCxF << " ms" << endl;
  cout << "Llamadas: " << callsCxF << endl;
  cout << "Pasos: " << stepsCxF << endl;
  deleteBoolMatriz(visited, dimention);
  cout << "Laberinto 10x10 ejecutado 1 vez" << endl;
  cout << "Recorrido FilasxColumnas vs Recorrido ColumnasxFilas" << endl;
  cout << "Llamadas: " << callsFxC << " vs " << callsCxF << endl;
  cout << "Pasos: " << stepsFxC << " vs " << stepsCxF << endl;
  cout << "Tiempo: " << timeFxC << " ms vs " << timeCxF << " ms" << endl;
  isExit = false;
  callsFxC = 0, stepsFxC = 0;
  callsCxF = 0, stepsCxF = 0;
  initializeBoolMatriz(visited, dimention);
  // metodo FxC matriz 10x10 ejecutado 10 veces
  cout << "Laberinto 10x10 ejecutado 10 veces" << endl;
  startFxC = high_resolution_clock::now();
  for (int i = 0; i < K10; i++)
  {
    goRowByColumn(maze, visited, dimention, 0, 0, callsFxC, stepsFxC, isExit);
    isExit = false;
    deleteBoolMatriz(visited, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  stopFxC = high_resolution_clock::now();
  durationFxC = stopFxC - startFxC;
  timeFxC = durationFxC.count();
  cout << "Llamadas: " << callsFxC << endl;
  cout << "Pasos: " << stepsFxC << endl;
  cout << "Tiempo de ejecución: " << timeFxC << " ms" << endl;
  deleteBoolMatriz(visited, dimention);
  initializeBoolMatriz(visited, dimention);
  // metodo CxF matriz 10x10 ejecutado 10 veces
  isExit = false;
  startCxF = high_resolution_clock::now();
  cout << "Recorrido ColumnasxFilas 10 veces" << endl;
  for (int i = 0; i < K10; i++)
  {
    goColumnByRow(maze, visited, dimention, 0, 0, callsCxF, stepsCxF, isExit);
    isExit = false;
    deleteBoolMatriz(visited, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  stopCxF = high_resolution_clock::now();
  durationCxF = stopCxF - startCxF;
  timeCxF = durationCxF.count();
  cout << "Llamadas: " << callsCxF << endl;
  cout << "Pasos: " << stepsCxF << endl;
  cout << "Tiempo de ejecución: " << timeCxF << " ms" << endl;
  deleteBoolMatriz(visited, dimention);
  cout << "Laberinto 10x10 ejecutado 10 veces" << endl;
  cout << "Recorrido FilasxColumnas vs Recorrido ColumnasxFilas" << endl;
  cout << "Llamadas: " << callsFxC << " vs " << callsCxF << endl;
  cout << "Pasos: " << stepsFxC << " vs " << stepsCxF << endl;
  cout << "Tiempo: " << timeFxC << " ms vs " << timeCxF << " ms" << endl;
  isExit = false;
  callsFxC = 0, stepsFxC = 0;
  callsCxF = 0, stepsCxF = 0;
  initializeBoolMatriz(visited, dimention);
  // metodo FxC matriz 10x10 ejecutado 100 veces
  cout << "Laberinto 10x10 ejecutado 100 veces" << endl;
  startFxC = high_resolution_clock::now();
  for (int i = 0; i < K100; i++)
  {
    goRowByColumn(maze, visited, dimention, 0, 0, callsFxC, stepsFxC, isExit);
    isExit = false;
    deleteBoolMatriz(visited, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  stopFxC = high_resolution_clock::now();
  durationFxC = stopFxC - startFxC;
  timeFxC = durationFxC.count();
  cout << "Llamadas: " << callsFxC << endl;
  cout << "Pasos: " << stepsFxC << endl;
  cout << "Tiempo de ejecución: " << timeFxC << " ms" << endl;
  deleteBoolMatriz(visited, dimention);
  initializeBoolMatriz(visited, dimention);
  // metodo CxF matriz 10x10 ejecutado 100 veces
  isExit = false;
  startCxF = high_resolution_clock::now();
  cout << "Recorrido ColumnasxFilas 100 veces" << endl;
  for (int i = 0; i < K100; i++)
  {
    goColumnByRow(maze, visited, dimention, 0, 0, callsCxF, stepsCxF, isExit);
    isExit = false;
    deleteBoolMatriz(visited, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  stopCxF = high_resolution_clock::now();
  durationCxF = stopCxF - startCxF;
  timeCxF = durationCxF.count();
  cout << "Llamadas: " << callsCxF << endl;
  cout << "Pasos: " << stepsCxF << endl;
  cout << "Tiempo de ejecución: " << timeCxF << " ms" << endl;
  deleteBoolMatriz(visited, dimention);
  cout << "Laberinto 10x10 ejecutado 100 veces" << endl;
  cout << "Recorrido FilasxColumnas vs Recorrido ColumnasxFilas" << endl;
  cout << "Llamadas: " << callsFxC << " vs " << callsCxF << endl;
  cout << "Pasos: " << stepsFxC << " vs " << stepsCxF << endl;
  cout << "Tiempo: " << timeFxC << " ms vs " << timeCxF << " ms" << endl;
  isExit = false;
  callsFxC = 0, stepsFxC = 0;
  callsCxF = 0, stepsCxF = 0;
  deleteMatriz(maze, dimention);
  // matriz 20x20
  cout << "Laberinto 20x20" << endl;
  dimention = readMaze("maze20x20.txt", maze);
  if (dimention == -1)
  {
    return 0;
  }
  else
  {
    printMatriz(maze, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  cout << "Recorrido FilasxColumnas 1 vez" << endl;
  startFxC = high_resolution_clock::now();
  goRowByColumn(maze, visited, dimention, 0, 0, callsFxC, stepsFxC, isExit);
  stopFxC = high_resolution_clock::now();
  durationFxC = stopFxC - startFxC;
  timeFxC = durationFxC.count();
  cout << "Tiempo de ejecución: " << timeFxC << " ms" << endl;
  cout << "Llamadas: " << callsFxC << endl;
  cout << "Pasos: " << stepsFxC << endl;
  deleteBoolMatriz(visited, dimention);
  initializeBoolMatriz(visited, dimention);
  isExit = false;
  startCxF = high_resolution_clock::now();
  cout << "Recorrido ColumnasxFilas 1 vez" << endl;
  goColumnByRow(maze, visited, dimention, 0, 0, callsCxF, stepsCxF, isExit);
  stopCxF = high_resolution_clock::now();
  durationCxF = stopCxF - startCxF;
  timeCxF = durationCxF.count();
  cout << "Tiempo de ejecución: " << timeCxF << " ms" << endl;
  cout << "Llamadas: " << callsCxF << endl;
  cout << "Pasos: " << stepsCxF << endl;
  deleteBoolMatriz(visited, dimention);
  cout << "Laberinto 20x20 ejecutado 1 vez" << endl;
  cout << "Recorrido FilasxColumnas vs Recorrido ColumnasxFilas" << endl;
  cout << "Llamadas: " << callsFxC << " vs " << callsCxF << endl;
  cout << "Pasos: " << stepsFxC << " vs " << stepsCxF << endl;
  cout << "Tiempo: " << timeFxC << " ms vs " << timeCxF << " ms" << endl;
  isExit = false;
  callsFxC = 0, stepsFxC = 0;
  callsCxF = 0, stepsCxF = 0;
  initializeBoolMatriz(visited, dimention);
  // metodo FxC matriz 20x20 ejecutado 10 veces
  cout << "Laberinto 20x20 ejecutado 10 veces" << endl;
  startFxC = high_resolution_clock::now();
  for (int i = 0; i < K10; i++)
  {
    goRowByColumn(maze, visited, dimention, 0, 0, callsFxC, stepsFxC, isExit);
    isExit = false;
    deleteBoolMatriz(visited, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  stopFxC = high_resolution_clock::now();
  durationFxC = stopFxC - startFxC;
  timeFxC = durationFxC.count();
  cout << "Llamadas: " << callsFxC << endl;
  cout << "Pasos: " << stepsFxC << endl;
  cout << "Tiempo de ejecución: " << timeFxC << " ms" << endl;
  deleteBoolMatriz(visited, dimention);
  initializeBoolMatriz(visited, dimention);
  // metodo CxF matriz 20x20 ejecutado 10 veces
  isExit = false;
  startCxF = high_resolution_clock::now();
  cout << "Recorrido ColumnasxFilas 10 veces" << endl;
  for (int i = 0; i < K10; i++)
  {
    goColumnByRow(maze, visited, dimention, 0, 0, callsCxF, stepsCxF, isExit);
    isExit = false;
    deleteBoolMatriz(visited, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  stopCxF = high_resolution_clock::now();
  durationCxF = stopCxF - startCxF;
  timeCxF = durationCxF.count();
  cout << "Llamadas: " << callsCxF << endl;
  cout << "Pasos: " << stepsCxF << endl;
  cout << "Tiempo de ejecución: " << timeCxF << " ms" << endl;
  deleteBoolMatriz(visited, dimention);
  cout << "Laberinto 20x20 ejecutado 10 veces" << endl;
  cout << "Recorrido FilasxColumnas vs Recorrido ColumnasxFilas" << endl;
  cout << "Llamadas: " << callsFxC << " vs " << callsCxF << endl;
  cout << "Pasos: " << stepsFxC << " vs " << stepsCxF << endl;
  cout << "Tiempo: " << timeFxC << " ms vs " << timeCxF << " ms" << endl;
  isExit = false;
  callsFxC = 0, stepsFxC = 0;
  callsCxF = 0, stepsCxF = 0;
  initializeBoolMatriz(visited, dimention);
  // metodo FxC matriz 20x20 ejecutado 100 veces
  cout << "Laberinto 20x20 ejecutado 100 veces" << endl;
  startFxC = high_resolution_clock::now();
  for (int i = 0; i < K100; i++)
  {
    goRowByColumn(maze, visited, dimention, 0, 0, callsFxC, stepsFxC, isExit);
    isExit = false;
    deleteBoolMatriz(visited, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  stopFxC = high_resolution_clock::now();
  durationFxC = stopFxC - startFxC;
  timeFxC = durationFxC.count();
  cout << "Llamadas: " << callsFxC << endl;
  cout << "Pasos: " << stepsFxC << endl;
  cout << "Tiempo de ejecución: " << timeFxC << " ms" << endl;
  deleteBoolMatriz(visited, dimention);
  initializeBoolMatriz(visited, dimention);
  // metodo CxF matriz 20x20 ejecutado 100 veces
  isExit = false;
  startCxF = high_resolution_clock::now();
  cout << "Recorrido ColumnasxFilas 100 veces" << endl;
  for (int i = 0; i < K100; i++)
  {
    goColumnByRow(maze, visited, dimention, 0, 0, callsCxF, stepsCxF, isExit);
    isExit = false;
    deleteBoolMatriz(visited, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  stopCxF = high_resolution_clock::now();
  durationCxF = stopCxF - startCxF;
  timeCxF = durationCxF.count();
  cout << "Llamadas: " << callsCxF << endl;
  cout << "Pasos: " << stepsCxF << endl;
  cout << "Tiempo de ejecución: " << timeCxF << " ms" << endl;
  deleteBoolMatriz(visited, dimention);
  cout << "Laberinto 20x20 ejecutado 100 veces" << endl;
  cout << "Recorrido FilasxColumnas vs Recorrido ColumnasxFilas" << endl;
  cout << "Llamadas: " << callsFxC << " vs " << callsCxF << endl;
  cout << "Pasos: " << stepsFxC << " vs " << stepsCxF << endl;
  cout << "Tiempo: " << timeFxC << " ms vs " << timeCxF << " ms" << endl;
  isExit = false;
  callsFxC = 0, stepsFxC = 0;
  callsCxF = 0, stepsCxF = 0;
  deleteMatriz(maze, dimention);

  // matriz 50x50
  cout << "Laberinto 50x50" << endl;
  dimention = readMaze("maze50x50.txt", maze);
  if (dimention == -1)
  {
    return 0;
  }
  else
  {
    printMatriz(maze, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  cout << "Recorrido FilasxColumnas 1 vez" << endl;
  startFxC = high_resolution_clock::now();
  goRowByColumn(maze, visited, dimention, 0, 0, callsFxC, stepsFxC, isExit);
  stopFxC = high_resolution_clock::now();
  durationFxC = stopFxC - startFxC;
  timeFxC = durationFxC.count();
  cout << "Tiempo de ejecución: " << timeFxC << " ms" << endl;
  cout << "Llamadas: " << callsFxC << endl;
  cout << "Pasos: " << stepsFxC << endl;
  deleteBoolMatriz(visited, dimention);
  initializeBoolMatriz(visited, dimention);
  isExit = false;
  startCxF = high_resolution_clock::now();
  cout << "Recorrido ColumnasxFilas 1 vez" << endl;
  goColumnByRow(maze, visited, dimention, 0, 0, callsCxF, stepsCxF, isExit);
  stopCxF = high_resolution_clock::now();
  durationCxF = stopCxF - startCxF;
  timeCxF = durationCxF.count();
  cout << "Tiempo de ejecución: " << timeCxF << " ms" << endl;
  cout << "Llamadas: " << callsCxF << endl;
  cout << "Pasos: " << stepsCxF << endl;
  deleteBoolMatriz(visited, dimention);
  cout << "Laberinto 50x50 ejecutado 1 vez" << endl;
  cout << "Recorrido FilasxColumnas vs Recorrido ColumnasxFilas" << endl;
  cout << "Llamadas: " << callsFxC << " vs " << callsCxF << endl;
  cout << "Pasos: " << stepsFxC << " vs " << stepsCxF << endl;
  cout << "Tiempo: " << timeFxC << " ms vs " << timeCxF << " ms" << endl;
  isExit = false;
  callsFxC = 0, stepsFxC = 0;
  callsCxF = 0, stepsCxF = 0;
  initializeBoolMatriz(visited, dimention);
  // metodo FxC matriz 50x50 ejecutado 10 veces
  cout << "Laberinto 50x50 ejecutado 10 veces" << endl;
  startFxC = high_resolution_clock::now();
  for (int i = 0; i < K10; i++)
  {
    goRowByColumn(maze, visited, dimention, 0, 0, callsFxC, stepsFxC, isExit);
    isExit = false;
    deleteBoolMatriz(visited, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  stopFxC = high_resolution_clock::now();
  durationFxC = stopFxC - startFxC;
  timeFxC = durationFxC.count();
  cout << "Llamadas: " << callsFxC << endl;
  cout << "Pasos: " << stepsFxC << endl;
  cout << "Tiempo de ejecución: " << timeFxC << " ms" << endl;
  deleteBoolMatriz(visited, dimention);
  initializeBoolMatriz(visited, dimention);
  // metodo CxF matriz 50x50 ejecutado 10 veces
  isExit = false;
  startCxF = high_resolution_clock::now();
  cout << "Recorrido ColumnasxFilas 10 veces" << endl;
  for (int i = 0; i < K10; i++)
  {
    goColumnByRow(maze, visited, dimention, 0, 0, callsCxF, stepsCxF, isExit);
    isExit = false;
    deleteBoolMatriz(visited, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  stopCxF = high_resolution_clock::now();
  durationCxF = stopCxF - startCxF;
  timeCxF = durationCxF.count();
  cout << "Llamadas: " << callsCxF << endl;
  cout << "Pasos: " << stepsCxF << endl;
  cout << "Tiempo de ejecución: " << timeCxF << " ms" << endl;
  deleteBoolMatriz(visited, dimention);
  cout << "Laberinto 50x50 ejecutado 10 veces" << endl;
  cout << "Recorrido FilasxColumnas vs Recorrido ColumnasxFilas" << endl;
  cout << "Llamadas: " << callsFxC << " vs " << callsCxF << endl;
  cout << "Pasos: " << stepsFxC << " vs " << stepsCxF << endl;
  cout << "Tiempo: " << timeFxC << " ms vs " << timeCxF << " ms" << endl;
  isExit = false;
  callsFxC = 0, stepsFxC = 0;
  callsCxF = 0, stepsCxF = 0;
  initializeBoolMatriz(visited, dimention);
  // metodo FxC matriz 50x50 ejecutado 100 veces
  cout << "Laberinto 50x50 ejecutado 100 veces" << endl;
  startFxC = high_resolution_clock::now();
  for (int i = 0; i < K100; i++)
  {
    goRowByColumn(maze, visited, dimention, 0, 0, callsFxC, stepsFxC, isExit);
    isExit = false;
    deleteBoolMatriz(visited, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  stopFxC = high_resolution_clock::now();
  durationFxC = stopFxC - startFxC;
  timeFxC = durationFxC.count();
  cout << "Llamadas: " << callsFxC << endl;
  cout << "Pasos: " << stepsFxC << endl;
  cout << "Tiempo de ejecución: " << timeFxC << " ms" << endl;
  deleteBoolMatriz(visited, dimention);
  initializeBoolMatriz(visited, dimention);
  // metodo CxF matriz 50x50 ejecutado 100 veces
  isExit = false;
  startCxF = high_resolution_clock::now();
  cout << "Recorrido ColumnasxFilas 100 veces" << endl;
  for (int i = 0; i < K100; i++)
  {
    goColumnByRow(maze, visited, dimention, 0, 0, callsCxF, stepsCxF, isExit);
    isExit = false;
    deleteBoolMatriz(visited, dimention);
    initializeBoolMatriz(visited, dimention);
  }
  stopCxF = high_resolution_clock::now();
  durationCxF = stopCxF - startCxF;
  timeCxF = durationCxF.count();
  cout << "Llamadas: " << callsCxF << endl;
  cout << "Pasos: " << stepsCxF << endl;
  cout << "Tiempo de ejecución: " << timeCxF << " ms" << endl;
  deleteBoolMatriz(visited, dimention);
  cout << "Laberinto 50x50 ejecutado 100 veces" << endl;
  cout << "Recorrido FilasxColumnas vs Recorrido ColumnasxFilas" << endl;
  cout << "Llamadas: " << callsFxC << " vs " << callsCxF << endl;
  cout << "Pasos: " << stepsFxC << " vs " << stepsCxF << endl;
  cout << "Tiempo: " << timeFxC << " ms vs " << timeCxF << " ms" << endl;
  isExit = false;
  callsFxC = 0, stepsFxC = 0;
  callsCxF = 0, stepsCxF = 0;
  deleteMatriz(maze, dimention);
  return 0;
}
