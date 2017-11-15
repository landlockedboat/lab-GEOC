#ifndef _GEOC_CGAL_KERNEL_H
#define _GEOC_CGAL_KERNEL_H

#include <geoc/geoc.h>
#include <geoc/math/Vector.h>
#include <geoc/geometry/LineSegment.h>
#include <geoc/geometry/Triangle.h>
#include <geoc/geometry/Circle.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Origin.h>

#include "Constructors.hpp"
#include "Vector_iterators.h"


namespace geoc {


/** \ingroup CGAL */
//! A CGAL kernel that integrates the viewer's geometric types into CGAL.
template <class K_, class K_Base>
class ViewerCartesian_base : public K_Base::template Base<K_>::Type
{
    typedef typename K_Base::template Base<K_>::Type   OldK;
    
public:
    
    typedef K_ Kernel;
    typedef Vector2 Point_2;
    typedef Vector2 Vector_2;
    typedef Vector2 Direction_2;
    typedef Vector3 Point_3;
    typedef Vector3 Vector_3;
    typedef Vector3 Direction_3;
    typedef LineSegment Segment_3;
    typedef Triangle Triangle_3;
    typedef Circle Circle_3;
    
    typedef const num* Cartesian_const_iterator_2;
    typedef const num* Cartesian_const_iterator_3;
    
    typedef geoc::Construct_Vector2_iterator Construct_cartesian_const_iterator_2;
    typedef geoc::Construct_Vector3_iterator Construct_cartesian_const_iterator_3;
    
    typedef Viewer_Point_2_cons<Kernel, OldK> Construct_point_2;
    typedef Viewer_Point_3_cons<Kernel, OldK> Construct_point_3;
    typedef Segment_3_cons Construct_segment_3;
    typedef Triangle_3_cons Construct_triangle_3;
    
    Construct_point_2 construct_point_2_object() const { return Construct_point_2(); }
    Construct_point_3 construct_point_3_object() const { return Construct_point_3(); }
    Construct_segment_3 construct_segment_3_object() const { return Construct_segment_3(); }
    Construct_triangle_3 construct_triangle_3_object() const { return Construct_triangle_3(); }
};


template <class FT>
struct Viewer_Kernel : 
        public CGAL::Type_equality_wrapper< 
        ViewerCartesian_base< Viewer_Kernel<FT>, CGAL::Cartesian<FT> >, 
        Viewer_Kernel<FT> 
        >
{};


} // namespace geoc

#endif
