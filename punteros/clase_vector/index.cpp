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
  if (length <= 0)
  {
    cout << "[]" << endl;
  }
  else
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
}

class IntVector
{
public:
  int *data;
  int size;

public:
  IntVector(int length)
  {
    data = new int[length];
    size = length;
  }
  ~IntVector()
  {
    delete[] data;
    size = 0;
  }

  int push(int element)
  {
    int *aux = new int[size + 1];
    for (int i = 0; i < size; i++)
    {
      aux[i] = data[i];
    }
    aux[size] = element;
    delete[] data;
    data = aux;
    size++;
    return size;
  }

  int shift()
  {
    if (size - 1 < 0)
    {
      return 0;
    }
    else
    {
      int *aux = new int[size - 1];
      int element = data[0];
      for (int i = 1; i < size; i++)
      {
        aux[i - 1] = data[i];
      }
      delete[] data;
      data = aux;
      size--;
      return element;
    }
  }

  int pop()
  {
    if (size - 1 < 0)
    {
      return 0;
    }
    else
    {
      int *aux = new int[size - 1];
      int element = data[size - 1];
      for (int i = 0; i < size; i++)
      {
        aux[i] = data[i];
      }
      delete[] data;
      aux[size] = element;
      data = aux;
      size--;
      return element;
    }
  }

  int unshift(int element)
  {
    int *aux = new int[size + 1];
    for (int i = 1; i <= size; i++)
    {
      aux[i] = data[i - 1];
    }
    aux[0] = element;
    delete[] data;
    data = aux;
    size++;
    return size;
  }

  void sort()
  {
    for (int i = 0; i < size - 1; i++)
    {
      for (int j = i + 1; j < size; j++)
      {
        if (data[i] > data[j])
        {
          int temp = data[i];
          data[i] = data[j];
          data[j] = temp;
        }
      }
    }
  }

  void forEach(void (*func)(int &))
  {
    for (int i = 0; i < size; i++)
    {
      func(data[i]);
    }
  }

  IntVector map(int (*func)(int))
  {
    IntVector newVec(size);
    for (int i = 0; i < size; i++)
    {
      newVec.data[i] = func(data[i]);
    }
    return newVec;
  }
};

int main()
{
  // srand(time(0)); //* Inicializa la semilla solo una vez, es para que en cada ejecucion random pueda generar numeros diferentes
  // int *array = nullptr, n = 0;
  // cout << "Tamanio del array" << endl;
  // cin >> n;
  // initializeArr(array, n);
  // int *copy = new int[n];
  // for (int i = 0; i < n; i++)
  // {
  //   copy[i] = array[i];
  // }
  // cout << "array" << endl;
  // printArray(array, n);
  // delete[] array;
  IntVector vec(0);
  int opcion;
  do
  {
    cout << "\n--- MENU ---\n";
    cout << "1. Agregar un elemento al final de la lista\n";
    cout << "2. Quitar el primer elemento de la lista\n";
    cout << "3. Quitar el ultimo elemento de la lista\n";
    cout << "4. Agregar un elemento al princio de la lista\n";
    cout << "9. Salir\n";
    cout << "Seleccione una opción: ";
    cin >> opcion;

    if (opcion == 1)
    {
      int valor;
      cout << "Ingrese el valor a agregar: ";
      cin >> valor;
      vec.push(valor);
      cout << "Valor agregado.\n";
      printArray(vec.data, vec.size);
    }
    else if (opcion == 2)
    {
      int valor = vec.shift();
      cout << "El valor obtenido es " << valor << endl;
      printArray(vec.data, vec.size);
    }
    else if (opcion == 3)
    {
      int valor = vec.pop();
      cout << "El valor obtenido es " << valor << endl;
      printArray(vec.data, vec.size);
    }
    if (opcion == 4)
    {
      int valor;
      cout << "Ingrese el valor a agregar: ";
      cin >> valor;
      vec.unshift(valor);
      cout << "Valor agregado.\n";
      printArray(vec.data, vec.size);
    }
    else if (opcion == 9)
    {
      cout << "Saliendo...\n";
    }
    else
    {
      cout << "Opción no válida.\n";
    }
  } while (opcion != 9);
  return 0;
}