/*
 * vec_test.c
 * Unit tests for vector math.
 *
 * Author: hm2code
 */
#include <vuray/util/utest.h>

#include "vec.h"

static void test_vec3_add(void) {
    struct vec3 a = (struct vec3) { .x = 0.f, .y = 1.f, .z = 2.f };
    struct vec3 b = (struct vec3) { .x = 3.f, .y = 4.f, .z = 5.f };

    struct vec3 c = vec3_add(a, b);

    expect_float_eq(3.f, c.x);
    expect_float_eq(5.f, c.y);
    expect_float_eq(7.f, c.z);

    c = vec3_add(a, 0.5f);

    expect_float_eq(0.5f, c.x);
    expect_float_eq(1.5f, c.y);
    expect_float_eq(2.5f, c.z);
}

static void test_vec3_sub(void) {
    struct vec3 a = (struct vec3) { .x = 0.f, .y = 1.f, .z = 2.f };
    struct vec3 b = (struct vec3) { .x = 2.f, .y = 4.f, .z = 6.f };

    struct vec3 c = vec3_sub(a, b);

    expect_float_eq(-2.f, c.x);
    expect_float_eq(-3.f, c.y);
    expect_float_eq(-4.f, c.z);

    c = vec3_sub(a, 0.5f);

    expect_float_eq(-0.5f, c.x);
    expect_float_eq( 0.5f, c.y);
    expect_float_eq( 1.5f, c.z);
}

static void test_vec3_mul(void) {
    struct vec3 a = (struct vec3) { .x = 0.f, .y = 1.f, .z = 2.f };
    struct vec3 b = (struct vec3) { .x = 3.f, .y = 4.f, .z = 5.f };

    struct vec3 c = vec3_mul(a, b);

    expect_float_eq( 0.f, c.x);
    expect_float_eq( 4.f, c.y);
    expect_float_eq(10.f, c.z);

    c = vec3_mul(a, 0.5f);

    expect_float_eq(0.0f, c.x);
    expect_float_eq(0.5f, c.y);
    expect_float_eq(1.0f, c.z);
}

static void test_vec3_div(void) {
    struct vec3 a = (struct vec3) { .x = 0.f, .y = 1.f, .z = 2.f };
    struct vec3 b = (struct vec3) { .x = 3.f, .y = 4.f, .z = 5.f };

    struct vec3 c = vec3_div(a, b);

    expect_float_eq(0.00f, c.x);
    expect_float_eq(0.25f, c.y);
    expect_float_eq(0.40f, c.z);

    c = vec3_div(a, 0.5f);

    expect_float_eq(0.f, c.x);
    expect_float_eq(2.f, c.y);
    expect_float_eq(4.f, c.z);
}

static void test_vec3_dot(void) {
    struct vec3 a = (struct vec3) { .x = 0.f, .y = 1.f, .z = 2.f };
    struct vec3 b = (struct vec3) { .x = 3.f, .y = 4.f, .z = 5.f };

    expect_float_eq(14.f, vec3_dot(a, b));
}

static void test_vec3_len_sq(void) {
    struct vec3 a = (struct vec3) { .x = 0.f, .y = 6.f, .z = 8.f };

    expect_float_eq(100.f, vec3_len_sq(a));
}

static void test_vec3_len(void) {
    struct vec3 a = (struct vec3) { .x = 0.f, .y = 6.f, .z = 8.f };

    expect_float_eq(10.f, vec3_len(a));
}

static void test_vec3_normalize(void) {
    struct vec3 a = (struct vec3) { .x = 0.f, .y = 6.f, .z = 8.f };

    struct vec3 b = vec3_normalize(a);

    expect_float_eq(0.0f, b.x);
    expect_float_eq(0.6f, b.y);
    expect_float_eq(0.8f, b.z);
}

static void test_ray_point_at(void) {
    struct ray r = (struct ray) {
        .origin = (struct vec3) { .x = 0.f, .y = 0.f, .z = 0.f },
        .direction = (struct vec3) { .x = 0.f, .y = 1.f, .z = 0.f }
    };

    struct vec3 p = ray_point_at(r, 2.f);

    expect_float_eq(0.f, p.x);
    expect_float_eq(2.f, p.y);
    expect_float_eq(0.f, p.z);
}

int main(void) {
    test_vec3_add();
    test_vec3_sub();
    test_vec3_mul();
    test_vec3_div();

    test_vec3_dot();
    test_vec3_len_sq();
    test_vec3_len();
    test_vec3_normalize();

    test_ray_point_at();

    utest_exit();
}
