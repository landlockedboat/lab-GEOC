#ifndef _GEOC_SCREEN_INPUT_H
#define _GEOC_SCREEN_INPUT_H

#include <geoc/geoc.h>
#include <geoc/io/input/Keyboard.h>
#include <geoc/math/Vector_fwd_decl.h>
#include <boost/function.hpp>
#include <boost/functional/factory.hpp>

namespace geoc {

class Camera;
class Graphics;
class Input;
class SceneManager;
class IScreenState;

struct ScreenInput_Impl;

/** \ingroup Screen */
//! The screen input subsystem.
/*!
 * The ScreenInput subsystem handles screen input.
 * Attach concrete ScreenState states to the ScreenInput class to add functionality to it.
 * \sa ScreenState
 */
class DECLDIR ScreenInput
{
    ScreenInput_Impl*	impl;
    
    void calculatePos(const ScreenPos& pos, Vector3& world_pos) const;
    
public:
    
    ScreenInput(const Camera& cam, const SceneManager& sceneMgr);
    ~ScreenInput();
    
    //! Notifies the screen input subsystem that the left mouse button has been pressed.
    char mouseClicked(const ScreenPos& pos);
    
    //! Notifies the screen input subsystem that the right mouse button has been pressed.
    char mouseRightClicked(const ScreenPos& pos);
    
    //! Notifies the screen input subsystem that the mouse has moved.
    char mouseMoved(const ScreenPos& pos);
    
    //! Notifies the screen input subsystem that a key has been pressed.
    char keyPressed(Keyboard::key key, const ScreenPos& pos);
    
    //! Draws the current state of the input subsystem.
    void draw(Graphics& gfx);
    
    //! Configures a state transition.
    void setTransition(Keyboard::key key, IScreenState* state);
    
    //! Sets the current state.
    void setState(IScreenState* state);
    
    //! Returns a description of the current state.
    const char* stateDescription() const;
};


} //namespace geoc

#endif //_GEOC_SCREEN_INPUT_H
