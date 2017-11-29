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

    DCEL dcel = DCEL(false,ps);

    vector<Face*> faces = dcel.getFaces();
    
    for(int i = 0; i < faces.size(); ++i)
    {
       Vector3 v1 = faces[i]->getBoundary()->getOrigin()->getVertex();
       Vector3 v2 = faces[i]->getBoundary()->getNext()->getOrigin()->getVertex();
       Vector3 v3 = faces[i]->getBoundary()->getNext()->getNext()->getOrigin()->getVertex();
       triangles.push_back(Triangle(v1,v2,v3));
   }   
}
