#ifndef _GEOC_MOUSE_H
#define _GEOC_MOUSE_H

#include <geoc/geoc.h>
#include <vector>


namespace geoc {


/** \ingroup Input */
//! Represents the mouse.
class Mouse
{	
public:
    
    /** \ingroup Input */
    //! Mouse buttons.
    enum button
    {
        Mouse_MIN,
        LMB, RMB, unknown,
        Mouse_MAX
    };
    
    
public:
    
    Mouse();
    
    //! Updates the given mouse button.
    /*!
     * \param bt The button to be updated.
     * \param pressed The state of the given buttom.
     * \sa Mouse::button
     */
    void setState(Mouse::button bt, bool pressed) { buttons[bt] = pressed; }
    
    //! Updates the mouse position.
    void setPosition(num x, num y);
    
    //! Updates the mouse displacement.
    void setDelta(num dx, num dy);
    
    //! Returns true if the given button is down, false otherwise.
    /*!
     * \sa Mouse::button
     */
    bool down(Mouse::button bt) const { return buttons[bt]; }
    
    //! Returns true if the given button is up, false otherwise.
    /*!
     * \sa Mouse::button
     */
    bool up(Mouse::button bt) const { return !buttons[bt]; }
    
    //! Returns the mouse position.
    void getPos(num* x, num* y) const;
    
    //! Returns the mouse offset since the last frame.
    void getDelta(num* dx, num* dy) const;
    
private:
    
    static const int NUM_MOUSE_BUTTONS = Mouse_MAX - Mouse_MIN - 1;
    num x;
    num y;
    num dx;
    num dy;
    std::vector<bool> buttons;
};


} //namespace geoc


#endif //_GEOC_MOUSE_H
