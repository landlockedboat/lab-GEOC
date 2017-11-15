/****************************************************************************
** Meta object code from reading C++ file 'GeocApplication.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/geoc/app/GeocApplication.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeocApplication.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_geoc__GeocApplication[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x09,
      73,   32,   22,   22, 0x09,
     131,  126,   22,   22, 0x09,
     165,  163,   22,   22, 0x09,
     206,  203,   22,   22, 0x09,
     256,  203,   22,   22, 0x09,
     300,   22,   22,   22, 0x09,
     307,   22,   22,   22, 0x09,
     319,   22,   22,   22, 0x09,
     333,   22,   22,   22, 0x09,
     345,   22,   22,   22, 0x09,
     359,   22,   22,   22, 0x09,
     371,   22,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_geoc__GeocApplication[] = {
    "geoc::GeocApplication\0\0render()\0"
    "camera_mode,camera_projection,input_desc\0"
    "updateStatusBar(std::string,std::string,std::string)\0"
    ",key\0labelsToggled(GeocWidget&,bool)\0"
    ",\0keyPressed(GeocWidget&,Keyboard::key)\0"
    ",,\0mouseClicked(GeocWidget&,ScreenPos,Mouse::button)\0"
    "mouseMoved(GeocWidget&,ScreenPos,ScreenPos)\0"
    "quit()\0loadScene()\0reloadScene()\0"
    "saveScene()\0saveSceneAs()\0showAbout()\0"
    "toggleLabels()\0"
};

void geoc::GeocApplication::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GeocApplication *_t = static_cast<GeocApplication *>(_o);
        switch (_id) {
        case 0: _t->render(); break;
        case 1: _t->updateStatusBar((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3]))); break;
        case 2: _t->labelsToggled((*reinterpret_cast< GeocWidget(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->keyPressed((*reinterpret_cast< GeocWidget(*)>(_a[1])),(*reinterpret_cast< Keyboard::key(*)>(_a[2]))); break;
        case 4: _t->mouseClicked((*reinterpret_cast< GeocWidget(*)>(_a[1])),(*reinterpret_cast< const ScreenPos(*)>(_a[2])),(*reinterpret_cast< Mouse::button(*)>(_a[3]))); break;
        case 5: _t->mouseMoved((*reinterpret_cast< GeocWidget(*)>(_a[1])),(*reinterpret_cast< const ScreenPos(*)>(_a[2])),(*reinterpret_cast< const ScreenPos(*)>(_a[3]))); break;
        case 6: _t->quit(); break;
        case 7: _t->loadScene(); break;
        case 8: _t->reloadScene(); break;
        case 9: _t->saveScene(); break;
        case 10: _t->saveSceneAs(); break;
        case 11: _t->showAbout(); break;
        case 12: _t->toggleLabels(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData geoc::GeocApplication::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject geoc::GeocApplication::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_geoc__GeocApplication,
      qt_meta_data_geoc__GeocApplication, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &geoc::GeocApplication::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *geoc::GeocApplication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *geoc::GeocApplication::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_geoc__GeocApplication))
        return static_cast<void*>(const_cast< GeocApplication*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int geoc::GeocApplication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
