#include <iostream>
#include <string>

using namespace std;

class DNATree
{
  struct Node
  {
    char type;
    int maxLinks;
    int currentLinks;
    Node *link1;
    Node *link2;
    Node *link3;
    Node *link4;
    Node(char t)
    {
      type = t;
      currentLinks = 0;
      // Define maxLinks based on type
      if (t == 'H')
        maxLinks = 1;
      else if (t == 'E')
        maxLinks = 4;
      else if (t == 'M')
        maxLinks = 2;
      else if (t == 'C')
        maxLinks = 2;
      link1 = nullptr;
      link2 = nullptr;
      link3 = nullptr;
      link4 = nullptr;
    }
  };
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
  char prev = '\0';
  int size = input.size();
  string dna = "";
  for (int i = 0; i < size; i++)
  {
    if (i == 0)
    {
      prev = input[0];
      dna += input[0];
      continue;
    }
    if (isDigit(input[i]))
    {
      int repeats = input[i] - '0';
      for (int j = 1; j < repeats; j++)
      {
        dna += prev;
      }
    }
    else
    {
      dna += input[i];
      prev = input[i];
    }
  }
  return dna;
}

int main(int argc, char const *argv[])
{
  /* code */
  string dna = readInput();
  cout << "DNA string: " << dna << endl;
  int size = dna.size();
  char *c = new char[size + 1];
  for (int i = 0; i < size; i++)
  {
    c[i] = dna[i];
  }
  for (int i = 0; i < size; i++)
  {
    cout << c[i] << " ";
  }
  delete[] c;
  c = nullptr;
  return 0;
}
