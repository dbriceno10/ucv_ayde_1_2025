#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_NUMORIS = 100; // Máximo número de Numoris en la base de datos
const int MAX_PISOS = 10;    // Máximo número de pisos en cada torre
const int MAX_TORRES = 100;  // Máximo número de torres
const int MAX_EQUIPO = 6;    // Tamaño fijo del equipo

struct Numer
{
  int id;
  string nombre;
  string tipo;
  float dmg;
  float life;
};

struct Piso
{
  string numers;
  int piso;
};

// Leer el archivo NumorisDB.in
int leerNumorisDB(string filename, Numer numoris[])
{
  ifstream file;
  file.open(filename);
  if (file.is_open())
  {
    int n;
    file >> n;
    for (int i = 0; i < n; i++)
    {
      file >> numoris[i].id >> numoris[i].nombre >> numoris[i].tipo >> numoris[i].dmg >> numoris[i].life;
    }
    file.close();
    return n;
  }
  else
  {
    cout << "Error al abrir el archivo " << filename << endl;
    return 0;
  }
}

// Leer un archivo TorreX.in
int leerTorre(int numTorre, string pisos[])
{
  ifstream file;
  file.open("Torre" + to_string(numTorre) + ".in");
  if (file.is_open())
  {
    int n;
    string line;
    // file >> n;
    getline(file, line);
    n = stoi(line);
    for (int i = 0; i < n; i++)
    {
      getline(file, line);
      pisos[i] = line;
    }
    file.close();
    return n;
  }
  else
  {
    cout << "Error al abrir el archivo Torre" + to_string(numTorre) + ".in" << endl;
    return 0;
  }
}

int main()
{
  Numer numoris[MAX_NUMORIS];
  string pisos[MAX_PISOS];
  int numNumoris = leerNumorisDB("NumorisDB.in", numoris);
  cout << "Número de Numoris leídos: " << numNumoris << endl;
  cout << "Numero de archivo a leer" << endl;
  int torre;
  cin >> torre;
  int numTorres = leerTorre(torre, pisos);
  cout << "Número de Torres leídas: " << numTorres << endl;
  // Imprimir el contenido de numoris
  cout << "Contenido de Numoris:" << endl;
  for (int i = 0; i < numNumoris; i++)
  {
    cout << "ID: " << numoris[i].id << ", Nombre: " << numoris[i].nombre << ", Tipo: " << numoris[i].tipo
         << ", Daño: " << numoris[i].dmg << ", Vida: " << numoris[i].life << endl;
  }
  // Imprimir el contenido de pisos
  cout << "Contenido de Torres:" << endl;
  for (int i = 0; i < numTorres; i++)
  {
    // cout << "Piso " << i + 1 << ": " << pisos[i] << endl;
    for (int j = 0; j < pisos[i].length(); j++)
    {
      if (pisos[i][j] == ' ')
      {
        continue;
      }
      else
      {

        cout << "Piso " << i + 1 << ": " << pisos[i][j] << endl;
      }
    }
  }

  return 0;
}