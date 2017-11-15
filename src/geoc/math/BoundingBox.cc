#ifndef _GEOC_BOUNDING_BOX_CC
#define _GEOC_BOUNDING_BOX_CC

#include <geoc/geoc.h>
#include <geoc/higher_order_cpp.h>
#include "BoundingBox.h"
#include <cmath>

namespace geoc {


template <int N> template <class iter_t>
BoundingBox<N>::BoundingBox(iter_t begin, const iter_t& end) : first_point(true)
{
    mapM(boost::bind(&BoundingBox<N>::add, this, _1), begin, end);
}


template <int N>
void BoundingBox<N>::add(const Vector<num,N>& v)
{
    if (first_point)
    {
        _min = v;
        _max = v;
        first_point = false;
    }
    else
    {
        for (int i = 0; i < N; ++i)
        {
            _min[i] = std::min(_min[i], v[i]);
            _max[i] = std::max(_max[i], v[i]);
        }
    }
}


template <int N>
const Vector<num,N> BoundingBox<N>::center() const
{
    return (_max + _min) / 2.0;
}

} //namespace geoc


#endif //_GEOC_BOUNDING_BOX_CC
