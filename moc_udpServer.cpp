/****************************************************************************
** Meta object code from reading C++ file 'udpServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/udpServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_udpServer_t {
    QByteArrayData data[9];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_udpServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_udpServer_t qt_meta_stringdata_udpServer = {
    {
QT_MOC_LITERAL(0, 0, 9), // "udpServer"
QT_MOC_LITERAL(1, 10, 8), // "finished"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "bataclan"
QT_MOC_LITERAL(4, 29, 7), // "started"
QT_MOC_LITERAL(5, 37, 10), // "readyStart"
QT_MOC_LITERAL(6, 48, 11), // "setupSocket"
QT_MOC_LITERAL(7, 60, 4), // "stop"
QT_MOC_LITERAL(8, 65, 15) // "ProcessDatagram"

    },
    "udpServer\0finished\0\0bataclan\0started\0"
    "readyStart\0setupSocket\0stop\0ProcessDatagram"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_udpServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,
       5,    0,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void udpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        udpServer *_t = static_cast<udpServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->bataclan(); break;
        case 2: _t->started(); break;
        case 3: _t->readyStart(); break;
        case 4: _t->setupSocket(); break;
        case 5: _t->stop(); break;
        case 6: _t->ProcessDatagram(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (udpServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&udpServer::finished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (udpServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&udpServer::bataclan)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (udpServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&udpServer::started)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (udpServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&udpServer::readyStart)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject udpServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_udpServer.data,
      qt_meta_data_udpServer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *udpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *udpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_udpServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int udpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void udpServer::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void udpServer::bataclan()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void udpServer::started()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void udpServer::readyStart()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
