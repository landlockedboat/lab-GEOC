#include <geoc/geometry/LineSegment.h>
#include <geoc/math/Math.h>


using namespace geoc;
using namespace std;

bool different(const num& a, const num& b) 
{
	if( (a >= 0 and b < 0) or (a < 0 and b >= 0) ) return true;
	else return false;
}

//given three colinear points, checks if r lies in pq
bool onSegment(Vector3& p, Vector3& q, Vector3& r)
{
	if(r[X] <= max(p[X],q[X]) and r[X] >= min(p[X],q[X]) and
		r[Y] <= max(p[Y],q[Y]) and r[Y] >= min(p[Y],q[Y])) return true;
	else return false;
}

void geoc::classifyIntersection(const LineSegment& s, const LineSegment& t, Colour3& colour, std::string& desc)
{
    //Exercise 1.
    //colour = Colour3(1, 1, 1);
    //desc = "To-do";

	Vector3 p = s[0];
	Vector3 q = s[1];
	Vector3 a = t[0];
	Vector3 b = t[1];

	//orientation test -> = 0 (on line), > 0 (left), < 0 (right)
	num a_test = geoc::Math::orientation2D(p,q,a);
	num b_test = geoc::Math::orientation2D(p,q,b);
	num p_test = geoc::Math::orientation2D(a,b,p);
	num q_test = geoc::Math::orientation2D(a,b,q);

	if(different(a_test,b_test) and different(p_test,q_test))
	{
		colour = Colour3(1,0,0);
		desc = "Intersection -> Interior Point";
	}
	else if(a_test == 0 and onSegment(p,q,a)
		or (b_test == 0 and onSegment(p,q,b))
		or (p_test == 0 and onSegment(a,b,p))
		or (q_test == 0 and onSegment(a,b,q)))
	{
		if(s == t) {
			colour = Colour3(1,0,1);
			desc = "Intersection -> Same Segments";
		}
		else if((a_test == 0 and b_test == 0) or ((p_test == 0 and q_test == 0))){
			colour = Colour3(0,1,0);
			desc = "Intersection -> Partial Segments";
		}
		else{
			colour = Colour3(1,1,0);
			desc = "Intersection -> Endpoint";
		}		
	}
	else
	{
		colour = Colour3(0,0,1);
		desc = "No Intersection";
	}
}
