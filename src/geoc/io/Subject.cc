#ifndef _GEOC_SUBJECT_CC
#define _GEOC_SUBJECT_CC


#include <geoc/geoc.h>
#include <geoc/higher_order_cpp.h>
#include "Subject.h"


namespace geoc {

template <class T>
void Subject<T>::attach(Observer<T>* observer)
{
    observers.push_front(observer);
}


template <class T>
void Subject<T>::detach(Observer<T>* observer)
{
    observers.remove(observer);
}


template <class T>
void Subject<T>::enters(T* elem)
{
    mapM(boost::bind(&Observer<T>::enters, _1, elem), observers.begin(), observers.end());
}


template <class T>
void Subject<T>::leaves(T* elem)
{
    mapM(boost::bind(&Observer<T>::leaves, _1, elem), observers.begin(), observers.end());
}


template <class T>
void Subject<T>::sceneCleared()
{
    mapM(boost::bind(&Observer<T>::sceneCleared, _1), observers.begin(), observers.end());
}


} //namespace geoc

#endif //_GEOC_SUBJECT_CC
