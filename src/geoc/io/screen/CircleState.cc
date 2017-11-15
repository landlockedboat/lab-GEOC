#include <geoc/io/screen/CircleState.h>
#include <geoc/gfx/Graphics.h>

using namespace geoc;


CircleState::CircleState() : points_entered(0) {}


GEOC_APP_REQUEST_CODE CircleState::mouseClick(const Vector3& pos)
{
    pts[points_entered] = pos;
    points_entered++;
    
    if (points_entered == 1 || points_entered == 2)
    {
        pts[points_entered] = pos;
        circle = circle_ent(pts);
    }
    else if (points_entered == 3)
    {
        circle = circle_ent(pts);
        enters(new CircleEnt(circle));
        cancel();
    }
    
    return GEOC_APP_REDISPLAY;
}


GEOC_APP_REQUEST_CODE CircleState::mouseMove(const Vector3& pos)
{
    pts[points_entered] = pos;
    circle = circle_ent(pts);
    return GEOC_APP_REDISPLAY;
}


void CircleState::cancel()
{
    points_entered = 0;
    pts[0] = pts[1] = pts[2] = zero3;
}


void CircleState::draw(Graphics& gfx)
{
    if (points_entered == 1)
    {
        gfx.drawSegment(circle[0], circle[1]);
    }
    else if (points_entered == 2)
    {
        gfx.drawCircle(&circle);
    }
}


const char* CircleState::description() const
{
    return "Circle mode";
}
