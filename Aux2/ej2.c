#include <stdio.h>
typedef unsigned int uint;
/*
Forma util de pensarlo:
Vean que x es un arreglo de 32 posiciones y queremos recorrer una ventana de tamaño n e ir comparando bit a bit si son iguales o no!
O sea que tenemos que apagar el resto de posiciones que no comparamos y luego preguntar si es igual a x 
Preguntas:
¿Porque podemos aplicar tranquilamente un shift right (>>) osea, no preocuparnos de que haya un 1 o no?
¿Que entrega sizeof(int)?
¿Que hace la mascara?
*/
int posicionBits(uint x, uint p, int n){
    int m = ~(-1 << n);
    for(int i = 0; i<sizeof(int)*8-n+1; i++){
        uint val = ((x >> i) & m);
        if (val == p)
            return i;
    }
    return -1;
}

int main(){
    uint x = 0b0001110;
    uint p = 0b111;
    printf("El patron ocurre primero en la posicion 1 y obtenemos que ocurren en la posicion: %d\n",posicionBits(x,p,3));

    p = 0b0;
    printf("El patron ocurre primero en la posicion 0 y obtenemos que ocurren en la posicion: %d\n",posicionBits(x,p,1));

    p = 0b1111;
    printf("El patron ocurre no ocurre y obtenemos que: %d\n",posicionBits(x,p,4));

    uint a = 0b011;
    printf("El patron ocurre primero en la posicion 2 y obtenemos que ocurren en la posicion: %d\n",posicionBits(x,a,3));
}