#include "iterator.h"
#include <stdlib.h>
#include <string.h>

struct iterator
{
    struct sequence *s;
    struct sequence *t;
    char text[10001];
    char sep[10001];
};

struct iterator *create_iterator()
{
    struct iterator *this = malloc(sizeof(struct iterator));
    if (this)
    {
        struct sequence *new_t = malloc(sizeof(struct sequence));
        if (!new_t)
            return 0;

        new_t->begin = 0;
        new_t->end = 0;
        this->t = new_t;

        struct sequence *new_s = malloc(sizeof(struct sequence));
        if (!new_s)
            return 0;
        this->text[0] = '.';
        this->text[1] = ';';
        this->text[2] = 0;
        new_s->begin = this->text;
        new_s->end = &this->text[2];

        this->s = new_s;
    }
    return this;
}
void destroy_iterator(struct iterator *i)
{
    free(i->s);
    free(i->t);
    free(i);
}

int set_text(struct iterator *i, const struct sequence *t)
{
    struct sequence *temp = malloc(sizeof(struct sequence));
    if (!temp)
        return 0;
    temp->begin = t->begin;
    temp->end = t->end;
    for (char *start = i->text; temp->begin != temp->end; ++(temp->begin))
        *start = *temp->begin;

    i->t->begin = i->text;
    i->t->end = &i->text[10001];
    free(temp);
    return 1;
}

int set_separators(struct iterator *i, const struct sequence *s)
{
    struct sequence *temp = malloc(sizeof(struct sequence));
    if (!temp)
        return 0;
    temp->begin = s->begin;
    temp->end = s->end;
    for (char *start = i->sep; temp->begin != temp->end; ++(temp->begin))
        *start = *temp->begin;

    i->s->begin = i->sep;
    i->s->end = &i->sep[10001];
    free(temp);
    return 1;
}

int get_next(struct iterator *i, struct sequence *x)
{
    char *start = i->t->begin;
    while (*i->t->begin != 0)
    {
        // check if is in separator
        for (char *sep = i->s->begin; sep != i->s->end; sep += 1)
        {
            //check if they are equal
        }

        i->t->begin += 1;
    }

    x->begin = start;
    x->end = i->t->begin;
}