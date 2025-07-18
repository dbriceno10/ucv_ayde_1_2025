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
        nodes[i].type = M;
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
      return false;
  }

  void printAdj()
  {
    cout << "here" << endl;
    for (int i = 0; i < nNodes; i++)
    {
      cout << "|";
      for (int j = 0; j < nNodes; j++)
      {
        // cout << "(" << i << "," << j << "): " << " " << M[i][j] << " ";
        cout << " " << adjMatrix[i][j] << " ";
      }
      cout << "|" << endl;
    }
    cout << endl;
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
    nodes = new Node[nNodes];
    initializeAdjMatriz();
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

  void PrintAdjMAtrix()
  {
    printAdj();
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
  if (!input.size())
  {
    cout << "El ADN no puede estar vacío";
    return "-1";
  }
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
    if (input[i] == 'h')
    {
      aux[i] = H;
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
  if (dna == "-1")
  {
    return 0;
  }
  DNA dnaNumoris = DNA(dna);
  dnaNumoris.PrintAdjMAtrix();
  // int n = dna.size();
  // char *c = new char[n + 1];
  // for (int i = 0; i < n; i++)
  // {
  //   c[i] = dna[i];
  // }
  // for (int i = 0; i < n; i++)
  // {
  //   cout << c[i] << " ";
  // }

  // delete[] c;  // Free the allocated memory
  // c = nullptr; // Avoid dangling pointer

  return 0;
}
