#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int reemplazarNodoK(Nodo **pa, int k, Nodo *b);

int main(void){
  Nodo *arbol = createNodo('s',
      createNodo('r', NULL, NULL),
      createNodo('u',
        createNodo('t', NULL, NULL),
        NULL));
  Nodo *b = createNodo('v', NULL, createNodo('w', NULL, NULL));

  printcArbol(arbol);
  printf("\n");

  printf("resultado = %d\n", reemplazarNodoK(&arbol, 2, b));

  printcArbol(arbol);
  printf("\n");

  return 0;
}

int reemplazarNodoK(Nodo **pa, int k, Nodo *b){
  Nodo *a = *pa;
  if(a == NULL) return 0;
  int cnt_left = reemplazarNodoK(&a->izq, k, b);
  if(cnt_left == k){
    return k;
  }
  else if(cnt_left == k-1){
    *pa = b;
    return k;
  }
  int cnt_right = reemplazarNodoK(&a->der, k-cnt_left-1, b);
  return cnt_left+1+cnt_right;
}
