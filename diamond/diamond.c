/*
diamond: Write a C program called diamond that takes a non-negative number n as a command-line argument,
and prints on the standard output an n-by-n diamond made of '#' characters.
For example, this should be the output for a 6-by-6 diamond:
     #
    ###
   #####
  #######
 #########
###########
 #########
  #######
   #####
    ###
     #
*/

#include <stdio.h>
#include <stdlib.h>

int main(int arg_c, char *args[])
{
    int n, height;
    // Get the number passed via shell (Saw from the solution file)
    if (arg_c > 1)
        n = atoi(args[1]);

    height = n * 2 - 1;

    int n_hash = -1;
    int n_space = n;
    for (int y = 0; y < height; y++)
    {
        if (y < n)
        {
            n_hash += 2;
            n_space -= 1;
        }
        else
        {
            n_hash -= 2;
            n_space += 1;
        }

        // Spaces
        for (int x = 0; x < n_space; x++)
            printf(" ");

        // #
        for (int x = 0; x < n_hash; x++)
            printf("#");

        printf("\n");
    }
}
