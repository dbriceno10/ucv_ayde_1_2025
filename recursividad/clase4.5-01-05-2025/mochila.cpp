#include <iostream>
using namespace std;

const int MAX_ITEMS = 100;

struct Item
{
  int valor;
  int peso;
};

struct Sol
{
  int valor;
  int peso;
  int index;
};

// Variables globales
int primera_solucion_valor = -1;
bool primera_solucion[MAX_ITEMS] = {false};
int total_soluciones = 0;
Sol soluciones[MAX_ITEMS] = {};

void imprimirSolucion(Item items[], int num_items, bool seleccion[], int valor, int peso)
{
  cout << "Items: ";
  int acum_valor = 0;
  int acum_peso = 0;
  for (int i = 0; i < num_items; i++)
  {
    if (seleccion[i])
    {
      cout << "Item" << i << " v:" << items[i].valor << ", p:" << items[i].peso << " ";
    }
  }
  cout << endl
       << endl;
}

// Versión 1: Encontrar la primera solución válida
void mochilaPrimeraSolucion(Item items[], int num_items, int capacidad, int index, int valor_actual, int peso_actual, bool seleccion_actual[])
{
  if (primera_solucion_valor != -1)
    return; // Ya encontramos la primera solución

  if (peso_actual > capacidad)
    return;

  if (index == num_items)
  {
    // validación para validar un peso valido
    if (peso_actual <= capacidad && peso_actual > 0)
    {
      primera_solucion_valor = valor_actual;
      // cout << "Valor de primera solucion " << primera_solucion_valor << endl;
      // cout << "capacidad " << capacidad << endl;
      // cout << "peso_actual " << peso_actual << endl;
      for (int i = 0; i < num_items; i++)
      {
        // cout << "seleccion_actual[" << i << "]: " << seleccion_actual[i] << endl;
        primera_solucion[i] = seleccion_actual[i];
      }
    }
    return;
  }

  // No tomar el item
  seleccion_actual[index] = false;
  mochilaPrimeraSolucion(items, num_items, capacidad, index + 1, valor_actual, peso_actual, seleccion_actual);

  // Tomar el item
  seleccion_actual[index] = true;
  mochilaPrimeraSolucion(items, num_items, capacidad, index + 1, valor_actual + items[index].valor, peso_actual + items[index].peso, seleccion_actual);
}

// totaliza cada solucion y la guarda
void guardarSoluciones(Item items[], int num_items, bool seleccion_actual[], int total_soluciones)
{
  int acum_valor = 0;
  int acum_peso = 0;
  for (int k = 0; k < num_items; k++)
  {
    if (seleccion_actual[k])
    {
      acum_valor += items[k].valor;
      acum_peso += items[k].peso;
    }
  }
  soluciones[total_soluciones - 1] = {valor : acum_valor, peso : acum_peso, index : total_soluciones - 1};
  // cout << "cual es el index: " << total_soluciones - 1 << endl;
  // cout << "cual es el valor: " << acum_valor << endl;
  // cout << "cual es el peso: " << acum_peso << endl;
}

// imprimir cual es la mejor solucion
void mejorSolucion()
{
  int mejor = 0;
  for (int i = 1; i < total_soluciones; i++)
  {
    if (soluciones[i].peso > soluciones[mejor].peso)
    {
      mejor = i;
    }
    else if (soluciones[i].peso == soluciones[mejor].peso)
    {
      if (soluciones[i].valor > soluciones[mejor].valor)
      {
        mejor = i;
      }
    }
  }
  cout << "La mejor solucion es la #" << soluciones[mejor].index << "con un valor de " << soluciones[mejor].valor << " y un peso de " << soluciones[mejor].peso << endl;
}

// todas las soluciones válidas
void mochilaTodasSoluciones(Item items[], int num_items, int capacidad, int index, int valor_actual, int peso_actual, bool seleccion_actual[])
{
  if (peso_actual > capacidad)
    return;

  if (index == num_items)
  {
    if (peso_actual <= capacidad && peso_actual > 0)
    {
      total_soluciones++;
      cout << "Solución # " << total_soluciones << ":" << endl;

      // Procedemos a totalizar los valores de cada solucion y su posicion para guardarlo
      guardarSoluciones(items, num_items, seleccion_actual, total_soluciones - 1);
      imprimirSolucion(items, num_items, seleccion_actual, valor_actual, peso_actual);
    }
    return;
  }

  // No tomar el item
  seleccion_actual[index] = false;
  mochilaTodasSoluciones(items, num_items, capacidad, index + 1, valor_actual, peso_actual, seleccion_actual);

  // Tomar el item
  seleccion_actual[index] = true;
  mochilaTodasSoluciones(items, num_items, capacidad, index + 1, valor_actual + items[index].valor, peso_actual + items[index].peso, seleccion_actual);
}

int main()
{
  Item items[MAX_ITEMS] = {
      {valor : 60, peso : 10},
      {valor : 30, peso : 60},
      {valor : 25, peso : 24},
      {valor : 3, peso : 14}};
  int num_items = 4;
  int capacidad = 50;
  bool seleccion_actual[MAX_ITEMS] = {false}; // 0,,0,0

  // 1. Primera solución
  mochilaPrimeraSolucion(items, num_items, capacidad, 0, 0, 0, seleccion_actual);
  if (primera_solucion_valor != -1)
  {
    imprimirSolucion(items, num_items, primera_solucion, primera_solucion_valor, capacidad);
  }

  // 2. Encontrar todas las soluciones
  cout << "\nBUSCANDO TODAS LAS SOLUCIONES...\n";
  total_soluciones = 0;
  mochilaTodasSoluciones(items, num_items, capacidad, 0, 0, 0, seleccion_actual);
  cout << "Total de soluciones válidas: " << total_soluciones << "\n\n";
  mejorSolucion();
  return 0;
}