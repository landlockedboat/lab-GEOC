#ifndef _GEOC_ALGORITHMS_H
#define _GEOC_ALGORITHMS_H


namespace geoc {

template <class func, class iter_t1, class iter_t2, class iter_t3>
void zipWith(func f, iter_t1 it1, const iter_t1& end1, iter_t2 it2, const iter_t2& end2, iter_t3 it3)
{
    for(; it1 != end1 && it2 != end2; ++it1, ++it2, ++it3) *it3 = f(*it1, *it2);
}


template <class func, class In1, class In2, class iter_out>
void zipWith(func f, const In1& is1, const In2& is2, iter_out it)
{
    zipWith(f, is1.first, is1.second, is2.first, is2.second, it);
}


template <class func, class iter_t1, class iter_t2>
void map(func f, iter_t1 it1, const iter_t1& end, iter_t2 it2)
{
    for(; it1 != end; ++it1, ++it2) *it2 = f(*it1);
}


template <class func, class In, class iter_t>
void map(func f, const In& is, iter_t it)
{
    geoc::map(f, is.first, is.second, it);
}


template <class func, class iter_t>
void map(func f, iter_t it, const iter_t& end)
{
    for(; it != end; ++it) *it = f(*it);
}


template <class func, class In>
void map(func f, const In& is)
{
    geoc::map(f, is.first, is.second);
}


template <class func, class iter_t>
void mapM(func f, iter_t it, const iter_t& end)
{
    for(; it != end; ++it) f(*it);
}


template <class func, class In>
void mapM(func f, const In& is)
{
    mapM(f, is.first, is.second);
}


template <class Acc, class func, class iter_t1, class iter_t2>
Acc foldl(func f, Acc acc, iter_t1 it, const iter_t2& end)
{
    Acc tmp = acc;
    for(; it != end; ++it) tmp = f(tmp, *it);
    return tmp;
}


template <class Acc, class func, class In>
Acc foldl(func f, Acc acc, const In& is)
{
    return foldl(f, acc, is.first, is.second);
}


template <class Acc, class func, class iter_t1, class iter_t2>
Acc foldr(func f, Acc acc, iter_t1 it, const iter_t2& begin)
{
    Acc tmp = acc;
    for(; it != begin; --it) tmp = f(*it, tmp);
    return tmp;
}


template <class Acc, class func, class In>
Acc foldr(func f, Acc acc, const In& is)
{
    return foldr(f, acc, is.second, is.first);
}


} // namespace geoc


#endif //_GEOC_ALGORITHMS_H
