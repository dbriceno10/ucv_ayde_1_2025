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

string reverse(string str)
{
  string aux = "";
  for (int i = str.length() - 1; i >= 0; i--)
  {

    aux += str[i];
  }
  return aux;
}

int factorial(int n)
{
  if (n <= 1)
    return 1;
  return n * factorial(n - 1);
}

bool include(string *array, string str, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (array[i] == str || array[i] == reverse(str))
    {
      return true;
    }
  }
  return false;
}

// imprimir premutacion
void imprimirPermutacion(char arr[], int n, string *array, int &size)
{
  string perm = "";
  for (int i = 0; i < n; i++)
  {
    perm += arr[i];
  }
  if (size == 0)
  {
    array[size] = perm;
    size++;
  }
  else
  {
    if (!include(array, perm, size))
    {
      array[size] = perm;
      size++;
    }
  }
}

void generarPermutaciones(char *arr, int n, int index, string *array, int &size)
{
  // cout << "index: " << index << endl;
  // cout << "n: " << n << endl;
  // imprimirPermutacion(arr, n);
  if (index == n)
  {
    // cout << "index == n" << endl;
    // Imprimir la permutación
    imprimirPermutacion(arr, n, array, size);
    // cout << "suma: " << calcularSuma(arr, n) << endl;
    return;
  }

  for (int i = index; i < n; i++)
  {
    swap(arr[index], arr[i]);                             // Intercambiar
    generarPermutaciones(arr, n, index + 1, array, size); // Llamada recursiva
    swap(arr[index], arr[i]);                             // Deshacer el intercambio
  }
}

int main(int argc, char const *argv[])
{
  string dna = readInput();
  cout << "DNA string: " << dna << endl;
  int n = dna.size();
  char *c = new char[n + 1];
  for (int i = 0; i < n; i++)
  {
    c[i] = dna[i];
  }
  for (int i = 0; i < n; i++)
  {
    cout << c[i] << " ";
  }

  int combinaciones = factorial(n);

  string *array = new string[combinaciones];
  int size = 0;

  cout << "\nTodas las permutaciones posibles: " << combinaciones << endl;
  generarPermutaciones(c, n, 0, array, size);

  cout << "Total de permutaciones validas: " << size << endl;
  cout << "Permutaciones:" << endl;
  for (int i = 0; i < size; i++)
  {
    cout << array[i] << endl;
  }

  delete[] c;      // Free the allocated memory
  c = nullptr;     // Avoid dangling pointer
  delete[] array;  // Free the allocated memory for permutations
  array = nullptr; // Avoid dangling pointer
  cout << "original: " << dna << " reverse: " << reverse(dna) << endl;
  return 0;
}
