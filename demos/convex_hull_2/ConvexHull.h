#ifndef _CONVEX_HULL_HPP
#define _CONVEX_HULL_HPP


#include <geoc/geoc.h>
#include <geoc/cgal/Kernel.h>
#include <geoc/math/Vector.h>
#include <geoc/math/BoundingBox.h>
#include <geoc/scene/Entity.h>
#include <geoc/gfx/Graphics.h>
#include <geoc/io/aux_functions.h>
#include <vector>


class ConvexHull : public geoc::Entity
{
    typedef std::vector<geoc::Vector2> container_t;
    
    geoc::BoundingBox3 _bb;
    container_t points;
    container_t hull;
    int n_points;
    
public:
    
    ConvexHull() : n_points(0) {}
    
    void addPoint(const geoc::Vector3& p);
    
    void update();
    
    void draw(geoc::Graphics& gfx) const;
    
    geoc::BoundingBox3 bb() const { return _bb; }
    
    static const char* header() { return "convex hull"; }
    
    static void read(std::istream& is, ConvexHull& ch);
};


#endif // _CONVEX_HULL_HPP
