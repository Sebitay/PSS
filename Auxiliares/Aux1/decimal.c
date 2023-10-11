#include <math.h>

int decimal(int binario) {
    int result = 0;
    int i = 0;
    while(binario) {
        if (binario%10)
            result += pow(2, i); 
        binario /= 10;
        i++;
    }
    return result;
}