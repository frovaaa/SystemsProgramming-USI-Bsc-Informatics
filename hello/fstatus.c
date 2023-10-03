#include <stdio.h>

int main () {
    int c;
    unsigned int count = 0;
    printf(" count  getchar  feof  ferror\n");
    do {
        c = getchar();
        printf("%6u  %7d  %4s  %6s\n",
               count, c,
               (feof(stdin) ? "yes" : "no"), (ferror(stdin) ? "yes" : "no"));
        ++count;
    } while (c != EOF);
}