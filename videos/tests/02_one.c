#include "basic_testing.h"

#include "../videos.h"

TEST (create_one) {
    struct platform * p;
    p = create();
    CHECK (p != 0);
    CHECK_INT_CMP (add_video (p, "T1", 10),>=,0);
    destroy(p);
    TEST_PASSED;
}

TEST (query_one_no_views) {
    struct platform * p;
    p = create();
    CHECK (p != 0);
    add_video (p, "T1", 10);
    CHECK_INT_CMP (total_view_minutes (p),==,0);
    CHECK_INT_CMP (total_full_views (p),==,0);
    destroy(p);
    TEST_PASSED;
}

TEST (add_one_view) {
    struct platform * p;
    p = create();
    CHECK (p != 0);
    int id = add_video (p, "T1", 10);
    CHECK_INT_CMP (id,>=,0);
    CHECK(add_view (p, id, 5));
    CHECK_INT_CMP (total_view_minutes (p),==,5);
    CHECK_INT_CMP (total_full_views (p),==,0);
    destroy(p);
    TEST_PASSED;
}

TEST (add_one_full_view) {
    struct platform * p;
    p = create();
    CHECK (p != 0);
    int id = add_video (p, "T1", 10);
    CHECK_INT_CMP (id,>=,0);
    CHECK(add_view (p, id, 10));
    CHECK_INT_CMP (total_view_minutes (p),==,10);
    CHECK_INT_CMP (total_full_views (p),==,1);
    destroy(p);
    TEST_PASSED;
}

TEST (add_one_full_long_view) {
    struct platform * p;
    p = create();
    CHECK (p != 0);
    int id = add_video (p, "T1", 10);
    CHECK_INT_CMP (id,>=,0);
    /* we add a view of 20 minutes for a video of 10 minutes, which
       must count as a single full view.  */
    CHECK(add_view (p, id, 20));
    CHECK_INT_CMP (total_view_minutes (p),==,20);
    CHECK_INT_CMP (total_full_views (p),==,1);
    destroy(p);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(create_one,
		 query_one_no_views,
		 add_one_view,
		 add_one_full_view,
		 add_one_full_long_view);
		 
