/**
 * \file    utest.h
 * \brief   A collection of utilities for unit testing.
 *
 * A unit test case is a single module executable that returns 0 if all unit
 * tests passed. A build system, such as CMake (CTest), can run such
 * executables as part of the build process and report the overall result.
 *
 * The framework keeps track of the number of failed assertions. This number
 * should be returned from `main()` using \ref utest_exit macro:
 *
 * ```c
 * int main(void) {
 *     ...
 *     utest_exit();
 * }
 * ```
 *
 * There are two classes of condition checking macros (assertions):
 * - `expect_...()` - non-fatal assertions that print diagnostics, record the
 *   test failure, and continue execution if the assert condition failed.
 * - `assert_...()` - fatal assertions that print diagnostics, record the test
 *   failure, and exit the test case by calling \ref utest_exit macro.
 *
 * Example:
 *
 * ```c
 * static void test_expected_that(void) {
 *     const int a = 1;
 *     const int b = 2;
 *
 *     expect_that(a == b);
 * }
 * ```
 * Output:
 * ```
 * Assertion failed: a == b
 * at utest_test.c:35: test_expected_that
 * ```
 * 
 * The diagnostic message is printed into `stderr` by default. This can be
 * overriden by defining \ref utest_out macro before including this file.
 *
 * \author  hm2code
 */
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Contains the number of failed assertions.
static int utest_result = 0;

#ifndef utest_exit
/**
 * The function to be called if `assert_...()` assertion failed.
 * Defined as `exit(utest_result)` by default (`utest_result` contains the
 * number of failed assertions).
 */
#define utest_exit() exit(utest_result)
#endif // utest_exit

#ifndef utest_out
/**
 * The `FILE*` to be used for printing diagnostic messages.
 * Defined as `stderr` by default.
 */
#define utest_out stderr
#endif // utest_out

/** \cond */
#define UTEST_MSG_START "Assertion failed: %s\n"
#define UTEST_MSG_END "at %s:%d: %s\n"
/** \endcond */

// Does the real job.
static inline void utest_assert_that(bool cond, const char* msg,
        const char* file, int line_num, const char* func, bool fatal) {
    if (!cond) {
        fprintf(utest_out,
                UTEST_MSG_START
                UTEST_MSG_END,
                msg,
                file, line_num, func);
        ++utest_result;
        if (fatal) {
            utest_exit();
        }
    }
}

/**
 * Non-fatal assertion that expects `cond` to be `true`.
 * If `cond` evaluates to `false`, then it prints diagnostic message to
 * \ref utest_out, increments the number of failed assertions, and continues
 * the test execution.
 */
#define expect_that(cond) \
    utest_assert_that((cond), #cond, __FILE__, __LINE__, __func__, false)

/**
 * Non-fatal assertion that expects `cond` to be `true`.
 * If `cond` evaluates to `false`, then it prints diagnostic message that
 * includes `msg` to \ref utest_out, increments the number of failed assertions,
 * and continues the test execution.
 */
#define expect_that_m(cond, msg) \
    utest_assert_that((cond), #cond": "msg, __FILE__, __LINE__, __func__, false)

/**
 * Fatal assertion that expects `cond` to be `true`.
 * If `cond` evaluates to `false`, then it prints diagnostic message to
 * \ref utest_out, increments the number of failed assertions, and exits the
 * test case by calling \ref utest_exit macro.
 */
#define assert_that(cond) \
    utest_assert_that((cond), #cond, __FILE__, __LINE__, __func__, true)

/**
 * Fatal assertion that expects `cond` to be `true`.
 * If `cond` evaluates to `false`, then it prints diagnostic message that
 * includes `msg` to \ref utest_out, increments the number of failed asserions,
 * and exits the test case by calling \ref utest_exit macro.
 */
#define assert_that_m(cond, msg) \
    utest_assert_that((cond), #cond": "msg, __FILE__, __LINE__, __func__, true)

// Does the real job.
static inline void utest_assert_str_eq(const char* expected, const char* actual,
        const char* msg, const char* file, int line_num, const char* func,
        bool fatal) {
    const bool failed = !expected || !actual
        ? expected != actual
        : strcmp(expected, actual);
    if (failed) {
        fprintf(utest_out,
                UTEST_MSG_START
                "Expected: %s\n"
                "  Actual: %s\n"
                UTEST_MSG_END,
                msg,
                expected ? expected : "NULL",
                actual ? actual : "NULL",
                file, line_num, func);
        ++utest_result;
        if (fatal) {
            utest_exit();
        }
    }
}

/**
 * Non-fatal assertion that expects the strings to be equal.
 * If the strings are not equal, then it prints diagnostic message to
 * \ref utest_out, increments the number of failed assertions, and continues
 * the test execution.
 */
#define expect_str_eq(expected, actual) \
    utest_assert_str_eq((expected), (actual), "", __FILE__, __LINE__, \
            __func__, false)

/**
 * Non-fatal assertion that expects the strings to be equal.
 * If the strings are not equal, then it prints diagnostic message that
 * includes `msg` to \ref utest_out, increments the number of failed assertions,
 * and continues the test execution.
 */
#define expect_str_eq_m(expected, actual, msg) \
    utest_assert_str_eq((expected), (actual), (msg), __FILE__, __LINE__, \
            __func__, false)

/**
 * Fatal assertion that expects the strings to be equal.
 * If the strings are not equal, then it prints diagnostic message to
 * \ref utest_out, increments the number of failed assertions, and exits the
 * test case by calling \ref utest_exit macro.
 */
#define assert_str_eq(expected, actual) \
    utest_assert_str_eq((expected), (actual), "", __FILE__, __LINE__, \
            __func__, true)

/**
 * Fatal assertion that expects the strings to be equal.
 * If the strings are not equal, then it prints diagnostic message that
 * includes `msg` to \ref utest_out, increments the number of failed asserions,
 * and exits the test case by calling \ref utest_exit macro.
 */
#define assert_str_eq_m(expected, actual, msg) \
    utest_assert_str_eq((expected), (actual), (msg), __FILE__, __LINE__, \
            __func__, true)
