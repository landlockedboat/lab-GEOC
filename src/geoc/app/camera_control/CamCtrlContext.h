#ifndef _GEOC_INPUT_CONTROL_H
#define _GEOC_INPUT_CONTROL_H

#include <geoc/geoc.h>
#include <geoc/camera/Camera.h>
#include <geoc/io/input/Keyboard.h>
#include <geoc/math/Vector_fwd_decl.h>
#include <string>

namespace geoc {

class Input;
class CamCtrlState;
class Camera;
class Graphics;
class SceneManager;


/** \ingroup CamCtrl */
//! The subsystem responsible for controlling the camera.
class CamCtrlContext
{
    CamCtrlState*   currentState;
    CamCtrlState*   state2D;
    CamCtrlState*   state3D;
    Camera          cam;
    
public:
    
    CamCtrlContext(const Input& input, Graphics& gfx, SceneManager& sceneMgr);
    
    ~CamCtrlContext();
    
    //! Changes the camera's transform accordingly.
    /*!
     * \param key The pressed key.
     * \return A GEOC_APP_REQUEST_CODE.
     * \sa GEOC_APP_REQUEST_CODE
     * \sa Keyboard::key
     */
    int keyPressed(Keyboard::key key);
    
    //! Changes the camera's transform accordingly.
    /*!
     * \param pos The current mouse position.
     * \return A GEOC_APP_REQUEST_CODE.
     * \sa GEOC_APP_REQUEST_CODE
     * \sa ScreenPos
     */
    int mouseMoved(const ScreenPos& pos);
    
    //! Changes the camera's transform accordingly.
    /*!
     * \param delta The distance the wheel is rotated.
     * \return A GEOC_APP_REQUEST_CODE.
     * \sa GEOC_APP_REQUEST_CODE
     */
    int mouseWheel(int delta);
    
    //! Changes the CamCtrlContext's state.
    /*!
     * \param state The state to set the CamCtrlContext to.
     * \sa CamCtrlState
     */
    void setState(CamCtrlState* state);
    
    //! Sets default values for the camera.
    void resetCamera();
    
    //! Updates the camera's zoom.
    /*!
    * Call this whenever the scene dimensions change to let the camera update
    * its zoom so that the entire scene is viewed on the screen.
    */
    void updateZoom();
    
    //! Centers the camera.
    /*!
    * Call this when the scene dimensions change so that the camera can
    * center itself properly.
    */
    void centerCamera();
    
    //! Updates the camera's viewport settings.
    /*!
     * \param width The viewport's width.
     * \param height The viewport's height.
     */
    void setDimensions(int width, int height) { cam.setDimensions(width, height); }
    
    //! Gets a string describing the current camera mode.
    std::string getCameraMode();
    
    //! Gets a string describing the camera's projection.
    std::string getCameraProjection();
    
    //! Gets the context's camera.
    /*!
     * \sa Camera
     */
    const Camera& camera () const { return cam; }
    
    //! Gets the current state.
    /*!
     * \return The current CamCtrlState.
     * \sa CamCtrlState
     */
    CamCtrlState* getState() const { return currentState; }
    
    //! Gets the 2D state.
    /*!
     * \return The machine's CamCtrlState2D.
     * \sa CamCtrlState
     */
    CamCtrlState* get2Dstate() const { return state2D; }
    
    //! Gets the 3D state.
    /*!
    * \return The machine's CamCtrlState3D.
    * \sa CamCtrlState
    */
    CamCtrlState* get3Dstate() const { return state3D; }
};

} //namespace geoc

#endif //_GEOC_INPUT_CONTROL_H
