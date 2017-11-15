#ifndef _GEOC_CIRCLE_STATE_H
#define _GEOC_CIRCLE_STATE_H

#include <geoc/geoc.h>
#include <geoc/io/screen/ScreenState.h>
#include <geoc/scene/CircleEnt.h>

namespace geoc {

/** \ingroup Screen */
//! A state for reading circles from the screen.
class DECLDIR CircleState : public ScreenState<CircleEnt>
{
    Vector3 pts[3];
    geoc::CircleEnt circle;
    int points_entered;
    
public:
    
    CircleState();
    
    GEOC_APP_REQUEST_CODE mouseClick(const Vector3& pos);
    GEOC_APP_REQUEST_CODE mouseMove(const Vector3& pos);
    void cancel();
    void draw(Graphics& gfx);
    const char* description() const;
};

} //namespace geoc

#endif //_GEOC_CIRCLE_STATE_H
