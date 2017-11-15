#include <geoc/geometry/Circle.h>


using namespace geoc;


Circle::Circle(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
    points[0] = v1;
    points[1] = v2;
    points[2] = v3;
}


const Vector3& Circle::operator[](int index) const
{
    GEOC_DEBUG_ASSERT(index >= 0 && index <= 2);
    return points[index];
}
