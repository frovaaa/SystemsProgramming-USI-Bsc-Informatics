#include "basic_testing.h"
#include "../iterator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

TEST (long_strings) {
    struct iterator * itr = create_iterator();
    CHECK(itr != 0);

    char *s = malloc(10000);
    CHECK(s != 0);

    struct sequence seq;
    seq.begin = s;
    seq.end = s + 10000;

    memset(s, 'a', 10000);

    CHECK_CMP(set_text(itr, &seq),==,1);
    free(s);
    CHECK_CMP(get_next(itr, &seq),==,1);

    for (const char *p = seq.begin; p != seq.begin + 10000; ++p)
        CHECK(*p == 'a');

    destroy_iterator(itr);
    TEST_PASSED;
}


TEST (many_long_strings) {
    struct iterator * itr[200];
    struct sequence itr_seq[200];

    char buf[5];
    struct sequence sep;
    memcpy(buf, ".", 1);
    sep.begin = buf;
    sep.end = sep.begin + 1;

    char *s = malloc(10000);
    CHECK(s != 0);

    struct sequence seq;
    seq.begin = s;
    seq.end = s + 10000;

    for (char c = '0'; c <= 'z'; ++c) {
        int i = c - '0';
        itr[i] = create_iterator();
        CHECK(itr[i] != 0);

        memset(s, c, 10000);

        CHECK_CMP(set_separators(itr[i], &sep),==,1);
        CHECK_CMP(set_text(itr[i], &seq),==,1);
        CHECK_CMP(get_next(itr[i], &itr_seq[i]),==,1);
    }

    free(s);

    for (char c = '0'; c <= 'z'; ++c) {
        for (const char *p = itr_seq[c - '0'].begin; p != itr_seq[c - '0'].begin + 10000; ++p)
            CHECK(*p == c);
        destroy_iterator(itr[c - '0']);
    }

    TEST_PASSED;
}


MAIN_TEST_DRIVER(long_strings, many_long_strings);
