#ifndef _GEOC_POLYGON_STATE_H
#define _GEOC_POLYGON_STATE_H

#include <geoc/geoc.h>
#include <geoc/io/screen/ScreenState.h>
#include <geoc/math/Vector.h>
#include <list>

namespace polygon {
class Polygon;
}

class PolygonState : public geoc::ScreenState<polygon::Polygon>
{
    std::list<geoc::Vector3>	vertices;
    
public:
    
    GEOC_APP_REQUEST_CODE mouseClick(const geoc::Vector3& pos);
    GEOC_APP_REQUEST_CODE mouseRightClick(const geoc::Vector3& pos);
    GEOC_APP_REQUEST_CODE mouseMove(const geoc::Vector3& pos);
    void cancel();
    void draw(geoc::Graphics& gfx);
    const char* description() const;
};


#endif //_GEOC_POLYGON_STATE_H
