#include <string.h>
#include "strqueue.h"
// #include <stddef.h>
// #include <stdlib.h>

int max_size = 0;
char *q;
char *h;
char *t;

// append to the head (head points to first cell after 0)
// tail points to the first char of the last inserted string

void strqueue_use_buffer(char *mem, size_t mem_size)
{
    q = mem;
    t = q;
    h = q;
    max_size = mem_size;
}

void strqueue_clear()
{
    t = q;
    h = q;
}

int strqueue_enqueue(const char *s)
{
    int len = strlen(s) + 1;

    if (h >= t)
    {
        if (len <= (max_size - (h - q) + (t - q)))
        {
            for (; *s != 0; ++s, ++h)
            {
                if ((h - q) > max_size)
                {
                    h = q;
                }
                *h = *s;
            }
            *h++ = 0;
            return 1;
        }
    }
    else if (len <= (max_size - (t - q) - (h - q)))
    {
        for (; *s != 0; ++s, ++h)
        {
            if ((h - q) > max_size)
            {
                h = q;
            }
            *h = *s;
        }
        *h++ = 0;
        return 1;
    }
    return 0;
}

const char *strqueue_dequeue()
{
    return 0;
    // if (h == t)
    //     return 0;
    // char 
}

// int main(int argc, char const *argv[])
// {
//     char *queue_memory = malloc(10);
//     strqueue_use_buffer(queue_memory, 10);
//     strqueue_enqueue("MA");
//     strqueue_enqueue("CIAO");
//     char *deq = strqueue_dequeue();

//     return 0;
// }
