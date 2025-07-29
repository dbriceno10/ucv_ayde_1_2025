#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class EulerCraft
{
  //* N --> dimension de la matriz, M --> Numero inicial de aristas, T--> tiempo restante para la procesion, P --> tiempo que tarda al construir un puente
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
      // cout << "N " << N << " M " << M << " T " << T << " P " << P << endl;

      adjMatrix = initializeAdj();

      for (int i = 0; i < M; i++)
      {
        int x = 0, y = 0;
        file >> x >> y;
        // cout << "x " << x << " y " << y << endl;
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
    {
      if (matrix[v][i] > 0)
        degree += matrix[i][v];
    }
    return degree;
  }

  int getInDegree(int v, int **matrix)
  {
    int degree = 0;
    for (int i = 0; i < N; ++i)
    {
      if (matrix[i][v] > 0)
        degree += matrix[i][v];
    }
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
      {
        excessOutCount = 2;
        excessInCount = 2;
        break;
      }
    }

    if (excessOutCount == 0 && excessInCount == 0)
    {
      cout << "No es necesario hacer cambios" << endl;
    }
    else if (excessOutCount == 1 && excessInCount == 1)
    {
      if (adjMatrix[verticeWithExcessOut][verticeWithExcessIn] > 0)
      {
        if (P <= T)
        { // It is verified that it is possible to build the bridge (new edge).

          int **tempAdjMatrix = initializeAdj();
          for (int i = 0; i < N; ++i)
          {
            for (int j = 0; j < N; ++j)
            {
              tempAdjMatrix[i][j] = adjMatrix[i][j];
            }
          }

          // Añadir el puente simulado: Esto balanceará los grados de excessOutNode y excessInNode
          tempAdjMatrix[verticeWithExcessOut][verticeWithExcessIn]++;

          // Verificar si con el nuevo puente los grados están balanceados
          // (la conectividad ya está garantizada)
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
          }
          else
          {
            // Este else debería ser raro si la lógica de los dos nodos desbalanceados es correcta
            cout << "Debo presentar mi renuncia" << endl;
          }

          // Liberar la memoria de la matriz temporal
          for (int i = 0; i < N; ++i)
          {
            delete[] tempAdjMatrix[i];
          }
          delete[] tempAdjMatrix;
          deleteAdjMatrix();
        }
        else
        {
          cout << "Debo presentar mi renuncia" << endl; // No hay tiempo para construir el puente
        }
      }
    }
    else // Cualquier otro caso de desequilibrio de grados
    {
      cout << "Debo presentar mi renuncia" << endl; // No se puede reparar con un solo puente
    }
  }
};

int main()
{
  EulerCraft euler;
  euler.print();
  euler.evaluate();
  return 0;
}