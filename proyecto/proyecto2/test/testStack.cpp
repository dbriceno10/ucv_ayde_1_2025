#include <iostream>
using namespace std;

template <typename T>
class historyDNA
{
private:
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
};

int main(int argc, char const *argv[])
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
  return 0;
}

void findLongestPath()
{
  bool *visited = new bool[nNodes];
  int maxLength = 0;
  int *path = new int[nNodes];
  int *bestPath = new int[nNodes];
  int bestLen = 0;

  for (int start = 0; start < nNodes; start++)
  {
    for (int i = 0; i < nNodes; i++)
      visited[i] = false;

    int currentLen = 0;
    dfsLongest(start, visited, path, bestPath, currentLen, bestLen);
  }

  // Mostrar resultados
  cout << "\n📏 Camino más largo encontrado (" << bestLen << " nodos): ";
  for (int i = 0; i < bestLen; i++)
  {
    cout << bestPath[i] << "(" << nodes[bestPath[i]].type << ")";
    if (i != bestLen - 1)
      cout << " -> ";
  }
  cout << endl;

  delete[] visited;
  delete[] path;
  delete[] bestPath;
}

void dfsLongest(int u, bool visited[], int path[], int bestPath[], int currentLen, int &bestLen)
{
  visited[u] = true;
  path[currentLen] = u;
  currentLen++;

  if (currentLen > bestLen)
  {
    bestLen = currentLen;
    for (int i = 0; i < bestLen; i++)
      bestPath[i] = path[i];
  }

  for (int v = 0; v < nNodes; v++)
  {
    if (adjMatrix[u][v] && !visited[v])
    {
      dfsLongest(v, visited, path, bestPath, currentLen, bestLen);
    }
  }

  visited[u] = false;
}