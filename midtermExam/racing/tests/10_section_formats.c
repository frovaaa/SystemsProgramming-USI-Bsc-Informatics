#include "basic_testing.h"
#include "../racing.h"

TEST (shuffled_fields) {
    CHECK_CMP(racing_init("./tests/shuffled.data"),==,90);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,50);
    CHECK_CMP(get_teams(),==,10);
    CHECK_CMP(count_drivers(0, 0),==,30);
    racing_delete();
    TEST_PASSED;
}

TEST (missing_fields) {
    CHECK_CMP(racing_init("./tests/missing_fields.data"),==,3);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,1);
    CHECK_CMP(get_teams(),==,0);
    CHECK_CMP(count_drivers(0, 0),==,2);
    racing_delete();
    TEST_PASSED;
}

TEST (wrong_car_formats) {
    CHECK_CMP(racing_init("./tests/wrong_car_format.data"),==,-1);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,0);
    CHECK_CMP(get_teams(),==,0);
    CHECK_CMP(count_drivers(0, 0),==,0);
    racing_delete();
    TEST_PASSED;
}

TEST (wrong_team_formats) {
    CHECK_CMP(racing_init("./tests/wrong_team_format.data"),==,-1);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,0);
    CHECK_CMP(get_teams(),==,0);
    CHECK_CMP(count_drivers(0, 0),==,0);
    racing_delete();
    TEST_PASSED;
}

TEST (wrong_driver_formats) {
    CHECK_CMP(racing_init("./tests/wrong_driver_format.data"),==,-1);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,0);
    CHECK_CMP(get_teams(),==,0);
    CHECK_CMP(count_drivers(0, 0),==,0);
    racing_delete();
    TEST_PASSED;
}

TEST (car_no_end_section) {
    CHECK_CMP(racing_init("./tests/car_no_end.data"),==,-1);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,0);
    CHECK_CMP(get_teams(),==,0);
    CHECK_CMP(count_drivers(0, 0),==,0);
    racing_delete();
    TEST_PASSED;
}

TEST (team_no_end_section) {
    CHECK_CMP(racing_init("./tests/team_no_end.data"),==,-1);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,0);
    CHECK_CMP(get_teams(),==,0);
    CHECK_CMP(count_drivers(0, 0),==,0);
    racing_delete();
    TEST_PASSED;
}

TEST (driver_no_end_section) {
    CHECK_CMP(racing_init("./tests/driver_no_end.data"),==,-1);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,0);
    CHECK_CMP(get_teams(),==,0);
    CHECK_CMP(count_drivers(0, 0),==,0);
    racing_delete();
    TEST_PASSED;
}

TEST (long_lines) {
    CHECK_CMP(racing_init("./tests/long_lines.data"),==,300);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,100);
    CHECK_CMP(get_teams(),==,100);
    CHECK_CMP(count_drivers(0, 0),==,100);
    racing_delete();
    TEST_PASSED;
}

MAIN_TEST_DRIVER (shuffled_fields, missing_fields, wrong_car_formats,
    wrong_driver_formats, wrong_team_formats, car_no_end_section,
    team_no_end_section, driver_no_end_section, long_lines);
