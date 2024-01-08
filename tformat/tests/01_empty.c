#include "basic_testing.h"
#include "../tformat.h"

TEST (empty) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    buf[0] = 0;
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,"");
    TEST_PASSED;
}

TEST (just_one_space) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf, " ", 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,"");
    TEST_PASSED;
}

TEST (just_two_spaces) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf, "  ", 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,"");
    TEST_PASSED;
}

TEST (various_spaces) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf, " \t\r\v   \t \r ", 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,"");
    TEST_PASSED;
}

MAIN_TEST_DRIVER(empty, just_two_spaces, various_spaces);
