#ifndef _GEOC_TRIANGLE_STATE_H
#define _GEOC_TRIANGLE_STATE_H

#include <geoc/geoc.h>
#include <geoc/io/screen/ScreenState.h>
#include <geoc/scene/TriangleEnt.h>

namespace geoc {

/** \ingroup Screen */
//! A state for reading triangles from the screen.
class DECLDIR TriangleState : public ScreenState<TriangleEnt>
{
    Vector3				pts[3];
    geoc::TriangleEnt	triangle;
    int					points_entered;
    
public:
    
    TriangleState();
    
    GEOC_APP_REQUEST_CODE mouseClick(const Vector3& pos);
    GEOC_APP_REQUEST_CODE mouseMove(const Vector3& pos);
    void cancel();
    void draw(Graphics& gfx);
    const char* description() const;
};

} //namespace geoc

#endif //GEOC_TRIANGLE_STATE_H
