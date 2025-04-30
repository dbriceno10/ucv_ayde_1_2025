#include <iostream>
#include <string>
using namespace std;

int binary(int n)
{
  if (n == 0)
  {
    return 0;
  }
  else
  {
    // return (n % 2 + 10 * binary(n / 2));
    const int resto = n % 2;
    const int cociente = n / 2;
    const int resultado = binary(cociente);
    const int binario = resto + 10 * resultado;
    return binario;
  }
}

string hex(int n)
{
  if (n == 0)
  {
    return "";
  }
  else
  {
    string numero = "";
    const int resto = n % 16;
    int cociente = n / 16;
    if (resto > 9)
    {
      if (resto == 10)
      {
        numero = "A";
      }
      if (resto == 11)
      {
        numero = "B";
      }
      if (resto == 12)
      {
        numero = "C";
      }
      if (resto == 13)
      {
        numero = "D";
      }
      if (resto == 14)
      {
        numero = "E";
      }
      if (resto == 15)
      {
        numero = "F";
      }
    }
    else
    {
      numero = numero + to_string(resto);
    }
    return hex(cociente) + numero;
  }
}

int main(int argc, char const *argv[])
{
  /* code */
  int n = 0, b = 0, h = 0;
  cout << "Introduce un numero decimal: " << endl;
  cin >> n;
  cout << "El numero binario es: " << binary(n) << endl;
  cout << "El numero hexadecimal es: " << hex(n) << endl;
  cout << "El numero decimal es: " << n << endl;
  return 0;
}
