#include <iostream>
#include <string>

using namespace std;

template <typename T>
class GenTree
{
  // protected:
public:
  struct Node
  {
    T data;
    Node *firstChild;
    Node *nextChild;
    Node *parent;
    // Node(const T &d) : data(d), firstChild(nullptr), nextChild(nullptr), parent(nullptr) {}
    Node(const T &d, Node *n = nullptr) : data(d), firstChild(n), nextChild(n), parent(n) {}
  };

  Node *root;
  int size; //*puede ser la cardinalidad o cantidad de nodos o niveles

private:
  void deleteSubTree(Node *node)
  {
    if (!node) // node != nullptr
    {
      return;
    }
    Node *child = node->firstChild;

    // me paro en un nodo padre, verifico si tengo hijo a la izquierda
    while (child)
    { // child != nullprt
      Node *next = child->nextChild;
      deleteSubTree(child);
      child = next;
    }
    delete node;
  }

public:
  GenTree() : root(nullptr)
  {
  }

  ~GenTree()
  {
    deleteSubTree(root);
  }

  Node *GetRoot()
  {
    return root; // Me da la raiz o padre del hijo en el que este, depende en que nivel este
    // si estoy en un nivel 4 me da un padre de nivel 3
  }

  Node *GetChild(Node *parent)
  {
    // if (!parent)
    // {
    //   return nullptr;
    // }
    // if (!parent->firstChild)
    // {
    //   return parent->firstChild;
    // }
    // return nullptr;
    if (!parent)
      return nullptr;
    return parent->firstChild;
  }

  Node *GetBrother(Node *parent)
  {
    if (!parent)
    {
      return nullptr;
    }
    parent->nextChild;
  }

  bool ExistBrother(Node *parent)
  {
    return parent && parent->nextChild != nullptr;
  }

  bool IsLeaft(Node *node)
  {
    return !(GetChild(node) || GetBrother(node));
  }

  bool IsEmpty()
  {
    return root == nullptr;
  }

  void Insert(T data)
  {
    if (IsEmpty())
    {
      root = new Node(T);
    }
  }

  void Insert(Node *newNode)
  {
    if (root == nullptr)
    {
      root = newNode;
    }
  }

  void Insert(Node *parentNode, Node *newNode)
  {
    if (!parentNode)
    {
      Insert(newNode); // si no tengo nodo padre voy a crear el root
      return;
    }
    newNode->parent = parentNode;
    if (!parentNode->firstChild)
    {
      parentNode->firstChild = newNode;
    }
    else
    {
      Node *brothers = parentNode->firstChild;
      while (brothers)
      {
        brothers = brothers->nextChild;
      }
      brothers->nextChild = newNode;
    }
    //  if (!parentNode->nextChild)
    //   {
    //     p arentNode->nextChild;
    //   }
  }
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

  void inorder(Node *nodo)
  {
    if (!nodo)
      return;
    inorder(nodo->firstChild);
    cout << nodo->data << " ";
    inorder(nodo->nextChild);
  }

  void recorrerInorder()
  {
    inorder(root);
    cout << endl;
  }
};

int main(int argc, char const *argv[])
{
  GenTree<string> Tree;
  Tree.Insert("A");
  // preorden -> A,B,D,C
  // inorden -> D,B,A,C
  // postorden -> D,B,C,A
  Tree.recorrerInorder();
  return 0;
}
