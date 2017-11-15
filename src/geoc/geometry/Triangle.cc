#include <geoc/geometry/Triangle.h>
#include <algorithm>
#include <CGAL/Bbox_3.h>
#include <cmath>


using namespace geoc;


Triangle::Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
    points[0] = v1;
    points[1] = v2;
    points[2] = v3;
}


bool Triangle::operator==(const Triangle& t) const
{
    return std::equal(points, points+3, t.points);
}


CGAL::Cartesian<num>::Plane_3 Triangle::supporting_plane() const
{
    Vector3 v1 = points[0] - points[1];
    Vector3 v2 = points[2] - points[1];
    Vector3 n = cross(v2, v1);
    
    num d = -(n[X] * points[1][X] + n[Y] * points[1][Y] + n[Z] * points[1][Z]);
    
    return CGAL::Cartesian<num>::Plane_3(n[X], n[Y], n[Z], d);
}


num Triangle::squared_area() const
{
    return 0.25 * (points[2] - points[1]).normSq() * (points[0] - points[1]).normSq();
}


CGAL::Bbox_3 Triangle::bbox() const
{
    using std::min; using std::max;
    Vector3 bot = Vector3(min(points[0][X], points[1][X]), min(points[0][Y], points[1][Y]), min(points[0][Z], points[1][Z]));
    Vector3 top = Vector3(max(points[0][X], points[1][X]), max(points[0][Y], points[1][Y]), max(points[0][Z], points[1][Z]));
    return CGAL::Bbox_3(bot[X], bot[Y], bot[Z], top[X], top[Y], top[Z]);
}


Vector3 geoc::normal(const Triangle& t)
{
    Vector3 v1 = t[1] - t[0];
    Vector3 v2 = t[2] - t[0];
    Vector3 normal = cross(v1, v2);
    return normal.normalise();
}
