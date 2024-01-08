#include "basic_testing.h"
#include "../racing.h"

TEST (car_queries_1) {
    CHECK_CMP(racing_init("./tests/queries.data"),==,15);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,5);
    CHECK_CMP(count_cars(0, "maker 2000", 0, 0, 0),==,0);
    CHECK_CMP(count_cars("model 16", "maker 4", 0, 0, 0),==,1);
    CHECK_CMP(count_cars(0, 0, 0, 80, 0),==,2);
    CHECK_CMP(count_cars(0, 0, 0, 0, 35000),==,3);
    CHECK_CMP(count_cars("model 2", "maker 1", "driver 23", 80, 35000),==,1);
    racing_delete();
    TEST_PASSED;
}

TEST (driver_queries_1) {
    CHECK_CMP(racing_init("./tests/queries.data"),==,15);
    CHECK_CMP(count_drivers("driver 10", 0),==,0);
    CHECK_CMP(count_drivers("driver 15", 0),==,1);
    CHECK_CMP(count_drivers("driver 15", "team 2"),==,1);
    CHECK_CMP(count_drivers(0, "team 2"),==,2);
    racing_delete();
    TEST_PASSED;

}

TEST (team_queries_1) {
    CHECK_CMP(racing_init("./tests/queries.data"),==,15);
    CHECK_CMP(get_teams(),==,5);
    racing_delete();
    TEST_PASSED;

}

TEST (car_queries_random_1) {
    CHECK_CMP(racing_init("./tests/queries_random_1.data"),==,1058);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,1000);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 2", 160, 20000),==,2);
    CHECK_CMP(count_cars("model 1", "maker 1", "driver 4", 150, 40000),==,0);
    CHECK_CMP(count_cars(0, "maker 2", "driver 2", 190, 20000),==,3);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 2", 160, 35000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 4", 170, 45000),==,0);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 1", 120, 25000),==,0);
    CHECK_CMP(count_cars("model 1", "maker 1", "driver 1", 150, 25000),==,2);
    CHECK_CMP(count_cars(0, "maker 0", 0, 140, 30000),==,4);
    CHECK_CMP(count_cars("model 1", "maker 2", 0, 180, 0),==,9);
    CHECK_CMP(count_cars("model 1", "maker 1", 0, 80, 25000),==,3);
    CHECK_CMP(count_cars(0, "maker 0", 0, 140, 45000),==,3);
    CHECK_CMP(count_cars(0, "maker 2", "driver 1", 100, 20000),==,0);
    CHECK_CMP(count_cars("model 0", 0, "driver 4", 130, 25000),==,1);
    CHECK_CMP(count_cars("model 0", 0, "driver 1", 170, 40000),==,5);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 1", 130, 40000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 4", 130, 30000),==,1);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 2", 0, 20000),==,4);
    CHECK_CMP(count_cars("model 1", "maker 0", 0, 110, 40000),==,1);
    CHECK_CMP(count_cars(0, "maker 2", "driver 2", 150, 45000),==,0);
    CHECK_CMP(count_cars("model 1", "maker 1", "driver 3", 130, 20000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 4", 110, 20000),==,0);
    CHECK_CMP(count_cars("model 0", 0, "driver 2", 180, 30000),==,0);
    CHECK_CMP(count_cars("model 1", "maker 1", "driver 0", 190, 35000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 2", 190, 20000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 3", 90, 20000),==,0);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 2", 90, 35000),==,0);
    CHECK_CMP(count_cars(0, "maker 1", "driver 3", 170, 25000),==,2);
    CHECK_CMP(count_cars("model 0", 0, "driver 1", 170, 30000),==,1);
    CHECK_CMP(count_cars("model 1", 0, "driver 2", 130, 45000),==,0);
    CHECK_CMP(count_cars(0, "maker 2", "driver 3", 80, 35000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 3", 80, 40000),==,0);
    CHECK_CMP(count_cars("model 1", 0, 0, 140, 25000),==,6);
    CHECK_CMP(count_cars("model 1", 0, "driver 1", 110, 30000),==,3);
    CHECK_CMP(count_cars(0, 0, "driver 3", 120, 20000),==,1);
    CHECK_CMP(count_cars(0, "maker 0", "driver 0", 170, 35000),==,2);
    CHECK_CMP(count_cars(0, 0, "driver 2", 80, 45000),==,2);
    CHECK_CMP(count_cars(0, 0, "driver 4", 140, 30000),==,2);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 3", 80, 35000),==,1);
    CHECK_CMP(count_cars(0, 0, "driver 1", 130, 45000),==,4);
    CHECK_CMP(count_cars(0, "maker 1", "driver 1", 90, 40000),==,2);
    CHECK_CMP(count_cars(0, 0, "driver 2", 150, 0),==,15);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 4", 120, 0),==,2);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 2", 140, 0),==,4);
    CHECK_CMP(count_cars("model 0", 0, "driver 3", 0, 20000),==,14);
    CHECK_CMP(count_cars("model 0", 0, "driver 3", 120, 30000),==,0);
    CHECK_CMP(count_cars("model 1", "maker 0", 0, 180, 25000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 3", 120, 30000),==,1);
    CHECK_CMP(count_cars(0, 0, "driver 1", 160, 30000),==,2);
    CHECK_CMP(count_cars("model 0", 0, 0, 110, 35000),==,7);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 0", 140, 0),==,0);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 4", 0, 20000),==,8);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 0", 170, 30000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 0", 190, 20000),==,0);
    CHECK_CMP(count_cars(0, "maker 1", "driver 4", 140, 20000),==,0);
    CHECK_CMP(count_cars(0, 0, "driver 3", 90, 30000),==,2);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 3", 90, 45000),==,0);
    CHECK_CMP(count_cars(0, "maker 1", "driver 2", 170, 0),==,8);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 0", 150, 0),==,3);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 2", 130, 20000),==,1);
    CHECK_CMP(count_cars("model 1", 0, "driver 3", 90, 30000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 1", 110, 25000),==,0);
    CHECK_CMP(count_cars(0, "maker 0", 0, 140, 0),==,31);
    CHECK_CMP(count_cars(0, "maker 2", 0, 110, 0),==,26);
    CHECK_CMP(count_cars(0, "maker 1", "driver 1", 80, 0),==,4);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 4", 190, 35000),==,0);
    CHECK_CMP(count_cars(0, "maker 0", "driver 3", 150, 20000),==,1);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 3", 130, 20000),==,0);
    CHECK_CMP(count_cars("model 0", 0, "driver 2", 130, 40000),==,2);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 3", 110, 25000),==,0);
    racing_delete();
    TEST_PASSED;
}

TEST (driver_queries_random_1) {
    CHECK_CMP(racing_init("./tests/queries_random_1.data"),==,1058);
    CHECK_CMP(count_drivers(0, 0),==,50);
    CHECK_CMP(count_drivers("driver 1", "team 0"),==,0);
    CHECK_CMP(count_drivers("driver 0", "team 7"),==,2);
    CHECK_CMP(count_drivers(0, "team 3"),==,5);
    CHECK_CMP(count_drivers("driver 4", "team 0"),==,0);
    CHECK_CMP(count_drivers("driver 3", 0),==,9);
    CHECK_CMP(count_drivers(0, "team 7"),==,4);
    CHECK_CMP(count_drivers("driver 4", "team 8"),==,1);
    CHECK_CMP(count_drivers("driver 1", "team 7"),==,0);
    CHECK_CMP(count_drivers("driver 0", "team 9"),==,2);
    CHECK_CMP(count_drivers("driver 3", "team 1"),==,0);
    CHECK_CMP(count_drivers("driver 4", "team 3"),==,1);
    CHECK_CMP(count_drivers("driver 3", "team 4"),==,0);
    CHECK_CMP(count_drivers("driver 3", "team 2"),==,0);
    CHECK_CMP(count_drivers("driver 0", "team 7"),==,2);
    CHECK_CMP(count_drivers("driver 4", "team 1"),==,0);
    racing_delete();
    TEST_PASSED;
}

TEST (team_queries_random_1) {
    CHECK_CMP(racing_init("./tests/queries_random_1.data"),==,1058);
    CHECK_CMP(get_teams(),==,8);
    racing_delete();
    TEST_PASSED;
}

TEST (car_queries_random_2) {
    CHECK_CMP(racing_init("./tests/queries_random_2.data"),==,1058);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,1000);
    CHECK_CMP(count_cars("model 1", "maker 1", "driver 3", 80, 35000),==,1);
    CHECK_CMP(count_cars(0, "maker 0", "driver 2", 130, 0),==,9);
    CHECK_CMP(count_cars("model 1", "maker 0", 0, 180, 20000),==,3);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 1", 90, 45000),==,0);
    CHECK_CMP(count_cars("model 0", 0, "driver 1", 80, 25000),==,0);
    CHECK_CMP(count_cars(0, "maker 1", 0, 150, 30000),==,8);
    CHECK_CMP(count_cars("model 0", 0, "driver 0", 170, 25000),==,2);
    CHECK_CMP(count_cars("model 0", 0, "driver 1", 130, 40000),==,1);
    CHECK_CMP(count_cars("model 0", 0, "driver 0", 110, 35000),==,2);
    CHECK_CMP(count_cars(0, "maker 2", 0, 140, 35000),==,6);
    CHECK_CMP(count_cars("model 1", "maker 1", "driver 0", 0, 35000),==,5);
    CHECK_CMP(count_cars(0, "maker 2", "driver 2", 130, 40000),==,2);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 2", 130, 35000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 4", 130, 45000),==,0);
    CHECK_CMP(count_cars("model 1", "maker 1", "driver 2", 150, 40000),==,0);
    CHECK_CMP(count_cars("model 1", 0, "driver 1", 150, 30000),==,2);
    CHECK_CMP(count_cars("model 1", "maker 1", "driver 0", 170, 30000),==,1);
    CHECK_CMP(count_cars(0, "maker 1", "driver 0", 100, 45000),==,2);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 4", 80, 35000),==,0);
    CHECK_CMP(count_cars(0, "maker 0", "driver 1", 130, 40000),==,1);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 3", 170, 40000),==,2);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 4", 180, 30000),==,2);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 2", 80, 35000),==,0);
    CHECK_CMP(count_cars(0, "maker 1", "driver 1", 180, 25000),==,4);
    CHECK_CMP(count_cars(0, "maker 2", "driver 2", 150, 30000),==,1);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 1", 90, 30000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 1", 140, 35000),==,1);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 3", 120, 20000),==,0);
    CHECK_CMP(count_cars(0, 0, "driver 2", 110, 45000),==,0);
    CHECK_CMP(count_cars(0, "maker 1", "driver 1", 180, 45000),==,3);
    CHECK_CMP(count_cars("model 1", 0, "driver 3", 130, 40000),==,0);
    CHECK_CMP(count_cars(0, "maker 2", 0, 150, 40000),==,3);
    CHECK_CMP(count_cars("model 0", 0, 0, 170, 45000),==,5);
    CHECK_CMP(count_cars("model 0", 0, "driver 2", 160, 20000),==,1);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 4", 110, 30000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 1", "driver 4", 150, 40000),==,0);
    CHECK_CMP(count_cars("model 1", 0, "driver 1", 170, 35000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", 0, 0, 35000),==,36);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 1", 120, 40000),==,0);
    CHECK_CMP(count_cars("model 1", 0, 0, 100, 0),==,34);
    CHECK_CMP(count_cars("model 0", 0, "driver 1", 110, 35000),==,2);
    CHECK_CMP(count_cars("model 0", 0, "driver 1", 90, 45000),==,3);
    CHECK_CMP(count_cars("model 0", 0, "driver 4", 140, 0),==,7);
    CHECK_CMP(count_cars("model 1", 0, "driver 2", 120, 30000),==,0);
    CHECK_CMP(count_cars("model 1", 0, "driver 0", 130, 0),==,8);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 4", 170, 40000),==,2);
    CHECK_CMP(count_cars("model 1", "maker 1", "driver 0", 120, 20000),==,2);
    CHECK_CMP(count_cars(0, "maker 2", "driver 1", 150, 40000),==,0);
    CHECK_CMP(count_cars(0, "maker 1", "driver 4", 170, 0),==,8);
    CHECK_CMP(count_cars(0, "maker 2", "driver 0", 0, 40000),==,15);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 1", 150, 40000),==,1);
    CHECK_CMP(count_cars(0, "maker 1", "driver 4", 180, 20000),==,2);
    CHECK_CMP(count_cars("model 0", 0, "driver 4", 160, 40000),==,2);
    CHECK_CMP(count_cars(0, "maker 1", 0, 170, 0),==,29);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 0", 90, 30000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 1", 90, 35000),==,0);
    CHECK_CMP(count_cars(0, "maker 2", 0, 100, 45000),==,7);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 0", 170, 40000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 3", 190, 0),==,1);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 3", 160, 45000),==,0);
    CHECK_CMP(count_cars(0, "maker 1", "driver 0", 120, 35000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 4", 140, 30000),==,2);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 2", 110, 40000),==,0);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 1", 180, 30000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 3", 100, 35000),==,1);
    CHECK_CMP(count_cars("model 1", 0, "driver 3", 80, 45000),==,0);
    CHECK_CMP(count_cars(0, "maker 2", "driver 1", 120, 40000),==,1);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 3", 130, 35000),==,0);
    CHECK_CMP(count_cars("model 1", "maker 0", 0, 0, 0),==,145);
    racing_delete();
    TEST_PASSED;
}

TEST (driver_queries_random_2) {
    CHECK_CMP(racing_init("./tests/queries_random_2.data"),==,1058);
    CHECK_CMP(count_drivers(0, 0),==,50);
    CHECK_CMP(count_drivers(0, "team 4"),==,6);
    CHECK_CMP(count_drivers("driver 4", "team 1"),==,2);
    CHECK_CMP(count_drivers("driver 2", 0),==,9);
    CHECK_CMP(count_drivers("driver 1", 0),==,8);
    CHECK_CMP(count_drivers(0, "team 4"),==,6);
    CHECK_CMP(count_drivers("driver 4", "team 3"),==,2);
    CHECK_CMP(count_drivers("driver 3", "team 4"),==,1);
    CHECK_CMP(count_drivers("driver 2", "team 9"),==,0);
    CHECK_CMP(count_drivers("driver 4", 0),==,15);
    CHECK_CMP(count_drivers("driver 0", "team 8"),==,1);
    CHECK_CMP(count_drivers(0, "team 1"),==,11);
    CHECK_CMP(count_drivers("driver 1", "team 7"),==,0);
    CHECK_CMP(count_drivers("driver 1", 0),==,8);
    CHECK_CMP(count_drivers(0, "team 3"),==,4);
    CHECK_CMP(count_drivers(0, "team 7"),==,6);
    racing_delete();
    TEST_PASSED;
}

TEST (team_queries_random_2) {
    CHECK_CMP(racing_init("./tests/queries_random_2.data"),==,1058);
    CHECK_CMP(get_teams(),==,8);
    racing_delete();
    TEST_PASSED;
}

TEST (car_queries_random_3) {
    CHECK_CMP(racing_init("./tests/queries_random_3.data"),==,1058);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,1000);
    CHECK_CMP(count_cars(0, "maker 0", 0, 110, 40000),==,4);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 3", 160, 20000),==,0);
    CHECK_CMP(count_cars(0, 0, "driver 3", 140, 20000),==,5);
    CHECK_CMP(count_cars(0, "maker 1", "driver 0", 90, 45000),==,1);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 1", 100, 20000),==,1);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 4", 90, 30000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 2", 80, 25000),==,1);
    CHECK_CMP(count_cars(0, 0, "driver 4", 90, 40000),==,3);
    CHECK_CMP(count_cars("model 1", "maker 1", "driver 0", 190, 20000),==,2);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 2", 100, 0),==,2);
    CHECK_CMP(count_cars("model 1", 0, 0, 150, 25000),==,9);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 4", 0, 40000),==,5);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 4", 190, 25000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 3", 80, 20000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 1", 80, 0),==,2);
    CHECK_CMP(count_cars("model 0", 0, "driver 2", 0, 25000),==,23);
    CHECK_CMP(count_cars(0, 0, "driver 4", 180, 35000),==,0);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 2", 0, 45000),==,10);
    CHECK_CMP(count_cars("model 0", 0, "driver 1", 130, 30000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 1", 100, 45000),==,0);
    CHECK_CMP(count_cars("model 1", 0, "driver 1", 100, 35000),==,2);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 1", 100, 20000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 4", 190, 45000),==,0);
    CHECK_CMP(count_cars(0, "maker 1", "driver 3", 150, 25000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 0", 130, 25000),==,1);
    CHECK_CMP(count_cars(0, "maker 0", "driver 4", 160, 45000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 1", 150, 35000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 2", 160, 25000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 4", 100, 45000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 2", 170, 20000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 1", 80, 40000),==,0);
    CHECK_CMP(count_cars(0, "maker 1", 0, 80, 30000),==,6);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 0", 130, 25000),==,0);
    CHECK_CMP(count_cars(0, "maker 1", "driver 4", 170, 30000),==,2);
    CHECK_CMP(count_cars(0, "maker 1", "driver 1", 100, 45000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 4", 170, 35000),==,1);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 3", 140, 0),==,1);
    CHECK_CMP(count_cars(0, "maker 2", "driver 3", 140, 45000),==,2);
    CHECK_CMP(count_cars("model 0", 0, "driver 0", 80, 35000),==,2);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 4", 150, 20000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 1", 100, 45000),==,0);
    CHECK_CMP(count_cars(0, 0, "driver 1", 140, 40000),==,2);
    CHECK_CMP(count_cars(0, 0, "driver 2", 160, 35000),==,1);
    CHECK_CMP(count_cars(0, "maker 2", "driver 4", 140, 45000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 1", "driver 0", 150, 40000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 1", 170, 0),==,4);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 1", 170, 20000),==,0);
    CHECK_CMP(count_cars("model 0", 0, "driver 1", 150, 20000),==,1);
    CHECK_CMP(count_cars(0, "maker 2", "driver 4", 110, 45000),==,0);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 4", 110, 20000),==,0);
    CHECK_CMP(count_cars("model 0", 0, "driver 1", 90, 45000),==,1);
    CHECK_CMP(count_cars(0, "maker 1", "driver 3", 130, 45000),==,2);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 3", 120, 0),==,4);
    CHECK_CMP(count_cars("model 1", "maker 0", "driver 4", 160, 45000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 0", 0, 140, 35000),==,2);
    CHECK_CMP(count_cars(0, "maker 2", "driver 0", 170, 40000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 0", 190, 20000),==,2);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 2", 180, 40000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 1", "driver 1", 170, 20000),==,1);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 0", 180, 25000),==,0);
    CHECK_CMP(count_cars(0, "maker 1", "driver 0", 160, 40000),==,1);
    CHECK_CMP(count_cars("model 0", 0, "driver 1", 100, 0),==,8);
    CHECK_CMP(count_cars(0, 0, "driver 0", 80, 35000),==,2);
    CHECK_CMP(count_cars(0, "maker 1", 0, 180, 45000),==,0);
    CHECK_CMP(count_cars(0, "maker 2", "driver 1", 150, 20000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 0", "driver 4", 140, 30000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 0", 130, 30000),==,0);
    CHECK_CMP(count_cars("model 0", "maker 2", "driver 0", 180, 45000),==,0);
    CHECK_CMP(count_cars("model 1", "maker 2", "driver 1", 80, 40000),==,0);
    racing_delete();
    TEST_PASSED;
}

TEST (driver_queries_random_3) {
    CHECK_CMP(racing_init("./tests/queries_random_3.data"),==,1058);
    CHECK_CMP(count_drivers(0, 0),==,50);
    CHECK_CMP(count_drivers(0, "team 9"),==,7);
    CHECK_CMP(count_drivers("driver 4", "team 3"),==,2);
    CHECK_CMP(count_drivers("driver 2", "team 0"),==,0);
    CHECK_CMP(count_drivers("driver 3", "team 9"),==,3);
    CHECK_CMP(count_drivers(0, "team 7"),==,5);
    CHECK_CMP(count_drivers("driver 0", "team 5"),==,0);
    CHECK_CMP(count_drivers("driver 4", "team 6"),==,0);
    CHECK_CMP(count_drivers("driver 0", "team 3"),==,1);
    CHECK_CMP(count_drivers(0, "team 3"),==,7);
    CHECK_CMP(count_drivers("driver 0", "team 8"),==,0);
    CHECK_CMP(count_drivers("driver 4", "team 4"),==,1);
    CHECK_CMP(count_drivers("driver 4", "team 9"),==,2);
    CHECK_CMP(count_drivers("driver 3", "team 6"),==,0);
    CHECK_CMP(count_drivers("driver 0", "team 4"),==,2);
    CHECK_CMP(count_drivers("driver 0", "team 2"),==,1);
    racing_delete();
    TEST_PASSED;
}

TEST (team_queries_random_3) {
    CHECK_CMP(racing_init("./tests/queries_random_3.data"),==,1058);
    CHECK_CMP(get_teams(),==,8);
    racing_delete();
    TEST_PASSED;
}



TEST (missing_fields) {
    CHECK_CMP(racing_init("./tests/queries_missing_fields.data"),==,9);
    CHECK_CMP(count_drivers(0, 0),==,4);
    CHECK_CMP(count_drivers("Ayrton Senna", 0),==,1);
    CHECK_CMP(count_drivers(0, "Ferrari"),==,1);
    CHECK_CMP(count_cars(0, 0, 0, 0, 0),==,4);
    CHECK_CMP(count_cars("250 GTO", 0, 0, 0, 0),==,2);
    CHECK_CMP(count_cars(0, "Ferrari", 0, 0, 0),==,2);
    CHECK_CMP(count_cars(0, 0, "Mario Andretti", 0, 0),==,1);
    CHECK_CMP(count_cars(0, 0, 0, 300, 0),==,3);
    racing_delete();
    TEST_PASSED;
}


MAIN_TEST_DRIVER (car_queries_1, driver_queries_1, team_queries_1,
    car_queries_random_1, driver_queries_random_1, team_queries_random_1,
    car_queries_random_2, driver_queries_random_2, team_queries_random_2,
    car_queries_random_3, driver_queries_random_3, team_queries_random_3,
    missing_fields);
