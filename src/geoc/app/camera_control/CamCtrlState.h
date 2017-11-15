#ifndef _GEOC_INPUT_STATE_H
#define _GEOC_INPUT_STATE_H

#include <geoc/geoc.h>
#include <geoc/io/input/Keyboard.h>
#include <geoc/app/update_requests.h>
#include <geoc/math/Vector.h>

namespace geoc {

class Input;
class CamCtrlContext;
class Camera;
class Graphics;
class SceneManager;

/** \ingroup CamCtrl */
//! A base class for every camera control state.
/*! See CamCtrlContext for information on each method. */
class CamCtrlState
{
protected:
    
    Camera&	      cam;
    const Input&  input;
    Graphics&	  gfx;
    SceneManager& sceneMgr;
    num		      scene_d;
    
public:
    
    CamCtrlState(Camera& camera, const Input& inputSys, Graphics& graphics, SceneManager& sceneManager)
        : cam(camera), input(inputSys), gfx(graphics), sceneMgr(sceneManager) {}
    
    virtual ~CamCtrlState() {}
    
    //! Notifies the state that a key has been pressed.
    /**
     * \param key The pressed key.
     * \sa Keyboard::key
     */
    virtual int keyPressed(Keyboard::key) { return GEOC_APP_NO_REQUEST; }
    
    //! Notifies the state that the mouse has moved.
    /**
     * \param pos The new mouse position.
     * \sa ScreenPos
     */
    virtual int mouseMoved(const ScreenPos&) { return GEOC_APP_NO_REQUEST; }
    
    //! Notifies the state that the mouse wheel has moved.
    /**
     * \param delta The distance the wheel has moved.
     */
    virtual int mouseWheel(int) { return GEOC_APP_NO_REQUEST; }
    
    //! Requests the state to reset the camera's default values.
    virtual void resetCamera() {}
    
    //! Requests the state to update the camera's zoom.
    virtual void updateZoom() {}
    
    //! Requests the state to center the camera around the scene.
    virtual void centerCamera() {}
};

} //namespace geoc

#endif //_GEOC_INPUT_STATE_H
