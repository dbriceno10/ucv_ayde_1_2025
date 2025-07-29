#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class EulerCraft
{
  int N = 0, M = 0, T = 0, P = 0;
  int **adjMatrix;

  int **initializeAdj()
  {
    int **matrix = new int *[N];
    for (int i = 0; i < N; i++)
    {
      matrix[i] = new int[N];
      for (int j = 0; j < N; j++)
      {
        matrix[i][j] = 0;
      }
    }
    return matrix;
  }

  void deleteAdjMatrix()
  {
    for (int i = 0; i < N; i++)
    {
      delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
  }

  void readFile(string filename)
  {
    ifstream file;
    file.open(filename, ios::in);
    if (file.is_open())
    {
      file >> N >> M;
      file >> T;
      file >> P;

      adjMatrix = initializeAdj();

      for (int i = 0; i < M; i++)
      {
        int x = 0, y = 0;
        file >> x >> y;
        linkBridges(x, y);
      }
      file.close();
    }
    else
    {
      cout << "No se pudo abrir el archivo " << filename << endl;
    }
  }

  void openFile()
  {
    int index = 0;
    cout << "Numero del archivo" << endl;
    cin >> index;
    readFile("Entrada" + to_string(index) + ".txt");
  }

  void linkBridges(const int &u, const int &v)
  {
    adjMatrix[u - 1][v - 1]++;
  }

  void printAdj(int **adjMatrix)
  {
    cout << "-------------------------\n";
    cout << endl;
    cout << "   ";
    for (int i = 0; i < N; i++)
    {
      cout << i + 1 << "  ";
    }
    cout << endl;
    for (int i = 0; i < N; i++)
    {
      cout << i + 1;
      for (int j = 0; j < N; j++)
      {
        cout << "  " << adjMatrix[i][j];
      }
      cout << "\n";
    }
    cout << "-------------------------\n";
  }

  int getOutDegree(int v, int **matrix)
  {
    int degree = 0;
    for (int i = 0; i < N; ++i)
      degree += matrix[v][i];

    return degree;
  }

  int getInDegree(int v, int **matrix)
  {
    int degree = 0;
    for (int i = 0; i < N; ++i)
      degree += matrix[i][v];

    return degree;
  }

public:
  EulerCraft()
  {
    adjMatrix = nullptr;
    openFile();
  }

  ~EulerCraft()
  {
    deleteAdjMatrix();
    N = 0;
    M = 0;
    T = 0;
    P = 0;
  }

  void print()
  {
    printAdj(adjMatrix);
  }

  void evaluate()
  {
    int excessOutCount = 0;
    int excessInCount = 0;
    int verticeWithExcessOut = -1;
    int verticeWithExcessIn = -1;

    // we verify if the Eulerian path is possible with the construction of a bridge (new edge).
    for (int i = 0; i < N; i++)
    {
      int outDeg = getOutDegree(i, adjMatrix);
      int inDeg = getInDegree(i, adjMatrix);

      if (outDeg == inDeg + 1)
      {
        excessOutCount++;
        verticeWithExcessOut = i;
      }
      else if (inDeg == outDeg + 1)
      {
        excessInCount++;
        verticeWithExcessIn = i;
      }
      else if (outDeg != inDeg)
      { // if the imbalance between the two nodes is greater than one, the bridge will not make the path possible.
        excessOutCount = 2;
        excessInCount = 2;
        break;
      }
    }

    if (excessOutCount == 0 && excessInCount == 0)
    { // all vertices are balanced, the path is possible by definition.
      cout << "No es necesario hacer cambios" << endl;
      return;
    }
    else if (excessOutCount == 1 && excessInCount == 1)
    {
      // checks if the vertices were updated correctly, and if an edge already existed between them.
      if ((verticeWithExcessIn != -1 && verticeWithExcessOut != -1) &&
          (adjMatrix[verticeWithExcessIn][verticeWithExcessOut] > 0 || adjMatrix[verticeWithExcessOut][verticeWithExcessIn] > 0))
      {

        if (P <= T)
        { // it is verified that it is possible to build the bridge (new edge).

          // we make a copy of the adjacency matrix to verify if the change makes the Eulerian path possible.
          int **tempAdjMatrix = initializeAdj();
          for (int i = 0; i < N; ++i)
          {
            for (int j = 0; j < N; ++j)
              tempAdjMatrix[i][j] = adjMatrix[i][j];
          }

          // we add the extra edge (the bridge).
          tempAdjMatrix[verticeWithExcessIn][verticeWithExcessOut]++;

          bool allDegreesBalanced = true;
          for (int i = 0; i < N; ++i)
          {
            if (getOutDegree(i, tempAdjMatrix) != getInDegree(i, tempAdjMatrix))
            {
              allDegreesBalanced = false;
              break;
            }
          }

          if (allDegreesBalanced)
          {
            cout << "Es posible modificar la ciudad" << endl;
            return;
          }
          else
          {
            cout << "Debo presentar mi renuncia" << endl;
            return;
          }

          for (int i = 0; i < N; ++i)
          {
            delete[] tempAdjMatrix[i];
          }
          delete[] tempAdjMatrix;
        }
      }
    }
    cout << "Debo presentar mi renuncia" << endl; // if the path is not possible in any way.
  }
};

int main()
{
  EulerCraft euler;
  euler.print();
  euler.evaluate();
  return 0;
}