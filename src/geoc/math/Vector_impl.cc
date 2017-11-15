#include <geoc/math/Vector.h>

using namespace geoc;

Vector3 geoc::cross(const Vector3& v1, const Vector3& v2)
{
    return Vector3
            ( v1[Y] * v2[Z] - v1[Z] * v2[Y],
              v1[Z] * v2[X] - v1[X] * v2[Z],
              v1[X] * v2[Y] - v1[Y] * v2[X]
              );
}
