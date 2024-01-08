#ifndef BASIC_TESTING_H_INCLUDED
#define BASIC_TESTING_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#define assert_int_equal(expr,value) \
    do { int e = (expr); int v = (value); \
         if (e != v) { \
	 fprintf(stderr, "%s:%d: Assertion `%s == %s' failed (%d != %d).\n", __FILE__, __LINE__, #expr, #value, e, v); \
         abort(); } } while(0)

#endif
