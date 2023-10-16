/**
 * In a source file called sortstrings.c write a function
 * void sort_strings(const char * input, char * output, unsigned int n)
 * that takes a sequence of n≤1000 contiguous C strings from a given input memory buffer,
 * and copies in a given output buffer the same strings, also as a sequence of contiguous C strings,
 * but sorted in non-decreasing lexicographical order. The order is defined by the numerical order of the character codes.
 * Do not worry too much about the complexity of your sorting algorithm.
 * You may not use any external library function, not even from the C standard library.
 */

int my_strcmp(const char *a, const char *b)
{
    while (*a == *b && *a != 0)
    {
        a++;
        b++;
    }
    return (*a > *b);
}

void sort_strings(const char *input, char *output, unsigned int n)
{
    const char *buffer[1000];
    // Copy the beginning of each string in the buffer
    for (int i = 0; i < n; i++)
    {
        buffer[i] = input;
        while (*input != 0)
        {
            input++;
        }
        input++;
    }

    // Sort
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            const char *tmp;
            if (my_strcmp(buffer[i], buffer[j]))
            {
                tmp = buffer[i];
                buffer[i] = buffer[j];
                buffer[j] = tmp;
            }
        }
    }

    // Copy in the output array
    for (int i = 0; i < n; i++)
    {
        while (*buffer[i] != 0)
        {
            *output = *buffer[i];
            output++;
            buffer[i]++;
        }
        *output = 0;
        output++;
    }
}