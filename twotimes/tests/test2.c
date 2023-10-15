#include "basic_testing.h"

extern int twotimes2(const char * begin, const char * end);
extern int twotimes(const char * s);

const char * z1 = "aa\0ab\0";
const char * z2 = "ab\0bab\0b";

TEST(zeros_aa_z_ab) {
    CHECK(twotimes(z1));
    TEST_PASSED;
}

TEST(zeros_aa_z_ab2) {
    CHECK(!twotimes2(z1,z1+6));
    TEST_PASSED;
}

TEST(zeros_ab_z_ab) {
    CHECK(!twotimes(z2));
    TEST_PASSED;
}

TEST(zeros_ab_z_ab2) {
    CHECK(twotimes2(z2,z2+8));
    TEST_PASSED;
}

MAIN_TEST_DRIVER(zeros_aa_z_ab, zeros_aa_z_ab2,
		 zeros_ab_z_ab, zeros_ab_z_ab2)
