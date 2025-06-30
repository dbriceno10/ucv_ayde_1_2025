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
  }

  ~IntList()
  {
    clear();
    delete head;
    delete tail;
  }

  bool IsEmpty()
  {
    return size == 0;
  }

  tPosition first()
  {
    return (head->next != tail) ? head->next : tail;
  }

  tPosition last()
  {
    return tail;
  }

  void next(tPosition &pValue)
  {
    if (pValue != tail)
    {
      pValue = pValue->next;
    }
  }

  int &Get(tPosition v)
  {
    return v->data;
  }

  void insert(int d, tPosition v)
  {
    tPosition current = head;
    while (current->next != v && current->next != nullptr)
    {
      current = current->next;
    }
    if (current->next == v)
    {
      current->next = new Node(d, v);
      size++;
    }
  }

  void Delete(tPosition v)
  {
    if (v == tail)
      return; // No eliminar tail
    tPosition current = head;
    while (current->next != v && current->next != tail)
    {
      current = current->next;
    }
    if (current->next == v)
    {
      current->next = v->next;
      delete v;
      size--;
    }
  }

  void printl()
  {
    tPosition current = first();
    int count = 1;
    while (current != tail)
    {
      cout << "Elemento " << count << endl;
      cout << current << endl;
      cout << current->data << endl;
      cout << current->next << endl;
      cout << current->next->data << endl;
      cout << Get(current) << endl;
      cout << current << endl;
      current = current->next;
      count++;
    }
  }

  void clear()
  {
    tPosition current = first();
    while (current != tail)
    {
      tPosition toDelete = current;
      current = current->next;
      delete toDelete;
    }
    head->next = tail;
    size = 0;
  }
};

int main()
{
  IntList lista;
  lista.insert(1, lista.last());
  // lista.insert(2, lista.last());
  // lista.insert(3, lista.last());
  // lista.insert(4, lista.last());
  // lista.insert(5, lista.last());
  int opcion;
  do
  {
    cout << "\n--- MENU LISTA ENLAZADA ---\n";
    cout << "1. Insertar al final\n";
    cout << "2. Eliminar primer elemento\n";
    cout << "3. Imprimir lista\n";
    cout << "4. Limpiar lista\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opción: ";
    cin >> opcion;

    if (opcion == 1)
    {
      int valor;
      cout << "Ingrese el valor a insertar: ";
      cin >> valor;
      lista.insert(valor, lista.last());
      cout << "Valor agregado.\n";
    }
    else if (opcion == 2)
    {
      if (!lista.IsEmpty())
      {
        lista.Delete(lista.first());
        cout << "Primer elemento eliminado.\n";
      }
      else
      {
        cout << "La lista está vacía.\n";
      }
    }
    else if (opcion == 3)
    {
      cout << "Contenido de la lista:\n";
      lista.printl();
    }
    else if (opcion == 4)
    {
      lista.clear();
      cout << "Lista limpiada.\n";
    }
    else if (opcion == 5)
    {
      cout << "Saliendo...\n";
    }
    else
    {
      cout << "Opción no válida.\n";
    }
  } while (opcion != 5);

  return 0;
}