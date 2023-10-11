#include <stddef.h>
#include "prev.h"

void asignarPrev(Nodo *t, Nodo **pprev) {
  if(t==NULL){
    t = *pprev;
    return;
  }
  if((t -> izq) != NULL){
    asignarPrev(t->izq, pprev);
  }
  (t -> prev) = *pprev;
  (t -> prox) = NULL;
  if(*pprev != NULL){
    ((*pprev)->prox) = t;
  }
  (*pprev) = t;
  if((t -> der) != NULL){
    asignarPrev((t->der), pprev);
    return;
  }
}