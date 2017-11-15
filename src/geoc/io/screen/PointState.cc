#include <geoc/io/screen/PointState.h>
#include <geoc/gfx/Graphics.h>

using namespace geoc;
using namespace std;

GEOC_APP_REQUEST_CODE PointState::mouseClick(const Vector3& pos)
{
    //Notify observers.
    enters(new Point(pos));
    return GEOC_APP_REDISPLAY;
}

GEOC_APP_REQUEST_CODE PointState::mouseMove(const Vector3& pos)
{
    cursor = Point(pos);
    return GEOC_APP_REDISPLAY;
}

void PointState::cancel()
{
    
}

void PointState::draw(Graphics& gfx)
{
    cursor.draw(gfx);
}

const char* PointState::description() const { return "Point mode"; }
