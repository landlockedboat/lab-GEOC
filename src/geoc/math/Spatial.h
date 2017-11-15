#ifndef _GEOC_SPATIAL_H
#define _GEOC_SPATIAL_H


#include <geoc/geoc.h>
#include "Vector.h"
#include "Quaternion.h"


namespace geoc {


/** \ingroup Math */
//! A spatial in 3D space.
class DECLDIR Spatial
{
    Vector3 pos;
    Quaternion rot;
    
public:
    
    //! Creates a Spatial.
    /*!
     * Default values:
     * position: origin.
     * forward: world space forward.
     * right: world space right.
     * up: world space up.
     */
    Spatial() {}
    
    //! Creates a Spatial.
    Spatial(const Vector3& position, const Vector3& target);
    
    virtual ~Spatial() {}
    
    //! Applies the Spatial's translation.
    void applyTranslation() const;
    
    //! Applies the Spatial's rotation.
    void applyRotation() const;
    
    //! Applies the Spatial's inverse translation.
    void applyInverseTranslation() const;
    
    //! Applies the Spatial's inverse rotation.
    void applyInverseRotation() const;
    
    //! Moves the Spatial in a given direction at a given speed.
    void move(const Vector3 &direction) { pos = pos + direction; }
    
    //! Moves the Spatial forwards.
    void moveForwards(num speed) { pos = pos + forward3 * speed; }
    
    //! Moves the Spatial backwards.
    void moveBackwards(num speed) { pos = pos - forward3 * speed; }
    
    //! Moves the Spatial to its left.
    void strafeLeft(num speed) { pos = pos - right3 * speed; }
    
    //! Moves the Spatial to its right.
    void strafeRight(num speed) { pos = pos + right3 * speed; }
    
    //! Moves the Spatial up.
    void moveUp(num speed) { pos = pos + up3 * speed; }
    
    //! Moves the Spatial down.
    void moveDown(num speed) { pos = pos - up3 * speed; }
    
    //! Rotates the Spatial about the given axis
    /*!
     * \param angle The angle of rotation.
     * \param x The x coordinate of the axis of rotation.
     * \param y The y coordinate of the axis of rotation.
     * \param z The z coordinate of the axis of rotation.
     */
    void rotate(num angle, num x, num y, num z);
    
    //! Rotates the Spatial about the given axis.
    /*!
     * \param angle The angle of rotation.
     * \param axis The axis of rotation.
     */
    void rotate(num angle, Vector3 axis) { rotate (angle, axis[X], axis[Y], axis[Z]); }
    
    //! Rotates the Spatial about the y axis.
    /*!
     * \param angle The angle in degrees.
     */
    void yaw(const num angle);
    
    //! Rotates the Spatial about the X axis.
    /*!
     * \param angle The angle in degrees.
     */
    void pitch(const num angle);
    
    //! Rotates the Spatial about the Z axis.
    /*!
     * \param angle The angle in degrees.
     */
    void roll(const num angle);
    
    //! Sets the Spatial's position.
    void setPosition(num x, num y, num z) { pos = Vector3(x, y, z); }
    
    //! Sets the Spatial's position.
    void setPosition(const Vector3 &v) { setPosition(v[X], v[Y], v[Z]); }
    
    //! Sets the Spatial's orientation.
    /*! The direction parameter becomes the Spatial's forward vector. */
    void setOrientation(num x, num y, num z) { setOrientation(Vector3(x,y,z)); }
    
    //! Sets the Spatial's orientation.
    /*! The direction parameter becomes the Spatial's forward vector. */
    void setOrientation(const Vector3 &forward);
    
    //! Sets the Spatial's target.
    void lookAt(num x, num y, num z) { setOrientation(Vector3(x,y,z) - pos); }
    
    //! Sets the Spatial's target.
    void lookAt(const Vector3 &target) { setOrientation(target - pos); }
    
    //! Sets the Spatial's rotation.
    void setRotation(num pitch, num yaw, num roll);
    
    //! Sets the Spatial's rotation.
    void setRotation(const Vector3 &v) { setRotation(v[X], v[Y], v[Z]); }
    
    //! Returns the Spatial's position.
    const Vector3& position() const { return pos; }
    
    //! Returns the Spatial's forward vector.
    const Vector3 forward() const { return geoc::rotate (rot, forward3); }
    
    //! Returns the Spatial's right vector.
    const Vector3 right() const { return geoc::rotate (rot, right3); }
    
    //! Returns the Spatial's up vector.
    const Vector3 up() const { return geoc::rotate (rot, up3); }
};


} //namespace geoc


#endif //_GEOC_SPATIAL_H
