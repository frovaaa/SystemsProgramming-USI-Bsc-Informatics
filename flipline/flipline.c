#include <stdio.h>

int main(int argc, char const *argv[])
{
    char buffer[1000];
    int currentChar = getchar();
    int i = 0;
    int isEOF = 0;

    if (currentChar == EOF)
        isEOF = 1;

    while (isEOF == 0)
    {

        // Get entire line
        while (currentChar != '\n')
        {
            if (currentChar == EOF)
            {
                isEOF = 1;
                break;
            }
            // add to buffer
            buffer[i++] = currentChar;
            currentChar = getchar();
        }

        for (--i; i >= 0; i--)
        {
            putchar(buffer[i]);
        }
        i = 0;

        if (currentChar == '\n')
        {
            putchar('\n');
            // Skip the \n
            currentChar = getchar();
            if (currentChar == EOF)
                isEOF = 1;
        }
    }

    return 0;
}
