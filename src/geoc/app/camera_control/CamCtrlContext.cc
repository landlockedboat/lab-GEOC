#include <geoc/geoc.h>
#include <geoc/app/camera_control/CamCtrlContext.h>
#include <geoc/app/camera_control/CamCtrlState.h>
#include <geoc/app/camera_control/CamCtrlState2D.h>
#include <geoc/app/camera_control/CamCtrlState3D.h>
#include <geoc/app/update_requests.h>
#include <geoc/camera/Camera.h>


using namespace geoc;


CamCtrlContext::CamCtrlContext(const Input& input, Graphics& gfx, SceneManager& sceneMgr)
{
    state2D = new CamCtrlState2D(cam, input, gfx, sceneMgr);
    state3D = new CamCtrlState3D(cam, input, gfx, sceneMgr);
    currentState = state2D;
}


CamCtrlContext::~CamCtrlContext()
{
    delete state2D;
    delete state3D;
}


int CamCtrlContext::mouseMoved(const ScreenPos& pos)
{
    return currentState->mouseMoved(pos);
}


int CamCtrlContext::mouseWheel(int delta)
{
    return currentState->mouseWheel(delta);
}


int CamCtrlContext::keyPressed(Keyboard::key key)
{
    int request_code = GEOC_APP_NO_REQUEST;
    
    if (key == Keyboard::Key_2)
    {
        setState(state2D);
        request_code |= GEOC_APP_STATUS_BAR_UPDATE;
    }
    else if (key == Keyboard::Key_3)
    {
        setState(state3D);
        request_code |= GEOC_APP_STATUS_BAR_UPDATE;
    }
    else request_code |= currentState->keyPressed(key);
    
    return request_code;
}


void CamCtrlContext::setState(CamCtrlState* state)
{
    currentState = state;
}


void CamCtrlContext::resetCamera()
{
    currentState->resetCamera();
}


void CamCtrlContext::updateZoom()
{
    currentState->updateZoom();
}


void CamCtrlContext::centerCamera()
{
    currentState->centerCamera();
}


std::string CamCtrlContext::getCameraMode()
{
    if (getState() == get2Dstate()) return "2D";
    return "3D";
}


std::string CamCtrlContext::getCameraProjection()
{
    if (cam.mode() == CAMERA_ORTHOGONAL) return "orthogonal";
    return "perspective";
}
