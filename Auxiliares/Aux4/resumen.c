#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void printList(int *list, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", list[i]);
  }
  printf("\n");
}
// este esta en el stack!
char* responderSaludo() {
  char respuesta[] = "Este es un arreglo de caracteres";
  return respuesta;
}
//este esta en el heap!
char* responderSaludo2() {
  char respuesta[] = "Este string persiste en memoria";
  char *res = malloc(strlen(respuesta) + 1);
  strcpy(res, respuesta);
  return res;
}

typedef struct Punto{
  int x;
  int y;
} Punto;

int main(int argc, char *argv[]) {
  /*
  El operador * permite instanciar un puntero que 
  apunta a una dirección de memoria de una variable.
  El operador & permite obtener la dirección de 
  memoria de una variable.
  */
  int a = 5;
  int p[3] = {a, a*2, a*3}; // p apunta a la dirección de memoria de a
  printf("p = %p \n", (void *) p);
  printf("a = %d\n", *p);
  printList(p, 3);
  // También se puede acceder a la variable y asignarle
  // un nuevo valor de la siguiente manera:
  int *ptr = p;
  *ptr = 7;
  printList(p, 3);
  printf("a = %d\n", a);
  // Se aplica aritmética de punteros, por ejemplo:
  ptr++;
  printf("p + 1 = %p\n", (void *) ptr);
  *ptr = 9;
  printList(p, 3);

  // Para malloc, se debe incluir stdlib.h, esta función
  // permite reservar memoria en el heap.
  char hola[] = "hola mundo!";
  printf("%s\n", hola);
  char *res = responderSaludo();
  //printf("%s\n", res); // Esto no funciona
  res = responderSaludo2();
  printf("%s\n", res); // Esto sí funciona

  // Para liberar memoria, se debe usar free
  free(res);
  printf("%s\n", res); // ya no se puede acceder a res

  // Las estructuras se pueden definir de la siguiente manera:
  Punto p1 = {1, 2};
  Punto p2 = {.y = 3, .x = 4};
  printf("p1 = (%d, %d)\n", p1.x, p1.y);
  printf("p2 = (%d, %d)\n", p2.x, p2.y);
  Punto *p3 = &p1;
  (*p3).x = 5;
  p3->y = 6;
  printf("p3 = (%d, %d)\n", p3->x, p3->y);
  return 0;
}