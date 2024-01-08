#include "basic_testing.h"

#include "../iterator.h"

TEST (no_iteration) {
    struct iterator * itr = create_iterator();
    CHECK(itr != 0);
    struct sequence seq;
    CHECK_CMP(get_next(itr, &seq),==,0);
    destroy_iterator(itr);
    TEST_PASSED;
}

TEST (no_iteration_with_separators) {
    struct iterator * itr = create_iterator();
    CHECK(itr != 0);
    struct sequence seq;

    CHECK_CMP(get_next(itr, &seq),==,0);

    char xyz[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    seq.begin = xyz;
    seq.end = xyz + 20;
    CHECK_CMP(set_separators(itr, &seq),==,1);

    CHECK_CMP(get_next(itr, &seq),==,0);

    destroy_iterator(itr);
    TEST_PASSED;
}

TEST (no_iteration_with_text) {
    struct iterator * itr = create_iterator();
    CHECK(itr != 0);
    struct sequence seq;

    CHECK_CMP(get_next(itr, &seq),==,0);

    char xyz[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    seq.begin = xyz;
    seq.end = xyz + 20;
    CHECK_CMP(set_separators(itr, &seq),==,1);

    char txt[20] = {1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10};
    seq.begin = txt;
    seq.end = txt + 20;
    CHECK_CMP(set_text(itr, &seq),==,1);

    CHECK_CMP(get_next(itr, &seq),==,0);

    destroy_iterator(itr);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(no_iteration, no_iteration_with_separators, no_iteration_with_text);
