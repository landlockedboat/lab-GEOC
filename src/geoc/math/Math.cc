#include "Math.h"
#include "Vector.h"
#include "Spatial.h"
#include <geoc/gl.h>
#include <geoc/glu.h>

using namespace geoc;
using namespace std;


void Math::createYawPitchRoll(	const Vector3& forward, const Vector3& right, num& yaw, num& pitch, num& roll)
{
    createPitchFromForward(forward, pitch);
    createYawFromForward(forward, yaw);
    createRollFromRight(right, roll);
}


void Math::createPitchFromForward(const Vector3& forward, num& pitch)
{
    // Use the XY plane's normal - the forward vector.
    // If the vector is on the XZ plane, the pitch is 0.
    Vector3 f = Vector3(forward[X], 0.0, forward[Z]);
    f.normalise();
    pitch = acos(dot(f, forward)) * TO_DEG * signOf(forward[Y]);
}


void Math::createYawFromForward(const Vector3& forward, num& yaw)
{
    // Use the XY plane's normal - the forward vector.
    Vector3 f = Vector3(forward[X], 0.0, forward[Z]);
    f.normalise();
    yaw = acos(dot(f, forward3)) * TO_DEG * -signOf(forward[X]);
}


void Math::createRollFromRight(const Vector3& right, num& roll)
{
    // Use the YZ plane's normal - the right vector.
    // If the vector is on the XZ plane, the roll is 0.
    if (!right[Y]) roll = 0.0;
    else
    {
        Vector3 f = Vector3(right[X], right[Y], 0.0);
        f.normalise();
        roll = acos(dot(f, right3)) * TO_DEG * -signOf(right[Y]);
    }
}


void Math::calculateVectors(num yaw, num pitch, num roll, Vector3& right, Vector3& up, Vector3& forward)
{
    calculateForwardVector(yaw, pitch, forward);
    calculateRightVector(yaw, roll, right);
    calculateUpVector(pitch, roll, up);
}


void Math::calculateVectors(const Vector3& forward, Vector3& right, Vector3& up)
{
    right = cross(up3, forward);
    up = cross(forward, right);
    right.normalise();
    up.normalise();
}


void Math::calculateForwardVector(num yaw, num pitch, Vector3& out)
{
    // The results come from multiplying the matrices ROT_X * ROT_Y and reading the 3rd row.
    num y = yaw * TO_RAD;
    num x = pitch * TO_RAD;
    
    out = -Vector3(-cos(-x)*sin(-y), sin(-x), cos(-x)*cos(-y));
    out.normalise();
}


void Math::calculateRightVector(num yaw, num roll, Vector3& out)
{
    // The results come from multiplying the matrices ROT_Y * ROT_Z and reading the 1st row.
    num y = yaw * TO_RAD;
    num z = roll * TO_RAD;
    
    out = Vector3(cos(-y)*cos(-z), -cos(-y)*sin(-z), sin(-y));
    out.normalise();
}


void Math::calculateUpVector(num pitch, num roll, Vector3& out)
{
    // The results come from multiplying the matrices ROT_X * ROT_Z and reading the 2nd row.
    num x = pitch * TO_RAD;
    num z = roll * TO_RAD;
    
    out = Vector3(cos(-x)*sin(-z), cos(-x)*cos(-z), -sin(-x));
    out.normalise();
}


Vector3 intersect(const Vector3& p_near, const Vector3& p_far, const Spatial& cam)
{
    Vector3 ray = p_far - p_near;
    ray.normalise();
    
    // Intersect the ray with an imaginary plane containing the object's space origin and aiming at the camera.
    Vector3 normal = -cam.forward();
    
    num denominator = normal[X] * ray[X] + normal[Y] * ray[Y] + normal[Z] * ray[Z];
    if (denominator == 0.0) denominator = 1.0;
    
    // Calculate t.
    num t = -(normal[X] * p_near[X] + normal[Y] * p_near[Y] + normal[Z] * p_near[Z]) / denominator;
    
    // Insert t into the ray's parametric equation to find out the point's coordinates in object space.
    return p_near + ray * t;
}


Vector3 viewportToObjectSpace(num sx, num sy, num sz)
{
    GLdouble model_mat[16], proj_mat[16];
    GLdouble x, y, z; //, sz;
    GLint viewport[4];
    
    // Translate from window coordinates to OpenGL viewport coordinates.
    // (0,0) is top-left in window coordinates, bottom-left in viewport coordinates.
    glGetIntegerv(GL_VIEWPORT, viewport);
    num height	= viewport[3];
    sy = height - sy;
    
    glGetDoublev(GL_MODELVIEW_MATRIX, model_mat);
    glGetDoublev(GL_PROJECTION_MATRIX, proj_mat);
    //glReadPixels(sx, sy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &sz );
    
    gluUnProject(sx, sy, sz, model_mat, proj_mat, viewport, &x, &y, &z);
    return Vector3(x, y, z);
}


ScreenPos objectToViewportSpace(num x, num y, num z)
{
    GLdouble model_mat[16], proj_mat[16];
    GLdouble sx, sy, sz; //, sz;
    GLint viewport[4];
    
    // Translate from window coordinates to OpenGL viewport coordinates.
    // (0,0) is top-left in window coordinates, bottom-left in viewport coordinates.
    glGetIntegerv(GL_VIEWPORT, viewport);
    num height	= viewport[3];
    sy = height - sy;
    
    glGetDoublev(GL_MODELVIEW_MATRIX, model_mat);
    glGetDoublev(GL_PROJECTION_MATRIX, proj_mat);
    
    gluProject(x, y, z, model_mat, proj_mat, viewport, &sx, &sy, &sz);
    return ScreenPos(sx, sy);
}


ScreenPos Math::objectToViewport(const Spatial& spatial, const Spatial& cam, const Vector3& p)
{
    glPushMatrix();
    glLoadIdentity();
    
    cam.applyInverseRotation();
    cam.applyInverseTranslation();
    
    /*spatial.applyTranslation();
    spatial.applyRotation();
    spatial.applyInverseTranslation();*/
    
    ScreenPos pos = objectToViewportSpace(p[X], p[Y], p[Z]);
    
    glPopMatrix();
    
    return pos;
}


Vector3 Math::viewportToObject(const ScreenPos& pos, const Spatial& cam, const Spatial& spatial)
{
    glPushMatrix();
    
    glLoadIdentity();
    cam.applyInverseRotation();
    cam.applyInverseTranslation();
    
    spatial.applyTranslation();
    spatial.applyRotation();
    spatial.applyInverseTranslation();
    
    Vector3 p_near = viewportToObjectSpace(pos[X], pos[Y], 0.0);
    Vector3 p_far  = viewportToObjectSpace(pos[X], pos[Y], 1.0);
    
    glPopMatrix();
    
    return intersect(p_near, p_far, cam);
}


Vector3 Math::viewportToWorld(const ScreenPos& pos, const Spatial& cam)
{
    glPushMatrix();
    
    glLoadIdentity();
    cam.applyInverseRotation();
    cam.applyInverseTranslation();
    
    Vector3 p_near = viewportToObjectSpace(pos[X], pos[Y], 0.0);
    Vector3 p_far  = viewportToObjectSpace(pos[X], pos[Y], 1.0);
    
    glPopMatrix();
    
    return intersect(p_near, p_far, cam);
}


void Math::makeCounterClockwise(Vector3& v1, Vector3& v2, Vector3& v3)
{
    if (orientation2D(v1, v2, v3) < 0)
    {
        Vector3 aux = v3;
        v3 = v2;
        v2 = aux;
    }
}


int Math::nextPowerOfTwo(int x)
{
    double logbase2 = log((num)x) / log(2.0);
    return round(pow(2, ceil((num)logbase2)));
}


num Math::signOf(num x)
{
    if (x < 0) return -1;
    return 1;
}


num Math::max(num a, num b, num c)
{
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}


int Math::nextMultiple(int a, int b)
{
    int mod = a%b;
    return a + b * !!mod - mod;
}

