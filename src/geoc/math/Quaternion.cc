#include "Quaternion.h"
#include <cmath>

static const num TO_RAD = M_PI / 180.0;

using namespace geoc;


Quaternion geoc::operator* (Quaternion q1, Quaternion q2)
{
    num w, x, y, z;
    w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
    x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
    y = q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x;
    z = q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w;
    return Quaternion (w, x, y, z);
}


Quaternion geoc::qAxisAngle (num angle, num x, num y, num z)
{
    num _w, _y, _x, _z;
    num s = sqrt(x*x + y*y + z*z);
    s = s == 0.0 ? 1.0 : s;
    num a = angle * TO_RAD * 0.5;
    num sa = sin (a);
    _w = cos (a);
    _x = x * sa * s;
    _y = y * sa * s;
    _z = z * sa * s;
    return Quaternion (_w, _x, _y, _z);
}


Quaternion geoc::inverse (Quaternion q)
{
    num magsq = q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z;
    magsq = magsq == 0.0 ? 1.0 : magsq;
    return Quaternion (q.w / magsq, -q.x / magsq, -q.y / magsq, -q.z / magsq);
}


Quaternion geoc::conjugate (Quaternion q)
{
    return Quaternion (q.w, -q.x, -q.y, -q.z);
}


Vector3 geoc::rotate (Quaternion q, Vector3 v)
{
    Quaternion p = conjugate (q);
    Quaternion qv (0, v[X], v[Y], v[Z]);
    qv = q * qv * p;
    return Vector3 (qv.x, qv.y, qv.z);
}
