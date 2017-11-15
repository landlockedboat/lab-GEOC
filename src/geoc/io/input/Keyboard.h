#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include <geoc/geoc.h>
#include <vector>

namespace geoc {

struct Keyboard_Impl;

/** \ingroup Input */
//! Represents the keyboard.
class Keyboard
{
public:
    
    /** \ingroup Input */
    //! Keyboard keys.
    enum key {	Key_MIN,
                Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H, Key_I, Key_J,
                Key_K, Key_L, Key_M, Key_N, Key_O, Key_P, Key_Q, Key_R, Key_S, Key_T,
                Key_U, Key_V, Key_W, Key_X, Key_Y, Key_Z,
                Key_0, Key_1, Key_2, Key_3, Key_4, Key_5, Key_6, Key_7, Key_8, Key_9,
                Key_space, Key_return, Key_shift, Key_escape, Key_tab, Key_backspace,
                Key_up, Key_down, Key_left, Key_right, Key_ctrl, Key_alt, Key_pgup, Key_pgdown,
                Key_unknown,
                Key_MAX};
    
private:
    static const int NUM_KEYS = Key_MAX - Key_MIN - 1;
    std::vector<bool> keys;
    
public:
    
    Keyboard() : keys(std::vector<bool>(NUM_KEYS, false)) {}
    
    //! Updates the state of the given key.
    /*!
     * \param key The key to be updated.
     * \param pressed The state of the given key.
     * \sa Keyboard::key
     */
    void setState(Keyboard::key key, bool pressed) { keys[key] = pressed; }
    
    //! Returns true if the key is down, false otherwise.
    /*!
     * \sa Keyboard::key
     */
    bool down(Keyboard::key key) const { return keys[key]; }
    
    //! Returns true if the key is up, false otherwise.
    /*!
     * \sa Keyboard::key
     */
    bool up(Keyboard::key key) const { return !keys[key]; }
};


} //namespace geoc


#endif // KEYBOARD_H_INCLUDED
