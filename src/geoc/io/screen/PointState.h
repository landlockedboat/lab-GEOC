#ifndef _GEOC__POINT_STATE_H
#define _GEOC__POINT_STATE_H

#include <geoc/geoc.h>
#include <geoc/scene/Point.h>
#include <geoc/io/screen/ScreenState.h>

namespace geoc {

/** \ingroup Screen */
//! A state for reading points from the screen.
class DECLDIR PointState : public ScreenState<Point>
{
    Point cursor;
    
public:
    
    GEOC_APP_REQUEST_CODE mouseClick(const Vector3& pos);
    GEOC_APP_REQUEST_CODE mouseMove(const Vector3& pos);
    void cancel();
    void draw(Graphics& gfx);
    const char* description() const;
};

} //namespace geoc

#endif //_GEOC_POINT_STATE_H
