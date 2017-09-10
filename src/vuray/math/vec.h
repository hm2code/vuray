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
 * Represents a ray from `origin` in the given `direction`.
 */
struct ray {
    struct vec3 origin;
    struct vec3 direction;
};

/**
 * Returns point on ray `r` at distance `t` from the ray origin.
 */
inline struct vec3 ray_point_at(struct ray r, float t) {
    r.direction = vec3_mul(r.direction, t);
    return vec3_add(r.origin, r.direction);
}
