#ifndef _GEOC_TRIANGLE_H
#define _GEOC_TRIANGLE_H

#include <geoc/geoc.h>
#include <geoc/math/Vector.h>
#include <CGAL/Cartesian.h>

namespace CGAL { class Bbox_3; }

namespace geoc {

class Graphics;
class Point;
class Plane_3;

/** \ingroup Geometry */
//! A triangle in 3D space.
/*!
 * A Triangle is composed of three points and has no other attributes.
 * This class is meant for heavy geometric computations, having no overhead and
 * exposing a minimal interface.
 */
class DECLDIR Triangle
{
    Vector3 points[3];
    
    template <class iter_t> friend Triangle triangle(iter_t);
    
public:
    
    //! Default constructor.
    /*!
     * Points are set to the origin.
     */
    Triangle() {}
    
    //! Builds a triangle from three points.
    Triangle(const Vector3& p1, const Vector3& p2, const Vector3& p3);
    
    //! Tests two triangles for equality.
    bool operator==(const Triangle& t) const;
    
    //! Tests two triangles of inequality.
    bool operator!=(const Triangle& t) const { return !((*this) == t); }
    
    //! Gets the ith vertex modulo 3.
    const Vector3& vertex(int index) const
    {
        return points[index%3];
    }
    
    //! Gets the ith vertex.
    /*!
     * The index is checked in debug mode, but not in release mode.
     */
    const Vector3& operator[](int index) const
    {
        GEOC_DEBUG_ASSERT(index >= 0 && index <= 2);
        return points[index];
    }
    
    //! Returns the triangle's supporting plane, with the same orientation.
    CGAL::Cartesian<num>::Plane_3 supporting_plane() const;
    
    // Returns true if the triangle's vertices are collinear, false otherwise.
    //bool is_degenerate() const;
    
    //bool has_on(const Vector3& p) const;
    
    //! Returns the triangle's area squared.
    num squared_area() const;
    
    //! Returns a bounding box containing the triangle.
    CGAL::Bbox_3 bbox() const;
};


//! Builds a triangle from three points, provided an iterator.
/*!
 * The given iterator must be an iterator over Vector3.
 * The given iterator must point to a sequence of at least three points.
 */
template <class iter_t>
Triangle triangle(iter_t it)
{
    Triangle t;
    for (int i = 0; i < 3; ++i) t.points[i] = *it++;
    return t;
}


//! Computes the given triangle's normal.
DECLDIR Vector3 normal(const Triangle& t);


//! Classifies a given point's position relative to the given triangle.
/*!
 * \param p The point to classify.
 * \return colour The colour to draw the point in.
 * \return desc A description about the classification.
 */
DECLDIR void classify(const Triangle& t, const Vector3& p, Colour3& colour, std::string& desc);


} //namespace geoc

#endif //_GEOC_TRIANGLE_H
