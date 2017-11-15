#ifndef _GEOC_INPUT_H
#define _GEOC_INPUT_H


#include <geoc/geoc.h>
#include <geoc/math/Vector_fwd_decl.h>
#include "Keyboard.h"
#include "Mouse.h"


namespace geoc {


/** \ingroup Input */
//! The input subsystem.
/*!
 * The input class provides access to keyboard and mouse devices, although
 * it does not expose them.
 */
class Input
{
    const Keyboard& kbd;
    const Mouse& mouse;
    
public:
    
    Input(Keyboard& keyboard, Mouse& mouse);
    
    //! Returns true if the given key is down, false otherwise.
    bool keyDown(Keyboard::key key) const;
    
    //! Returns true if the given key is up, false otherwise.
    bool keyUp(Keyboard::key key) const;
    
    //! Returns true if the given button is down, false otherwise.
    bool buttonDown(Mouse::button bt) const;
    
    //! Returns true if the given button is up, false otherwise.
    bool buttonUp(Mouse::button bt) const;
    
    //! Gets the mouse position.
    void getMousePos(num* x, num* y) const;
    
    //! Gets the mouse position.
    void getMousePos(ScreenPos& pos) const;
    
    //! Gets the mouse position offset.
    void getMouseDelta(num* dx, num* dy) const;
    
    //! Gets the mouse position offset.
    void getMouseDelta(Vector2& delta) const;
};


} //namespace geoc


#endif //_GEOC_INPUT_H
