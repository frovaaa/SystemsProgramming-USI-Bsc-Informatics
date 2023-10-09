#include "basic_testing.h"

extern int concatenate(char * s, unsigned max_size, const char * s2);

TEST(empty) {
    char buffer[1000];

    buffer[0] = 0;
    CHECK(concatenate(buffer, 10, ""));
    CHECK_STRING_CMP(buffer,==,"");
    TEST_PASSED;
}

TEST(ciao) {
    char buffer[1000];
    strcpy(buffer, "ciao");
    CHECK(concatenate(buffer, 5, ""));
    CHECK_STRING_CMP(buffer, ==, "ciao");
    TEST_PASSED;
}

TEST(x) {
    char buffer[1000];
    strcpy(buffer, "x");
    CHECK(!concatenate(buffer, 2, "y"));
    CHECK_STRING_CMP(buffer, ==, "x");
    TEST_PASSED;
}

TEST(bella_100) {
    char buffer[1000];
    strcpy(buffer, "bella ");
    CHECK(concatenate(buffer, 100, "ciao"));
    CHECK_STRING_CMP(buffer,  ==, "bella ciao");
    TEST_PASSED;
}

TEST(bella_10) {
    char buffer[1000];
    strcpy(buffer, "bella ");
    CHECK(!concatenate(buffer, 10, "ciao"));
    CHECK_STRING_CMP(buffer, ==, "bella cia");
    TEST_PASSED;
}

TEST(ciao_bella_16) {
    char buffer[1000];
    strcpy(buffer, "ciao bella ");
    CHECK(concatenate(buffer, 16, "ciao"));
    CHECK_STRING_CMP(buffer, ==, "ciao bella ciao");
    TEST_PASSED;
}

TEST(ciao_bella_15) {
    char buffer[1000];
    strcpy(buffer, "ciao bella ");
    CHECK(!concatenate(buffer, 15, "ciao"));
    CHECK_STRING_CMP(buffer, ==, "ciao bella cia");
    TEST_PASSED;
}

MAIN_TEST_DRIVER(empty, ciao, x, bella_100, bella_10, ciao_bella_16, ciao_bella_15);

