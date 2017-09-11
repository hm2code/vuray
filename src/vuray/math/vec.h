/**
 * \file    vec.h
 * \brief   Vector math.
 *
 * \author  hm2code
 */
#pragma once
#include <math.h>

/**
 * A three-element floating-point vector.
 */
struct vec3 {
    float x, y, z;
};

/**
 * Stores vector `v` into memory pointed by `dst`. Please note that the memory
 * must have space for 3 float values.
 */
inline void vec3_store(float* dst, struct vec3 v) {
    dst[0] = v.x; dst[1] = v.y; dst[2] = v.z;
}

/** \cond */
inline struct vec3 vec3_addv(struct vec3 a, struct vec3 b) {
    return (struct vec3) { .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z };
}

inline struct vec3 vec3_adds(struct vec3 a, float b) {
    return (struct vec3) { .x = a.x + b, .y = a.y + b, .z = a.z + b };
}
/** \endcond */

/**
 * Returns `a + b`.
 * \param a - `struct vec3`
 * \param b - either `struct vec3` or `float`
 */
#define vec3_add(a, b) \
    _Generic((b), \
            struct vec3: vec3_addv, \
            default: vec3_adds \
    )((a), (b))

/** \cond */
inline struct vec3 vec3_subv(struct vec3 a, struct vec3 b) {
    return (struct vec3) { .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z };
}

inline struct vec3 vec3_subs(struct vec3 a, float b) {
    return (struct vec3) { .x = a.x - b, .y = a.y - b, .z = a.z - b };
}
/** \endcond */

/**
 * Returns `a - b`.
 * \param a - `struct vec3`
 * \param b - either `struct vec3` or `float`
 */
#define vec3_sub(a, b) \
    _Generic((b), \
            struct vec3: vec3_subv, \
            default: vec3_subs \
    )((a), (b))

/** \cond */
inline struct vec3 vec3_mulv(struct vec3 a, struct vec3 b) {
    return (struct vec3) { .x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z };
}

inline struct vec3 vec3_muls(struct vec3 a, float b) {
    return (struct vec3) { .x = a.x * b, .y = a.y * b, .z = a.z * b };
}
/** \endcond */

/**
 * Returns `a * b`.
 * \param a - `struct vec3`
 * \param b - either `struct vec3` or `float`
 */
#define vec3_mul(a, b) \
    _Generic((b), \
            struct vec3: vec3_mulv, \
            default: vec3_muls \
    )((a), (b))

/** \cond */
inline struct vec3 vec3_divv(struct vec3 a, struct vec3 b) {
    return (struct vec3) { .x = a.x / b.x, .y = a.y / b.y, .z = a.z / b.z };
}

inline struct vec3 vec3_divs(struct vec3 a, float b) {
    return (struct vec3) { .x = a.x / b, .y = a.y / b, .z = a.z / b };
}
/** \endcond */

/**
 * Returns `a / b`.
 * \param a - `struct vec3`
 * \param b - either `struct vec3` or `float`
 */
#define vec3_div(a, b) \
    _Generic((b), \
            struct vec3: vec3_divv, \
            default: vec3_divs \
    )((a), (b))

/**
 * Returns dot product of the two vectors.
 */
inline float vec3_dot(struct vec3 a, struct vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
 * Returns length squared of the given vector.
 */
inline float vec3_len_sq(struct vec3 v) {
    return vec3_dot(v, v);
}

/**
 * Returns length of the given vector.
 */
inline float vec3_len(struct vec3 v) {
    return sqrt(vec3_len_sq(v));
}

/**
 * Returns normalized (unit length) vector `v`.
 */
inline struct vec3 vec3_normalize(struct vec3 v) {
    return vec3_mul(v, 1.f / vec3_len(v));
}

/**
 * Returns a point on the ray at distance `t` from the ray `origin` in the ray
 * `direction`.
 */
inline struct vec3 ray_point_at(struct vec3 origin, struct vec3 direction,
        float t) {
    direction = vec3_mul(direction, t);
    return vec3_add(origin, direction);
}
