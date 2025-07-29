#include <iostream>
#include <queue>
#include <chrono>
#include <stdlib.h>
using namespace std;
using namespace chrono;

// HECHO POR JOSE PEREZ Y DANIEL BRICENO

class Arbol
{
private:
  struct Node
  {
    int valor;
    Node *izquierdo;
    Node *derecho;
    Node(int v) : valor(v), izquierdo(nullptr), derecho(nullptr) {}
  };

  Node *raiz;

  void insert(Node *nodo, int valor)
  {
    if (!nodo->izquierdo)
    {
      nodo->izquierdo = new Node(valor);
    }
    else if (!nodo->derecho)
    {
      nodo->derecho = new Node(valor);
    }
    else
    {
      if (size(nodo->izquierdo) <= size(nodo->derecho))
      {
        insert(nodo->izquierdo, valor);
      }
      else
      {
        insert(nodo->derecho, valor);
      }
    }
  }

  int size(Node *nodo)
  {
    if (!nodo)
      return 0;

    int sizeL = size(nodo->izquierdo);
    int sizeR = size(nodo->derecho);

    return 1 + (sizeL > sizeR ? sizeL : sizeR);
  }

  void PreOrden(Node *nodo)
  {
    if (nodo != nullptr)
    {
      cout << nodo->valor << " ";
      PreOrden(nodo->izquierdo);
      PreOrden(nodo->derecho);
    }
  }

  void Borrar(Node *nodo)
  {
    if (!nodo)
      return;

    Borrar(nodo->izquierdo);
    Borrar(nodo->derecho);
    delete nodo;
  }

  void BFS(Node *nodo, int X)
  {
    if (!nodo)
      return;

    int contador = 1;
    queue<Node *> q;
    q.push(nodo);

    cout << "Nodos: ";

    while (!q.empty())
    {
      Node *current = q.front();
      q.pop();

      cout << current->valor << " ";

      if (current->valor == X)
      {
        cout << endl
             << "valor encontrado" << endl;
        cout << "nodos visitados: " << contador << endl;
        return;
      }

      if (current->izquierdo)
      {
        q.push(current->izquierdo);
      }

      if (current->derecho)
      {
        q.push(current->derecho);
      }
      contador++;
    }
  }

  bool DFS_PreOrden(Node *nodo, int X, int &contador)
  {
    if (!nodo)
      return false;

    contador++;

    cout << nodo->valor << " ";

    if (nodo->valor == X)
    {
      cout << endl
           << "Valor encontrado" << endl;
      cout << "Nodos visitados: " << contador << endl;
      return true;
    }

    if (DFS_PreOrden(nodo->izquierdo, X, contador))
      return true;
    if (DFS_PreOrden(nodo->derecho, X, contador))
      return true;

    return false;
  }

  bool DFS_InOrden(Node *nodo, int X, int &contador)
  {
    if (!nodo)
      return false;

    if (DFS_InOrden(nodo->izquierdo, X, contador))
      return true;

    contador++;
    cout << nodo->valor << " ";

    if (nodo->valor == X)
    {
      cout << endl
           << "Valor encontrado" << endl;
      cout << "Nodos visitados: " << contador << endl;
      return true;
    }

    if (DFS_PreOrden(nodo->derecho, X, contador))
      return true;

    return false;
  }

  bool DFS_PostOrden(Node *nodo, int X, int &contador)
  {
    if (!nodo)
      return false;

    if (DFS_InOrden(nodo->izquierdo, X, contador))
      return true;
    if (DFS_PreOrden(nodo->derecho, X, contador))
      return true;

    contador++;
    cout << nodo->valor << " ";

    if (nodo->valor == X)
    {
      cout << endl
           << "Valor encontrado" << endl;
      cout << "Nodos visitados: " << contador << endl;
      return true;
    }

    return false;
  }

public:
  Arbol() : raiz(nullptr) {}

  ~Arbol()
  {
    Borrar(raiz);
  }

  void insertar(int valor)
  {
    if (!raiz)
    {
      raiz = new Node(valor);
    }
    else
    {
      insert(raiz, valor);
    }
  }

  void insertNiveles(int niveles)
  {
    Borrar(raiz);

    srand(time(NULL));

    queue<Node *> cola;

    raiz = new Node(rand() % 500 + 1);
    cola.push(raiz);

    int nivel_actual = 1;
    int nodos_en_nivel = 1;

    while (nivel_actual < niveles)
    {
      int c = 0;

      for (int i = 0; i < nodos_en_nivel; i++)
      {
        Node *actual = cola.front();
        cola.pop();

        actual->izquierdo = new Node(rand() % 500 + 1);
        cola.push(actual->izquierdo);
        c++;

        actual->derecho = new Node(rand() % 500 + 1);
        cola.push(actual->derecho);
        c++;
      }

      nivel_actual++;
      nodos_en_nivel = c;
    }
  }

  void pre()
  {
    PreOrden(raiz);
  }

  int altura()
  {
    return size(raiz);
  }

  void anchura(int valor)
  {
    BFS(raiz, valor);
  }

  void profundidad_pre(int valor, int contador)
  {
    DFS_PreOrden(raiz, valor, contador);
  }

  void profundidad_in(int valor, int contador)
  {
    DFS_InOrden(raiz, valor, contador);
  }

  void profundidad_post(int valor, int contador)
  {
    DFS_PostOrden(raiz, valor, contador);
  }
};

int main()
{
  cout << "// TAREA 2 //" << endl
       << endl;

  Arbol arbol; // ARBOL A EVALUAR (gracias a que se borra en cada insert de niveles podemos reutilizarlo multiples veces)

  int contador = 0; // para los algoritmos de profundidad

  int num; // para los numeros random (del 1 al 10)
  srand(time(NULL));

  cout << "ingrese el numero a buscar: ";
  int M;
  cin >> M;

  /////////////////////////////////////////////////
  ////////////////////5 NIVELES///////////////////

  cout << "// ARBOL DE 5 NIVELES //" << endl;

  arbol.insertNiveles(5);

  cout << "//////////////////////////////////" << endl
       << endl;

  auto start = high_resolution_clock::now(); // inicio del cronometraje

  cout << "Busqueda por anchura: "; // queremos buscar el numero 100
  arbol.anchura(M);

  auto end = high_resolution_clock::now(); // fin del cronometraje
  duration<float, milli> duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now();

  cout << "Busqueda por profundidad (pre orden): ";
  arbol.profundidad_pre(M, 0);

  end = high_resolution_clock::now();
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now();

  cout << "Busqueda por profundidad (in orden): ";
  arbol.profundidad_in(M, 0);

  end = high_resolution_clock::now();
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now();

  cout << "Busqueda por profundidad (post orden): ";
  arbol.profundidad_post(M, 0);

  end = high_resolution_clock::now();
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  ///////////////////////////////////////////////////
  ///////////////////10 NIVELES/////////////////////

  cout << "// ARBOL DE 10 NIVELES //" << endl;

  arbol.insertNiveles(10);

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now(); // inicio del cronometraje

  cout << "Busqueda por anchura: "; // queremos buscar el numero 100
  arbol.anchura(M);

  end = high_resolution_clock::now(); // fin del cronometraje
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now();

  cout << "Busqueda por profundidad (pre orden): ";
  arbol.profundidad_pre(M, 0);

  end = high_resolution_clock::now();
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now();

  cout << "Busqueda por profundidad (in orden): ";
  arbol.profundidad_in(M, 0);

  end = high_resolution_clock::now();
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now();

  cout << "Busqueda por profundidad (post orden): ";
  arbol.profundidad_post(M, 0);

  end = high_resolution_clock::now();
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  ///////////////////////////////////////////////////
  /////////////////15 NIVELES///////////////////////

  cout << "// ARBOL DE 15 NIVELES //" << endl;

  arbol.insertNiveles(15);

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now(); // inicio del cronometraje

  cout << "Busqueda por anchura: "; // queremos buscar el numero 100
  arbol.anchura(M);

  end = high_resolution_clock::now(); // fin del cronometraje
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now();

  cout << "Busqueda por profundidad (pre orden): ";
  arbol.profundidad_pre(M, 0);

  end = high_resolution_clock::now();
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now();

  cout << "Busqueda por profundidad (in orden): ";
  arbol.profundidad_in(M, 0);

  end = high_resolution_clock::now();
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now();

  cout << "Busqueda por profundidad (post orden): ";
  arbol.profundidad_post(M, 0);

  end = high_resolution_clock::now();
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  ///////////////////////////////////////////////////
  /////////////////20 NIVELES///////////////////////

  cout << "// ARBOL DE 20 NIVELES //" << endl;

  arbol.insertNiveles(20);

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now(); // inicio del cronometraje

  cout << "Busqueda por anchura: "; // queremos buscar el numero 100
  arbol.anchura(M);

  end = high_resolution_clock::now(); // fin del cronometraje
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now();

  cout << "Busqueda por profundidad (pre orden): ";
  arbol.profundidad_pre(M, 0);

  end = high_resolution_clock::now();
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now();

  cout << "Busqueda por profundidad (in orden): ";
  arbol.profundidad_in(M, 0);

  end = high_resolution_clock::now();
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  cout << "//////////////////////////////////" << endl
       << endl;

  start = high_resolution_clock::now();

  cout << "Busqueda por profundidad (post orden): ";
  arbol.profundidad_post(M, 0);

  end = high_resolution_clock::now();
  duration = end - start;
  cout << endl
       << "tiempo de ejecucion: " << duration.count() << " milisegundos" << endl
       << endl;

  return 0;
}