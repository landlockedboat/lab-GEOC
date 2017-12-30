#include <geoc/geometry/Triangle.h>
#include <geoc/geometry/LineSegment.h>
#include <geoc/scene/Point.h>
#include <geoc/math/Math.h>
#include <geoc/GeocException.h>


using namespace geoc;
using namespace std;

bool onSegment(const Vector3& p, const Vector3& q, const Vector3& r)
{
	if(r[X] <= max(p[X],q[X]) and r[X] >= min(p[X],q[X]) and
		r[Y] <= max(p[Y],q[Y]) and r[Y] >= min(p[Y],q[Y])) return true;
	else return false;
}

num otest(const Vector3& a, const Vector3& b, const Vector3& p, Colour3& colour, std::string& desc)
{
    num test = geoc::Math::orientation2D(a,b,p);
    if(test == 0) 
    {
        if(a == p or b == p) 
        {
            // Vertex
            colour = Colour3(0,0,1);
            desc = "Vertex";
	    return test;
        }
        // Edge
	//if p is in segment ab

	if(onSegment(a,b,p))
	{
            colour = Colour3(1,1,0);
            desc = "Edge";
	    return test;
	}
    }
    return test;
}

void geoc::classify(const Triangle& t, const Vector3& p, Colour3& colour, std::string& desc)
{
    //Exercise 2.
    //colour = Colour3(1, 1, 1);
    //desc = "To-do";

    /* Green: interior, Red: exterior, Yellow: edge, Other: vertex*/
    Vector3 a = t[0];
    Vector3 b = t[1];
    Vector3 c = t[2];

    num test1 = otest(a,b,p,colour,desc);
    if(desc=="Vertex" or desc=="Edge") return;
    num test2 = otest(b,c,p,colour,desc);
    if(desc=="Vertex" or desc=="Edge") return;
    num test3 = otest(c,a,p,colour,desc); 
    if(desc=="Vertex" or desc=="Edge") return;

    if((test1 > 0 and test2 > 0 and test3 > 0) or (test1 < 0 and test2 <0 and test3 <0))
    {
	//Interior
	colour = Colour3(0,1,0);
	desc = "Interior";
    }
    else
    {
	//Exterior
	colour = Colour3(1,0,0);
	desc = "Exterior";
    }
}
