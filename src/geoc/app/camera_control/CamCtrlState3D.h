#ifndef _INPUT_STATE_3D_H
#define _INPUT_STATE_3D_H

#include <geoc/geoc.h>
#include <geoc/app/camera_control/CamCtrlState2D.h>

namespace geoc {

/** \ingroup CamCtrl */
//! State for controlling the camera in 3D.
class CamCtrlState3D : public CamCtrlState2D
{
    ScreenPos old_pos;
    bool initial_drag;
    
public:
    
    CamCtrlState3D(Camera& cam, const Input& input, Graphics& gfx, SceneManager& sceneMgr)
        : CamCtrlState2D(cam, input, gfx, sceneMgr), initial_drag (true) {}
    
    int mouseMoved(const ScreenPos& pos);
};

} //namespace geoc

#endif //_INPUT_STATE_3D_H
