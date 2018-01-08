#include <geoc/math/Math.h>
#include <geoc/math/Vector.h>


using namespace geoc;


num Math::orientation2D(const Vector3& p, const Vector3& q, const Vector3& r)
{
    //Exercise 1. 
    //orientation test -> = 0 (on line), > 0 (left), < 0 (right)
	num res = ((q[X] - p[X]) * (r[Y] - p[Y])) - ((r[X] - p[X]) * (q[Y] - p[Y]));
	return res;
}


num Math::orientation25D(const Vector2& p, const Vector2& q, const Vector2& r, const Vector2& t)
{
    //Exercise 3.
	//Projections
	Vector2 a = Vector2(p[X],p[Y]);
	Vector2 b = Vector2(q[X],q[Y]);
	Vector2 c = Vector2(r[X],r[Y]);
	Vector2 x = Vector2(t[X],t[Y]);

	//Oriented volume determinant fast

	num det1 = ((c[Y]-a[Y])*((x[X]-a[X])*(x[X]+a[X])+(x[Y]-a[Y])*(x[Y]+a[Y]))) - (((c[X]-a[X])*(c[X]+a[X])+(c[Y]-a[Y])*(c[Y]+a[Y]))*(x[Y]-a[Y]));
	num part1 = (b[X]-a[X])*det1;
	num det2 = ((c[X]-a[X])*((x[X]-a[X])*(x[X]+a[X])+(x[Y]-a[Y])*(x[Y]+a[Y]))) - (((c[X]-a[X])*(c[X]+a[X])+(c[Y]-a[Y])*(c[Y]+a[Y]))*(x[X]-a[X]));
	num part2 = (b[Y]-a[Y])*det2;
	num det3 = ((c[X]-a[X])*(x[Y]-a[Y])) - ((c[Y]-a[Y])*(x[X]+a[X]));
	num part3 = ((b[X]-a[X])*(b[X]+a[X])+(b[Y]-a[Y])*(b[Y]+a[Y]))*det3;
	num res = part1 - part2 + part3;
	return res;
}
