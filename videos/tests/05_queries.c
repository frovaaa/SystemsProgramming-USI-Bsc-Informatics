#include <stdlib.h>
#include <stdio.h>

#include "basic_testing.h"

#include "../videos.h"

TEST (create_1000_and_views) {
    struct platform * p;

    p = create();
    CHECK (p != 0);

    int id;

    for (int i = 0; i < 500; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	id = add_video (p, title, 10);
	CHECK_INT_CMP (id,>=,0);
	CHECK(add_view (p, id, 20));
    }

    CHECK_INT_CMP (total_view_minutes (p),==,10000);
    CHECK_INT_CMP (total_full_views (p),==,500);
    
    for (int i = 500; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	id = add_video (p, title, 10);
	CHECK_INT_CMP (id,>=,0);
	CHECK(add_view (p, id, 20));
    }

    CHECK_INT_CMP (total_view_minutes (p),==,20000);
    CHECK_INT_CMP (total_full_views (p),==,1000);
    
    destroy(p);
    TEST_PASSED;
}

TEST (create_1000_and_views_non_full) {
    struct platform * p;

    p = create();
    CHECK (p != 0);

    int id;

    for (int i = 0; i < 500; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	id = add_video (p, title, 10);
	CHECK_INT_CMP (id,>=,0);
	CHECK(add_view (p, id, 9));
    }

    CHECK_INT_CMP (total_view_minutes (p),==,4500);
    CHECK_INT_CMP (total_full_views (p),==,0);
    
    for (int i = 500; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	id = add_video (p, title, 10);
	CHECK_INT_CMP (id,>=,0);
	CHECK(add_view (p, id, 20));
    }

    CHECK_INT_CMP (total_view_minutes (p),==,14500);
    CHECK_INT_CMP (total_full_views (p),==,500);
    
    destroy(p);
    TEST_PASSED;
}

TEST (create_1000_and_views_clear) {
    struct platform * p;

    p = create();
    CHECK (p != 0);

    int id;

    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	id = add_video (p, title, 10);
	CHECK_INT_CMP (id,>=,0);
	CHECK(add_view (p, id, 20));
    }

    CHECK_INT_CMP (total_view_minutes (p),==,20000);
    CHECK_INT_CMP (total_full_views (p),==,1000);
    
    clear(p);

    CHECK_INT_CMP (total_view_minutes (p),==,0);
    CHECK_INT_CMP (total_full_views (p),==,0);

    for (int i = 0; i < 100; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	id = add_video (p, title, 10);
	CHECK_INT_CMP (id,>=,0);
	CHECK(add_view (p, id, 20));
    }

    CHECK_INT_CMP (total_view_minutes (p),==,2000);
    CHECK_INT_CMP (total_full_views (p),==,100);
    
    destroy(p);
    TEST_PASSED;
}

TEST (create_1000_and_ids_clear) {
    struct platform * p;

    p = create();
    CHECK (p != 0);

    int * V = malloc(sizeof(int)*1000);
    CHECK (V != 0);

    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	V[i] = add_video (p, title, 10);
	CHECK_INT_CMP (V[i],>=,0);
    }

    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	CHECK_INT_CMP (video_by_title (p, title),==,V[i]);
    }

    clear(p);

    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	CHECK_INT_CMP (video_by_title (p, title),==,-1);
    }

    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	V[i] = add_video (p, title, 10);
	CHECK_INT_CMP (V[i],>=,0);
    }

    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	CHECK_INT_CMP (video_by_title (p, title),==,V[i]);
    }

    destroy(p);
    free(V);
    TEST_PASSED;
}

TEST (bad_ids) {
    struct platform * p;

    p = create();
    CHECK (p != 0);

    int id;
    int bad_id = 0;

    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	id = add_video (p, title, 10);
	CHECK_INT_CMP (id,>=,0);
	CHECK(add_view (p, id, 20));
	if (bad_id <= id)
	    bad_id = id + 1;
    	CHECK(!add_view (p, bad_id, 20));
    }

    CHECK_INT_CMP (total_view_minutes (p),==,20000);
    CHECK_INT_CMP (total_full_views (p),==,1000);
    
    destroy(p);
    TEST_PASSED;
}

TEST (bad_ids2) {
    struct platform * p;

    p = create();
    CHECK (p != 0);

    int id;

    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	id = add_video (p, title, 10);
	CHECK_INT_CMP (id,>=,0);
    }

    for (int i = 1000; i < 2000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	CHECK_INT_CMP (video_by_title (p, title),==,-1);
    }

    destroy(p);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(create_1000_and_views,
		 create_1000_and_views_non_full,
		 create_1000_and_views_clear,
		 create_1000_and_ids_clear,
		 bad_ids,
		 bad_ids2);

