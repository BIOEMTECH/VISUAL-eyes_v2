/****************************************************************************
** Meta object code from reading C++ file 'appWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/appWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_appWindow_t {
    QByteArrayData data[18];
    char stringdata0[277];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_appWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_appWindow_t qt_meta_stringdata_appWindow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "appWindow"
QT_MOC_LITERAL(1, 10, 13), // "exitAndDelete"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 4), // "Init"
QT_MOC_LITERAL(4, 30, 9), // "printHelp"
QT_MOC_LITERAL(5, 40, 14), // "imagingClicked"
QT_MOC_LITERAL(6, 55, 18), // "calibrationClicked"
QT_MOC_LITERAL(7, 74, 21), // "postProcessingClicked"
QT_MOC_LITERAL(8, 96, 11), // "startWindow"
QT_MOC_LITERAL(9, 108, 19), // "gammaWindowControls"
QT_MOC_LITERAL(10, 128, 10), // "gamma_eye*"
QT_MOC_LITERAL(11, 139, 16), // "FramelessWindow*"
QT_MOC_LITERAL(12, 156, 18), // "betaWindowControls"
QT_MOC_LITERAL(13, 175, 8), // "betaEye*"
QT_MOC_LITERAL(14, 184, 11), // "beyeRestart"
QT_MOC_LITERAL(15, 196, 13), // "returnAndshow"
QT_MOC_LITERAL(16, 210, 31), // "on_actionExit_Program_triggered"
QT_MOC_LITERAL(17, 242, 34) // "on_actionSearch_Database_trig..."

    },
    "appWindow\0exitAndDelete\0\0Init\0printHelp\0"
    "imagingClicked\0calibrationClicked\0"
    "postProcessingClicked\0startWindow\0"
    "gammaWindowControls\0gamma_eye*\0"
    "FramelessWindow*\0betaWindowControls\0"
    "betaEye*\0beyeRestart\0returnAndshow\0"
    "on_actionExit_Program_triggered\0"
    "on_actionSearch_Database_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_appWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    1,   85,    2, 0x08 /* Private */,
       9,    2,   88,    2, 0x08 /* Private */,
      12,    2,   93,    2, 0x08 /* Private */,
      14,    0,   98,    2, 0x08 /* Private */,
      15,    0,   99,    2, 0x08 /* Private */,
      16,    0,  100,    2, 0x08 /* Private */,
      17,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 11,    2,    2,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 11,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void appWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        appWindow *_t = static_cast<appWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->exitAndDelete(); break;
        case 1: _t->Init(); break;
        case 2: _t->printHelp(); break;
        case 3: _t->imagingClicked(); break;
        case 4: _t->calibrationClicked(); break;
        case 5: _t->postProcessingClicked(); break;
        case 6: _t->startWindow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->gammaWindowControls((*reinterpret_cast< gamma_eye*(*)>(_a[1])),(*reinterpret_cast< FramelessWindow*(*)>(_a[2]))); break;
        case 8: _t->betaWindowControls((*reinterpret_cast< betaEye*(*)>(_a[1])),(*reinterpret_cast< FramelessWindow*(*)>(_a[2]))); break;
        case 9: _t->beyeRestart(); break;
        case 10: _t->returnAndshow(); break;
        case 11: _t->on_actionExit_Program_triggered(); break;
        case 12: _t->on_actionSearch_Database_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FramelessWindow* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< gamma_eye* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< FramelessWindow* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< betaEye* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (appWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&appWindow::exitAndDelete)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject appWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_appWindow.data,
      qt_meta_data_appWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *appWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *appWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_appWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int appWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void appWindow::exitAndDelete()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
