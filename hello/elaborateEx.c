#include <stdio.h>
#include <ctype.h>

int main () {
    int c;
    unsigned int x = 0;
    int reading_number = 0;
    do {
        c = getchar();
        if (isdigit(c)) {
            reading_number = 1;
            x = 10*x + (c - '0');
        } else {
            if (reading_number == 1) {
                for (; x > 0; --x) {
                    putchar('#');
                }
                putchar('\n');
                reading_number = 0;
            }
        }
    } while (c != EOF);
}

// Custom error message perror("message")

/*
Errors handled version
#include <stdio.h>
#include <ctype.h>

int main () {
    int c;
    int x = 0;
    int reading_number = 0;
    do {
        c = getchar();
        if (isdigit(c)) {
            reading_number = 1;
            x = 10*x + (c - '0');
        } else {
            if (reading_number == 1) {
                for (; x > 0; --x) {
                    if (putchar('#') == EOF) {
                        perror("putchar() failed");
                        return 1;
                    }
                }
                if (putchar('\n') == EOF)  {
                    perror("putchar() failed");
                    return 1;
                }
                reading_number = 0;
            }
        }
    } while (c != EOF);
    return 0;
}
*/