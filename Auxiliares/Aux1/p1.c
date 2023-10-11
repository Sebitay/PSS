#include <stdio.h> // printf
#include <stdlib.h> // atois

int factorial(int n);

int main(int argc, char** argv) {
    /* Parte A */
    int celsius = 23;
    float farenheit = celsius * 9.f/5.f + 32.f;
    printf("23°C son %.1f°F\n", farenheit);

    /* Parte B */
    // Usando la función definida más abajo
    int resultado;
    resultado = factorial(9);
    printf("El factorial de 9 es %d\n", resultado);

    /* Parte C */
    // Tomamos los inputs desde argv
    if (argc == 1) { // Esto es simplemente para garantizar que el ejecutable tenga la cantidad de argumentos correcta
        printf("Error en la cantidad de argumentos (%d <= 1)\n", argc);
        return -1;
    }

    int num = atoi(argv[1]);
    int last = 1;
    factorial(num);
    for(int i = 1; i <= num; ++i) {
        last *= i;
    }

    printf("El factorial iterativo de %d es %d\n", num, last);
    return 0;
}

int factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n-1);
}

