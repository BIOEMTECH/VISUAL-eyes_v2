/****************************************************************************
** Meta object code from reading C++ file 'PETsysWorker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/PETsysWorker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PETsysWorker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PETsysWorker_t {
    QByteArrayData data[13];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PETsysWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PETsysWorker_t qt_meta_stringdata_PETsysWorker = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PETsysWorker"
QT_MOC_LITERAL(1, 13, 14), // "stopProcessing"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 23), // "sendImagingDataProgress"
QT_MOC_LITERAL(4, 53, 14), // "QVector<qreal>"
QT_MOC_LITERAL(5, 68, 12), // "castor_frame"
QT_MOC_LITERAL(6, 81, 3), // "run"
QT_MOC_LITERAL(7, 85, 10), // "initialise"
QT_MOC_LITERAL(8, 96, 19), // "frameReconstruction"
QT_MOC_LITERAL(9, 116, 11), // "stopToFrame"
QT_MOC_LITERAL(10, 128, 11), // "imagingData"
QT_MOC_LITERAL(11, 140, 15), // "receiveContrast"
QT_MOC_LITERAL(12, 156, 11) // "stopImaging"

    },
    "PETsysWorker\0stopProcessing\0\0"
    "sendImagingDataProgress\0QVector<qreal>\0"
    "castor_frame\0run\0initialise\0"
    "frameReconstruction\0stopToFrame\0"
    "imagingData\0receiveContrast\0stopImaging"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PETsysWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,   10,   65,    2, 0x06 /* Public */,
       5,    1,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   89,    2, 0x0a /* Public */,
       7,    0,   90,    2, 0x0a /* Public */,
       8,    0,   91,    2, 0x0a /* Public */,
       9,    0,   92,    2, 0x0a /* Public */,
      10,    0,   93,    2, 0x0a /* Public */,
      11,    1,   94,    2, 0x0a /* Public */,
      12,    0,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 4, QMetaType::QPolygonF, QMetaType::QPolygonF, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,

       0        // eod
};

void PETsysWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PETsysWorker *_t = static_cast<PETsysWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stopProcessing(); break;
        case 1: _t->sendImagingDataProgress((*reinterpret_cast< QVector<qreal>(*)>(_a[1])),(*reinterpret_cast< QVector<qreal>(*)>(_a[2])),(*reinterpret_cast< QVector<qreal>(*)>(_a[3])),(*reinterpret_cast< QPolygonF(*)>(_a[4])),(*reinterpret_cast< QPolygonF(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7])),(*reinterpret_cast< double(*)>(_a[8])),(*reinterpret_cast< int(*)>(_a[9])),(*reinterpret_cast< int(*)>(_a[10]))); break;
        case 2: _t->castor_frame((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->run(); break;
        case 4: _t->initialise(); break;
        case 5: _t->frameReconstruction(); break;
        case 6: _t->stopToFrame(); break;
        case 7: _t->imagingData(); break;
        case 8: _t->receiveContrast((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->stopImaging(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<qreal> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PETsysWorker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PETsysWorker::stopProcessing)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PETsysWorker::*)(QVector<qreal> , QVector<qreal> , QVector<qreal> , QPolygonF , QPolygonF , double , double , double , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PETsysWorker::sendImagingDataProgress)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PETsysWorker::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PETsysWorker::castor_frame)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PETsysWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PETsysWorker.data,
      qt_meta_data_PETsysWorker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PETsysWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PETsysWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PETsysWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PETsysWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void PETsysWorker::stopProcessing()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PETsysWorker::sendImagingDataProgress(QVector<qreal> _t1, QVector<qreal> _t2, QVector<qreal> _t3, QPolygonF _t4, QPolygonF _t5, double _t6, double _t7, double _t8, int _t9, int _t10)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)), const_cast<void*>(reinterpret_cast<const void*>(&_t9)), const_cast<void*>(reinterpret_cast<const void*>(&_t10)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PETsysWorker::castor_frame(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
