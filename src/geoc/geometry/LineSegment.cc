#include <geoc/geometry/LineSegment.h>
#include <algorithm>
#include <CGAL/Bbox_3.h>


using namespace geoc;


LineSegment::LineSegment(const Vector3& p1, const Vector3& p2)
{
    points[0]		= p1;
    points[1]		= p2;
}


bool LineSegment::operator==(const LineSegment& s) const
{
    return std::equal(points, points+2, s.points);
}


const Vector3& LineSegment::min() const
{
    if (points[0] < points[1]) return points[0];
    return points[1];
}


const Vector3& LineSegment::max() const
{
    if (points[0] > points[1]) return points[0];
    return points[1];
}


num LineSegment::squared_length() const
{
    return (points[0] - points[1]).normSq();
}


CGAL::Cartesian<num>::Line_3 LineSegment::supporting_line() const
{
    return CGAL::Cartesian<num>::Line_3(
                CGAL::Cartesian<num>::Point_3(points[0][X], points[0][Y], points[0][Z]),
                CGAL::Cartesian<num>::Point_3(points[1][X], points[1][Y], points[1][Z])
                );
}


CGAL::Bbox_3 LineSegment::bbox() const
{
    return CGAL::Bbox_3(points[0][X], points[0][Y], points[0][Z],
                        points[1][X], points[1][Y], points[1][Z]);
}
