#include "basic_testing.h"

extern int twotimes2(const char * begin, const char * end);
extern int twotimes(const char * s);

TEST(empty) {
    CHECK(twotimes(""));
    TEST_PASSED;
}

TEST(empty2) {
    char buf[1];
    buf[0] = 0;
    CHECK(twotimes2(buf,buf));
    TEST_PASSED;
}

MAIN_TEST_DRIVER(empty, empty2)
