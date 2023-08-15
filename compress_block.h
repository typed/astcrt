#ifndef ASTC_COMPRESS_BLOCK_H_
#define ASTC_COMPRESS_BLOCK_H_

#ifdef RTTC_USE_ASTCRT

#include "constants.h"

union unorm8_t;
struct PhysicalBlock;

void compress_block(const unorm8_t texels[BLOCK_TEXEL_COUNT], PhysicalBlock& physical_block);

void compress_block_alpha(const unorm8_t texels[BLOCK_TEXEL_COUNT], PhysicalBlock& physical_block);

#endif

#endif  // ASTC_COMPRESS_BLOCK_H_
