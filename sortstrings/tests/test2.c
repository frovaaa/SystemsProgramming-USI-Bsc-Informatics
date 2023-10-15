#include <string.h>

#include "basic_testing.h"

extern void sort_strings(const char * input, char * output, unsigned int n);

TEST(ciao_ciao) {
    char buf[1000];
    sort_strings("ciao\0ciao", buf, 2);
    CHECK(memcmp(buf, "ciao\0ciao", 10) == 0);
    TEST_PASSED;
}

TEST(a_b) {
    char buf[1000];
    sort_strings("a\0b", buf, 2);
    CHECK(memcmp(buf, "a\0b", 4) == 0);
    TEST_PASSED;
}

TEST(a_b_c) {
    char buf[1000];
    sort_strings("a\0b\0c", buf, 3);
    CHECK(memcmp(buf, "a\0b\0c", 6) == 0);
    TEST_PASSED;
}

TEST(b_c_a) {
    char buf[1000];
    sort_strings("b\0c\0a", buf, 3);
    CHECK(memcmp(buf, "a\0b\0c", 6) == 0);
    TEST_PASSED;
}

TEST(c_a_b) {
    char buf[1000];
    sort_strings("c\0a\0b", buf, 3);
    CHECK(memcmp(buf, "a\0b\0c", 6) == 0);
    TEST_PASSED;
}

TEST(c_a_b_1) {
    char buf[1000];
    sort_strings("c\0a\0b", buf, 1);
    CHECK(memcmp(buf, "c", 2) == 0);
    TEST_PASSED;
}

TEST(c_a_b_2) {
    char buf[1000];
    sort_strings("c\0a\0b", buf, 2);
    CHECK(memcmp(buf, "a\0c", 2) == 0);
    TEST_PASSED;
}

TEST(a_a_2) {
    char buf[1000];
    sort_strings("a\0a", buf, 2);
    CHECK(memcmp(buf, "a\0a", 4) == 0);
    TEST_PASSED;
}

TEST(b_a_a_a_b) {
    char buf[1000];
    sort_strings("b\0a\0a\0a\0b", buf, 5);
    CHECK(memcmp(buf, "a\0a\0a\0b\0b", 10) == 0);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(ciao_ciao,
		 a_b,
		 a_b_c,
		 b_c_a,
		 c_a_b,
		 c_a_b_1,
		 c_a_b_2,
		 a_a_2,
		 b_a_a_a_b)
		 
