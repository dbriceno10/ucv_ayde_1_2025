#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Daniel Briceno y Jose Alberto Perez Jimenez C1 AyD

const int MAX_NUMORIS = 1000;
const int MAX_PISOS = 1000;
const int MAX_NUMEROS = 10;
const int MAX_EQUIPO = 6;
string primerElementoTorre = "";
float vidaTorre = 0;
float vidaPiso = 0;
string mejorEquipo = "";
int valorMejorEquipo = 0;
int mejorBajas = 0;
float mejorDamage = 0;

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
  file.open(filename, ios::in);
  if (file.is_open())
  {
    int n;
    // obteneos el numero de numoris en la db
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
    }
    file.close();
    return n;
  }
  else
  {
    cout << "Error al abrir el archivo " << filename << endl;
    return -1;
  }
}

// Leer un archivo TorreX.in
int leerTorre(int numTorre, string pisos[])
{
  ifstream file;
  file.open("Torre" + to_string(numTorre) + ".in", ios::in);
  if (file.is_open())
  {
    int n;
    string line;
    getline(file, line);
    // primero obtenemos el numero de pisos en la torre
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
    return -1;
  }
}

// convertir a Mayusculas, para normalizar el tipo de elemento
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

// Calcular el damage
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
      numero += linea[i]; // va acumulando los di­gitos del numoris
    }
    else if (!numero.empty())
    {
      numeros[cantidad++] = stoi(numero); // convierte el string a entero
      numero = "";                        // limpia para el proximo numoris
    }
  }
  return cantidad; // devuelve la cantidad de numoris encontrados
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
      // cout << "No se encontro el Numoris con ID: " << ids[i] << endl;
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

bool EsApto(Numer retadores[], Numer numoris[], int ids[], int max)
{
  int sumaRetadores = 0;

  for (int i = 0; i < max; i++)
  {
    sumaRetadores += retadores[i].life;
  }

  int comparador = numoris[1].life + numoris[2].life + numoris[3].life + numoris[4].life + numoris[5].life + numoris[6].life;

  if (sumaRetadores >= comparador)
  {
    return true;
  }

  return false;
}

bool combate(string equipo, string torre[], int pisos, Numer numoris[], int &contadorBajas, float &acumDamage)
{
  // torre es un array de strings, tiene la forma {"1", "1 1"} se itera por cada posicion la cual es el piso, se lee el string para recuperar los ids y armar a los defensores de cada piso
  int idsRetadores[MAX_EQUIPO];
  // obtenermos al elquipo, 6 integrantes
  int maxRetadores = dividirEnNumeros(equipo, idsRetadores);
  Numer retadores[MAX_EQUIPO];
  // armar equipo
  obtenerNumoris(retadores, numoris, idsRetadores, maxRetadores);
  // pequena poda para verificar si el equipo es apto para recorrer el piso
  // if (EsApto(retadores, numoris, idsRetadores, maxRetadores))
  // {
    // recorrer los pisos
    for (int i = 0; i < pisos; i++)
    {
      int idsPiso[MAX_NUMEROS];
      int cantidad = dividirEnNumeros(torre[i], idsPiso);
      Numer defensoresPiso[MAX_NUMEROS];
      // armar defensores
      obtenerNumoris(defensoresPiso, numoris, idsPiso, cantidad);
      // iteramos en el piso, los malos empiezan en cada piso
      string turno = "malos";
      for (int j = 0; j < cantidad;)
      {
        // obtenemos a los retadores
        int index = obtenerNumerActo(retadores, maxRetadores);
        if (index == -1)
        {
          return false;
        }
        else
        {
          // combate en piso
          while (retadores[index].life > 0 && defensoresPiso[j].life > 0)
          {
            if (turno == "malos")
            {
              defensoresPiso[j].life -= calcularDano(retadores[index], defensoresPiso[j]);
              turno = "buenos";
            }
            else
            {
              const float damage = calcularDano(defensoresPiso[j], retadores[index]);
              retadores[index].life -= damage;
              acumDamage += damage;
              turno = "malos";
            }
            if (defensoresPiso[j].life <= 0)
            {
              defensoresPiso[j].life = 0;
              turno = "buenos";
            }
            if (retadores[index].life <= 0)
            {
              retadores[index].life = 0;
              turno = "malos";
              contadorBajas++;
            }
          }
          if (defensoresPiso[j].life <= 0)
          {
            j++;
          }
        }
      }
    // }
  }
  return true;
}

// Generar Equipos
void generarEquipos(int idsNumoris[], int numNumoris, int index, int seleccionados, int equipo[], string torre[], int pisos, Numer numoris[])
{
  if (seleccionados == 6)
  {
    // Construir string del equipo
    string salida = "";
    for (int i = 0; i < 6; i++)
    {
      salida += to_string(equipo[i]);
      if (i < 5)
        salida += " ";
    }
    int contadorBajas = 0;
    float acumDamage = 0;
    if (combate(salida, torre, pisos, numoris, contadorBajas, acumDamage))
    {
      // encontramos al primer ganador
      if (mejorEquipo == "" && valorMejorEquipo == 0 && mejorBajas == 0 && mejorDamage == 0)
      {
        mejorEquipo = salida;
        for (int i = 0; i < 6; i++)
        {
          valorMejorEquipo += equipo[i];
        }
        mejorBajas = contadorBajas;
        mejorDamage = acumDamage;
      }
      else
      {
        // validamos si el nuevo ganador supera al mejor
        if (contadorBajas < mejorBajas && acumDamage < mejorDamage)
        {
          mejorEquipo = salida;
          mejorBajas = contadorBajas;
          mejorDamage = acumDamage;
          int valorActual = 0;
          for (int i = 0; i < 6; i++)
          {
            valorActual += equipo[i];
          }
          valorMejorEquipo = valorActual;
        }
        // si el ganador actual empata al anterior
        else if (contadorBajas == mejorBajas && acumDamage == mejorDamage)
        {
          int valorActual = 0;
          for (int i = 0; i < 6; i++)
          {
            valorActual += equipo[i];
          }
          // condicion desempate 1
          if (valorActual < valorMejorEquipo)
          {
            mejorEquipo = salida;
            valorMejorEquipo = valorActual;
            mejorBajas = contadorBajas;
            mejorDamage = acumDamage;
          }
          // condicion desempate 2
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
            // evaluar el numero formado por los ids
            if (stoi(idActual) < stoi(idMejor))
            {
              mejorEquipo = salida;
              valorMejorEquipo = valorActual;
              mejorBajas = contadorBajas;
              mejorDamage = acumDamage;
            }
          }
        }
      }
    }
    // salimos del nivel actual
    return;
  }
  if (index >= numNumoris)
  {
    // caso base, ya armamos las combinaciones
    return;
  }
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
  int numNumoris = leerNumorisDB("NumorisDB.in", numoris, idNumoris);
  if (numNumoris == -1)
  {
    return 0;
  }
  int torre;
  cin >> torre;
  int numTorres = leerTorre(torre, pisos);
  if (numTorres == -1)
  {
    return 0;
  }
  int equipo[MAX_EQUIPO];

  generarEquipos(idNumoris, numNumoris, 0, 0, equipo, pisos, numTorres, numoris);
  if (mejorEquipo != "")
  {
    cout << mejorEquipo << endl;
  }
  else
  {
    cout << 0 << endl;
  }
  return 0;
}