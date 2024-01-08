#include "basic_testing.h"
#include "../iterator.h"
#include <stdio.h>
#include <string.h>


TEST (create_itr1_itr2) {
    struct iterator * itr1 = create_iterator();
    CHECK(itr1 != 0);
    struct iterator * itr2 = create_iterator();
    CHECK(itr2 != 0);
    destroy_iterator(itr1);
    destroy_iterator(itr2);
    TEST_PASSED;
}

TEST (create_itr1_itr2_many) {
    struct iterator * itr1 = create_iterator();
    CHECK(itr1 != 0);
    struct iterator * itr2 = create_iterator();
    CHECK(itr2 != 0);

    for (unsigned int i = 1; i <= 1000; ++i) {
        char xyz[20], abc[25];
	char buf[1024];
	struct sequence seq;

        sprintf(xyz, "xyz%u", i);
        sprintf(abc, "abc%u", i);


	seq.begin = xyz;
	seq.end = xyz + strlen(xyz);
        CHECK_CMP(set_separators(itr1, &seq),==,1);

	seq.begin = abc;
	seq.end = abc + strlen(abc);
        CHECK_CMP(set_separators(itr2, &seq),==,1);

	seq.begin = buf;
	seq.end = buf + 1024;
        CHECK_CMP(set_text(itr1, &seq),==,1);

	seq.begin = buf;
	seq.end = buf + 1024;
        CHECK_CMP(set_text(itr2, &seq),==,1);
    }
    destroy_iterator(itr1);
    destroy_iterator(itr2);
    TEST_PASSED;
}


TEST (same_string_many_iterators) {
    char buf[100];
    memcpy(buf, "text0text1text2text3text4text5text6text7text8text9", 50);
    struct iterator *itrs[10];

	struct sequence seq;
    for (unsigned int i = 0; i < 10; ++i) {
        char sep[2];
        itrs[i] = create_iterator();
        CHECK(itrs[i] != 0);
        seq.begin = buf;
        seq.end = seq.begin + 50;
        CHECK_CMP(set_text(itrs[i], &seq),==,1);

        sep[0] = i + '0';
        seq.begin = sep;
        seq.end = sep + 1;
        CHECK_CMP(set_separators(itrs[i], &seq),==,1);
    }

    for (unsigned int i = 0; i < 9; ++i) {
        char cmp[100];
        CHECK_CMP(get_next(itrs[i], &seq),==,1);

        unsigned len = 0;
        for (unsigned int j = 0; j < i; ++j)
            len += sprintf(cmp  + len, "text%u", j);
        len += sprintf(cmp + len, "text");

        CHECK_CMP(memcmp(cmp, seq.begin, seq.end - seq.begin),==,0);
        CHECK_CMP(get_next(itrs[i], &seq),==,1);

        len = 0;
        for (unsigned int j = i + 1; j < 10; ++j)
            len += sprintf(cmp  + len, "text%u", j);

        CHECK_CMP(memcmp(cmp, seq.begin, seq.end - seq.begin),==,0);
    }

    CHECK_CMP(get_next(itrs[9], &seq),==,1);
    CHECK_CMP(memcmp(buf, seq.begin, seq.end - seq.begin),==,0);
    CHECK_CMP(get_next(itrs[9], &seq),==,0);

    for (unsigned int i = 0; i < 10; ++i)
        destroy_iterator(itrs[i]);

    TEST_PASSED;
}


MAIN_TEST_DRIVER(create_itr1_itr2, create_itr1_itr2_many, same_string_many_iterators);
