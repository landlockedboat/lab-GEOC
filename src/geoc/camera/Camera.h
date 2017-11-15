#ifndef _GEOC_CAMERA_H
#define _GEOC_CAMERA_H

#include <geoc/geoc.h>
#include <geoc/math/Spatial.h>

namespace geoc {

enum CAMERA_MODE { CAMERA_PERSPECTIVE, CAMERA_ORTHOGONAL };

/** \ingroup Camera */
//! A camera in 3D space.
class DECLDIR Camera : public Spatial
{
    num m_fov;		/*!< Vertical field of view angle in degrees. */
    num _near;		/*!< Near clip distance. */
    num _far;		/*!< Far clip distance. */
    num m_zoom;		/*!< Zoom factor. */
    num m_sensitivity;	/*!< Sensitivity factor. */
    num _width;		/*!< The viewports's width. */
    num _height;	/*!< The viewports's height. */
    CAMERA_MODE m_mode;	/*!< Current camera mode (orthogonal or perspective view). */
    
    //! Applies the camera's perspective projection matrix.
    void applyPerspectiveView() const;
    
    //! Applies the camera's orthogonal projection matrix.
    void applyOrthogonalView() const;
    
public:
    
    //! Constructor.
    /*!
     * Default values:
     * field of view (vertical): 45
     * zoom: 1
     * near: 1.0
     * far: 1000.0
     */
    Camera();
    
    //! Constructor.
    /*!
     * \param pos The camera's position.
     * \param target The camera's look target.
     * Default values:
     * field of view (vertical): 45
     * zoom: 1
     * near: 1.0
     * far: 1000.0
     */
    Camera(const Vector3& pos, const Vector3& target);
    
    //! Applies the camera's transformation matrix.
    /*!
     * Multiplies the current matrix stack with the camera's inverse transform.
     * Call this method prior to drawing geometry to transform the geometry from
     * world space to view space.
     */
    void applyTransformationMatrix() const;
    
    //! Applies the camera's projection matrix.
    /*!
     * Loads the camera's projection matrix onto the projection matrix stack.
     * The top of the stack is replaced with the camera's projection matrix.
     */
    void applyProjectionMatrix() const;
    
    //! Sets the camera's sensitivity.
    /*!
     * \param s The camera's sensitivity.
     */
    void setSensitivity(num s) { m_sensitivity = s; }
    
    //! Sets the camera's projection mode.
    /*!
     * \param mode The kind of projection mode, either CAMERA_ORTHOGONAL or CAMERA_PERSPECTIVE.
     * \sa CAMERA_MODE
     */
    void setMode(CAMERA_MODE mode);
    
    //! Toggles the camera's projection mode.
    void toggleMode();
    
    //! Makes the camera zoom in or out.
    /*!
     * \param f The amount of zoom. A positive zoom makes the camera zoom in; a negative one makes the camera zoom out.
     */
    void zoom(num f);
    
    //! Sets the camera's zoom.
    /*!
     * \param f The desired zoom. Notice that this call does not add to the current zoom; it will replace it instead.
     */
    void setZoom(num f);
    
    //! Computes the camera's zoom.
    void computeZoom(num scene_width, num scene_height);
    
    //! Centers the camera so that the entire scene is visible.
    /**
     * \param scene_center The scene's center.
     * \param scene_width The scene's width.
     * \param scene_height The scene's height.
     * \param scene_depth The scene's depth.
     */
    void center(const Vector3& scene_center, num scene_width, num scene_height, num scene_depth);
    
    //! Sets the camera's near clip.
    /*!
     * \param f The desired near clip.
     */
    void setNearClip(num f) { _near = f; }
    
    //! Sets the camera's far clip.
    /*!
     * \param f The desired far clip.
     */
    void setFarClip(num f) { _far = f; }
    
    //! Sets the camera's clip dimensions and aspect ratio.
    /*!
     * \param width The viewport's width.
     * \param height The viewport's height.
     */
    void setDimensions(int width, int height);
    
    //! Gets the camera's projection mode.
    /*!
     * \return A value representing the camera's projection mode.
     * \sa CAMERA_MODE
     */
    CAMERA_MODE mode() const { return m_mode; }
    
    //! Gets the camera's zoom.
    num zoom() const { return m_zoom; }
    
    //! Gets the camera's near clip.
    num nearClip() const { return _near; }
    
    //! Gets the camera's far clip.
    num farClip() const { return _far; }
    
    //! Gets the camera's sensitivity.
    num sensitivity() const { return m_sensitivity; }
};

} //namespace geoc


#endif //_GEOC_CAMERA_H
