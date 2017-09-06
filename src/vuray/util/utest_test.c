/*
 * utest_test.c
 * Unit tests for utest.h file.
 *
 * Author: hm2code
 */

// Redefine utest_exit so we can test assert_...() macros.
static int exit_called = 0;

static void my_exit(void) {
    ++exit_called;
}

#define utest_exit my_exit
#include "utest.h"

static inline void my_assert(bool cond) {
    if (!cond) {
        exit(-1);
    }
}

static void test_expect_that(void) {
    utest_result = 0; 

    expect_that(1 == 1);
    my_assert(utest_result == 0);

    const int a = 1;
    const int b = 2;

    expect_that(a == b);
    my_assert(utest_result == 1);

    expect_that(~(~(0)));
    my_assert(utest_result == 2);

    utest_result = 0; 

    expect_that_m(1, "one is true");
    my_assert(utest_result == 0);

    expect_that_m(false, "A detailed message about this particular check.");
    my_assert(utest_result == 1);

    expect_that_m(1 < 0, "really?");
    my_assert(utest_result == 2);
}

static void test_assert_that(void) {
    utest_result = 0; 
    exit_called = 0;

    assert_that(1 == 1);
    my_assert(utest_result == 0);
    my_assert(exit_called == 0);

    assert_that(2 > 1 && 1 == 0);
    my_assert(utest_result == 1);
    my_assert(exit_called == 1);

    assert_that(0x00000000);
    my_assert(utest_result == 2);
    my_assert(exit_called == 2);

    utest_result = 0; 
    exit_called = 0; 

    assert_that_m(true, "true is true");
    my_assert(utest_result == 0);
    my_assert(exit_called == 0);

    assert_that_m("foo" == "bar", "something is wrong");
    my_assert(utest_result == 1);
    my_assert(exit_called == 1);

    assert_that_m(utest_result > exit_called, "not in sync");
    my_assert(utest_result == 2);
    my_assert(exit_called == 2);
}

int main(void) {
    test_expect_that();
    test_assert_that();
}
