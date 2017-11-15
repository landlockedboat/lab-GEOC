#ifndef _GEOC_SPATIAL_INLINE_CC
#define _GEOC_SPATIAL_INLINE_CC

#include <geoc/geoc.h>
#include "Spatial.h"

namespace geoc {

inline void Spatial::setPosition(const Vector3 &v) { setPosition(v[X], v[Y], v[Z]); }

inline void Spatial::setOrientation(const Vector3 &v) { setOrientation(v[X], v[Y], v[Z]); }

inline void Spatial::setRotation(const Vector3 &v) { setRotation(v[X], v[Y], v[Z]); }

inline const Vector3& Spatial::position() const { return mpos; }

inline const Vector3& Spatial::forward() const { return mforward; }

inline const Vector3& Spatial::right() const { return mright; }

inline const Vector3& Spatial::up() const { return mup; }

} //namespace geoc

#endif //_GEOC_SPATIAL_INLINE_CC
