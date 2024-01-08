#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min;
int max; // -1 means inifinity
const int hardCap = 60;

int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        min = atoi(argv[1]);
    }
    else
    {
        min = 0;
        max = -1;
    }
    if (argc > 2)
    {
        max = atoi(argv[2]);
    }
    else
    {
        max = -1;
    }

    char line[60 + 2];
    char *t = line;
    int len = 0;
    for (int c = getchar(); c != EOF; c = getchar())
    {
        if (c == '\n')
        {
            *t = 0;
            if ((max == -1 || len <= max) && len >= min)
            {
                printf((len > hardCap ? "%s...\n" : "%s\n"), line);
            }
            t = line;
            len = 0;
        }
        else if (len < hardCap)
        {
            *t++ = c;
            ++len;
        } else if (len >= hardCap) {
            ++len;
        }
    }
}
