/****************************************************************************
** Meta object code from reading C++ file 'timeSettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/timeSettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timeSettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_timeSettings_t {
    QByteArrayData data[10];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_timeSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_timeSettings_t qt_meta_stringdata_timeSettings = {
    {
QT_MOC_LITERAL(0, 0, 12), // "timeSettings"
QT_MOC_LITERAL(1, 13, 15), // "previousPressed"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 13), // "finishPressed"
QT_MOC_LITERAL(4, 44, 16), // "sendTimeSettings"
QT_MOC_LITERAL(5, 61, 33), // "cb_expTime_2_currentIndex_Cha..."
QT_MOC_LITERAL(6, 95, 16), // "setStudyProtocol"
QT_MOC_LITERAL(7, 112, 18), // "setUserDefinedCase"
QT_MOC_LITERAL(8, 131, 18), // "on_PB_prev_clicked"
QT_MOC_LITERAL(9, 150, 16) // "on_PB_ok_clicked"

    },
    "timeSettings\0previousPressed\0\0"
    "finishPressed\0sendTimeSettings\0"
    "cb_expTime_2_currentIndex_Changed\0"
    "setStudyProtocol\0setUserDefinedCase\0"
    "on_PB_prev_clicked\0on_PB_ok_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_timeSettings[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    5,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   67,    2, 0x08 /* Private */,
       6,    1,   70,    2, 0x08 /* Private */,
       7,    1,   73,    2, 0x08 /* Private */,
       8,    0,   76,    2, 0x08 /* Private */,
       9,    0,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    2,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void timeSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        timeSettings *_t = static_cast<timeSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->previousPressed(); break;
        case 1: _t->finishPressed(); break;
        case 2: _t->sendTimeSettings((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 3: _t->cb_expTime_2_currentIndex_Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setStudyProtocol((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setUserDefinedCase((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_PB_prev_clicked(); break;
        case 7: _t->on_PB_ok_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (timeSettings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&timeSettings::previousPressed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (timeSettings::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&timeSettings::finishPressed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (timeSettings::*)(int , int , QString , QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&timeSettings::sendTimeSettings)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject timeSettings::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_timeSettings.data,
      qt_meta_data_timeSettings,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *timeSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *timeSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_timeSettings.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int timeSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void timeSettings::previousPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void timeSettings::finishPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void timeSettings::sendTimeSettings(int _t1, int _t2, QString _t3, QString _t4, bool _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
