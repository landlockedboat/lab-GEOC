#include <geoc/app/camera_control/CamCtrlState3D.h>
#include <geoc/io/input/Input.h>
#include <geoc/camera/Camera.h>
#include <geoc/scene/SceneManager.h>


using namespace geoc;


int CamCtrlState3D::mouseMoved(const ScreenPos& pos)
{
    int request_code = CamCtrlState2D::mouseMoved(pos);
    
    if (input.keyDown(Keyboard::Key_ctrl) && input.buttonDown(Mouse::LMB))
    {
        num dx, dy;
        input.getMouseDelta(&dx, &dy);
        num sensitivity = cam.sensitivity();
        
        sceneMgr.yaw(dx * sensitivity);
        sceneMgr.pitch(dy * sensitivity);
        request_code |= GEOC_APP_REDISPLAY;
    }
    return request_code;
}
