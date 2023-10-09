#include <string.h>

#include "basic_testing.h"

extern int line_to_args (char * argv[], int max_count, char * line);

TEST (ten_words_max_11) {
    char buf[2000];
    char * argv[11];
    strncpy(buf, " one   two  three            four five  six seven eight nine   ten ", 2000);
    CHECK_INT_CMP(line_to_args(argv, 11, buf),==,10);
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

TEST (ten_words_max_10) {
    char buf[2000];
    char * argv[10];
    strncpy(buf, " one   two  three            four five  six seven eight nine   ten ", 2000);
    CHECK_INT_CMP(line_to_args(argv, 10, buf),==,10);
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

TEST (ten_words_max_9) {
    char buf[2000];
    char * argv[9];
    strncpy(buf, " one   two  three            four five  six seven eight nine   ten ", 2000);
    CHECK_INT_CMP(line_to_args(argv, 9, buf),==,9);
    CHECK_STRING_CMP(argv[0],==,"one");
    CHECK_STRING_CMP(argv[1],==,"two");
    CHECK_STRING_CMP(argv[2],==,"three");
    CHECK_STRING_CMP(argv[3],==,"four");
    CHECK_STRING_CMP(argv[4],==,"five");
    CHECK_STRING_CMP(argv[5],==,"six");
    CHECK_STRING_CMP(argv[6],==,"seven");
    CHECK_STRING_CMP(argv[7],==,"eight");
    CHECK_STRING_CMP(argv[8],==,"nine");
    TEST_PASSED;
}

MAIN_TEST_DRIVER(ten_words_max_11,
		 ten_words_max_10,
		 ten_words_max_9);
		 
