#include "basic_testing.h"

#include "../bufile.h"

TEST(correct_compilation) {
    char buf[1000];
    char s[1000];
    buf[0] = '\n';
    BUFILE * f = bufopen(buf, buf + 1000);
    CHECK(f != 0);
    bufgets(s, 10, f);
    bufclose(f);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(correct_compilation)
