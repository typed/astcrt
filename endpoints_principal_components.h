#ifndef ASTC_ENDPOINTS_PRINCIPAL_COMPONENTS_H_
#define ASTC_ENDPOINTS_PRINCIPAL_COMPONENTS_H_

#ifdef RTTC_USE_ASTCRT

#include <cstddef>

#include "colors.h"
#include "constants.h"
#include "vector.h"

void principal_component_analysis(const unorm8_t texels[BLOCK_TEXEL_COUNT], vec3f_t& line_k, vec3f_t& line_m);

void principal_component_analysis(const unorm8_t texels[BLOCK_TEXEL_COUNT], vec4f_t& line_k, vec4f_t& line_m);

#endif

#endif  // ASTC_ENDPOINTS_PRINCIPAL_COMPONENTS_H_
