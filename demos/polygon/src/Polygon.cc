#include "Polygon.h"
#include <geoc/io/aux_functions.h>
#include <geoc/gfx/Graphics.h>


using namespace geoc;
using namespace std;
using namespace polygon;


void Polygon::addVertex(const Vector3& v)
{
    points.push_back(v);
    m_bb.add(v);
}


void Polygon::draw(Graphics& gfx) const
{
    gfx.drawPolygon(&points[0], points.size(), colour);
}


geoc::BoundingBox3 Polygon::bb() const
{
    return m_bb;
}


const char* Polygon::getHeader() const
{
    return Polygon::header();
}


const char* Polygon::header()
{
    return "polygon";
}


void Polygon::write(std::fstream& fs) const
{
    fs << points.size() << endl;
    
    foreach (const Vector3& v, points)
    {
	fs << v << endl;
    }
    fs << endl;
}


void Polygon::read(std::istream& is, Polygon& p)
{
    Vector3 v;
    int n_points;
    is >> n_points;
    
    p.points.reserve(n_points);
    for (int i = 0; i < n_points; ++i)
    {
	read_vector3(is, v);
	p.addVertex(v);
    }
}
