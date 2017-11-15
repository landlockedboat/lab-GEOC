#ifndef _MATH_INLINE_CC
#define _MATH_INLINE_CC

#include <geoc/geoc.h>
#include <geoc/math/Math.h>

namespace geoc {

inline int Math::round(num x) { return (int)(x+0.5); }

inline num Math::square(num x) { return x*x; }

} //namespace geoc

#endif //_MATH_INLINE_CC
