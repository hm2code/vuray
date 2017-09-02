//
// unit_test.h
// ~~~~~~~~~~~
// Unit testing utilities.
//
// Athor: hm2code
//
#pragma once
#include <iostream>

namespace vuray {
namespace util {

#ifndef VURAY_UNIT_TEST_FAILED_FN
namespace {
inline void assert_failed_fn_default() {
    std::exit(1);
}
}
// This macro represents a function to be called when assertion failed.
// Default implementation ends up with calling `std::exit(1)`.
#define VURAY_UNIT_TEST_FAILED_FN assert_failed_fn_default
#endif

#ifndef VURAY_UNIT_TEST_OUTPUT
// This macro represents an output stream to be used to print diagnostics when
// an assertion failed. Default: `std::cerr`.
#define VURAY_UNIT_TEST_OUTPUT std::cerr
#endif

namespace {
// Puts `value` into the output stream.
template<typename T> 
std::ostream& put_value(std::ostream& out, T value) {
    return out << value;
}

// Specialization for bool.
template<>
std::ostream& put_value(std::ostream& out, bool value) {
    return out << (value ? "true" : "false");
}

// Specialization for strings.
template<>
std::ostream& put_value(std::ostream& out, const char* value) {
    return out << (value ? value : "nullptr");
}

// Prints diagnostics into the output.
template<typename T>
inline void print_diagnostics(T expected, T actual, const char* message,
        std::ostream& out, const char* file_name, int line_num) {
    out << "Assertion failed: " << message << '\n';
    out << "Expected: "; put_value(out, expected) << '\n';
    out << "  Actual: "; put_value(out, actual) << '\n';
    out << "at " << file_name << " line " << line_num << std::endl;
}

/// Generic implementation expecting the values to be equal.
template<typename T>
inline void assert_eq_(T expected, T actual, const char* message,
        std::ostream& out, const char* file_name, int line_num) {
    if (expected != actual) {
        print_diagnostics(expected, actual, message, out, file_name, line_num);
        VURAY_UNIT_TEST_FAILED_FN();
    }
}

// Specialization for strings.
template<>
inline void assert_eq_(const char* expected, const char* actual,
        const char* message, std::ostream& out, const char* file_name,
        int line_num) {
    const bool failed = !expected || !actual
        ? expected != actual
        : std::strcmp(expected, actual) != 0;
    if (failed) {
        print_diagnostics(expected, actual, message, out, file_name, line_num);
        VURAY_UNIT_TEST_FAILED_FN();
    }
}
}

// Asserts that `actual` equals to `expected`.
#define assert_eq(expected, actual, message) \
    vuray::util::assert_eq_((expected), (actual), (message),\
            VURAY_UNIT_TEST_OUTPUT, __FILE__, __LINE__)

} // util
} // vuray
