#include <stdlib.h>
#include <stdio.h>

#include "basic_testing.h"

#include "../videos.h"

TEST (create_1000) {
    struct platform * p;
    p = create();
    CHECK (p != 0);

    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	int id = add_video (p, title, 10);
	CHECK_INT_CMP (id,>=,0);
    }
    destroy(p);
    TEST_PASSED;
}

TEST (create_1000_and_views) {
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
	CHECK(add_view (p, V[i], 20));
    }

    CHECK_INT_CMP (total_view_minutes (p),==,20000);
    CHECK_INT_CMP (total_full_views (p),==,1000);
    
    destroy(p);
    free(V);
    TEST_PASSED;
}

TEST (create_1000_and_later_views) {
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
	CHECK(add_view (p, V[i], 20));
    }

    CHECK_INT_CMP (total_view_minutes (p),==,20000);
    CHECK_INT_CMP (total_full_views (p),==,1000);
    
    destroy(p);
    free(V);
    TEST_PASSED;
}

TEST (create_10_and_1000_views) {
    struct platform * p;

    p = create();
    CHECK (p != 0);

    int * V = malloc(sizeof(int)*10);
    CHECK (V != 0);

    for (int i = 0; i < 10; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	V[i] = add_video (p, title, 10);
	CHECK_INT_CMP (V[i],>=,0);
    }

    for (int i = 0; i < 10; ++i) 
	for (int j = 0; j < 100; ++j) 
	    CHECK(add_view (p, V[i], 20));

    CHECK_INT_CMP (total_view_minutes (p),==,20000);
    CHECK_INT_CMP (total_full_views (p),==,1000);
    
    destroy(p);
    free(V);
    TEST_PASSED;
}

TEST (create_100_and_check_ids) {
    struct platform * p;

    p = create();
    CHECK (p != 0);

    int * V = malloc(sizeof(int)*100);
    CHECK (V != 0);

    for (int i = 0; i < 100; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	V[i] = add_video (p, title, 10);
	CHECK_INT_CMP (V[i],>=,0);
    }

    /* we check that all ids are different */
    for (int i = 0; i < 100; ++i) 
	for (int j = i + 1; j < 100; ++j)
	    CHECK_INT_CMP (V[i],!=,V[j]);

    destroy(p);
    free(V);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(create_1000,
		 create_1000_and_views,
		 create_1000_and_later_views,
		 create_10_and_1000_views);
		 
		 
