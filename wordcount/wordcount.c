#include <stdio.h>

int main()
{
    int wordCount = 0;
    int currentChar = getchar();
    int state = -2; // 0: space   -   1: word   -   -2: initial state
    int space = 32;
    int newLine = 10;
    int tab = 9;


    state = (currentChar == space || currentChar == newLine || currentChar == EOF || currentChar == tab) ? 0 : 1;

    while (currentChar != EOF)
    {
        if(state == 1){
            // The previous byte was a char of a word
            if (currentChar == space || currentChar == newLine || currentChar == tab){
                // I ended a word or new line, so previous word is complete
                wordCount++;
                state = 0; // Enter space or new line state
            }
        } else if (state == 0){
            //Last byte was space or new line
            if (currentChar != space && currentChar != newLine && currentChar != tab){
                //I am starting a new word, so change state
                state = 1;
            }
        }
        
        currentChar = getchar();
    }

    // Finished in word without space or new line
    if (state == 1){
        wordCount++;
    } else if (state == -2){
        wordCount = 0;
    }

    printf("%d\n", wordCount);
}