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
  string water;
  string fire;
  string earth;
  string air;
};

const Elemento ELEMENTOS = {"AGUA", "FUEGO", "TIERRA", "AIRE"};

struct Numer
{
  int id;
  string name;
  string type;
  float damage;
  float life;
};

// Leer el archivo NumorisDB.in
int leerNumorisDB(string filename, Numer numoris[], int idNumoris[])
{
  ifstream file;
  file.open(filename);
  if (file.is_open())
  {
    int n;
    file >> n;
    for (int i = 0; i < n; i++)
    {
      int id;
      string name, type;
      float damage, life;
      file >> id >> name >> type >> damage >> life;
      numoris[i].id = id;
      numoris[i].name = name;
      numoris[i].type = type;
      numoris[i].damage = damage;
      numoris[i].life = life;
      idNumoris[i] = id;
      // file >> numoris[i].id >> numoris[i].name >> numoris[i].type >> numoris[i].damage >> numoris[i].life;
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
  if (toUpperCase(atacante.type) == ELEMENTOS.water && toUpperCase(defensor.type) == ELEMENTOS.fire)
  {
    return atacante.damage * 2;
  }
  if (toUpperCase(atacante.type) == ELEMENTOS.fire && toUpperCase(defensor.type) == ELEMENTOS.water)
  {
    return atacante.damage / 2;
  }
  if (toUpperCase(atacante.type) == ELEMENTOS.fire && toUpperCase(defensor.type) == ELEMENTOS.earth)
  {
    return atacante.damage * 2;
  }
  if (toUpperCase(atacante.type) == ELEMENTOS.earth && toUpperCase(defensor.type) == ELEMENTOS.fire)
  {
    return atacante.damage / 2;
  }
  if (toUpperCase(atacante.type) == ELEMENTOS.earth && toUpperCase(defensor.type) == ELEMENTOS.air)
  {
    return atacante.damage * 2;
  }
  if (toUpperCase(atacante.type) == ELEMENTOS.air && toUpperCase(defensor.type) == ELEMENTOS.earth)
  {
    return atacante.damage / 2;
  }
  if (toUpperCase(atacante.type) == ELEMENTOS.air && toUpperCase(defensor.type) == ELEMENTOS.water)
  {
    return atacante.damage * 2;
  }
  if (toUpperCase(atacante.type) == ELEMENTOS.water && toUpperCase(defensor.type) == ELEMENTOS.air)
  {
    return atacante.damage / 2;
  }
  return atacante.damage;
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

void swap(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

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
    // cout << "Piso " << i + 1 << endl;
    for (int j = 0; j < cantidad;)
    {
      // cout << "Defensor: " << defensoresPiso[j].name << endl;
      // obtenemos al malo
      int index = obtenerNumerActo(retadores, maxRetadores);
      if (index == -1)
      {
        return false;
      }
      else
      {
        // combate en piso
        // cout << "El retador " << retadores[index].name << "(" << retadores[index].life << ")" << " está combatiendo en contra del defensor " << defensoresPiso[j].name << "(" << defensoresPiso[j].life << ")" << endl;

        while (retadores[index].life > 0 && defensoresPiso[j].life > 0)
        {
          if (turno == "malos")
          {
            defensoresPiso[j].life -= calcularDano(retadores[index], defensoresPiso[j]);
            // cout << "El daño de " << retadores[index].name << " a " << defensoresPiso[j].name << " es: " << calcularDano(retadores[index], defensoresPiso[j]) << endl;
            turno = "buenos";
          }
          else
          {
            retadores[index].life -= calcularDano(defensoresPiso[j], retadores[index]);
            // cout << "El daño de " << defensoresPiso[j].name << " a " << retadores[index].name << " es: " << calcularDano(defensoresPiso[j], retadores[index]) << endl;
            turno = "malos";
          }
          if (defensoresPiso[j].life <= 0)
          {
            // cout << "El defensor " << defensoresPiso[j].name << " ha sido derrotado." << endl;
            defensoresPiso[j].life = 0;
            turno = "buenos";
            // j++;
          }
          if (retadores[index].life <= 0)
          {
            // cout << "El retador " << retadores[index].name << " ha sido derrotado." << endl;
            retadores[index].life = 0;
            turno = "malos";
          }
          // cout << "Ronda terminada" << endl;
          // cout << "Vida del Malo " << retadores[index].name << ": " << retadores[index].life << endl;
          // cout << "Vida de Bueno " << defensoresPiso[j].name << ": " << defensoresPiso[j].life << endl;
        }
        if (defensoresPiso[j].life <= 0)
        {
          j++;
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
    //     cout << "El daño de " << atacante.name << " a " << defensor.name << " es: " << dano << endl;
    //   }
    // }
  }
  return true;
}

// Generar Equipos
int combinaciones = 0;
int ganadores = 0;
string mejorEquipo = "";
int valorMejorEquipo = 0;
void generarEquipos(int idsNumoris[], int numNumoris, int index, int seleccionados, int equipo[], string torre[], int pisos, Numer numoris[])
{
  if (seleccionados == 6)
  {
    combinaciones++;
    // Construir string de salida
    string salida = "";
    for (int i = 0; i < 6; i++)
    {
      salida += to_string(equipo[i]);
      if (i < 5)
        salida += " ";
    }
    // cout << salida << endl;
    if (combate(salida, torre, pisos, numoris))
    {

      ganadores++;
      cout << "Ganamos con el equipo: " << salida << endl;
      if (mejorEquipo == "" && valorMejorEquipo == 0)
      {
        mejorEquipo = salida;
        for (int i = 0; i < 6; i++)
        {
          valorMejorEquipo += equipo[i];
        }
      }
      else
      {
        int valorActual = 0;
        for (int i = 0; i < 6; i++)
        {
          valorActual += equipo[i];
        }
        if (valorActual < valorMejorEquipo)
        {
          mejorEquipo = salida;
          valorMejorEquipo = valorActual;
        }
        else if (valorActual == valorMejorEquipo)
        {
          int arrayMejorEquipo[6];
          dividirEnNumeros(mejorEquipo, arrayMejorEquipo);
          string idMejor = "";
          string idActual = "";
          for (int i = 0; i < 6; i++)
          {
            idMejor = idMejor + to_string(arrayMejorEquipo[i]);
            idActual = idActual + to_string(equipo[i]);
          }
          if (stoi(idActual) < stoi(idMejor))
          {
            mejorEquipo = salida;
            valorMejorEquipo = valorActual;
          }
        }
      }
    }
    return;
  }
  if (index >= numNumoris)
    return;

  // Para cada posición desde idx hasta n-1, intercambia y selecciona
  for (int i = index; i < numNumoris; i++)
  {
    swap(idsNumoris[index], idsNumoris[i]);
    equipo[seleccionados] = idsNumoris[index];
    generarEquipos(idsNumoris, numNumoris, index + 1, seleccionados + 1, equipo, torre, pisos, numoris);
    swap(idsNumoris[index], idsNumoris[i]);
  }
}

int main()
{
  Numer numoris[MAX_NUMORIS];
  int idNumoris[MAX_NUMORIS];
  string pisos[MAX_PISOS];
  int numNumoris = leerNumorisDB("NumorisDB2.in", numoris, idNumoris);
  cout << "Número de Numoris leídos: " << numNumoris << endl;
  cout << "Numero de archivo a leer" << endl;
  int torre;
  cin >> torre;
  int numTorres = leerTorre(torre, pisos);
  // cout << "Número de Torres leídas: " << numTorres << endl;
  // // Imprimir el contenido de numoris
  // cout << "Contenido de Numoris:" << endl;
  // for (int i = 0; i < numNumoris; i++)
  // {
  //   cout << "ID: " << numoris[i].id << ", Nombre: " << numoris[i].name << ", Tipo: " << numoris[i].type
  //        << ", Daño: " << numoris[i].damage << ", Vida: " << numoris[i].life << endl;
  // }
  // // Imprimir el contenido de pisos
  // cout << "Contenido de Torres:" << endl;
  // for (int i = 0; i < numTorres; i++)
  // {
  //   // cout << "Piso " << i + 1 << ": " << pisos[i] << endl;
  //   // for (int j = 0; j < pisos[i].length(); j++)
  //   // {
  //   //   if (pisos[i][j] == ' ')
  //   //   {
  //   //     continue;
  //   //   }
  //   //   else
  //   //   {
  //   //     int contador = 0;
  //   //     cout << "Piso " << i + 1 << ": " << pisos[i][j] << endl;
  //   //   }
  //   // }
  //   int numeros[10];
  //   int cantidad = dividirEnNumeros(pisos[i], numeros);
  //   cout << "Piso " << i + 1 << ": ";
  //   for (int j = 0; j < cantidad; j++)
  //   {
  //     cout << numeros[j] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << (combate(generarEquipo(), pisos, numTorres, numoris) ? "Ganamos" : "Perdimos") << endl;
  // generarEquipo(idNumoris, numNumoris, 0);
  int equipo[6];
  generarEquipos(idNumoris, numNumoris, 0, 0, equipo, pisos, numTorres, numoris);
  cout << "Total de combinaciones: " << combinaciones << endl;
  cout << "Total de ganadores: " << ganadores << endl;
  cout << "Mejor equipo: " << mejorEquipo << endl;
  return 0;
}