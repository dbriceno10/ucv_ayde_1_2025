#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class EulerCraft
{
  //* N --> dimension de la matriz, M --> Numero inicial de aristas, T--> tiempo restante para la procesion, P --> tiempo que tarda al construir un puente
  int N = 0, M = 0, T = 0, P = 0;
  bool **adjMatrix;

  void initializeAdj()
  {
    adjMatrix = new bool *[N];
    for (int i = 0; i < N; i++)
    {
      adjMatrix[i] = new bool[N];
    }
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        adjMatrix[i][j] = false;
      }
    }
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
      initializeAdj();
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

  void linkBridges(const int &x, const int &y)
  {
    adjMatrix[x - 1][y - 1] = 1;
    adjMatrix[y - 1][x - 1] = 1;
  }

  void printAdj(bool **adjMatrix)
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

  void dfs(int u, bool *visited)
  {
    visited[u] = true;
    cout << "Visitando nodo " << "(" << u + 1 << ")" << endl;

    for (int v = 0; v < N; v++)
    {
      if (adjMatrix[u][v] && !visited[v])
      {
        dfs(v, visited);
      }
    }
  }

  void traverseGraph()
  {
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
    {
      visited[i] = false;
    }

    cout << "Iniciando recorrido del grafo completo desde nodo 1:" << endl;
    dfs(0, visited);

    delete[] visited;
  }

public:
  EulerCraft()
  {
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

  void traverse()
  {
    traverseGraph();
  }
};

int main(int argc, char const *argv[])
{
  EulerCraft euler;
  euler.print();
  euler.traverse();
  return 0;
}
