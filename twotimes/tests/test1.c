#include "basic_testing.h"

extern int twotimes2(const char * begin, const char * end);
extern int twotimes(const char * s);

TEST(single_char) {
    CHECK(!twotimes("a"));
    TEST_PASSED;
}

TEST(single_char2) {
    const char * s = "a";
    CHECK(!twotimes2(s,s+1));
    TEST_PASSED;
}

TEST(one_char_same) {
    CHECK(twotimes("aa"));
    TEST_PASSED;
}

TEST(one_char_same2) {
    const char * s = "aa";
    CHECK(twotimes2(s, s + 2));
    TEST_PASSED;
}

TEST(one_char_diff) {
    CHECK(!twotimes("ab"));
    TEST_PASSED;
}

TEST(one_char_diff2) {
    const char * s = "ab";
    CHECK(!twotimes2(s,s+2));
    TEST_PASSED;
}

MAIN_TEST_DRIVER(single_char, single_char2,
		 one_char_same, one_char_same2,
		 one_char_diff, one_char_diff2)
