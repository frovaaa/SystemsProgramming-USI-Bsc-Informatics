#include <stdio.h>

/*
 * Exercise
 * Write a function print_sequence(int n) that, given a non-negative number n, outputs
 * on a single line with all adjacent numbers separated by a single space.
 * In fact, write three variants of print_sequence(int n) with a while, do-while, and for loop, respectively.
 */

void print_sequence_while(int n)
{
    int i = 1;
    while (i <= n)
        printf("%d ", i++);

    printf("\n");

    while (n > 0)
        printf("%d ", n--);
}

void print_sequence_do_while(int n)
{
    int i = 1;
    do
        printf("%d ", i++);
    while (i <= n);

    printf("\n");

    do
        printf("%d ", n--);
    while (n > 0);
}

void print_sequence_for(int n)
{
    for (int i = 1; i <= n; i++)
        printf("%d ", i);

    printf("\n");

    for (; n > 0; n--)
        printf("%d ", n);
}

void print_primes_less_than_100()
{
    int C[100];
    for (int i = 0; i < 100; ++i)
        C[i] = 0;
    for (int i = 2; i < 100; ++i)
    {
        if (C[i])
            continue;
        for (int j = i * i; j < 100; j += i)
            C[j] = 1;
        printf("%d ", i);
    }
    printf("\n");
}

void nested_breaks()
{
    /*
     * This function takes numbers as input, every time you enter a new number
     * it will print it back, if the number has already been inserted, it will not be printed back
    */
    int A[100];
    int n = 0;
    while (n < 100 && scanf("%d", &(A[n])) > 0)
    {
        int found = 0;
        for (int i = 0; i < n; ++i)
            if (A[i] == A[n])
            {
                found = 1;
                break;
            }
        if (found)
            continue;
        printf("%d\n", A[n]);
        ++n;
    }
}

int main()
{
    // int n;
    // scanf("%d", &n);
    // printf("\n");
    // print_sequence_while(n);
    // printf("\n");
    // print_sequence_do_while(n);
    // printf("\n");
    // print_sequence_for(n);
    // printf("\n");
    // print_primes_less_than_100();
    nested_breaks();
    return 0;
}