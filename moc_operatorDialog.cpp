/****************************************************************************
** Meta object code from reading C++ file 'operatorDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/operatorDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'operatorDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_operatorDialog_t {
    QByteArrayData data[15];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_operatorDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_operatorDialog_t qt_meta_stringdata_operatorDialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "operatorDialog"
QT_MOC_LITERAL(1, 15, 8), // "sendName"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "nextPressed"
QT_MOC_LITERAL(4, 37, 14), // "exitToMainMenu"
QT_MOC_LITERAL(5, 52, 4), // "Init"
QT_MOC_LITERAL(6, 57, 15), // "addInst_pressed"
QT_MOC_LITERAL(7, 73, 13), // "addOp_pressed"
QT_MOC_LITERAL(8, 87, 12), // "Inst_toggled"
QT_MOC_LITERAL(9, 100, 7), // "checked"
QT_MOC_LITERAL(10, 108, 10), // "OP_toggled"
QT_MOC_LITERAL(11, 119, 28), // "hospital_currentIndexChanged"
QT_MOC_LITERAL(12, 148, 5), // "index"
QT_MOC_LITERAL(13, 154, 20), // "on_PB_cancel_clicked"
QT_MOC_LITERAL(14, 175, 18) // "on_PB_next_clicked"

    },
    "operatorDialog\0sendName\0\0nextPressed\0"
    "exitToMainMenu\0Init\0addInst_pressed\0"
    "addOp_pressed\0Inst_toggled\0checked\0"
    "OP_toggled\0hospital_currentIndexChanged\0"
    "index\0on_PB_cancel_clicked\0"
    "on_PB_next_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_operatorDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       3,    0,   72,    2, 0x06 /* Public */,
       4,    0,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   74,    2, 0x0a /* Public */,
       6,    0,   75,    2, 0x08 /* Private */,
       7,    0,   76,    2, 0x08 /* Private */,
       8,    1,   77,    2, 0x08 /* Private */,
      10,    1,   80,    2, 0x08 /* Private */,
      11,    1,   83,    2, 0x08 /* Private */,
      13,    0,   86,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void operatorDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        operatorDialog *_t = static_cast<operatorDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->nextPressed(); break;
        case 2: _t->exitToMainMenu(); break;
        case 3: _t->Init(); break;
        case 4: _t->addInst_pressed(); break;
        case 5: _t->addOp_pressed(); break;
        case 6: _t->Inst_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->OP_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->hospital_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_PB_cancel_clicked(); break;
        case 10: _t->on_PB_next_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (operatorDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&operatorDialog::sendName)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (operatorDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&operatorDialog::nextPressed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (operatorDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&operatorDialog::exitToMainMenu)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject operatorDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_operatorDialog.data,
      qt_meta_data_operatorDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *operatorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *operatorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_operatorDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int operatorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void operatorDialog::sendName(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void operatorDialog::nextPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void operatorDialog::exitToMainMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
