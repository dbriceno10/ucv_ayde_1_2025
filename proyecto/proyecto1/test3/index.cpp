#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_NUMORIS = 100; // Máximo número de Numoris en la base de datos
const int MAX_PISOS = 100;   // Máximo número de pisos en cada torre
const int MAX_NUMEROS = 10;  // Máximo número de números en una línea
const int MAX_EQUIPO = 6;    // Tamaño fijo del equipo

struct Elemento
{
  string agua;
  string fuego;
  string tierra;
  string aire;
};

const Elemento ELEMENTOS = {"AGUA", "FUEGO", "TIERRA", "AIRE"};

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

// convertir a Mayusculas
string toUpperCase(string s)
{
  for (int i = 0; i < s.length(); i++)
  {
    if (s[i] >= 'a' && s[i] <= 'z')
    {
      s[i] = s[i] - 'a' + 'A';
    }
  }
  return s;
}

// Calcular el daño
float calcularDano(Numer atacante, Numer defensor)
{
  if (toUpperCase(atacante.tipo) == ELEMENTOS.agua && toUpperCase(defensor.tipo) == ELEMENTOS.fuego)
  {
    return atacante.dmg * 2;
  }
  if (toUpperCase(atacante.tipo) == ELEMENTOS.fuego && toUpperCase(defensor.tipo) == ELEMENTOS.agua)
  {
    return atacante.dmg / 2;
  }
  if (toUpperCase(atacante.tipo) == ELEMENTOS.fuego && toUpperCase(defensor.tipo) == ELEMENTOS.tierra)
  {
    return atacante.dmg * 2;
  }
  if (toUpperCase(atacante.tipo) == ELEMENTOS.tierra && toUpperCase(defensor.tipo) == ELEMENTOS.fuego)
  {
    return atacante.dmg / 2;
  }
  if (toUpperCase(atacante.tipo) == ELEMENTOS.tierra && toUpperCase(defensor.tipo) == ELEMENTOS.aire)
  {
    return atacante.dmg * 2;
  }
  if (toUpperCase(atacante.tipo) == ELEMENTOS.aire && toUpperCase(defensor.tipo) == ELEMENTOS.tierra)
  {
    return atacante.dmg / 2;
  }
  if (toUpperCase(atacante.tipo) == ELEMENTOS.aire && toUpperCase(defensor.tipo) == ELEMENTOS.agua)
  {
    return atacante.dmg * 2;
  }
  if (toUpperCase(atacante.tipo) == ELEMENTOS.agua && toUpperCase(defensor.tipo) == ELEMENTOS.aire)
  {
    return atacante.dmg / 2;
  }
  return atacante.dmg;
}

int buscarNumber(int id, Numer numoris[], int numNumoris)
{
  for (int i = 0; i < numNumoris; i++)
  {
    if (numoris[i].id == id)
    {
      return i;
    }
  }
  return -1;
}

// generar equipo

string generarEquipo()
{
  return "2 1 3 4 5 6";
}

// combate
//  bool combate(string equipo, string piso) {
//    int idNumber, idEqupo;
//    for(int i = 0; i < piso.length(); i++) {
//      if(piso[i] == ' ') {
//        continue;
//      }
//      else {
//       idNumber = stoi(piso[i]);
//      }
//    }
//    return true;
//  }

int dividirEnNumeros(string linea, int numeros[])
{
  int n = linea.length();
  string numero = "";
  int cantidad = 0;

  for (int i = 0; i <= n; i++)
  {
    if (i < n && linea[i] != ' ')
    {
      numero += linea[i]; // va acumulando los dígitos del número
    }
    else if (!numero.empty())
    {
      numeros[cantidad++] = stoi(numero); // convierte el string a entero
      numero = "";                        // limpia para el próximo número
    }
  }
  return cantidad; // devuelve la cantidad de números encontrados
}

// obtener numores
void obtenerNumoris(Numer newNumoris[], Numer numoris[], int ids[], int max)
{
  for (int i = 0; i < max; i++)
  {
    int index = buscarNumber(ids[i], numoris, MAX_NUMORIS);
    if (index != -1)
    {
      // cout << "Encontrado el Numoris con ID: " << ids[i] << endl;
      newNumoris[i] = numoris[index];
    }
    else
    {
      cout << "No se encontró el Numoris con ID: " << ids[i] << endl;
    }
  }
}

// obtener el primer miembro del equipo en condiciones de combatir
int obtenerNumerActo(Numer retadores[], int max)
{
  for (int i = 0; i < max; i++)
  {
    if (retadores[i].life > 0)
    {
      return i;
    }
  }
  return -1; // si no hay miembros en condiciones de combatir
}

bool combate(string equipo, string torre[], int pisos, Numer numoris[])
{
  int idsRetadores[MAX_EQUIPO];
  int maxRetadores = dividirEnNumeros(equipo, idsRetadores);
  Numer retadores[MAX_EQUIPO];
  // armar equipo
  obtenerNumoris(retadores, numoris, idsRetadores, maxRetadores);
  // recorrer los pisos
  for (int i = 0; i < pisos; i++)
  {
    int idsPiso[MAX_NUMEROS];
    int cantidad = dividirEnNumeros(torre[i], idsPiso);
    Numer defensoresPiso[MAX_NUMEROS];
    // armar defensores
    obtenerNumoris(defensoresPiso, numoris, idsPiso, cantidad);
    // cout <<"idsPiso: " << torre[i] << endl;
    // iteramos en el piso
    string turno = "malos";
    for (int j = 0; j < cantidad; j++)
    {
      // cout << "Defensor: " << defensoresPiso[j].nombre << endl;
      // obtenemos al malo
      int index = obtenerNumerActo(retadores, maxRetadores);
      if (index == -1)
      {
        return false;
      }
      else
      {
        // combate en piso actual
        while (retadores[index].life > 0 && defensoresPiso[j].life > 0)
        {
          if (turno == "malos")
          {
            defensoresPiso[j].life -= calcularDano(retadores[index], defensoresPiso[j]);
            cout << "El daño de " << retadores[index].nombre << " a " << defensoresPiso[j].nombre << " es: " << calcularDano(retadores[index], defensoresPiso[j]) << endl;
            turno = "buenos";
          }
          else
          {
            retadores[index].life -= calcularDano(defensoresPiso[j], retadores[index]);
            cout << "El daño de " << defensoresPiso[j].nombre << " a " << retadores[index].nombre << " es: " << calcularDano(defensoresPiso[j], retadores[index]) << endl;
            turno = "malos";
          }
          if (defensoresPiso[j].life <= 0)
          {
            cout << "El defensor " << defensoresPiso[j].nombre << " ha sido derrotado." << endl;
            turno = "buenos";
          }
          if (retadores[index].life <= 0)
          {
            turno = "malos";
          }
        }
      }
    }

    // for (int j = 0; j < cantidad; j++)
    // {
    //   int index = buscarNumber(idsPiso[j], numoris, MAX_NUMORIS);
    //   Numer defensor = numoris[index];
    //   for (int k = 0; k < MAX_EQUIPO; k++)
    //   {
    //     Numer atacante = arrEquipo[k];
    //     float dano = calcularDano(atacante, defensor);
    //     cout << "El daño de " << atacante.nombre << " a " << defensor.nombre << " es: " << dano << endl;
    //   }
    // }
  }
  return true;
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
    // for (int j = 0; j < pisos[i].length(); j++)
    // {
    //   if (pisos[i][j] == ' ')
    //   {
    //     continue;
    //   }
    //   else
    //   {
    //     int contador = 0;
    //     cout << "Piso " << i + 1 << ": " << pisos[i][j] << endl;
    //   }
    // }
    int numeros[10];
    int cantidad = dividirEnNumeros(pisos[i], numeros);
    cout << "Piso " << i + 1 << ": ";
    for (int j = 0; j < cantidad; j++)
    {
      cout << numeros[j] << " ";
    }
    cout << endl;
  }
  cout << (combate(generarEquipo(), pisos, numTorres, numoris) ? "Ganamos" : "Perdimos") << endl;
  return 0;
}