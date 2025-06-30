// 6. Dada la siguiente secuencia de instrucciones indique que es lo que ocurre en cada línea.Indique si queda algún
//     espacio de memoria por liberar.
#include <iostream>
using namespace std;
class Nodo
{
public:
  int Info;
  Nodo *prox;
};
Nodo *P, *Q;
int *E;
int I;
int **F;

int main()
{
  P = new Nodo();
  E = new int();
  *E = 0;
  F = &E;
  P->prox = new Nodo();
  Q = &(*P);
  P = P->prox;
  Q->Info = 30;
  (*P).Info = Q->Info + 10;
  P->prox = new Nodo();
  P->prox->Info = Q->Info + P->Info + 10;
  P = (*P).prox;
  P->prox = nullptr;
  while (Q != nullptr)
  {
    *E = **F + Q->Info;
    Q = Q->prox;
  }
  F = new int *();
  *F = new int();
  **F = 1;
  delete *F;
  *F = &I;
  I = 5;
  std::cout << **F << std::endl;
  return 0;
}

/*

Claro, aquí tienes el análisis línea por línea de lo que ocurre en el código, y al final, qué memoria queda sin liberar:

Declaraciones
Se definen los punteros y variables necesarias.
Dentro de main()
P = new Nodo();

Reserva memoria para un nodo y P apunta a él.
E = new int();

Reserva memoria para un entero y E apunta a él.
*E = 0;

El valor apuntado por E es 0.
F = &E;

F apunta a E (no reserva memoria nueva, solo apunta).
P->prox = new Nodo();

Reserva memoria para otro nodo y lo enlaza como siguiente de P.
Q = &(*P);

Q apunta al mismo nodo que P.
P = P->prox;

P avanza al siguiente nodo (el que se creó en el paso 5).
Q->Info = 30;

El campo Info del primer nodo (al que apunta Q) se pone en 30.
(*P).Info = Q->Info + 10;

El campo Info del segundo nodo (al que apunta P) se pone en 40.
P->prox = new Nodo();

Reserva memoria para un tercer nodo y lo enlaza como siguiente de P.
P->prox->Info = Q->Info + P->Info + 10;

El campo Info del tercer nodo se pone en 30 + 40 + 10 = 80.
P = (*P).prox;

P avanza al tercer nodo.
P->prox = NULL;

El campo prox del tercer nodo se pone en NULL (fin de la lista).
while ( Q !=  NULL ) { *E = *F + Q->Info; Q = Q->prox; }

Recorre la lista desde el primer nodo, sumando el valor apuntado por F (que es E, valor 0) y el campo Info de cada nodo, guardando el resultado en *E.
Al final del ciclo, Q queda en NULL.
F = new int*();

Reserva memoria para un puntero a entero y F apunta a él.
*F = new int();

Reserva memoria para un entero y el puntero apuntado por F apunta a él.
**F = 1;

El valor apuntado por el puntero apuntado por F se pone en 1.
delete *F;

Libera la memoria del entero apuntado por *F.
*F = &I;

El puntero apuntado por F ahora apunta a I.
I=5;

I se pone en 5.
std::cout << **F << std::endl;

Imprime el valor de I (5).
return 0;

Termina el programa.
Memoria que queda sin liberar
No se libera la memoria de los nodos creados con new Nodo().
(Tres nodos: el primero, el segundo y el tercero).
No se libera la memoria de E (el primer entero creado con new int()).
No se libera la memoria de F (el puntero a entero creado con new int*()).
Solo se libera el entero creado con *F = new int(); (línea 16, liberado en línea 18).

Resumen final
Quedan sin liberar:

Los tres nodos de la lista (new Nodo()).
El entero creado con E = new int();.
El puntero creado con F = new int*();.
Liberado correctamente:

El entero creado con *F = new int(); (línea 16).

*/