#include <iostream>

using namespace std;

struct Dano
{
  int tipo;
  int cantidad;
};

class ControlDeDano
{
  struct Node
  {
    Dano dano;
    Node *next;
    Node(Dano d, Node *n = nullptr) : dano(d), next(n) {}
  };

  Node *topNode;
  int vidaActual;
  int count;

public:
  typedef Node *tPosition;
  ControlDeDano(int vidaInicial) : topNode(nullptr), vidaActual(vidaInicial), count(0) {}

  int recibirDano(Dano d) // push
  {
    topNode = new Node(d, topNode);
    vidaActual -= d.cantidad;
    count++;
    return vidaActual;
  }

  int curarDano() // pop
  {
    tPosition temp = topNode;
    topNode = topNode->next;
    vidaActual += temp->dano.cantidad;
    delete temp;
    count--;
    return vidaActual;
  }

  int curarNDanos(int n)
  {
    for (int i = 0; i < n && topNode != nullptr; i++)
    {
      tPosition temp = topNode;
      topNode = topNode->next;
      vidaActual += temp->dano.cantidad;
      delete temp;
      count--;
    }
    return vidaActual;
  }
  int curarPorTipo(int tipo)
  {

    while (topNode != nullptr)
    {
      if (topNode->dano.tipo == tipo)
      {
        tPosition toDelete = topNode;
        vidaActual += toDelete->dano.cantidad;
        topNode = topNode->next;
        delete toDelete;
        count--;
      }
    }
    return vidaActual;
  }

  ~ControlDeDano()
  {
    tPosition current = topNode;
    while (current != nullptr)
    {
      tPosition temp = current;
      current = current->next;
      delete temp;
    }
    delete topNode; // Clean up the top node
    vidaActual = 0; // Reset vidaActual
    count = 0;      // Reset count
  }
};