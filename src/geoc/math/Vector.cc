#ifndef _VECTOR_CC
#define _VECTOR_CC

#include <geoc/geoc.h>
#include <geoc/higher_order_cpp.h>
#include <geoc/math/Vector.h>
#include <cstdlib>
#include <algorithm>
#include <cmath>

namespace geoc {

template <class iter_t>
struct Iseq : public std::pair<iter_t,iter_t>
{
    Iseq(const iter_t& it1, const iter_t& it2) : std::pair<iter_t,iter_t>(it1, it2) {}
};


template <class C>
Iseq<typename C::iterator> iseq(C& c)
{
    return Iseq<typename C::iterator>(c.begin(), c.end());
}


template <class C>
Iseq<typename C::const_iterator> const_iseq(const C& c)
{
    return Iseq<typename C::const_iterator>(c.begin(), c.end());
}


template <class T, int N>
Vector<T,N>::Vector()
{
    for (int i = 0; i < N; ++i) data[i] = num();
}


template <class T, int N>
Vector<T,N>::Vector(T val)
{
    memset(data, val, N);
}


template <class T, int N>
Vector<T,N>::Vector(T x0, T x1)
{
    data[0] = x0;
    data[1] = x1;
}


template <class T, int N>
Vector<T,N>::Vector(T x0, T x1, T x2)
{
    data[0] = x0;
    data[1] = x1;
    data[2] = x2;
}


template <class T, int N>
Vector<T,N>::Vector(T x0, T x1, T x2, T x3)
{
    data[0] = x0;
    data[1] = x1;
    data[2] = x2;
    data[3] = x3;
}


template <class T, int N>
Vector<T,N>::Vector(T xs[N])
{
    for (int i = 0; i < N; ++i) data[i] = xs[i];
}


template <class T, int N> template <int d>
Vector<T,N>::Vector(const Vector<T,d>& v, const T& c)
{
    int m = std::min(d, N);
    for (int i = 0; i < m; ++i) data[i] = v[i];
    for (int i = m; i < N; ++i) data[i] = c;
}



template <class T, int N>
inline T& Vector<T,N>::operator[](int i)
{
    GEOC_DEBUG_ASSERT( (i >= 0) && (i < N) );
    return data[i];
}


template <class T, int N>
inline const T& Vector<T,N>::operator[](int i) const
{
    GEOC_DEBUG_ASSERT( (i >= 0) && (i < N) );
    return data[i];
}


template <class T, int N>
inline const T& Vector<T,N>::x() const
{
    GEOC_DEBUG_ASSERT(N >= 1);
    return data[X];
}


template <class T, int N>
inline const T& Vector<T,N>::y() const
{
    GEOC_DEBUG_ASSERT(N >= 2);
    return data[Y];
}


template <class T, int N>
inline const T& Vector<T,N>::z() const
{
    GEOC_DEBUG_ASSERT(N >= 3);
    return data[Z];
}


template <class T, int N>
inline T& Vector<T,N>::x()
{
    GEOC_DEBUG_ASSERT(N >= 1);
    return data[X];
}


template <class T, int N>
inline T& Vector<T,N>::y()
{
    GEOC_DEBUG_ASSERT(N >= 2);
    return data[Y];
}


template <class T, int N>
inline T& Vector<T,N>::z()
{
    GEOC_DEBUG_ASSERT(N >= 3);
    return data[Z];
}


template <class T, int N>
num Vector<T,N>::norm() const
{
    return std::sqrt(normSq());
}

template <class T, int N>
num Vector<T,N>::normSq() const
{
    num mag = 0.0;
    foreach (T val, data) mag += (val * val);
    return mag;
}


template <class T, int N>
Vector<T,N>& Vector<T,N>::normalise()
{
    num mag = norm();
    mag = (mag == 0.0) ? 1.0 : 1.0/mag;
    geoc::map(mag * boost::lambda::_1, iseq(data));
    return *this;
}



template <class T, int N>
inline Vector<T,N> Vector<T,N>::operator+(const Vector<T,N>& v) const
{
    T vals[N];
    //zipWith([](T x, T y) {return x+y;}, data.begin(), data.end(), v.data.begin(), v.data.end(), vals);
    zipWith(boost::lambda::_1 + boost::lambda::_2, const_iseq(data), const_iseq(v.data), vals);
    return Vector(vals);
}

template <class T, int N>
inline Vector<T,N> Vector<T,N>::operator-(const Vector<T,N>& v) const
{
    T vals[N];
    zipWith(boost::lambda::_1 - boost::lambda::_2, const_iseq(data), const_iseq(v.data), vals);
    return Vector(vals);
}

template <class T, int N>
inline Vector<T,N> Vector<T,N>::operator+(num d) const
{
    T vals[N];
    geoc::map(boost::lambda::_1 + d, const_iseq(data), vals);
    return Vector(vals);
}

template <class T, int N>
inline Vector<T,N> Vector<T,N>::operator-(num d) const
{
    T vals[N];
    geoc::map(boost::lambda::_1 - d, const_iseq(data), vals);
    return Vector(vals);
}

template <class T, int N>
inline Vector<T,N> Vector<T,N>::operator*(num d) const
{
    T vals[N];
    geoc::map(boost::lambda::_1 * d, const_iseq(data), vals);
    return Vector(vals);
}

template <class T, int N>
inline Vector<T,N> Vector<T,N>::operator/(num d) const
{
    T vals[N];
    geoc::map(boost::lambda::_1 / d, const_iseq(data), vals);
    return Vector(vals);
}

template <class T, int N>
inline Vector<T,N>& Vector<T,N>::operator+=(const Vector<T,N>& v)
{
    zipWith(boost::lambda::_1 + boost::lambda::_2, iseq(data), const_iseq(v.data), data.begin());
    return *this;
}

template <class T, int N>
inline Vector<T,N>& Vector<T,N>::operator-=(const Vector<T,N>& v)
{
    zipWith(boost::lambda::_1 - boost::lambda::_2, iseq(data), const_iseq(v.data, N), data.begin());
    return *this;
}

template <class T, int N>
inline Vector<T,N>& Vector<T,N>::operator+=(num d)
{
    geoc::map(boost::lambda::_1 + d, iseq(data));
    return *this;
}

template <class T, int N>
inline Vector<T,N>& Vector<T,N>::operator-=(num d)
{
    geoc::map(boost::lambda::_1 - d, iseq(data));
    return *this;
}

template <class T, int N>
inline Vector<T,N>& Vector<T,N>::operator*=(num d)
{
    geoc::map(boost::lambda::_1 * d, iseq(data));
    return *this;
}

template <class T, int N>
inline Vector<T,N>& Vector<T,N>::operator/=(num d)
{
    geoc::map(boost::lambda::_1 / d, iseq(data));
    return *this;
}

template <class T, int N>
inline Vector<T,N> Vector<T,N>::operator-() const
{
    T vals[N];
    geoc::map(-boost::lambda::_1, const_iseq(data), vals);
    return Vector(vals);
}

template <class T, int N>
inline bool Vector<T,N>::operator==(const Vector<T,N>& v) const
{
    return std::equal(data.begin(), data.end(), v.data.begin());
}

template <class T, int N>
inline bool Vector<T,N>::operator!=(const Vector<T,N>& v) const
{
    return !std::equal(data.begin(), data.end(), v.data.end());
}

template <class T, int N>
inline bool Vector<T,N>::operator<(const Vector<T,N>&v ) const
{
    bool all_eq = true;
    for (int i = 0; i < N; ++i)
    {
        if (data[i] > v[i]) return false;
        if (data[i] < v[i]) all_eq = false;
    }
    return !all_eq;
}

template <class T, int N>
inline bool Vector<T,N>::operator>(const Vector<T,N>&v ) const
{
    bool all_eq = true;
    for (int i = 0; i < N; ++i)
    {
        if (data[i] < v[i]) return false;
        if (data[i] > v[i]) all_eq = false;
    }
    return !all_eq;
}

template <class T, int N>
inline bool Vector<T,N>::operator>=(const Vector<T,N>&v ) const
{
    for (int i = 0; i < N; ++i)
    {
        if (data[i] < v[i]) return false;
    }
    return true;
}

template <class T, int N>
inline bool Vector<T,N>::operator<=(const Vector<T,N>&v ) const
{
    for (int i = 0; i < N; ++i)
    {
        if (data[i] > v[i]) return false;
    }
    return true;
}



template <class T, int N>
std::ostream& operator<<(std::ostream& os, const Vector<T,N>& v)
{
    os << "(";
    for (int i = 0; i < N-1; ++i)
    {
        os << v[i] << ", ";
    }
    os << v[N-1] << ")";
    
    return os;
}

template <class T, int N>
std::istream& operator>>(std::istream& is, Vector<T,N>& v)
{
    for (int i = 0; i < N; ++i)
    {
        is >> v[i];
    }
    
    return is;
}

template <class T, int N>
std::fstream& operator<<(std::fstream& fs, const Vector<T,N>& v)
{
    for (int i = 0; i < N-1; ++i)
    {
        fs << v[i] << " ";
    }
    fs << v[N-1];
    
    return fs;
}


template <class T, int N>
T dot(const Vector<T,N>& v1, const Vector<T,N>& v2)
{
    T d = 0;
    
    for (int i = 0; i != N; ++i)
    {
        d += (v1[i] * v2[i]);
    }
    
    return d;
}

} //namespace geoc

#endif //_VECTOR_CC
