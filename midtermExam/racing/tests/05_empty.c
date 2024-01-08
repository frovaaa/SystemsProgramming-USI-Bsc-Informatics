#include "basic_testing.h"
#include "../racing.h"

TEST (empty_file) {
    CHECK_CMP(racing_init("./tests/empty.data"),==,0);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,0);
    CHECK_CMP(get_teams(),==,0);
    CHECK_CMP(count_drivers(0, 0),==,0);
    racing_delete();
    TEST_PASSED;
}

MAIN_TEST_DRIVER (empty_file);
