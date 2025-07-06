#include <iostream>
#include <string>
using namespace std;

template <typename T>
class GenTree
{
public:
  struct Node
  {
    T data;
    Node *firstChild;
    Node *nextSibling;
    Node *parent;
    Node(const T &d) : data(d), firstChild(nullptr), nextSibling(nullptr), parent(nullptr) {}
  };

private:
  Node *root;

  void deleteSubTree(Node *node)
  {
    if (!node)
      return;
    Node *child = node->firstChild;
    while (child)
    {
      Node *next = child->nextSibling;
      deleteSubTree(child);
      child = next;
    }
    delete node;
  }

public:
  GenTree() : root(nullptr) {}
  ~GenTree() { deleteSubTree(root); }

  Node *GetRoot() { return root; }

  bool IsEmpty() { return root == nullptr; }

  // Inserta el nodo como raíz si el árbol está vacío
  void Insert(Node *newNode)
  {
    if (!root)
      root = newNode;
  }

  // Inserta newNode como hijo de parentNode
  void Insert(Node *parentNode, Node *newNode)
  {
    if (!parentNode)
    {
      Insert(newNode);
      return;
    }
    newNode->parent = parentNode;
    if (!parentNode->firstChild)
    {
      parentNode->firstChild = newNode;
    }
    else
    {
      Node *sibling = parentNode->firstChild;
      while (sibling->nextSibling)
      {
        sibling = sibling->nextSibling;
      }
      sibling->nextSibling = newNode;
    }
  }

  // Devuelve el primer hijo de un nodo
  Node *GetChild(Node *parent)
  {
    return parent ? parent->firstChild : nullptr;
  }

  // Devuelve el siguiente hermano de un nodo
  Node *GetSibling(Node *node)
  {
    return node ? node->nextSibling : nullptr;
  }

  // Devuelve true si el nodo es hoja
  bool IsLeaf(Node *node)
  {
    return node && node->firstChild == nullptr;
  }

  // Devuelve el nivel del nodo (raíz = 0)
  int Level(Node *node)
  {
    if (!node)
      return -1;
    int level = 0;
    Node *current = node;
    while (current->parent)
    {
      level++;
      current = current->parent;
    }
    return level;
  }

  // Recorrido preorden
  void PreOrder(Node *node)
  {
    if (!node)
      return;
    cout << node->data << " ";
    for (Node *child = node->firstChild; child; child = child->nextSibling)
      PreOrder(child);
  }

  // Recorrido postorden
  void PostOrder(Node *node)
  {
    if (!node)
      return;
    for (Node *child = node->firstChild; child; child = child->nextSibling)
      PostOrder(child);
    cout << node->data << " ";
  }
};

int main()
{
  GenTree<string> Tree;

  auto grandpa = new GenTree<string>::Node("Abuelo"); // A
  auto father = new GenTree<string>::Node("Padre");   // B
  auto uncle = new GenTree<string>::Node("Tio");      // C
  auto child = new GenTree<string>::Node("Hijo");     // D

  Tree.Insert(grandpa);         // Raíz
  Tree.Insert(grandpa, father); // A,B
  Tree.Insert(grandpa, uncle);  // A,C
  Tree.Insert(father, child);   // B,D

  cout << "Preorden: ";
  Tree.PreOrder(Tree.GetRoot());
  cout << endl;

  cout << "Postorden: ";
  Tree.PostOrder(Tree.GetRoot());
  cout << endl;

  cout << "Nivel de 'Hijo': " << Tree.Level(child) << endl;
  cout << "Nivel de 'Padre': " << Tree.Level(father) << endl;
  cout << "Nivel de 'Abuelo': " << Tree.Level(grandpa) << endl;

  return 0;
}