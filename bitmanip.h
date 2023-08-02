#ifndef ASTC_BITMANIP_H_
#define ASTC_BITMANIP_H_

#ifdef RTTC_USE_ASTCRT

#include <cstddef>
#include <cstdint>

#include "dcheck.h"

inline bool getbit(size_t number, size_t n) {
    return (number >> n) & 1;
}

inline uint8_t getbits(uint8_t number, uint8_t msb, uint8_t lsb) {
    const int one = 1;
    int count = msb - lsb + one;
    return static_cast<uint8_t>((number >> lsb) & ((one << count) - one));
}

inline size_t getbits(size_t number, size_t msb, size_t lsb) {
    const size_t one = 1;
    size_t count = msb - lsb + one;
    return (number >> lsb) & (static_cast<size_t>(one << count) - one);
}

inline void orbits8_ptr(uint8_t* ptr, size_t bitoffset, size_t number, size_t bitcount) {
    DCHECK(bitcount <= 8);
    DCHECK((number >> bitcount) == 0);

    size_t index = bitoffset / 8;
    size_t shift = bitoffset % 8;

    // Depending on the offset we might have to consider two bytes when
    // writing, for instance if we are writing 8 bits and the offset is 4,
    // then we have to write 4 bits to the first byte (ptr[index]) and 4 bits
    // to the second byte (ptr[index+1]).
    //
    // FIXME: Writing to the last byte when the number of bytes is a multiple of 2
    // will write past the allocated memory.

    uint8_t* p = ptr + index;
    size_t mask = number << shift;

    DCHECK((p[0] & mask) == 0);
    DCHECK((p[1] & (mask >> 8)) == 0);

    p[0] |= static_cast<uint8_t>(mask & 0xFF);
    p[1] |= static_cast<uint8_t>((mask >> 8) & 0xFF);
}

inline void orbits16_ptr(uint8_t* ptr, size_t bitoffset, size_t number, size_t bitcount) {
    DCHECK(bitcount > 8 && bitcount <= 16);

    size_t index = bitoffset / 8;
    size_t shift = bitoffset % 8;

    uint8_t* p = ptr + index;
    size_t mask = number << shift;

    p[0] |= static_cast<uint8_t>(mask & 0xFF);
    p[1] |= static_cast<uint8_t>((mask >> 8) & 0xFF);
    p[2] |= static_cast<uint8_t>((mask >> 16) & 0xFF);
    p[3] |= static_cast<uint8_t>((mask >> 24) & 0xFF);
}

inline uint16_t getbytes2(const uint8_t* ptr, size_t byteoffset) {
    const uint8_t* p = ptr + byteoffset;
    return static_cast<uint16_t>((p[1] << 8) | p[0]);
}

inline void setbytes2(uint8_t* ptr, size_t byteoffset, uint16_t bytes) {
    ptr[byteoffset + 0] = static_cast<uint8_t>(bytes & 0xFF);
    ptr[byteoffset + 1] = static_cast<uint8_t>((bytes >> 8) & 0xFF);
}

inline void split_high_low(uint8_t n, size_t i, uint8_t& high, uint8_t& low) {
    DCHECK(i < 8);

    uint8_t low_mask = static_cast<uint8_t>((1 << i) - 1);

    low = n & low_mask;
    high = static_cast<uint8_t>(n >> i);
}

class bitwriter {
public:
    explicit bitwriter(uint8_t* ptr) : ptr_(ptr), bitoffset_(0) {
        // assumption that all bits in ptr are zero after the offset

        // writing beyound the bounds of the allocated memory is undefined
        // behaviour
    }

    // Specialized function that can't write more than 8 bits.
    void write8(uint8_t number, size_t bitcount) {
        orbits8_ptr(ptr_, bitoffset_, number, bitcount);

        bitoffset_ += bitcount;
    }

    size_t offset() const { return bitoffset_; }

private:
    uint8_t* ptr_;
    size_t bitoffset_;  // in bits
};

const uint8_t bit_reverse_table[256] = {
    0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0,
    0x30, 0xB0, 0x70, 0xF0, 0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8,
    0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 0x04, 0x84, 0x44, 0xC4,
    0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
    0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC,
    0x3C, 0xBC, 0x7C, 0xFC, 0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2,
    0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, 0x0A, 0x8A, 0x4A, 0xCA,
    0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
    0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6,
    0x36, 0xB6, 0x76, 0xF6, 0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE,
    0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE, 0x01, 0x81, 0x41, 0xC1,
    0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
    0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9,
    0x39, 0xB9, 0x79, 0xF9, 0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5,
    0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5, 0x0D, 0x8D, 0x4D, 0xCD,
    0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
    0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3,
    0x33, 0xB3, 0x73, 0xF3, 0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB,
    0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB, 0x07, 0x87, 0x47, 0xC7,
    0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
    0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF,
    0x3F, 0xBF, 0x7F, 0xFF
};

/**
 * Reverse a byte, total function.
 */
inline uint8_t reverse_byte(uint8_t number) {
    return bit_reverse_table[number];
}

/**
 * Reverse a sequence of bytes.
 *
 * Assumes that the bits written to (using bitwise or) are zero and that they
 * will not clash with bits already written to target sequence. That is it is
 * possible to write to a non-zero byte as long as the bits that are actually
 * written to are zero.
 */
inline void reverse_bytes(const uint8_t* source,
                          size_t bytecount,
                          uint8_t* target) {
    for (int i = 0; i < static_cast<int>(bytecount); ++i) {
        DCHECK((reverse_byte(source[i]) & target[-i]) == 0);
        target[-i] = target[-i] | reverse_byte(source[i]);
    }
}

inline void copy_bytes(const uint8_t* source,
                       size_t bytecount,
                       uint8_t* target,
                       size_t bitoffset) {
    for (size_t i = 0; i < bytecount; ++i) {
        orbits8_ptr(target, bitoffset + i * 8, source[i], 8);
    }
}

#endif

#endif  // ASTC_BITMANIP_H_
