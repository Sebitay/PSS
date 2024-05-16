#include <stdio.h>

typedef struct nodo {
  int x;
  int y;
  struct nodo *izq;
  struct nodo *der;
} Nodo;


Nodo *g(Nodo *a, int z, int *pres) {
  goto cond1;
ciclo:
  if (z>=a->x) goto sino;
  a= a->izq;
  goto cond1;
sino:
  a= a->der;
cond1:
  if (a!=NULL) goto cond2;
  return a;
cond2:
  if (a->x!=z) goto ciclo;
fin:
  *pres= a->y;
  return a;
}
