/****************************************************************************
** Meta object code from reading C++ file 'CameraWorker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/CameraWorker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CameraWorker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CameraWorker_t {
    QByteArrayData data[10];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraWorker_t qt_meta_stringdata_CameraWorker = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CameraWorker"
QT_MOC_LITERAL(1, 13, 11), // "finishedRec"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 9), // "insertBed"
QT_MOC_LITERAL(4, 36, 12), // "startWriting"
QT_MOC_LITERAL(5, 49, 6), // "record"
QT_MOC_LITERAL(6, 56, 4), // "init"
QT_MOC_LITERAL(7, 61, 13), // "stopRecording"
QT_MOC_LITERAL(8, 75, 22), // "optical_reconstruction"
QT_MOC_LITERAL(9, 98, 10) // "createXray"

    },
    "CameraWorker\0finishedRec\0\0insertBed\0"
    "startWriting\0record\0init\0stopRecording\0"
    "optical_reconstruction\0createXray"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CameraWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CameraWorker *_t = static_cast<CameraWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finishedRec(); break;
        case 1: _t->insertBed(); break;
        case 2: _t->startWriting(); break;
        case 3: _t->record(); break;
        case 4: _t->init(); break;
        case 5: _t->stopRecording(); break;
        case 6: _t->optical_reconstruction(); break;
        case 7: _t->createXray(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CameraWorker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraWorker::finishedRec)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CameraWorker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraWorker::insertBed)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CameraWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CameraWorker.data,
      qt_meta_data_CameraWorker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CameraWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CameraWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CameraWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CameraWorker::finishedRec()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CameraWorker::insertBed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
