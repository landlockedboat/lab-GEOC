#ifndef _GEOC_CGAL_TRIANGULATION_H
#define _GEOC_CGAL_TRIANGULATION_H

#define CGAL_TRIANGULATION_2_DONT_INSERT_RANGE_OF_POINTS_WITH_INFO
#include <geoc/geoc.h>
#include <geoc/geometry/TriangulationBase.h>
#include <geoc/cgal/Kernel.h>
#include <CGAL/Filtered_kernel.h>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>

namespace geoc {

class LineSegmentEnt;
class TriangleEnt;

/** \ingroup Geometry */
//! A delaunay triangulation of a set of points in the plane.
class DECLDIR CgalTriangulation : public TriangulationBase
{
    typedef Viewer_Kernel<num> VK_;
    typedef CGAL::Filtered_kernel_adaptor<VK_> K_;
    typedef CGAL::Projection_traits_xy_3<K_> K;
    typedef CGAL::Delaunay_triangulation_2<K> Delaunay_triangulation_2;
    
    Delaunay_triangulation_2 dt;
    
public:
    
    void triangulate(const std::vector<Vector3>& ps,
                     const std::vector<int>& idxs,
                     std::vector<LineSegmentEnt>& segments,
                     std::vector<TriangleEnt>& triangles,
                     std::vector<TriangleEnt>& triangles_pruned);
    
};

} // namespace geoc

#endif // _GEOC_CGAL_TRIANGULATION_H
