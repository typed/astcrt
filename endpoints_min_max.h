#ifndef ASTC_ENDPOINTS_MIN_MAX_H_
#define ASTC_ENDPOINTS_MIN_MAX_H_

#ifdef RTTC_USE_ASTCRT

#include <algorithm>
#include <cstddef>

#include "colors.h"
#include "constants.h"
#include "dcheck.h"
#include "misc.h"
#include "vector.h"

inline void find_min_max(const unorm8_t texels[BLOCK_TEXEL_COUNT], const vec3f_t& line_k, vec3f_t line_m, vec3f_t& e0, vec3f_t& e1) {
    const size_t count = BLOCK_TEXEL_COUNT;
    //DCHECK(count <= BLOCK_TEXEL_COUNT);
    DCHECK(approx_equal(quadrance(line_k), 1.0, 0.0001f));

    float a, b;
    {
        float t = dot(to_vec3f(texels[0]) - line_m, line_k);
        a = t;
        b = t;
    }

    for (size_t i = 1; i < count; ++i) {
        float t = dot(to_vec3f(texels[i]) - line_m, line_k);
        a = std::min(a, t);
        b = std::max(b, t);
    }

    e0 = clamp_rgb(line_k * a + line_m);
    e1 = clamp_rgb(line_k * b + line_m);
}

//suppost alpha

inline void find_min_max(const unorm8_t texels[BLOCK_TEXEL_COUNT], const vec4f_t& line_k, const vec4f_t& line_m, vec4f_t& e0, vec4f_t& e1) {

    const size_t count = BLOCK_TEXEL_COUNT;
    //DCHECK(count <= BLOCK_TEXEL_COUNT);
    DCHECK(approx_equal(quadrance(line_k), 1.0, 0.0001f));

    float a, b;
    {
        float t = dot(to_vec4f(texels[0]) - line_m, line_k);
        a = t;
        b = t;
    }

    for (size_t i = 1; i < count; ++i) {
        float t = dot(to_vec4f(texels[i]) - line_m, line_k);
        a = std::min(a, t);
        b = std::max(b, t);
    }

    e0 = clamp_rgba(line_k * a + line_m);
    e1 = clamp_rgba(line_k * b + line_m);
}

#endif

#endif  // ASTC_ENDPOINTS_MIN_MAX_H_
