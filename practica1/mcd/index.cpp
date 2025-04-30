#include <iostream>

using namespace std;

// Función recursiva para calcular el MCD usando el algoritmo de Euclides
int mcd(int a, int b)
{
  if (b == 0)
  {
    return a; // Caso base: si el divisor es 0, el MCD es el dividendo
  }
  int resto = a % b;
  return mcd(b, resto); // Llamada recursiva con (b, a % b)
}

int main()
{
  int a, b;
  cout << "Ingrese el primer número: ";
  cin >> a;
  cout << "Ingrese el segundo número: ";
  cin >> b;

  cout << "El MCD de " << a << " y " << b << " es: " << mcd(a, b) << endl;

  return 0;
}