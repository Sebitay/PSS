#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

Nodo* createNodo(int x, Nodo *izq, Nodo *der) {
  Nodo *a = (Nodo*)malloc(sizeof(Nodo));
  a->x = x;
  a->izq = izq;
  a->der = der;
  return a;
}

void printcArbol(Nodo *a) {
  if(a == NULL) return;
  printcArbol(a->izq);
  printf("%c ", a->x);
  printcArbol(a->der);
}

void printiArbol(Nodo *a) {
  if(a == NULL) return;
  printiArbol(a->izq);
  printf("%i ", a->x);
  printiArbol(a->der);
}
