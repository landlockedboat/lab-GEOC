#ifndef _GEOC_OBSERVER_H
#define _GEOC_OBSERVER_H

#include <geoc/geoc.h>

namespace geoc {

/** \ingroup IO */
//! An entity that observes elements as they move into and out of the scene.
template <class T>
class Observer
{
public:
    
    virtual ~Observer() {}
    
    //! Notifies the observer that the given element wishes to enter the scene.
    virtual void enters(T*) {}
    
    //! Notifies the observer that the given element is leaving the scene.
    virtual void leaves(T*) {}
    
    //! Notifies the observer that the scene has been cleared.
    virtual void sceneCleared() {}
};

} //namespace geoc

#endif //_GEOC_OBSERVER_H
