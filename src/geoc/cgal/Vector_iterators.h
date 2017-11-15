#ifndef _GEOC_CGAL_VECTOR_ITERATORS_H
#define _GEOC_CGAL_VECTOR_ITERATORS_H


#include <geoc/geoc.h>
#include <geoc/math/Vector_fwd_decl.h>

namespace geoc {

/** \ingroup CGAL */
//! Vector2 iterator.
class Construct_Vector2_iterator
{
public:
    
    const num* operator()(const Vector2& v);
    const num* operator()(const Vector2& v, int);
};

/** \ingroup CGAL */
//! Vector3 iterator.
class Construct_Vector3_iterator
{
public:
    
    const num* operator()(const Vector3& v);
    const num* operator()(const Vector3& v, int);
};


} // namespace geoc


#endif // _GEOC_CGAL_VECTOR_ITERATORS_H
