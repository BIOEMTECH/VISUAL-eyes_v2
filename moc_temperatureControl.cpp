/****************************************************************************
** Meta object code from reading C++ file 'temperatureControl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/temperatureControl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'temperatureControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_temperatureControl_t {
    QByteArrayData data[10];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_temperatureControl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_temperatureControl_t qt_meta_stringdata_temperatureControl = {
    {
QT_MOC_LITERAL(0, 0, 18), // "temperatureControl"
QT_MOC_LITERAL(1, 19, 11), // "init_system"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 17), // "check_temperature"
QT_MOC_LITERAL(4, 50, 17), // "close_electronics"
QT_MOC_LITERAL(5, 68, 19), // "measure_temperature"
QT_MOC_LITERAL(6, 88, 23), // "std::tuple<float,float>"
QT_MOC_LITERAL(7, 112, 21), // "process_sensor_output"
QT_MOC_LITERAL(8, 134, 11), // "run_process"
QT_MOC_LITERAL(9, 146, 14) // "temperature_ok"

    },
    "temperatureControl\0init_system\0\0"
    "check_temperature\0close_electronics\0"
    "measure_temperature\0std::tuple<float,float>\0"
    "process_sensor_output\0run_process\0"
    "temperature_ok"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_temperatureControl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x08 /* Private */,
       7,    1,   53,    2, 0x08 /* Private */,
       8,    1,   56,    2, 0x08 /* Private */,
       9,    1,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    0x80000000 | 6,
    0x80000000 | 6, QMetaType::QString,    2,
    QMetaType::QString, QMetaType::QString,    2,
    QMetaType::Bool, QMetaType::Float,    2,

       0        // eod
};

void temperatureControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        temperatureControl *_t = static_cast<temperatureControl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->init_system();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->check_temperature();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->close_electronics(); break;
        case 3: { std::tuple<float,float> _r = _t->measure_temperature();
            if (_a[0]) *reinterpret_cast< std::tuple<float,float>*>(_a[0]) = std::move(_r); }  break;
        case 4: { std::tuple<float,float> _r = _t->process_sensor_output((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::tuple<float,float>*>(_a[0]) = std::move(_r); }  break;
        case 5: { QString _r = _t->run_process((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->temperature_ok((*reinterpret_cast< float(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject temperatureControl::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_temperatureControl.data,
      qt_meta_data_temperatureControl,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *temperatureControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *temperatureControl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_temperatureControl.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int temperatureControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
