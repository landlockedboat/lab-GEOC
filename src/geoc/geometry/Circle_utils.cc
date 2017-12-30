#include <geoc/geometry/Circle.h>
#include <geoc/scene/Point.h>
#include <geoc/math/Math.h>


using namespace geoc;
using namespace std;


void geoc::classify(const Circle& c, const Vector3& p, Colour3& colour, std::string& desc)
{
    //Exercise 3.
    //colour = Colour3(1, 1, 1);
    //desc = "To-do";
	Vector2 v1 = Vector2(c[0][X],c[0][Y]);
	Vector2 v2 = Vector2(c[1][X],c[1][Y]);
	Vector2 v3 = Vector2(c[2][X],c[2][Y]);
	Vector2 t = Vector2(p[X],p[Y]);
	num o1 = Math::orientation2D(v1,v2,v3);
	num o2 = Math::orientation25D(v1,v2,v3,t);

	if(o2 == 0) {
		//Edge
		colour = Colour3(1,1,0);
		desc = "Edge";
	}
	else if(o2 < 0 and o1 > 0) {
		//Interior
		colour = Colour3(0,1,0);
                desc = "Interior";
	}
	else if (o2 > 0 and o1 > 0) {
		//Exterior
		colour = Colour3(1,0,0);
                desc = "Exterior";
	}
	else if (o2 < 0 and o1 < 0) {
		//Exterior
                colour = Colour3(1,0,0);
                desc = "Exterior";
	}
	else if (o2 > 0 and o1 < 0) {
		//Interior
                colour = Colour3(0,1,0);
                desc = "Interior";
	}
}

