#include <string>
using namespace std;

// Estructura de material
struct Material
{
  int ID;
  string nombre;
  float pureza;
  Material *siguiente; // Para lista enlazada
};

// Lista de materiales (para la cola)
class ListaMateriales
{
public:
  Material *inicio;
  Material *fin;

  ListaMateriales() : inicio(nullptr), fin(nullptr) {}

  // Agrega material al final
  void agregar(Material *nuevo)
  {
    nuevo->siguiente = nullptr;
    if (!inicio)
    {
      inicio = fin = nuevo;
    }
    else
    {
      fin->siguiente = nuevo;
      fin = nuevo;
    }
  }

  // Vacía la lista y retorna el puntero al inicio
  Material *consumirTodo()
  {
    Material *lista = inicio;
    inicio = fin = nullptr;
    return lista;
  }

  // Calcula pureza promedio
  float purezaPromedio()
  {
    int cantidad = 0;
    float suma = 0.0f;
    for (Material *actual = inicio; actual; actual = actual->siguiente)
    {
      suma += actual->pureza;
      cantidad++;
    }
    return cantidad ? suma / cantidad : 0.0f;
  }

  // Liberar memoria de la lista
  void liberar()
  {
    Material *actual = inicio;
    while (actual)
    {
      Material *sig = actual->siguiente;
      delete actual;
      actual = sig;
    }
    inicio = fin = nullptr;
  }
};

// Cola de listas de materiales
class ColaDeListas
{
  struct NodoCola
  {
    ListaMateriales *lista;
    NodoCola *siguiente;
    NodoCola(ListaMateriales *l) : lista(l), siguiente(nullptr) {}
  };
  NodoCola *frente, *final;

public:
  ColaDeListas() : frente(nullptr), final(nullptr) {}

  // Encolar una lista de materiales
  void encolar(ListaMateriales *lista)
  {
    NodoCola *nuevo = new NodoCola(lista);
    if (!frente)
    {
      frente = final = nuevo;
    }
    else
    {
      final->siguiente = nuevo;
      final = nuevo;
    }
  }

  // Desencolar y obtener la lista más antigua
  ListaMateriales *desencolar()
  {
    if (!frente)
      return nullptr;
    NodoCola *tmp = frente;
    ListaMateriales *lista = tmp->lista;
    frente = frente->siguiente;
    if (!frente)
      final = nullptr;
    delete tmp;
    return lista;
  }

  // Liberar toda la cola y sus listas
  void liberar()
  {
    while (frente)
    {
      ListaMateriales *lista = desencolar();
      if (lista)
        lista->liberar();
      delete lista;
    }
  }
};

// Ejemplo de uso
int main()
{
  ColaDeListas almacen;

  // Crear una lista de materiales y agregar materiales
  ListaMateriales *lote1 = new ListaMateriales();
  lote1->agregar(new Material{1, "Hierro", 98.5f, nullptr});
  lote1->agregar(new Material{2, "Cobre", 95.2f, nullptr});
  almacen.encolar(lote1);

  ListaMateriales *lote2 = new ListaMateriales();
  lote2->agregar(new Material{3, "Aluminio", 99.1f, nullptr});
  almacen.encolar(lote2);

  // Consumir materiales (FIFO)
  ListaMateriales *salida = almacen.desencolar();
  Material *m = salida->consumirTodo();
  // Mostrar materiales consumidos
  for (Material *actual = m; actual; actual = actual->siguiente)
  {
    // Ejemplo de impresión
    // cout << actual->ID << " " << actual->nombre << " " << actual->pureza << endl;
  }
  // Calcular pureza promedio
  float prom = salida->purezaPromedio();
  // cout << "Pureza promedio: " << prom << endl;

  salida->liberar();
  delete salida;

  almacen.liberar();
  return 0;
}