#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "../strqueue.h"

const char * S[] = {
    "ciao mamma",
    "blah!",
    "it ain't over till it's over",
    "",
    "ciao",
    "--",
    "#include <stdio.h>",
    "Hello world!"
};

const char * str10 = "1234567989";
const char * str11 = "12345679890";

int main() {
    int i;

    char * queue_memory = malloc(100);
    assert(queue_memory);

    assert(!strqueue_enqueue(""));
    assert(!strqueue_dequeue());

    strqueue_use_buffer(queue_memory, 100);
    assert(strqueue_enqueue(""));
    assert(strqueue_dequeue());

    strqueue_clear();

    for (i = 0; i < 1000; ++i) {
	const char * s;
	assert(strqueue_enqueue(""));
	s = strqueue_dequeue();
	assert(s);
	assert(*s == 0);
    }

    strqueue_clear();
    assert(!strqueue_dequeue());

    for (i = 0; i < 9; ++i)
	assert(strqueue_enqueue(str10));

    assert(!strqueue_enqueue(str11));
    assert(strqueue_dequeue());
    assert(!strqueue_enqueue(str11));
    assert(strqueue_dequeue());
    assert(strqueue_enqueue(str11));

    for (i = 0; i < 7; ++i) {
	const char * s = strqueue_dequeue();
	assert(s);
	assert(strcmp(s,str10)==0);
    }
    {
	const char * s = strqueue_dequeue();
	assert(s);
	assert(strcmp(s,str11)==0);
    }
    assert(!strqueue_dequeue());

    for (i = 0; i < 200; ++i) {
	int j;
	for (j = 0; j < 8; ++j)
	    assert(strqueue_enqueue(S[j]));

	for (j = 0; j < 8; ++j) {
	    const char * s = strqueue_dequeue();
	    assert(s);
	    assert(strcmp(s, S[j])==0);
	}
    }
    printf("TEST PASSED.\n");

    free(queue_memory);
    return 0;
}
