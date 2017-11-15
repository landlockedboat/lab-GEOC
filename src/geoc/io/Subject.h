#ifndef _GEOC_SUBJECT_H
#define _GEOC_SUBJECT_H

#include <geoc/geoc.h>
#include "Observer.h"
#include <list>

namespace geoc {

/** \ingroup IO */
//! An entity that can notify observers about elements moving into and out of the scene.
template <class T>
class Subject
{
    std::list< Observer<T>* >	observers;
    
protected:
    
    //! Notifies observers that the given element wishes to enter the scene.
    void enters(T* elem);
    
    //! Notifies observers that the given element is leaving the scene.
    void leaves(T* elem);
    
    //! Notifies observers that the scene has been cleared.
    void sceneCleared();
    
public:
    
    virtual ~Subject() {}
    
    //! Attaches an observer.
    void attach(Observer<T>* observer);
    
    //! Detaches an observer.
    void detach(Observer<T>* observer);
};

} //namespace geoc

#include "Subject.cc"

#endif //_GEOC_SUBJECT_H
