#include <string.h>

#include "basic_testing.h"

extern void sort_strings(const char * input, char * output, unsigned int n);

TEST(one_string) {
    char buf[100];
    sort_strings("ciao", buf, 1);
    CHECK(memcmp(buf, "ciao", 5) == 0);
    TEST_PASSED;
}

TEST(two_strings) {
    char buf[100];
    sort_strings("ciao\0blah", buf, 2);
    CHECK(memcmp(buf, "blah\0ciao", 10) == 0);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(one_string, two_strings)
    
