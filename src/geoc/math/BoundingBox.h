#ifndef _GEOC_BOUNDING_BOX_H
#define _GEOC_BOUNDING_BOX_H

#include <geoc/geoc.h>
#include <geoc/math/Vector.h>

namespace geoc {

/** \ingroup Math */
//! An N-dimensional bounding box.
template <int N>
class BoundingBox
{
    Vector<num,N>	_min;
    Vector<num,N>	_max;
    bool			first_point;
    
public:
    
    //! Creates a bounding box.
    /*!
     * This bounding box's min and max will be set to the origin.
     */
    BoundingBox() : first_point(true) {}
    
    //! Creates a bounding box from the given points.
    template <class iter_t>
    BoundingBox(iter_t begin, const iter_t& end);
    
    //! Adds a point to the bounding box.
    void add(const Vector<num,N>& v);
    
    //! Gets the bounding box's center.
    const Vector<num,N> center() const;
    
    //! Gets the bounding box's min vertex.
    const Vector<num,N>& min() const { return _min; }
    
    //! Gets the bounding box's max vertex.
    const Vector<num,N>& max() const { return _max; }
};

typedef BoundingBox<2> BoundingBox2;
typedef BoundingBox<3> BoundingBox3;

} //namespace geoc

#include "BoundingBox.cc"

#endif //_GEOC_BOUNDING_BOX_H
