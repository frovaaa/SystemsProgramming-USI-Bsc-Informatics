#ifndef LISTS_H_INCLUDED
#define LISTS_H_INCLUDED

struct list {
    int value;
    struct list * next;
};

extern struct list * concatenate_all(int count, struct list * lists[]); 

extern struct list * merge_sorted(struct list * a, struct list * b); 

#endif

