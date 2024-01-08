#include <assert.h>

#include "basic_testing.h"

#include "../lists.h"

int main() {
    struct list L1[100];
    struct list L2[100];
    struct list * l;
    int i;

    /* L1 = [0, 1, 2, 3, 4, 5]  */
    l = L1;
    for(i = 0; i < 5; ++i) {
	l->value = i;
	l->next = l + 1;
	l = l->next;
    }
    l->value = i;
    l->next = 0;

    l = merge_sorted(L1, 0);

    /* l should be: 0, 1, 2, 3, 4, 5  */
    for (int j = 0; j <= 5; ++j) {
	assert(l);
	assert_int_equal(l->value, j);
	l = l->next;
    }
    assert(!l);

    /* L2 = [0, 1, 2, 3, 4, 5, 6]  */
    l = L2;
    for(i = 0; i < 6; ++i) {
	l->value = i;
	l->next = l + 1;
	l = l->next;
    }
    l->value = i;
    l->next = 0;

    l = merge_sorted(0, L2);

    /* l should be: 0, 1, 2, 3, 4, 5, 6  */
    for (int j = 0; j <= 6; ++j) {
	assert(l);
	assert_int_equal(l->value, j);
	l = l->next;
    }
    assert(!l);

    /* L1 = [0, 1, 2, 3, 4]  */
    l = L1;
    for(i = 0; i < 4; ++i) {
	l->value = i;
	l->next = l + 1;
	l = l->next;
    }
    l->value = i;
    l->next = 0;

    /* L2 = [1, 3, 5]  */
    l = L2;
    for(i = 1; i < 5; i += 2) {
	l->value = i;
	l->next = l + 1;
	l = l->next;
    }
    l->value = i;
    l->next = 0;

    l = merge_sorted(L1, L2);
    /* l should be: 0, 1, 1, 2, 3, 3, 4, 5  */
    assert(l);
    assert_int_equal(l->value, 0);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 1);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 1);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 2);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 3);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 3);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 4);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 5);
    l = l->next;
    assert(!l);

    /* L1 = [0, 1, 2, 3, 4]  */
    l = L1;
    for(i = 0; i < 4; ++i) {
	l->value = i;
	l->next = l + 1;
	l = l->next;
    }
    l->value = i;
    l->next = 0;

    /* L2 = [1, 3, 5]  */
    l = L2;
    for(i = 1; i < 5; i += 2) {
	l->value = i;
	l->next = l + 1;
	l = l->next;
    }
    l->value = i;
    l->next = 0;

    l = merge_sorted(L2, L1);
    /* l should be: 0, 1, 1, 2, 3, 3, 4, 5  */
    assert(l);
    assert_int_equal(l->value, 0);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 1);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 1);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 2);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 3);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 3);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 4);
    l = l->next;
    assert(l);
    assert_int_equal(l->value, 5);
    l = l->next;
    assert(!l);


    return 0;
}
