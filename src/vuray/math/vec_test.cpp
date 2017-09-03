//
// vec_test.cpp
// ~~~~~~~~~~~~
// Unit tests for vec.h.
//
// Author: hm2code
//
#include <vuray/util/unit_test.h>

#include "vec.h"

using namespace vuray::math;
using namespace vuray::util;

namespace {

void test_vec2_basics() {
    vec<float, 2> v{1.f, 2.f};

    assert_eq(1.f, v.x(), "v.x() == 1");
    assert_eq(2.f, v.y(), "v.y() == 2");

    v.set_x(10);
    v.set_y(11);

    assert_eq(10.f, v.x(), "v.x() == 10");
    assert_eq(11.f, v.y(), "v.y() == 11");
}

void test_vec3_basics() {
    vec<float, 3> v{1.f, 2.f, 3.f};

    assert_eq(1.f, v.x(), "v.x() == 1");
    assert_eq(2.f, v.y(), "v.y() == 2");
    assert_eq(3.f, v.z(), "v.z() == 3");

    v.set_x(10);
    v.set_y(11);
    v.set_z(12);

    assert_eq(10.f, v.x(), "v.x() == 10");
    assert_eq(11.f, v.y(), "v.y() == 11");
    assert_eq(12.f, v.z(), "v.z() == 12");
}

void test_vec4_basics() {
    vec<float, 4> v{1.f, 2.f, 3.f, 4.f};

    assert_eq(1.f, v.x(), "v.x() == 1");
    assert_eq(2.f, v.y(), "v.y() == 2");
    assert_eq(3.f, v.z(), "v.z() == 3");
    assert_eq(4.f, v.w(), "v.w() == 4");

    v.set_x(10);
    v.set_y(11);
    v.set_z(12);
    v.set_w(13);

    assert_eq(10.f, v.x(), "v.x() == 10");
    assert_eq(11.f, v.y(), "v.y() == 11");
    assert_eq(12.f, v.z(), "v.z() == 12");
    assert_eq(13.f, v.w(), "v.w() == 13");
}

void test_operator_add() {
    vec<float, 3> lhs{1.f, 2.f, 3.f};
    constexpr vec<float, 3> rhs{2.f, 3.f, 4.f};

    lhs += rhs;

    assert_eq(3.f, lhs.x(), "lhs.x() == 3");
    assert_eq(5.f, lhs.y(), "lhs.y() == 5");
    assert_eq(7.f, lhs.z(), "lhs.z() == 7");
}

void test_operator_sub() {
    vec<float, 3> lhs{1.f, 2.f, 3.f};
    constexpr vec<float, 3> rhs{4.f, 3.f, 2.f};

    lhs -= rhs;

    assert_eq(-3.f, lhs.x(), "lhs.x() == -3");
    assert_eq(-1.f, lhs.y(), "lhs.y() == -1");
    assert_eq(1.f, lhs.z(), "lhs.z() == 1");
}

void test_operator_mul() {
    vec<float, 3> lhs{1.f, 2.f, 3.f};
    constexpr vec<float, 3> rhs{2.f, 3.f, 4.f};

    lhs *= rhs;

    assert_eq(2.f, lhs.x(), "lhs.x() == 2");
    assert_eq(6.f, lhs.y(), "lhs.y() == 6");
    assert_eq(12.f, lhs.z(), "lhs.z() == 12");
}

void test_operator_div() {
    vec<float, 3> lhs{30.f, 20.f, 12.f};
    constexpr vec<float, 3> rhs{5.f, 4.f, 3.f};

    lhs /= rhs;

    assert_eq(6.f, lhs.x(), "lhs.x() == 6");
    assert_eq(5.f, lhs.y(), "lhs.y() == 5");
    assert_eq(4.f, lhs.z(), "lhs.z() == 4");
}

void test_operator_add_scalar() {
    vec<float, 3> lhs{1.f, 2.f, 3.f};

    lhs += 2;

    assert_eq(3.f, lhs.x(), "lhs.x() == 3");
    assert_eq(4.f, lhs.y(), "lhs.y() == 4");
    assert_eq(5.f, lhs.z(), "lhs.z() == 5");
}

void test_operator_sub_scalar() {
    vec<float, 3> lhs{1.f, 2.f, 3.f};

    lhs -= 2;

    assert_eq(-1.f, lhs.x(), "lhs.x() == -1");
    assert_eq(0.f, lhs.y(), "lhs.y() == 0");
    assert_eq(1.f, lhs.z(), "lhs.z() == 1");
}

void test_operator_mul_scalar() {
    vec<float, 3> lhs{1.f, 2.f, 3.f};

    lhs *= 2;

    assert_eq(2.f, lhs.x(), "lhs.x() == 2");
    assert_eq(4.f, lhs.y(), "lhs.y() == 4");
    assert_eq(6.f, lhs.z(), "lhs.z() == 6");
}

void test_operator_div_scalar() {
    vec<float, 3> lhs{12.f, 10.f, 8.f};

    lhs /= 2;

    assert_eq(6.f, lhs.x(), "lhs.x() == 6");
    assert_eq(5.f, lhs.y(), "lhs.y() == 5");
    assert_eq(4.f, lhs.z(), "lhs.z() == 4");
}

void test_length_sq() {
    constexpr vec<float, 2> v{2.f, 3.f};

    assert_eq(13.f, v.length_sq(), "{2, 3}.length_sq() == 13");
}

void test_length() {
    constexpr vec<float, 2> v{4.f, 3.f};

    assert_eq(5.f, v.length(), "{4, 3}.length() == 5");
}

void test_normalized() {
    constexpr vec<float, 2> v{4.f, 3.f};
    vec<float, 2> n = v.normalized();
    
    assert_eq(0.8f, n.x(), "n.x() == 0.8");
    assert_eq(0.6f, n.y(), "n.y() == 0.6");
}

void test_dot() {
    constexpr vec<float, 2> a{1.f, 2.f};
    constexpr vec<float, 2> b{3.f, 4.f};

    assert_eq(11.f, a.dot(b), "{1, 2}.dot({3, 4}) == 11");
}

void test_operator_add_binary() {
    constexpr vec<float, 2> a{1.f, 2.f};
    constexpr vec<float, 2> b{3.f, 4.f};

    constexpr auto c = a + b;

    assert_eq(4.f, c.x(), "c.x() == 4");
    assert_eq(6.f, c.y(), "c.y() == 6");
}

void test_operator_sub_binary() {
    constexpr vec<float, 2> a{3.f, 4.f};
    constexpr vec<float, 2> b{2.f, 1.f};

    constexpr auto c = a - b;

    assert_eq(1.f, c.x(), "c.x() == 1");
    assert_eq(3.f, c.y(), "c.y() == 3");
}

void test_operator_mul_binary() {
    constexpr vec<float, 2> a{1.f, 2.f};
    constexpr vec<float, 2> b{3.f, 4.f};

    constexpr auto c = a * b;

    assert_eq(3.f, c.x(), "c.x() == 3");
    assert_eq(8.f, c.y(), "c.y() == 8");
}

void test_operator_div_binary() {
    constexpr vec<float, 2> a{3.f, 4.f};
    constexpr vec<float, 2> b{2.f, 1.f};

    constexpr auto c = a / b;

    assert_eq(1.5f, c.x(), "c.x() == 1.5");
    assert_eq(4.f, c.y(), "c.y() == 4");
}

void test_operator_add_binary_scalar() {
    constexpr vec<float, 2> a{1.f, 2.f};

    constexpr auto b = a + 3.f;

    assert_eq(4.f, b.x(), "b.x() == 4");
    assert_eq(5.f, b.y(), "b.y() == 5");

    constexpr auto c = 4.f + a;

    assert_eq(5.f, c.x(), "c.x() == 5");
    assert_eq(6.f, c.y(), "c.y() == 6");
}

void test_operator_sub_binary_scalar() {
    constexpr vec<float, 2> a{1.f, 2.f};

    constexpr auto b = a - 3.f;

    assert_eq(-2.f, b.x(), "b.x() == -2");
    assert_eq(-1.f, b.y(), "b.y() == -1");
}

void test_operator_mul_binary_scalar() {
    constexpr vec<float, 2> a{1.f, 2.f};

    constexpr auto b = a * 3.f;

    assert_eq(3.f, b.x(), "b.x() == 3");
    assert_eq(6.f, b.y(), "b.y() == 6");

    constexpr auto c = 4.f * a;

    assert_eq(4.f, c.x(), "c.x() == 4");
    assert_eq(8.f, c.y(), "c.y() == 8");
}

void test_operator_div_binary_scalar() {
    constexpr vec<float, 2> a{1.f, 2.f};

    constexpr auto b = a / 4.f;

    assert_eq(0.25f, b.x(), "b.x() == 0.25");
    assert_eq(0.5f, b.y(), "b.y() == 0.5");
}

} // anonymous

int main() {
    test_vec2_basics();
    test_vec3_basics();
    test_vec4_basics();

    test_operator_add();
    test_operator_sub();
    test_operator_mul();
    test_operator_div();

    test_operator_add_scalar();
    test_operator_sub_scalar();
    test_operator_mul_scalar();
    test_operator_div_scalar();

    test_dot();
    test_length_sq();
    test_length();
    test_normalized();

    test_operator_add_binary();
    test_operator_sub_binary();
    test_operator_mul_binary();
    test_operator_div_binary();

    test_operator_add_binary_scalar();
    test_operator_sub_binary_scalar();
    test_operator_mul_binary_scalar();
    test_operator_div_binary_scalar();

    return 0;
}

