#include <stdio.h>

int main () {
    int c;
    while ((c = getchar()) != EOF) {
        switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            putchar(c);
            putchar('s');
        default:
            putchar(c);
        }
    }
}