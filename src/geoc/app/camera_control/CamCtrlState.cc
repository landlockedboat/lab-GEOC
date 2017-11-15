#include <geoc/geoc.h>
#include <geoc/app/camera_control/CamCtrlState.h>
#include <geoc/app/camera_control/CamCtrlContext.h>
#include <geoc/app/update_requests.h>
#include <geoc/io/input/Input.h>
#include <geoc/gfx/Graphics.h>
#include <geoc/camera/Camera.h>
#include <geoc/math/Math.h>
#include <geoc/math/Vector.h>
#include <geoc/scene/SceneManager.h>
#include <cmath>

using namespace std;
using namespace geoc;

#define PERSPECTIVE_SENSITIVITY	cam.sensitivity() * Math::abs(cam.position()[Z]) * 0.005


CamCtrlState::CamCtrlState(Camera& camera, const Input& inputSys, Graphics& graphics, SceneManager& sceneManager)
    : cam(camera), input(inputSys), gfx(graphics), sceneMgr(sceneManager) {}


int CamCtrlState::keyPressed(Keyboard::key key)
{
    switch (key)
    {
    case Keyboard::Key_I:
    {
	resetCamera();
	return GEOC_APP_REDISPLAY | GEOC_APP_STATUS_BAR_UPDATE;
    }
	
    case Keyboard::Key_F:
	gfx.toggleWireframe();
	return GEOC_APP_REDISPLAY;
	
    case Keyboard::Key_V:
    {
	cam.toggleMode();
	return GEOC_APP_REDISPLAY | GEOC_APP_STATUS_BAR_UPDATE;
    }
	
    default: break;
    }
    return GEOC_APP_NO_REQUEST;
}


int CamCtrlState::mouseMoved(const ScreenPos& pos)
{
    int request_code = GEOC_APP_NO_REQUEST;
    num dx, dy;
    input.getMouseDelta(&dx, &dy);
    
    if (input.buttonDown(Mouse::LMB))
    {
	if (input.keyDown(Keyboard::Key_Z))
	{
	    sceneMgr.roll(-dx * cam.sensitivity());
	    request_code |= GEOC_APP_REDISPLAY;
	}
	else if (!input.keyDown(Keyboard::Key_shift) && !input.keyDown(Keyboard::Key_ctrl))
	{
	    //Calculate the displacement in world coordinates and translate
	    //the camera by that amount.
	    Vector3 v1, v2;
	    Vector2 delta = Vector2(dx, dy);
	    
	    v1 = Math::viewportToWorld(pos - delta, cam);
	    v2 = Math::viewportToWorld(pos, cam);
	    
	    Vector3 disp = v1 - v2;
	    cam.move(disp);
	    request_code |= GEOC_APP_REDISPLAY;
	}
	else if (input.keyDown(Keyboard::Key_shift))
	{
	    if (cam.mode() == CAMERA_ORTHOGONAL)	cam.zoom(-dy);
	    else									cam.moveForwards(-dy * PERSPECTIVE_SENSITIVITY);
	    request_code |= GEOC_APP_REDISPLAY;
	}
    }
    
    return request_code;
}


int CamCtrlState::mouseWheel(int delta)
{
    if (cam.mode() == CAMERA_ORTHOGONAL)	cam.zoom(delta);
    else									cam.moveForwards(delta * PERSPECTIVE_SENSITIVITY);
    return GEOC_APP_REDISPLAY;
}


void CamCtrlState::resetCamera()
{
    sceneMgr.setRotation(zero3);
    cam.setOrientation(forward3);
    cam.setMode(CAMERA_ORTHOGONAL);
    updateZoom();
    centerCamera();
}


void CamCtrlState::updateZoom()
{
    if (!sceneMgr.empty())
    {
	num scene_width = sceneMgr.width();
	num scene_height = sceneMgr.height();
	cam.computeZoom(scene_width, scene_height);
    }
}


void CamCtrlState::centerCamera()
{
    if (!sceneMgr.empty())
    {
	num scene_width		= sceneMgr.width();
	num scene_height	= sceneMgr.height();
	num scene_depth		= sceneMgr.depth();
	cam.center(sceneMgr.center(), scene_width, scene_height, scene_depth);
    }
}
