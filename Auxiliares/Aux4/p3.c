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
typedef struct pila {
  Nodo *primero; // Puntero al primer nodo de la cola, no debe tener la palabra clave struct antes de Nodo, solo se utiliza cuando es una definición recursiva.
  Nodo *ultimo; // Puntero al último nodo de la cola
} Cola;

Cola *creaCola(){
  Cola *c = malloc(sizeof(Cola));
  c->primero = NULL;
  c->ultimo = NULL;
  return c;
}

void put(Cola *q, int *x){
  Nodo *n = malloc(sizeof(Nodo));
  n->info = x;
  n->sgte = NULL;
  if (q->primero == NULL){
    q->primero = n;
    q->ultimo = n;
    return;
  }
  Nodo *pu = q->primero; // La única diferencia con la cola de p2, es como se inserta el nodo, en este caso, se inserta al inicio de la cola.
  n->sgte = pu; 
  q->primero = n;
  return;
}

int *get(Cola *q){
  if (q->primero == NULL){
    return NULL;
  }
  Nodo *p = q->primero;
  int *resultado = p->info;
  q->primero = p->sgte;
  if (p->sgte == NULL){
    q->ultimo = NULL;
  }
  free(p);
  return resultado;
}


void freeCola(Cola *q){
  if (q->primero == NULL){
    free(q);
    return;
  }
  Nodo *n = q->primero;
  q->primero = n->sgte;
  free(n);
  freeCola(q);
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