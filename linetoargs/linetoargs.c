#include <ctype.h>

int line_to_args(char *argv[], int max_count, char *line)
{
    int argv_i = 0;
    int line_i = 0;
    int writing_arg = 0;

    // scan line
    while (line[line_i] != 0 && argv_i < max_count)
    {
        if (isspace(line[line_i]))
        {
            // I was saving an argv
            if (writing_arg == 1)
            {
                writing_arg = 0;

                line[line_i] = 0;
                argv[argv_i] = &line[line_i];

                ++argv_i;
            }
        }
        else
        {
            writing_arg = 1;
        }

        ++line_i;
    }

    // End without space
    if (writing_arg)
    {
        ++argv_i;
        line[line_i] = 0;
    }

    // Number of arguments <= max_count
    return argv_i;
}