#include "basic_testing.h"
#include "../racing.h"

TEST (init_delete_database) {
    CHECK_CMP(racing_init("./tests/queries.data"),==,15);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,5);
    CHECK_CMP(count_drivers(0, 0),==,5);
    CHECK_CMP(get_teams(),==,5);
    racing_delete();

    CHECK_CMP(racing_init("./tests/queries_random_1.data"),==,1058);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,1000);
    CHECK_CMP(count_drivers(0, 0),==,50);
    CHECK_CMP(get_teams(),==,8);
    racing_delete();

    CHECK_CMP(racing_init("./tests/queries_random_2.data"),==,1058);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,1000);
    CHECK_CMP(count_drivers(0, 0),==,50);
    CHECK_CMP(get_teams(),==,8);
    racing_delete();


    CHECK_CMP(racing_init("./tests/queries_random_3.data"),==,1058);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,1000);
    CHECK_CMP(count_drivers(0, 0),==,50);
    CHECK_CMP(get_teams(),==,8);
    racing_delete();
    TEST_PASSED;
}

TEST (init_without_delete) {
    CHECK_CMP(racing_init("./tests/queries.data"),==,15);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,5);
    CHECK_CMP(count_drivers(0, 0),==,5);
    CHECK_CMP(get_teams(),==,5);

    CHECK_CMP(racing_init("./tests/queries_random_1.data"),==,1058);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,1000);
    CHECK_CMP(count_drivers(0, 0),==,50);
    CHECK_CMP(get_teams(),==,8);

    CHECK_CMP(racing_init("./tests/queries_random_2.data"),==,1058);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,1000);
    CHECK_CMP(count_drivers(0, 0),==,50);
    CHECK_CMP(get_teams(),==,8);

    CHECK_CMP(racing_init("./tests/queries_random_3.data"),==,1058);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,1000);
    CHECK_CMP(count_drivers(0, 0),==,50);
    CHECK_CMP(get_teams(),==,8);
    racing_delete();
    TEST_PASSED;
}


MAIN_TEST_DRIVER (init_delete_database, init_without_delete);
