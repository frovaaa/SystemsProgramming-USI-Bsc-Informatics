#include <stdio.h>
#include <string.h>
#include <math.h>

void swap(int *p, int *q)
{
    int tmp = *p;
    *p = *q;
    *q = tmp;
}

void polyLen()
{
    int xa, ya;
    int xb, yb;
    int first = 1;
    double len = 0;
    while (scanf(" ( %d, %d)", &xb, &yb) == 2)
    {
        if (first)
        {
            first = 0;
        }
        else
        {
            len += sqrt((xb - xa) * (xb - xa) + (yb - ya) * (yb - ya));
        }
        xa = xb;
        ya = yb;
    }
    printf("polygon length = %lf\n", len);
}

void byteToInt()
{
    int a;
    unsigned char a_rep[sizeof(a)];
    printf ("input the %zu byte values that make up the representation of an integer: ", sizeof(a));
    for (int i = 0; i < sizeof(a); ++i)
        scanf ("%hhu ", &(a_rep[i]));
    memcpy(&a, a_rep, sizeof(a)); /* copy the bytes in a_rep into object a */
    printf ("the int value of");
    for (int i = 0; i < sizeof(a); ++i)
        printf (" %hhu", a_rep[i]);
    printf (" is: %d\n", a);
}

int main(int argc, char const *argv[])
{
    // printf("sizeof(int) = %2zu\n", sizeof(int));
    // return 0;

    // int i = 7;
    // int j = 5;
    // swap(&i, &j);
    // printf("i = %d\nj = %d\n", i, j);
    // return 0;

    // polyLen();
    // return 0;

    byteToInt();
    printf("\n");
    return 0;

    int i = 0;
    printf("The size of i is %zu bytes\n"
           "The size of an int is %zu bytes -- no surprise\n",
           sizeof(i), sizeof(int));
    printf("\n");

    int A[10];
    char *s = "Use the Force, Luke!";
    char S[] = "ABC";
    printf("sizeof(A) = %2zu bytes\t(int A[10])\n", sizeof(A));
    printf("sizeof(s) = %2zu bytes\t(char * s = \"%s\")\n", sizeof(s), s);
    printf("strlen(s) = %2zu bytes\t(char * s = \"%s\")\n", strlen(s), s);
    printf("strlen(S) = %2zu bytes\t(char S[] = \"%s\")\n", strlen(S), S);
    printf("sizeof(S) = %2zu bytes\t(char S[] = \"%s\")\n", sizeof(S), S);

    printf("\n");

    int a;
    unsigned char a_rep[sizeof(a)];
    printf("input an integer: ");
    scanf("%d", &a);
    memcpy(a_rep, &a, sizeof(a)); /* copy the representation of a into a_rep */
    printf("the representation of %d (int) is:", a);
    for (int i = 0; i < sizeof(a); ++i)
        printf(" %hhu", a_rep[i]);
    printf("\n");
}
