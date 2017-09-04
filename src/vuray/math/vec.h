//
// vec.h
// ~~~~~
// Vector math.
//
// Author: hm2code
//
#pragma once
#include <cmath>

namespace vuray {
namespace math {

// All vectors are immutable by design (compiler generates exactly the same
// code if there were mutating operators such as +=). Also, there is no direct
// access to the vector components in order to make the interface compatible
// with SIMD implementations where vector components are packed within a single
// 128-bit value.
// None of the methods is declared as `constexpr` in order to make the
// interface compatible with SIMD implementations via intrinsic functions,
// which unfortunately are not declared as constant expressions.
// The following vector operations are defined:
// - -a
// - a + b
// - a - b
// - a * b
// - a / b
// - dot(a, b)
// - length(a)
// - normalize(a)

// Two element vector of `T` element type.
template<typename T>
class vec2 {
public:
    vec2() {}
    explicit vec2(T v) : _x{v}, _y{v} {}
    explicit vec2(const T* v) : _x{v[0]}, _y{v[1]} {}
    vec2(T x, T y) : _x{x}, _y{y} {}

    T x() const { return _x; }
    T y() const { return _y; }

    vec2 operator -() const { return vec2{-_x, -_y}; }

private:
    T _x, _y;
};

template<typename T>
inline vec2<T> operator +(vec2<T> a, vec2<T> b) {
    return vec2<T>{a.x() + b.x(), a.y() + b.y()};
}

template<typename T>
inline vec2<T> operator +(vec2<T> a, T b) {
    return vec2<T>{a.x() + b, a.y() + b};
}

template<typename T>
inline vec2<T> operator +(T a, vec2<T> b) {
    return vec2<T>{a + b.x(), a + b.y()};
}

template<typename T>
inline vec2<T> operator -(vec2<T> a, vec2<T> b) {
    return vec2<T>{a.x() - b.x(), a.y() - b.y()};
}

template<typename T>
inline vec2<T> operator -(vec2<T> a, T b) {
    return vec2<T>{a.x() - b, a.y() - b};
}

template<typename T>
inline vec2<T> operator -(T a, vec2<T> b) {
    return vec2<T>{a - b.x(), a - b.y()};
}

template<typename T>
inline vec2<T> operator *(vec2<T> a, vec2<T> b) {
    return vec2<T>{a.x() * b.x(), a.y() * b.y()};
}

template<typename T>
inline vec2<T> operator *(vec2<T> a, T b) {
    return vec2<T>{a.x() * b, a.y() * b};
}

template<typename T>
inline vec2<T> operator *(T a, vec2<T> b) {
    return vec2<T>{a * b.x(), a * b.y()};
}

template<typename T>
inline vec2<T> operator /(vec2<T> a, vec2<T> b) {
    return vec2<T>{a.x() / b.x(), a.y() / b.y()};
}

template<typename T>
inline vec2<T> operator /(vec2<T> a, T b) {
    return vec2<T>{a.x() / b, a.y() / b};
}

template<typename T>
inline vec2<T> operator /(T a, vec2<T> b) {
    return vec2<T>{a / b.x(), a / b.y()};
}

template<typename T>
inline T dot(vec2<T> a, vec2<T> b) {
    return a.x() * b.x() + a.y() * b.y();
}

template<typename T>
inline T length(vec2<T> v) {
    return std::sqrt(dot(v, v));
}

template<typename T>
inline vec2<T> normalize(vec2<T> v) {
    return v * (static_cast<T>(1) / length(v));
}

// Three element vector of `T` element type.
template<typename T>
class vec3 {
public:
    vec3() {}
    explicit vec3(T v) : _x{v}, _y{v}, _z{v} {}
    explicit vec3(const T* v) : _x{v[0]}, _y{v[1]}, _z{v[2]} {}
    vec3(T x, T y, T z) : _x{x}, _y{y}, _z{z} {}
    vec3(vec2<T> v, T z) : _x{v.x()}, _y{v.y()}, _z{z} {}

    T x() const { return _x; }
    T y() const { return _y; }
    T z() const { return _z; }

    vec3 operator -() const { return vec3{-_x, -_y, -_z}; }

private:
    T _x, _y, _z;
};

template<typename T>
inline vec3<T> operator +(vec3<T> a, vec3<T> b) {
    return vec3<T>{a.x() + b.x(), a.y() + b.y(), a.z() + b.z()};
}

template<typename T>
inline vec3<T> operator +(vec3<T> a, T b) {
    return vec3<T>{a.x() + b, a.y() + b, a.z() + b};
}

template<typename T>
inline vec3<T> operator +(T a, vec3<T> b) {
    return vec3<T>{a + b.x(), a + b.y(), a + b.z()};
}

template<typename T>
inline vec3<T> operator -(vec3<T> a, vec3<T> b) {
    return vec3<T>{a.x() - b.x(), a.y() - b.y(), a.z() - b.z()};
}

template<typename T>
inline vec3<T> operator -(vec3<T> a, T b) {
    return vec3<T>{a.x() - b, a.y() - b, a.z() - b};
}

template<typename T>
inline vec3<T> operator -(T a, vec3<T> b) {
    return vec3<T>{a - b.x(), a - b.y(), a - b.z()};
}

template<typename T>
inline vec3<T> operator *(vec3<T> a, vec3<T> b) {
    return vec3<T>{a.x() * b.x(), a.y() * b.y(), a.z() * b.z()};
}

template<typename T>
inline vec3<T> operator *(vec3<T> a, T b) {
    return vec3<T>{a.x() * b, a.y() * b, a.z() * b};
}

template<typename T>
inline vec3<T> operator *(T a, vec3<T> b) {
    return vec3<T>{a * b.x(), a * b.y(), a * b.z()};
}

template<typename T>
inline vec3<T> operator /(vec3<T> a, vec3<T> b) {
    return vec3<T>{a.x() / b.x(), a.y() / b.y(), a.z() / b.z()};
}

template<typename T>
inline vec3<T> operator /(vec3<T> a, T b) {
    return vec3<T>{a.x() / b, a.y() / b, a.z() / b};
}

template<typename T>
inline vec3<T> operator /(T a, vec3<T> b) {
    return vec3<T>{a / b.x(), a / b.y(), a / b.z()};
}

template<typename T>
inline T dot(vec3<T> a, vec3<T> b) {
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

template<typename T>
inline T length(vec3<T> v) {
    return std::sqrt(dot(v, v));
}

template<typename T>
inline vec3<T> normalize(vec3<T> v) {
    return v * (static_cast<T>(1) / length(v));
}

// Four element vector of `T` element type.
template<typename T>
class vec4 {
public:
    vec4() {}
    explicit vec4(T v) : _x{v}, _y{v}, _z{v}, _w{v} {}
    explicit vec4(const T* v) : _x{v[0]}, _y{v[1]}, _z{v[2]}, _w{v[3]} {}
    vec4(T x, T y, T z, T w) : _x{x}, _y{y}, _z{z}, _w{w} {}
    vec4(vec3<float> v, T w) : _x{v.x()}, _y{v.y()}, _z{v.z()}, _w{w} {}

    T x() const { return _x; }
    T y() const { return _y; }
    T z() const { return _z; }
    T w() const { return _w; }

    vec4 operator -() const { return vec4{-_x, -_y, -_z, -_w}; }

private:
    T _x, _y, _z, _w;
};

template<typename T>
inline vec4<T> operator +(vec4<T> a, vec4<T> b) {
    return vec4<T>{a.x() + b.x(), a.y() + b.y(), a.z() + b.z(), a.w() + b.w()};
}

template<typename T>
inline vec4<T> operator +(vec4<T> a, T b) {
    return vec4<T>{a.x() + b, a.y() + b, a.z() + b, a.w() + b};
}

template<typename T>
inline vec4<T> operator +(T a, vec4<T> b) {
    return vec4<T>{a + b.x(), a + b.y(), a + b.z(), a + b.w()};
}

template<typename T>
inline vec4<T> operator -(vec4<T> a, vec4<T> b) {
    return vec4<T>{a.x() - b.x(), a.y() - b.y(), a.z() - b.z(), a.w() - b.w()};
}

template<typename T>
inline vec4<T> operator -(vec4<T> a, T b) {
    return vec4<T>{a.x() - b, a.y() - b, a.z() - b, a.w() - b};
}

template<typename T>
inline vec4<T> operator -(T a, vec4<T> b) {
    return vec4<T>{a - b.x(), a - b.y(), a - b.z(), a - b.w()};
}

template<typename T>
inline vec4<T> operator *(vec4<T> a, vec4<T> b) {
    return vec4<T>{a.x() * b.x(), a.y() * b.y(), a.z() * b.z(), a.w() * b.w()};
}

template<typename T>
inline vec4<T> operator *(vec4<T> a, T b) {
    return vec4<T>{a.x() * b, a.y() * b, a.z() * b, a.w() * b};
}

template<typename T>
inline vec4<T> operator *(T a, vec4<T> b) {
    return vec4<T>{a * b.x(), a * b.y(), a * b.z(), a * b.w()};
}

template<typename T>
inline vec4<T> operator /(vec4<T> a, vec4<T> b) {
    return vec4<T>{a.x() / b.x(), a.y() / b.y(), a.z() / b.z(), a.w() / b.w()};
}

template<typename T>
inline vec4<T> operator /(vec4<T> a, T b) {
    return vec4<T>{a.x() / b, a.y() / b, a.z() / b, a.w() / b};
}

template<typename T>
inline vec4<T> operator /(T a, vec4<T> b) {
    return vec4<T>{a / b.x(), a / b.y(), a / b.z(), a / b.w()};
}

template<typename T>
inline T dot(vec4<T> a, vec4<T> b) {
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z() + a.w() * b.w();
}

template<typename T>
inline T length(vec4<T> v) {
    return std::sqrt(dot(v, v));
}

template<typename T>
inline vec4<T> normalize(vec4<T> v) {
    return v * (static_cast<T>(1) / length(v));
}

} // math
} // vuray
