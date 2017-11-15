/****************************************************************************
** Meta object code from reading C++ file 'GeocWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/geoc/app/GeocWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeocWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_geoc__GeocWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      68,   27,   17,   17, 0x05,
     129,  118,   17,   17, 0x05,
     161,  118,   17,   17, 0x05,
     217,  199,   17,   17, 0x05,
     286,  267,   17,   17, 0x05,
     330,   17,   17,   17, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_geoc__GeocWidget[] = {
    "geoc::GeocWidget\0\0render()\0"
    "camera_mode,camera_projection,input_desc\0"
    "updateStatus(std::string,std::string,std::string)\0"
    "widget,key\0labelsToggled(GeocWidget&,bool)\0"
    "keyPressed(GeocWidget&,Keyboard::key)\0"
    "widget,pos,button\0"
    "mouseClicked(GeocWidget&,ScreenPos,Mouse::button)\0"
    "widget,old_pos,pos\0"
    "mouseMoved(GeocWidget&,ScreenPos,ScreenPos)\0"
    "requestExit()\0"
};

void geoc::GeocWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GeocWidget *_t = static_cast<GeocWidget *>(_o);
        switch (_id) {
        case 0: _t->render(); break;
        case 1: _t->updateStatus((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3]))); break;
        case 2: _t->labelsToggled((*reinterpret_cast< GeocWidget(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->keyPressed((*reinterpret_cast< GeocWidget(*)>(_a[1])),(*reinterpret_cast< Keyboard::key(*)>(_a[2]))); break;
        case 4: _t->mouseClicked((*reinterpret_cast< GeocWidget(*)>(_a[1])),(*reinterpret_cast< const ScreenPos(*)>(_a[2])),(*reinterpret_cast< Mouse::button(*)>(_a[3]))); break;
        case 5: _t->mouseMoved((*reinterpret_cast< GeocWidget(*)>(_a[1])),(*reinterpret_cast< const ScreenPos(*)>(_a[2])),(*reinterpret_cast< const ScreenPos(*)>(_a[3]))); break;
        case 6: _t->requestExit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData geoc::GeocWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject geoc::GeocWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_geoc__GeocWidget,
      qt_meta_data_geoc__GeocWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &geoc::GeocWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *geoc::GeocWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *geoc::GeocWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_geoc__GeocWidget))
        return static_cast<void*>(const_cast< GeocWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int geoc::GeocWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void geoc::GeocWidget::render()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void geoc::GeocWidget::updateStatus(const std::string & _t1, const std::string & _t2, const std::string & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void geoc::GeocWidget::labelsToggled(GeocWidget & _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void geoc::GeocWidget::keyPressed(GeocWidget & _t1, Keyboard::key _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void geoc::GeocWidget::mouseClicked(GeocWidget & _t1, const ScreenPos & _t2, Mouse::button _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void geoc::GeocWidget::mouseMoved(GeocWidget & _t1, const ScreenPos & _t2, const ScreenPos & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void geoc::GeocWidget::requestExit()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
