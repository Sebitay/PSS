#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "elim.h"

void eliminar(char *str, char *pat) {
    char *change = str;
    unsigned long patlen = strlen(pat);
    int letter = 0;
    while(*str){
        *change = *str;
        change++;
        if(*str == *pat){
            letter++;
            pat++;
            if(letter == patlen){
                change -= letter;
                pat -= letter;
                letter = 0;
            }
        }else{
            pat -= letter;
            letter = 0;
            if(*str == *pat){
                letter++;
                pat++;
                if(letter == patlen){
                    change -= letter;
                    pat -= letter;
                    letter = 0;
                }
            }
        }
        str++;
    }
    *change = 0;
    return;
}

char *eliminados(char *str, char *pat) {
    int letter= 0;
    int count = 0;
    unsigned long strlength = strlen(str);
    unsigned long patlen = strlen(pat);
    while(*str){
        if(*str == *pat){
            letter++;
            pat++;
            if(letter == patlen){
                count++;
                pat -= letter;
                letter = 0;
            }
            str++;
        }else{
            if(letter==0){
                str++;
            }
            pat -= letter;
            letter = 0;
        }
    }
    str -= strlength;
    pat -= letter;
    char* ptr = (char*) malloc(strlength - count * patlen);
    letter = 0;
    count = 0;
    while(*str){
        if(*str == *pat){
            letter++;
            pat++;
            if(letter == patlen){
                pat -= letter;
                letter = 0;
            }
            str++;
        }else{
            if(letter==0){
                ptr += count;
                *ptr = *str;
                ptr -= count;
                count++;
                str++;
            }
            pat -= letter;
            str -= letter;
            while(letter>0){
                ptr += count;
                *ptr = *str;
                ptr -= count;
                count++;
                str++;
                letter--;
            }
        }
    }
    str -= letter;
    while(letter>0){
        ptr += count;
        *ptr = *str;
        ptr -= count;
        count++;
        str++;
        letter--;
    }
    return ptr;
}
