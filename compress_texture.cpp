#ifdef RTTC_USE_ASTCRT

#include "compress_texture.h"

#include <cstddef>

#include "colors.h"
#include "compress_block.h"
#include "constants.h"
#include "store_block.h"

#ifdef __GNUC__
#   pragma GCC diagnostic ignored "-Wmissing-braces"
#endif

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

    unorm8_t texels[BLOCK_TEXEL_COUNT];
    for (size_t ypos = 0; ypos < height; ypos += BLOCK_WIDTH) {
        for (size_t xpos = 0; xpos < width; xpos += BLOCK_HEIGHT) {

            const unorm8_t* row = data + (ypos * width + xpos);
            for (size_t i = 0; i < BLOCK_TEXEL_COUNT; ++i) {
                texels[i] = *(row + (i / BLOCK_HEIGHT) * width + (i % BLOCK_WIDTH));
            }

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
