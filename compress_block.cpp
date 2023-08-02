#ifdef RTTC_USE_ASTCRT

#include "compress_block.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>

#include "colors.h"
#include "constants.h"
#include "data_size.h"
#include "endpoints.h"
#include "endpoints_encode.h"
#include "endpoints_min_max.h"
#include "endpoints_principal_components.h"
#include "integer_sequence_encoding.h"
#include "misc.h"
#include "range.h"
#include "store_block.h"
#include "vector.h"
#include "weights_quantize.h"

/**
 * Write void extent block bits for LDR mode and unused extent coordinates.
 */
inline void encode_void_extent(vec3i_t color, PhysicalBlock* physical_block) {
    void_extent_to_physical(unorm8_to_unorm16(to_unorm8(color)), physical_block);
}

inline void encode_luminance(const uint8_t texels[BLOCK_TEXEL_COUNT], PhysicalBlock* physical_block) {
    size_t partition_count = 1;
    size_t partition_index = 0;

    color_endpoint_mode_t color_endpoint_mode = CEM_LDR_LUMINANCE_DIRECT;
    range_t weight_quant = RANGE_32;
    range_t endpoint_quant = endpoint_quantization(partition_count, weight_quant, color_endpoint_mode); //RANGE_256

    uint8_t l0 = 255;
    uint8_t l1 = 0;
    for (size_t i = 0; i < BLOCK_TEXEL_COUNT; ++i) {
        l0 = std::min(l0, texels[i]);
        l1 = std::max(l1, texels[i]);
    }

    uint8_t endpoint_unquantized[2];
    uint8_t endpoint_quantized[2];
    encode_luminance_direct(endpoint_quant, l0, l1, endpoint_quantized, endpoint_unquantized);

    uint8_t weights_quantized[BLOCK_TEXEL_COUNT];
    calculate_quantized_weights_luminance(texels, weight_quant, endpoint_unquantized[0], endpoint_unquantized[1], weights_quantized);

    const size_t endpoint_ise_count = MAXIMUM_ENCODED_COLOR_ENDPOINT_BYTES;
    uint8_t endpoint_ise[endpoint_ise_count] = {0};
    integer_sequence_encode(endpoint_quantized, 2, endpoint_quant, endpoint_ise);

    const size_t weights_ise_count = MAXIMUM_ENCODED_WEIGHT_BYTES;
    uint8_t weights_ise[weights_ise_count + 1] = {0};
    integer_sequence_encode(weights_quantized, BLOCK_TEXEL_COUNT, RANGE_32, weights_ise);

    symbolic_to_physical2(color_endpoint_mode, endpoint_quant, weight_quant, partition_count, partition_index, endpoint_ise, endpoint_ise_count, weights_ise, weights_ise_count, physical_block);
}

inline void encode_rgb_single_partition(const unorm8_t texels[BLOCK_TEXEL_COUNT], vec3f_t e0, vec3f_t e1, PhysicalBlock* physical_block) {
    size_t partition_index = 0;
    size_t partition_count = 1;

    color_endpoint_mode_t color_endpoint_mode = CEM_LDR_RGB_DIRECT;
    range_t weight_quant = RANGE_12;
    range_t endpoint_quant = endpoint_quantization(partition_count, weight_quant, color_endpoint_mode); //RANGE_256

    vec3i_t endpoint_unquantized[2];
    const size_t endpoint_quantized_count = 6;
    uint8_t endpoint_quantized[endpoint_quantized_count];
    encode_rgb_direct(endpoint_quant, round(e0), round(e1), endpoint_quantized, endpoint_unquantized);

    uint8_t weights_quantized[BLOCK_TEXEL_COUNT];
    calculate_quantized_weights_rgb(texels, weight_quant, endpoint_unquantized[0], endpoint_unquantized[1], weights_quantized);

    const size_t endpoint_ise_count = MAXIMUM_ENCODED_COLOR_ENDPOINT_BYTES;
    uint8_t endpoint_ise[endpoint_ise_count] = {0};
    integer_sequence_encode(endpoint_quantized, endpoint_quantized_count, endpoint_quant, endpoint_ise);

    const size_t weights_ise_count = MAXIMUM_ENCODED_WEIGHT_BYTES;
    uint8_t weights_ise[weights_ise_count + 1] = {0};
    integer_sequence_encode(weights_quantized, BLOCK_TEXEL_COUNT, weight_quant, weights_ise);

    symbolic_to_physical2(color_endpoint_mode, endpoint_quant, weight_quant, partition_count, partition_index, endpoint_ise, endpoint_ise_count, weights_ise, weights_ise_count, physical_block);
}

//是否为相同颜色
inline bool is_solid(const unorm8_t texels[BLOCK_TEXEL_COUNT], vec3i_t& color) {
    color = vec3i_t(0, 0, 0);
    for (size_t i = 0; i < BLOCK_TEXEL_COUNT; ++i) {
        if (!approx_equal(to_vec3i(texels[i]), to_vec3i(texels[0]))) {
            return false;
        }
        color.r += texels[i].channels.r;
        color.g += texels[i].channels.g;
        color.b += texels[i].channels.b;
    }
    color.r = clamp<int>(0, 255, color.r / BLOCK_TEXEL_COUNT);
    color.g = clamp<int>(0, 255, color.g / BLOCK_TEXEL_COUNT);
    color.b = clamp<int>(0, 255, color.b / BLOCK_TEXEL_COUNT);
    return true;
}

//是否为灰度
inline bool is_greyscale(const unorm8_t texels[BLOCK_TEXEL_COUNT], uint8_t luminances[BLOCK_TEXEL_COUNT]) {
    for (size_t i = 0; i < BLOCK_TEXEL_COUNT; ++i) {
        vec3i_t color = to_vec3i(texels[i]);
        luminances[i] = static_cast<uint8_t>(luminance(color));
        vec3i_t lum(luminances[i], luminances[i], luminances[i]);
        if (!approx_equal(color, lum)) {
            return false;
        }
    }
    return true;
}

void compress_block(const unorm8_t texels[BLOCK_TEXEL_COUNT], PhysicalBlock* physical_block) {
    {
        vec3i_t color;
        if (is_solid(texels, color)) {
            encode_void_extent(color, physical_block);
            /* encode_void_extent(vec3i_t(0, 0, 0), physical_block); */
            return;
        }
    }

    {
        uint8_t luminances[BLOCK_TEXEL_COUNT];
        if (is_greyscale(texels, luminances)) {
            encode_luminance(luminances, physical_block);
            /* encode_void_extent(vec3i_t(255, 0, 0), physical_block); */
            return;
        }
    }

    vec3f_t k, m;
    principal_component_analysis(texels, k, m);
    vec3f_t e0, e1;
    find_min_max(texels, k, m, e0, e1);
    encode_rgb_single_partition(texels, e0, e1, physical_block);
    /* encode_void_extent(vec3i_t(0, 255, 0), physical_block); */
}

//suppost alpha

inline void encode_void_extent(vec4i_t color, PhysicalBlock* physical_block) {
    void_extent_to_physical(unorm8_to_unorm16(to_unorm8(color)), physical_block);
}

//是否为全透明
inline bool is_alpha0(const unorm8_t texels[BLOCK_TEXEL_COUNT], vec4i_t& color) {
    color = vec4i_t(0, 0, 0, 0);
    for (size_t i = 0; i < BLOCK_TEXEL_COUNT; ++i) {
        if (texels[i].channels.a > 0) {
            return false;
        }
        color.r += texels[i].channels.r;
        color.g += texels[i].channels.g;
        color.b += texels[i].channels.b;
    }
    color = clamp_rgba(color);
    return true;
}

inline void encode_rgba_single_partition(const unorm8_t texels[BLOCK_TEXEL_COUNT], vec4f_t e0, vec4f_t e1, PhysicalBlock* physical_block) {
    size_t partition_index = 0;
    size_t partition_count = 1;

    color_endpoint_mode_t color_endpoint_mode = CEM_LDR_RGBA_DIRECT;
    range_t weight_quant = RANGE_6;
    range_t endpoint_quant = endpoint_quantization(partition_count, weight_quant, color_endpoint_mode); //RANGE_256

    vec4i_t endpoint_unquantized[2];
    const size_t endpoint_quantized_count = 8;
    uint8_t endpoint_quantized[endpoint_quantized_count];
    encode_rgba_direct(endpoint_quant, round(e0), round(e1), endpoint_quantized, endpoint_unquantized);

    uint8_t weights_quantized[BLOCK_TEXEL_COUNT];
    calculate_quantized_weights_rgba(texels, weight_quant, endpoint_unquantized[0], endpoint_unquantized[1], weights_quantized);

    const size_t endpoint_ise_count = MAXIMUM_ENCODED_COLOR_ENDPOINT_BYTES;
    uint8_t endpoint_ise[endpoint_ise_count] = { 0 };
    integer_sequence_encode(endpoint_quantized, endpoint_quantized_count, endpoint_quant, endpoint_ise);

    const size_t weights_ise_count = MAXIMUM_ENCODED_WEIGHT_BYTES;
    uint8_t weights_ise[weights_ise_count + 1] = { 0 };
    integer_sequence_encode(weights_quantized, BLOCK_TEXEL_COUNT, weight_quant, weights_ise);

    symbolic_to_physical2(color_endpoint_mode, endpoint_quant, weight_quant, partition_count, partition_index, endpoint_ise, endpoint_ise_count, weights_ise, weights_ise_count, physical_block);
}

void compress_block_alpha(const unorm8_t texels[BLOCK_TEXEL_COUNT], PhysicalBlock* physical_block) {

    {
        vec4i_t color;
        if (is_alpha0(texels, color)) {
            encode_void_extent(color, physical_block);
            return;
        }
    }

    vec4f_t k, m;
    principal_component_analysis(texels, k, m);
    vec4f_t e0, e1;
    find_min_max(texels, k, m, e0, e1);
    encode_rgba_single_partition(texels, e0, e1, physical_block);
    /* encode_void_extent(vec3i_t(0, 255, 0), physical_block); */
}

#endif