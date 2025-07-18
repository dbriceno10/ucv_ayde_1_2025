#include <iostream>
using namespace std;

class Grafo
{
private:
  int **matrizAdyacencia;
  int numNodos;
  bool dirigido;

public:
  // Constructor
  Grafo(int n, bool d = false)
  {
    numNodos = n;
    dirigido = d;

    // Crear matriz de adyacencia
    matrizAdyacencia = new int *[numNodos];
    for (int i = 0; i < numNodos; ++i)
    {
      matrizAdyacencia[i] = new int[numNodos];
      // Inicializar con 0 (sin conexiones)
      for (int j = 0; j < numNodos; ++j)
      {
        matrizAdyacencia[i][j] = 0;
      }
    }
  }

  // Destructor
  ~Grafo()
  {
    for (int i = 0; i < numNodos; ++i)
    {
      delete[] matrizAdyacencia[i];
    }
    delete[] matrizAdyacencia;
  }

  // Agregar una arista
  void agregarArista(int origen, int destino, int peso = 1)
  {
    if (origen >= 0 && origen < numNodos && destino >= 0 && destino < numNodos)
    {
      matrizAdyacencia[origen][destino] = peso;
      if (!dirigido)
      {
        matrizAdyacencia[destino][origen] = peso;
      }
    }
    else
    {
      cout << "Nodos inválidos!" << endl;
    }
  }

  // Eliminar una arista
  void eliminarArista(int origen, int destino)
  {
    if (origen >= 0 && origen < numNodos && destino >= 0 && destino < numNodos)
    {
      matrizAdyacencia[origen][destino] = 0;
      if (!dirigido)
      {
        matrizAdyacencia[destino][origen] = 0;
      }
    }
    else
    {
      cout << "Nodos inválidos!" << endl;
    }
  }

  // Mostrar la matriz de adyacencia
  void mostrar()
  {
    cout << "Matriz de adyacencia:\n";
    cout << "   ";
    for (int i = 0; i < numNodos; ++i)
    {
      cout << i << " ";
    }
    cout << "\n";

    for (int i = 0; i < numNodos; ++i)
    {
      cout << i << ": ";
      for (int j = 0; j < numNodos; ++j)
      {
        cout << matrizAdyacencia[i][j] << " ";
      }
      cout << "\n";
    }
  }

  // Verificar si hay una arista entre dos nodos
  bool existeArista(int origen, int destino)
  {
    if (origen >= 0 && origen < numNodos && destino >= 0 && destino < numNodos)
    {
      return matrizAdyacencia[origen][destino] != 0;
    }
    return false;
  }
};

int main()
{
  // Ejemplo de uso
  int numNodos = 5;
  Grafo g(numNodos); // Grafo no dirigido

  // Agregar algunas aristas
  g.agregarArista(0, 1);
  g.agregarArista(0, 2);
  g.agregarArista(1, 3);
  g.agregarArista(2, 3);
  g.agregarArista(3, 4);

  // Mostrar la matriz
  g.mostrar();

  // Verificar si existe una arista
  cout << "\nExiste arista entre 0 y 1? " << (g.existeArista(0, 1) ? "Sí" : "No") << endl;
  cout << "Existe arista entre 1 y 4? " << (g.existeArista(1, 4) ? "Sí" : "No") << endl;

  // Eliminar una arista
  cout << "\nEliminando arista entre 0 y 1...\n";
  g.eliminarArista(0, 1);
  g.mostrar();

  return 0;
}