#include <stdio.h>

typedef unsigned int uint;

//Preguntas interesantes:
/*
¿Porque podemos aplicar tranquilamente un shift right (>>)?
¿Que entrega sizeof(int)?
*/
int bits1(uint n){
    int k = 0;
    for(int i = 0; i<sizeof(int)*8; i++){
        uint m = 1;
        k = k + (m & (n>>i));
    }
    return k;
}


int main(){
    uint n = 0b011001;
    printf("El numero esperado es 3 y el actual es %d\n",bits1(n));

    n = 0b00000000;
    printf("El numero esperado es 0 y el actual es %d\n",bits1(n));

    n = (uint) -1;
    printf("El numero esperado es 32 y el actual es %d\n",bits1(n));

    n = 0b10000000000000000000000000000;
    printf("El numero esperado es 1 y el actual es %d\n",bits1(n));

}