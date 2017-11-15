#include "CgalTriangulation.h"
#include <geoc/scene/LineSegmentEnt.h>
#include <geoc/scene/TriangleEnt.h>
#include <cstdio>


using namespace geoc;


void CgalTriangulation::triangulate(const std::vector<Vector3>& ps,
                                    const std::vector<int>& idxs,
                                    std::vector<LineSegmentEnt>& segments,
                                    std::vector<TriangleEnt>& triangles,
                                    std::vector<TriangleEnt>& triangles_pruned)
{
    printf("Compiling CGAL triangulation\n");
    
    dt.insert(ps.begin(), ps.end());
    printf("tris: %d\n", dt.number_of_faces());
    typedef Delaunay_triangulation_2::Finite_faces_iterator iter_t;
    typedef Delaunay_triangulation_2::Face face_t;
    
    triangles.reserve(dt.number_of_faces());
    const Colour3 c (0x8f / 255.0, 0xbc / 255.0, 0x8f / 255.0);
    for (iter_t it = dt.finite_faces_begin(), itend = dt.finite_faces_end(); it != itend; ++it)
    {
        triangles.push_back(TriangleEnt(dt.triangle(it), c));
    }
}
