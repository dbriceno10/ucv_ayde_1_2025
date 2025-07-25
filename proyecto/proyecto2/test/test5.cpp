#include <iostream>
#include <string>

using namespace std;

char const H = 'H', E = 'E', M = 'M', C = 'C';

class DNA
{
  // private:
  struct Node
  {
    char type;
    int maxLinks;
    int actualLinks;
    Node()
    {
      actualLinks = 0;
      type = '\0';
      maxLinks = 0;
    }
    Node(char t) : actualLinks(0)
    {
      type = t;
      if (t == H)
        maxLinks = 1;
      else if (t == E)
        maxLinks = 4;
      else if (t == M)
        maxLinks = 2;
      else if (t == C)
        maxLinks = 2;
    }
  };

  int nNodes;
  Node *nodes;
  bool **adjMatrix;
  int **indexMatrix;
  string dna;
  int globalMaxLinks = 0;
  int solutions = 0;

  void initializeAdjMatriz()
  {
    // agregamos inicializacion de matriz de indices
    adjMatrix = new bool *[nNodes];
    indexMatrix = new int *[nNodes];
    for (int i = 0; i < nNodes; i++)
    {
      adjMatrix[i] = new bool[nNodes];
      indexMatrix[i] = new int[nNodes];
    }
    for (int i = 0; i < nNodes; i++)
    {
      for (int j = 0; j < nNodes; j++)
      {
        adjMatrix[i][j] = false;
        indexMatrix[i][j] = -1;
      }
    }
  }

  void initializeNodes()
  {
    nodes = new Node[nNodes];
    for (int i = 0; i < nNodes; i++)
    {
      if (dna[i] == H)
      {
        nodes[i].maxLinks = 1;
        nodes[i].type = H;
        nodes[i].actualLinks = 0;
      }
      if (dna[i] == E)
      {
        nodes[i].maxLinks = 4;
        nodes[i].type = E;
        nodes[i].actualLinks = 0;
      }
      if (dna[i] == M)
      {
        nodes[i].maxLinks = 2;
        nodes[i].type = M;
        nodes[i].actualLinks = 0;
      }
      if (dna[i] == C)
      {
        nodes[i].maxLinks = 2;
        nodes[i].type = C;
        nodes[i].actualLinks = 0;
      }
    }
  }

  bool canLink(const int &i, const int &j)
  {
    if (i == j)
      return false; // un nodo no se puede enlazar consigo mismo

    if ((nodes[i].actualLinks < nodes[i].maxLinks) && (nodes[j].actualLinks < nodes[j].maxLinks))
      return true;

    return false;
  }

  bool canLinkLegacy(const int &i, const int &j)
  {
    if (i == j)
      return false; // un nodo no se puede enlazar consigo mismo

    // Contar enlaces actuales del nodo i y j
    int countI = 0, countJ = 0;
    for (int k = 0; k < nNodes; k++)
    {
      if (adjMatrix[i][k])
      {
        // cout << "ik " << k << endl;
        countI++;
      }
      if (adjMatrix[j][k])
      {
        // cout << "jk " << k << endl;
        countJ++;
      }
    }

    // // Obtener tipos de nodos
    // char A = nodes[i].type;
    // char B = nodes[j].type;

    if (countI < nodes[i].maxLinks && countJ < nodes[j].maxLinks)
      return true;

    return false;
  }

  void deleteNodes()
  {
    delete[] nodes;
  }

  void deleteAdjMatrix()
  {
    for (int i = 0; i < nNodes; i++)
    {
      delete[] adjMatrix[i];
      delete[] indexMatrix[i];
    }
    delete[] adjMatrix;
    delete[] indexMatrix;
  }

  bool isLinked(const int &i, const int &j) const
  {
    return adjMatrix[i][j] && adjMatrix[j][i];
  }

  // este es el verdadero backtraking
  void testGraphs(const int &i, const int &j)
  {
    if (i == nNodes)
    {

      if (!isDisconnected())
      {
        solutions++;
        // if (solutions == 4)
        printAdj();
      }

      return;
    }

    int nextI = i, nextJ = j + 1;
    if (nextJ == nNodes)
    {
      nextI++;
      nextJ = 0;
    }

    // Solo recorrer la mitad superior de la matriz (evita duplicados)
    if (j <= i)
    {
      testGraphs(nextI, nextJ);
      return;
    }

    // Poda: si ya alcanzaron el máximo de enlaces, no probar este enlace
    if (nodes[i].actualLinks >= nodes[i].maxLinks || nodes[j].actualLinks >= nodes[j].maxLinks)
    {
      testGraphs(nextI, nextJ);
      return;
    }

    // Opción 1: no marcar la casilla
    testGraphs(nextI, nextJ);

    // Opción 2: marcar la casilla si se puede
    if (canLink(i, j) && !isLinked(i, j))
    {
      adjMatrix[i][j] = true;
      adjMatrix[j][i] = true;
      nodes[i].actualLinks++;
      nodes[j].actualLinks++;
      testGraphs(nextI, nextJ);
      adjMatrix[i][j] = false;
      adjMatrix[j][i] = false;
      nodes[i].actualLinks--;
      nodes[j].actualLinks--;
    }
  }

  // Verifica si el grafo está desconectado (retorna true si hay algún nodo no alcanzable desde el nodo 0)
  bool isDisconnected()
  {
    // Arreglo para marcar los nodos visitados
    bool *visited = new bool[nNodes];
    for (int i = 0; i < nNodes; i++)
    {
      visited[i] = false; // Inicializa todos los nodos como no visitados
    }

    // Pila para realizar DFS (búsqueda en profundidad)
    int *stack = new int[nNodes];
    int top = 0;

    // Comienza el recorrido desde el nodo 0
    visited[0] = true; // Marca el nodo 0 como visitado
    stack[top++] = 0;  // Agrega el nodo 0 a la pila

    // Recorrido DFS iterativo
    while (top > 0)
    {
      int u = stack[--top]; // Saca un nodo de la pila
      for (int v = 0; v < nNodes; v++)
      {
        // Si hay una arista y el nodo v no ha sido visitado
        if (adjMatrix[u][v] && !visited[v])
        {
          visited[v] = true; // Marca el nodo como visitado
          stack[top++] = v;  // Agrega el nodo a la pila para seguir el recorrido
        }
      }
    }

    // Verifica si hay algún nodo no visitado
    for (int i = 0; i < nNodes; i++)
    {
      if (!visited[i])
      {
        // Si encuentra un nodo no visitado, el grafo está desconectado
        delete[] visited;
        delete[] stack;
        return true;
      }
    }

    // Si todos los nodos fueron visitados, el grafo está conectado
    delete[] visited;
    delete[] stack;
    return false;
  }

  int getActualLinks() const
  {
    int links = 0;
    for (int i = 0; i < nNodes; i++)
    {
      links += nodes[i].actualLinks;
    }
    return links / 2;
  }

  int getEnergySystem() const
  {
    int energy = 0;
    for (int i = 0; i < nNodes; i++)
    {
      int counterE = 0;
      int fileEnergy = 0;
      for (int j = 0; j < nNodes; j++)
      {
        if (nodes[i].type == H)
          continue;

        // descartamos la diagonal principal
        if (i == j || !adjMatrix[i][j])
          continue;

        // contamos los nodos E
        cout << "nodo I " << nodes[i].type << "(" << i << ")" << " nodo J " << nodes[j].type << "(" << j << ")" << endl;
        if (nodes[i].type == E && nodes[j].type == E)
        {
          counterE++;
        }
        // if ((nodes[i].type == E || nodes[i].type == M) && (nodes[j].type == E || nodes[j].type == M))
        if ((nodes[i].type == M) && (nodes[j].type == E || nodes[j].type == M))
        {
          fileEnergy++;
        }
        if (nodes[i].type == C && nodes[j].type != H)
        {
          fileEnergy--;
        }
      }
      if (nodes[i].type == E && counterE > 0)
      {
        while (counterE > 0)
        {
          if (counterE > 1)
          {
            counterE = counterE - 2;
            fileEnergy += 2 * 3;
          }
          else
          {
            fileEnergy++;
            counterE--;
          }
        }
      }
      energy += fileEnergy;
      cout << "fileEnery: " << fileEnergy << endl;
    }
    cout << "the energy is: " << energy << endl;
    return energy / 2;
  }

public:
  DNA(string strDna)
  {
    nNodes = strDna.size();
    dna = strDna;
    initializeAdjMatriz();
    initializeNodes();
  }

  ~DNA()
  {
    deleteNodes();
    deleteAdjMatrix();
    dna = "";
    nNodes = 0;
    nodes = nullptr;
    adjMatrix = nullptr;
    globalMaxLinks = 0;
    solutions = 0;
    indexMatrix = nullptr;
  }

  void printAdj()
  {
    // printNodes();
    cout << "-------------------------\n";
    cout << "    ";
    for (int i = 0; i < nNodes; i++)
    {
      cout << "  " << nodes[i].type;
    }
    cout << endl;
    cout << "    ";
    for (int i = 0; i < nNodes; i++)
    {
      cout << "  " << i;
    }
    cout << endl;
    cout << "-------------------------\n";
    for (int i = 0; i < nNodes; i++)
    {
      cout << nodes[i].type << '(' << i << ')';
      for (int j = 0; j < nNodes; j++)
      {
        cout << "  " << adjMatrix[i][j];
      }
      cout << "\n";
    }
    cout << "-------------------------\n";
    cout << "#" << solutions << " enlaces: " << getActualLinks() << endl;
    // cout << " energia del sistema: " << getEnergySystem() << endl;
    getEnergySystem();
  }

  void printNodes()
  {
    cout << "-------------------------\n";
    cout << "Nodos actuales" << endl;
    cout << "-------------------------\n";
    for (int i = 0; i < nNodes; i++)
    {
      cout << "type: " << nodes[i].type << endl;
      cout << "maxLinks: " << nodes[i].maxLinks << endl;
      cout << "actualLinks: " << nodes[i].actualLinks << endl;
      cout << "-------------------------\n";
    }
  }

  void backtracking()
  {
    testGraphs(0, 0);
  }

  int getGlobalMaxLikns() const
  {
    return globalMaxLinks;
  }

  int getSolutions() const
  {
    return solutions;
  }
};

bool isDigit(char c)
{
  return c >= '0' && c <= '9';
}

string readInput()
{
  string input;
  cout << "Enter a string: ";
  cin >> input;
  string aux = input;
  for (int i = 0; i < input.size(); i++)
  {
    if (input[i] == 'h')
    {
      aux[i] = H;
    }
    if (input[i] == 'e')
    {
      aux[i] = E;
    }
    if (input[i] == 'm')
    {
      aux[i] = M;
    }
    if (input[i] == 'c')
    {
      aux[i] = C;
    }
  }
  char prev = '\0';
  int size = aux.size();
  string dna = "";
  for (int i = 0; i < size; i++)
  {
    if (i == 0)
    {
      prev = aux[0];
      dna += aux[0];
      continue;
    }
    if (isDigit(aux[i]))
    {
      int repeats = aux[i] - '0';
      for (int j = 1; j < repeats; j++)
      {
        dna += prev;
      }
    }
    else
    {
      dna += aux[i];
      prev = aux[i];
    }
  }
  return dna;
}

int main(int argc, char const *argv[])
{
  string dna = readInput();
  cout << "DNA string: " << dna << endl;
  DNA dnaNumoris = DNA(dna);
  // dnaNumoris.printAdj();
  // dnaNumoris.printNodes();
  // dnaNumoris.firstGraph();
  dnaNumoris.backtracking();
  cout << "cantidad de combinaciones " << dnaNumoris.getSolutions() << endl;

  return 0;
}
