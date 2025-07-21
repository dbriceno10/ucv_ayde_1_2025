#include <iostream>
#include <string>

using namespace std;

char const H = 'H', E = 'E', M = 'M', C = 'C';

class DNA
{
  template <typename T>
  class historyDNA
  {
  protected:
    struct Node
    {
      T data;
      Node *next;
      Node(const T &d, Node *n = nullptr) : data(d), next(n) {}
    };

    Node *topNode; // Puntero al tope
    int count;     // Contador de elementos
  public:
    // Constructor
    historyDNA() : topNode(nullptr), count(0) {}

    // Destructor
    ~historyDNA()
    {
      Clear();
    }

    // Vacía la pila
    void Clear()
    {
      while (!IsEmpty())
      {
        Pop();
      }
      topNode = nullptr;
      count = 0;
    }

    // Verifica si está vacía
    bool IsEmpty() const
    {
      return count == 0;
    }

    // Agrega elemento al tope
    void Push(const T &x)
    {
      topNode = new Node(x, topNode);
      count++;
    }

    // Elimina el elemento del tope
    void Pop()
    {
      // if (IsEmpty())
      // {
      //   cout << "Pila vacía" << endl;
      // }
      Node *temp = topNode;
      topNode = topNode->next;
      delete temp;
      count--;
    }

    // Tamaño de la pila
    int Size() const
    {
      return count;
    }

    // Acceso al elemento tope
    T Top() const
    {
      // if (IsEmpty())
      // {
      //   cout << "Pila vacía" << endl;
      // }
      return topNode->data;
    }

    bool Include(T element)
    {
      if (IsEmpty())
        return false;
      bool flag = false;
      Node *current = topNode;
      while (current && !flag)
      {
        if (current->data == element)
        {
          flag = true;
        }
        else
        {
          current = current->next;
        }
      }
      return flag;
    }

    void PrintAll()
    {
      Node *current = topNode;
      while (current)
      {
        cout << current->data << endl;
        current = current->next;
      }
    }
  };

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

  struct Cycle
  {
    string cycle;
    int multiplier;
  };

  class CycleList : public historyDNA<Cycle>
  {
  public:
    bool Find(string element, Cycle &cycle)
    {
      if (IsEmpty())
        return false;
      bool flag = false;
      Node *current = topNode;
      while (current && !flag)
      {
        if (current->data.cycle == element)
        {
          flag = true;
          cycle.cycle = current->data.cycle;
          cycle.multiplier = current->data.multiplier;
        }
        else
        {
          current = current->next;
        }
      }
      return flag;
    }
    bool FindByIndex(const int &i, const int &j, const int &k, Cycle &cycle) const
    {
      if (IsEmpty())
        return false;
      bool flag = false;
      Node *current = topNode;
      while (current && !flag)
      {
        const string aux = current->data.cycle;
        if (aux.find(i) && aux.find(j) && aux.find(k))
        {
          flag = true;
          cycle.cycle = current->data.cycle;
          cycle.multiplier = current->data.multiplier;
        }
        else
        {
          current = current->next;
        }
      }
      return flag;
    }
    void PrintAll()
    {
      Node *current = topNode;
      while (current)
      {
        cout << current->data.cycle << endl;
        current = current->next;
      }
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

  int countFreeLinks() const
  {
    int freeLinks = 0;
    for (int i = 0; i < nNodes; i++)
      freeLinks += nodes[i].maxLinks - nodes[i].actualLinks;
    return freeLinks;
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
        countI++;
      }
      if (adjMatrix[j][k])
      {
        countJ++;
      }
    }

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
        // {
        printAdj();
        // startFromNode(0);
        // for (int i = 0; i < nNodes; i++)
        // {
        //   startFromNode(i);
        // }
        CycleList cicles;
        detectAndClassifyCycles(cicles);
        // cicles.PrintAll();
        // cout << "Esta vacia? " << (cicles.IsEmpty() ? "SI" : "NO") << endl;
        // Cycle cycle;
        // cout << "2-3-4 esta? " << (cicles.Find("2-3-4", cycle) ? "SI" : "NO") << endl;
        // cout << "Energia del sistema " <<  getEnergySystem()<< endl;
        int e = getEnergySystem(cicles);
        cout << "energia bruta " << e << endl;
        // }
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

  int getEnergySystem(const CycleList &list) const
  {
    int energy = 0;
    for (int i = 0; i < nNodes; i++)
    {
      if (nodes[i].type == H)
        continue;
      int counterE = 0;
      int fileEnergy = 0;
      bool *rows = new bool[nNodes];
      bool flag = false;
      Cycle cycle;
      for (int k = 0; k < nNodes; k++)
      {
        if (adjMatrix[i][k] && nodes[k].type != H)
        {
          rows[k] = 1;
        }
        else
        {
          rows[k] = 0;
        }
      }

      for (int k = 0; k < nNodes; k++)
      {
        if (!flag)
        {
          if (rows[k])
          {
            for (int m = k; k < nNodes; k++)
            {
              if (!flag)
              {
                flag = list.FindByIndex(i, k, m, cycle);
              }
              else
              {
                break;
              }
            }
          }
        }
        else
        {
          break;
        }
      }

      for (int j = 0; j < nNodes; j++)
      {

        // descartamos la diagonal principal
        if (i == j || !adjMatrix[i][j] || nodes[j].type == H)
          continue; // // contamos los nodos E
        int multiplier = 1;
        if (flag && cycle.cycle.find(j))
        {
          // cout << "ciclo " << cycle.cycle << " i: " << i << " j: " << j << endl;
          multiplier = cycle.multiplier;
        }
        if ((nodes[i].type == E || nodes[i].type == M) && (nodes[j].type == E || nodes[j].type == M))
        {
          int e = 1;
          fileEnergy = fileEnergy + e * multiplier;
        }
        if ((nodes[i].type == C && nodes[j].type != H) || (nodes[j].type == C && nodes[i].type != H))
        {
          int e = -1;
          fileEnergy = fileEnergy + e * multiplier;
        }
      }
      energy += fileEnergy;
      delete[] rows;
    }
    energy = energy / 2;
    int freeLinks = countFreeLinks();
    energy = energy - freeLinks;
    return energy;
  }

  void dfsDNA(int u, bool *visited)
  {
    visited[u] = true;

    cout << "Visitando nodo " << nodes[u].type << "(" << u << ")" << endl;

    for (int v = 0; v < nNodes; v++)
    {
      if (adjMatrix[u][v] && !visited[v])
      {
        dfsDNA(v, visited);
      }
    }
  }

  void startFromNode(int indexNode)
  {
    bool *visited = new bool[nNodes];
    for (int i = 0; i < nNodes; i++)
      visited[i] = false;
    cout << "Iniciando recorrido DFS desde nodo " << nodes[indexNode].type << "(" << indexNode << ")" << endl;
    dfsDNA(indexNode, visited);
    delete[] visited;
  }

  void detectAndClassifyCycles(CycleList &list)
  {
    cout << "\n--- Detectando y clasificando ciclos de 3 nodos ---\n";

    for (int i = 0; i < nNodes; i++)
    {
      if (nodes[i].type == H)
        continue;
      for (int j = i + 1; j < nNodes; j++)
      {
        if (!adjMatrix[i][j])
          continue;
        for (int k = j + 1; k < nNodes; k++)
        {
          if (!adjMatrix[i][k] || !adjMatrix[j][k])
            continue;

          char ti = nodes[i].type;
          char tj = nodes[j].type;
          char tk = nodes[k].type;
          if (ti == H || tj == H || tk == H)
            continue;

          // Determinar el tipo de ciclo
          string aux = to_string(i) + "-" + to_string(j) + "-" + to_string(k);
          Cycle cycle;
          cycle.cycle = aux;
          cycle.multiplier = 1;
          if ((ti == E && tj == E && tk == E) || (ti == C && tj == C && tk == C) || (ti == M && tj == M && tk == M))
          {
            cout << "Ciclo homogéneo (" << ti << "-" << tj << "-" << tk << ") entre nodos: " << i << ", " << j << ", " << k << " (triplica energía)\n";
            cycle.multiplier = 3;
            list.Push(cycle);
          }
          else if ((ti == C || ti == M || ti == E) &&
                   (tj == C || tj == M || tj == E) &&
                   (tk == C || tk == M || tk == E) &&
                   (ti != tj || tj != tk || ti != tk)) // Al menos 2 diferentes
          {
            cout << "Ciclo mixto (" << ti << "-" << tj << "-" << tk << ") entre nodos: " << i << ", " << j << ", " << k << " (duplica energía)\n";
            cycle.multiplier = 2;
            list.Push(cycle);
          }
          else
          {
            cout << "Ciclo (" << ti << "-" << tj << "-" << tk << ") entre nodos: " << i << ", " << j << ", " << k << " (sin efecto especial)\n";
            cycle.multiplier = 2;
            list.Push(cycle);
          }
        }
      }
    }
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

  void testStack()
  {
    historyDNA<int> stack;

    for (int i = 0; i < 20; i++)
    {
      cout << "push " << i + 1 << endl;
      stack.Push(i + 1);
    }
    cout << "esta el 15? " << (stack.Include(15) ? "SI" : "NO") << endl;
    cout << "esta el 30? " << (stack.Include(30) ? "SI" : "NO") << endl;
    for (int i = 0; i < 20; i++)
    {
      cout << "pop " << stack.Top() << endl;
      stack.Pop();
    }
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
  dnaNumoris.backtracking();
  cout << "cantidad de combinaciones " << dnaNumoris.getSolutions() << endl;
  // dnaNumoris.testStack();

  // historyDNA stack = historyDNA(dna.size());

  // for (int i = 0; i < dna.size(); i++)
  // {
  //   cout << "push " << 50 + i << endl;
  //   stack.push(50 + i);
  // }
  // for (int i = 0; i < dna.size(); i++)
  // {
  //   cout << "pop " << stack.pop() << endl;
  // }

  return 0;
}
