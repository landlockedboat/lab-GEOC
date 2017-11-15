#ifndef _INPUT_STATE_2D_H
#define _INPUT_STATE_2D_H

#include <geoc/geoc.h>
#include <geoc/app/camera_control/CamCtrlState.h>

namespace geoc {

/** \ingroup CamCtrl */
//! State for controlling the camera in 2D.
class CamCtrlState2D : public CamCtrlState
{
public:
    
    CamCtrlState2D(Camera& cam, const Input& input, Graphics& gfx, SceneManager& sceneMgr)
        : CamCtrlState(cam, input, gfx, sceneMgr) {}
    
    
    int keyPressed(Keyboard::key key);
    
    int mouseMoved(const ScreenPos& pos);
    
    int mouseWheel(int delta);
    
    virtual void resetCamera();
    
    virtual void updateZoom();
    
    virtual void centerCamera();
};

} //namespace geoc

#endif //_INPUT_STATE_2D_H
