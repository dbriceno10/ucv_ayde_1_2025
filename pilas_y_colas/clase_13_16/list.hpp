#ifndef LISTA_SIMPLE_HPP
#define LISTA_SIMPLE_HPP

template <typename T>
class ListaSimple {
private:
  struct Nodo {
    T dato;
    Nodo* siguiente;
    Nodo(const T& valor) : dato(valor), siguiente(nullptr) {}
  };
  Nodo* cabeza;
  int longitud;

public:
  ListaSimple() : cabeza(nullptr), longitud(0) {}

  ~ListaSimple() {
    while (cabeza) {
      Nodo* temp = cabeza;
      cabeza = cabeza->siguiente;
      delete temp;
    }
  }

  void insertarAlInicio(const T& valor) {
    Nodo* nuevo = new Nodo(valor);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    ++longitud;
  }

  void insertarAlFinal(const T& valor) {
    Nodo* nuevo = new Nodo(valor);
    if (!cabeza) {
      cabeza = nuevo;
    } else {
      Nodo* actual = cabeza;
      while (actual->siguiente) {
        actual = actual->siguiente;
      }
      actual->siguiente = nuevo;
    }
    ++longitud;
  }

  bool eliminar(const T& valor) {
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;
    while (actual) {
      if (actual->dato == valor) {
        if (anterior) {
          anterior->siguiente = actual->siguiente;
        } else {
          cabeza = actual->siguiente;
        }
        delete actual;
        --longitud;
        return true;
      }
      anterior = actual;
      actual = actual->siguiente;
    }
    return false;
  }

  bool buscar(const T& valor) const {
    Nodo* actual = cabeza;
    while (actual) {
      if (actual->dato == valor) return true;
      actual = actual->siguiente;
    }
    return false;
  }

  int size() const {
    return longitud;
  }

  bool vacia() const {
    return cabeza == nullptr;
  }
};

#endif // LISTA_SIMPLE_HPP