#include <iostream>

using namespace std;

class BST
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

  void deleteSubTree(Nodo *nodo)
  {
    if (!nodo)
      return;
    deleteSubTree(nodo->izquierdo);
    deleteSubTree(nodo->derecho);
    delete nodo;
  }

public:
  BST() : raiz(nullptr) {}
  ~BST()
  {
    // deleteSubTree(raiz);
  }

  Nodo *insert(Nodo *nodo, int valor)
  {
    if (!nodo)
      return new Nodo(valor);

    if (valor < nodo->valor)
      nodo->izquierdo = insert(nodo->izquierdo, valor);
    else
      nodo->derecho = insert(nodo->derecho, valor);

    nodo->altura = 1 + std::max(altura(nodo->izquierdo), altura(nodo->derecho));
    int balanceAux = balance(nodo);

    // Caso LL
    if (balanceAux > 1 && valor < nodo->izquierdo->valor)
      return rotarDerecha(nodo);

    // Caso RR
    if (balanceAux < -1 && valor > nodo->derecho->valor)
      return rotarIzquierda(nodo);

    // Caso LR
    if (balanceAux > 1 && valor > nodo->izquierdo->valor)
      return rotarIzquierdaDerecha(nodo);

    // Caso RL
    if (balanceAux < -1 && valor < nodo->derecho->valor)
      return rotarDerechaIzquierda(nodo);

    return nodo;
  }

  bool find(Nodo *nodo, int valor)
  {
    if (!nodo)
    {
      return false;
    }
    if (valor == nodo->valor)
    {
      return true;
    }

    if (valor < nodo->valor)
    {
      return find(nodo->izquierdo, valor);
    }
    else
    {
      return find(nodo->derecho, valor);
    }
  }

  Nodo *min(Nodo *nodo)
  {
    while (nodo && nodo->izquierdo)
    {
      nodo = nodo->izquierdo;
    }
    return nodo;
  }

  Nodo *max(Nodo *nodo)
  {
    while (nodo && nodo->derecho)
    {
      nodo = nodo->derecho;
    }
    return nodo;
  }

  Nodo *eliminar(Nodo *nodo, int valor)
  {
    if (!nodo)
    {
      return nullptr; // Valor no encontrado
    }
    if (valor < nodo->valor)
    {
      nodo->izquierdo = eliminar(nodo->izquierdo, valor);
    }
    else if (valor > nodo->valor)
    {
      nodo->derecho = eliminar(nodo->derecho, valor);
    }
    else
    {
      // caso 1: es una hoja o 0 hijos
      if (!nodo->izquierdo && !nodo->derecho)
      {
        delete nodo;
        return nullptr;
      }
      // caso 2a: tiene un hijo derecho o 1 hijo
      if (!nodo->derecho)
      {
        Nodo *temp = nodo->izquierdo;
        delete nodo;
        return temp;
      }
      // caso 2b: tiene un hijo izquierdo o 1 hijo
      if (!nodo->izquierdo)
      {
        Nodo *temp = nodo->derecho;
        delete nodo;
        return temp;
      }
      // caso 3: tiene dos hijos
      Nodo *temp = min(nodo->derecho);                      // Encuentra el mínimo en el subárbol derecho
      nodo->valor = temp->valor;                            // Reemplaza el valor del nodo a eliminar
      nodo->derecho = eliminar(nodo->derecho, temp->valor); // Elimina el nodo mínimo encontrado
    }
    return nodo; // Retorna el nodo actualizado
  }

  void inorder(Nodo *nodo)
  {
    if (!nodo)
      return;
    inorder(nodo->izquierdo);
    cout << nodo->valor << " ";
    inorder(nodo->derecho);
  }

  void preorder(Nodo *nodo)
  {
    if (!nodo)
      return;
    cout << nodo->valor << " ";
    preorder(nodo->izquierdo);
    preorder(nodo->derecho);
  }

  void postorder(Nodo *nodo)
  {
    if (!nodo)
      return;
    postorder(nodo->izquierdo);
    postorder(nodo->derecho);
    cout << nodo->valor << " ";
  }

  // Funciones públicas para recorrer el árbol
  void insertar(int valor)
  {
    raiz = insert(raiz, valor);
  }

  void recorrerPreorden()
  {
    preorder(raiz);
    cout << endl;
  }

  int altura(Nodo *nodo) const
  {
    if (!nodo)
      return 0;
    return nodo->altura;
  }

  int balance(Nodo *nodo)
  {
    if (!nodo)
      return 0;
    return altura(nodo->izquierdo) - altura(nodo->derecho);
    // return altura(nodo->derecho) + altura(nodo->izquierdo); otra forma
  }

  // (LL) Rotación simple a la derecha
  Nodo *rotarDerecha(Nodo *x)
  {
    Nodo *y = x->izquierdo; // el hijo izquierdo se convierte en el nuevo nodo raíz
    Nodo *z = y->derecho;   // el subárbol derecho de y

    // Realizar rotación
    y->derecho = x;
    x->izquierdo = z;

    // Actualizar alturas
    x->altura = 1 + std::max(altura(x->izquierdo), altura(x->derecho));
    y->altura = 1 + std::max(altura(y->izquierdo), altura(y->derecho));

    return y;
  }

  // (RR) Rotación simple a la izquierda
  Nodo *rotarIzquierda(Nodo *x)
  {
    Nodo *y = x->derecho;   // el hijo derecho se convierte en el nuevo nodo raíz
    Nodo *z = y->izquierdo; // el subárbol izquierdo de y

    // Realizar rotación
    y->izquierdo = x;
    x->derecho = z;

    // Actualizar alturas
    x->altura = 1 + std::max(altura(x->izquierdo), altura(x->derecho));
    y->altura = 1 + std::max(altura(y->izquierdo), altura(y->derecho));

    return y;
  }

  // (LR) Rotación doble izquierda-derecha
  Nodo *rotarIzquierdaDerecha(Nodo *x)
  {
    x->izquierdo = rotarIzquierda(x->izquierdo);
    return rotarDerecha(x);
  }

  // (RL) Rotación doble derecha-izquierda
  Nodo *rotarDerechaIzquierda(Nodo *x)
  {
    x->derecho = rotarDerecha(x->derecho);
    return rotarIzquierda(x);
  }
};

int main()
{
  BST arbol;
  arbol.insertar(5);
  arbol.insertar(3);
  arbol.insertar(7);
  arbol.insertar(2);
  arbol.insertar(4);
  arbol.insertar(6);
  arbol.insertar(8);

  arbol.recorrerPreorden(); // Imprime: 5 3 2 4 7 6 8

  return 0;
}