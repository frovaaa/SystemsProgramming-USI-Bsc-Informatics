#include <stddef.h>
#include "strstack.h"

char *M = 0;
char *M_top = 0;
size_t M_size = 0;

void strstack_use_buffer(char *mem, size_t mem_size)
{
    M = mem;
    M_size = mem_size;
    M_top = mem;
}

void strstack_clear()
{
    M_top = M;
}

int strstack_push(const char *s)
{
    if (M == 0)
        return 0;
    if (M_top - M <= M_size)
    {
        while (*s != 0)
        {
            *M_top = *s;
            ++s;
            ++M_top;
        }
        *M_top = 0;
        ++M_top;
        return 1;
    }
    else
        return 0;
}

const char *strstack_pop()
{
    if (M == 0 || M_top == M)
        return 0;

    do
    {
        --M_top;
    } while (*(M_top - 1) != 0 && M_top != M);

    return M_top;
}