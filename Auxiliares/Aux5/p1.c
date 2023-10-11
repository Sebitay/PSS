#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void podar(Nodo **pa, int y);

int main(void){
  Nodo *arbol = 
    createNodo(4, 
        createNodo(2,
          createNodo(1, NULL, NULL),
          createNodo(3, NULL, NULL)),
        createNodo(6,
          createNodo(5, NULL, NULL),
          NULL));
  printiArbol(arbol);
  printf("\n");
  podar(&arbol, 5);
  printiArbol(arbol);
  printf("\n");
  return 0;
}

void podar(Nodo **pa, int y){
  Nodo *a = *pa;
  if(a == NULL){
    return;
  }
  if(a->x <= y){
    podar(&a->der, y);
  }
  else{
    podar(&a->izq, y);
    *pa = a->izq;
  }
}
