#include <geoc/geoc.h>
#include <geoc/io/input/Mouse.h>


using namespace geoc;


Mouse::Mouse() : x(0), y(0), dx(0), dy(0), buttons(NUM_MOUSE_BUTTONS, false) {}


void Mouse::setPosition(num x, num y)
{
    this->x = x;
    this->y = y;
}


void Mouse::setDelta(num dx, num dy)
{
    this->dx = dx;
    this->dy = dy;
}

void Mouse::getPos(num* x, num* y) const
{
    if (x) *x = this->x;
    if (y) *y = this->y;
}


void Mouse::getDelta(num* dx, num* dy) const
{
    if (dx) *dx = this->dx;
    if (dy) *dy = this->dy;
}
