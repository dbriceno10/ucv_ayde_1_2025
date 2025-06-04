#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
using namespace std;

int randomFn(int min, int max)
{
  return min + rand() % (max - min + 1);
}

void initializeArr(int *&array, int n)
{
  array = new int[n];
  for (int i = 0; i < n - 1; i++)
  {
    // array[i] = random(); //esa funcion random existe solo en algunos compiladores
    array[i] = randomFn(0, n);
  }
}

void printArray(int *array, int length)
{
  cout << "[";
  for (int i = 0; i < length; i++)
  {
    if (i == length - 1)
    {
      cout << array[i] << "]" << endl;
    }
    else
    {
      cout << array[i] << ", ";
    }
  }
}

int main()
{
  srand(time(0)); //* Inicializa la semilla solo una vez, es para que en cada ejecucion random pueda generar numeros diferentes
  int *array = nullptr, n = 0;
  cout << "Tamanio del array" << endl;
  cin >> n;
  initializeArr(array, n);
  int *copy = new int[n];
  for (int i = 0; i < n; i++)
  {
    copy[i] = array[i];
  }
  cout << "array" << endl;
  printArray(array, n);
  delete[] array;
  cout << "copy" << endl;
  printArray(copy, n);
  delete[] copy;
  return 0;
}