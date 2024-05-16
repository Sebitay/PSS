#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
  char x;
  struct nodo *izq, *der;
} Nodo;

Nodo *desbalancear(Nodo **pa);
char *toString(Nodo *a);
Nodo *makeNodo(char x, Nodo *izq, Nodo *der);
void delNodo(Nodo *a);

int main(int argc, char* argv[]) {
  Nodo *a, *u;
  char *sa, *su;
  a = makeNodo('a', NULL, NULL);
  u = desbalancear(&a);

  sa = toString(a);
  su = toString(u);
  printf("a: %s\n", sa);
  printf("u: %s\n", su);
  free(sa);
  free(su);

  delNodo(a);

  a = makeNodo('v', 
                makeNodo('s', 
                          NULL, 
                          makeNodo('u', NULL, NULL)),
                makeNodo('x', 
                          makeNodo('w', NULL, NULL), 
                          NULL));

  u = desbalancear(&a);

  sa = toString(a);
  su = toString(u);
  printf("a: %s\n", sa);
  printf("u: %s\n", su);
  free(sa);
  free(su);

  delNodo(a);

  return 0;
}


Nodo *desbalancear(Nodo **pa) {
  Nodo *a = *pa;
  if (a == NULL) return NULL;
  Nodo *izq = a->izq;
  Nodo *der = a->der;

  if (izq) {
    Nodo *ultIzq = desbalancear(&izq);
    ultIzq->der = a;
    a->izq = NULL;
    a->der = NULL;
    *pa = izq;
  } 
  if (der) {
    Nodo *ultDer = desbalancear(&der);
    a->der = der;
    a = ultDer;
  } 
  return a;
}

char *toString(Nodo *a) {
  char *s, *si, *sd;
  if (a==NULL) {
    s = malloc(2);
    strcpy(s, "-");
  } else {
    si = toString(a->izq);
    sd = toString(a->der);
    int in = strlen(si);
    int dn = strlen(sd);
    s = malloc(dn + in + 6);
    snprintf(s, dn + in + 6, "(%s %c %s)", si, a->x, sd);
    free(si);
    free(sd);
  }
  return s;
}

Nodo *makeNodo(char x, Nodo *izq, Nodo *der) {
  Nodo *a = malloc(sizeof(Nodo));
  a->x = x;
  a->izq = izq;
  a->der = der;
  return a;
}

void delNodo(Nodo *a) {
  if (a!=NULL) {
    delNodo(a->izq);
    delNodo(a->der);
    free(a);
  }
}
