#ifndef _GEOC_CIRCLE_H
#define _GEOC_CIRCLE_H

#include <geoc/geoc.h>
#include <geoc/math/Vector.h>

namespace geoc {

class Graphics;
class Point;

/** \ingroup Geometry */
//! A circle in 3D space.
class DECLDIR Circle
{
    Vector3 points[3];
    
    template <class iter_t> friend Circle circle(iter_t);
    
public:
    
    //! Default constructor.
    /*!
     * Points are set to the origin.
     */
    Circle() {}
    
    //! Builds a circle from three points.
    Circle(const Vector3& v1, const Vector3& v2, const Vector3& v3);
    
    //! Gets the ith vertex.
    const Vector3& operator[](int index) const;
};


//! Builds a circle from three points, provided an iterator.
/*!
 * The given iterator must be an iterator over Vector3.
 * The given iterator must point to a sequence of at least three points.
 */
template <class iter_t>
Circle circle(iter_t it)
{
    Circle c;
    for (int i = 0; i != 3; ++i) c.points[i] = *it++;
    return c;
}


//! Classifies a given point's position relative to the given circle.
/*!
 * \param p The point to classify.
 * \return colour The colour to draw the point in.
 * \return desc A description describing this classification.
 */
DECLDIR void classify(const Circle& c, const Vector3& p, Colour3& colour, std::string& desc);


} //namespace geoc

#endif //_GEOC_CIRCLE_H
