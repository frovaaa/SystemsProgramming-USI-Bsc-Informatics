#include <string.h>

#include "basic_testing.h"

extern int line_to_args (char * argv[], int max_count, char * line);

TEST (two_words_one_space) {
    char buf[2000];
    char * argv[1000];
    strncpy(buf, "abc xyz", 2000);
    CHECK_INT_CMP(line_to_args(argv, 1000, buf),==,2);
    CHECK_STRING_CMP(argv[0],==,"abc");
    CHECK_STRING_CMP(argv[1],==,"xyz");
    TEST_PASSED;
}

TEST (two_words_punct_one_space) {
    char buf[2000];
    char * argv[1000];
    strncpy(buf, "abc! ..xyz-][{}]", 2000);
    CHECK_INT_CMP(line_to_args(argv, 1000, buf),==,2);
    CHECK_STRING_CMP(argv[0],==,"abc!");
    CHECK_STRING_CMP(argv[1],==,"..xyz-][{}]");
    TEST_PASSED;
}

TEST (two_words_with_space) {
    char buf[2000];
    char * argv[1000];
    strncpy(buf, " abc!    ..xyz-][{}]             ", 2000);
    CHECK_INT_CMP(line_to_args(argv, 1000, buf),==,2);
    CHECK_STRING_CMP(argv[0],==,"abc!");
    CHECK_STRING_CMP(argv[1],==,"..xyz-][{}]");
    TEST_PASSED;
}
TEST (ten_words) {
    char buf[2000];
    char * argv[1000];
    strncpy(buf, " one   two  three            four five  six seven eight nine   ten ", 2000);
    CHECK_INT_CMP(line_to_args(argv, 1000, buf),==,10);
    CHECK_STRING_CMP(argv[0],==,"one");
    CHECK_STRING_CMP(argv[1],==,"two");
    CHECK_STRING_CMP(argv[2],==,"three");
    CHECK_STRING_CMP(argv[3],==,"four");
    CHECK_STRING_CMP(argv[4],==,"five");
    CHECK_STRING_CMP(argv[5],==,"six");
    CHECK_STRING_CMP(argv[6],==,"seven");
    CHECK_STRING_CMP(argv[7],==,"eight");
    CHECK_STRING_CMP(argv[8],==,"nine");
    CHECK_STRING_CMP(argv[9],==,"ten");
    TEST_PASSED;
}

MAIN_TEST_DRIVER(two_words_one_space,
		 two_words_punct_one_space,
		 two_words_with_space,
		 ten_words,
		 two_words_one_space,
		 two_words_punct_one_space,
		 two_words_with_space,
		 ten_words);
		 
