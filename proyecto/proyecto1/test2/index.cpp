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
  char nombre[50];
  char tipo[10];
  int dmg;
  int life;
};

struct Piso
{
  int numoris[MAX_NUMORIS];
  int cantidad;
};

struct Torre
{
  Piso pisos[MAX_PISOS];
  int cantidadPisos;
};

// Función para comparar cadenas manualmente
bool compararCadenas(const char *str1, const char *str2)
{
  int i = 0;
  while (str1[i] != '\0' && str2[i] != '\0')
  {
    if (str1[i] != str2[i])
    {
      return false; // Las cadenas son diferentes
    }
    i++;
  }
  return str1[i] == '\0' && str2[i] == '\0'; // Verificar si ambas cadenas terminan al mismo tiempo
}

// Leer el archivo NumorisDB.in
int leerNumorisDB(const char *filename, Numer numoris[])
{
  ifstream file(filename);
  if (!file)
  {
    cout << "Error al abrir el archivo " << filename << endl;
    return 0;
  }

  int n;
  file >> n;
  for (int i = 0; i < n; i++)
  {
    file >> numoris[i].id >> numoris[i].nombre >> numoris[i].tipo >> numoris[i].dmg >> numoris[i].life;
  }
  return n;
}

// Leer un archivo TorreX.in
int leerTorre(const char *filename, Piso torre[])
{
  ifstream file(filename);
  if (!file)
  {
    return 0; // Retorna 0 si no se puede abrir el archivo
  }

  int n;
  file >> n;
  for (int i = 0; i < n; i++)
  {
    torre[i].cantidad = 0;
    while (file.peek() != '\n' && file >> torre[i].numoris[torre[i].cantidad])
    {
      torre[i].cantidad++;
    }
  }
  return n;
}

// Leer todas las torres disponibles (Torre1.in, Torre2.in, ...)
int leerTodasLasTorres(Torre torres[])
{
  int cantidadTorres = 0;

  for (int i = 1; i <= MAX_TORRES; i++)
  {
    // Construir el nombre del archivo TorreX.in
    string filename = "Torre" + to_string(i) + ".in";

    Piso pisos[MAX_PISOS];
    int cantidadPisos = leerTorre(filename.c_str(), pisos);
    if (cantidadPisos == 0)
    {
      break; // Detenerse si no se puede abrir el archivo
    }

    // Copiar los pisos leídos a la estructura Torre
    torres[cantidadTorres].cantidadPisos = cantidadPisos;
    for (int j = 0; j < cantidadPisos; j++)
    {
      torres[cantidadTorres].pisos[j] = pisos[j];
    }
    cantidadTorres++;
  }
  return cantidadTorres;
}

// Calcular el daño entre dos Numoris considerando las reglas elementales
int calcularDanio(const Numer &atacante, const Numer &defensor)
{
  if (compararCadenas(atacante.tipo, "Agua") && compararCadenas(defensor.tipo, "Fuego"))
    return atacante.dmg * 2;
  if (compararCadenas(atacante.tipo, "Fuego") && compararCadenas(defensor.tipo, "Tierra"))
    return atacante.dmg * 2;
  if (compararCadenas(atacante.tipo, "Tierra") && compararCadenas(defensor.tipo, "Aire"))
    return atacante.dmg * 2;
  if (compararCadenas(atacante.tipo, "Aire") && compararCadenas(defensor.tipo, "Agua"))
    return atacante.dmg * 2;

  if (compararCadenas(atacante.tipo, "Fuego") && compararCadenas(defensor.tipo, "Agua"))
    return atacante.dmg / 2;
  if (compararCadenas(atacante.tipo, "Tierra") && compararCadenas(defensor.tipo, "Fuego"))
    return atacante.dmg / 2;
  if (compararCadenas(atacante.tipo, "Aire") && compararCadenas(defensor.tipo, "Tierra"))
    return atacante.dmg / 2;
  if (compararCadenas(atacante.tipo, "Agua") && compararCadenas(defensor.tipo, "Aire"))
    return atacante.dmg / 2;

  return atacante.dmg; // Daño normal si no hay ventaja/desventaja
}

int main()
{
  Numer numoris[MAX_NUMORIS];
  Torre torres[MAX_TORRES];
  int numNumoris = leerNumorisDB("NumorisDB.in", numoris);
  int numTorres = leerTodasLasTorres(torres);

  // Imprimir el contenido de numoris
  cout << "Contenido de numoris:" << endl;
  for (int i = 0; i < numNumoris; i++)
  {
    cout << "ID: " << numoris[i].id
         << ", Nombre: " << numoris[i].nombre
         << ", Tipo: " << numoris[i].tipo
         << ", Daño: " << numoris[i].dmg
         << ", Vida: " << numoris[i].life << endl;
  }

  // Imprimir el contenido de las torres
  cout << "\nContenido de las torres:" << endl;
  for (int i = 0; i < numTorres; i++)
  {
    cout << "Torre " << i + 1 << " (" << torres[i].cantidadPisos << " pisos):" << endl;
    for (int j = 0; j < torres[i].cantidadPisos; j++)
    {
      cout << "  Piso " << j + 1 << ": ";
      for (int k = 0; k < torres[i].pisos[j].cantidad; k++)
      {
        cout << torres[i].pisos[j].numoris[k] << " ";
      }
      cout << endl;
    }
  }

  return 0;
}