#include <string.h>
#include "basic_testing.h"

#include "../iterator.h"

TEST (one_no_separator) {
    struct iterator * itr = create_iterator();
    CHECK(itr != 0);
    struct sequence seq;
    seq.begin = "123abc---   +++";
    seq.end = seq.begin + 15;
    CHECK_CMP(set_text(itr, &seq),==,1);
    seq.begin = 0;
    seq.end = 0;
    CHECK_CMP(get_next(itr, &seq),==,1);
    CHECK_CMP (memcmp("123abc---   +++", seq.begin, seq.end - seq.begin),==,0);
    CHECK_CMP(get_next(itr, &seq),==,0);
    destroy_iterator(itr);
    TEST_PASSED;
}

TEST (one_cleared_buffer) {
    struct iterator * itr = create_iterator();
    CHECK(itr != 0);
    struct sequence seq;
    char buf[100];
    memset(buf, 255, sizeof(buf));
    memcpy(buf, "123abc---   +++", 15);
    seq.begin = buf;
    seq.end = buf + 15;
    CHECK_CMP(set_text(itr, &seq),==,1);
    seq.begin = 0;
    seq.end = 0;
    memset(buf, 111, sizeof(buf));
    CHECK_CMP(get_next(itr, &seq),==,1);
    CHECK_CMP(memcmp("123abc---   +++", seq.begin, seq.end - seq.begin),==,0);
    CHECK_CMP(get_next(itr, &seq),==,0);
    destroy_iterator(itr);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(one_no_separator, one_cleared_buffer);
