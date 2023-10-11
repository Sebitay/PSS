typedef struct nodo {
  int x;
  struct nodo *izq, *der;
} Nodo;

Nodo *createNodo(int x, Nodo *izq, Nodo *der);
void printcArbol(Nodo *a);
void printiArbol(Nodo *a);
