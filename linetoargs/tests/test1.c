#include <string.h>

#include "basic_testing.h"

extern int line_to_args (char * argv[], int max_count, char * line);

TEST (only_spaces) {
    char buf[2000];
    char * argv[1000];
    for (int i = 0; i < 1999; ++i)
	buf[i] = ' ';
    buf[1999] = 0;
    CHECK_INT_CMP(line_to_args(argv, 1000, buf),==,0);
    TEST_PASSED;
}

TEST (one_word_no_spaces) {
    char buf[2000];
    char * argv[1000];
    strncpy(buf, "abracadabra!", 2000);
    CHECK_INT_CMP(line_to_args(argv, 1000, buf),==,1);
    CHECK_STRING_CMP(argv[0],==,"abracadabra!");
    TEST_PASSED;
}

TEST (one_word_spaces_before) {
    char buf[2000];
    char * argv[1000];
    strncpy(buf, " \n\n abracadabra!", 2000);
    CHECK_INT_CMP(line_to_args(argv, 1000, buf),==,1);
    CHECK_STRING_CMP(argv[0],==,"abracadabra!");
    TEST_PASSED;
}

TEST (one_word_spaces_after) {
    char buf[2000];
    char * argv[1000];
    strncpy(buf, "abracadabra!        ", 2000);
    CHECK_INT_CMP(line_to_args(argv, 1000, buf),==,1);
    CHECK_STRING_CMP(argv[0],==,"abracadabra!");
    TEST_PASSED;
}

TEST (one_word_spaces_before_and_after) {
    char buf[2000];
    char * argv[1000];
    strncpy(buf, " \n\n abracadabra!\n", 2000);
    CHECK_INT_CMP(line_to_args(argv, 1000, buf),==,1);
    CHECK_STRING_CMP(argv[0],==,"abracadabra!");
    TEST_PASSED;
}

MAIN_TEST_DRIVER(only_spaces,
		 one_word_no_spaces,
		 one_word_spaces_before,
		 one_word_spaces_after,
		 one_word_spaces_before_and_after);

