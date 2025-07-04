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
  // int curarPorTipo(int tipo)
  // {

  //   while (topNode != nullptr)
  //   {
  //     if (topNode->dano.tipo == tipo)
  //     {
  //       tPosition toDelete = topNode;
  //       vidaActual += toDelete->dano.cantidad;
  //       topNode = topNode->next;
  //       delete toDelete;
  //       count--;
  //     }
  //   }
  //   return vidaActual;
  // }

  int curarPorTipo(int tipo)
{
    tPosition current = topNode;
    tPosition prev = nullptr;
    while (current != nullptr)
    {
        if (current->dano.tipo == tipo)
        {
            vidaActual += current->dano.cantidad;
            tPosition toDelete = current;
            if (prev == nullptr)
            {
                // Borrando el tope
                topNode = current->next;
                current = topNode;
            }
            else
            {
                prev->next = current->next;
                current = current->next;
            }
            delete toDelete;
            count--;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
    return vidaActual;
}

  int getVidaActual() const
  {
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
    // delete topNode; // Clean up the top node
    vidaActual = 0; // Reset vidaActual
    count = 0;      // Reset count
  }


};

int main(int argc, char const *argv[])
{
  ControlDeDano control(100);
  Dano d1 = {1, 10};
  Dano d2 = {2, 20};
  Dano d3 = {1, 30};
  control.recibirDano(d1);
  control.recibirDano(d2);
  control.recibirDano(d3);
  cout << "Vida actual: " << control.curarDano() << endl;     // Should return 90
  cout << "Vida actual: " << control.curarNDanos(2) << endl;  // Should return 100
  cout << "Vida actual: " << control.curarPorTipo(1) << endl; // Should return 100
  Dano d4 = {1, 30};                                          // Reset d1 to original state
  control.recibirDano(d4);                                    // Reapply d1
  cout << "Vida actual: " << control.getVidaActual() << endl; // Should return 100
  return 0;
}
