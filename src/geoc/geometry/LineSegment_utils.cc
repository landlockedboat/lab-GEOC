#include <geoc/geometry/LineSegment.h>
#include <geoc/math/Math.h>

using namespace geoc;
using namespace std;

bool differentSign(const num& a, const num& b) 
{
  return (a * b) < 0;
}

// Given a segment s and a point colinear to the projected,
// segment s, checks if p is inside s
bool checkInSegment(
    const LineSegment& s,
    const Vector3 &p)
{
  // x check
  bool c1 = p[0] <= max(s[0][0], s[1][0]);
  bool c2 = p[0] >= min(s[0][0], s[1][0]);
  // y check
  bool c3 = p[1] <= max(s[0][1], s[1][1]);
  bool c4 = p[1] >= min(s[0][1], s[1][1]);

  return c1 && c2 && c3 && c4;
}

void geoc::classifyIntersection(
    const LineSegment& s,
    const LineSegment& t,
    Colour3& colour,
    std::string& desc)
{

  if(s == t) {
    colour = Colour3(1,0,1);
    desc = "Intersection: segments are the same";
    return;
  }

  Vector3 p = s[0];
  Vector3 q = s[1];
  Vector3 a = t[0];
  Vector3 b = t[1];

  // Orientation test for each segment - point combination:
  // 0: on projected line
  // > 0: left of projected line
  // < 0: right of projected line
  num a_test = geoc::Math::orientation2D(p,q,a);
  num b_test = geoc::Math::orientation2D(p,q,b);
  num p_test = geoc::Math::orientation2D(a,b,p);
  num q_test = geoc::Math::orientation2D(a,b,q);

  if(
      differentSign(a_test, b_test) and
      differentSign(p_test, q_test)
    )
  {
    colour = Colour3(1,0,0);
    desc = "Intersection: interior point";
    return;
  }

  if(
      (a_test != 0 or not checkInSegment(s,a)) and
      (b_test != 0 or not checkInSegment(s,b)) and
      (p_test != 0 or not checkInSegment(t,p)) and
      (q_test != 0 or not checkInSegment(t,q)))
  {
    colour = Colour3(0,0,1);
    desc = "No Intersection";
    return;
  }

  // Arrived at this point, at least an orientation 
  // test is 0 and is colinear with one of the segments.
  if(
      (a_test == 0 and b_test == 0) or
      (p_test == 0 and q_test == 0)
    )
  {
    // If both endpoints of a segment are colinear with the other
    // segment, they are overlapping
    colour = Colour3(0,1,0);
    desc = "Intersection: overlapping segments";
    return;
  }

  // All options have been explored, and given the circumstances,
  // we can only assume the intersection s and t form is equivalent
  // to an endpoint of one of the two.
  colour = Colour3(1,1,0);
  desc = "Intersection: endpoint";
  return;
}
