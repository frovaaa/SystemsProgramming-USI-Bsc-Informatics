#include "basic_testing.h"

extern int concatenate(char * s, unsigned max_size, const char * s2);

TEST(correct_compilation) {
    char buffer[1000];

    buffer[0] = 0;
    concatenate(buffer, 10, "");
    TEST_PASSED;
}

MAIN_TEST_DRIVER(correct_compilation)

