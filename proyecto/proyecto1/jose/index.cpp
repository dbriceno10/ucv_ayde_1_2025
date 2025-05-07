#include <iostream>
#include <fstream>

using namespace std;

// Hecho por José Alberto Pérez Jimenez C1 AyD

class numer
{
private:
  int id;
  string nombre;
  string tipo;
  int dmg;
  int life;

public:
  numer() : id(0), nombre(""), tipo(""), dmg(0), life(0) {}

  void setId(int id)
  {
    this->id = id;
  }

  void setNombre(string nombre)
  {
    this->nombre = nombre;
  }

  void setTipo(string tipo)
  {
    this->tipo = tipo;
  }

  void setDmg(int dmg)
  {
    this->dmg = dmg;
  }

  void setLife(int life)
  {
    this->life = life;
  }

  int getId()
  {
    return id;
  }

  string getNombre()
  {
    return nombre;
  }

  string getTipo()
  {
    return tipo;
  }

  int getDmg()
  {
    return dmg;
  }

  int getLife()
  {
    return life;
  }
};

int main()
{
  cout << "Proyecto #1 AyD" << endl;

  int n;

  ifstream archivo("NumorisDB.in");
  if (!archivo.is_open())
  {
    cout << "|| ARCHIVO NO ENCONTRADO ||" << endl;
    return 0;
  }

  archivo >> n;
  cout << n << endl;

  numer *Numoris = new numer[n];

  int num;
  string aux;

  for (int i = 0; i < n; i++)
  {
    archivo >> num;
    Numoris[i].setId(num);
    cout << Numoris[i].getId() << " ";

    archivo >> aux;
    Numoris[i].setNombre(aux);
    cout << Numoris[i].getNombre() << " ";

    archivo >> aux;
    Numoris[i].setTipo(aux);
    cout << Numoris[i].getTipo() << " ";

    archivo >> num;
    Numoris[i].setDmg(num);
    cout << Numoris[i].getDmg() << " ";

    archivo >> num;
    Numoris[i].setLife(num);
    cout << Numoris[i].getLife() << endl;
  }

  archivo.close();

  string u;
  cin >> u;
  string Torre_Nombre = "Torre" + u + ".in";
  ifstream archivo_torre(Torre_Nombre);

  if (!archivo_torre.is_open())
  {
    cout << "|| ARCHIVO NO ENCONTRADO ||" << endl;
    return 0;
  }

  archivo_torre >> n;
  cout << n << endl;

  int **enemigo = new int *[n];

  for (int i = 0; i < n; i++)
  {
    enemigo[i] = new int[10];
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      archivo_torre >> enemigo[i][j];
      cout << enemigo[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}