#include <assert.h>
#include <string.h>

#include "basic_testing.h"

extern void sort_strings(const char * input, char * output, unsigned int n);

TEST(empty) {
    char buf[100];
    sort_strings("", buf, 1);
    CHECK(memcmp(buf, "", 1) == 0);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(empty)
