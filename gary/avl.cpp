#include <iostream>

class BST
{

private:
  struct Nodo
  {
    int valor;
    Nodo *izquierdo;
    Nodo *derecho;
    Nodo(int v) : valor(v), izquierdo(nullptr), derecho(nullptr) {}
  };

  Nodo *raiz;

  Nodo *insert(Nodo *nodo, int valor)
  {
    if (!nodo)
    {
      return new Nodo(valor);
    }
    if (valor < nodo->valor)
    {
      nodo->izquierdo = insert(nodo->izquierdo, valor);
    }
    else
    {
      nodo->derecho = insert(nodo->derecho, valor);
    }
    return nodo;
  }

  Nodo *eliminar(Nodo *nodo, int valor)
  {
    if (!nodo)
      return nullptr;

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
      // Caso 1: hoja o 0 hijos
      if (!nodo->izquierdo && !nodo->derecho)
      {
        delete nodo;
        return nullptr;
      }
      // Caso 2: tiene hijo izquierdo o 1 hijo
      if (!nodo->derecho)
      {
        Nodo *temp = nodo->izquierdo;
        delete nodo;
        return temp;
      }
      // Caso 2b: tiene hijo derecho  o 1 hijo
      if (!nodo->izquierdo)
      {
        Nodo *temp = nodo->derecho;
        delete nodo;
        return temp;
      }
      // Caso 3 dos hijos
      Nodo *temp = min(nodo->derecho);
      nodo->valor = temp->valor;
      nodo->derecho = eliminar(nodo->derecho, temp->valor);
    }
    return nodo;
  }

  void inorden(Nodo *nodo) const
  {
    if (!nodo)
      return;
    inorden(nodo->izquierdo);
    std::cout << nodo->valor << " ";
    inorden(nodo->derecho);
  }

  void preorden(Nodo *nodo) const
  {
    if (!nodo)
      return;
    std::cout << nodo->valor << " ";
    preorden(nodo->izquierdo);
    preorden(nodo->derecho);
  }

  void postorden(Nodo *nodo) const
  {
    if (!nodo)
      return;
    postorden(nodo->izquierdo);
    postorden(nodo->derecho);
    std::cout << nodo->valor << " ";
  }

public:
  BST() : raiz(nullptr) {}

  ~BST() {}

  bool find(Nodo *nodo, int valor)
  {
    if (!nodo)
      return false;

    if (valor == nodo->valor)
      return true;

    return (valor < nodo->valor) ? find(nodo->izquierdo, valor) : find(nodo->derecho, valor);
  }

  Nodo *min(Nodo *nodo)
  {
    if (!nodo)
      return nullptr;
    while (nodo && nodo->izquierdo)
      nodo = nodo->izquierdo;
    return nodo;
  }

  Nodo *max(Nodo *nodo)
  {
    if (!nodo)
      return nullptr;
    while (nodo && nodo->derecho)
    {
      nodo = nodo->derecho;
    }
    return nodo;
  }

  void insertar(int valor)
  {
    raiz = insert(raiz, valor);
  }

  void pre() const
  {
    std::cout << "Recorrido en pre orden" << std::endl;
    preorden(raiz);
    std::cout << std::endl;
  }

  void in() const
  {
    std::cout << "Recorrido en in orden" << std::endl;
    inorden(raiz);
    std::cout << std::endl;
  }

  void post() const
  {
    std::cout << "Recorrido en post orden" << std::endl;
    postorden(raiz);
    std::cout << std::endl;
  }
};

int main()
{

  BST tree;

  //         50
  //     30       70
  //  20   35     60
  //     32 33
  tree.insertar(50);
  tree.insertar(30);
  tree.insertar(70);
  tree.insertar(20);
  tree.insertar(60);

  tree.pre(); // 50 30 20 70 60
  std::cout << std::endl;
  tree.in(); // 20 30 50 60 70
  std::cout << std::endl;
  tree.post(); // 20 30 60 70 50
  std::cout << std::endl;
  return 0;
}