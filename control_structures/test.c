#include <stdio.h>

void print_score(int);

int main()
{
    // int n;
    // scanf("%d", &n);
    // print_score(n);

    // int n;
    // scanf("%d", &n);
    // do
    // {
    //     if (n % 2 == 1)
    //         n = 3 * n + 1;
    //     else
    //         n = n / 2;
    //     printf("%d\n", n);
    // } while (n != 1);

    // int n;
    // scanf("%d", &n);
    // do
    // {
    //     if (n % 2 == 1)
    //         n = 3 * n + 1;
    //     n = n / 2;
    //     printf("%d\n", n);
    // } while (n != 1);

    int n;
    scanf("%d", &n);
    do
        printf("%d\n", n--);
    while (n > 0);
}

// int main () {
//     int n;
//     scanf("%d", &n);    /* read a number from standard input  */
//     if (n % 2 == 1)
//         n = 3*n + 1;
//     n = n / 2;
//     printf("%d\n", n);
// }

// void print_score(int p)
// {
//     if (p < 0)
//     {
//         printf("Something is wrong: your score is negative!\n");
//     }
//     else
//     {
//         printf("You have %d point", p);
//         if (p != 1)
//             printf("s");
//         printf("\n");
//     }
// }

void print_score(int p)
{
    if (p < 0)
    {
        printf("Something is wrong: your score is negative!\n");
        return;
    }
    printf("You have %d point", p);
    if (p != 1)
        printf("s");
    printf("\nThat is ");
    switch (p)
    {
    case 0:
    case 1:
        printf("a bit low");
        break;
    case 2:
        printf("okay");
        break;
    case 4:
        printf("very ");
    case 3:
        printf("good");
        break;
    case 5:
        printf("excellent!");
        break;
    default:
        printf("unbelievable!");
        break;
    }
    printf("\n");
}