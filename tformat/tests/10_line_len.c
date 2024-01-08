#include "basic_testing.h"
#include "../tformat.h"

#if WITH_OPT_TESTS
TEST (empty) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 20;
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
    opts.max_line_len = 20;
    char buf[1000];
    strncpy (buf, "    \n \n", 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==,"\n\n");
    TEST_PASSED;
}

TEST (less_than_max) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 20;
    char buf[1000];
    strncpy (buf,
	     "abc defghijklm 1234\n"
	     "defghijklm 1234 abc\n"
	     , 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, "abc defghijklm 1234\n" "defghijklm 1234 abc\n");
    TEST_PASSED;
}

TEST (less_than_max_extra_spaces) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 20;
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
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 50;
    char buf[1000];
    strncpy (buf, LT1, 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, 
		     "Except for bit fields, objects are composed of\n"
		     "contiguous sequences of one or more bytes, each\n"
		     "consisting of CHAR_BIT bits, and can be copied\n"
		     "with memcpy into an object of type unsigned\n"
		     "char[n], where n is the size of the object. The\n"
		     "contents of the resulting array are known as\n"
		     "object representation.\n\n"
		     
		     "If two objects have the same object\n"
		     "representation, they compare equal (except if they\n"
		     "are floating-point NaNs). The opposite is not\n"
		     "true: two objects that compare equal may have\n"
		     "different object representations because not every\n"
		     "bit of the object representation needs to\n"
		     "participate in the value. Such bits may be used\n"
		     "for padding to satisfy alignment requirement, for\n"
		     "parity checks, to indicate trap representations,\n"
		     "etc.\n");
    TEST_PASSED;
}

static const char * LT1_spaces = 
    "Except for bit fields, objects are composed of contiguous sequences of one or more bytes, each consisting of CHAR_BIT bits, and can be copied with memcpy into an object of type unsigned char[n],  where n is the size of the object. The contents of the resulting array are known as object representation. \n"
    "\n"
    "If two objects have the same object representation, they compare equal (except if they are floating-point NaNs). The opposite is not true: two objects that compare equal may have different object representations because not every bit of the object representation needs to participate in the value.  Such bits may be used for padding to satisfy alignment requirement, for parity checks, to indicate trap representations, etc. \n";

TEST (long_text_spaces) {
    struct t_opts opts;
    opts.format_paragraphs = 0;
    opts.format_punctuation = 0;
    opts.max_line_len = 50;
    char buf[1000];
    strncpy (buf, LT1_spaces, 1000);
    t_format(buf, &opts);
    CHECK_STRING_CMP(buf,==, 
		     "Except for bit fields, objects are composed of\n"
		     "contiguous sequences of one or more bytes, each\n"
		     "consisting of CHAR_BIT bits, and can be copied\n"
		     "with memcpy into an object of type unsigned\n"
		     "char[n], where n is the size of the object. The\n"
		     "contents of the resulting array are known as\n"
		     "object representation.\n\n"
		     
		     "If two objects have the same object\n"
		     "representation, they compare equal (except if they\n"
		     "are floating-point NaNs). The opposite is not\n"
		     "true: two objects that compare equal may have\n"
		     "different object representations because not every\n"
		     "bit of the object representation needs to\n"
		     "participate in the value. Such bits may be used\n"
		     "for padding to satisfy alignment requirement, for\n"
		     "parity checks, to indicate trap representations,\n"
		     "etc.\n");
    TEST_PASSED;
}

MAIN_TEST_DRIVER(empty,
		 two_lines_with_spaces,
		 less_than_max,
		 less_than_max_extra_spaces,
		 long_text_no_spaces,
		 long_text_spaces);
#else
TEST (empty) {
    TEST_PASSED;
}

MAIN_TEST_DRIVER(empty)
#endif
