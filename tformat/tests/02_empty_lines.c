#include "basic_testing.h"
#include "../tformat.h"

TEST (two_empty_lines) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf, "\n\n", 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,"\n\n");
    TEST_PASSED;
}

TEST (two_lines_with_spaces) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf, "    \n \n", 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,"\n\n");
    TEST_PASSED;
}

TEST (ten_lines_with_spaces) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf, "    \n \n\n \n\n\n              \n\n\n\n", 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,"\n\n\n\n\n\n\n\n\n\n");
    TEST_PASSED;
}

TEST (ten_lines_space_ends) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf, "    \n \n\n \n\n\n              \n\n\n\n ", 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,"\n\n\n\n\n\n\n\n\n\n");
    TEST_PASSED;
}

TEST (ten_lines_spaces_end) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf, "    \n \n\n \n\n\n              \n\n\n\n ", 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,"\n\n\n\n\n\n\n\n\n\n");
    TEST_PASSED;
}

TEST (ten_lines_spaces_end2) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf, "    \n \n\n \n\n\n  aaa            \n\n\n\n ", 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,"aaa\n");
    TEST_PASSED;
}

MAIN_TEST_DRIVER(two_empty_lines,
		 two_lines_with_spaces,
		 ten_lines_with_spaces,
		 ten_lines_space_ends,
		 ten_lines_spaces_end,
		 ten_lines_spaces_end2);
