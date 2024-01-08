#include "basic_testing.h"
#include "../iterator.h"

TEST (iterator_create_destroy) {
    struct iterator * itr = create_iterator();
    CHECK (itr != 0);
    destroy_iterator(itr);
    TEST_PASSED;
}

TEST (iterator_create_destroy_two) {
    struct iterator * itr1 = create_iterator();
    CHECK (itr1 != 0);
    struct iterator * itr2 = create_iterator();
    CHECK (itr2 != 0);
    destroy_iterator(itr1);
    destroy_iterator(itr2);
    TEST_PASSED;
}

TEST (iterator_create_destroy_1000) {
    struct iterator * itr[1000];
    for (unsigned int i = 0; i < 1000; ++i) {
	itr[i] = create_iterator();
	CHECK (itr[i] != 0);
    }
    for (unsigned int i = 0; i < 1000; ++i)
	destroy_iterator(itr[i]);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(iterator_create_destroy,
		 iterator_create_destroy_two,
		 iterator_create_destroy_1000);
