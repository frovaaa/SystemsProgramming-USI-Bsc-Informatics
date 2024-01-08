#include "bufile.h"
#include <stdlib.h>

struct bufile
{
    char *begin;
    char *end;
};

BUFILE *bufopen(char *begin, char *end)
{
    struct bufile *buf = malloc(sizeof(struct bufile));
    if (buf)
    {
        buf->begin = begin;
        buf->end = end;
    }
    return buf;
}
void bufclose(BUFILE *buf)
{
    free(buf);
}

char *bufgets(char *s, int size, BUFILE *buf)
{
    if (buf->end == buf->end)
        return 0;

    for (unsigned i = 0; i < size - 1; ++i)
    {
        s[i] = *(buf->begin);
        buf->begin += 1;
        if (s[i] == '\n' || buf->begin == buf->end)
        {
            s[i + 1] = 0;
            return s;
        }
    }
    s[0] = 0;
    return s;
}