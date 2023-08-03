#ifndef ASTC_ENDPOINTS_PRINCIPAL_COMPONENTS_H_
#define ASTC_ENDPOINTS_PRINCIPAL_COMPONENTS_H_

#ifdef RTTC_USE_ASTCRT

#include <cstddef>

#include "colors.h"
#include "constants.h"
#include "dcheck.h"
#include "matrix.h"
#include "vector.h"

inline vec3f_t mean(const unorm8_t texels[BLOCK_TEXEL_COUNT], size_t count) {
    vec3i_t sum(0, 0, 0);
    for (size_t i = 0; i < count; ++i) {
        sum = sum + to_vec3i(texels[i]);
    }

    return to_vec3f(sum) / static_cast<float>(count);
}

inline void subtract(const unorm8_t texels[BLOCK_TEXEL_COUNT], size_t count, vec3f_t v, vec3f_t output[BLOCK_TEXEL_COUNT]) {
    for (size_t i = 0; i < count; ++i) {
        output[i] = to_vec3f(texels[i]) - v;
    }
}

inline mat3x3f_t covariance(const vec3f_t m[BLOCK_TEXEL_COUNT], size_t count) {
    mat3x3f_t cov;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            float s = 0;
            for (size_t k = 0; k < count; ++k) {
                s += m[k].components[i] * m[k].components[j];
            }
            cov.at(i, j) = s / static_cast<float>(count - 1);
        }
    }
    return cov;
}

inline void principal_component_analysis(const unorm8_t texels[BLOCK_TEXEL_COUNT], vec3f_t& line_k, vec3f_t& line_m) {
    // Since we are working with fixed sized blocks count we can cap count. This
    // avoids dynamic allocation.
    //DCHECK(count <= BLOCK_TEXEL_COUNT);

    int count = BLOCK_TEXEL_COUNT;

    line_m = mean(texels, count);

    vec3f_t n[BLOCK_TEXEL_COUNT];
    subtract(texels, count, line_m, n);

    mat3x3f_t w = covariance(n, count);

    eigen_vector(w, line_k);
}

//suppost alpha

inline vec4f_t mean_alpha(const unorm8_t texels[BLOCK_TEXEL_COUNT], size_t count) {
    vec4i_t sum(0, 0, 0, 0);
    for (size_t i = 0; i < count; ++i) {
        sum = sum + to_vec4i(texels[i]);
    }
    return to_vec4f(sum) / static_cast<float>(count);
}

inline mat4x4f_t covariance(const vec4f_t m[BLOCK_TEXEL_COUNT], size_t count) {
    mat4x4f_t cov;
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            float s = 0;
            for (size_t k = 0; k < count; ++k) {
                s += m[k].components[i] * m[k].components[j];
            }
            cov.at(i, j) = s / static_cast<float>(count - 1);
        }
    }
    return cov;
}

inline void subtract(const unorm8_t texels[BLOCK_TEXEL_COUNT], size_t count, vec4f_t v, vec4f_t output[BLOCK_TEXEL_COUNT]) {
    for (size_t i = 0; i < count; ++i) {
        output[i] = to_vec4f(texels[i]) - v;
    }
}

inline void principal_component_analysis(const unorm8_t texels[BLOCK_TEXEL_COUNT], vec4f_t& line_k, vec4f_t& line_m) {
    // Since we are working with fixed sized blocks count we can cap count. This
    // avoids dynamic allocation.
    //DCHECK(count <= BLOCK_TEXEL_COUNT);

    int count = BLOCK_TEXEL_COUNT;

    line_m = mean_alpha(texels, count);

    vec4f_t n[BLOCK_TEXEL_COUNT];
    subtract(texels, count, line_m, n);

    mat4x4f_t w = covariance(n, count);

    eigen_vector(w, line_k);
}

#endif

#endif  // ASTC_ENDPOINTS_PRINCIPAL_COMPONENTS_H_
