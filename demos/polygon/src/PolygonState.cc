#include <PolygonState.h>
#include <Polygon.h>
#include <geoc/gfx/Graphics.h>


using namespace geoc;
using namespace std;
using namespace polygon;


GEOC_APP_REQUEST_CODE PolygonState::mouseClick(const Vector3& pos)
{
    if (vertices.size() == 0) vertices.push_front(pos);
    vertices.push_front(pos);
    return GEOC_APP_REDISPLAY;
}


GEOC_APP_REQUEST_CODE PolygonState::mouseRightClick(const Vector3& pos)
{
    vertices.push_front(pos);
    Polygon* p = new Polygon;
    
    foreach (const Vector3& v, vertices)
    {
	p->addVertex(v);
    }
    
    enters(p);
    vertices.clear();
    
    return GEOC_APP_REDISPLAY;
}


GEOC_APP_REQUEST_CODE PolygonState::mouseMove(const Vector3& pos)
{
    if (vertices.size() >= 1)
    {
	vertices.front() = pos;
    }
    
    return GEOC_APP_REDISPLAY;
}


void PolygonState::cancel()
{
    vertices.clear();
}


void PolygonState::draw(Graphics& gfx)
{
    if (vertices.size() == 1)
    {
	gfx.drawPoint(vertices.front());
    }
    else if (vertices.size() > 1)
    {
	list<Vector3>::const_iterator vertex = vertices.begin();
	vertex++;
	
	while (vertex != vertices.end())
	{
	    list<Vector3>::const_iterator previous = vertex;
	    previous--;
	    
	    gfx.drawSegment(*previous, *vertex);
	    vertex++;
	}
    }
}


const char* PolygonState::description() const
{
    return "Polygon mode";
}

