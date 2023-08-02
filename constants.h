#ifndef ASTC_CONSTANTS_H_
#define ASTC_CONSTANTS_H_

#ifdef RTTC_USE_ASTCRT

#include <cstddef>

static const size_t BLOCK_WIDTH = 4;
static const size_t BLOCK_HEIGHT = 4;
static const size_t BLOCK_TEXEL_COUNT = BLOCK_WIDTH * BLOCK_HEIGHT;
static const size_t BLOCK_BYTES = 16;

static const size_t MAXIMUM_ENCODED_WEIGHT_BITS = 96;
static const size_t MAXIMUM_ENCODED_WEIGHT_BYTES = 12;

static const size_t MAXIMUM_ENCODED_COLOR_ENDPOINT_BYTES = 12;

static const size_t MAX_ENDPOINT_VALUE_COUNT = 18;

#endif

#endif  // ASTC_CONSTANTS_H_
