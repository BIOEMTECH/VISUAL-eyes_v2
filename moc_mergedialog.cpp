/****************************************************************************
** Meta object code from reading C++ file 'mergedialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/mergedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mergedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mergeDialog_t {
    QByteArrayData data[9];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mergeDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mergeDialog_t qt_meta_stringdata_mergeDialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "mergeDialog"
QT_MOC_LITERAL(1, 12, 16), // "on_pB_ok_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 20), // "on_pB_cancel_clicked"
QT_MOC_LITERAL(4, 51, 9), // "addFrames"
QT_MOC_LITERAL(5, 61, 12), // "saveSumDICOM"
QT_MOC_LITERAL(6, 74, 10), // "closeEvent"
QT_MOC_LITERAL(7, 85, 12), // "QCloseEvent*"
QT_MOC_LITERAL(8, 98, 12) // "saveInfoFile"

    },
    "mergeDialog\0on_pB_ok_clicked\0\0"
    "on_pB_cancel_clicked\0addFrames\0"
    "saveSumDICOM\0closeEvent\0QCloseEvent*\0"
    "saveInfoFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mergeDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    1,   48,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,

       0        // eod
};

void mergeDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mergeDialog *_t = static_cast<mergeDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pB_ok_clicked(); break;
        case 1: _t->on_pB_cancel_clicked(); break;
        case 2: _t->addFrames(); break;
        case 3: _t->saveSumDICOM(); break;
        case 4: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 5: _t->saveInfoFile(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mergeDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_mergeDialog.data,
      qt_meta_data_mergeDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *mergeDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mergeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mergeDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int mergeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
