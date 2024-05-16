#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/wait.h"

typedef struct nodo {
  char *val;
  struct nodo *izq, *der;
} Nodo;

Nodo *crearArbol(char *val, Nodo *izq, Nodo *der){
  Nodo *abb = malloc(sizeof(Nodo));
  abb->val = val;
  abb->izq = izq;
  abb->der = der;
  return abb;
}

void printArbol(Nodo *a){
  if (a==NULL){
    printf(" ");
    return;
  }
  printf("(");
  printArbol(a->izq);
  printf(") ");
  printf("%s",a->val);
  printf(" (");
  printArbol(a->der);
  printf(")");
}

int leer(int fd, void *buf, int n) {
  if (n==0)
    return 0;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
    return 1; // fracaso: error o fin del archivo/pipe/socket
    n-= rc; // descontamos los bytes leídos
    buf= (char*)buf + rc; // avanzamos el buffer
  } while (n>0); // mientras no leamos todo lo que esperamos
  return 0; // exito
}

Nodo *buscar(Nodo *a, char *val, char p) {
  if (a==NULL)
    return NULL;
  if (strcmp(val, a->val)==0){
    return a;
  }
  if (p==1){
    Nodo *rizq = buscar(a->izq, val, 1);
    if (rizq!=NULL){
      return rizq;
    }
    else {
      return buscar(a->der, val, 1);
    }
  }
  else {
    int fds[2];
    pipe(fds); // 0: lectura y 1: escritura
    int pid = fork();
    if (pid==0){ // proceso hijo
      Nodo *rizq=buscar(a->izq, val, p/2);
      write(fds[1], &rizq, sizeof(rizq));
      exit(0); // buena practica
      return NULL; //evitar warning de compilador
    }
    else {  // proceso padre
      close(fds[1]);
      Nodo *rder=buscar(a->der, val, p/2);
      Nodo *rizq;
      leer(fds[0], &rizq, sizeof(rizq));
      close(fds[0]);
      waitpid(pid, NULL, 0);
      return rizq!=NULL ? rizq : rder;
    }
  }
}


int main(){
  Nodo *b = crearArbol("2",
    crearArbol("5", NULL, NULL),
    crearArbol("38", NULL, NULL));
  Nodo *c = crearArbol("24",
    crearArbol("12", NULL, NULL),
    crearArbol("3", NULL, NULL));
  Nodo *a = crearArbol("100", b, c);
  printArbol(a);
  printf("\n");
  Nodo *r = buscar(a, "2", 2);
  printArbol(r);
  printf("\n");
  return 0;
}
