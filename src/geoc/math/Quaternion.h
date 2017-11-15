#ifndef _GEOC_QUATERNION_H
#define _GEOC_QUATERNION_H

#include <geoc/geoc.h>
#include "Vector.h"

namespace geoc
{

/** \ingroup Math */
class Quaternion
{
public:
    
    num w, x, y, z;
    
    Quaternion () : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
    
    Quaternion (num _w, num _x, num _y, num _z)
        : w(_w), x(_x), y(_y), z(_z) {}
};

/// Computes the product of the given two quaternions.
Quaternion operator* (Quaternion q1, Quaternion q2);

/// Computes the quaternion representing the given rotation.
Quaternion qAxisAngle (num angle, num x, num y, num z);

/// Computes the inverse the given quaternion.
Quaternion inverse (Quaternion q);

/// Computes the conjugate of the given quaternion.
Quaternion conjugate (Quaternion q);

/// Rotates the given vector by the given (unit) quaternion.
Vector3 rotate (Quaternion q, Vector3 v);

} // namespace geoc

#endif // _GEOC_QUATERNION_H
