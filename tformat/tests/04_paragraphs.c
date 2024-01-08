#include "basic_testing.h"
#include "../tformat.h"

TEST (one_word) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf,
	     "precipitevolissimevolmente\n"
	     , 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, "precipitevolissimevolmente\n");
    TEST_PASSED;
}

TEST (one_word_spaces_before) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf,
	     " precipitevolissimevolmente\n"
	     , 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, "precipitevolissimevolmente\n");
    TEST_PASSED;
}

TEST (one_word_spaces_after) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf,
	     "precipitevolissimevolmente \n"
	     , 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, "precipitevolissimevolmente\n");
    TEST_PASSED;
}

TEST (empty_lines_before) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf,
	     "\nprecipitevolissimevolmente\n\n"
	     , 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, "precipitevolissimevolmente\n");
    TEST_PASSED;
}

TEST (empty_lines_plus_spaces) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf,
	     "\n   precipitevolissimevolmente\n   \n"
	     , 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, "precipitevolissimevolmente\n");
    TEST_PASSED;
}

TEST (one_word_spaces_both) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf,
	     " precipitevolissimevolmente \n"
	     , 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, "precipitevolissimevolmente\n");
    TEST_PASSED;
}

TEST (one_letter_words) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf, "a\n" " b\n" "c \n", 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, "a\n" "b\n" "c\n");
    TEST_PASSED;
}

TEST (one_letter_words_seq) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf,
	     " a \n"
	     "   p r e c i p i t e v o l i s s i m e v o l m e n t e  \n"
	     , 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,
		     "a\n"
		     "p r e c i p i t e v o l i s s i m e v o l m e n t e\n");
    TEST_PASSED;
}

TEST (one_letter_words_spaces) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf,
	     " a \n"
	     "   p r e c i p i t e     v o l i s s i m e v o      l m e n t e  \n"
	     , 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,
		     "a\n"
		     "p r e c i p i t e v o l i s s i m e v o l m e n t e\n");
    TEST_PASSED;
}

TEST (no_extra_spaces) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf,
	     "abc defghijklm 1234\n"
	     "defghijklm 1234 abc\n"
	     , 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, "abc defghijklm 1234\n" "defghijklm 1234 abc\n");
    TEST_PASSED;
}

TEST (extra_spaces) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf,
	     "abc    defghijklm     1234\n"
	     "defghijklm  1234  abc     \n"
	     , 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, "abc defghijklm 1234\n" "defghijklm 1234 abc\n");
    TEST_PASSED;
}

static const char * LT1 = 
    "Except for bit fields, objects are composed of contiguous sequences of one or more bytes, each consisting of CHAR_BIT bits, and can be copied with memcpy into an object of type unsigned char[n], where n is the size of the object. The contents of the resulting array are known as object representation.\n"
    "\n"
    "If two objects have the same object representation, they compare equal (except if they are floating-point NaNs). The opposite is not true: two objects that compare equal may have different object representations because not every bit of the object representation needs to participate in the value. Such bits may be used for padding to satisfy alignment requirement, for parity checks, to indicate trap representations, etc.\n";


TEST (long_text_no_spaces) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf, LT1, 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, LT1);
    TEST_PASSED;
}

static const char * LT1_spaces = 
    "Except for bit fields, objects are composed of contiguous sequences of one or more bytes, each consisting of CHAR_BIT bits, and can be copied with memcpy into an object of type unsigned char[n],  where n is the size of the object. The contents of the resulting array are known as object representation. \n"
    "\n"
    "If two objects have the same object representation, they compare equal (except if they are floating-point NaNs). The opposite is not true: two objects that compare equal may have different object representations because not every bit of the object representation needs to participate in the value.  Such bits may be used for padding to satisfy alignment requirement, for parity checks, to indicate trap representations, etc. \n";

TEST (long_text_spaces) {
    struct t_opts opts;
    opts.format_paragraphs = 1;
    opts.format_punctuation = 0;
    opts.max_line_len = 0;
    char buf[1000];
    strncpy (buf, LT1_spaces, 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, LT1);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(one_word,
		 one_word_spaces_before,
		 one_word_spaces_after,
		 empty_lines_before,
		 empty_lines_plus_spaces,
		 one_word_spaces_both,
		 one_letter_words,
		 one_letter_words_seq,
		 one_letter_words_spaces,
		 no_extra_spaces,
		 extra_spaces,
		 long_text_no_spaces,
		 long_text_spaces);
