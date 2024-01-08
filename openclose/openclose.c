// read o/c pairs | Y

// repeat until EOF
// Read lines from stidn
// stack the line
// clean the line
// look for o/c
// print the line
// endrepeat

#include <stdio.h>
#include <string.h>

const char *oc = "()[]{}";
char stack[1001];

int findClosing(const char s)
{
    unsigned i = 0;
    for (; oc[i] != 0; i += 2)
    {
        if (oc[i] == s)
        {
            return oc[i + 1];
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        oc = argv[1];
    }

    char *t = stack;
    for (int c = getchar(); c != EOF; c = getchar())
    {

        if (c == '\n')
        {
            *t = 0;
            printf("%s\n", stack);
            t = stack;
        }
        else if (t == stack)
        {
            *t++ = c;
        }
        else if (findClosing(*(t - 1)) == c)
        {
            --t;
        }
        else
        {
            *t++ = c;
        }
    }
}
