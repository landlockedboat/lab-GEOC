#ifndef _GEOC_MATH_H
#define _GEOC_MATH_H

#include <geoc/geoc.h>
#include <cmath>
#include <geoc/math/Vector_fwd_decl.h>

namespace geoc {

class Spatial;

/** \ingroup Math */
//! Math functions grouped under a single namespace.
namespace Math {
//! Performs a 2D orientation test.
num orientation2D(const Vector3& p, const Vector3& q, const Vector3& r);

//! Performs a 3D orientation test.
num orientation25D(const Vector2& p, const Vector2& q, const Vector2& r, const Vector2& t);

//! Creates pitch, yaw, and roll values from the given coordinate system's forward and right vectors.
void createYawPitchRoll(const Vector3& forward, const Vector3& right,
                        num& yaw, num& pitch, num& roll);

//! Creates a pitch value from the given forward vector.
void createPitchFromForward(const Vector3& forward, num& pitch);

//! Creates a yaw value from the given forward vector.
void createYawFromForward(const Vector3& forward, num& yaw);

//! Creates a roll value from the given right vector.
void createRollFromRight(const Vector3& right, num&roll);

//! Calculates an object's vectors from the given rotation angles.
void calculateVectors(num yaw, num pitch, num roll, Vector3& right, Vector3& up, Vector3& forward);

//! Calculates an object's right and up vectors from the given forward vector.
void calculateVectors(const Vector3& forward, Vector3& right, Vector3& up);

//! Calculates an object's forward vector from the given angles.
void calculateForwardVector(num yaw, num pitch, Vector3& out);

//! Calculates an object's right vector from the given angles.
void calculateRightVector(num yaw, num roll, Vector3& out);

//! Calculates an object's up vector from the given angles.
void calculateUpVector(num pitch, num roll, Vector3& out);

//! Maps the given point in the given Spatial's local space to viewport coordinates.
ScreenPos objectToViewport(const Spatial& spatial, const Spatial& cam, const Vector3& p);

//! Maps viewport coordinates to the given Spatial's local space.
Vector3 viewportToObject(const ScreenPos& pos, const Spatial& cam, const Spatial& spatial);

//! Maps viewport coordinates to world space.
Vector3 viewportToWorld(const ScreenPos& pos, const Spatial& cam);

//! Rearranges the given vectors so that v1-v2-v3 are in counter-clockwise order.
void makeCounterClockwise(Vector3& v1, Vector3& v2, Vector3& v3);

//! Returns the next power of two of x.
int nextPowerOfTwo(int x);

//! Returns the sign of x.
num signOf(num x);

//! Returns the absolute value of x.
inline num abs(num x) { return fabs(x); }

//! Returns the maximum of the given numbers.
num max(num a, num b, num c);

//! Returns x rounded.
inline int round(num x);

//! Returns x squared.
inline num square(num x);

int nextMultiple(int a, int b);
}; // namespace Math

const num TO_RAD = M_PI/180.0;
const num TO_DEG = 180.0/M_PI;

} // namespace geoc

#include "Math_inline.cc"

#endif //_GEOC_MATH_H
