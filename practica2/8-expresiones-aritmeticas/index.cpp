#include <iostream>
using namespace std;

const int MAX_N = 9;
char ops[] = {'+', '-', '*', '/'};

void printArray(char array[], int length)
{
  cout << "[";
  for (int i = 0; i < length; i++)
  {
    if (i == length - 1)
    {
      cout << array[i] << "]" << endl;
    }
    else
    {
      cout << array[i] << ", ";
    }
  }
}

void imprimirExpresion(int N, char expr[], int R)
{
  // Construir y evaluar la expresión de izquierda a derecha
  int res = 0;
  int curr = 1;
  int idx = 0;
  // Primer operador puede ser + o -
  if (expr[0] == '+')
    res = 1;
  else if (expr[0] == '-')
    res = -1;
  else
    return; // No permitir * o / como primer operador

  for (int i = 2; i <= N; i++)
  {
    idx = i - 1;
    if (expr[idx] == '+')
      res = res + i;
    else if (expr[idx] == '-')
      res = res - i;
    else if (expr[idx] == '*')
      res = res * i;
    else if (expr[idx] == '/')
    {
      if (i == 0 || res % i != 0)
        return; // Evitar división por cero y solo divisiones exactas
      res = res / i;
    }
  }
  if (res == R)
  {
    cout << "expresion" << endl;
    printArray(expr, N);
    // Imprimir la expresión
    cout << expr[0] << "1";
    for (int i = 2; i <= N; i++)
    {
      cout << " " << expr[i - 1] << i;
    }
    cout << " = " << R << endl;
  }
}

void backtrack(int N, int R, char expr[], int pos)
{
  if (pos == N)
  {
    imprimirExpresion(N, expr, R);
    return;
  }
  // Primer operador solo puede ser + o -
  int start = (pos == 0) ? 0 : 0;
  int end = (pos == 0) ? 2 : 4;
  for (int i = start; i < end; i++)
  {
    expr[pos] = ops[i];
    backtrack(N, R, expr, pos + 1);
  }
}

int main()
{
  int N, R;
  cout << "Ingrese N y R: ";
  cin >> N >> R;
  if (N < 1 || N > MAX_N)
  {
    cout << "N fuera de rango" << endl;
    return 1;
  }
  char expr[MAX_N] = {};
  backtrack(N, R, expr, 0);
  return 0;
}