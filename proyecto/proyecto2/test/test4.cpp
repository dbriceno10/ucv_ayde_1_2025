#include <iostream>
#include <string>

using namespace std;

char const H = 'H', E = 'E', M = 'M', C = 'C';

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

  int nNodes;
  Node *nodes;
  bool **adjMatrix;
  string dna;

  void initializeAdjMatriz()
  {
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

  bool canLink(const int &i, const int &j)
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
    }
    delete[] adjMatrix;
  }

public:
  DNA(string strDna)
  {
    nNodes = strDna.size();
    dna = strDna;
    initializeAdjMatriz();
    initializeNodes();
    // for (int i = 0; i < nNodes; i++)
    // {
    //   for (int j = 0; j < nNodes; j++)
    //   {
    //     if (canLink(i, j))
    //     {
    //       adjMatrix[i][j] = true;
    //       adjMatrix[j][i] = true;
    //     }
    //   }
    // }
  }

  void backtraking(const int i, const int j)
  {
    if (i == nNodes - 1 && j == nNodes - 1)
    {
      printAdj();
    }
    for (int i = 0; i < nNodes; i++)
    {
      for (int j = 0; j < nNodes; j++)
      {
        if (canLink(i, j))
        {
          adjMatrix[i][j] = true;
          adjMatrix[j][i] = true;
        }
        backtraking(i, j);
        if (canLink(i, j))
        {
          adjMatrix[i][j] = false;
          adjMatrix[j][i] = false;
        }
      }
    }
  }

  ~DNA()
  {
    deleteNodes();
    deleteAdjMatrix();
    dna = "";
    nNodes = 0;
    nodes = nullptr;
    adjMatrix = nullptr;
  }

  void printAdj()
  {
    cout << "-------------------------\n";
    cout << "    ";
    for (int i = 0; i < nNodes; i++)
    {
      cout << "  " << nodes[i].type;
    }
    cout << endl;
    cout << "    ";
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
  }

  void printNodes()
  {
    for (int i = 0; i < nNodes; i++)
    {
      cout << "type: " << nodes[i].type << endl;
      cout << "maxLinks: " << nodes[i].maxLinks << endl;
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
  // dnaNumoris.printAdj();
  // dnaNumoris.printNodes();
  dnaNumoris.backtraking(0, 0);

  return 0;
}
