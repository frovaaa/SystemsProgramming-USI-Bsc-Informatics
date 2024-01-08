#ifndef STRQUEUE_H_INCLUDED
#define STRQUEUE_H_INCLUDED

#include <stddef.h> 		/* declares size_t */

extern void strqueue_use_buffer(char * mem, size_t mem_size);
extern void strqueue_clear();
extern int strqueue_enqueue(const char * s);
extern const char * strqueue_dequeue();

#endif
