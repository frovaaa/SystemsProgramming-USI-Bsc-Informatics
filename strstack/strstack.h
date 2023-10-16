#ifndef STRSTACK_H_INCLUDED
#define STRSTACK_H_INCLUDED

#include <stddef.h> 		/* declares size_t */

extern void strstack_use_buffer(char * mem, size_t mem_size);
extern void strstack_clear();
extern int strstack_push(const char * s);
extern const char * strstack_pop();

#endif
