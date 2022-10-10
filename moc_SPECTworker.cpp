/****************************************************************************
** Meta object code from reading C++ file 'SPECTworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/SPECTworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SPECTworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SPECTworker_t {
    QByteArrayData data[12];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SPECTworker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SPECTworker_t qt_meta_stringdata_SPECTworker = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SPECTworker"
QT_MOC_LITERAL(1, 12, 14), // "stopProcessing"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 23), // "sendImagingDataProgress"
QT_MOC_LITERAL(4, 52, 14), // "QVector<qreal>"
QT_MOC_LITERAL(5, 67, 13), // "imageFinished"
QT_MOC_LITERAL(6, 81, 9), // "frameStop"
QT_MOC_LITERAL(7, 91, 15), // "receiveContrast"
QT_MOC_LITERAL(8, 107, 11), // "stopImaging"
QT_MOC_LITERAL(9, 119, 3), // "run"
QT_MOC_LITERAL(10, 123, 11), // "imagingData"
QT_MOC_LITERAL(11, 135, 10) // "Initialise"

    },
    "SPECTworker\0stopProcessing\0\0"
    "sendImagingDataProgress\0QVector<qreal>\0"
    "imageFinished\0frameStop\0receiveContrast\0"
    "stopImaging\0run\0imagingData\0Initialise"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SPECTworker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    8,   60,    2, 0x06 /* Public */,
       5,    0,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   78,    2, 0x0a /* Public */,
       7,    1,   79,    2, 0x0a /* Public */,
       8,    0,   82,    2, 0x0a /* Public */,
       9,    0,   83,    2, 0x0a /* Public */,
      10,    0,   84,    2, 0x0a /* Public */,
      11,    0,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 4, QMetaType::QPolygonF, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int,    2,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SPECTworker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SPECTworker *_t = static_cast<SPECTworker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stopProcessing(); break;
        case 1: _t->sendImagingDataProgress((*reinterpret_cast< QVector<qreal>(*)>(_a[1])),(*reinterpret_cast< QVector<qreal>(*)>(_a[2])),(*reinterpret_cast< QVector<qreal>(*)>(_a[3])),(*reinterpret_cast< QPolygonF(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8]))); break;
        case 2: _t->imageFinished(); break;
        case 3: _t->frameStop(); break;
        case 4: _t->receiveContrast((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->stopImaging(); break;
        case 6: _t->run(); break;
        case 7: _t->imagingData(); break;
        case 8: _t->Initialise(); break;
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
            using _t = void (SPECTworker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SPECTworker::stopProcessing)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SPECTworker::*)(QVector<qreal> , QVector<qreal> , QVector<qreal> , QPolygonF , double , double , double , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SPECTworker::sendImagingDataProgress)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SPECTworker::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SPECTworker::imageFinished)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SPECTworker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SPECTworker.data,
      qt_meta_data_SPECTworker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SPECTworker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SPECTworker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SPECTworker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SPECTworker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SPECTworker::stopProcessing()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SPECTworker::sendImagingDataProgress(QVector<qreal> _t1, QVector<qreal> _t2, QVector<qreal> _t3, QPolygonF _t4, double _t5, double _t6, double _t7, int _t8)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SPECTworker::imageFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
