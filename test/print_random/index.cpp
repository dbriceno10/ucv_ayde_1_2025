#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
using namespace std;

void imprimirRandom(int cantidad, int minimo, int maximo)
{
  srand(time(0)); // Inicializa la semilla solo una vez
  for (int i = 0; i < cantidad; i++)
  {
    int num = minimo + rand() % (maximo - minimo + 1);
    cout << num << endl;
  }
}

int main()
{
  imprimirRandom(10, 1, 100); // Imprime 10 números aleatorios entre 1 y 100
  return 0;
}