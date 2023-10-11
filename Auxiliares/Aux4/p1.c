#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// Estructura nodo, creada con typedef que permite generar un alias. El primer nombre se utiliza para su definición recursiva.
typedef struct nodo {
  int info; // Información del nodo
  struct nodo * sgte; // Puntero al siguiente nodo, al ser una definición recursiva, se debe utilizar la palabra clave struct antes del nombre de la estructura.
} Nodo; // Alias de la estructura

// Función que imprime una lista enlazada
void printList ( Nodo *n ) {
  if ( n == NULL ) { // Si el nodo es nulo, se termina la función
    printf ( "\n" );
    return;
  }
  printf ( "%d " , n->info ); // Se imprime la información del nodo
  printList ( n->sgte ); // Se llama a la función con el siguiente nodo
}

// Función que crea una lista enlazada a partir de un arreglo y el tamaño del arreglo
Nodo *createNodeList(int *list, int size) {
  Nodo *n = malloc(sizeof(Nodo)); // Se reserva memoria para el nodo
  n->info = *list; // Se asigna la información del nodo
  if (size > 1) { // Si el tamaño es mayor a 1, se crea el siguiente nodo
    n->sgte = createNodeList(list + 1, size - 1);
  }
  else { // Si el tamaño es 1, se asigna NULL al siguiente nodo
    n->sgte = NULL;
  }
  return n; // Se retorna el nodo
}

// Función que agrega un nodo al final de una lista enlazada
void append ( Nodo ** pa , Nodo * b ){
  if ( *pa == NULL ) { // Si el nodo es nulo, se termina la función añadiendo el nodo b
    *pa = b ;
  }
  else { // Si el nodo no es nulo, se llama a la función con el siguiente nodo, hasta llegar al último nodo
    append ( &(*pa)->sgte , b );
  }
  return;
}

int main(){
  printf("ejemplo 1\n");
  int array_a[] =  {3, 1};
  Nodo *a = createNodeList(array_a, 2);
  printf("a = ");
  printList(a);
  int array_b[] = {7, 8, 4};
  Nodo *b = createNodeList(array_b, 3);
  printf("b = ");
  printList(b);
  append(&a, b);
  printf("a = ");
  printList(a);
  printf("ejemplo 2\n");
  Nodo *a2 = NULL;
  printf("a = ");
  printList(a2);
  int array_b2[] = {7, 8, 4};
  Nodo *b2 = createNodeList(array_b2, 3);
  printf("b = ");
  printList(b2);
  append(&a2, b2);
  printf("a = ");
  printList(a2);
  return 0;
}
