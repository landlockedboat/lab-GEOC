#ifndef _GEOC_SCREEN_STATE_H
#define _GEOC_SCREEN_STATE_H

#include <geoc/geoc.h>
#include "IScreenState.h"
#include <geoc/io/input/Keyboard.h>
#include <geoc/io/Subject.h>
#include <list>

namespace geoc {

/** \ingroup Screen */
//! Base class for all screen input states.
template <class T>
class ScreenState :	public IScreenState, public Subject<T>
{	
public:
    
    virtual ~ScreenState() {}
};

} //namespace geoc

#endif //_GEOC_SCREEN_STATE_H
