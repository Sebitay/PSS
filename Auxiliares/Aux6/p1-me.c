#include <stdio.h>
#include <string.h>

void modificar(char *nom_dic, char *palabra, char *def, int n_lin, int ancho);

int main(int argc, char *argv[]) {
    // Funcion para no tener que compilar cada vez que queramos cambiar definiciones
    if (argc != 4) {
        printf("Uso: %s <diccionario> <palabra> <definicion>\n", argv[0]);
        return 1;
    }
    modificar(argv[1], argv[2], argv[3], 11, 48);
}

void modificar(char *nom_dic, char *palabra, char *def, int n_lin, int ancho) {
    // Abrimos el archivo
    FILE *f = fopen(nom_dic, "r+");
    int n = strlen(palabra);
    // Guardamos un buffer para leer la primera palabra
    char buf[n+1];
    buf[n] = 0;
    while(fgets(buf, n+1, f)) { // Leemos n chars de f y lo dejamos en buf
        // Verificamos si es la palabra (caso borde: que sucede con palabras que empiezan igual? ej: casa y casamiento)
        if(strcmp(buf, palabra) == 0) {
            // Nos 'saltamos' el primer ':' 
            fseek(f, 1, SEEK_CUR);
            // Reemplazamos con la definicion nueva
            fputs(def, f);
            // Limpiamos lo que estaba antes
            char tmp;
            while((tmp=fgetc(f))!= ':') {
                fseek(f, -1, SEEK_CUR); // Importante! todas las funciones avanzan el puntero en f, 
                fputc(' ', f);          // por lo que si queremos reemplazar caracteres tenemos que retroceder un poquito
            }
            break;
        }
        // Si no, avanzamos lo necesario: con fgets leimos n bytes y una linea tiene ancho bytes
        fseek(f, ancho-n, SEEK_CUR);
    }
    // Importante! Cerramos el archivo
    fclose(f);
}
