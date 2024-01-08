#include <stdio.h>
#include <string.h>

int main()
{
    char s[] = "Hello";
    s[2] = 'A';
    printf("2nd character of the string is: %c\n", s[2]);
    printf("The new string is: %s", s);
}