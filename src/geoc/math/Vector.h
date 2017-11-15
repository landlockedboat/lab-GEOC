#ifndef _VECTOR_H
#define _VECTOR_H

#include <geoc/geoc.h>
#include <geoc/math/Vector_fwd_decl.h> //Ensure type consistency.
#include <boost/array.hpp>
#include <iostream>
#include <fstream>
#include <utility>

namespace geoc {

/** \ingroup Math */
//! An N-dimensional vector.
template <class T, int N>
class Vector
{
    boost::array<T,N> data;
    
public:
    
    Vector();
    Vector(T val);
    Vector(T x0, T x1);
    Vector(T x0, T x1, T x2);
    Vector(T x0, T x1, T x2, T x3);
    Vector(T xs[N]);
    
    //! Projects a vector from d-dimensional space to N-dimensional space.
    template <int d>
    Vector(const Vector<T,d>& v, const T& c = T());
    
    //! Returns a reference to one of the vector's components.
    inline const T& operator[](int i) const;
    
    //! Returns a reference to one of the vector's components.
    inline T& operator[](int i);
    
    inline const T& x() const;
    inline const T& y() const;
    inline const T& z() const;
    inline T& x();
    inline T& y();
    inline T& z();
    
    //! Normalises the vector.
    Vector<T,N>& normalise();
    
    //! Returns the vector's magnitude.
    num norm() const;
    
    //! Returns the vector's squared magnitude.
    num normSq() const;
    
    inline Vector<T,N> operator+(const Vector<T,N>& v) const;
    inline Vector<T,N> operator-(const Vector<T,N>& v) const;
    
    inline Vector<T,N> operator+(num d) const;
    inline Vector<T,N> operator-(num d) const;
    inline Vector<T,N> operator*(num d) const;
    inline Vector<T,N> operator/(num d) const;
    
    inline Vector<T,N>& operator+=(const Vector<T,N>& v);
    inline Vector<T,N>& operator-=(const Vector<T,N>& v);
    
    inline Vector<T,N>& operator+=(num d);
    inline Vector<T,N>& operator-=(num d);
    inline Vector<T,N>& operator*=(num d);
    inline Vector<T,N>& operator/=(num d);
    
    inline Vector<T,N> operator-() const;
    
    inline bool operator==(const Vector<T,N>& v) const;
    inline bool operator!=(const Vector<T,N>& v) const;
    inline bool operator<(const Vector<T,N>& v) const;
    inline bool operator>(const Vector<T,N>& v) const;
    inline bool operator>=(const Vector<T,N>& v) const;
    inline bool operator<=(const Vector<T,N>& v) const;
    
    typename boost::array<T,N>::iterator begin() { return data.begin(); }
    typename boost::array<T,N>::const_iterator begin() const { return data.begin(); }
    
    typename boost::array<T,N>::iterator end() { return data.end(); }
    typename boost::array<T,N>::const_iterator end() const { return data.end(); }
};


template <class T, int N>
std::ostream& operator<<(std::ostream& os, const Vector<T,N>& v);

template <class T, int N>
std::istream& operator>>(std::istream& is, Vector<T,N>& v);

template <class T, int N>
std::fstream& operator<<(std::fstream& fs, const Vector<T,N>& v);


const Vector3 zero3 = Vector3(0.0, 0.0, 0.0);
const Vector3 forward3 = Vector3(0.0, 0.0, -1.0);
const Vector3 right3 = Vector3(1.0, 0.0, 0.0);
const Vector3 up3 = Vector3(0.0, 1.0, 0.0);

enum COORD { X, Y, Z, W };
enum COLOUR {R, G, B, A};



//! Returns the dot product between the given vectors.
template <class T, int N>
T dot(const Vector<T,N>& v1, const Vector<T,N>& v2);


//! Returns the cross product between the given vectors.
Vector3 cross(const Vector3& v1, const Vector3& v2);


} //namespace geoc

#include "Vector.cc"

#endif //_VECTOR_H
