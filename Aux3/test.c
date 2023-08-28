#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void elim(char *str, char *pat){
    char *change = str;
    int letter = 0;
    unsigned long count = 0;
    int patlen = strlen(pat);
    int strlength = strlen(str);
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
            if(letter == 0){
                *change = *str;
                str++;
                change++;
            }
            pat -= letter;
            str = str - letter;
            while(letter > 0){
                *change = *str;
                str++;
                change++;
                letter--;
            }
        }
    }
    str = str - letter;
    while(letter > 0){
        *change = *str;
        str++;
        change++;
        letter--;
    }
    *change = 0;
    str = str - strlength;
    return; 
}


void elim2(char *str,char *pat){
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
    printf("%lu\n",strlength - count * patlen);
    char* ptr = (char*) malloc(strlength - count * patlen);
    printf("%lu\n",sizeof(ptr));
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

int main(){
    char s1[] = "111011001";
    char* s2 = eliminados(s1,"10");
    printf("%s\n",s1);
    printf("'%s'\n",s2);
    printf("%lu\n", sizeof(s2));
    elim2(s1, "10");
    printf("'%s'\n",s1);
}