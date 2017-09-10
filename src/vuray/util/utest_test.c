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

    expect_that_m(1, "one is true");
    my_assert(utest_result == 2);

    expect_that_m(false, "A detailed message about this particular check.");
    my_assert(utest_result == 3);

    expect_that_m(1 < 0, "really?");
    my_assert(utest_result == 4);
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

    assert_that_m(true, "true is true");
    my_assert(utest_result == 2);
    my_assert(exit_called == 2);

    assert_that_m('a' == 'b', "something is wrong");
    my_assert(utest_result == 3);
    my_assert(exit_called == 3);

    assert_that_m(utest_result > exit_called, "not in sync");
    my_assert(utest_result == 4);
    my_assert(exit_called == 4);
}

static void test_expect_str_eq(void) {
    utest_result = 0;

    expect_str_eq(0, 0);
    my_assert(utest_result == 0);

    expect_str_eq("one", "one");
    my_assert(utest_result == 0);

    expect_str_eq("one", "two");
    my_assert(utest_result == 1);

    expect_str_eq(0, "one");
    my_assert(utest_result == 2);

    expect_str_eq("one", 0);
    my_assert(utest_result == 3);

    expect_str_eq_m("one", "one", "One and one");
    my_assert(utest_result == 3);

    expect_str_eq_m("one", "two", "One and two");
    my_assert(utest_result == 4);
}

static void test_assert_str_eq(void) {
    utest_result = 0;
    exit_called = 0;

    assert_str_eq(0, 0);
    my_assert(utest_result == 0);
    my_assert(exit_called == 0);

    assert_str_eq("one", "one");
    my_assert(utest_result == 0);
    my_assert(exit_called == 0);

    assert_str_eq("one", "two");
    my_assert(utest_result == 1);
    my_assert(exit_called == 1);

    assert_str_eq(0, "one");
    my_assert(utest_result == 2);
    my_assert(exit_called == 2);

    assert_str_eq("one", 0);
    my_assert(utest_result == 3);
    my_assert(exit_called == 3);

    assert_str_eq_m("one", "one", "One and one");
    my_assert(utest_result == 3);
    my_assert(exit_called == 3);

    assert_str_eq_m("one", "two", "One and two");
    my_assert(utest_result == 4);
    my_assert(exit_called == 4);
}

static void test_expect_near(void) {
    utest_result = 0;

    expect_near(0.f, 0.f, 0.01f);
    my_assert(utest_result == 0);

    expect_near_m(0.f, 0.001f, 0.01f, "Message");
    my_assert(utest_result == 0);

    expect_near(0.f, 0.01f, 0.01f);
    my_assert(utest_result == 0);

    expect_near(0.f, 0.1f, 0.01f);
    my_assert(utest_result == 1);

    expect_near_m(0.f, 1.f, 0.01f, "Zero and one");
    my_assert(utest_result == 2);
}

static void test_assert_near(void) {
    utest_result = 0;
    exit_called = 0;

    assert_near(0.f, 0.f, 0.01f);
    my_assert(utest_result == 0);
    my_assert(exit_called == 0);

    assert_near_m(0.001f, 0.f, 0.01f, "Message");
    my_assert(utest_result == 0);
    my_assert(exit_called == 0);

    assert_near(0.01f, 0.f, 0.01f);
    my_assert(utest_result == 0);
    my_assert(exit_called == 0);

    assert_near(0.1f, 0.f, 0.01f);
    my_assert(utest_result == 1);
    my_assert(exit_called == 1);

    assert_near_m(1.f, 0.f, 0.01f, "One and zero");
    my_assert(utest_result == 2);
    my_assert(exit_called == 2);
}

static void test_expect_float_eq(void) {
    utest_result = 0;

    expect_float_eq(1.2345f, 1.23456f);
    my_assert(utest_result == 0);

    expect_float_eq_m(-1.23456f, -1.2345f, "Works for negative floats too");
    my_assert(utest_result == 0);

    expect_float_eq(-0.00001f, 0.00001f);
    my_assert(utest_result == 0);

    expect_float_eq(-0.0001f, 0.0001f);
    my_assert(utest_result == 1);

    expect_float_eq_m(0.001f, -0.001f, "Too far away");
    my_assert(utest_result == 2);
}

static void test_assert_float_eq(void) {
    utest_result = 0;
    exit_called = 0;

    assert_float_eq(1.23456f, 1.23456f);
    my_assert(utest_result == 0);
    my_assert(exit_called == 0);

    assert_float_eq_m(-1.2345f, -1.23456f, "Works for negative floats too");
    my_assert(utest_result == 0);
    my_assert(exit_called == 0);

    assert_float_eq(-0.00001f, -0.00001f);
    my_assert(utest_result == 0);
    my_assert(exit_called == 0);

    assert_float_eq(0.0001f, -0.0001f);
    my_assert(utest_result == 1);
    my_assert(exit_called == 1);

    assert_float_eq_m(-0.001f, 0.001f, "The difference is too large");
    my_assert(utest_result == 2);
    my_assert(exit_called == 2);
}

int main(void) {
    test_expect_that();
    test_assert_that();

    test_expect_str_eq();
    test_assert_str_eq();

    test_expect_near();
    test_assert_near();

    test_expect_float_eq();
    test_assert_float_eq();
}
