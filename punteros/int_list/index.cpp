#include <iostream>
using namespace std;

class IntList
{
  struct Node
  {
    int data;
    Node *next;
    Node(int d, Node *n = nullptr) : data(d), next(n) {}
  };
  Node *head = nullptr;
  Node *tail = nullptr;
  int size = 0;

public:
  typedef Node *tPosition;

  IntList() : size(0)
  {
    tail = new Node(0);
    head = new Node(0, tail);
  };

  ~IntList()
  {
    delete head;
    delete tail;
  }

  //*verificar si esta vacio
  bool IsEmpty()
  {
    return size == 0;
  }

  // obtener el primer nodo
  tPosition first()
  {
    // return (head->next !=tail)? head->next : nullptr;
    // return (head->next != tail) ? head->next : tail;
    if (head->next != tail)
    {
      return head->next;
    }
    else
    {
      return tail;
    }
  }
  // obtener el ultimo nodo
  tPosition last()
  {
    // // return (tail->next != nullptr) ? tail->next : nullptr;
    // // return (tail->next != nullptr) ? tail : head;
    // if (tail->next != nullptr)
    // {
    //   return tail;
    // }
    // else
    // {
    //   return head;
    // }
    return tail;
  }
  void next(tPosition &pValue)
  {
    // if(pValue != nullptr && pValue->next != nullptr) {
    //   pValue = pValue->next;
    // } else {
    //   pValue = tail; // Set to tail if next is null
    // }
    if (pValue != tail)
    {
      pValue = pValue->next;
    }
  }
  // obtener el valor del nodo
  int &Get(tPosition v)
  {
    return v->data;
  }
  // insertar
  void insert(int d, tPosition v)
  {
    tPosition current = head;
    while (current->next != nullptr)
    {
      current = current->next;
    }
    // current->next = nullptr;
    current->next = new Node(d, v);
    size++;
  }
  // borrar un nodo
  void Delete(tPosition v)
  {
    tPosition current = head;
    // if (v == tail)
    // {
    // delete v; // Delete the node
    // size--;
    //   return; // No action needed if trying to delete the tail
    // }
    while (current->next != v)
    {
      current = current->next;
    }
    delete v;
    current->next = v->next; // Link the previous node to the next node
    size--;
  }

  void printl()
  {
    tPosition current = first();
    while (current != tail)
    {
      cout << Get(current) << endl;
      next(current);
      current = current->next;
    }
  }
  void clear()
  {
    tPosition current = first();
    while (current != tail)
    {
      tPosition toDelete = current;
      next(current);
      delete toDelete;
    }
    head->next = tail; // Reset the list
    size = 0;
  }
};