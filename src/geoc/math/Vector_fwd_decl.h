#ifndef _GEOC_VECTOR_FWD_DECL_H
#define _GEOC_VECTOR_FWD_DECL_H

//Include this header file when only the declaration of class Vector is
//needed and not its definition to speed up compilation.

namespace geoc {
template <class T, int N>
class Vector;

typedef Vector<num,2> Vector2;
typedef Vector<num,3> Vector3;
typedef Vector<num,4> Vector4;

typedef Vector3 Colour3;
typedef Vector4 Colour4;
typedef Vector2 ScreenPos;
} // geoc namespace


#endif //_GEOC_VECTOR_FWD_DECL_H
