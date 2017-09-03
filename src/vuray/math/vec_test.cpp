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

void test_vec2_data() {
    vec_data<float, 2> data;
    data[X] = 1.f;
    assert_eq(1.f, data[X], "data[X] == 1");
    data[Y] = 2.f;
    assert_eq(2.f, data[Y], "data[Y] == 2");
}

void test_vec3_data() {
    vec_data<float, 3> data;
    data[X] = 1.f;
    assert_eq(1.f, data[X], "data[X] == 1");
    data[Y] = 2.f;
    assert_eq(2.f, data[Y], "data[Y] == 2");
    data[Z] = 3.f;
    assert_eq(3.f, data[Z], "data[Z] == 3");
}

void test_vec4_data() {
    vec_data<float, 4> data;
    data[X] = 1.f;
    assert_eq(1.f, data[X], "data[X] == 1");
    data[Y] = 2.f;
    assert_eq(2.f, data[Y], "data[Y] == 2");
    data[Z] = 3.f;
    assert_eq(3.f, data[Z], "data[Z] == 3");
    data[W] = 4.f;
    assert_eq(4.f, data[W], "data[W] == 4");
}

void test_vec2_basics() {
    vec<float, 2, vec_data<float, 2>> v;

    v.set_x(1.f);
    assert_eq(1.f, v.x(), "v.x() == 1");
    v.set_y(2.f);
    assert_eq(2.f, v.y(), "v.y() == 2");
}

void test_vec3_basics() {
    vec<float, 3, vec_data<float, 3>> v;

    v.set_x(1.f);
    assert_eq(1.f, v.x(), "v.x() == 1");
    v.set_y(2.f);
    assert_eq(2.f, v.y(), "v.y() == 2");
    v.set_z(3.f);
    assert_eq(3.f, v.z(), "v.z() == 3");
}

void test_vec4_basics() {
    vec<float, 4, vec_data<float, 4>> v;

    v.set_x(1.f);
    assert_eq(1.f, v.x(), "v.x() == 1");
    v.set_y(2.f);
    assert_eq(2.f, v.y(), "v.y() == 2");
    v.set_z(3.f);
    assert_eq(3.f, v.z(), "v.z() == 3");
    v.set_w(4.f);
    assert_eq(4.f, v.w(), "v.w() == 4");
}

void test_operator_add() {
    vec<float, 3, vec_data<float, 3>> lhs;

    lhs.set_x(1);
    lhs.set_y(2);
    lhs.set_z(3);

    vec<float, 3, vec_data<float, 3>> rhs;

    rhs.set_x(2);
    rhs.set_y(3);
    rhs.set_z(4);

    lhs += rhs;

    assert_eq(3.f, lhs.x(), "lhs.x() == 3");
    assert_eq(5.f, lhs.y(), "lhs.y() == 5");
    assert_eq(7.f, lhs.z(), "lhs.z() == 7");
}

void test_operator_sub() {
    vec<float, 3, vec_data<float, 3>> lhs;

    lhs.set_x(1);
    lhs.set_y(2);
    lhs.set_z(3);

    vec<float, 3, vec_data<float, 3>> rhs;

    rhs.set_x(4);
    rhs.set_y(3);
    rhs.set_z(2);

    lhs -= rhs;

    assert_eq(-3.f, lhs.x(), "lhs.x() == -3");
    assert_eq(-1.f, lhs.y(), "lhs.y() == -1");
    assert_eq(1.f, lhs.z(), "lhs.z() == 1");
}

void test_operator_mul() {
    vec<float, 3, vec_data<float, 3>> lhs;

    lhs.set_x(1);
    lhs.set_y(2);
    lhs.set_z(3);

    vec<float, 3, vec_data<float, 3>> rhs;

    rhs.set_x(2);
    rhs.set_y(3);
    rhs.set_z(4);

    lhs *= rhs;

    assert_eq(2.f, lhs.x(), "lhs.x() == 2");
    assert_eq(6.f, lhs.y(), "lhs.y() == 6");
    assert_eq(12.f, lhs.z(), "lhs.z() == 12");
}

void test_operator_div() {
    vec<float, 3, vec_data<float, 3>> lhs;

    lhs.set_x(30);
    lhs.set_y(20);
    lhs.set_z(12);

    vec<float, 3, vec_data<float, 3>> rhs;

    rhs.set_x(5);
    rhs.set_y(4);
    rhs.set_z(3);

    lhs /= rhs;

    assert_eq(6.f, lhs.x(), "lhs.x() == 6");
    assert_eq(5.f, lhs.y(), "lhs.y() == 5");
    assert_eq(4.f, lhs.z(), "lhs.z() == 4");
}

void test_operator_add_scalar() {
    vec<float, 3, vec_data<float, 3>> lhs;

    lhs.set_x(1);
    lhs.set_y(2);
    lhs.set_z(3);

    lhs += 2;

    assert_eq(3.f, lhs.x(), "lhs.x() == 3");
    assert_eq(4.f, lhs.y(), "lhs.y() == 4");
    assert_eq(5.f, lhs.z(), "lhs.z() == 5");
}

void test_operator_sub_scalar() {
    vec<float, 3, vec_data<float, 3>> lhs;

    lhs.set_x(1);
    lhs.set_y(2);
    lhs.set_z(3);

    lhs -= 2;

    assert_eq(-1.f, lhs.x(), "lhs.x() == -1");
    assert_eq(0.f, lhs.y(), "lhs.y() == 0");
    assert_eq(1.f, lhs.z(), "lhs.z() == 1");
}

void test_operator_mul_scalar() {
    vec<float, 3, vec_data<float, 3>> lhs;

    lhs.set_x(1);
    lhs.set_y(2);
    lhs.set_z(3);

    lhs *= 2;

    assert_eq(2.f, lhs.x(), "lhs.x() == 2");
    assert_eq(4.f, lhs.y(), "lhs.y() == 4");
    assert_eq(6.f, lhs.z(), "lhs.z() == 6");
}

void test_operator_div_scalar() {
    vec<float, 3, vec_data<float, 3>> lhs;

    lhs.set_x(12);
    lhs.set_y(10);
    lhs.set_z(8);

    lhs /= 2;

    assert_eq(6.f, lhs.x(), "lhs.x() == 6");
    assert_eq(5.f, lhs.y(), "lhs.y() == 5");
    assert_eq(4.f, lhs.z(), "lhs.z() == 4");
}

} // anonymous

int main() {
    test_vec2_data();
    test_vec3_data();
    test_vec4_data();

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

    return 0;
}

