int concatenate(char *s, unsigned max_size, const char *s2)
{

    // Go to end of buffer string
    int i = 0;
    while (s[i] != 0)
    {
        ++i;
    }

    int j = 0;
    // Concatenate string until reach end of s2 or max_size
    while (i < max_size && s2[j] != 0)
    {
        s[i++] = s2[j++];
    }

    // Need to go 1 back and set to 0
    if ((i == max_size) && (j != 0))
    {
        s[--i] = 0;
        return 0;
    }
    else
    {
        // No need to go 1 back
        s[i] = 0;
    }
    return 1;
}