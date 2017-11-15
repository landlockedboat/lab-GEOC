#ifndef _GEOC_TRIANGULATION_H
#define _GEOC_TRIANGULATION_H

#include <geoc/geoc.h>
#include <geoc/geometry/TriangulationBase.h>
#include <geoc/math/Vector_fwd_decl.h>
#include <vector>

namespace geoc {

class LineSegmentEnt;
class TriangleEnt;


/** \ingroup Geometry */
//! A triangulation of a set of points in the plane.
class Triangulation : public TriangulationBase
{	
public:
    
    Triangulation();
    ~Triangulation();
    
    void triangulate(const std::vector<Vector3>& ps,
                     const std::vector<int>& idxs,
                     std::vector<LineSegmentEnt>& segments,
                     std::vector<TriangleEnt>& triangles,
                     std::vector<TriangleEnt>& triangles_pruned);
};

} // namespace geoc


#endif //_GEOC_TRIANGULATION_H
