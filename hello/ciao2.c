#include <stdio.h>

int main () {
    for (int n = 0; n < 15; ++n)
        printf("%6dPI = %6.3f\n", n, 3.14159265*n);
}