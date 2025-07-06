#include <iostream>
#include <string>
using namespace std;

// Ejemplo de struct
struct Persona
{
  string nombre;
  int edad;
};

// Ejemplo de clase
class Punto
{
public:
  float x, y;
  Punto(float x = 0, float y = 0) : x(x), y(y) {}
  void mostrar() { cout << "(" << x << ", " << y << ")" << endl; }
};

enum Color { ROJO, VERDE, AZUL };

void fn1()
{
  // Tipos de datos básicos
  int entero = 10;
  float flotante = 3.14f;
  double doble = 2.71828;
  char caracter = 'A';
  bool booleano = true;
  short corto = 100;
  long largo = 100000L;
  unsigned int uentero = 42u;

  cout << "int: " << entero << endl;
  cout << "float: " << flotante << endl;
  cout << "double: " << doble << endl;
  cout << "char: " << caracter << endl;
  cout << "bool: " << booleano << endl;
  cout << "short: " << corto << endl;
  cout << "long: " << largo << endl;
  cout << "unsigned int: " << uentero << endl;

  // Arreglos
  int arr[5] = {1, 2, 3, 4, 5};
  cout << "Arreglo de int: ";
  for (int i = 0; i < 5; i++)
    cout << arr[i] << " ";
  cout << endl;

  // Matriz (arreglo bidimensional)
  float matriz[2][3] = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}};
  cout << "Matriz de float:" << endl;
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 3; j++)
      cout << matriz[i][j] << " ";
    cout << endl;
  }

  // Struct
  Persona p1 = {"Ana", 20};
  cout << "Struct Persona: " << p1.nombre << ", " << p1.edad << endl;

  // Clase
  Punto pt(5.5, 7.7);
  cout << "Clase Punto: ";
  pt.mostrar();

  // Arreglo de apuntadores
  int a = 10, b = 20, c = 30;
  int *parr[3] = {&a, &b, &c};
  cout << "Arreglo de apuntadores a int: ";
  for (int i = 0; i < 3; i++)
    cout << *parr[i] << " ";
  cout << endl;

  // Matriz de apuntadores
  int x = 1, y = 2, z = 3, w = 4;
  int *mptr[2][2] = {{&x, &y}, {&z, &w}};
  cout << "Matriz de apuntadores a int:" << endl;
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
      cout << *mptr[i][j] << " ";
    cout << endl;
  }
}

void fn2()
{
  // Variable string
  string saludo = "Hola mundo";
  cout << "String: " << saludo << endl;

  // Arreglo de string
  string dias[3] = {"Lunes", "Martes", "Miercoles"};
  cout << "Arreglo de string: ";
  for (int i = 0; i < 3; i++)
    cout << dias[i] << " ";
  cout << endl;

  // Matriz de string
  string matriz[2][2] = {{"uno", "dos"}, {"tres", "cuatro"}};
  cout << "Matriz de string:" << endl;
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
      cout << matriz[i][j] << " ";
    cout << endl;
  }

  // Arreglo de apuntadores a string
  string s1 = "A";
  string s2 = "B";
  string s3 = "C";
  string *sparr[3] = {&s1, &s2, &s3};
  cout << "Arreglo de apuntadores a string: ";
  for (int i = 0; i < 3; i++)
    cout << *sparr[i] << " ";
  cout << endl;

  // Matriz de apuntadores a string
  string sa = "X", sb = "Y", sc = "Z", sd = "W";
  string *smat[2][2] = {{&sa, &sb}, {&sc, &sd}};
  cout << "Matriz de apuntadores a string:" << endl;
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
      cout << *smat[i][j] << " ";
    cout << endl;
  }
}

void fn3()
{
  // ...existing code...

  // Enum
  Color colorFavorito = VERDE;
  cout << "Enum Color: ";
  switch (colorFavorito)
  {
    case ROJO: cout << "Rojo"; break;
    case VERDE: cout << "Verde"; break;
    case AZUL: cout << "Azul"; break;
  }
  cout << endl;

  // ...existing code...
}

int main(int argc, char const *argv[])
{
  fn1();
  cout << endl;
  fn2();
  cout << endl;
  fn3();
  return 0;
}
