#include "stdio.h"
#include "stdlib.h"
#include "string.h"
// Incluimos la estructura nodo creada en p1
typedef struct nodo {
  int *info ;
  struct nodo * sgte ;
} Nodo;

void printList ( Nodo *n ) {
  if ( n == NULL ) {
    printf ( "\n" );
    return;
  }
  printf ( "%d " , *n->info );
  printList ( n->sgte ); // Se llama a la función con el siguiente nodo
}

// Ahora vamos con la p2
typedef struct cola {
  Nodo *primero; // Puntero al primer nodo de la cola, no debe tener la palabra clave struct antes de Nodo, solo se utiliza cuando es una definición recursiva.
  Nodo *ultimo; // Puntero al último nodo de la cola
} Cola;

// La estructura permite mantener la información del primer y último nodo, facilitando la inserción y eliminación de nodo bajo un orden constante.
Cola *creaCola(){
  Cola *c = malloc(sizeof(Cola)); // Se reserva memoria para la cola
  c->primero = NULL; // Se asigna NULL al primer nodo
  c->ultimo = NULL; // Se asigna NULL al último nodo
  return c; // Se retorna la cola
}

// Función que agrega un nodo al final de una cola
void put(Cola *q, int *x){
  Nodo *n = malloc(sizeof(Nodo)); // Se reserva memoria para el nodo
  n->info = x; // Se asigna la información del nodo
  n->sgte = NULL; // Se asigna NULL al siguiente nodo
  if (q->primero == NULL){ // Si el primer nodo es nulo, se asigna el nodo a la cola
    q->primero = n; // Como es el único nodo en la estructura, tanto el primero como el último nodo son el mismo.
    q->ultimo = n;
    return; 
  }
  Nodo *pu = q->ultimo;  // Se obtiene el último nodo de la cola
  pu->sgte = n; // Se asigna el nodo como el siguiente nodo del último nodo
  q->ultimo = n; // Se asigna el nodo como el último nodo de la cola
  return;
}

// Función que obtiene el primer nodo de una cola
int *get(Cola *q){
  if (q->primero == NULL){ // Si el primer nodo es nulo, se retorna NULL
    return NULL;
  }
  Nodo *p = q->primero; // Se obtiene el primer nodo de la cola
  int *resultado = p->info; // Se obtiene la información del nodo
  q->primero = p->sgte; // Se asigna el siguiente nodo como el primer nodo de la cola
  if (p->sgte == NULL){ // Si el siguiente nodo es nulo, se asigna NULL al último nodo de la cola, (pues era el único nodo en la cola)
    q->ultimo = NULL;
  }
  free(p); // Se libera la memoria del nodo
  return resultado;
}

// Función que libera la memoria de una cola
void freeCola(Cola *q){
  if (q->primero == NULL){ // Si el primer nodo es nulo, se termina la función
    free(q); // Se libera la memoria de la cola
    return;
  }
  Nodo *n = q->primero; // Se obtiene el primer nodo de la cola
  q->primero = n->sgte; // Se asigna el siguiente nodo como el primer nodo de la cola
  free(n); // Se libera la memoria del nodo
  freeCola(q); // Se llama a la función con el siguiente nodo
}

void printCola(Cola *q){
  printf("Cola: ");
  if (q->primero == NULL){
    printf("Vacio\n");
    return;
  }
  Nodo *p = q->primero;
  printf("%d ", *p->info);
  printList(p->sgte);
}


int main(){
  Cola *q = creaCola();
  printCola(q);
  int n[] = {1, 2, 3, 4, 5};
  put(q, n);
  printCola(q);
  put(q, n+1);
  put(q, n+2);
  printCola(q);
  int *x = get(q);
  printf("x = %d\n", *x);
  printCola(q);
  x = get(q);
  printf("x = %d\n", *x);
  printCola(q);
  put(q, n+3);
  put(q, n+4);
  printCola(q);
  printf("free cola\n");
  freeCola(q);
  printf("x = %d\n", *x);
  printCola(q);
  return 0;
}
