#include <iostream>

using namespace std;

class Heap
{
  struct Nodo
  {
    int valor;
    Nodo *izquierdo;
    Nodo *derecho;
    int altura;
    // la altura se puede inicializar en 1 para el nodo raíz
    //  o en 0 si se considera que un nodo hoja tiene altura 0
    Nodo(int val) : valor(val), izquierdo(nullptr), derecho(nullptr), altura(1) {}
  };

  Nodo *raiz;

public:
  Nodo *insert(Nodo *nodo, int valor)
  {

    if (!nodo)
    {
      return new Nodo(valor);
    }
    if (!nodo->izquierdo)
    {
      nodo->izquierdo = insert(nodo->izquierdo, valor);
    }
    else if (!nodo->derecho)
    {
      nodo->derecho = insert(nodo->derecho, valor);
    }
    else
    {
      nodo->izquierdo = insert(nodo->izquierdo, valor);
    }
    return reestucturar(nodo); // balancear
  }

  Nodo *reestucturar(Nodo *nodo)
  { // balancear
    if (!nodo)
    {
      return nullptr;
    }

    if (nodo->izquierdo && nodo->izquierdo->valor > nodo->valor)
    {
      std::swap(nodo->valor, nodo->izquierdo->valor); // esto es una trampa, ya que intercambio los valores en lugar de los punteros
      nodo = reestucturar(nodo->izquierdo);           // rotamos
    }

    if (nodo->derecho && nodo->derecho->valor > nodo->valor)
    {
      std::swap(nodo->valor, nodo->derecho->valor); // esto es una trampa, ya que intercambio los valores en lugar de los punteros
      nodo = reestucturar(nodo->derecho);           // rotamos
    }
    return nodo;
  }

  Nodo *max(Nodo *nodo, int &valor)
  {
    if (!nodo)
    {
      return nullptr; // árbol vacío
    }
    valor = nodo->valor; // asignar el valor del nodo actual
    Nodo *mayor = nullptr;
    if (nodo->izquierdo || nodo->derecho)
    {
      if (nodo->izquierdo && nodo->derecho)
      {
        mayor = nodo->izquierdo->valor > nodo->derecho->valor ? nodo->izquierdo : nodo->derecho;
      }
      else if (nodo->izquierdo)
      {
        mayor = nodo->izquierdo;
      }
      // else if (nodo->derecho) // puede ser un else
      else
      {
        mayor = nodo->derecho;
      }
      nodo->valor = mayor->valor; // asignar el valor del nodo mayor al nodo actual
      nodo->izquierdo = max(nodo->izquierdo, mayor->valor);
      nodo->derecho = max(nodo->derecho, mayor->valor);
    }
    return nodo; // yo era el mayor
  }

  Heap() : raiz(nullptr) {}
  ~Heap()
  {
    // deleteSubTree(raiz);
  }

  void insertar(int valor)
  {
    raiz = insert(raiz, valor);
  }
};

int main()
{

  Heap heap;
  heap.insertar(10);
  heap.insertar(20);
  heap.insertar(5);
  heap.insertar(7);
  heap.insertar(2);
  heap.insertar(30); 

  //                10
  //              /    \
  //            20      5
  //           /
  //          7      2    30


  // implementar que ordene al insertar

  return 0;
}