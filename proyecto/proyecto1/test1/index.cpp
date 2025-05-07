#include <iostream>
#include <fstream>
using namespace std;

const int MAX_NUMORIS = 100; // Máximo número de Numoris en la base de datos
const int MAX_PISOS = 10;    // Máximo número de pisos en la torre
const int MAX_EQUIPO = 6;    // Tamaño fijo del equipo

struct Numer {
    int id;
    char nombre[50];
    char tipo[10];
    int dmg;
    int life;
};

struct Piso {
    int numoris[MAX_NUMORIS];
    int cantidad;
};

// Función para comparar cadenas manualmente
bool compararCadenas(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false; // Las cadenas son diferentes
        }
        i++;
    }
    return str1[i] == '\0' && str2[i] == '\0'; // Verificar si ambas cadenas terminan al mismo tiempo
}

// Leer el archivo NumorisDB.in
int leerNumorisDB(const char* filename, Numer numoris[]) {
    ifstream file(filename);
    if (!file) {
        cout << "Error al abrir el archivo " << filename << endl;
        return 0;
    }

    int n;
    file >> n;
    for (int i = 0; i < n; i++) {
        file >> numoris[i].id >> numoris[i].nombre >> numoris[i].tipo >> numoris[i].dmg >> numoris[i].life;
    }
    return n;
}

// Leer el archivo TorreX.in
int leerTorre(const char* filename, Piso torre[]) {
    ifstream file(filename);
    if (!file) {
        cout << "Error al abrir el archivo " << filename << endl;
        return 0;
    }

    int n;
    file >> n;
    for (int i = 0; i < n; i++) {
        torre[i].cantidad = 0;
        while (file.peek() != '\n' && file >> torre[i].numoris[torre[i].cantidad]) {
            torre[i].cantidad++;
        }
    }
    return n;
}

// Calcular el daño entre dos Numoris considerando las reglas elementales
int calcularDanio(const Numer& atacante, const Numer& defensor) {
    if (compararCadenas(atacante.tipo, "Agua") && compararCadenas(defensor.tipo, "Fuego")) return atacante.dmg * 2;
    if (compararCadenas(atacante.tipo, "Fuego") && compararCadenas(defensor.tipo, "Tierra")) return atacante.dmg * 2;
    if (compararCadenas(atacante.tipo, "Tierra") && compararCadenas(defensor.tipo, "Aire")) return atacante.dmg * 2;
    if (compararCadenas(atacante.tipo, "Aire") && compararCadenas(defensor.tipo, "Agua")) return atacante.dmg * 2;

    if (compararCadenas(atacante.tipo, "Fuego") && compararCadenas(defensor.tipo, "Agua")) return atacante.dmg / 2;
    if (compararCadenas(atacante.tipo, "Tierra") && compararCadenas(defensor.tipo, "Fuego")) return atacante.dmg / 2;
    if (compararCadenas(atacante.tipo, "Aire") && compararCadenas(defensor.tipo, "Tierra")) return atacante.dmg / 2;
    if (compararCadenas(atacante.tipo, "Agua") && compararCadenas(defensor.tipo, "Aire")) return atacante.dmg / 2;

    return atacante.dmg; // Daño normal si no hay ventaja/desventaja
}

// Simular un combate entre dos Numoris
bool combate(Numer& atacante, Numer& defensor) {
    defensor.life -= calcularDanio(atacante, defensor);
    if (defensor.life <= 0) return true; // El defensor fue derrotado
    atacante.life -= calcularDanio(defensor, atacante);
    return atacante.life > 0; // Retorna si el atacante sigue vivo
}

// Simular un combate entre un equipo y un piso de la torre
bool simularCombate(Numer equipo[], int equipoTam, Numer piso[], int pisoTam) {
    int i = 0, j = 0;
    while (i < equipoTam && j < pisoTam) {
        if (combate(equipo[i], piso[j])) {
            j++; // El defensor del piso fue derrotado
        } else {
            i++; // El atacante del equipo fue derrotado
        }
    }
    return j == pisoTam; // Retorna true si el equipo derrotó a todos los Numoris del piso
}

// Generar todas las combinaciones de 6 Numoris
void generarCombinaciones(Numer numoris[], int n, Numer equipo[], int equipoTam, int index, int start, Numer mejorEquipo[], int& mejorSumaID) {
    if (equipoTam == MAX_EQUIPO) {
        // Calcular la suma de IDs del equipo actual
        int sumaID = 0;
        for (int i = 0; i < MAX_EQUIPO; i++) {
            sumaID += equipo[i].id;
        }

        // Actualizar el mejor equipo si la suma de IDs es menor
        if (sumaID < mejorSumaID) {
            mejorSumaID = sumaID;
            for (int i = 0; i < MAX_EQUIPO; i++) {
                mejorEquipo[i] = equipo[i];
            }
        }
        return;
    }

    for (int i = start; i < n; i++) {
        equipo[equipoTam] = numoris[i];
        generarCombinaciones(numoris, n, equipo, equipoTam + 1, index + 1, i + 1, mejorEquipo, mejorSumaID);
    }
}

int main() {
    Numer numoris[MAX_NUMORIS];
    Piso torre[MAX_PISOS];
    Numer mejorEquipo[MAX_EQUIPO];
    Numer equipo[MAX_EQUIPO];
    int mejorSumaID = 1e9;

    // Leer los archivos
    int numNumoris = leerNumorisDB("NumorisDB.in", numoris);
    int numPisos = leerTorre("Torre1.in", torre);
  // Imprimir el contenido de numoris
  cout << "Contenido de numoris:" << endl;
  for (int i = 0; i < numNumoris; i++) {
    cout << "ID: " << numoris[i].id 
       << ", Nombre: " << numoris[i].nombre 
       << ", Tipo: " << numoris[i].tipo 
       << ", Daño: " << numoris[i].dmg 
       << ", Vida: " << numoris[i].life << endl;
  }

  // Imprimir el contenido de torre
  cout << "Contenido de torre:" << endl;
  for (int i = 0; i < numPisos; i++) {
    cout << "Piso " << i + 1 << ": ";
    for (int j = 0; j < torre[i].cantidad; j++) {
      cout << torre[i].numoris[j] << " ";
    }
    cout << endl;
  }
    // Generar combinaciones y encontrar el mejor equipo
    generarCombinaciones(numoris, numNumoris, equipo, 0, 0, 0, mejorEquipo, mejorSumaID);

    // Imprimir el mejor equipo
    cout << "Mejor equipo:" << endl;
    for (int i = 0; i < MAX_EQUIPO; i++) {
        cout << mejorEquipo[i].id << " ";
    }
    cout << endl;

    return 0;
}