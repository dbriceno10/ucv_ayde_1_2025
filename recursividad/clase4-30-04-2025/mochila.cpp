#include <iostream>

using namespace std;

const int MAX_ITEMS = 100;

struct Item
{
  int valor;
  int peso;
};

int primera_solucion_valor = -1;
bool primera_solucion[MAX_ITEMS] = {false}; // 1,0,1,1,1,0,0

void mochilaPrimeraSolucion(Item items[], int num_items, int capacidad, int index, int valor_actual,
                            int peso_actual, bool seleccion_actual[])
{

  if (primera_solucion_valor != -1)
  {
    return;
  }

  if (peso_actual > capacidad)
  {
    return;
  }

  /*if (== num_items) {

  }*/

  if (peso_actual <= capacidad)
  { // 0 <= 50
    primera_solucion_valor = valor_actual;
    for (int i = 0; i < num_items; ++i)
    {
      primera_solucion[i] = seleccion_actual[i];
    }
  }

  seleccion_actual[index] = false; // no agarre el item
  mochilaPrimeraSolucion(items, num_items, capacidad, index + 1, valor_actual,
                         peso_actual, seleccion_actual);
  seleccion_actual[index] = true; // Agarre el item
  mochilaPrimeraSolucion(items, num_items, capacidad, index + 1, valor_actual + items[index].valor,
                         peso_actual + items[index].peso, seleccion_actual);
}

void imprimirSolucion(Item items[], int num_items, int solucion)
{
}

int main()
{

  Item items[MAX_ITEMS] = {
      {60, 10},
      {30, 60},
      {25, 24},
      {3, 14}};

  int num_items = 4;
  int capacidad = 50;

  bool seleccion_actual[MAX_ITEMS] = {false}; // 0,0,0,0

  mochilaPrimeraSolucion(items, num_items, capacidad, 0, 0, 0, seleccion_actual);

  if (primera_solucion_valor != -1)
  {
    imprimirSolucion(items, num_items, primera_solucion_valor);
  }
}