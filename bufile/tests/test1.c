#include <string.h>

#include "basic_testing.h"

#include "../bufile.h"

TEST(init_eof) {
    char buf[1000];
    char s[1000];
    buf[0] = '\n';
    BUFILE * f = bufopen(buf, buf);
    CHECK(f != 0);
    CHECK(bufgets(s, 10, f) == 0);
    bufclose(f);
    TEST_PASSED;
}

TEST(single_line) {
    char buf[1000];
    char s[1000];
    buf[0] = '\n';
    BUFILE * f = bufopen(buf, buf + 1000);
    CHECK(f != 0);
    CHECK(bufgets(s, 10, f) != 0);
    CHECK_STRING_CMP(s,==,"\n");
    bufclose(f);
    TEST_PASSED;
}

TEST(single_line_then_eof) {
    // char buf[1000];
    // char s[1000];
    // buf[0] = '\n';
    // BUFILE * f = bufopen(buf, buf + 1);
    // CHECK(f != 0);
    // CHECK(bufgets(s, 10, f) != 0);
    // CHECK(bufgets(s, 10, f) == 0);
    // bufclose(f);
    TEST_PASSED;
}

TEST(four_lines) {
    char buf[1000];
    char s[1000];
    strcpy(buf, "abc\n123\n55555\n666666\n");
    
    BUFILE * f = bufopen(buf, buf + 1000);
    CHECK(bufgets(s, 10, f) != 0);
    CHECK_STRING_CMP(s,==,"abc\n");
    CHECK(bufgets(s, 10, f) != 0);
    CHECK_STRING_CMP(s,==,"123\n");
    CHECK(bufgets(s, 10, f) != 0);
    CHECK_STRING_CMP(s,==,"55555\n");
    CHECK(bufgets(s, 10, f) != 0);
    CHECK_STRING_CMP(s,==,"666666\n");
    bufclose(f);
    TEST_PASSED;
}

TEST(four_lines_with_limits) {
    char buf[1000];
    char s[1000];
    strcpy(buf, "abc\n123\n55555\n666666\n");
    
    BUFILE * f = bufopen(buf, buf + 1000);
    CHECK(bufgets(s, 5, f) != 0);
    CHECK_STRING_CMP(s,==,"abc\n");
    CHECK(bufgets(s, 4, f) != 0);
    CHECK_STRING_CMP(s,==,"123");
    CHECK(bufgets(s, 5, f) != 0);
    CHECK_STRING_CMP(s,==,"\n");
    CHECK(bufgets(s, 5, f) != 0);
    CHECK_STRING_CMP(s,==,"5555");
    CHECK(bufgets(s, 5, f) != 0);
    CHECK_STRING_CMP(s,==,"5\n");
    CHECK(bufgets(s, 2, f) != 0);
    CHECK_STRING_CMP(s,==,"6");
    CHECK(bufgets(s, 3, f) != 0);
    CHECK_STRING_CMP(s,==,"66");
    CHECK(bufgets(s, 10, f) != 0);
    CHECK_STRING_CMP(s,==,"666\n");
    bufclose(f);
    TEST_PASSED;
}

TEST(four_empty_lines) {
    char buf[1000];
    char s[1000];
    strcpy(buf, "\n\n\n\n");
    
    BUFILE * f = bufopen(buf, buf + 4);
    CHECK(bufgets(s, 1, f) != 0);
    CHECK_STRING_CMP(s,==,"");
    CHECK(bufgets(s, 2, f) != 0);
    CHECK_STRING_CMP(s,==,"\n");
    CHECK(bufgets(s, 2, f) != 0);
    CHECK_STRING_CMP(s,==,"\n");
    CHECK(bufgets(s, 3, f) != 0);
    CHECK_STRING_CMP(s,==,"\n");
    CHECK(bufgets(s, 4, f) != 0);
    CHECK_STRING_CMP(s,==,"\n");
    CHECK(bufgets(s, 10, f) == 0);
    bufclose(f);
    TEST_PASSED;
}

TEST(long_binary) {
    char buf[1000];
    char s[1000];
    /* fill the buffer with rotating values except newlines */
    for (int i = 0; i < 1000; ++i) {
	buf[i] = i & 0xff;
	if (buf[i] == '\n')
	    buf[i] = 0;
    }
    
    BUFILE * f = bufopen(buf, buf + 1000);
    CHECK(bufgets(s, 1000, f) != 0);
    CHECK(memcmp(buf, s, 999) == 0);
    buf[999] = 0;
    CHECK(memcmp(buf, s, 1000) == 0);
    bufclose(f);
    TEST_PASSED;
}

MAIN_TEST_DRIVER(init_eof, single_line,
		 single_line_then_eof,
		 four_lines,
		 four_lines_with_limits,
		 four_empty_lines,
		 long_binary)
