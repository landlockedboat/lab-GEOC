#include "Vector_iterators.h"
#include <geoc/math/Vector.h>


using namespace geoc;


const num* Construct_Vector2_iterator::operator()(const Vector2& v)
{
    return &v[X];
}


const num* Construct_Vector2_iterator::operator()(const Vector2& v, int)
{
    return &v[Y+1];
}


const num* Construct_Vector3_iterator::operator()(const Vector3& v)
{
    return &v[X];
}


const num* Construct_Vector3_iterator::operator()(const Vector3& v, int)
{
    return &v[Z+1];
}
