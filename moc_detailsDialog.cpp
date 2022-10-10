/****************************************************************************
** Meta object code from reading C++ file 'detailsDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/detailsDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'detailsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_detailsDialog_t {
    QByteArrayData data[18];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_detailsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_detailsDialog_t qt_meta_stringdata_detailsDialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "detailsDialog"
QT_MOC_LITERAL(1, 14, 15), // "previousPressed"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 11), // "nextPressed"
QT_MOC_LITERAL(4, 43, 11), // "sendStudyID"
QT_MOC_LITERAL(5, 55, 11), // "sendNuclide"
QT_MOC_LITERAL(6, 67, 13), // "sendDacayInfo"
QT_MOC_LITERAL(7, 81, 15), // "sendNuclideName"
QT_MOC_LITERAL(8, 97, 15), // "getTimeSettings"
QT_MOC_LITERAL(9, 113, 12), // "save_Session"
QT_MOC_LITERAL(10, 126, 17), // "requestNewStudyID"
QT_MOC_LITERAL(11, 144, 4), // "Init"
QT_MOC_LITERAL(12, 149, 20), // "Inventory_calculator"
QT_MOC_LITERAL(13, 170, 22), // "on_PB_previous_clicked"
QT_MOC_LITERAL(14, 193, 18), // "on_PB_next_clicked"
QT_MOC_LITERAL(15, 212, 19), // "on_PB_clear_clicked"
QT_MOC_LITERAL(16, 232, 38), // "on_CB_radionuclide_currentInd..."
QT_MOC_LITERAL(17, 271, 36) // "on_cB_collimator_currentIndex..."

    },
    "detailsDialog\0previousPressed\0\0"
    "nextPressed\0sendStudyID\0sendNuclide\0"
    "sendDacayInfo\0sendNuclideName\0"
    "getTimeSettings\0save_Session\0"
    "requestNewStudyID\0Init\0Inventory_calculator\0"
    "on_PB_previous_clicked\0on_PB_next_clicked\0"
    "on_PB_clear_clicked\0"
    "on_CB_radionuclide_currentIndexChanged\0"
    "on_cB_collimator_currentIndexChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_detailsDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    4,   96,    2, 0x06 /* Public */,
       5,    1,  105,    2, 0x06 /* Public */,
       6,    6,  108,    2, 0x06 /* Public */,
       7,    1,  121,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    5,  124,    2, 0x0a /* Public */,
       9,    4,  135,    2, 0x0a /* Public */,
      10,    0,  144,    2, 0x0a /* Public */,
      11,    0,  145,    2, 0x08 /* Private */,
      12,    0,  146,    2, 0x08 /* Private */,
      13,    0,  147,    2, 0x08 /* Private */,
      14,    0,  148,    2, 0x08 /* Private */,
      15,    0,  149,    2, 0x08 /* Private */,
      16,    1,  150,    2, 0x08 /* Private */,
      17,    1,  153,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime, QMetaType::Double, QMetaType::QString,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void detailsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        detailsDialog *_t = static_cast<detailsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->previousPressed(); break;
        case 1: _t->nextPressed(); break;
        case 2: _t->sendStudyID((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 3: _t->sendNuclide((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sendDacayInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QDateTime(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 5: _t->sendNuclideName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->getTimeSettings((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 7: _t->save_Session((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 8: _t->requestNewStudyID(); break;
        case 9: _t->Init(); break;
        case 10: { int _r = _t->Inventory_calculator();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->on_PB_previous_clicked(); break;
        case 12: _t->on_PB_next_clicked(); break;
        case 13: _t->on_PB_clear_clicked(); break;
        case 14: _t->on_CB_radionuclide_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_cB_collimator_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (detailsDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&detailsDialog::previousPressed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (detailsDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&detailsDialog::nextPressed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (detailsDialog::*)(QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&detailsDialog::sendStudyID)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (detailsDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&detailsDialog::sendNuclide)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (detailsDialog::*)(QString , QString , QString , QDateTime , double , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&detailsDialog::sendDacayInfo)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (detailsDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&detailsDialog::sendNuclideName)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject detailsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_detailsDialog.data,
      qt_meta_data_detailsDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *detailsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *detailsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_detailsDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int detailsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void detailsDialog::previousPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void detailsDialog::nextPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void detailsDialog::sendStudyID(QString _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void detailsDialog::sendNuclide(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void detailsDialog::sendDacayInfo(QString _t1, QString _t2, QString _t3, QDateTime _t4, double _t5, QString _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void detailsDialog::sendNuclideName(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
