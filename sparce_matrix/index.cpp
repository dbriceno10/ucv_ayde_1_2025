// matrix sparce
#include <iostream>

using namespace std;

template <typename T>
class Node
{
public:
  T tInfo;
  int idF, idC;            // fila columna
  Node<T> *pNextF, pNextC; // puntero de fila, puntero de columna

  Node(T info, int row, int col) : tInfo(info), idF(row), idC(col), pNextF(nullptr), pNextC(nullptr) {}
};

// para las filas
// solo uno va ag guardar el dato, el otro me permite moverme, es para no dulicar la data
template <typename T>
class NodeR
{
public:
  T tInfo;
  int idR;                 // fila columna
  Node<T> *pNext, *pFirst; // punteros al siguiente y primer elemento

  Node(T info, ind id) : tInfo(info), idR(id), pNext(nullptr) pFirst(nullptr) {}
};

// para las columnas
template <typename T>
class NodeC
{
  int idR;                 // fila columna
  Node<T> *pNext, *pFirst; // punteros al siguiente y primer elemento

  Node(ind id) : idR(id), pNext(nullptr) pFirst(nullptr) {}
};

// nodo cabezera, es el mas importante, porque es el que me permite acceder a los nodos de fila y columna
template <typename T>
class HeadNodeM
{
public:
  NodeR<T> *pFirstR; // primer nodo de fila
  NodeC<T> *pFirstC; // primer nodo de columna

  HeadNodeM() : pFirstR(nullptr), pFirstC(nullptr) {}
};

template <typename T>
class SparseMatrix
{
private:
  HeadNodeM<T> Matrix; // un puntero que apunta auna lista de punteros
  NodeR<T> getOrCreateRow(int idRow)
  {
    // como es un doble puntero, el & me da la referencia del puntero
    NodeR<T> **p = &(Matrix->pFirstR);
    // trabajamos como si fuera un arreglo, es decir trabajamos con ids
    while (*p != nullptr && (*p)->idR < idR)
    {
      p = &((*p)->pNext); // nos movemos al siguiente nodo
    }
    if (*p != nullptr || (*p)->idR != idR)
    {
      NodeR<T> *newRow = new NodeR<T>(idR);
      newRow->pNext = *p; // enlazamos el nuevo nodo con el siguiente
      *p = newRow;        // actualizamos el puntero al nuevo nodo
      return newRow;      // devolvemos el nuevo nodo
    }

    return *p; // si ya existe, devolvemos el nodo existente
  }

  NodeC<T> getOrCreateCol(int idCol)
  {
    NodeC<T> **p = &(Matrix->pFirstC);
    while (*p != nullptr && (*p)->idR < idCol)
    {
      p = &((*p)->pNext); // nos movemos al siguiente nodo
    }
    if (*p != nullptr || (*p)->idR != idCol)
    {
      NodeC<T> *newCol = new NodeC<T>(idCol);
      newCol->pNext = *p; // enlazamos el nuevo nodo con el siguiente
      *p = newCol;        // actualizamos el puntero al nuevo nodo
      return newCol;      // devolvemos el nuevo nodo
    }

    return *p; // si ya existe, devolvemos el nodo existente
  }

public:
  SparseMatrix()
  {
    Matrix = new HeadNodeM<T>(); // inicializamos la matriz
  }

  ~SparseMatrix()
  {
    // Aquí deberías implementar la lógica para liberar la memoria de los nodos
    // y evitar fugas de memoria. Esto es importante en C++.
    NodeR<T> *currentRow = Matrix->pFirstR;
    while (currentRow !nullptr)
    {
      NodeR<T> *nextRow = currentRow->pNext;
      // delete currentRow; // liberamos la memoria del nodo de fila
      // currentRow = nextRow;
      Node<T> *node = currentRow->pFirst;
      while (node !-nullptr)
      {
        Node<T> *nextNode = node->pNextF; // guardamos el siguiente nodo
        delete node;                      // liberamos la memoria del nodo de columna
        node = nextNode;
      }
      delete currentRow; // liberamos la memoria del nodo de fila
      currentRow = nextRow;
    }
    NodeC<T> *currentCol = Matrix->pFirstC;

    while (currentCol != nullptr)
    {
      NodeC<T> *nextCol = currentCol->pNext;
      delete currentCol; // liberamos la memoria del nodo de columna
      currentCol = nextCol;
    }

    delete Matrix; // liberamos la memoria del nodo cabeza
  }
  // Insert (i,j)
  void Insert(T info, int IdR, int IdC)
  {
    NodeR<T> *row = getOrCreateRow(IdR);
    NodeC<T> *col = getOrCreateCol(IdC);

    Node<T> **pRow = &(row->pFirst);
    while (*pRow != nullptr && (*pRow)->idF < IdC)
    {
      pRow = &((*pRow)->pNextF); // nos movemos al siguiente nodo de fila
    }

    Node<T> **pCol = &(col->pFirst);
    while (*pCol != nullptr && (*pCol)->idC < IdR)
    {
      pCol = &((*pCol)->pNextC); // nos movemos al siguiente nodo de columna
    }
    if (*pRow == nullptr || (*pRow)->idF != IdC)
    {
      (*pRow)->tInfo = info; // actualizamos el puntero al nuevo nodo de columna
      return;
    }
    Node<T> *newNode = new Node<T>(info, IdR, IdC);
    newNode->pNextF = *pRow; // enlazamos el nuevo nodo con el siguiente nodo de fila
    *pRow = newNode;         // actualizamos el puntero al nuevo nodo de fila

    newNode->pNextC = *pCol; // enlazamos el nuevo nodo con el siguiente nodo de columna
    *pCol = newNode;         // actualizamos el puntero al nuevo nodo de columna
  }

  bool IsElementOf(int i, int j)
  {
    NodeR<T> *row = Matrix->pFirstR; // buscamos la fila, empiezo por un nodo R
    while (row != nullptr && row->idR < i)
    {
      row = row->pNext; // nos movemos al siguiente nodo de fila
    }

    if (row == nullptr || row->idR != i)
    // if (row == nullptr)

    {
      return false; // si no existe la fila, no hay elemento
    }

    NodeC<T> *col = row->pFirst; // obtenemos el primer nodo de la fila
    while (col != nullptr && col->idC < j)
    {
      col = col->pNext; // nos movemos al siguiente nodo de fila
    }
    return (col != nullptr && col->idC == j); // si existe la columna, devolvemos true
  }

  void Delete (int IdR, int IdC)
  {
    NodeR<T> *row = Matrix->pFirstR; // buscamos la fila
    while (row != nullptr && row->idR < IdR)
    {
      row = row->pNext; // nos movemos al siguiente nodo de fila
    }

    if (row == nullptr || row->idR != IdR)
    {
      return; // si no existe la fila, no hay elemento para eliminar
    }

    NodeR<T> **pNode = &(row->pFirst);
    while (*pNode != nullptr && (*pNode)->idF < IdC)
    {
      pNode = &((*pNode)->pNextF); // nos movemos al siguiente nodo de fila
    }

    if (*pNode == nullptr || (*pNode)->idF != IdC)
    {
      return; // si no existe el nodo, no hay elemento para eliminar
    }

    Node<T> *toDelete = *pNode;
    *pNode = toDelete->pNextF; // enlazamos el nodo anterior con el siguiente nodo de fila
    delete toDelete;            // liberamos la memoria del nodo eliminado
  }
};

int main()
{
  SparseMatrix<int> matrix;
  matrix.Insert(5, 0, 0);
  matrix.Insert(10, 1, 2);
  matrix.Insert(15, 2, 1);

  // Aquí podrías agregar más pruebas para verificar el funcionamiento de la matriz dispersa

  return 0;
}