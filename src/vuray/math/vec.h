//
// vec.h
// ~~~~~
// Vector math.
//
// Author: hm2code
//
#pragma once
#include <array>
#include <cstddef>
#include <cmath>

namespace vuray {
namespace math {

// Vector element indeces.
enum { X = 0, Y, Z, W };

// A generic vector of `SIZE` elements of type `T`.
template<typename T, std::size_t SIZE>
struct vec {
public:
    vec() {}
    template<typename... TT>
    constexpr vec(TT... values) : data{values...} {}

    constexpr T x() const { return data[X]; }
    constexpr void set_x(T x) { data[X] = x; }

    constexpr T y() const {
        static_assert(SIZE > 1, "Need a 2 element vector or higher");
        return data[Y];
    }
    constexpr void set_y(T y) {
        static_assert(SIZE > 1, "Need a 2 element vector or higher");
        data[Y] = y;
    }

    constexpr T z() const {
        static_assert(SIZE > 2, "Need a 3 element vector or higher");
        return data[Z];
    }
    constexpr void set_z(T z) {
        static_assert(SIZE > 2, "Need a 3 element vector or higher");
        data[Z] = z;
    }

    constexpr T w() const {
        static_assert(SIZE > 3, "Need a 4 element vector or higher");
        return data[W];
    }
    constexpr void set_w(T w) {
        static_assert(SIZE > 3, "Need a 4 element vector or higher");
        data[W] = w;
    }

    template<typename TT>
    constexpr vec<T, SIZE>& operator +=(vec<TT, SIZE> v) {
        for (auto i = 0; i < SIZE; ++i) {
            data[i] += v.data[i];
        }
        return *this;
    }

    template<typename TT>
    constexpr vec<T, SIZE>& operator -=(vec<TT, SIZE> v) {
        for (auto i = 0; i < SIZE; ++i) {
            data[i] -= v.data[i];
        }
        return *this;
    }

    template<typename TT>
    constexpr vec<T, SIZE>& operator *=(vec<TT, SIZE> v) {
        for (auto i = 0; i < SIZE; ++i) {
            data[i] *= v.data[i];
        }
        return *this;
    }

    template<typename TT>
    constexpr vec<T, SIZE>& operator /=(vec<TT, SIZE> v) {
        for (auto i = 0; i < SIZE; ++i) {
            data[i] /= v.data[i];
        }
        return *this;
    }

    template<typename TT>
    constexpr vec<T, SIZE>& operator +=(TT s) {
        for (auto i = 0; i < SIZE; ++i) {
            data[i] += s;
        }
        return *this;
    }

    template<typename TT>
    constexpr vec<T, SIZE>& operator -=(TT s) {
        for (auto i = 0; i < SIZE; ++i) {
            data[i] -= s;
        }
        return *this;
    }

    template<typename TT>
    constexpr vec<T, SIZE>& operator *=(TT s) {
        for (auto i = 0; i < SIZE; ++i) {
            data[i] *= s;
        }
        return *this;
    }

    template<typename TT>
    constexpr vec<T, SIZE>& operator /=(TT s) {
        for (auto i = 0; i < SIZE; ++i) {
            data[i] /= s;
        }
        return *this;
    }

    constexpr T dot(vec<T, SIZE> v) const {
        T acc = 0;
        for (auto i = 0; i < SIZE; ++i) {
            acc += data[i] * v.data[i];
        }
        return acc;
    }

    constexpr T length_sq() const {
        T acc = 0;
        for (auto i = 0; i < SIZE; ++i) {
            acc += data[i] * data[i];
        }
        return acc;
    }

    T length() const { return std::sqrt(length_sq()); }

    vec<T, SIZE> normalized() const {
        vec<T, SIZE> result{*this};
        return result *= static_cast<T>(1) / length();
    }

private:
    T data[SIZE];
};

template<typename T, std::size_t SIZE>
constexpr vec<T, SIZE> operator +(vec<T, SIZE> a, vec<T, SIZE> b) {
    return a += b;
}

template<typename T, std::size_t SIZE>
constexpr vec<T, SIZE> operator +(vec<T, SIZE> v, T s) {
    return v += s;
}

template<typename T, std::size_t SIZE>
constexpr vec<T, SIZE> operator +(T s, vec<T, SIZE> v) {
    return v += s;
}

template<typename T, std::size_t SIZE>
constexpr vec<T, SIZE> operator -(vec<T, SIZE> a, vec<T, SIZE> b) {
    return a -= b;
}

template<typename T, std::size_t SIZE>
constexpr vec<T, SIZE> operator -(vec<T, SIZE> v, T s) {
    return v -= s;
}

template<typename T, std::size_t SIZE>
constexpr vec<T, SIZE> operator *(vec<T, SIZE> a, vec<T, SIZE> b) {
    return a *= b;
}

template<typename T, std::size_t SIZE>
constexpr vec<T, SIZE> operator *(vec<T, SIZE> v, T s) {
    return v *= s;
}

template<typename T, std::size_t SIZE>
constexpr vec<T, SIZE> operator *(T s, vec<T, SIZE> v) {
    return v *= s;
}

template<typename T, std::size_t SIZE>
constexpr vec<T, SIZE> operator /(vec<T, SIZE> a, vec<T, SIZE> b) {
    return a /= b;
}

template<typename T, std::size_t SIZE>
constexpr vec<T, SIZE> operator /(vec<T, SIZE> v, T s) {
    return v /= s;
}

} // math
} // vuray
