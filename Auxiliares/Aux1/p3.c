#include <stdio.h>
#include <stdlib.h>

void factoresPrimos(int n);

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <numero>\n", argv[0]);
        return -1;
    }

    int n = atoi(argv[1]);
    if (n == 1)
        printf("1\n");
    else
        factoresPrimos(n);
}

void factoresPrimos(int n) {
    int factor = 2;
    while (factor <= n) {
        if (n%factor == 0) {
            printf("%d ", factor);
            n /= factor;
        }
        else
            factor++;
    }
    printf("\n");
}