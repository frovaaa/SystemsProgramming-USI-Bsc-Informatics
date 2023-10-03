#include <stdio.h>

void print_score(int points)
{
    if (points < 0)
    {
        printf("Something is wrong: your score is negative!\n");
    }
    else
    {
        printf("You have %d point", points);
        if (points != 1)
            printf("s");
        printf("\n");
    }
}

int is_prime(int n)
{
    for (int d = 2; d * d <= n; ++d)
        if (n % d == 0)
            return 0;
    return 1;
}

int gcd(int a, int b)
{ /* parameters: int a, int b */
    while (a != b)
    {
        if (a > b)
        {
            a -= b;
        }
        else
        {
            b -= a;
        }
    }
    return a;
}

int main(int argc, char const *argv[])
{
    print_score(20);
    printf("%d\n", is_prime(52347));

    for (int i = 1; i < 100; ++i)
        printf("%d -> %d\n", i, is_prime(i));

    int n, m;
    printf("input  two non-negative integers: ");
    scanf("%d%d", &n, &m);
    printf("the least common multiple between %d and %d is", n, m);
    printf("%d\n", n / gcd(n, m) * m); /* arguments: a <- n; b <- m; */

    for (int i = 0; i < argc; ++i)
    {
        printf("arg[%d] = \"%s\"\n", i, argv[i]);
    }

    return 0;
}
