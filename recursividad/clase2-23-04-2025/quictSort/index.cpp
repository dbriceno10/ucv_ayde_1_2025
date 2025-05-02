#include <iostream>

using namespace std;

// quick sort

void swap(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

void printArray(int array[], int length)
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

int contador = 0;

void quickSort(int arr[], int low, int high)
{
  contador++;
  if (low >= high)
  {
    cout << low << " >= " << high << endl;
    return;
  }

  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; ++j)
  {
    if (arr[j] < pivot)
    {
      ++i;
      swap(arr[i], arr[j]);
    }
  }

  swap(arr[i + 1], arr[high]);
  int aux = i + 1; // 4
  cout << "LLamado: " << contador << " Pivote: " << pivot << " Index: " << i << " Auxiliar: " << aux << endl;
  quickSort(arr, low, aux - 1);
  cout << "Izquierda" << endl;
  printArray(arr, 6);
  cout << "Izquierda" << endl;
  quickSort(arr, aux + 1, high);
  cout << "Derecha" << endl;
  printArray(arr, 6);
  cout << "Derecha" << endl;
}

int main()
{

  int arr[] = {10, 9, 3, 8, 5, 7};
  cout << "Arreglo sin ordenar" << endl;
  printArray(arr, 6);
  cout << "Arreglo sin ordenar" << endl;
  quickSort(arr, 0, 5);
  // for (int i = 0; i < 6; i++)
  // {
  //   cout << arr[i] << " ";
  // }
  cout << "Arreglo ordenado" << endl;
  printArray(arr, 6);
  cout << "Arreglo ordenado" << endl;
  return 0;
}