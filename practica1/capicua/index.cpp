#include <iostream>

using namespace std;

string reverse(string palabra, int index)
{
  if (index > palabra.size() - 1)
  {
    return "";
  }
  else
  {
    char letra = palabra[index];
    return reverse(palabra, index + 1) + letra;
  }
}

void capicua(string palabra)
{
  string palabra_invertida = reverse(palabra, 0);
  if (palabra == palabra_invertida)
  {
    cout << "Es capicua" << endl;
  }
  else
  {
    cout << "No es capicua" << endl;
  }
  cout << palabra << " ----> " << palabra_invertida << endl;
}

int main(int argc, char const *argv[])
{
  /* code */
  string palabra = "";
  cout << "Introducir palabra" << endl;
  cin >> palabra;
  capicua(palabra);
  return 0;
}
