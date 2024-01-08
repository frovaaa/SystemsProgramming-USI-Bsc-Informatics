#include "basic_testing.h"

#include "../videos.h"

TEST (create_delete_empty) {
    struct platform * p;
    p = create();
    CHECK (p != 0);
    destroy(p);
    TEST_PASSED;
}

TEST (query_empty_minutes) {
    struct platform * p;
    p = create();
    CHECK (p != 0);
    CHECK_INT_CMP (total_view_minutes (p),==,0);
    CHECK_INT_CMP (total_full_views (p),==,0);
    destroy(p);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(create_delete_empty, query_empty_minutes);
