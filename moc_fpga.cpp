/****************************************************************************
** Meta object code from reading C++ file 'fpga.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/fpga.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fpga.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_fpga_t {
    QByteArrayData data[24];
    char stringdata0[335];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fpga_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fpga_t qt_meta_stringdata_fpga = {
    {
QT_MOC_LITERAL(0, 0, 4), // "fpga"
QT_MOC_LITERAL(1, 5, 9), // "readyRead"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 13), // "sendErrorCode"
QT_MOC_LITERAL(4, 30, 18), // "downloadSuccesfull"
QT_MOC_LITERAL(5, 49, 8), // "exitBash"
QT_MOC_LITERAL(6, 58, 22), // "initialisationComplete"
QT_MOC_LITERAL(7, 81, 11), // "check_lsusb"
QT_MOC_LITERAL(8, 93, 26), // "download_SPECT_FPGA_script"
QT_MOC_LITERAL(9, 120, 15), // "check_downState"
QT_MOC_LITERAL(10, 136, 4), // "exit"
QT_MOC_LITERAL(11, 141, 25), // "check_xmd_connectionState"
QT_MOC_LITERAL(12, 167, 3), // "run"
QT_MOC_LITERAL(13, 171, 4), // "stop"
QT_MOC_LITERAL(14, 176, 9), // "terminate"
QT_MOC_LITERAL(15, 186, 20), // "Initialize_ADC_SPECT"
QT_MOC_LITERAL(16, 207, 12), // "kill_process"
QT_MOC_LITERAL(17, 220, 23), // "check_usb_whileDownload"
QT_MOC_LITERAL(18, 244, 7), // "started"
QT_MOC_LITERAL(19, 252, 9), // "fpgaError"
QT_MOC_LITERAL(20, 262, 10), // "cleanCable"
QT_MOC_LITERAL(21, 273, 18), // "script_batFinished"
QT_MOC_LITERAL(22, 292, 22), // "timeForDownloadElapsed"
QT_MOC_LITERAL(23, 315, 19) // "initScript_finished"

    },
    "fpga\0readyRead\0\0sendErrorCode\0"
    "downloadSuccesfull\0exitBash\0"
    "initialisationComplete\0check_lsusb\0"
    "download_SPECT_FPGA_script\0check_downState\0"
    "exit\0check_xmd_connectionState\0run\0"
    "stop\0terminate\0Initialize_ADC_SPECT\0"
    "kill_process\0check_usb_whileDownload\0"
    "started\0fpgaError\0cleanCable\0"
    "script_batFinished\0timeForDownloadElapsed\0"
    "initScript_finished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fpga[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  124,    2, 0x06 /* Public */,
       3,    1,  125,    2, 0x06 /* Public */,
       4,    0,  128,    2, 0x06 /* Public */,
       5,    0,  129,    2, 0x06 /* Public */,
       6,    0,  130,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  131,    2, 0x0a /* Public */,
       8,    0,  132,    2, 0x0a /* Public */,
       9,    0,  133,    2, 0x0a /* Public */,
      10,    0,  134,    2, 0x0a /* Public */,
      11,    0,  135,    2, 0x0a /* Public */,
      12,    0,  136,    2, 0x0a /* Public */,
      13,    0,  137,    2, 0x0a /* Public */,
      14,    0,  138,    2, 0x0a /* Public */,
      15,    0,  139,    2, 0x0a /* Public */,
      16,    1,  140,    2, 0x0a /* Public */,
      17,    0,  143,    2, 0x0a /* Public */,
      18,    0,  144,    2, 0x0a /* Public */,
      19,    0,  145,    2, 0x08 /* Private */,
      20,    0,  146,    2, 0x08 /* Private */,
      21,    1,  147,    2, 0x08 /* Private */,
      22,    0,  150,    2, 0x08 /* Private */,
      23,    1,  151,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void fpga::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        fpga *_t = static_cast<fpga *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readyRead(); break;
        case 1: _t->sendErrorCode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->downloadSuccesfull(); break;
        case 3: _t->exitBash(); break;
        case 4: _t->initialisationComplete(); break;
        case 5: { bool _r = _t->check_lsusb();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->download_SPECT_FPGA_script(); break;
        case 7: _t->check_downState(); break;
        case 8: _t->exit(); break;
        case 9: _t->check_xmd_connectionState(); break;
        case 10: _t->run(); break;
        case 11: _t->stop(); break;
        case 12: _t->terminate(); break;
        case 13: _t->Initialize_ADC_SPECT(); break;
        case 14: _t->kill_process((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->check_usb_whileDownload(); break;
        case 16: _t->started(); break;
        case 17: _t->fpgaError(); break;
        case 18: _t->cleanCable(); break;
        case 19: _t->script_batFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->timeForDownloadElapsed(); break;
        case 21: _t->initScript_finished((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (fpga::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&fpga::readyRead)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (fpga::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&fpga::sendErrorCode)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (fpga::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&fpga::downloadSuccesfull)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (fpga::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&fpga::exitBash)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (fpga::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&fpga::initialisationComplete)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject fpga::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_fpga.data,
      qt_meta_data_fpga,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *fpga::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fpga::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_fpga.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int fpga::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void fpga::readyRead()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void fpga::sendErrorCode(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void fpga::downloadSuccesfull()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void fpga::exitBash()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void fpga::initialisationComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
