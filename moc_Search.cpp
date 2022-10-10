/****************************************************************************
** Meta object code from reading C++ file 'Search.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/Search.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Search.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_cSqlTableQueryModel_t {
    QByteArrayData data[1];
    char stringdata0[20];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cSqlTableQueryModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cSqlTableQueryModel_t qt_meta_stringdata_cSqlTableQueryModel = {
    {
QT_MOC_LITERAL(0, 0, 19) // "cSqlTableQueryModel"

    },
    "cSqlTableQueryModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cSqlTableQueryModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void cSqlTableQueryModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject cSqlTableQueryModel::staticMetaObject = {
    { &QSqlTableModel::staticMetaObject, qt_meta_stringdata_cSqlTableQueryModel.data,
      qt_meta_data_cSqlTableQueryModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *cSqlTableQueryModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cSqlTableQueryModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cSqlTableQueryModel.stringdata0))
        return static_cast<void*>(this);
    return QSqlTableModel::qt_metacast(_clname);
}

int cSqlTableQueryModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_Search_t {
    QByteArrayData data[13];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Search_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Search_t qt_meta_stringdata_Search = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Search"
QT_MOC_LITERAL(1, 7, 4), // "Init"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 11), // "ResiseTable"
QT_MOC_LITERAL(4, 25, 10), // "TableQuery"
QT_MOC_LITERAL(5, 36, 26), // "on_double_click_table_item"
QT_MOC_LITERAL(6, 63, 11), // "QModelIndex"
QT_MOC_LITERAL(7, 75, 8), // "getRowID"
QT_MOC_LITERAL(8, 84, 12), // "QStringList&"
QT_MOC_LITERAL(9, 97, 3), // "lst"
QT_MOC_LITERAL(10, 101, 6), // "column"
QT_MOC_LITERAL(11, 108, 10), // "dateSearch"
QT_MOC_LITERAL(12, 119, 11) // "comboSearch"

    },
    "Search\0Init\0\0ResiseTable\0TableQuery\0"
    "on_double_click_table_item\0QModelIndex\0"
    "getRowID\0QStringList&\0lst\0column\0"
    "dateSearch\0comboSearch"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Search[] = {

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
       3,    1,   50,    2, 0x08 /* Private */,
       4,    1,   53,    2, 0x08 /* Private */,
       5,    1,   56,    2, 0x08 /* Private */,
       7,    2,   59,    2, 0x08 /* Private */,
      11,    0,   64,    2, 0x08 /* Private */,
      12,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Int, 0x80000000 | 8, QMetaType::Int,    9,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Search::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Search *_t = static_cast<Search *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Init(); break;
        case 1: _t->ResiseTable((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->TableQuery((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->on_double_click_table_item((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: { int _r = _t->getRowID((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->dateSearch(); break;
        case 6: _t->comboSearch(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Search::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Search.data,
      qt_meta_data_Search,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Search::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Search::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Search.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Search::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
