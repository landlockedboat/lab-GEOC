#include <geoc/io/screen/TriangleState.h>
#include <geoc/gfx/Graphics.h>

using namespace geoc;

TriangleState::TriangleState()
{
    points_entered = 0;
}

GEOC_APP_REQUEST_CODE TriangleState::mouseClick(const Vector3& pos)
{
    pts[points_entered] = pos;
    points_entered++;
    
    if (points_entered == 3)
    {
        triangle = triangle_ent(pts);
        enters(new TriangleEnt(triangle));
        cancel();
    }
    else {
        pts[points_entered] = pos;
        triangle = triangle_ent(pts);
    }
    
    return GEOC_APP_REDISPLAY;
}

GEOC_APP_REQUEST_CODE TriangleState::mouseMove(const Vector3& pos)
{
    pts[points_entered] = pos;
    triangle = triangle_ent(pts);
    return GEOC_APP_REDISPLAY;
}

void TriangleState::cancel()
{
    points_entered = 0;
    pts[0] = pts[1] = pts[2] = zero3;
}

void TriangleState::draw(Graphics& gfx)
{
    if (points_entered == 1 || points_entered == 2)
    {
        gfx.drawSegment(triangle[0], triangle[1]);
    }
    if (points_entered == 2)
    {
        gfx.drawTriangle(triangle[0], triangle[1], triangle[2]);
    }
}

const char* TriangleState::description() const
{
    return "Triangle mode";
}
