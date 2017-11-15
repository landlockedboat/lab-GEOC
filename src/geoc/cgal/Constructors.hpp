#ifndef _GEOC_CGAL_CONSTRUCTORS_H
#define _GEOC_CGAL_CONSTRUCTORS_H

#include <geoc/math/Vector.h>
#include <geoc/geometry/LineSegment.h>
#include <geoc/geometry/Triangle.h>
#include <geoc/geometry/Circle.h>

namespace geoc {

/** \ingroup CGAL */
//! Point_2 constructor.
template <typename K, typename OldK>
class Viewer_Point_2_cons
{
    typedef typename K::RT        RT;
    typedef typename K::Point_2   Point_2;
    typedef typename K::Line_2    Line_2;
    typedef typename Point_2::Rep Rep;
    
public:
    typedef Point_2     result_type;
    
    Rep operator()(CGAL::Return_base_tag, CGAL::Origin o) const
    { return Rep(o); }
    
    Rep operator()(CGAL::Return_base_tag, const RT& x, const RT& y) const 
    { return Rep(x,y); }
    
    Point_2 operator()(CGAL::Origin o) const
    { return Vector2(0,0,0); }
    
    Point_2 operator()(const RT& x, const RT& y) const
    { return Vector2(x,y); }
};


/** \ingroup CGAL */
//! Point_3 constructor.
template <typename K, typename OldK>
class Viewer_Point_3_cons
{
    typedef typename K::RT        RT;
    typedef typename K::Point_3   Point_3;
    typedef typename K::Line_3    Line_3;
    typedef typename Point_3::Rep Rep;
    
public:
    typedef Point_3     result_type;
    
    Rep operator()(CGAL::Return_base_tag, CGAL::Origin o) const
    { return Rep(o); }
    
    Rep operator()(CGAL::Return_base_tag, const RT& x, const RT& y, const RT& z) const 
    { return Rep(x,y,z); }
    
    Point_3 operator()(CGAL::Origin o) const
    { return Vector3(0,0,0); }
    
    Point_3 operator()(const RT& x, const RT& y, const RT& z) const
    { return Vector3(x,y,z); }
};


/** \ingroup CGAL */
//! Segment_3 constructor.
class Segment_3_cons
{
public:
    LineSegment operator()(const Vector3& source, const Vector3& target)
    {
        return LineSegment(source, target);
    }
};


/** \ingroup CGAL */
//! Triangle_3 constructor.
class Triangle_3_cons
{
public:
    Triangle operator()(const Vector3& p, const Vector3& q, const Vector3& r)
    {
        return Triangle(p, q, r);
    }
};


/** \ingroup CGAL */
//! Circle_3 constructor.
class Circle_3_cons
{
public:
    Circle operator()(const Vector3& p, const Vector3& q, const Vector3& r)
    {
        return Circle(p, q, r);
    }
};

} // namespace geoc

#endif // _GEOC_CGAL_CONSTRUCTORS_H
