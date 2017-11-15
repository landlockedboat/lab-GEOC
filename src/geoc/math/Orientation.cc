#include <geoc/math/Math.h>
#include <geoc/math/Vector.h>

using namespace geoc;

num Math::orientation2D(
    const Vector3& p,
    const Vector3& q,
    const Vector3& r)
{
  num res = (q[0] - p[0]) * (r[1] - p[1]) - (q[1] - p[1]) * (r[0] - p[0]);

  if (res == 0)
  {
    return 0;
  }
  return (res > 0) ? 1 : -1;
}

num Math::orientation25D(
    const Vector2& p,
    const Vector2& q,
    const Vector2& r,
    const Vector2& t)
{
  // Calculate the determinant of the matrix
  float a11, a12, a13, a21, a22, a23, a31, a32, a33;
  a11 = q[0] - p[0];
  a12 = q[1] - p[1];
  a13 = (q[0] - p[0]) * (q[0] + p[0]) + (q[1] - p[1]) * (q[1] + p[1]);
  a21 = r[0] - p[0];
  a22 = r[1] - p[1];
  a23 = (r[0] - p[0]) * (r[0] + p[0]) + (r[1] - p[1]) * (r[1] + p[1]);
  a31 = t[0] - p[0];
  a32 = t[1] - p[1];
  a33 = (t[0] - p[0]) * (t[0] + p[0]) + (t[1] - p[1]) * (t[1] + p[1]);

  float res = 
    a11 * a22 * a33 + 
    a12 * a23 * a31 +
    a13 * a21 * a32 -
    (
     a31 * a22 * a13 +
     a32 * a23 * a11 +
     a33 * a21 * a12
    );

  if (res == 0)
  {
    return 0;
  }
  return (res > 0) ? 1 : -1;
}
