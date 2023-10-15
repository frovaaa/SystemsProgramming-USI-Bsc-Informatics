
int twotimes(const char *s)
{
    // Returns 1 if the string is the concatenation of 2 identical strings
    // 0 otherwise
    int len = 0;

    // Check for odd length
    int arnoldCounter = 0;
    int middleArnold = 0;
    while (1)
    {
        if (*s == 0 && *(s + 1) != 0)
        {
            ++arnoldCounter;
            middleArnold = len;
        }
        else if (*s == 0)
        {
            break;
        }
        ++s;
        ++len;
    }

    if (arnoldCounter == 1)
    {
        // Two arnolds in the string (concatenated strings)
        // remove middle arnold
        --len;
        if (len == 0)
            return 1;
        if (len % 2 != 0)
            return 0;

        int posHalf = middleArnold + 1;
        for (int i = 0; i < posHalf; i++)
        {
            if (*(s + i) != *(s + posHalf + i))
                return 0;
        }
        return 1;
    }
    else
    {
        // One arnold (one single string)
        if (len == 0)
            return 1;
        if (len % 2 != 0)
            return 0;

        int posHalf = len / 2;
        for (int i = 0; i < posHalf; i++)
        {
            if (*(s + i) != *(s + posHalf + i))
                return 0;
        }
        return 1;
    }
}

int twotimes2(const char *begin, const char *end)
{
    // Returns 1 if the string is the concatenation of 2 identical strings
    // 0 otherwise

    const char *s = begin;

    int len = 0;

    // Check for odd length
    int arnoldCounter = 0;
    int middleArnold = 0;
    while (s != end)
    {
        if (*s == 0 && s != end)
        {
            ++arnoldCounter;
            middleArnold = len;
        }
        ++s;
        ++len;
    }

    if (arnoldCounter == 1)
    {
        // Two arnolds in the string (concatenated strings)
        // remove middle arnold
        --len;
        if (len == 0)
            return 1;
        if (len % 2 != 0)
            return 0;

        int posHalf = middleArnold + 1;
        for (int i = 0; i < posHalf; i++)
        {
            if (*(s + i) != *(s + posHalf + i))
                return 0;
        }
        return 1;
    }
    else
    {
        // One arnold (one single string)
        if (len == 0)
            return 1;
        if (len % 2 != 0)
            return 0;

        int posHalf = len / 2;
        for (int i = 0; i < posHalf; i++)
        {
            if (*(s + i) != *(s + posHalf + i))
                return 0;
        }
        return 1;
    }
}

// #include <stdio.h>
// int main(int argc, char const *argv[])
// {
//     // const char * s = "ab";

//     // int res = !twotimes("ab");
//     // int res2 = !twotimes2(s,s+2);
//     // printf("res: %d\n", res);
//     // printf("res2: %d\n", res2);

//     const char * z1 = "aa\0ab\0";
//     int res = twotimes(z1);
//     printf("res: %d\n", res);


//     return 0;
// }