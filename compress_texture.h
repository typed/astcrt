#ifndef ASTC_COMPRESS_TEXTURE_H_
#define ASTC_COMPRESS_TEXTURE_H_

#ifdef RTTC_USE_ASTCRT

#include <cstdint>

/**
 * Compress an texture with the ASTC format.
 *
 * @param src The source data, width*height*4 bytes with BGRA ordering.
 * @param dst The output, width*height bytes.
 * @param width The width of the input texture.
 * @param height The height of the input texture.
 * @param use_alpha 是否用alpha通道，不用的话赋值255
 */
void compress_texture(const uint8_t* src, uint8_t* dst, int width, int height, bool use_alpha = false);

void test_compress_texture();

#endif

#endif  // ASTC_COMPRESS_TEXTURE_H_
