#ifndef ASTC_VECTOR_H_
#define ASTC_VECTOR_H_

#ifdef RTTC_USE_ASTCRT

#include <algorithm>
#include <cmath>

#include "dcheck.h"

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4201)
#endif

template <typename T>
union vec3_t {
public:
    vec3_t() {}
    vec3_t(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

    struct {
        T x, y, z;
    };
    struct {
        T r, g, b;
    };
    T components[3];
};

typedef vec3_t<float> vec3f_t;
typedef vec3_t<int> vec3i_t;

template <typename T>
inline vec3_t<T> operator+(const vec3_t<T>& a, const vec3_t<T>& b) {
    vec3_t<T> result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

template <typename T>
inline vec3_t<T> operator-(const vec3_t<T>& a, const vec3_t<T>& b) {
    vec3_t<T> result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

template <typename T>
inline vec3_t<T> operator*(const vec3_t<T>& a, const vec3_t<T>& b) {
    vec3_t<T> result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    return result;
}

template <typename T>
inline vec3_t<T> operator*(const vec3_t<T>& a, T b) {
    vec3_t<T> result;
    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    return result;
}

template <typename T>
inline vec3_t<T> operator/(const vec3_t<T>& a, T b) {
    vec3_t<T> result;
    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;
    return result;
}

template <typename T>
inline vec3_t<T> operator/(const vec3_t<T>& a, const vec3_t<T>& b) {
    vec3_t<T> result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    result.z = a.z / b.z;
    return result;
}

template <typename T>
inline bool operator==(const vec3_t<T>& a, const vec3_t<T>& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

template <typename T>
inline bool operator!=(const vec3_t<T>& a, const vec3_t<T>& b) {
    return a.x != b.x || a.y != b.y || a.z != b.z;
}

template <typename T>
inline T dot(const vec3_t<T>& a, const vec3_t<T>& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
inline T quadrance(const vec3_t<T>& a) {
    return dot(a, a);
}

template <typename T>
inline T norm(const vec3_t<T>& a) {
    return static_cast<T>(sqrt(quadrance(a)));
}

template <typename T>
inline T distance(const vec3_t<T>& a, const vec3_t<T>& b) {
    return norm(a - b);
}

template <typename T>
inline T qd(const vec3_t<T>& a, const vec3_t<T>& b) {
    return quadrance(a - b);
}

template <typename T>
inline vec3_t<T> signorm(const vec3_t<T>& a) {
    T x = norm(a);
    DCHECK(x != 0.0);
    return a / x;
}

template <typename T>
inline vec3_t<T> vecmin(const vec3_t<T>& a, const vec3_t<T>& b) {
    vec3_t<T> result;
    result.x = std::min(a.x, b.x);
    result.y = std::min(a.y, b.y);
    result.z = std::min(a.z, b.z);
    return result;
}

template <typename T>
inline vec3_t<T> vecmax(const vec3_t<T>& a, const vec3_t<T>& b) {
    vec3_t<T> result;
    result.x = std::max(a.x, b.x);
    result.y = std::max(a.y, b.y);
    result.z = std::max(a.z, b.z);
    return result;
}

template <typename T>
inline T qd_to_line(const vec3_t<T>& m, const vec3_t<T>& k, T kk, const vec3_t<T>& p) {
    T t = dot(p - m, k) / kk;
    vec3_t<T> q = k * t + m;
    return qd(p, q);
}

//suppost alpha

template <typename T>
union vec4_t {
public:
    vec4_t() {}
    vec4_t(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}

    struct {
        T x, y, z, w;
    };
    struct {
        T r, g, b, a;
    };
    T components[4];
};

typedef vec4_t<float> vec4f_t;
typedef vec4_t<int> vec4i_t;

template <typename T>
inline vec4_t<T> operator+(const vec4_t<T>& a, const vec4_t<T>& b) {
    vec4_t<T> result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}

template <typename T>
inline vec4_t<T> operator-(const vec4_t<T>& a, const vec4_t<T>& b) {
    vec4_t<T> result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}

template <typename T>
inline vec4_t<T> operator*(const vec4_t<T>& a, const vec4_t<T>& b) {
    vec4_t<T> result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    result.w = a.w * b.w;
    return result;
}

template <typename T>
inline vec4_t<T> operator*(const vec4_t<T>& a, T b) {
    vec4_t<T> result;
    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;
    return result;
}

template <typename T>
inline vec4_t<T> operator/(const vec4_t<T>& a, T b) {
    vec4_t<T> result;
    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;
    result.w = a.w / b;
    return result;
}

template <typename T>
inline vec4_t<T> operator/(const vec4_t<T>& a, const vec4_t<T>& b) {
    vec4_t<T> result;
    result.x = a.x / b.x;
    result.y = a.y / b.y;
    result.z = a.z / b.z;
    result.w = a.w / b.w;
    return result;
}

template <typename T>
inline bool operator==(const vec4_t<T>& a, const vec4_t<T>& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

template <typename T>
inline bool operator!=(const vec4_t<T>& a, const vec4_t<T>& b) {
    return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w;
}

template <typename T>
inline T dot(const vec4_t<T>& a, const vec4_t<T>& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template <typename T>
inline T quadrance(const vec4_t<T>& a) {
    return dot(a, a);
}

template <typename T>
inline T norm(const vec4_t<T>& a) {
    return static_cast<T>(sqrt(quadrance(a)));
}

template <typename T>
inline T distance(const vec4_t<T>& a, const vec4_t<T>& b) {
    return norm(a - b);
}

template <typename T>
inline T qd(const vec4_t<T>& a, const vec4_t<T>& b) {
    return quadrance(a - b);
}

template <typename T>
inline vec4_t<T> signorm(const vec4_t<T>& a) {
    T x = norm(a);
    DCHECK(x != 0.0);
    return a / x;
}

template <typename T>
inline vec4_t<T> vecmin(const vec4_t<T>& a, const vec4_t<T>& b) {
    vec4_t<T> result;
    result.x = std::min(a.x, b.x);
    result.y = std::min(a.y, b.y);
    result.z = std::min(a.z, b.z);
    result.w = std::min(a.w, b.w);
    return result;
}

template <typename T>
inline vec4_t<T> vecmax(const vec4_t<T>& a, const vec4_t<T>& b) {
    vec4_t<T> result;
    result.x = std::max(a.x, b.x);
    result.y = std::max(a.y, b.y);
    result.z = std::max(a.z, b.z);
    result.w = std::max(a.w, b.w);
    return result;
}

template <typename T>
inline T qd_to_line(const vec4_t<T>& m, const vec4_t<T>& k, T kk, const vec4_t<T>& p) {
    T t = dot(p - m, k) / kk;
    vec4_t<T> q = k * t + m;
    return qd(p, q);
}

#ifdef _MSC_VER
#   pragma warning(pop)
#endif

#endif

#endif  // ASTC_VECTOR_H_
