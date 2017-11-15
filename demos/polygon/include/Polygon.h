#ifndef _GEOC_POLYGON_H
#define _GEOC_POLYGON_H

#include <geoc/geoc.h>
#include <geoc/scene/Entity.h>
#include <geoc/math/Vector.h>
#include <geoc/math/BoundingBox.h>
#include <fstream>
#include <vector>

namespace geoc {
class Graphics;
}

namespace polygon {

class Polygon : public geoc::Entity
{
    std::vector<geoc::Vector3> points;
    geoc::BoundingBox3 m_bb;
    
public:
    
    geoc::Colour3 colour;
    
public:
    
    void addVertex(const geoc::Vector3& v);
    
    void draw(geoc::Graphics& gfx) const;
    
    geoc::BoundingBox3 bb() const;
    
    const char* getHeader() const;
    static const char* header();
    
    static void read(std::istream& is, Polygon& p);
    void write(std::fstream& fs) const;
};


} // polygon namespace end


#endif //_GEOC_POLYGON_H
