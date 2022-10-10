/****************************************************************************
** Meta object code from reading C++ file 'readRawDataPipe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/readRawDataPipe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'readRawDataPipe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_readRawDataPipe_t {
    QByteArrayData data[5];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_readRawDataPipe_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_readRawDataPipe_t qt_meta_stringdata_readRawDataPipe = {
    {
QT_MOC_LITERAL(0, 0, 15), // "readRawDataPipe"
QT_MOC_LITERAL(1, 16, 9), // "sendEvent"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "post_finished"
QT_MOC_LITERAL(4, 41, 8) // "postProc"

    },
    "readRawDataPipe\0sendEvent\0\0post_finished\0"
    "postProc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_readRawDataPipe[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void readRawDataPipe::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        readRawDataPipe *_t = static_cast<readRawDataPipe *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendEvent(); break;
        case 1: _t->post_finished(); break;
        case 2: _t->postProc(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (readRawDataPipe::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&readRawDataPipe::sendEvent)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (readRawDataPipe::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&readRawDataPipe::post_finished)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject readRawDataPipe::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_readRawDataPipe.data,
      qt_meta_data_readRawDataPipe,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *readRawDataPipe::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *readRawDataPipe::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_readRawDataPipe.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int readRawDataPipe::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void readRawDataPipe::sendEvent()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void readRawDataPipe::post_finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
