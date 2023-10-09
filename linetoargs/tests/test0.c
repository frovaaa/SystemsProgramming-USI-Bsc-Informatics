#include "basic_testing.h"

extern int line_to_args (char * argv[], int max_count, char * line);

TEST (empty) {
    char buf[1000];
    char * argv[1000];
    buf[0] = 0;
    CHECK_INT_CMP(line_to_args(argv, 1000, buf),==,0);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(empty);

