/*
    shellcomments:
    Write a C program called shellcomments that reads a shell script from the standard input, and prints on the standard output the comments in the input script.
    Recall that a comment is the text following the pound character ('#') up to the end of line, including the new-line character ('\n').
    The output should be the same as the command: sed -n -e 's/^[^#]*#//p'
*/

#include <stdio.h>

int main()
{
    int current_char = getchar();
    int state; // 0 = not in comment, 1 = in comment

    while (current_char != EOF)
    {
        if (state == 0)
        {
            if (current_char == '#')
                state = 1;
        }
        else if (state == 1)
        {
            printf("%c", current_char);

            if (current_char == '\n')
                state = 0;
        }
        current_char = getchar();
    }
}