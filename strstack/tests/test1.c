#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "basic_testing.h"
#include "../strstack.h"

const char * S[] = {
    "ciao mamma",
    "blah!",
    "it ain't over till it's over",
    "",
    "ciao",
    "",
    "#include <stdio.h>",
    "Hello world!"
};

TEST (misc) {
    int i;

    char * stack_memory = malloc(10000);
    CHECK(stack_memory);

    CHECK(!strstack_push(""));
    CHECK(!strstack_pop());

    strstack_use_buffer(stack_memory, 10000);
    CHECK(strstack_push(""));
    CHECK(strstack_pop());

    strstack_clear();

    for (i = 0; i < 8; ++i)
	CHECK(strstack_push(S[i]));

    while (i > 0) {
	const char * s = strstack_pop();
	CHECK(s);
	CHECK(strcmp(s, S[--i]) == 0);
    }

    CHECK(!strstack_pop());

    for (i = 0; i < 8; ++i)
	CHECK(strstack_push(S[i]));

    strstack_pop();
    strstack_pop();

    for (i = 0; i < 8; ++i)
	CHECK(strstack_push(S[i]));

    while (i > 0) {
	const char * s = strstack_pop();
	CHECK(s);
	CHECK(strcmp(s, S[--i]) == 0);
    }

    i = 6;

    while (i > 0) {
	const char * s = strstack_pop();
	CHECK(s);
	CHECK(strcmp(s, S[--i]) == 0);
    }

    CHECK(!strstack_pop());

#if STRSTACK_USES_EXTERNAL_MEMORY
    free(stack_memory);
#endif

    TEST_PASSED;
}

MAIN_TEST_DRIVER (misc);
