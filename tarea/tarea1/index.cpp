#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// const int N_10 = 10;

// char laberinto10x10[N_10][N_10] = {
//     {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
//     {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
//     {'#', ' ', '#', '#', '#', '#', '#', ' ', ' ', '#'},
//     {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', '#'},
//     {'#', '#', '#', '#', ' ', '#', '#', ' ', ' ', '#'},
//     {'#', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', '#'},
//     {'#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#'},
//     {'#', ' ', ' ', '#', '#', '#', '#', '#', 'E','#'},
//     {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
//     {'#','#','#','#','#','#','#','#','#','#'}
// };

const char wall = '#', trail = '.', exit = 'S', entrance = 'E';

bool isValid(int row, int col, int n)
{
  return (row >= 0 && row < n && col >= 0 && col < n);
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

// int readMaze(string filename, char **matriz, int n)
// {
//   ifstream file;
//   file.open(filename, ios::in);
//   if (file.is_open())
//   {
//     int dimention = 0;
//     file >> dimention;
//     for (int i = 0; i < dimention; i++)
//     {
//       for (int j = 0; j < dimention; j++)
//       {
//         file >> maze10x10[i][j];
//       }
//     }
//     file.close();
//     return dimention;
//   }
//   else
//   {
//     cout << "Error al abrir el archivo " << filename << endl;
//     return -1;
//   }
// }

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
        cout << value << endl;
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

void goRowByColumn(char **&matriz, bool **&visited, int n, int row, int col, int &calls, int &steps, bool &isExit)
{
  if(isExit)
  {
    //encontramos la salida
    return;
  }
  
}

int main()
{
  char **maze10x10;
  bool **visited10x10;
  int calls = 0, steps = 0;
  bool isExit = false;
  int D10x10 = readMaze("maze10x10.txt", maze10x10);
  if (D10x10 == -1)
  {
    return 0;
  }
  else
  {
    printMatriz(maze10x10, D10x10);
    initializeBoolMatriz(visited10x10, D10x10);
  }
  goRowByColumn(maze10x10, visited10x10, D10x10, 0, 0, calls, steps, isExit);
  deleteMatriz(maze10x10, D10x10);
  deleteBoolMatriz(visited10x10, D10x10);
  return 0;
}
