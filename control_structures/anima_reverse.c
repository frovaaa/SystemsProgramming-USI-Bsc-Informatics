#include <stdio.h>

int main()
{
    int c;
    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        {
            int next = getchar();
            if (next != EOF && next == 's')
            {
                next = getchar();
                if (next != EOF && next == c)
                    putchar(c);
            }
        }
        break;
        default:
            putchar(c);
        }
    }
}