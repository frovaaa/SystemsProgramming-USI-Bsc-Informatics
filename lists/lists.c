#include "lists.h"
#include <stdio.h>

/**
 * The two functions operate on lists of integers implemented with struct list objects (single-link
    lists). The two functions must not allocate any memory, so they must work exclusively with the
    objects passed as parameters.
*/

// struct list {
//     int value;
//     struct list * next;
// };

// Function concatenate_all(int n, struct list * L[]) takes an array of n lists (pointers to
// the first element of a linked list), and returns a single list by concatenating all the elements of the
// n lists in the given order. Some lists might be empty (null).
struct list *concatenate_all(int count, struct list *lists[])
{
    struct list *result = 0;
    struct list **last = &result;
    for (unsigned i = 0; i < count; ++i)
    {
        if (lists[i] != 0)
        {
            struct list *t = lists[i];
            *last = t;
            while (t->next)
                t = t->next;
            last = &(t->next);
        }
    }

    return result;
}

// struct list *result = 0;

// for (unsigned i = 0; i < count; ++i)
// {
//     if (lists[i] != 0)
//     {
//         if (!result)
//         {
//             result = lists[i];
//         }
//         else
//         {
//             struct list *temp = result;
//             while (temp->next)
//                 temp = temp->next;
//             temp->next = lists[i];
//         }
//     }
// }

// return result;

// Function merge_sorted(struct list * a, struct list * a) takes two lists that are sorted
// in non-decreasing order, and returns a single, sorted list that contains all the elements of both
// input lists. No values must be removed, so if there are repeated values, those must be part of the
// resulting list. Either or both input lists might be empty (null).
struct list *merge_sorted(struct list *a, struct list *b)
{
    struct list *result = 0;
    struct list **last = &result;
    if (!a && b)
        return b;
    else if (a && !b)
        return a;
    else if (!a && !b)
        return 0;
    else
    {
        if (a->value <= b->value)
        {
            *last = a;
            last = &(a->next);
            a = a->next;
        }
        else
        {
            *last = b;
            last = &(b->next);
            b = b->next;
        }
        while (a && b)
        {
            if (a->value <= b->value)
            {
                *last = a;
                last = &(a->next);
                a = a->next;
            }
            else
            {
                *last = b;
                last = &(b->next);
                b = b->next;
            }
        }
        struct list *remain;
        if (a)
            remain = a;
        else
            remain = b;
        while (remain)
        {
            *last = remain;
            last = &(remain->next);
            remain = remain->next;
        }
    }
    return result;
}