#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "decimal.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <binario>\n", argv[0]);
        return -1;
    }
    int num = atoi(argv[1]);
    printf("%d\n", decimal(num));
}

