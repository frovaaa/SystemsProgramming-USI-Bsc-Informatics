#include <assert.h>

#include "basic_testing.h"
#include "../lists.h"

int main() {
    struct list * LV[10];
    struct list L[100];
    struct list * l;

    for(int i = 0; i < 100; ++i)
	L[i].value = i;
	
    for(int i = 0; i < 10; ++i) {
	struct list * l = L + i*10;
	LV[i] = l;
	for (int j = 0; j < 5; ++j) {
	    l->next = l + 1;
	    l = l->next;
	}
	l->next = 0;
    }

    l = concatenate_all(10, LV);

    for(int i = 0; i < 10; ++i) 
	for (int j = 0; j <= 5; ++j) {
	    assert(l);
	    assert_int_equal(l->value, i*10 + j);
	    l = l->next;
	}

    for(int i = 0; i < 10; ++i) {
	if (i % 2 == 0) {
	    LV[i] = 0;
	} else {
	    struct list * l = L + i*10;
	    LV[i] = l;
	    for (int j = 0; j < 5; ++j) {
		l->next = l + 1;
		l = l->next;
	    }
	    l->next = 0;
	}
    }

    l = concatenate_all(10, LV);
    for(int i = 1; i < 10; i += 2) 
	for (int j = 0; j <= 5; ++j) {
	    assert(l);
	    assert_int_equal(l->value, i*10 + j);
	    l = l->next;
	}

    for(int i = 0; i < 10; ++i) {
	if (i == 7) {
	    struct list * l = L + i*10;
	    LV[i] = l;
	    for (int j = 0; j < 5; ++j) {
		l->next = l + 1;
		l = l->next;
	    }
	    l->next = 0;
	} else {
	    LV[i] = 0;
	}
    }

    l = concatenate_all(10, LV);
    for (int j = 0; j <= 5; ++j) {
	assert(l);
	assert_int_equal(l->value, 70 + j);
	l = l->next;
    }

    return 0;
}
