/****************************************************************************
** Meta object code from reading C++ file 'DAQcounter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/DAQcounter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DAQcounter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DAQcounter_t {
    QByteArrayData data[15];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DAQcounter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DAQcounter_t qt_meta_stringdata_DAQcounter = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DAQcounter"
QT_MOC_LITERAL(1, 11, 26), // "DAQprogressBarValueChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 28), // "frameProgressBarValueChanged"
QT_MOC_LITERAL(4, 68, 13), // "stopEverthing"
QT_MOC_LITERAL(5, 82, 13), // "sendFrameStop"
QT_MOC_LITERAL(6, 96, 16), // "sendNewFrameTime"
QT_MOC_LITERAL(7, 113, 11), // "replotFrame"
QT_MOC_LITERAL(8, 125, 15), // "displayProgress"
QT_MOC_LITERAL(9, 141, 8), // "finished"
QT_MOC_LITERAL(10, 150, 3), // "DAQ"
QT_MOC_LITERAL(11, 154, 17), // "DynamicAquisition"
QT_MOC_LITERAL(12, 172, 11), // "frameReplot"
QT_MOC_LITERAL(13, 184, 8), // "Initiate"
QT_MOC_LITERAL(14, 193, 9) // "stopTimer"

    },
    "DAQcounter\0DAQprogressBarValueChanged\0"
    "\0frameProgressBarValueChanged\0"
    "stopEverthing\0sendFrameStop\0"
    "sendNewFrameTime\0replotFrame\0"
    "displayProgress\0finished\0DAQ\0"
    "DynamicAquisition\0frameReplot\0Initiate\0"
    "stopTimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DAQcounter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       3,    1,   82,    2, 0x06 /* Public */,
       4,    0,   85,    2, 0x06 /* Public */,
       5,    0,   86,    2, 0x06 /* Public */,
       6,    1,   87,    2, 0x06 /* Public */,
       7,    0,   90,    2, 0x06 /* Public */,
       8,    0,   91,    2, 0x06 /* Public */,
       9,    0,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   93,    2, 0x0a /* Public */,
      11,    0,   94,    2, 0x0a /* Public */,
      12,    0,   95,    2, 0x0a /* Public */,
      13,    0,   96,    2, 0x0a /* Public */,
      14,    0,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DAQcounter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DAQcounter *_t = static_cast<DAQcounter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DAQprogressBarValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->frameProgressBarValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->stopEverthing(); break;
        case 3: _t->sendFrameStop(); break;
        case 4: _t->sendNewFrameTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->replotFrame(); break;
        case 6: _t->displayProgress(); break;
        case 7: _t->finished(); break;
        case 8: _t->DAQ(); break;
        case 9: _t->DynamicAquisition(); break;
        case 10: _t->frameReplot(); break;
        case 11: _t->Initiate(); break;
        case 12: _t->stopTimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DAQcounter::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DAQcounter::DAQprogressBarValueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DAQcounter::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DAQcounter::frameProgressBarValueChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DAQcounter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DAQcounter::stopEverthing)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DAQcounter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DAQcounter::sendFrameStop)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DAQcounter::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DAQcounter::sendNewFrameTime)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DAQcounter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DAQcounter::replotFrame)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (DAQcounter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DAQcounter::displayProgress)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (DAQcounter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DAQcounter::finished)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DAQcounter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DAQcounter.data,
      qt_meta_data_DAQcounter,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DAQcounter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DAQcounter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DAQcounter.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DAQcounter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void DAQcounter::DAQprogressBarValueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DAQcounter::frameProgressBarValueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DAQcounter::stopEverthing()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DAQcounter::sendFrameStop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void DAQcounter::sendNewFrameTime(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DAQcounter::replotFrame()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void DAQcounter::displayProgress()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void DAQcounter::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
