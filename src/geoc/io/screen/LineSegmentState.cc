#include <geoc/io/screen/LineSegmentState.h>
#include <geoc/gfx/Graphics.h>

using namespace geoc;

LineSegmentState::LineSegmentState()
{
    points_entered = 0;
}

GEOC_APP_REQUEST_CODE LineSegmentState::mouseClick(const Vector3& pos)
{
    pts[points_entered] = pos;
    points_entered++;
    
    if (points_entered == 1)
    {
        pts[1] = pts[0];
        segment = linesegment_ent(pts);
    }
    else if (points_entered == 2)
    {
        enters(new LineSegmentEnt(segment));
        cancel();
    }
    
    return GEOC_APP_REDISPLAY;
}

GEOC_APP_REQUEST_CODE LineSegmentState::mouseMove(const Vector3& pos)
{
    pts[points_entered] = pos;
    segment = linesegment_ent(pts);
    return GEOC_APP_REDISPLAY;
}

void LineSegmentState::cancel()
{
    points_entered = 0;
    pts[0] = pts[1] = zero3;
}

void LineSegmentState::draw(Graphics& gfx)
{
    if (points_entered == 1)
    {
        segment.draw(gfx);
    }
}

const char* LineSegmentState::description() const
{
    return "Line segment mode";
}
