#ifndef ASTC_ENDPOINTS_BOUNDING_BOX_H_
#define ASTC_ENDPOINTS_BOUNDING_BOX_H_

#ifdef RTTC_USE_ASTCRT

#include <cstddef>

#include "colors.h"
#include "constants.h"
#include "misc.h"
#include "vector.h"

inline void bounding_box(const unorm8_t* texels, size_t count, vec3i_t& e0, vec3i_t& e1) {
    vec3i_t a(255, 255, 255);
    vec3i_t b(0, 0, 0);
    for (size_t i = 0; i < count; ++i) {
        vec3i_t t = to_vec3i(texels[i]);
        a = vecmin(a, t);
        b = vecmax(b, t);
    }
    e0 = a;
    e1 = b;
}

inline void bounding_box_block(const unorm8_t texels[BLOCK_TEXEL_COUNT], vec3i_t& e0, vec3i_t& e1) {
    bounding_box(texels, BLOCK_TEXEL_COUNT, e0, e1);
}

#endif

#endif  // ASTC_ENDPOINTS_BOUNDING_BOX_H_
