﻿#ifdef RTTC_USE_ASTCRT

#include "compress_texture.h"

#include <cstddef>

#include "colors.h"
#include "compress_block.h"
#include "constants.h"
#include "store_block.h"

#ifdef __GNUC__
#   pragma GCC diagnostic ignored "-Wmissing-braces"
#endif

inline void fetch_image_block(const unorm8_t* source, size_t image_width, size_t xpos, size_t ypos, unorm8_t texels[BLOCK_TEXEL_COUNT]) {

    size_t topleft_index = ypos * image_width + xpos;

    const unorm8_t* row0 = source + topleft_index;
    const unorm8_t* row1 = row0 + image_width;
    const unorm8_t* row2 = row0 + 2 * image_width;
    const unorm8_t* row3 = row0 + 3 * image_width;

    texels[0] = row0[0];
    texels[1] = row0[1];
    texels[2] = row0[2];
    texels[3] = row0[3];

    texels[4] = row1[0];
    texels[5] = row1[1];
    texels[6] = row1[2];
    texels[7] = row1[3];

    texels[8] = row2[0];
    texels[9] = row2[1];
    texels[10] = row2[2];
    texels[11] = row2[3];

    texels[12] = row3[0];
    texels[13] = row3[1];
    texels[14] = row3[2];
    texels[15] = row3[3];
}

//是否透明
inline bool has_transparent(const unorm8_t texels[BLOCK_TEXEL_COUNT]) {
    for (size_t i = 0; i < BLOCK_TEXEL_COUNT; ++i) {
        if (texels[i].channels.a < 255) {
            return true;
        }
    }
    return false;
}

void compress_texture(const uint8_t* src, uint8_t* dst, int width_int, int height_int, bool use_alpha) {

    const unorm8_t* data = reinterpret_cast<const unorm8_t*>(src);

    size_t width = static_cast<size_t>(width_int);
    size_t height = static_cast<size_t>(height_int);

    PhysicalBlock* dst_re = reinterpret_cast<PhysicalBlock*>(dst);

    PhysicalBlock physical_block_zero = { 0 };

    for (size_t ypos = 0; ypos < height; ypos += BLOCK_WIDTH) {
        for (size_t xpos = 0; xpos < width; xpos += BLOCK_HEIGHT) {
            unorm8_t texels[BLOCK_TEXEL_COUNT];
            fetch_image_block(data, width, xpos, ypos, texels);

            *dst_re = physical_block_zero;

            if (use_alpha && has_transparent(texels)) {
                compress_block_alpha(texels, dst_re);
            }
            else {
                compress_block(texels, dst_re);
            }

            ++dst_re;
        }
    }
}

void test_compress_texture()
{
    unorm8_t Data[BLOCK_TEXEL_COUNT];
    uint8_t DesData[BLOCK_TEXEL_COUNT];
    static int s_inited = 0;
    if (s_inited == 0) {
        s_inited = 1;
        srand((uint32_t)(size_t)&s_inited);
    }
    for (size_t i = 0; i < BLOCK_TEXEL_COUNT; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            Data[i].components[j] = rand() % 256;
        }
    }
    compress_texture((uint8_t*)&Data, DesData, BLOCK_WIDTH, BLOCK_HEIGHT, rand() % 2 == 0);
}

#endif
