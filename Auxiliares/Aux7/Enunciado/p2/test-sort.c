#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort(char *noms[], int n);

// El arreglo de nombres de personas


int main() {
  printf("Primero un arreglo de un solo nombre: pedro gonzalez\n");
  char *noms1[]= {"pedro gonzalez"};
  sort(noms1, 1);
  printf("Resultado: %s\n", noms1[0]);
  printf("Ahora un arreglo bien ordenado: pedro gonzalez, ana perez\n");
  char *noms2[]= {"pedro gonzalez", "ana perez"};
  sort(noms2, 2);
  printf("Resultado: %s, %s\n", noms2[0], noms2[1]);
  if (strcmp(noms2[0], "pedro gonzalez")!=0 ||
      strcmp(noms2[1], "ana perez")!=0) {
    fprintf(stderr, "El resultado es incorrecto\n");
    exit(1);
  }
  printf("Ahora el arreglo: pedro gonzalez, luis gonzalez\n");
  char *noms3[]= {"pedro gonzalez", "luis gonzalez"};
  sort(noms3, 2);
  printf("Resultado: %s, %s\n", noms3[0], noms3[1]);
  if (strcmp(noms3[0], "luis gonzalez")!=0 ||
      strcmp(noms3[1], "pedro gonzalez")!=0) {
    fprintf(stderr, "El resultado es incorrecto\n");
    exit(1);
  }
  printf("Ahora el arreglo: ana perez, pedro gonzalez\n");
  char *noms4[]= {"ana perez", "pedro gonzalez"};
  sort(noms4, 2);
  printf("Resultado: %s, %s\n", noms4[0], noms4[1]);
  if (strcmp(noms4[0], "pedro gonzalez")!=0 ||
      strcmp(noms4[1], "ana perez")!=0) {
    fprintf(stderr, "El resultado es incorrecto\n");
    exit(1);
  }

  printf("Ahora un arreglo de 10 nombres\n");
  char *noms[]= {"pedro gonzalez", "juan perez" , "diego gonzalez", "ana gonzalez", "vero fernandez", "jose perez", "monica fernandez", "alberto perez", "maria fernandez", "tatiana jerez"};
  char *refs[]= {"maria fernandez", "monica fernandez", "vero fernandez", "ana gonzalez", "diego gonzalez", "pedro gonzalez", "tatiana jerez", "alberto perez", "jose perez", "juan perez"};
  printf("El arreglo desordenado es:\n");
  printf("--------------------------\n");
  for (int i= 0; i<10; i++)
    puts(noms[i]);
  sort(noms, 10);
  printf("\n");
  printf("El arreglo ordenado es:\n");
  printf("-----------------------\n");
  for (int i= 0; i<10; i++)
    puts(noms[i]);
  for (int i= 0; i<10; i++) {
    if (strcmp(noms[i],refs[i])!=0) {
      fprintf(stderr, "El resultado es incorrecto\n");
      exit(1);
    }
  }
  printf("Felicitaciones: test de prueba aprobado\n");
  return 0;
}
