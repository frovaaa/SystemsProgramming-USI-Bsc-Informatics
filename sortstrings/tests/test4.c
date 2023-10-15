#include <string.h>

#include "basic_testing.h"

extern void sort_strings(const char * input, char * output, unsigned int n);

const char * S_sorted = "cfreq\0concatenate\0concatenate/tests\0coursesdb\0deletedigits\0deletedigits/tests\0findstrings\0flipline\0flipline/tests\0flipstream\0linkedlist\0redactdigits\0redactdigits/tests\0topcolor\0topcolor/tests\0volumes\0volumes/tests\0wordcount\0wordcount/tests";

const char * S = "concatenate/tests\0concatenate\0linkedlist\0topcolor/tests\0topcolor\0flipstream\0deletedigits/tests\0deletedigits\0coursesdb\0volumes/tests\0volumes\0cfreq\0wordcount/tests\0wordcount\0flipline/tests\0flipline\0findstrings\0redactdigits/tests\0redactdigits";


TEST(ciao_ciao) {
    char buf[1000];
    sort_strings("ciao\0cia", buf, 2);
    CHECK(memcmp(buf, "cia\0ciao", 9) == 0);
    TEST_PASSED;
}

TEST(long_list) {
    char buf[1000];
    sort_strings(S, buf, 19);
    CHECK(memcmp(buf, S_sorted, 239) == 0);
    TEST_PASSED;
}

TEST(reverse_first_long) {
    char buf[1000];
    sort_strings("zaaaaaaaaaaaaaaa\0c\0\b\0\0", buf, 2);
    CHECK(memcmp(buf, "\0b\0c\0zaaaaaaaaaaaaaaa\0", 22) == 0);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(ciao_ciao, long_list)
