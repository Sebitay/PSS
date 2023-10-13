#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pss.h"

char * BLANK = "                                                                               ";

int main(int argc, char *argv[]) {

  if(argc!= 4){ // Error si los argumentos estan mal puestos
    fprintf(stderr,"Uso: ./definir <diccionario> <llave> <definicion>\n");
    abort();
  }

  FILE * dicc = fopen(argv[1],"r+");

  if(dicc == NULL){ // Error si no se puede abrir el archivo
    perror(argv[1]);
    abort();
  }

  fseek(dicc,0,SEEK_END);
  int n_lineas_dicc = ftell(dicc)/81; // Encuentra el numero de lineas en el diccionario

  int linea = hash_string(argv[2]) % n_lineas_dicc;
  char linea_dicc[80];
  int inicio = linea;
  fseek(dicc,linea*81,SEEK_SET);
  fgets(linea_dicc, 80, dicc);

  while(strcmp(linea_dicc,BLANK)){ // Mientras la linea no este en blanco

    if(!strncmp(linea_dicc,argv[2],strlen(argv[2]))){ // Revisa si ya esta definida la llave
      fprintf(stderr,"La llave %s ya se encuentra en el diccionario\n",argv[2]);
      abort();
    }

    if(linea == inicio-1){ // Revisa si esta lleno el diccionario
      fprintf(stderr,"%s: el diccionario esta lleno\n",argv[1]);
      abort();
    }

    linea++;// Aumenta a la siguiente linea
    if(linea > n_lineas_dicc){// Volver al inicio si se llega al final
      linea = 0;
    }
    fseek(dicc,linea*81,SEEK_SET);
    fgets(linea_dicc, 80, dicc);
  }
  
  // De no haber ningun error se escribe en el archivo
  fseek(dicc,linea*81,SEEK_SET);
  fputs(argv[2],dicc);
  fputs(":",dicc);
  fputs(argv[3],dicc);
  fclose(dicc);
}