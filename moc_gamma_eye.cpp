/****************************************************************************
** Meta object code from reading C++ file 'gamma_eye.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/gamma_eye.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamma_eye.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_gamma_eye_t {
    QByteArrayData data[86];
    char stringdata0[1424];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_gamma_eye_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_gamma_eye_t qt_meta_stringdata_gamma_eye = {
    {
QT_MOC_LITERAL(0, 0, 9), // "gamma_eye"
QT_MOC_LITERAL(1, 10, 19), // "saveStudyToDatabase"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 17), // "closeTimeSettings"
QT_MOC_LITERAL(4, 49, 14), // "terminate_fpga"
QT_MOC_LITERAL(5, 64, 14), // "onPressedStart"
QT_MOC_LITERAL(6, 79, 13), // "onPressedStop"
QT_MOC_LITERAL(7, 93, 12), // "updateSummed"
QT_MOC_LITERAL(8, 106, 12), // "sendContrast"
QT_MOC_LITERAL(9, 119, 16), // "exitToMainWindow"
QT_MOC_LITERAL(10, 136, 13), // "sendFrameStop"
QT_MOC_LITERAL(11, 150, 16), // "openTimeSettings"
QT_MOC_LITERAL(12, 167, 4), // "exit"
QT_MOC_LITERAL(13, 172, 11), // "exitProgram"
QT_MOC_LITERAL(14, 184, 12), // "sendStudyDir"
QT_MOC_LITERAL(15, 197, 17), // "deleteSPECTarrays"
QT_MOC_LITERAL(16, 215, 15), // "bedInsertSignal"
QT_MOC_LITERAL(17, 231, 8), // "Initiate"
QT_MOC_LITERAL(18, 240, 8), // "closeWin"
QT_MOC_LITERAL(19, 249, 10), // "StudyCycle"
QT_MOC_LITERAL(20, 260, 16), // "calibrationCycle"
QT_MOC_LITERAL(21, 277, 11), // "getOperator"
QT_MOC_LITERAL(22, 289, 10), // "getStudyID"
QT_MOC_LITERAL(23, 300, 16), // "getCalibrationID"
QT_MOC_LITERAL(24, 317, 14), // "AquisitionData"
QT_MOC_LITERAL(25, 332, 5), // "reset"
QT_MOC_LITERAL(26, 338, 9), // "saveDICOM"
QT_MOC_LITERAL(27, 348, 12), // "fpgaErrorMsg"
QT_MOC_LITERAL(28, 361, 18), // "disableStartButton"
QT_MOC_LITERAL(29, 380, 15), // "startAquisition"
QT_MOC_LITERAL(30, 396, 14), // "stopAquisition"
QT_MOC_LITERAL(31, 411, 13), // "stopWithError"
QT_MOC_LITERAL(32, 425, 15), // "InitiateThreads"
QT_MOC_LITERAL(33, 441, 11), // "plotsUpdate"
QT_MOC_LITERAL(34, 453, 14), // "QVector<qreal>"
QT_MOC_LITERAL(35, 468, 18), // "sliderValueChanged"
QT_MOC_LITERAL(36, 487, 31), // "cb_ColorMap_currentIndexChanged"
QT_MOC_LITERAL(37, 519, 11), // "frameReplot"
QT_MOC_LITERAL(38, 531, 17), // "directoryCreation"
QT_MOC_LITERAL(39, 549, 17), // "infoFileGenerator"
QT_MOC_LITERAL(40, 567, 24), // "calibrationInfoGenerator"
QT_MOC_LITERAL(41, 592, 15), // "getNewFrameTime"
QT_MOC_LITERAL(42, 608, 18), // "RestartApplication"
QT_MOC_LITERAL(43, 627, 13), // "insertCapture"
QT_MOC_LITERAL(44, 641, 13), // "changeVoltage"
QT_MOC_LITERAL(45, 655, 17), // "getCameraFeedback"
QT_MOC_LITERAL(46, 673, 15), // "insertNoCapture"
QT_MOC_LITERAL(47, 689, 13), // "exitBedDialog"
QT_MOC_LITERAL(48, 703, 14), // "FPGA_initState"
QT_MOC_LITERAL(49, 718, 17), // "arduino_initState"
QT_MOC_LITERAL(50, 736, 19), // "timeFinishedPressed"
QT_MOC_LITERAL(51, 756, 18), // "arduinoSocketState"
QT_MOC_LITERAL(52, 775, 13), // "bedEjectState"
QT_MOC_LITERAL(53, 789, 12), // "setDecayInfo"
QT_MOC_LITERAL(54, 802, 24), // "sliderSummedValueChanged"
QT_MOC_LITERAL(55, 827, 16), // "configureArduino"
QT_MOC_LITERAL(56, 844, 15), // "gammaEvaluation"
QT_MOC_LITERAL(57, 860, 10), // "pdf_report"
QT_MOC_LITERAL(58, 871, 19), // "PB_startDAQ_clicked"
QT_MOC_LITERAL(59, 891, 9), // "qwt_plots"
QT_MOC_LITERAL(60, 901, 20), // "qwt_validation_plots"
QT_MOC_LITERAL(61, 922, 28), // "delete_qwt_plots_and_globals"
QT_MOC_LITERAL(62, 951, 27), // "delete_qwt_validation_plots"
QT_MOC_LITERAL(63, 979, 39), // "on_actionGo_back_to_main_menu..."
QT_MOC_LITERAL(64, 1019, 29), // "on_actionInsert_Bed_triggered"
QT_MOC_LITERAL(65, 1049, 28), // "on_actionEject_Bed_triggered"
QT_MOC_LITERAL(66, 1078, 41), // "on_actionCalibrate_Bed_Positi..."
QT_MOC_LITERAL(67, 1120, 19), // "on_PB_eject_clicked"
QT_MOC_LITERAL(68, 1140, 12), // "on_cb_fusion"
QT_MOC_LITERAL(69, 1153, 7), // "checked"
QT_MOC_LITERAL(70, 1161, 10), // "on_cb_xray"
QT_MOC_LITERAL(71, 1172, 20), // "setCheckstateOptical"
QT_MOC_LITERAL(72, 1193, 17), // "setCheckstateXray"
QT_MOC_LITERAL(73, 1211, 12), // "msgBoxClosed"
QT_MOC_LITERAL(74, 1224, 16), // "QAbstractButton*"
QT_MOC_LITERAL(75, 1241, 13), // "msgBox2Closed"
QT_MOC_LITERAL(76, 1255, 14), // "errorMsgAction"
QT_MOC_LITERAL(77, 1270, 20), // "CameraErrorMsgAction"
QT_MOC_LITERAL(78, 1291, 11), // "msgBoxBedIn"
QT_MOC_LITERAL(79, 1303, 20), // "addOpticalBackground"
QT_MOC_LITERAL(80, 1324, 17), // "addXrayBackground"
QT_MOC_LITERAL(81, 1342, 16), // "removeBackground"
QT_MOC_LITERAL(82, 1359, 19), // "opacityValueChanged"
QT_MOC_LITERAL(83, 1379, 19), // "setBackgroundImages"
QT_MOC_LITERAL(84, 1399, 18), // "searchPhotopeak_T1"
QT_MOC_LITERAL(85, 1418, 5) // "TH1F*"

    },
    "gamma_eye\0saveStudyToDatabase\0\0"
    "closeTimeSettings\0terminate_fpga\0"
    "onPressedStart\0onPressedStop\0updateSummed\0"
    "sendContrast\0exitToMainWindow\0"
    "sendFrameStop\0openTimeSettings\0exit\0"
    "exitProgram\0sendStudyDir\0deleteSPECTarrays\0"
    "bedInsertSignal\0Initiate\0closeWin\0"
    "StudyCycle\0calibrationCycle\0getOperator\0"
    "getStudyID\0getCalibrationID\0AquisitionData\0"
    "reset\0saveDICOM\0fpgaErrorMsg\0"
    "disableStartButton\0startAquisition\0"
    "stopAquisition\0stopWithError\0"
    "InitiateThreads\0plotsUpdate\0QVector<qreal>\0"
    "sliderValueChanged\0cb_ColorMap_currentIndexChanged\0"
    "frameReplot\0directoryCreation\0"
    "infoFileGenerator\0calibrationInfoGenerator\0"
    "getNewFrameTime\0RestartApplication\0"
    "insertCapture\0changeVoltage\0"
    "getCameraFeedback\0insertNoCapture\0"
    "exitBedDialog\0FPGA_initState\0"
    "arduino_initState\0timeFinishedPressed\0"
    "arduinoSocketState\0bedEjectState\0"
    "setDecayInfo\0sliderSummedValueChanged\0"
    "configureArduino\0gammaEvaluation\0"
    "pdf_report\0PB_startDAQ_clicked\0qwt_plots\0"
    "qwt_validation_plots\0delete_qwt_plots_and_globals\0"
    "delete_qwt_validation_plots\0"
    "on_actionGo_back_to_main_menu_triggered\0"
    "on_actionInsert_Bed_triggered\0"
    "on_actionEject_Bed_triggered\0"
    "on_actionCalibrate_Bed_Position_triggered\0"
    "on_PB_eject_clicked\0on_cb_fusion\0"
    "checked\0on_cb_xray\0setCheckstateOptical\0"
    "setCheckstateXray\0msgBoxClosed\0"
    "QAbstractButton*\0msgBox2Closed\0"
    "errorMsgAction\0CameraErrorMsgAction\0"
    "msgBoxBedIn\0addOpticalBackground\0"
    "addXrayBackground\0removeBackground\0"
    "opacityValueChanged\0setBackgroundImages\0"
    "searchPhotopeak_T1\0TH1F*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_gamma_eye[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      80,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  414,    2, 0x06 /* Public */,
       3,    0,  423,    2, 0x06 /* Public */,
       4,    0,  424,    2, 0x06 /* Public */,
       5,    0,  425,    2, 0x06 /* Public */,
       6,    0,  426,    2, 0x06 /* Public */,
       7,    0,  427,    2, 0x06 /* Public */,
       8,    1,  428,    2, 0x06 /* Public */,
       9,    0,  431,    2, 0x06 /* Public */,
      10,    0,  432,    2, 0x06 /* Public */,
      11,    0,  433,    2, 0x06 /* Public */,
      12,    0,  434,    2, 0x06 /* Public */,
      13,    0,  435,    2, 0x06 /* Public */,
      14,    1,  436,    2, 0x06 /* Public */,
      15,    0,  439,    2, 0x06 /* Public */,
      16,    1,  440,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,  443,    2, 0x0a /* Public */,
      18,    0,  444,    2, 0x0a /* Public */,
      19,    0,  445,    2, 0x0a /* Public */,
      20,    0,  446,    2, 0x0a /* Public */,
      21,    1,  447,    2, 0x0a /* Public */,
      22,    4,  450,    2, 0x0a /* Public */,
      23,    2,  459,    2, 0x0a /* Public */,
      24,    5,  464,    2, 0x0a /* Public */,
      25,    0,  475,    2, 0x0a /* Public */,
      26,    0,  476,    2, 0x0a /* Public */,
      27,    1,  477,    2, 0x0a /* Public */,
      28,    0,  480,    2, 0x0a /* Public */,
      29,    0,  481,    2, 0x0a /* Public */,
      30,    0,  482,    2, 0x0a /* Public */,
      31,    0,  483,    2, 0x0a /* Public */,
      32,    0,  484,    2, 0x0a /* Public */,
      33,    8,  485,    2, 0x0a /* Public */,
      35,    1,  502,    2, 0x0a /* Public */,
      36,    1,  505,    2, 0x0a /* Public */,
      37,    0,  508,    2, 0x0a /* Public */,
      38,    0,  509,    2, 0x0a /* Public */,
      39,    0,  510,    2, 0x0a /* Public */,
      40,    0,  511,    2, 0x0a /* Public */,
      41,    1,  512,    2, 0x0a /* Public */,
      42,    0,  515,    2, 0x0a /* Public */,
      43,    0,  516,    2, 0x0a /* Public */,
      44,    1,  517,    2, 0x0a /* Public */,
      45,    0,  520,    2, 0x0a /* Public */,
      46,    0,  521,    2, 0x0a /* Public */,
      47,    0,  522,    2, 0x0a /* Public */,
      48,    0,  523,    2, 0x0a /* Public */,
      49,    0,  524,    2, 0x0a /* Public */,
      50,    0,  525,    2, 0x0a /* Public */,
      51,    0,  526,    2, 0x0a /* Public */,
      52,    0,  527,    2, 0x0a /* Public */,
      53,    6,  528,    2, 0x0a /* Public */,
      54,    1,  541,    2, 0x0a /* Public */,
      55,    0,  544,    2, 0x0a /* Public */,
      56,    0,  545,    2, 0x08 /* Private */,
      57,    1,  546,    2, 0x08 /* Private */,
      58,    0,  549,    2, 0x08 /* Private */,
      59,    0,  550,    2, 0x08 /* Private */,
      60,    0,  551,    2, 0x08 /* Private */,
      61,    0,  552,    2, 0x08 /* Private */,
      62,    0,  553,    2, 0x08 /* Private */,
      63,    0,  554,    2, 0x08 /* Private */,
      64,    0,  555,    2, 0x08 /* Private */,
      65,    0,  556,    2, 0x08 /* Private */,
      66,    0,  557,    2, 0x08 /* Private */,
      67,    0,  558,    2, 0x08 /* Private */,
      68,    1,  559,    2, 0x08 /* Private */,
      70,    1,  562,    2, 0x08 /* Private */,
      71,    0,  565,    2, 0x08 /* Private */,
      72,    0,  566,    2, 0x08 /* Private */,
      73,    1,  567,    2, 0x08 /* Private */,
      75,    1,  570,    2, 0x08 /* Private */,
      76,    1,  573,    2, 0x08 /* Private */,
      77,    1,  576,    2, 0x08 /* Private */,
      78,    1,  579,    2, 0x08 /* Private */,
      79,    0,  582,    2, 0x08 /* Private */,
      80,    0,  583,    2, 0x08 /* Private */,
      81,    0,  584,    2, 0x08 /* Private */,
      82,    1,  585,    2, 0x08 /* Private */,
      83,    0,  588,    2, 0x08 /* Private */,
      84,    2,  589,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    2,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 34, 0x80000000 | 34, 0x80000000 | 34, QMetaType::QPolygonF, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int,    2,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QDateTime, QMetaType::Double, QMetaType::QString,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   69,
    QMetaType::Void, QMetaType::Bool,   69,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 74,    2,
    QMetaType::Void, 0x80000000 | 74,    2,
    QMetaType::Void, 0x80000000 | 74,    2,
    QMetaType::Void, 0x80000000 | 74,    2,
    QMetaType::Void, 0x80000000 | 74,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Float, 0x80000000 | 85, QMetaType::Float,    2,    2,

       0        // eod
};

void gamma_eye::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        gamma_eye *_t = static_cast<gamma_eye *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveStudyToDatabase((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: _t->closeTimeSettings(); break;
        case 2: _t->terminate_fpga(); break;
        case 3: _t->onPressedStart(); break;
        case 4: _t->onPressedStop(); break;
        case 5: _t->updateSummed(); break;
        case 6: _t->sendContrast((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->exitToMainWindow(); break;
        case 8: _t->sendFrameStop(); break;
        case 9: _t->openTimeSettings(); break;
        case 10: _t->exit(); break;
        case 11: _t->exitProgram(); break;
        case 12: _t->sendStudyDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->deleteSPECTarrays(); break;
        case 14: _t->bedInsertSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->Initiate(); break;
        case 16: _t->closeWin(); break;
        case 17: _t->StudyCycle(); break;
        case 18: _t->calibrationCycle(); break;
        case 19: _t->getOperator((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->getStudyID((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 21: _t->getCalibrationID((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 22: _t->AquisitionData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 23: _t->reset(); break;
        case 24: _t->saveDICOM(); break;
        case 25: _t->fpgaErrorMsg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->disableStartButton(); break;
        case 27: _t->startAquisition(); break;
        case 28: _t->stopAquisition(); break;
        case 29: _t->stopWithError(); break;
        case 30: _t->InitiateThreads(); break;
        case 31: _t->plotsUpdate((*reinterpret_cast< QVector<qreal>(*)>(_a[1])),(*reinterpret_cast< QVector<qreal>(*)>(_a[2])),(*reinterpret_cast< QVector<qreal>(*)>(_a[3])),(*reinterpret_cast< QPolygonF(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6])),(*reinterpret_cast< double(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8]))); break;
        case 32: _t->sliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->cb_ColorMap_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->frameReplot(); break;
        case 35: _t->directoryCreation(); break;
        case 36: _t->infoFileGenerator(); break;
        case 37: _t->calibrationInfoGenerator(); break;
        case 38: _t->getNewFrameTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->RestartApplication(); break;
        case 40: _t->insertCapture(); break;
        case 41: _t->changeVoltage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 42: _t->getCameraFeedback(); break;
        case 43: _t->insertNoCapture(); break;
        case 44: _t->exitBedDialog(); break;
        case 45: _t->FPGA_initState(); break;
        case 46: _t->arduino_initState(); break;
        case 47: _t->timeFinishedPressed(); break;
        case 48: _t->arduinoSocketState(); break;
        case 49: _t->bedEjectState(); break;
        case 50: _t->setDecayInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< QDateTime(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 51: _t->sliderSummedValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->configureArduino(); break;
        case 53: _t->gammaEvaluation(); break;
        case 54: _t->pdf_report((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 55: _t->PB_startDAQ_clicked(); break;
        case 56: _t->qwt_plots(); break;
        case 57: _t->qwt_validation_plots(); break;
        case 58: _t->delete_qwt_plots_and_globals(); break;
        case 59: _t->delete_qwt_validation_plots(); break;
        case 60: _t->on_actionGo_back_to_main_menu_triggered(); break;
        case 61: _t->on_actionInsert_Bed_triggered(); break;
        case 62: _t->on_actionEject_Bed_triggered(); break;
        case 63: _t->on_actionCalibrate_Bed_Position_triggered(); break;
        case 64: _t->on_PB_eject_clicked(); break;
        case 65: _t->on_cb_fusion((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 66: _t->on_cb_xray((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 67: _t->setCheckstateOptical(); break;
        case 68: _t->setCheckstateXray(); break;
        case 69: _t->msgBoxClosed((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 70: _t->msgBox2Closed((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 71: _t->errorMsgAction((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 72: _t->CameraErrorMsgAction((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 73: _t->msgBoxBedIn((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 74: _t->addOpticalBackground(); break;
        case 75: _t->addXrayBackground(); break;
        case 76: _t->removeBackground(); break;
        case 77: _t->opacityValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 78: _t->setBackgroundImages(); break;
        case 79: { float _r = _t->searchPhotopeak_T1((*reinterpret_cast< TH1F*(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 31:
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
            using _t = void (gamma_eye::*)(QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::saveStudyToDatabase)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::closeTimeSettings)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::terminate_fpga)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::onPressedStart)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::onPressedStop)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::updateSummed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::sendContrast)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::exitToMainWindow)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::sendFrameStop)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::openTimeSettings)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::exit)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::exitProgram)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::sendStudyDir)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::deleteSPECTarrays)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (gamma_eye::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&gamma_eye::bedInsertSignal)) {
                *result = 14;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject gamma_eye::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_gamma_eye.data,
      qt_meta_data_gamma_eye,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *gamma_eye::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *gamma_eye::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_gamma_eye.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int gamma_eye::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 80)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 80;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 80)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 80;
    }
    return _id;
}

// SIGNAL 0
void gamma_eye::saveStudyToDatabase(QString _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void gamma_eye::closeTimeSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void gamma_eye::terminate_fpga()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void gamma_eye::onPressedStart()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void gamma_eye::onPressedStop()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void gamma_eye::updateSummed()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void gamma_eye::sendContrast(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void gamma_eye::exitToMainWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void gamma_eye::sendFrameStop()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void gamma_eye::openTimeSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void gamma_eye::exit()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void gamma_eye::exitProgram()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void gamma_eye::sendStudyDir(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void gamma_eye::deleteSPECTarrays()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void gamma_eye::bedInsertSignal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
