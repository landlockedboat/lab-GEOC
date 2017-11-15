#ifndef _GEOC_SCREEN_STATE_INTERFACE_H
#define _GEOC_SCREEN_STATE_INTERFACE_H

#include <geoc/geoc.h>
#include <geoc/io/input/Keyboard.h>
#include <geoc/app/update_requests.h>
#include <geoc/math/Vector_fwd_decl.h>

namespace geoc {

class Graphics;

/** \ingroup Screen */
//! An interface for all screen input states.
/*!
 * Do not derive concrete screen states from this class; derive from ScreenState instead.
 * \sa ScreenState
 */
class DECLDIR IScreenState
{
    
public:
    
    virtual ~IScreenState() {}
    
    //! Notifies the screen state that the left mouse button has been clicked.
    virtual GEOC_APP_REQUEST_CODE mouseClick(const Vector3&) { return GEOC_APP_NO_REQUEST; }
    
    //! Notifies the screen state that the right mouse button has been clicked.
    virtual GEOC_APP_REQUEST_CODE mouseRightClick(const Vector3&) { return GEOC_APP_NO_REQUEST; }
    
    //! Notifies the screen state that the mouse has moved.
    virtual GEOC_APP_REQUEST_CODE mouseMove(const Vector3&) { return GEOC_APP_NO_REQUEST; }
    
    //! Notifies the screen state that the given key has been pressed.
    virtual GEOC_APP_REQUEST_CODE keyPressed(Keyboard::key){ return GEOC_APP_NO_REQUEST; }
    
    //! Cancels any progress.
    virtual void cancel() {}
    
    //! Draws the ScreenState's current state.
    virtual void draw(Graphics&) {}
    
    //! Gets a description for the ScreenState.
    virtual const char* description() const = 0;
};

} //namespace geoc

#endif //_GEOC_SCREEN_STATE_INTERFACE_H
