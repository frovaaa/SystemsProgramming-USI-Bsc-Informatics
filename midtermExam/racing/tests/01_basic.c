#include "basic_testing.h"
#include "../racing.h"

TEST (not_existing_file) {
    CHECK_CMP(racing_init("not_existing.data"),==,-1);
    racing_delete();
    TEST_PASSED;
}

TEST (one_car_file) {
    CHECK_CMP(racing_init("./tests/basic_one_car.data"),==,1);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,1);
    racing_delete();
    TEST_PASSED;
}

TEST (one_team_file) {
    CHECK_CMP(racing_init("./tests/basic_one_team.data"),==,1);
    CHECK_CMP(get_teams(),==,1);
    racing_delete();
    TEST_PASSED;
}

TEST (one_driver_file) {
    CHECK_CMP(racing_init("./tests/basic_one_driver.data"),==,1);
    CHECK_CMP(count_drivers(0, 0),==,1);
    racing_delete();
    TEST_PASSED;
}

TEST (complete_file) {
    CHECK_CMP(racing_init("./tests/basic_complete.data"),==,3);
    CHECK_CMP(count_drivers(0, 0),==,1);
    CHECK_CMP(get_teams(),==,1);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,1);
    racing_delete();
    TEST_PASSED;
}

MAIN_TEST_DRIVER (not_existing_file, one_car_file, one_team_file, one_driver_file, complete_file);
