#ifndef ASTC_COLORS_H_
#define ASTC_COLORS_H_

#ifdef RTTC_USE_ASTCRT

#include <math.h>
#include <cstdint>

#include "misc.h"
#include "vector.h"

const int APPROX_COLOR_EPSILON = 50;

union unorm8_t {
    struct RgbaColorType {
        uint8_t b, g, r, a;
    } channels;
    uint8_t components[4];
    uint32_t bits;
};

union unorm16_t {
    struct RgbaColorType {
        uint16_t b, g, r, a;
    } channels;
    uint16_t components[4];
    uint64_t bits;
};

inline bool is_greyscale(const vec3i_t& color) {
    // integer equality is transitive
    return color.r == color.g && color.g == color.b;
}

inline int luminance(const vec3i_t& color) {
    return (color.r + color.g + color.b) / 3;
}

inline bool approx_equal(const vec3i_t& a, const vec3i_t& b) {
    return quadrance(a - b) <= APPROX_COLOR_EPSILON;
}

inline vec3i_t clamp_rgb(const vec3i_t& color) {
    vec3i_t result;
    result.r = clamp(0, 255, color.r);
    result.g = clamp(0, 255, color.g);
    result.b = clamp(0, 255, color.b);
    return result;
}

inline vec3f_t clamp_rgb(const vec3f_t& color) {
    vec3f_t result;
    result.r = clamp(0.0f, 255.0f, color.r);
    result.g = clamp(0.0f, 255.0f, color.g);
    result.b = clamp(0.0f, 255.0f, color.b);
    return result;
}

inline vec3i_t floor(const vec3f_t& color) {
    vec3i_t result;
    result.r = static_cast<int>(floor(color.r));
    result.g = static_cast<int>(floor(color.g));
    result.b = static_cast<int>(floor(color.b));
    return result;
}

inline vec3i_t round(const vec3f_t& color) {
    vec3i_t result;
    result.r = static_cast<int>(round(color.r));
    result.g = static_cast<int>(round(color.g));
    result.b = static_cast<int>(round(color.b));
    return result;
}

inline vec3i_t to_vec3i(const unorm8_t& color) {
    vec3i_t result;
    result.r = color.channels.r;
    result.g = color.channels.g;
    result.b = color.channels.b;
    return result;
}

inline vec3i_t to_vec3i(const vec3f_t& color) {
    vec3i_t result;
    result.r = static_cast<int>(color.r);
    result.g = static_cast<int>(color.g);
    result.b = static_cast<int>(color.b);
    return result;
}

inline vec3f_t to_vec3f(const unorm8_t& color) {
    vec3f_t result;
    result.r = color.channels.r;
    result.g = color.channels.g;
    result.b = color.channels.b;
    return result;
}

inline vec3f_t to_vec3f(const vec3i_t& color) {
    vec3f_t result;
    result.r = static_cast<float>(color.r);
    result.g = static_cast<float>(color.g);
    result.b = static_cast<float>(color.b);
    return result;
}

inline unorm8_t to_unorm8(const vec3i_t& color) {
    unorm8_t result;
    result.channels.r = static_cast<uint8_t>(color.r);
    result.channels.g = static_cast<uint8_t>(color.g);
    result.channels.b = static_cast<uint8_t>(color.b);
    result.channels.a = 255;
    return result;
}

inline unorm16_t unorm8_to_unorm16(const unorm8_t& c8) {
    // (x / 255) * (2^16-1) = x * 65535 / 255 = x * 257
    unorm16_t result;
    result.channels.r = static_cast<uint16_t>(c8.channels.r * 257);
    result.channels.g = static_cast<uint16_t>(c8.channels.g * 257);
    result.channels.b = static_cast<uint16_t>(c8.channels.b * 257);
    result.channels.a = static_cast<uint16_t>(c8.channels.a * 257);
    return result;
}

//suppost alpha

inline bool approx_equal(const vec4i_t& a, const vec4i_t& b) {
    return quadrance(a - b) <= APPROX_COLOR_EPSILON;
}

inline vec4i_t clamp_rgba(const vec4i_t& color) {
    vec4i_t result;
    result.r = clamp(0, 255, color.r);
    result.g = clamp(0, 255, color.g);
    result.b = clamp(0, 255, color.b);
    result.a = clamp(0, 255, color.a);
    return result;
}

inline vec4f_t clamp_rgba(const vec4f_t& color) {
    vec4f_t result;
    result.r = clamp(0.0f, 255.0f, color.r);
    result.g = clamp(0.0f, 255.0f, color.g);
    result.b = clamp(0.0f, 255.0f, color.b);
    result.a = clamp(0.0f, 255.0f, color.a);
    return result;
}

inline vec4i_t floor(const vec4f_t& color) {
    vec4i_t result;
    result.r = static_cast<int>(floor(color.r));
    result.g = static_cast<int>(floor(color.g));
    result.b = static_cast<int>(floor(color.b));
    result.a = static_cast<int>(floor(color.a));
    return result;
}

inline vec4i_t round(const vec4f_t& color) {
    vec4i_t result;
    result.r = static_cast<int>(round(color.r));
    result.g = static_cast<int>(round(color.g));
    result.b = static_cast<int>(round(color.b));
    result.a = static_cast<int>(round(color.a));
    return result;
}

inline vec4i_t to_vec4i(const unorm8_t& color) {
    vec4i_t result;
    result.r = color.channels.r;
    result.g = color.channels.g;
    result.b = color.channels.b;
    result.a = color.channels.a;
    return result;
}

inline vec4i_t to_vec4i(const vec4f_t& color) {
    vec4i_t result;
    result.r = static_cast<int>(color.r);
    result.g = static_cast<int>(color.g);
    result.b = static_cast<int>(color.b);
    result.a = static_cast<int>(color.a);
    return result;
}

inline vec4f_t to_vec4f(const unorm8_t& color) {
    vec4f_t result;
    result.r = color.channels.r;
    result.g = color.channels.g;
    result.b = color.channels.b;
    result.a = color.channels.a;
    return result;
}

inline vec4f_t to_vec4f(const vec4i_t& color) {
    vec4f_t result;
    result.r = static_cast<float>(color.r);
    result.g = static_cast<float>(color.g);
    result.b = static_cast<float>(color.b);
    result.a = static_cast<float>(color.a);
    return result;
}

inline unorm8_t to_unorm8(const vec4i_t& color) {
    unorm8_t result;
    result.channels.r = static_cast<uint8_t>(color.r);
    result.channels.g = static_cast<uint8_t>(color.g);
    result.channels.b = static_cast<uint8_t>(color.b);
    result.channels.a = static_cast<uint8_t>(color.a);
    return result;
}

#endif

#endif  // ASTC_COLORS_H_
