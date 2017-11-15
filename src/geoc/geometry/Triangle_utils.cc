#include <geoc/geometry/Triangle.h>
#include <geoc/geometry/LineSegment.h>
#include <geoc/scene/Point.h>
#include <geoc/math/Math.h>
#include <geoc/GeocException.h>

using namespace geoc;
using namespace std;

bool isBetween(const Vector3 &p, const Vector3 &q, const Vector3 &r){

  float dotproduct = 
    (p[0] - q[0]) * (r[0] - q[0]) +
    (p[1] - q[1]) * (r[1] - q[1]);

  float squaredlengthba = 
    (r[0] - q[0]) * (r[0] - q[0]) +
    (r[1] - q[1]) * (r[1] - q[1]);

  return dotproduct <= squaredlengthba;
}


void geoc::classify(
    const Triangle& t,
    const Vector3& p,
    Colour3& colour,
    std::string& desc)
{
  int o1 = Math::orientation2D(p, t[0], t[1]);
  bool ob1 = isBetween(p, t[0], t[1]);

  int o2 = Math::orientation2D(p, t[1], t[2]);
  bool ob2 = isBetween(p, t[1], t[2]);

  int o3 = Math::orientation2D(p, t[2], t[0]);
  bool ob3 = isBetween(p, t[2], t[0]);

  if (o1 == o2 && o1 == o3){
    colour = Colour3(0, 1, 0);
    desc = "Inside";
  }
  else if ((o1 == 0 && o2 == 0) || (o1 == 0 && o3 == 0) || (o2 == 0 && o3 == 0)){
    colour = Colour3(1, 1, 1);
    desc = "Vertex";
  }
  else if ((o1 == 0 && ob1) || (o2 == 0 && ob2) || (o3 == 0 && ob3)){
    colour = Colour3(1, 1, 0);
    desc = "Part of segment";
  }
  else {
    colour = Colour3(1, 0, 0);
    desc = "Outside";
  }
}
