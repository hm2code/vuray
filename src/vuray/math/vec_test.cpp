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

// vec2
void test_vec2_constructors() {
    const vec2<float> a{3};

    assert_eq(3.f, a.x(), "a.x() == 3");
    assert_eq(3.f, a.y(), "a.y() == 3");

    const float data[] = {4, 5};
    const vec2<float> b(data);

    assert_eq(4.f, b.x(), "b.x() == 4");
    assert_eq(5.f, b.y(), "b.y() == 5");

    const vec2<float> c{6, 7};

    assert_eq(6.f, c.x(), "c.x() == 6");
    assert_eq(7.f, c.y(), "c.y() == 7");

    const vec2<float> d{c};

    assert_eq(6.f, d.x(), "d.x() == 6");
    assert_eq(7.f, d.y(), "d.y() == 7");

    vec2<float> e;
    e = d;

    assert_eq(6.f, e.x(), "e.x() == 6");
    assert_eq(7.f, e.y(), "e.y() == 7");
}

void test_vec2_negate() {
    const vec2<float> a{1, 2};

    const auto b = -a;

    assert_eq(-1.f, b.x(), "b.x() == -1");
    assert_eq(-2.f, b.y(), "b.y() == -2");
}

void test_vec2_add() {
    const vec2<float> a{1, 2};
    const vec2<float> b{3, 4};

    auto c = a + b;

    assert_eq(4.f, c.x(), "c.x() == 4");
    assert_eq(6.f, c.y(), "c.y() == 6");

    c = a + 3.f;

    assert_eq(4.f, c.x(), "c.x() == 4");
    assert_eq(5.f, c.y(), "c.y() == 5");

    c = 4.f + b;

    assert_eq(7.f, c.x(), "c.x() == 7");
    assert_eq(8.f, c.y(), "c.y() == 8");
}

void test_vec2_sub() {
    const vec2<float> a{5, 6};
    const vec2<float> b{3, 1};

    auto c = a - b;

    assert_eq(2.f, c.x(), "c.x() == 2");
    assert_eq(5.f, c.y(), "c.y() == 5");

    c = a - 2.f;

    assert_eq(3.f, c.x(), "c.x() == 3");
    assert_eq(4.f, c.y(), "c.y() == 4");

    c = 7.f - b;

    assert_eq(4.f, c.x(), "c.x() == 4");
    assert_eq(6.f, c.y(), "c.y() == 6");
}

void test_vec2_mul() {
    const vec2<float> a{2, 3};
    const vec2<float> b{4, 5};

    auto c = a * b;

    assert_eq(8.f, c.x(), "c.x() == 8");
    assert_eq(15.f, c.y(), "c.y() == 15");

    c = a * 3.f;

    assert_eq(6.f, c.x(), "c.x() == 6");
    assert_eq(9.f, c.y(), "c.y() == 9");

    c = 4.f * b;

    assert_eq(16.f, c.x(), "c.x() == 16");
    assert_eq(20.f, c.y(), "c.y() == 20");
}

void test_vec2_div() {
    const vec2<float> a{6, 10};
    const vec2<float> b{3, 5};

    auto c = a / b;

    assert_eq(2.f, c.x(), "c.x() == 2");
    assert_eq(2.f, c.y(), "c.y() == 2");

    c = a / 2.f;

    assert_eq(3.f, c.x(), "c.x() == 3");
    assert_eq(5.f, c.y(), "c.y() == 5");

    c = 30.f / b;

    assert_eq(10.f, c.x(), "c.x() == 10");
    assert_eq(6.f, c.y(), "c.y() == 6");
}

void test_vec2_dot() {
    const vec2<float> a{2, 3};
    const vec2<float> b{4, 5};

    assert_eq(13.f, dot(a, a), "dot(a, a) == 13");
    assert_eq(23.f, dot(a, b), "dot(a, b) == 23");
}

void test_vec2_length() {
    const vec2<float> a{6, 8};

    assert_eq(10.f, length(a), "length(a) == 10.f");
}

void test_vec2_normalize() {
    const vec2<float> a{6, 8};

    const auto n = normalize(a);

    assert_eq(.6f, n.x(), "n.x() == .6f");
    assert_eq(.8f, n.y(), "n.y() == .8f");
}

void test_vec2() {
    test_vec2_constructors();

    test_vec2_negate();

    test_vec2_add();
    test_vec2_sub();
    test_vec2_mul();
    test_vec2_div();

    test_vec2_dot();
    test_vec2_length();
    test_vec2_normalize();
}

// vec3
void test_vec3_constructors() {
    const vec3<float> a{3};

    assert_eq(3.f, a.x(), "a.x() == 3");
    assert_eq(3.f, a.y(), "a.y() == 3");
    assert_eq(3.f, a.z(), "a.z() == 3");

    const float data[] = {4, 5, 6};
    const vec3<float> b(data);

    assert_eq(4.f, b.x(), "b.x() == 4");
    assert_eq(5.f, b.y(), "b.y() == 5");
    assert_eq(6.f, b.z(), "b.z() == 6");

    const vec3<float> c{7, 8, 9};

    assert_eq(7.f, c.x(), "c.x() == 7");
    assert_eq(8.f, c.y(), "c.y() == 8");
    assert_eq(9.f, c.z(), "c.z() == 9");

    const vec3<float> d{c};

    assert_eq(7.f, d.x(), "d.x() == 7");
    assert_eq(8.f, d.y(), "d.y() == 8");
    assert_eq(9.f, d.z(), "d.z() == 9");

    vec3<float> e;
    e = d;

    assert_eq(7.f, e.x(), "e.x() == 7");
    assert_eq(8.f, e.y(), "e.y() == 8");
    assert_eq(9.f, e.z(), "e.z() == 9");

    vec3<float> f{vec2<float>{10, 11}, 12};

    assert_eq(10.f, f.x(), "f.x() == 10");
    assert_eq(11.f, f.y(), "f.y() == 11");
    assert_eq(12.f, f.z(), "f.z() == 12");
}

void test_vec3_negate() {
    const vec3<float> a{1, 2, 3};

    const auto b = -a;

    assert_eq(-1.f, b.x(), "b.x() == -1");
    assert_eq(-2.f, b.y(), "b.y() == -2");
    assert_eq(-3.f, b.z(), "b.z() == -3");
}

void test_vec3_add() {
    const vec3<float> a{1, 2, 3};
    const vec3<float> b{4, 5, 6};

    auto c = a + b;

    assert_eq(5.f, c.x(), "c.x() == 5");
    assert_eq(7.f, c.y(), "c.y() == 7");
    assert_eq(9.f, c.z(), "c.z() == 9");

    c = a + 3.f;

    assert_eq(4.f, c.x(), "c.x() == 4");
    assert_eq(5.f, c.y(), "c.y() == 5");
    assert_eq(6.f, c.z(), "c.z() == 6");

    c = 4.f + b;

    assert_eq(8.f, c.x(), "c.x() == 8");
    assert_eq(9.f, c.y(), "c.y() == 9");
    assert_eq(10.f, c.z(), "c.z() == 10");
}

void test_vec3_sub() {
    const vec3<float> a{5, 6, 7};
    const vec3<float> b{3, 2, 1};

    auto c = a - b;

    assert_eq(2.f, c.x(), "c.x() == 2");
    assert_eq(4.f, c.y(), "c.y() == 4");
    assert_eq(6.f, c.z(), "c.z() == 6");

    c = a - 2.f;

    assert_eq(3.f, c.x(), "c.x() == 3");
    assert_eq(4.f, c.y(), "c.y() == 4");
    assert_eq(5.f, c.z(), "c.z() == 5");

    c = 7.f - b;

    assert_eq(4.f, c.x(), "c.x() == 4");
    assert_eq(5.f, c.y(), "c.y() == 5");
    assert_eq(6.f, c.z(), "c.z() == 6");
}

void test_vec3_mul() {
    const vec3<float> a{2, 3, 4};
    const vec3<float> b{5, 6, 7};

    auto c = a * b;

    assert_eq(10.f, c.x(), "c.x() == 10");
    assert_eq(18.f, c.y(), "c.y() == 18");
    assert_eq(28.f, c.z(), "c.z() == 28");

    c = a * 3.f;

    assert_eq(6.f, c.x(), "c.x() == 6");
    assert_eq(9.f, c.y(), "c.y() == 9");
    assert_eq(12.f, c.z(), "c.z() == 12");

    c = 4.f * b;

    assert_eq(20.f, c.x(), "c.x() == 20");
    assert_eq(24.f, c.y(), "c.y() == 24");
    assert_eq(28.f, c.z(), "c.z() == 28");
}

void test_vec3_div() {
    const vec3<float> a{6, 10, 8};
    const vec3<float> b{3, 5, 2};

    auto c = a / b;

    assert_eq(2.f, c.x(), "c.x() == 2");
    assert_eq(2.f, c.y(), "c.y() == 2");
    assert_eq(4.f, c.z(), "c.z() == 4");

    c = a / 2.f;

    assert_eq(3.f, c.x(), "c.x() == 3");
    assert_eq(5.f, c.y(), "c.y() == 5");
    assert_eq(4.f, c.z(), "c.z() == 4");

    c = 30.f / b;

    assert_eq(10.f, c.x(), "c.x() == 10");
    assert_eq(6.f, c.y(), "c.y() == 6");
    assert_eq(15.f, c.z(), "c.z() == 15");
}

void test_vec3_dot() {
    const vec3<float> a{2, 3, 4};
    const vec3<float> b{5, 6, 7};

    assert_eq(29.f, dot(a, a), "dot(a, a) == 29");
    assert_eq(56.f, dot(a, b), "dot(a, b) == 56");
}

void test_vec3_length() {
    const vec3<float> a{6, 8, 0};
    const vec3<float> b{8, 0, 6};

    assert_eq(10.f, length(a), "length(a) == 10.f");
    assert_eq(10.f, length(b), "length(b) == 10.f");
}

void test_vec3_normalize() {
    const vec3<float> a{6, 8, 0};
    const vec3<float> b{6, 0, 8};

    auto n = normalize(a);

    assert_eq(.6f, n.x(), "n.x() == .6f");
    assert_eq(.8f, n.y(), "n.y() == .8f");
    assert_eq(.0f, n.z(), "n.z() == .0f");

    n = normalize(b);

    assert_eq(.6f, n.x(), "n.x() == .6f");
    assert_eq(.0f, n.y(), "n.y() == .0f");
    assert_eq(.8f, n.z(), "n.z() == .8f");
}

void test_vec3() {
    test_vec3_constructors();

    test_vec3_negate();

    test_vec3_add();
    test_vec3_sub();
    test_vec3_mul();
    test_vec3_div();

    test_vec3_dot();
    test_vec3_length();
    test_vec3_normalize();
}

// vec4
void test_vec4_constructors() {
    const vec4<float> a{3};

    assert_eq(3.f, a.x(), "a.x() == 3");
    assert_eq(3.f, a.y(), "a.y() == 3");
    assert_eq(3.f, a.z(), "a.z() == 3");
    assert_eq(3.f, a.w(), "a.w() == 3");

    const float data[] = {4, 5, 6, 7};
    const vec4<float> b(data);

    assert_eq(4.f, b.x(), "b.x() == 4");
    assert_eq(5.f, b.y(), "b.y() == 5");
    assert_eq(6.f, b.z(), "b.z() == 6");
    assert_eq(7.f, b.w(), "b.w() == 7");

    const vec4<float> c{8, 9, 10, 11};

    assert_eq(8.f, c.x(), "c.x() == 8");
    assert_eq(9.f, c.y(), "c.y() == 9");
    assert_eq(10.f, c.z(), "c.z() == 10");
    assert_eq(11.f, c.w(), "c.w() == 11");

    const vec4<float> d{c};

    assert_eq(8.f, d.x(), "d.x() == 8");
    assert_eq(9.f, d.y(), "d.y() == 9");
    assert_eq(10.f, d.z(), "d.z() == 10");
    assert_eq(11.f, d.w(), "d.w() == 11");

    vec4<float> e;
    e = d;

    assert_eq(8.f, e.x(), "e.x() == 8");
    assert_eq(9.f, e.y(), "e.y() == 9");
    assert_eq(10.f, e.z(), "e.z() == 10");
    assert_eq(11.f, e.w(), "e.w() == 11");

    vec4<float> f{vec3<float>{10, 11, 12}, 13};

    assert_eq(10.f, f.x(), "f.x() == 10");
    assert_eq(11.f, f.y(), "f.y() == 11");
    assert_eq(12.f, f.z(), "f.z() == 12");
    assert_eq(13.f, f.w(), "f.w() == 13");
}

void test_vec4_negate() {
    const vec4<float> a{1, 2, 3, 4};

    const auto b = -a;

    assert_eq(-1.f, b.x(), "b.x() == -1");
    assert_eq(-2.f, b.y(), "b.y() == -2");
    assert_eq(-3.f, b.z(), "b.z() == -3");
    assert_eq(-4.f, b.w(), "b.w() == -4");
}

void test_vec4_add() {
    const vec4<float> a{1, 2, 3, 4};
    const vec4<float> b{5, 6, 7, 8};

    auto c = a + b;

    assert_eq(6.f, c.x(), "c.x() == 6");
    assert_eq(8.f, c.y(), "c.y() == 8");
    assert_eq(10.f, c.z(), "c.z() == 10");
    assert_eq(12.f, c.w(), "c.w() == 12");

    c = a + 3.f;

    assert_eq(4.f, c.x(), "c.x() == 4");
    assert_eq(5.f, c.y(), "c.y() == 5");
    assert_eq(6.f, c.z(), "c.z() == 6");
    assert_eq(7.f, c.w(), "c.w() == 7");

    c = 4.f + b;

    assert_eq(9.f, c.x(), "c.x() == 9");
    assert_eq(10.f, c.y(), "c.y() == 10");
    assert_eq(11.f, c.z(), "c.z() == 11");
    assert_eq(12.f, c.w(), "c.w() == 12");
}

void test_vec4_sub() {
    const vec4<float> a{5, 6, 7, 8};
    const vec4<float> b{3, 2, 1, 5};

    auto c = a - b;

    assert_eq(2.f, c.x(), "c.x() == 2");
    assert_eq(4.f, c.y(), "c.y() == 4");
    assert_eq(6.f, c.z(), "c.z() == 6");
    assert_eq(3.f, c.w(), "c.w() == 3");

    c = a - 2.f;

    assert_eq(3.f, c.x(), "c.x() == 3");
    assert_eq(4.f, c.y(), "c.y() == 4");
    assert_eq(5.f, c.z(), "c.z() == 5");
    assert_eq(6.f, c.w(), "c.w() == 6");

    c = 7.f - b;

    assert_eq(4.f, c.x(), "c.x() == 4");
    assert_eq(5.f, c.y(), "c.y() == 5");
    assert_eq(6.f, c.z(), "c.z() == 6");
    assert_eq(2.f, c.w(), "c.w() == 2");
}

void test_vec4_mul() {
    const vec4<float> a{2, 3, 4, 5};
    const vec4<float> b{6, 7, 8, 9};

    auto c = a * b;

    assert_eq(12.f, c.x(), "c.x() == 12");
    assert_eq(21.f, c.y(), "c.y() == 21");
    assert_eq(32.f, c.z(), "c.z() == 32");
    assert_eq(45.f, c.w(), "c.w() == 45");

    c = a * 3.f;

    assert_eq(6.f, c.x(), "c.x() == 6");
    assert_eq(9.f, c.y(), "c.y() == 9");
    assert_eq(12.f, c.z(), "c.z() == 12");
    assert_eq(15.f, c.w(), "c.w() == 15");

    c = 4.f * b;

    assert_eq(24.f, c.x(), "c.x() == 24");
    assert_eq(28.f, c.y(), "c.y() == 28");
    assert_eq(32.f, c.z(), "c.z() == 32");
    assert_eq(36.f, c.w(), "c.z() == 36");
}

void test_vec4_div() {
    const vec4<float> a{6, 10, 8, 12};
    const vec4<float> b{3, 5, 2, 4};

    auto c = a / b;

    assert_eq(2.f, c.x(), "c.x() == 2");
    assert_eq(2.f, c.y(), "c.y() == 2");
    assert_eq(4.f, c.z(), "c.z() == 4");
    assert_eq(3.f, c.w(), "c.w() == 3");

    c = a / 2.f;

    assert_eq(3.f, c.x(), "c.x() == 3");
    assert_eq(5.f, c.y(), "c.y() == 5");
    assert_eq(4.f, c.z(), "c.z() == 4");
    assert_eq(6.f, c.w(), "c.w() == 6");

    c = 60.f / b;

    assert_eq(20.f, c.x(), "c.x() == 20");
    assert_eq(12.f, c.y(), "c.y() == 12");
    assert_eq(30.f, c.z(), "c.z() == 30");
    assert_eq(15.f, c.w(), "c.w() == 15");
}

void test_vec4_dot() {
    const vec4<float> a{2, 3, 4, 5};
    const vec4<float> b{6, 7, 8, 9};

    assert_eq(54.f, dot(a, a), "dot(a, a) == 54");
    assert_eq(110.f, dot(a, b), "dot(a, b) == 110");
}

void test_vec4_length() {
    const vec4<float> a{6, 8, 0, 0};
    const vec4<float> b{0, 0, 6, 8};

    assert_eq(10.f, length(a), "length(a) == 10.f");
    assert_eq(10.f, length(b), "length(b) == 10.f");
}

void test_vec4_normalize() {
    const vec4<float> a{6, 8, 0, 0};
    const vec4<float> b{0, 0, 8, 6};

    auto n = normalize(a);

    assert_eq(.6f, n.x(), "n.x() == .6f");
    assert_eq(.8f, n.y(), "n.y() == .8f");
    assert_eq(.0f, n.z(), "n.z() == .0f");
    assert_eq(.0f, n.w(), "n.w() == .0f");

    n = normalize(b);

    assert_eq(.0f, n.x(), "n.x() == .0f");
    assert_eq(.0f, n.y(), "n.y() == .0f");
    assert_eq(.8f, n.z(), "n.z() == .8f");
    assert_eq(.6f, n.w(), "n.w() == .6f");
}

void test_vec4() {
    test_vec4_constructors();

    test_vec4_negate();

    test_vec4_add();
    test_vec4_sub();
    test_vec4_mul();
    test_vec4_div();

    test_vec4_dot();
    test_vec4_length();
    test_vec4_normalize();
}

} // anonymous

int main() {
    test_vec2();
    test_vec3();
    test_vec4();

    return 0;
}

