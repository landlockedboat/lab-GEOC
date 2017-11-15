#include "Input.h"
#include <geoc/math/Vector.h>

using namespace geoc;
using namespace std;


Input::Input(Keyboard& keyboard, Mouse& mouse_) : kbd(keyboard), mouse(mouse_) {}


bool Input::keyDown(Keyboard::key key) const
{
    return kbd.down(key);
}


bool Input::keyUp(Keyboard::key key) const
{
    return !keyDown(key);
}


bool Input::buttonDown(Mouse::button bt) const
{
    return mouse.down(bt);
}


bool Input::buttonUp(Mouse::button bt) const
{
    return !buttonDown(bt);
}


void Input::getMousePos(num* x, num* y) const
{
    mouse.getPos(x, y);
}


void Input::getMousePos(ScreenPos& pos) const
{
    mouse.getPos(&pos[X], &pos[Y]);
}


void Input::getMouseDelta(num* dx, num* dy) const
{
    mouse.getDelta(dx, dy);
}


void Input::getMouseDelta(Vector2& delta) const
{
    mouse.getDelta(&delta[X], &delta[Y]);
}

