//
// unit_test_test.cpp
// ~~~~~~~~~~~~~~~~~~
// Unit tests for unit_test.h.
//
// Author: hm2code
//
namespace {
bool failed_trap_called;

inline void failed_trap() {
    failed_trap_called = true;
}
}

#define VURAY_UNIT_TEST_FAILED_FN failed_trap
#include "unit_test.h"

using namespace vuray::util;

namespace {
bool test_assert_eq_int() {
    failed_trap_called = false;
    assert_eq(1, 1, "1 == 1");
    if (failed_trap_called) {
        return false;
    }
    assert_eq(1, 2, "1 == 2");
    if (!failed_trap_called) {
        return false;
    }
    return true;
}

bool test_assert_eq_bool() {
    failed_trap_called = false;
    assert_eq(true, true, "true == true");
    if (failed_trap_called) {
        return false;
    }
    assert_eq(true, false, "true == false");
    if (!failed_trap_called) {
        return false;
    }
    return true;
}

bool test_assert_eq_ptr() {
    failed_trap_called = false;
    assert_eq(reinterpret_cast<void*>(0x123), reinterpret_cast<void*>(0x123),
            "0x123 == 0x123");
    if (failed_trap_called) {
        return false;
    }
    assert_eq(reinterpret_cast<void*>(0x123), reinterpret_cast<void*>(0x456),
            "0x123 == 0x456");
    if (!failed_trap_called) {
        return false;
    }
    return true;
}

bool test_assert_eq_nullptr() {
    failed_trap_called = false;
    assert_eq(reinterpret_cast<void*>(0), reinterpret_cast<void*>(0),
            "nullptr == nullptr");
    if (failed_trap_called) {
        return false;
    }
    assert_eq(reinterpret_cast<void*>(0x123), reinterpret_cast<void*>(0),
            "0x123 == nullptr");
    if (!failed_trap_called) {
        return false;
    }
    return true;
}

bool test_assert_eq_str() {
    failed_trap_called = false;
    assert_eq("foo", "foo", "foo == foo");
    if (failed_trap_called) {
        return false;
    }
    assert_eq("foo", "bar", "foo == bar");
    if (!failed_trap_called) {
        return false;
    }
    failed_trap_called = false;
    assert_eq(reinterpret_cast<const char*>(0),
            reinterpret_cast<const char*>(0), "nullptr == nullptr");
    if (failed_trap_called) {
        return false;
    }
    assert_eq("foo", reinterpret_cast<const char*>(0), "foo == nullptr");
    if (!failed_trap_called) {
        return false;
    }
    return true;
}
}

int main() {
    if (!test_assert_eq_int()) {
        return 1;
    }
    if (!test_assert_eq_bool()) {
        return 1;
    }
    if (!test_assert_eq_ptr()) {
        return 1;
    }
    if (!test_assert_eq_nullptr()) {
        return 1;
    }
    if (!test_assert_eq_str()) {
        return 1;
    }
    return 0;
}
