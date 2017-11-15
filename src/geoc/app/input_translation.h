#ifndef _GEOC_INPUT_TRANSLATION_H
#define _GEOC_INPUT_TRANSLATION_H


#include <geoc/io/input/Keyboard.h>
#include <geoc/io/input/Mouse.h>
#include <QMouseEvent>


namespace geoc {

Keyboard::key translate_key(int qt_key);
Mouse::button translate_mouse(Qt::MouseButton qt_bt);

}


#endif //_GEOC_INPUT_TRANSLATION_H
