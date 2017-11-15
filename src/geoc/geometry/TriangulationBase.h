#ifndef _GEOC_TRIANGULATION_BASE_H
#define _GEOC_TRIANGULATION_BASE_H

#include <geoc/geoc.h>
#include <geoc/math/Vector.h>
#include <vector>

namespace geoc {

class LineSegmentEnt;
class TriangleEnt;

/** \ingroup Geometry */
//! Base class for triangulations.
class DECLDIR TriangulationBase
{
    
public:
    
    virtual ~TriangulationBase () {}
    
    //! Triangulates the given set of points.
    /**
     * \param ps The points to triangulate.
     * \param idxs An array of indices into the ps vector pointing out those vertices belonging to the boundary.
     * \param segments The vector where segments are left.
     * \param triangles The vector where triangles are left.
     * \param triangles_pruned The vector where the triangles describing the actual terrain are left.
     */
    virtual void triangulate(const std::vector<Vector3>& ps,
                             const std::vector<int>& idxs,
                             std::vector<LineSegmentEnt>& segments,
                             std::vector<TriangleEnt>& triangles,
                             std::vector<TriangleEnt>& triangles_pruned) = 0;
};

} // geoc namespace end

#endif // _GEOC_TRIANGULATION_BASE_H
