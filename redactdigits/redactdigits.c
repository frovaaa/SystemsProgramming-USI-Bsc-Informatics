#include <stdio.h>
#include <ctype.h>

int redact_digits(char *s)
{
    int foundDigits = 0;
    while (*s != 0)
    {
        if (isdigit(*s))
        {
            *s = '#';
            foundDigits++;
        }
        s++;
    }

    return (foundDigits != 0 ? 1 : 0);
}
