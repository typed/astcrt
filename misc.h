#ifndef ASTC_MISC_H_
#define ASTC_MISC_H_

#ifdef RTTC_USE_ASTCRT

#include <math.h>

template <typename T>
inline T clamp(T a, T b, T x) {
    if (x < a) {
        return a;
    }
    if (x > b) {
        return b;
    }
    return x;
}

inline bool approx_equal(float x, float y, float epsilon) {
    return fabs(x - y) < epsilon;
}

#endif

#endif  // ASTC_MISC_H_
