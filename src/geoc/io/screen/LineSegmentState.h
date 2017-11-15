#ifndef _GEOC_LINE_SEGMENT_STATE_H
#define _GEOC_LINE_SEGMENT_STATE_H

#include <geoc/geoc.h>
#include <geoc/scene/LineSegmentEnt.h>
#include <geoc/io/screen/ScreenState.h>

namespace geoc {

/** \ingroup Screen */
//! A state for reading line segments from the screen.
class DECLDIR LineSegmentState : public ScreenState<LineSegmentEnt>
{
    Vector3					pts[2];
    geoc::LineSegmentEnt	segment;
    int						points_entered;
    
public:
    
    LineSegmentState();
    
    GEOC_APP_REQUEST_CODE mouseClick(const Vector3& pos);
    GEOC_APP_REQUEST_CODE mouseMove(const Vector3& pos);
    void cancel();
    void draw(Graphics& gfx);
    const char* description() const;
};

} //namespace geoc

#endif //_GEOC_LINE_SEGMENT_STATE_H
