#include <stdio.h>
typedef unsigned int uint;


/*
Aqui es una combinacion de las dos cosas
y vemos que el 'or' sirve para prender bits ya que 0 or algo = algo
y aplicamos lo visto el los dos ejercicios anteriormente
*/
uint repBits(uint x, int i, int k, uint val) {
    //hacemos una mascara de la forma 0^{32-k}1^{k}
	uint mask1 = ~((-1)<<k);
	//lo desplazamos i bits para que empieze de la posicion i
	uint mask2 = mask1 << i; 
	// desplazamos el valor i bits
	val <<= i;
	// apagamos los bits que queremos remplazar
	x &= ~mask2;
	// Prendemos los bits con el |
	x |= val;
	return x;
}

int main() {
    uint x = 0b1110;
    printf("Llamando repBits(0b1110, 0, 4, 0b1010) deberia de dar 0b1010 = 10 y el valor que da es %d\n", repBits(x,0,4,0b1010));
    printf("Llamando repBits(0b1110, 0, 4, 0b1111) deberia de dar 0b1111 = 15 y el valor que da es %d\n", repBits(x,0,4,0b1111));
    printf("Llamando repBits(0b1110, 4, 4, 0b1111) deberia de dar 0b11111110 = 254 y el valor que da es %d\n", repBits(x,4,4,0b1111));
    printf("Llamando repBits(0b1110, 1, 3, 0b0) deberia de dar 0b0 = 0 y el valor que da es %d\n", repBits(x,1,3,0b0));
}
