

// Supón que la estructura es:
struct Nodo
{
  int valor;
  Nodo *hijoIzq;
  Nodo *hijoDer;
};

// Busca un valor en un BST
bool buscar(Nodo *raiz, int valor)
{
  if (!raiz)
    return false;
  if (valor == raiz->valor)
    return true;
  if (valor < raiz->valor)
    return buscar(raiz->hijoIzq, valor);
  return buscar(raiz->hijoDer, valor);
}

// Cuenta nodos de A presentes en B
int contarPresentes(Nodo *raizA, Nodo *raizB)
{
  if (!raizA)
    return 0;
  int presente = buscar(raizB, raizA->valor) ? 1 : 0;
  return presente +
         contarPresentes(raizA->hijoIzq, raizB) +
         contarPresentes(raizA->hijoDer, raizB);
}

// Cuenta total de nodos en A
int contarNodos(Nodo *raizA)
{
  if (!raizA)
    return 0;
  return 1 + contarNodos(raizA->hijoIzq) + contarNodos(raizA->hijoDer);
}

// Calcula el porcentaje
float porcentaje(Nodo *raizA, Nodo *raizB)
{
  int total = contarNodos(raizA);
  if (total == 0)
    return 0.0f;
  int presentes = contarPresentes(raizA, raizB);
  return (presentes * 100.0f) / total;
}