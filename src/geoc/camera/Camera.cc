#include "Camera.h"
#include <geoc/math/Math.h>
#include <geoc/gl.h>
#include <geoc/glu.h>

#ifdef _GEOC_DEBUG
#include <geoc/GeocException.h>
#endif


using namespace geoc;


static num CAM_SENSITIVITY  = 0.5;
static num MIN_ZOOM	    = 0.00025;
static num DEFAULT_NEAR     = 1.0;
static num DEFAULT_FAR      = 5000.0;
static num DEFAULT_FOV      = 45.0;


Camera::Camera() : Spatial(Vector3(0, 0, 425), forward3),
    m_fov(DEFAULT_FOV), _near(DEFAULT_NEAR), _far(DEFAULT_FAR), m_zoom(1),
    m_sensitivity(CAM_SENSITIVITY), m_mode(CAMERA_ORTHOGONAL) {}


Camera::Camera(const Vector3& pos, const Vector3& target) : Spatial(pos, target),
    m_fov(DEFAULT_FOV), _near(DEFAULT_NEAR),
    _far(DEFAULT_FAR), m_zoom(1), m_sensitivity(CAM_SENSITIVITY), m_mode(CAMERA_ORTHOGONAL) {}


void Camera::applyTransformationMatrix() const
{
    applyInverseTranslation();
    applyInverseRotation();
}


void Camera::applyProjectionMatrix() const
{
    switch (m_mode)
    {
    case CAMERA_PERSPECTIVE:
        applyPerspectiveView();
        break;
        
    case CAMERA_ORTHOGONAL:
        applyOrthogonalView();
        break;
        
        GEOC_DEBUG_CODE(default: throw GEOC_EXCEPTION("Unknown mode");)
    }
}


void Camera::applyPerspectiveView() const
{
    num aspect = _width / _height;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(m_fov, aspect, _near, _far);
    glMatrixMode(GL_MODELVIEW);
}


void Camera::applyOrthogonalView() const
{
    num scale = 1.0 / m_zoom * 0.5;
    num width = _width;
    num height = _height;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width * scale, width * scale, -height * scale, height * scale, _near, _far);
    glMatrixMode(GL_MODELVIEW);
}


void Camera::setMode(CAMERA_MODE mode)
{
    m_mode = mode;
}


void Camera::toggleMode()
{
    if (m_mode == CAMERA_PERSPECTIVE) setMode(CAMERA_ORTHOGONAL);
    else setMode(CAMERA_PERSPECTIVE);
}


void Camera::zoom(num f)
{
    setZoom(m_zoom + f * m_sensitivity * m_zoom * 0.003);
}


void Camera::setZoom(num zoom)
{
    if (zoom < MIN_ZOOM) m_zoom = MIN_ZOOM;
    else m_zoom = zoom;
}


void Camera::computeZoom(num scene_width, num scene_height)
{
    static const num margin = 0.9;
    
    scene_width = (scene_width == 0.0) ? 1.0 : scene_width;
    scene_height = (scene_height == 0.0) ? 1.0 : scene_height;
    
    if (scene_width / _width > scene_height / _height)
    {
        m_zoom = _width / scene_width * margin;
    }
    else
    {
        m_zoom = _height / scene_height * margin;
    }
}


void Camera::center(const Vector3& scene_center, num scene_width, num scene_height, num scene_depth)
{
    // Position is irrelevant for an orthogonal camera, so assume persective
    // mode and set a position that suits it.
    Vector3 cam_pos	= scene_center;
    num fov_vert = m_fov * TO_RAD;
    num off = 0;
    
    num off1 = scene_height / (2 * tan(fov_vert / 2));
    
    num r = _width / _height;
    num fov_hor  = 2 * atan(r * tan(fov_vert / 2));
    num off2 = scene_width / (2 * tan(fov_hor / 2));
    
    off = std::max(off1, off2);
    
    // Margin.
    off *= 1.1;
    
    cam_pos[Z] = cam_pos[Z] + (scene_depth / 2) + off + _near;
    setPosition(cam_pos);
    
    // Adjust far clip
    num d = Math::max(scene_width, scene_height, scene_depth);
    num range = off + _near + d + 1.0;
    _far = _far < range ? range : _far;
}


void Camera::setDimensions(int width, int height)
{
    _width  = width;
    _height = height;
}
