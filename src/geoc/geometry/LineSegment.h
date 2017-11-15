#ifndef _GEOC_LINE_SEGMENT_H
#define _GEOC_LINE_SEGMENT_H

#include <geoc/geoc.h>
#include <geoc/math/Vector.h>
#include <CGAL/Cartesian.h>

namespace CGAL { class Bbox_3; }

namespace geoc {

class Graphics;

/** \ingroup Geometry */
//! A line segment in 3D space.
class DECLDIR LineSegment
{
    Vector3 points[2];
    
    template <class iter_t> friend LineSegment linesegment(iter_t);
    
public:
    
    //! Default constructor.
    /*!
     * Points are set to the origin.
     */
    LineSegment() {}
    
    //! Builds a line segment from two points.
    LineSegment(const Vector3& p1, const Vector3& p2);
    
    //! Tests two line segments for equality.
    bool operator==(const LineSegment& s) const;
    
    //! Tests two line segments for inequality.
    bool operator!=(const LineSegment& s) const
    {
        return !(*this == s);
    }
    
    //! Gets the source.
    const Vector3& source() const { return points[0]; }
    
    //! Gets the target.
    const Vector3& target() const { return points[1]; }
    
    //! Returns the point with smallest coordinate.
    const Vector3& min() const;
    
    //! Returns the point with largest coordinate.
    const Vector3& max() const;
    
    //! Gets the source or target.
    const Vector3& vertex(int index) const { return points[index % 2]; }
    
    //! Gets the ith vertex.
    const Vector3& point(int index) const { return points[index]; }
    
    //! Gets the ith vertex.
    const Vector3& operator[](int index) const
    {
        GEOC_DEBUG_ASSERT(index >= 0 && index <= 1);
        return points[index];
    }
    
    //! Returns the squared length.
    num squared_length() const;
    
    //! Returns the vector s.target() - s.source().
    Vector3 to_vector() const { return points[1] - points[0]; }
    
    //! Returns the direction from source to target.
    Vector3 direction() const { return points[1] - points[0]; }
    
    //! Returns a LineSegment with source and target interchanged.
    LineSegment opposite() const { return LineSegment(points[1], points[0]); }
    
    CGAL::Cartesian<num>::Line_3 supporting_line() const;
    
    //! Returns true if both of the segment's points fall together, false otherwise.
    bool is_degenerate() const { return points[0] == points[1]; }
    
    //bool has_on(const Vector3& p) const;
    
    //! Returns a bounding box containing the line segment.
    CGAL::Bbox_3 bbox() const;
    
    //! Returns the segment obtained by applying t on the source and the target of the line segment.
    template <class Transform>
    LineSegment transform(const Transform& t) const
    {
        return LineSegment( t(points[0]), t(points[1]) );
    }
};


//! Builds a line segment from two points, provided an iterator.
/*!
 * The given iterator must be an iterator over Vector3.
 * The given iterator must point to a sequence of at least two points.
*/
template <class iter_t>
LineSegment linesegment(iter_t it)
{
    LineSegment s;
    for (int i = 0; i < 2; ++i) s.points[i] = *it++;
    return s;
}


//! Classifies the intersection between two line segments.
/*!
 * \param s The segment to intersect this segment with.
 * \return colour The colour to draw the segments in.
 * \return desc A description about the intersection.
 */
DECLDIR void classifyIntersection(const LineSegment& s, const LineSegment& t, Colour3& colour, std::string& desc);


} //namespace geoc


#endif //_GEOC_LINE_SEGMENT_H
