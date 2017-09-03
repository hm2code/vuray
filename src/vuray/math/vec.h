//
// vec.h
// ~~~~~
// Vector math.
//
// Author: hm2code
//
#pragma once
#include <type_traits>

namespace vuray {
namespace math {

// Vector element indeces.
enum { X = 0, Y, Z, W };

// Color element indeces.
enum { R = 0, G, B, A };

// Vector data storage with a pointer-like interface.
template<typename T, int SIZE>
class vec_data {
public:
    operator const T*() const { return data; }
    operator T*() { return data; }

private:
    T data[SIZE];
};

// A (very) generic vector.
template<typename T, int SIZE, typename DATA>
struct vec {
public:
    T x() const { return data[X]; }
    void set_x(T x) { data[X] = x; }

    T y() const {
        static_assert(SIZE > 1, "Need a 2 element vector or higher");
        return data[Y];
    }
    void set_y(T y) {
        static_assert(SIZE > 1, "Need a 2 element vector or higher");
        data[Y] = y;
    }

    T z() const {
        static_assert(SIZE > 2, "Need a 3 element vector or higher");
        return data[Z];
    }
    void set_z(T z) {
        static_assert(SIZE > 2, "Need a 3 element vector or higher");
        data[Z] = z;
    }

    T w() const {
        static_assert(SIZE > 3, "Need a 4 element vector or higher");
        return data[W];
    }
    void set_w(T w) {
        static_assert(SIZE > 3, "Need a 4 element vector or higher");
        data[W] = w;
    }

    template<typename TT, typename D>
    vec<T, SIZE, DATA>& operator +=(const vec<TT, SIZE, D> v) {
        for (int i = 0; i < SIZE; ++i) {
            data[i] += v.data[i];
        }
        return *this;
    }

    template<typename TT, typename D>
    vec<T, SIZE, DATA>& operator -=(const vec<TT, SIZE, D> v) {
        for (int i = 0; i < SIZE; ++i) {
            data[i] -= v.data[i];
        }
        return *this;
    }

    template<typename TT, typename D>
    vec<T, SIZE, DATA>& operator *=(const vec<TT, SIZE, D> v) {
        for (int i = 0; i < SIZE; ++i) {
            data[i] *= v.data[i];
        }
        return *this;
    }

    template<typename TT, typename D>
    vec<T, SIZE, DATA>& operator /=(const vec<TT, SIZE, D> v) {
        for (int i = 0; i < SIZE; ++i) {
            data[i] /= v.data[i];
        }
        return *this;
    }

private:
    DATA data;
};

} // math
} // vuray
