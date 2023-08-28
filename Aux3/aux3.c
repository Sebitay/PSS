#include <stdio.h>
#include <string.h>

void to_lower(char* s){
    // char son 256 val y estan todas las minusculas juntas y las mayusculas tambien.
    char mayusc = 'A';
    char minusc = 'a';
    while(*s){//mientras s no sea 0
        if(*s < 'a'){
            *s -=(mayusc - minusc);
        }
        s++;
    }
}


void to_upper(char* s){
    // char son 256 val y estan todas las minusculas juntas y las mayusculas tambien.
    char mayusc = 'A';
    char minusc = 'a';
    while(*s){//mientras s no sea 0
        if(*s >= 'a'){
            *s +=(mayusc - minusc);
        }
        s++;
    }
}


int main(int argc, char** argv){
    char* palabra = argv[1];
    printf("%s\n",palabra);
    to_lower(palabra);
    printf("%s\n",palabra);
    to_upper(palabra);
    printf("%s\n",palabra);
}