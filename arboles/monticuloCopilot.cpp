#include <iostream>
using namespace std;

class Heap
{
  struct Nodo
  {
    int valor;
    Nodo *izquierdo;
    Nodo *derecho;
    Nodo(int val) : valor(val), izquierdo(nullptr), derecho(nullptr) {}
  };

  Nodo *raiz;

  // Inserta el valor en el primer lugar disponible (nivel por nivel)
  void insert(Nodo *&nodo, int valor, int nivel, int &insertado)
  {
    if (!nodo)
    {
      nodo = new Nodo(valor);
      insertado = 1;
      return;
    }
    // Inserta por niveles: primero izquierdo, luego derecho
    if (!insertado)
    {
      insert(nodo->izquierdo, valor, nivel + 1, insertado);
      if (!insertado)
        insert(nodo->derecho, valor, nivel + 1, insertado);
    }
    // Después de insertar, reestructura hacia arriba
    if (nodo->izquierdo && nodo->izquierdo->valor > nodo->valor)
      std::swap(nodo->valor, nodo->izquierdo->valor);
    if (nodo->derecho && nodo->derecho->valor > nodo->valor)
      std::swap(nodo->valor, nodo->derecho->valor);
  }

  void preorder(Nodo *root)
  {
    if (!root)
      return;
    cout << root->valor << " ";
    preorder(root->izquierdo);
    preorder(root->derecho);
  }

  void deleteSubTree(Nodo *nodo)
  {
    if (!nodo) return;
    deleteSubTree(nodo->izquierdo);
    deleteSubTree(nodo->derecho);
    delete nodo;
  }

public:
  Heap() : raiz(nullptr) {}
  ~Heap() { deleteSubTree(raiz); }

  void insertar(int valor)
  {
    int insertado = 0;
    insert(raiz, valor, 0, insertado);
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

  heap.mostrar(); // Muestra los valores en preorden, raíz es el máximo

  return 0;
}