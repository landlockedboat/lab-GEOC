#include <geoc/geoc.h>
#include <geoc/math/Spatial.h>
#include <geoc/math/Math.h>
#include <geoc/gl.h>

using namespace geoc;


Spatial::Spatial(const Vector3 &position, const Vector3 &target) : pos(position)
{
    lookAt(target);
}


void Spatial::applyTranslation() const
{
    glTranslatef(pos[X], pos[Y], pos[Z]);
}


void Spatial::applyRotation() const
{
    float angle = 2 * acos (rot.w) * TO_DEG;
    float s = angle == 0.0 ? 1.0 : 1.0 / sin(angle*0.5*TO_RAD);
    glRotatef (angle, s*rot.x, s*rot.y, s*rot.z);
}


void Spatial::applyInverseTranslation() const
{
    glTranslatef(-pos[X], -pos[Y], -pos[Z]);
}


void Spatial::applyInverseRotation() const
{
    float angle = 2 * acos (rot.w) * TO_DEG;
    float s = angle == 0.0 ? 1.0 : 1.0 / sin(angle*0.5*TO_RAD);
    glRotatef (-angle, s*rot.x, s*rot.y, s*rot.z);
}


void Spatial::rotate(num angle, num x, num y, num z)
{
    rot = qAxisAngle (angle, x, y, z) * rot;
}


void Spatial::yaw(const num angle)
{
    rot = qAxisAngle (angle, 0.0, 1.0, 0.0) * rot;
}


void Spatial::pitch(const num angle)
{
    rot = qAxisAngle (angle, 1.0, 0.0, 0.0) * rot;
}


void Spatial::roll(const num angle)
{
    rot = qAxisAngle (angle, 0.0, 0.0, 1.0) * rot;
}


void Spatial::setOrientation(const Vector3 &forward)
{
    num pitch, yaw;
    Math::createPitchFromForward(forward, pitch);
    Math::createYawFromForward(forward, yaw);
    rot = qAxisAngle (pitch, 1.0, 0.0, 0.0) * qAxisAngle (yaw, 0.0, 1.0, 0.0);
}


void Spatial::setRotation(num pitch, num yaw, num roll)
{
    rot = qAxisAngle (roll, 0.0, 0.0, 1.0) *
            qAxisAngle (pitch, 1.0, 0.0, 0.0) *
            qAxisAngle (yaw, 0.0, 1.0, 0.0);
}
