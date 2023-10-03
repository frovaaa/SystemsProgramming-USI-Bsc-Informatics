#include <stdio.h>
#include <ctype.h>

int delete_digits(char *s)
{
    int foundDigits = 0;
    while (*s != 0)
    {
        if (isdigit(*s))
        {
            char *tempS = s;
            while (*tempS != 0)
            {
                *tempS = *(tempS + 1);
                tempS++;
            }
            foundDigits++;
        }
        else
        {
            s++;
        }
    }

    return (foundDigits != 0 ? 1 : 0);
}
