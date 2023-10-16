#include "basic_testing.h"

#include "../strstack.h"

TEST (clear) {
    strstack_clear();
    TEST_PASSED;
}

MAIN_TEST_DRIVER (clear)

