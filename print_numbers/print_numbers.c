/**
 * The function print_numbers must print on the standard output all the numbers in the input string, each on an individual line.
 * A number is a contiguous sequence of digits (characters ’0’,. . . , ’9’)
 * possibly preceded by a sign (characters ’-’ or ’+’). The function returns the total count of numbers printed.
 */

#include <stdio.h>
#include <assert.h>

int isDigit(const char val)
{
    if (val >= 48 && val <= 57)
        return 1;
    else
        return 0;
}

int print_numbers(const char *input)
{
    int numbering = 0;
    int result = 0;

    while (*input != 0)
    {
        if (isDigit(*input))
        {
            numbering = 1;
            printf("%c", *input);
        }
        else if (*input == '-' || *input == '+')
        {
            const char *nextChar = input + 1;
            if (*nextChar != 0 && isDigit(*nextChar))
            {
                numbering = 1;
                if (*input == '-')
                    printf("-%c", *nextChar);
                if (*input == '+')
                    printf("+%c", *nextChar);
                ++input;
            }
            else
            {
                if (numbering)
                {
                    ++result;
                    printf("\n");
                    numbering = 0;
                }
            }
        }
        else
        {
            if (numbering)
            {
                ++result;
                printf("\n");
                numbering = 0;
            }
        }
        ++input;
    }
    if (numbering)
    {
        printf("\n");
        ++result;
    }

    return result;
}

int main()
{
    assert(print_numbers("abc123xyz-7//443.2") == 4);
}
