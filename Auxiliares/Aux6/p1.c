#include <stdio.h>
#include <string.h>

void modificar(char *nom_dic, char *palabra, char *def, int n_lin, int ancho){
  FILE *f = fopen(nom_dic, "r+");
  char buf[ancho+1];
  while(fread(buf, 1, ancho, f) > 0){
    char *c = buf;
    while(*c != ':'){
      c++;
    }
    *c = '\0';
    if(strcmp(palabra, buf) == 0){
      // son iguales! encontramos la línea
      fseek(f, -ancho+strlen(palabra)+1, SEEK_CUR);
      fputs(def, f);
      while(fgetc(f) != ':'){
        fseek(f, -1, SEEK_CUR);
        fputc(' ', f);
      }
    }
  }
}

int main(){
  modificar("dict.txt", "nueve", "ola", 10, 48);
}


