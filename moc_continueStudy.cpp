/****************************************************************************
** Meta object code from reading C++ file 'continueStudy.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/continueStudy.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'continueStudy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_continueStudy_t {
    QByteArrayData data[8];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_continueStudy_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_continueStudy_t qt_meta_stringdata_continueStudy = {
    {
QT_MOC_LITERAL(0, 0, 13), // "continueStudy"
QT_MOC_LITERAL(1, 14, 8), // "followUp"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "restartStudy"
QT_MOC_LITERAL(4, 37, 4), // "exit"
QT_MOC_LITERAL(5, 42, 27), // "on_PB_InitiateStudy_clicked"
QT_MOC_LITERAL(6, 70, 21), // "on_PB_restart_clicked"
QT_MOC_LITERAL(7, 92, 18) // "on_PB_Exit_clicked"

    },
    "continueStudy\0followUp\0\0restartStudy\0"
    "exit\0on_PB_InitiateStudy_clicked\0"
    "on_PB_restart_clicked\0on_PB_Exit_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_continueStudy[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void continueStudy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        continueStudy *_t = static_cast<continueStudy *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->followUp(); break;
        case 1: _t->restartStudy(); break;
        case 2: _t->exit(); break;
        case 3: _t->on_PB_InitiateStudy_clicked(); break;
        case 4: _t->on_PB_restart_clicked(); break;
        case 5: _t->on_PB_Exit_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (continueStudy::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&continueStudy::followUp)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (continueStudy::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&continueStudy::restartStudy)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (continueStudy::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&continueStudy::exit)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject continueStudy::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_continueStudy.data,
      qt_meta_data_continueStudy,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *continueStudy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *continueStudy::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_continueStudy.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int continueStudy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void continueStudy::followUp()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void continueStudy::restartStudy()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void continueStudy::exit()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
