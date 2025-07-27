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
    // Inserta primero por la rama menos llena (nivel más bajo)
    int alturaIzq = getAltura(nodo->izquierdo);
    int alturaDer = getAltura(nodo->derecho);

    if (alturaIzq <= alturaDer)
    {
      nodo->izquierdo = insert(nodo->izquierdo, valor);
    }
    else
    {
      nodo->derecho = insert(nodo->derecho, valor);
    }
    return reestucturar(nodo); // balancear
  }

  Nodo *reestucturar(Nodo *nodo)
  { // balancear
    if (!nodo)
      return nullptr;

    if (nodo->izquierdo && nodo->izquierdo->valor > nodo->valor)
    {
      std::swap(nodo->valor, nodo->izquierdo->valor);
      nodo->izquierdo = reestucturar(nodo->izquierdo);
    }

    if (nodo->derecho && nodo->derecho->valor > nodo->valor)
    {
      std::swap(nodo->valor, nodo->derecho->valor);
      nodo->derecho = reestucturar(nodo->derecho);
    }
    return nodo;
  }

  Nodo *max(Nodo *nodo, int &valor)
  {
    if (!nodo)
      return nullptr; // árbol vacío

    valor = nodo->valor;
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
      else
      {
        mayor = nodo->derecho;
      }
      nodo->valor = mayor->valor;
      nodo->izquierdo = max(nodo->izquierdo, mayor->valor);
      nodo->derecho = max(nodo->derecho, mayor->valor);
    }
    return nodo;
  }

  int getAltura(Nodo *nodo)
  {
    if (!nodo) return 0;
    int izq = getAltura(nodo->izquierdo);
    int der = getAltura(nodo->derecho);
    return 1 + (izq > der ? izq : der);
  }

  Heap() : raiz(nullptr) {}
  ~Heap()
  {
    deleteSubTree(raiz);
  }

  void deleteSubTree(Nodo *nodo)
  {
    if (!nodo) return;
    deleteSubTree(nodo->izquierdo);
    deleteSubTree(nodo->derecho);
    delete nodo;
  }

  void insertar(int valor)
  {
    raiz = insert(raiz, valor);
  }

  void preorder(Nodo *root)
  {
    if (!root)
      return;
    cout << root->valor << " ";
    preorder(root->izquierdo);
    preorder(root->derecho);
  }

  void mostrar()
  {
    preorder(raiz);
    cout << endl;
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

  heap.mostrar(); // Debe mostrar los valores en orden de heap

  return 0;
}