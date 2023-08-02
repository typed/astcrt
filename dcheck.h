#ifndef ASTC_DCHECK_H_
#define ASTC_DCHECK_H_

#ifdef RTTC_USE_ASTCRT

#include <cassert>
#define DCHECK(x) assert(x)

#endif

#endif  // ASTC_DCHECK_H_
