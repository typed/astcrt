#ifndef ASTC_MATRIX_H_
#define ASTC_MATRIX_H_

#ifdef RTTC_USE_ASTCRT

#include <cstddef>

#include "vector.h"

struct mat3x3f_t {
public:
    mat3x3f_t() {}

    mat3x3f_t(
        float m00,
        float m01,
        float m02,
        float m10,
        float m11,
        float m12,
        float m20,
        float m21,
        float m22) {
        m[0] = vec3f_t(m00, m01, m02);
        m[1] = vec3f_t(m10, m11, m12);
        m[2] = vec3f_t(m20, m21, m22);
    }

    const vec3f_t& row(size_t i) const { return m[i]; }

    float& at(size_t i, size_t j) { return m[i].components[j]; }
    const float& at(size_t i, size_t j) const { return m[i].components[j]; }

private:
    vec3f_t m[3];
};

inline vec3f_t operator*(const mat3x3f_t& a, const vec3f_t& b) {
    vec3f_t tmp;
    tmp.x = dot(a.row(0), b);
    tmp.y = dot(a.row(1), b);
    tmp.z = dot(a.row(2), b);
    return tmp;
}

inline void eigen_vector(const mat3x3f_t& a, vec3f_t& eig) {
    vec3f_t b = signorm(vec3f_t(1, 3, 2));  // FIXME: Magic number
    for (size_t i = 0; i < 8; ++i) {
        b = signorm(a * b);
    }
    eig = b;
}

struct mat4x4f_t {
public:
    mat4x4f_t() {}

    mat4x4f_t(
        float m00,
        float m01,
        float m02,
        float m03,
        float m10,
        float m11,
        float m12,
        float m13,
        float m20,
        float m21,
        float m22,
        float m23,
        float m30,
        float m31,
        float m32,
        float m33) {
        m[0] = vec4f_t(m00, m01, m02, m03);
        m[1] = vec4f_t(m10, m11, m12, m13);
        m[2] = vec4f_t(m20, m21, m22, m23);
        m[3] = vec4f_t(m30, m31, m32, m33);
    }

    const vec4f_t& row(size_t i) const { return m[i]; }

    float& at(size_t i, size_t j) { return m[i].components[j]; }
    const float& at(size_t i, size_t j) const { return m[i].components[j]; }

private:
    vec4f_t m[4];
};

inline vec4f_t operator*(const mat4x4f_t& a, const vec4f_t& b) {
    vec4f_t tmp;
    tmp.x = dot(a.row(0), b);
    tmp.y = dot(a.row(1), b);
    tmp.z = dot(a.row(2), b);
    tmp.w = dot(a.row(3), b);
    return tmp;
}

inline void eigen_vector(const mat4x4f_t& a, vec4f_t& eig) {
    vec4f_t b = signorm(vec4f_t(1, 3, 2, 4));  // FIXME: Magic number
    for (size_t i = 0; i < 8; ++i) {
        b = signorm(a * b);
    }
    eig = b;
}

#endif

#endif  // ASTC_MATRIX_H_
