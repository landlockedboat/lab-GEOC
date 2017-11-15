#ifndef _GEOC_IDLE_STATE_H
#define _GEOC_IDLE_STATE_H

#include <geoc/geoc.h>
#include "ScreenState.h"

namespace geoc {

/** \ingroup Screen */
//! A screen state which basically does nothing.
class IdleState : public IScreenState
{
public:
    
    const char* description() const { return "Idle"; }
};

} //namespace geoc

#endif //_GEOC_IDLE_STATE
