#include "tformat.h"
#include <ctype.h>

//
void do_normalization(char *t)
{
    char *s = t;
    int addSpace = 0;
    int emptyLine = 1;
    while (*s)
    {
        if (*s == '\n')
        {
            *t++ = '\n';
            addSpace = 0;
            emptyLine = 1;
            ++s;
        }
        else if (isspace(*s))
        {
            if (!emptyLine)
                addSpace = 1;
            ++s;
        }
        else
        {
            if (addSpace)
                *t++ = ' ';
            *t++ = *s++;
            emptyLine = 0;
            addSpace = 0;
        }
    }
    *t = 0;
}

void do_format_paragraphs(char *t)
{
    int prevNL = 0;
    for (char *s = t; *s != 0; ++s)
    {
        if (*s == '\n')
            prevNL = 1;
        else
        {
            if (prevNL)
            {
                prevNL = 0;
                *t++ = '\n';
            }
            *t++ = *s;
        }
    }
    if(prevNL){
        *t++ = '\n';
    }
    *t = 0;
}

void do_format_punctuation(char *t)
{
    int prevSpace = 0;
    for (char *s = t; *s != 0; ++s)
    {
        if (*s == '\n')
            *t++ = *s;
        else if (ispunct(*s))
            *t++ = *s;
        else if (isspace(*s))
            prevSpace = 1;
        else
        {
            if (prevSpace)
            {
                prevSpace = 0;
                *t++ = ' ';
            }
            *t++ = *s;
        }
    }
    *t = 0;
}

void t_format(char *t, const struct t_opts *opt)
{
    do_normalization(t);

    if (opt->format_paragraphs)
    {
        do_format_paragraphs(t);
    }
    if (opt->format_punctuation)
    {
        do_format_punctuation(t);
    }
}
