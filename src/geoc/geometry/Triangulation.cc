#include <geoc/geometry/Triangulation.h>
#include <geoc/geometry/Triangle.h>
#include <geoc/geometry/Circle.h>
#include <geoc/math/Math.h>
#include <geoc/scene/LineSegmentEnt.h>
#include <geoc/scene/TriangleEnt.h>
#include <geoc/GeocException.h>
#include <algorithm>
#include <sstream>
#include <cstdio>


using namespace geoc;
using namespace std;


Triangulation::Triangulation()
{
}


Triangulation::~Triangulation()
{
}


void Triangulation::triangulate(const std::vector<Vector3>& ps,
                                const std::vector<int>& idxs,
                                std::vector<LineSegmentEnt>& segments,
                                std::vector<TriangleEnt>& triangles,
                                std::vector<TriangleEnt>& triangles_pruned)
{
    printf("Compiling student triangulation\n");
    
    // Add code here.
}
