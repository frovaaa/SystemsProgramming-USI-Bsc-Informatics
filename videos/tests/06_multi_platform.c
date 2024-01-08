#include <stdlib.h>
#include <stdio.h>

#include "basic_testing.h"

#include "../videos.h"

TEST (create_p1_p2) {
    struct platform * p1;
    struct platform * p2;

    p1 = create();
    CHECK (p1 != 0);

    p2 = create();
    CHECK (p2 != 0);

    destroy(p1);
    destroy(p2);
    TEST_PASSED;
}

TEST (create_p1_p2_many) {
    struct platform * p1;
    struct platform * p2;

    /* we create TWO platform objects */
    p1 = create();
    CHECK (p1 != 0);

    p2 = create();
    CHECK (p2 != 0);

    int id;

    /* we then add 1000 videos with titles "title 0", "title 1", "title 0", etc. */
    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	id = add_video (p1, title, 10);
	/* add_video must return a non-negative id; the result can be
	   negative, but only if the procedure fails due to memory
	   exhaustion*/
	CHECK_INT_CMP (id,>=,0);
	/* we then add a view for each video.  20 minutes for a video
	   of 10 minutes (see add_video above) means that this view
	   counts as a full view */
	CHECK(add_view (p1, id, 20));
    }

    /* we check p1 */
    CHECK_INT_CMP (total_view_minutes (p1),==,20000);
    CHECK_INT_CMP (total_full_views (p1),==,1000);
    
    /* p2 is instead empty */
    CHECK_INT_CMP (total_view_minutes (p2),==,0);
    CHECK_INT_CMP (total_full_views (p2),==,0);
    
    for (int i = 0; i < 100; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	id = add_video (p2, title, 10);
	CHECK_INT_CMP (id,>=,0);
	CHECK(add_view (p2, id, 20));
    }

    /* we check p1, which hasn't changed */
    CHECK_INT_CMP (total_view_minutes (p1),==,20000);
    CHECK_INT_CMP (total_full_views (p1),==,1000);
    
    /* p2 is instead not not empty */
    CHECK_INT_CMP (total_view_minutes (p2),==,2000);
    CHECK_INT_CMP (total_full_views (p2),==,100);
    
    clear(p1);

    /* we check p1, which should be empty */
    CHECK_INT_CMP (total_view_minutes (p1),==,0);
    CHECK_INT_CMP (total_full_views (p1),==,0);
    
    /* p2 is instead not empty */
    CHECK_INT_CMP (total_view_minutes (p2),==,2000);
    CHECK_INT_CMP (total_full_views (p2),==,100);
    
    destroy(p1);
    destroy(p2);
    TEST_PASSED;
}

TEST (create_p1_p2_many_titles) {
    struct platform * p1;
    struct platform * p2;

    p1 = create();
    CHECK (p1 != 0);

    p2 = create();
    CHECK (p2 != 0);

    int * V1 = malloc(sizeof(int)*1000);
    int * V2 = malloc(sizeof(int)*1000);
    CHECK (V1 != 0);
    CHECK (V2 != 0);

    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	V1[i] = add_video (p1, title, 10);
	CHECK_INT_CMP (V1[i],>=,0);
    }

    /* we check p1 */
    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	CHECK_INT_CMP (video_by_title (p1, title),==,V1[i]);
    }
    
    /* p2 is instead empty */
    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	CHECK_INT_CMP (video_by_title (p2, title),==,-1);
    }
    
    /* we add 100 videos to p2 */
    for (int i = 0; i < 100; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	V2[i] = add_video (p2, title, 10);
	CHECK_INT_CMP (V2[i],>=,0);
    }

    /* we check p1 */
    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	CHECK_INT_CMP (video_by_title (p1, title),==,V1[i]);
    }
    
    /* we check p2, which now has some titles */
    for (int i = 0; i < 100; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	CHECK_INT_CMP (video_by_title (p2, title),==,V2[i]);
    }
    
    for (int i = 100; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	CHECK_INT_CMP (video_by_title (p2, title),==,-1);
    }
    
    clear(p1);

    /* we check p1, which should now be empty */
    for (int i = 0; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	CHECK_INT_CMP (video_by_title (p1, title),==,-1);
    }
    
    /* we check p2, which now has some titles */
    for (int i = 0; i < 100; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	CHECK_INT_CMP (video_by_title (p2, title),==,V2[i]);
    }
    
    for (int i = 100; i < 1000; ++i) {
	char title[100];
	sprintf(title, "title %d", i);
	CHECK_INT_CMP (video_by_title (p2, title),==,-1);
    }
    
    destroy(p1);
    destroy(p2);
    free(V1);
    free(V2);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(create_p1_p2,
		 create_p1_p2_many,
		 create_p1_p2_many_titles);

