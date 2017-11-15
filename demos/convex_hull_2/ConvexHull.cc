#include "ConvexHull.h"
#include <CGAL/ch_graham_andrew.h>


using namespace geoc;


void ConvexHull::addPoint(const Vector3& p)
{
    points.push_back(Vector2(p[X], p[Y]));
    _bb.add(p);
}


void ConvexHull::update()
{
    typedef container_t::const_iterator iter_t;
    
    hull.resize(points.size());
    
    iter_t end;
    end = CGAL::ch_graham_andrew(points.begin(),
				 points.end(),
				 hull.begin(),
				 Viewer_Kernel<num>());
    
    n_points = 0;
    for (iter_t it = hull.begin(); it != end; ++it) n_points++;
}


void ConvexHull::draw(Graphics& gfx) const
{
    if (n_points >= 3) gfx.drawPolygon(&hull[0], n_points, zero3);
}


void ConvexHull::read(std::istream& is, ConvexHull& ch)
{
    std::streampos pos;
    
    for(;;)
    {
	pos = is.tellg();
	
	Vector3 v;
	read_vector3(is, v);
	
	if (!is.good()) break;
	
	ch.addPoint(v);
    }
    
    if (is.bad()) return;
    
    is.clear();
    is.seekg(pos);
}

