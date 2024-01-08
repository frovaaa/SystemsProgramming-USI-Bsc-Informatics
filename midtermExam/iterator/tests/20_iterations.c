#include <string.h>
#include "basic_testing.h"

#include "../iterator.h"


TEST (default_separators) {
    struct iterator * itr = create_iterator();
    CHECK(itr != 0);
    struct sequence seq;
    char buf[100];
    memset(buf, 255, sizeof(buf));
    memcpy(buf, "1;2;3,4;5;6;", 12);
    seq.begin = buf;
    seq.end = buf + 12;
    CHECK_CMP(set_text(itr, &seq),==,1);
    for (int i = 1; i < 7; ++i) {
        CHECK_CMP(get_next(itr, &seq),==,1);
        sprintf(buf, "%u", i);
        CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);
    }
    CHECK_CMP(get_next(itr, &seq),==,0);
    destroy_iterator(itr);
    TEST_PASSED;
}


TEST (only_separators_text) {
    struct iterator * itr = create_iterator();
    CHECK(itr != 0);
    struct sequence seq;
    char buf[100];
    memset(buf, 255, sizeof(buf));
    memcpy(buf, ";;;;;;;;;;;;;;;;;;;;,,,,,,,,", 28);
    seq.begin = buf;
    seq.end = buf + 28;
    CHECK_CMP(set_text(itr, &seq),==,1);
    CHECK_CMP(get_next(itr, &seq),==,0);
    destroy_iterator(itr);
    TEST_PASSED;
}

TEST (letter_separators) {
    struct iterator * itr = create_iterator();
    CHECK(itr != 0);
    struct sequence seq;
    char buf[100];
    memset(buf, 255, sizeof(buf));
    memcpy(buf, "abcdefghijk", 12);
    seq.begin = buf;
    seq.end = buf + 12;
    CHECK_CMP(set_text(itr, &seq),==,1);
    struct sequence sep;
    memcpy(buf, "ciao", 4);
    sep.begin = buf;
    sep.end = sep.begin + 4;
    CHECK_CMP(set_separators(itr, &sep),==,1);

    CHECK_CMP(get_next(itr, &seq),==,1);
    sprintf(buf, "b");
    CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);

    CHECK_CMP(get_next(itr, &seq),==,1);
    sprintf(buf, "defgh");
    CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);

    CHECK_CMP(get_next(itr, &seq),==,1);
    sprintf(buf, "jk");
    CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);

    CHECK_CMP(get_next(itr, &seq),==,0);
    destroy_iterator(itr);
    TEST_PASSED;
}

TEST (non_default_separators) {
    struct iterator * itr = create_iterator();
    CHECK(itr != 0);
    struct sequence seq;
    char buf[100];
    memset(buf, 255, sizeof(buf));
    memcpy(buf, "1.2:3-4:5.6:", 12);
    seq.begin = buf;
    seq.end = buf + 12;
    CHECK_CMP(set_text(itr, &seq),==,1);
    struct sequence sep;
    memcpy(buf, ".:-", 3);
    sep.begin = buf;
    sep.end = sep.begin + 3;
    CHECK_CMP(set_separators(itr, &sep),==,1);

    for (int i = 1; i < 7; ++i) {
        CHECK_CMP(get_next(itr, &seq),==,1);
        sprintf(buf, "%u", i);
        CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);
    }
    CHECK_CMP(get_next(itr, &seq),==,0);
    destroy_iterator(itr);
    TEST_PASSED;
}



TEST (changing_separators) {
    struct iterator * itr = create_iterator();
    CHECK(itr != 0);
    struct sequence seq;
    char buf[100];
    memset(buf, 255, sizeof(buf));
    memcpy(buf, "text1;text2,text3.text4,text5,text6.text7.text8:text9-text10", 60);
    seq.begin = buf;
    seq.end = buf + 60;
    CHECK_CMP(set_text(itr, &seq),==,1);

    CHECK_CMP(get_next(itr, &seq),==,1);
    sprintf(buf, "text1");
    CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);
    CHECK_CMP(get_next(itr, &seq),==,1);
    sprintf(buf, "text2");
    CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);
    CHECK_CMP(get_next(itr, &seq),==,1);
    sprintf(buf, "text3.text4");
    CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);

    struct sequence sep;
    buf[0] = '.';
    sep.begin = buf;
    sep.end = sep.begin + 1;
    CHECK_CMP(set_separators(itr, &sep),==,1);

    CHECK_CMP(get_next(itr, &seq),==,1);
    sprintf(buf, ",text5,text6");
    CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);
    CHECK_CMP(get_next(itr, &seq),==,1);
    sprintf(buf, "text7");
    CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);

    buf[0] = ':';
    sep.begin = buf;
    sep.end = sep.begin + 1;
    CHECK_CMP(set_separators(itr, &sep),==,1);
    CHECK_CMP(get_next(itr, &seq),==,1);
    sprintf(buf, ".text8");
    CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);

    buf[0] = '-';
    sep.begin = buf;
    sep.end = sep.begin + 1;
    CHECK_CMP(set_separators(itr, &sep),==,1);
    CHECK_CMP(get_next(itr, &seq),==,1);
    sprintf(buf, ":text9");
    CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);
    CHECK_CMP(get_next(itr, &seq),==,1);
    sprintf(buf, "text10");
    CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);

    CHECK_CMP(get_next(itr, &seq),==,0);
    destroy_iterator(itr);
    TEST_PASSED;
}

TEST (many_separators) {
    struct iterator * itr = create_iterator();
    CHECK(itr != 0);
    struct sequence seq;
    char buf[100];
    memcpy(buf, "text;;;;;;text;;;;;;;text;;;;text;;;", 36);
    seq.begin = buf;
    seq.end = buf + 36;
    CHECK_CMP(set_text(itr, &seq),==,1);
    memcpy(buf, "text", 4);
    for (int i = 0; i < 4; ++i) {
        CHECK_CMP(get_next(itr, &seq),==,1);
        CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);
    }
    CHECK_CMP(get_next(itr, &seq),==,0);
    destroy_iterator(itr);
    TEST_PASSED;
}


MAIN_TEST_DRIVER(default_separators, non_default_separators, letter_separators, only_separators_text, changing_separators, many_separators);
