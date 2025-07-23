#include <iostream>
#include <string>
#include <cmath>
#include <chrono>

using namespace std;

char const H = 'H', E = 'E', M = 'M', C = 'C';
const int magic = 38;

template <typename T>
class Stack
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
  typedef Node *tPosition;
  // Constructor
  Stack() : topNode(nullptr), count(0) {}

  // Destructor
  ~Stack()
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
    tPosition temp = topNode;
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

  tPosition TopPtr()
  {
    return topNode;
  }

  bool Include(T element)
  {
    if (IsEmpty())
      return false;
    bool flag = false;
    tPosition current = topNode;
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
    tPosition current = topNode;
    while (current)
    {
      cout << current->data << endl;
      current = current->next;
    }
  }
};

class DNA
{

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
    int index1;
    int index2;
    int index3;
  };

  class CycleList : public Stack<Cycle>
  {
    bool IncludeIndex(int indexA, int indexB, Cycle cycle)
    {
      int index1 = cycle.index1;
      int index2 = cycle.index2;
      int index3 = cycle.index3;
      string str = to_string(indexA) + "-" + to_string(indexB);
      string chain1 = to_string(index1) + "-" + to_string(index2);
      string chain2 = to_string(index1) + "-" + to_string(index3);
      string chain3 = to_string(index2) + "-" + to_string(index3);
      string chainA = to_string(indexA) + "-" + to_string(indexB);
      string chainB = to_string(indexB) + "-" + to_string(indexA);
      if ((chainA == chain1) ||
          (chainA == chain2) ||
          (chainA == chain3) ||
          (chainB == chain1) ||
          (chainB == chain2) ||
          (chainB == chain3))
      {
        return true;
      }
      return false;
    }

  public:
    int GetAllCycles(const int &indexA, const int &indexB)
    {
      if (IsEmpty())
        return 1;
      int multiplier = 1;
      Node *current = topNode;
      while (current)
      {
        if (IncludeIndex(indexA, indexB, current->data))
        {
          multiplier = multiplier * current->data.multiplier;
        }
        current = current->next;
      }
      return multiplier;
    }

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
      tPosition current = topNode;
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
      tPosition current = topNode;
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
  string dna;
  int solutions = 0;
  int bestSolution = 0;
  int bestEnergy = 0;
  int bestUsefullLife = 0;

  void initializeAdjMatriz()
  {
    // agregamos inicializacion de matriz de indices
    adjMatrix = new bool *[nNodes];
    for (int i = 0; i < nNodes; i++)
    {
      adjMatrix[i] = new bool[nNodes];
    }
    for (int i = 0; i < nNodes; i++)
    {
      for (int j = 0; j < nNodes; j++)
      {
        adjMatrix[i][j] = false;
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

  void deleteNodes()
  {
    delete[] nodes;
  }

  void deleteAdjMatrix()
  {
    for (int i = 0; i < nNodes; i++)
    {
      delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
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
        CycleList cicles;
        detectAndClassifyCycles(adjMatrix, cicles);
        int eSystem = getEnergySystem(adjMatrix, cicles);
        bool **longestMatrix;
        const int nNodosPath = buildLongestPathMatrix(longestMatrix);
        // al tener el camino mas largo, la energia la calcularemos respecto a los ciclos de la matriz completa, por lo que en esa ocasion no vamos a modificar esa pila
        detectAndClassifyCycles(longestMatrix, cicles, false);
        int eLongest = getEnergySystem(longestMatrix, cicles);
        deleteSubMatrix(longestMatrix);
        int usefullLife = abs(eSystem * eLongest * nNodosPath * 10);
        if (solutions == magic)
        {
          printAdj(adjMatrix, true);
          cicles.PrintAll();
          cout << "#" << solutions << " energia: " << eSystem << " vida: " << usefullLife << endl;
        }
        if (bestSolution == 0)
        {
          bestSolution = solutions;
          bestEnergy = eSystem;
          bestUsefullLife = usefullLife;
        }
        else
        {
          if (eSystem > bestEnergy)
          {
            bestSolution = solutions;
            bestEnergy = eSystem;
            bestUsefullLife = usefullLife;
          }
          else if (eSystem == bestEnergy)
          {
            if (usefullLife > bestUsefullLife)
            {
              bestSolution = solutions;
              bestEnergy = eSystem;
              bestUsefullLife = usefullLife;
            }
          }
        }
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

    // No enlaces posibles, pero aún debemos seguir recorriendo para llegar a i == nNodes
    if (countFreeLinks() == 0)
    {
      testGraphs(nextI, nextJ); // seguir sin enlazar
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

  // Verificamos si la matriz generada es disconexa para excluirla de las posibles soluciones
  bool isDisconnected()
  {
    // array para marcar los nodos visitados
    bool *visited = new bool[nNodes];
    for (int i = 0; i < nNodes; i++)
    {
      visited[i] = false;
    }

    Stack<int> stack;

    visited[0] = true;
    stack.Push(0);

    while (!stack.IsEmpty())
    {
      int u = stack.Top();
      stack.Pop();

      for (int v = 0; v < nNodes; v++)
      {
        if (adjMatrix[u][v] && !visited[v])
        {
          visited[v] = true;
          stack.Push(v);
        }
      }
    }

    // Verificamos si quedó algún nodo sin visitar
    for (int i = 0; i < nNodes; i++)
    {
      if (!visited[i])
      {
        delete[] visited;
        return true; // Hay al menos un nodo no conectado
      }
    }

    delete[] visited;
    return false; // Todos fueron visitados, el grafo es conexo
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

  int getEnergySystem(bool **adjMatrix, CycleList &list) const
  {
    int energy = 0;
    for (int i = 0; i < nNodes; i++)
    {
      if (nodes[i].type == H)
        continue;
      int counterE = 0;
      int fileEnergy = 0;
      bool *rows = new bool[nNodes];

      for (int j = 0; j < nNodes; j++)
      {

        // descartamos la diagonal principal
        if (i == j || !adjMatrix[i][j] || nodes[j].type == H)
          continue; // // contamos los nodos E
        int multiplier = list.GetAllCycles(i, j);
        if (solutions == magic)
        {
          string str = to_string(i) + "-" + to_string(j);
          // cout << "multiplier " << multiplier << " con i: " << i << " con j: " << j << endl;
          cout << "multiplier " << multiplier << " con " << str << endl;

          // if (!list.IsEmpty())
          // {
          //   cout << "multiplier list " << list.Top().multiplier << endl;
          // }
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
  // Metodo para determinar que elementos en la matriz forman ciclos para guardarlos en la "pila de busqueda", si en la matriz consigo que A-B, B-C y C-A entonces se forma un ciclo
  void detectAndClassifyCycles(bool **adjMatrix, CycleList &list, bool saveCicles = true)
  {
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
          string aux = "|" + to_string(i) + "-" + to_string(j) + "-" + to_string(k) + "|";
          Cycle cycle;
          cycle.cycle = aux;
          cycle.multiplier = 1;
          cycle.index1 = i;
          cycle.index2 = j;
          cycle.index3 = k;
          if ((ti == E && tj == E && tk == E) || (ti == C && tj == C && tk == C) || (ti == M && tj == M && tk == M))
          {
            cycle.multiplier = 3;
            if (saveCicles)
            {
              list.Push(cycle);
            }
          }
          else if ((ti == C || ti == M || ti == E) &&
                   (tj == C || tj == M || tj == E) &&
                   (tk == C || tk == M || tk == E) &&
                   (ti != tj || tj != tk || ti != tk)) // Al menos 2 diferentes
          {
            cycle.multiplier = 2;
            if (saveCicles)
            {
              list.Push(cycle);
            }
          }
          else
          {
            // si se forma un ciclo entre nodos distintos
            cycle.multiplier = 2;
            if (saveCicles)
            {
              list.Push(cycle);
            }
          }
        }
      }
    }
  }
  // usamos el algoritmo de busqueda por profundidad, nos movemos por el grafo hasta caer en un nodo ya recorrido
  void dfsLongestPath(int u, bool *visited, Stack<int> &currentPath, Stack<int> &longestPath)
  {
    // el entrar marcamos cada nodo como visitado y lo guardamos en la pila
    visited[u] = true;
    currentPath.Push(u);
    // recursion mientras tengamos nodos no visitados
    for (int v = 0; v < nNodes; v++)
    {
      if (adjMatrix[u][v] && !visited[v])
      {
        dfsLongestPath(v, visited, currentPath, longestPath);
      }
    }
    // como nuestra pila actual tiene mas elementos que la pila del camino mas largo, vamos a copiar en una pila temporal ese camino
    if (currentPath.Size() > longestPath.Size())
    {
      longestPath.Clear();
      Stack<int>::tPosition p = currentPath.TopPtr();
      Stack<int> temp;
      while (p)
      {
        temp.Push(p->data);
        p = p->next;
      }
      // invertimos al guardar para que quede en el mismo orden
      p = temp.TopPtr();
      while (p)
      {
        longestPath.Push(p->data);
        p = p->next;
      }
    }

    currentPath.Pop();
    visited[u] = false;
  }

  int buildLongestPathMatrix(bool **&longestMatrix)
  {
    bool *visited = new bool[nNodes];
    Stack<int> longestPath;

    // Paso 1: Obtener el camino más largo
    for (int i = 0; i < nNodes; i++)
    {
      for (int v = 0; v < nNodes; v++)
        visited[v] = false;
      Stack<int> currentPath;
      dfsLongestPath(i, visited, currentPath, longestPath);
    }

    // Paso 2: Crear nueva submatriz
    initializeSubMatrix(longestMatrix);

    // Paso 3: Marcar solo los enlaces del camino más largo
    Stack<int>::tPosition p = longestPath.TopPtr();
    while (p && p->next)
    {
      int u = p->data;
      int v = p->next->data;
      longestMatrix[u][v] = true;
      longestMatrix[v][u] = true;
      p = p->next;
    }
    delete[] visited;
    return longestPath.Size();
  }

  void initializeSubMatrix(bool **&subAdjMatrix)
  {
    subAdjMatrix = new bool *[nNodes];
    for (int i = 0; i < nNodes; i++)
    {
      subAdjMatrix[i] = new bool[nNodes];
    }
    for (int i = 0; i < nNodes; i++)
    {
      for (int j = 0; j < nNodes; j++)
      {
        subAdjMatrix[i][j] = false;
      }
    }
  }

  void deleteSubMatrix(bool **&subAdjMatrix)
  {
    for (int i = 0; i < nNodes; i++)
    {
      delete[] subAdjMatrix[i];
    }
    delete[] subAdjMatrix;
  }

  void printAdj(bool **adjMatrix, bool printSolutions = false)
  {
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
    if (printSolutions)
    {
      cout << "#" << solutions << " enlaces: " << getActualLinks() << endl;
    }
  }

public:
  DNA(string strDna)
  {
    nNodes = strDna.size();
    dna = strDna;
    initializeAdjMatriz();
    initializeNodes();
    solutions = 0;
    bestSolution = 0;
    bestEnergy = 0;
    bestUsefullLife = 0;
  }

  ~DNA()
  {
    deleteNodes();
    deleteAdjMatrix();
    dna = "";
    nNodes = 0;
    nodes = nullptr;
    adjMatrix = nullptr;
    solutions = 0;
    bestSolution = 0;
    bestEnergy = 0;
    bestUsefullLife = 0;
  }

  void backtracking()
  {
    testGraphs(0, 0);
  }

  int getSolutions() const
  {
    return solutions;
  }

  int getBestSolution() const
  {
    return bestSolution;
  }

  int getBestEnery() const
  {
    return bestEnergy;
  }

  int getBestUsefullLife() const
  {
    return bestUsefullLife;
  }
};

bool isDigit(char c)
{
  return (c >= '0' && c <= '9');
}

bool isLetter(char c)
{
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

string readInput()
{
  string input;
  cout << "Enter a string: ";
  cin >> input;
  string dna = "";

  char currentChar = '\0';
  int i = 0;

  while (i < input.size())
  {
    char c = input[i];

    if (isLetter(c))
    {
      // Convertimos minúscula a tipo de nodo en mayúscula
      if (c == 'h' || c == H)
        currentChar = H;
      else if (c == 'e' || c == E)
        currentChar = E;
      else if (c == 'm' || c == M)
        currentChar = M;
      else if (c == 'c' || c == C)
        currentChar = C;

      dna += currentChar;
      i++;
    }
    else if (isDigit(c))
    {
      int num = 0;
      // Construimos el número manualmente
      while (i < input.size() && input[i] >= '0' && input[i] <= '9')
      {
        num = num * 10 + (input[i] - '0');
        i++;
      }

      // Repetimos el carácter anterior (ya agregado una vez), num - 1 veces
      for (int j = 1; j < num; j++)
      {
        dna += currentChar;
      }
    }
    else
    {
      // Ignorar cualquier otro carácter inválido
      i++;
    }
  }

  return dna;
}

int main()
{
  // Usa std::chrono para medir el tiempo correctamente
  auto startFxC = std::chrono::high_resolution_clock::now();
  string dna = readInput();
  cout << "DNA string: " << dna << endl;
  DNA dnaNumoris = DNA(dna);
  dnaNumoris.backtracking();
  cout << "cantidad de combinaciones " << dnaNumoris.getSolutions() << endl;
  cout << endl;

  cout << "La mejor solucion fue la #" << dnaNumoris.getBestSolution() << " energia: " << dnaNumoris.getBestEnery() << " vida util: " << dnaNumoris.getBestUsefullLife() << endl;

  // cout << dnaNumoris.getBestEnery() << " " << dnaNumoris.getBestUsefullLife() << endl;
  auto stopFxC = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float, std::milli> durationFxC = stopFxC - startFxC;
  double timeFxC = durationFxC.count();
  cout << "Tiempo de ejecución: " << timeFxC << " ms" << endl;
  return 0;
}