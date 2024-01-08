#include "basic_testing.h"

#include "../videos.h"

TEST (create_two) {
    struct platform * p;
    p = create();
    CHECK (p != 0);
    CHECK_INT_CMP (add_video (p, "T1", 10),>=,0);
    CHECK_INT_CMP (add_video (p, "T2", 10),>=,0);
    destroy(p);
    TEST_PASSED;
}

TEST (query_no_views) {
    struct platform * p;
    p = create();
    CHECK (p != 0);

    int id1 = add_video (p, "T1", 10);
    CHECK_INT_CMP (id1,>=,0);
    int id2 = add_video (p, "T2", 30);
    CHECK_INT_CMP (id2,>=,0);

    int m = total_view_minutes (p);
    CHECK_INT_CMP(m,==,0);
    CHECK_INT_CMP (total_full_views (p),==,0);
    destroy(p);
    TEST_PASSED;
}

TEST (add_one_view) {
    struct platform * p;
    p = create();
    CHECK (p != 0);

    int id1 = add_video (p, "T1", 10);
    CHECK_INT_CMP (id1,>=,0);
    int id2 = add_video (p, "T2", 30);
    CHECK_INT_CMP (id2,>=,0);

    CHECK(add_view (p, id1, 5));

    CHECK_INT_CMP (total_view_minutes (p),==,5);
    CHECK_INT_CMP (total_full_views (p),==,0);
    destroy(p);
    TEST_PASSED;
}

TEST (add_one_full_view) {
    struct platform * p;
    p = create();
    CHECK (p != 0);

    int id1 = add_video (p, "T1", 10);
    CHECK_INT_CMP (id1,>=,0);
    int id2 = add_video (p, "T2", 30);
    CHECK_INT_CMP (id2,>=,0);

    CHECK(add_view (p, id1, 15));

    CHECK_INT_CMP (total_view_minutes (p),==,15);
    CHECK_INT_CMP (total_full_views (p),==,1);
    destroy(p);
    TEST_PASSED;
}

TEST (add_two_full_views) {
    struct platform * p;
    p = create();
    CHECK (p != 0);

    int id1 = add_video (p, "T1", 10);
    CHECK_INT_CMP (id1,>=,0);
    int id2 = add_video (p, "T2", 30);
    CHECK_INT_CMP (id2,>=,0);

    CHECK(add_view (p, id1, 15));
    CHECK(add_view (p, id2, 30));

    CHECK_INT_CMP (total_view_minutes (p),==,45);
    CHECK_INT_CMP (total_full_views (p),==,2);
    destroy(p);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(create_two,
		 query_no_views,
		 add_one_view,
		 add_one_full_view,
		 add_two_full_views);
		 
