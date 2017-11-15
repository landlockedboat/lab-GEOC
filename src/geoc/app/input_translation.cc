#include <geoc/app/input_translation.h>
#include <QKeyEvent>


using namespace geoc;


Keyboard::key geoc::translate_key(int qt_key)
{
    switch (qt_key)
    {
    case Qt::Key_A: 		return Keyboard::Key_A;
    case Qt::Key_B: 		return Keyboard::Key_B;
    case Qt::Key_C: 		return Keyboard::Key_C;
    case Qt::Key_D: 		return Keyboard::Key_D;
    case Qt::Key_E: 		return Keyboard::Key_E;
    case Qt::Key_F: 		return Keyboard::Key_F;
    case Qt::Key_G: 		return Keyboard::Key_G;
    case Qt::Key_H: 		return Keyboard::Key_H;
    case Qt::Key_I: 		return Keyboard::Key_I;
    case Qt::Key_J: 		return Keyboard::Key_J;
    case Qt::Key_K: 		return Keyboard::Key_K;
    case Qt::Key_L: 		return Keyboard::Key_L;
    case Qt::Key_M: 		return Keyboard::Key_M;
    case Qt::Key_N: 		return Keyboard::Key_N;
    case Qt::Key_O: 		return Keyboard::Key_O;
    case Qt::Key_P: 		return Keyboard::Key_P;
    case Qt::Key_Q: 		return Keyboard::Key_Q;
    case Qt::Key_R: 		return Keyboard::Key_R;
    case Qt::Key_S: 		return Keyboard::Key_S;
    case Qt::Key_T: 		return Keyboard::Key_T;
    case Qt::Key_U: 		return Keyboard::Key_U;
    case Qt::Key_V: 		return Keyboard::Key_V;
    case Qt::Key_W:			return Keyboard::Key_W;
    case Qt::Key_X: 		return Keyboard::Key_X;
    case Qt::Key_Y: 		return Keyboard::Key_Y;
    case Qt::Key_Z: 		return Keyboard::Key_Z;
    case Qt::Key_0: 		return Keyboard::Key_0;
    case Qt::Key_1:			return Keyboard::Key_1;
    case Qt::Key_2:			return Keyboard::Key_2;
    case Qt::Key_3:			return Keyboard::Key_3;
    case Qt::Key_4:			return Keyboard::Key_4;
    case Qt::Key_5:			return Keyboard::Key_5;
    case Qt::Key_6:			return Keyboard::Key_6;
    case Qt::Key_7:			return Keyboard::Key_7;
    case Qt::Key_8:			return Keyboard::Key_8;
    case Qt::Key_9:			return Keyboard::Key_9;
    case Qt::Key_Space:		return Keyboard::Key_space;
    case Qt::Key_Return:	return Keyboard::Key_return;
    case Qt::Key_Shift:		return Keyboard::Key_shift;
    case Qt::Key_Escape:	return Keyboard::Key_escape; 
    case Qt::Key_Tab:		return Keyboard::Key_tab;
    case Qt::Key_Backspace:	return Keyboard::Key_backspace;
    case Qt::Key_Up:		return Keyboard::Key_up;
    case Qt::Key_Down:		return Keyboard::Key_down;
    case Qt::Key_Left:		return Keyboard::Key_left;
    case Qt::Key_Right:		return Keyboard::Key_right;
    case Qt::Key_Control:	return Keyboard::Key_ctrl;
    case Qt::Key_Alt:		return Keyboard::Key_alt;
    case Qt::Key_PageUp:	return Keyboard::Key_pgup;
    case Qt::Key_PageDown:	return Keyboard::Key_pgdown;
    default:				return Keyboard::Key_unknown;
    }
}


Mouse::button geoc::translate_mouse(Qt::MouseButton qt_bt)
{
    switch (qt_bt)
    {
    case Qt::LeftButton: return Mouse::LMB;
    case Qt::RightButton: return Mouse::RMB;
    default: return Mouse::unknown;
    }
}
