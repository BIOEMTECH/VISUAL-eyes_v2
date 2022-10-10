/****************************************************************************
** Meta object code from reading C++ file 'PostProcessing.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headers/PostProcessing.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PostProcessing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CustomMagnifier_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomMagnifier_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomMagnifier_t qt_meta_stringdata_CustomMagnifier = {
    {
QT_MOC_LITERAL(0, 0, 15) // "CustomMagnifier"

    },
    "CustomMagnifier"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomMagnifier[] = {

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

void CustomMagnifier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CustomMagnifier::staticMetaObject = {
    { &QwtPlotMagnifier::staticMetaObject, qt_meta_stringdata_CustomMagnifier.data,
      qt_meta_data_CustomMagnifier,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CustomMagnifier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomMagnifier::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomMagnifier.stringdata0))
        return static_cast<void*>(this);
    return QwtPlotMagnifier::qt_metacast(_clname);
}

int CustomMagnifier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlotMagnifier::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_GUI_Plot_t {
    QByteArrayData data[25];
    char stringdata0[281];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GUI_Plot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GUI_Plot_t qt_meta_stringdata_GUI_Plot = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GUI_Plot"
QT_MOC_LITERAL(1, 9, 15), // "enableAddButton"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "disableAddButton"
QT_MOC_LITERAL(4, 43, 24), // "construct_picker_machine"
QT_MOC_LITERAL(5, 68, 4), // "Type"
QT_MOC_LITERAL(6, 73, 23), // "destruct_picker_machine"
QT_MOC_LITERAL(7, 97, 17), // "selected_RECT_ROI"
QT_MOC_LITERAL(8, 115, 20), // "selected_ELLIPSE_ROI"
QT_MOC_LITERAL(9, 136, 10), // "drawLineTo"
QT_MOC_LITERAL(10, 147, 9), // "clearROIS"
QT_MOC_LITERAL(11, 157, 7), // "addItem"
QT_MOC_LITERAL(12, 165, 5), // "moved"
QT_MOC_LITERAL(13, 171, 3), // "pos"
QT_MOC_LITERAL(14, 175, 6), // "resize"
QT_MOC_LITERAL(15, 182, 14), // "setItemVisible"
QT_MOC_LITERAL(16, 197, 17), // "QwtPlotShapeItem*"
QT_MOC_LITERAL(17, 215, 4), // "item"
QT_MOC_LITERAL(18, 220, 2), // "on"
QT_MOC_LITERAL(19, 223, 9), // "raiseItem"
QT_MOC_LITERAL(20, 233, 7), // "pressed"
QT_MOC_LITERAL(21, 241, 8), // "released"
QT_MOC_LITERAL(22, 250, 6), // "itemAt"
QT_MOC_LITERAL(23, 257, 12), // "QwtPlotItem*"
QT_MOC_LITERAL(24, 270, 10) // "itemAtEdge"

    },
    "GUI_Plot\0enableAddButton\0\0disableAddButton\0"
    "construct_picker_machine\0Type\0"
    "destruct_picker_machine\0selected_RECT_ROI\0"
    "selected_ELLIPSE_ROI\0drawLineTo\0"
    "clearROIS\0addItem\0moved\0pos\0resize\0"
    "setItemVisible\0QwtPlotShapeItem*\0item\0"
    "on\0raiseItem\0pressed\0released\0itemAt\0"
    "QwtPlotItem*\0itemAtEdge"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUI_Plot[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       3,    1,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,  105,    2, 0x0a /* Public */,
       6,    1,  108,    2, 0x0a /* Public */,
       7,    1,  111,    2, 0x0a /* Public */,
       8,    1,  114,    2, 0x0a /* Public */,
       9,    1,  117,    2, 0x0a /* Public */,
      10,    0,  120,    2, 0x0a /* Public */,
      11,    0,  121,    2, 0x0a /* Public */,
      12,    1,  122,    2, 0x0a /* Public */,
      14,    1,  125,    2, 0x0a /* Public */,
      15,    2,  128,    2, 0x0a /* Public */,
      19,    1,  133,    2, 0x0a /* Public */,
      20,    1,  136,    2, 0x0a /* Public */,
      21,    1,  139,    2, 0x0a /* Public */,
      22,    1,  142,    2, 0x0a /* Public */,
      24,    1,  145,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::QRectF,    2,
    QMetaType::Void, QMetaType::QRectF,    2,
    QMetaType::Void, QMetaType::QPointF,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   13,
    QMetaType::Void, QMetaType::QPoint,   13,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Bool,   17,   18,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Bool, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    0x80000000 | 23, QMetaType::QPoint,    2,
    0x80000000 | 23, QMetaType::QPoint,    2,

       0        // eod
};

void GUI_Plot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GUI_Plot *_t = static_cast<GUI_Plot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enableAddButton((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->disableAddButton((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->construct_picker_machine((*reinterpret_cast< Type(*)>(_a[1]))); break;
        case 3: _t->destruct_picker_machine((*reinterpret_cast< Type(*)>(_a[1]))); break;
        case 4: _t->selected_RECT_ROI((*reinterpret_cast< QRectF(*)>(_a[1]))); break;
        case 5: _t->selected_ELLIPSE_ROI((*reinterpret_cast< QRectF(*)>(_a[1]))); break;
        case 6: _t->drawLineTo((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 7: _t->clearROIS(); break;
        case 8: _t->addItem(); break;
        case 9: _t->moved((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 10: _t->resize((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 11: _t->setItemVisible((*reinterpret_cast< QwtPlotShapeItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 12: _t->raiseItem((*reinterpret_cast< QwtPlotShapeItem*(*)>(_a[1]))); break;
        case 13: { bool _r = _t->pressed((*reinterpret_cast< const QPoint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->released((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 15: { QwtPlotItem* _r = _t->itemAt((*reinterpret_cast< const QPoint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QwtPlotItem**>(_a[0]) = std::move(_r); }  break;
        case 16: { QwtPlotItem* _r = _t->itemAtEdge((*reinterpret_cast< const QPoint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QwtPlotItem**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GUI_Plot::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI_Plot::enableAddButton)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GUI_Plot::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GUI_Plot::disableAddButton)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GUI_Plot::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_GUI_Plot.data,
      qt_meta_data_GUI_Plot,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GUI_Plot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUI_Plot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GUI_Plot.stringdata0))
        return static_cast<void*>(this);
    return QwtPlot::qt_metacast(_clname);
}

int GUI_Plot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void GUI_Plot::enableAddButton(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GUI_Plot::disableAddButton(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_NumberFormatDelegate_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NumberFormatDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NumberFormatDelegate_t qt_meta_stringdata_NumberFormatDelegate = {
    {
QT_MOC_LITERAL(0, 0, 20) // "NumberFormatDelegate"

    },
    "NumberFormatDelegate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NumberFormatDelegate[] = {

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

void NumberFormatDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject NumberFormatDelegate::staticMetaObject = {
    { &QStyledItemDelegate::staticMetaObject, qt_meta_stringdata_NumberFormatDelegate.data,
      qt_meta_data_NumberFormatDelegate,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NumberFormatDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NumberFormatDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NumberFormatDelegate.stringdata0))
        return static_cast<void*>(this);
    return QStyledItemDelegate::qt_metacast(_clname);
}

int NumberFormatDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStyledItemDelegate::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_PostProcessing_t {
    QByteArrayData data[72];
    char stringdata0[1197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PostProcessing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PostProcessing_t qt_meta_stringdata_PostProcessing = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PostProcessing"
QT_MOC_LITERAL(1, 15, 12), // "closedWindow"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "directFileLoader"
QT_MOC_LITERAL(4, 46, 11), // "ImageSlider"
QT_MOC_LITERAL(5, 58, 28), // "combobox_currentIndexChanged"
QT_MOC_LITERAL(6, 87, 4), // "Init"
QT_MOC_LITERAL(7, 92, 18), // "sliderValueChanged"
QT_MOC_LITERAL(8, 111, 19), // "LoadStudy_triggered"
QT_MOC_LITERAL(9, 131, 20), // "selectActivityPerROI"
QT_MOC_LITERAL(10, 152, 18), // "selectCountsPerROI"
QT_MOC_LITERAL(11, 171, 13), // "loadLastStudy"
QT_MOC_LITERAL(12, 185, 21), // "on_pb_rectROI_clicked"
QT_MOC_LITERAL(13, 207, 24), // "on_pb_ellipseROI_clicked"
QT_MOC_LITERAL(14, 232, 21), // "on_pb_freeROI_clicked"
QT_MOC_LITERAL(15, 254, 24), // "on_PB_ShowLabels_toggled"
QT_MOC_LITERAL(16, 279, 15), // "ShowContextMenu"
QT_MOC_LITERAL(17, 295, 16), // "ShowContextMenu2"
QT_MOC_LITERAL(18, 312, 12), // "addROItoList"
QT_MOC_LITERAL(19, 325, 22), // "on_PB_showRois_clicked"
QT_MOC_LITERAL(20, 348, 23), // "on_ROI_list_itemClicked"
QT_MOC_LITERAL(21, 372, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(22, 389, 4), // "item"
QT_MOC_LITERAL(23, 394, 10), // "delete_roi"
QT_MOC_LITERAL(24, 405, 14), // "memory_dealloc"
QT_MOC_LITERAL(25, 420, 23), // "on_PB_renameRoi_pressed"
QT_MOC_LITERAL(26, 444, 29), // "on_ROI_list_itemDoubleClicked"
QT_MOC_LITERAL(27, 474, 17), // "OnItemsCommitData"
QT_MOC_LITERAL(28, 492, 8), // "QWidget*"
QT_MOC_LITERAL(29, 501, 9), // "pLineEdit"
QT_MOC_LITERAL(30, 511, 14), // "ROI_statistics"
QT_MOC_LITERAL(31, 526, 29), // "std::tuple<float,float,float>"
QT_MOC_LITERAL(32, 556, 6), // "points"
QT_MOC_LITERAL(33, 563, 5), // "image"
QT_MOC_LITERAL(34, 569, 21), // "on_PB_measure_pressed"
QT_MOC_LITERAL(35, 591, 11), // "closeDialog"
QT_MOC_LITERAL(36, 603, 8), // "plotROIS"
QT_MOC_LITERAL(37, 612, 18), // "set_reference_area"
QT_MOC_LITERAL(38, 631, 13), // "multi_measure"
QT_MOC_LITERAL(39, 645, 15), // "color_generator"
QT_MOC_LITERAL(40, 661, 1), // "h"
QT_MOC_LITERAL(41, 663, 1), // "s"
QT_MOC_LITERAL(42, 665, 1), // "v"
QT_MOC_LITERAL(43, 667, 26), // "randomCurveSymbolGenerator"
QT_MOC_LITERAL(44, 694, 10), // "QwtSymbol*"
QT_MOC_LITERAL(45, 705, 11), // "saveImageAs"
QT_MOC_LITERAL(46, 717, 3), // "str"
QT_MOC_LITERAL(47, 721, 13), // "saveAllFrames"
QT_MOC_LITERAL(48, 735, 15), // "savePlotAsImage"
QT_MOC_LITERAL(49, 751, 8), // "clearAll"
QT_MOC_LITERAL(50, 760, 23), // "on_PB_updatePos_pressed"
QT_MOC_LITERAL(51, 784, 24), // "on_PB_plot_excel_pressed"
QT_MOC_LITERAL(52, 809, 26), // "on_PB_saveSelected_clicked"
QT_MOC_LITERAL(53, 836, 11), // "on_PB_merge"
QT_MOC_LITERAL(54, 848, 15), // "on_PB_pdfReport"
QT_MOC_LITERAL(55, 864, 23), // "on_cB_selection_toggled"
QT_MOC_LITERAL(56, 888, 7), // "checked"
QT_MOC_LITERAL(57, 896, 22), // "PB_saveAsDICOM_pressed"
QT_MOC_LITERAL(58, 919, 20), // "actionExit_triggered"
QT_MOC_LITERAL(59, 940, 36), // "on_actionExit_to_Main_Menu_tr..."
QT_MOC_LITERAL(60, 977, 25), // "on_PB_dicomViewer_clicked"
QT_MOC_LITERAL(61, 1003, 12), // "on_cB_fusion"
QT_MOC_LITERAL(62, 1016, 10), // "on_cB_xray"
QT_MOC_LITERAL(63, 1027, 17), // "setCheckstateXray"
QT_MOC_LITERAL(64, 1045, 20), // "setCheckstateOptical"
QT_MOC_LITERAL(65, 1066, 24), // "ms_sliderValueChangedMin"
QT_MOC_LITERAL(66, 1091, 14), // "sB_max_changed"
QT_MOC_LITERAL(67, 1106, 14), // "sB_min_changed"
QT_MOC_LITERAL(68, 1121, 16), // "removeBackground"
QT_MOC_LITERAL(69, 1138, 17), // "addXrayBackground"
QT_MOC_LITERAL(70, 1156, 20), // "addOpticalBackground"
QT_MOC_LITERAL(71, 1177, 19) // "opacityValueChanged"

    },
    "PostProcessing\0closedWindow\0\0"
    "directFileLoader\0ImageSlider\0"
    "combobox_currentIndexChanged\0Init\0"
    "sliderValueChanged\0LoadStudy_triggered\0"
    "selectActivityPerROI\0selectCountsPerROI\0"
    "loadLastStudy\0on_pb_rectROI_clicked\0"
    "on_pb_ellipseROI_clicked\0on_pb_freeROI_clicked\0"
    "on_PB_ShowLabels_toggled\0ShowContextMenu\0"
    "ShowContextMenu2\0addROItoList\0"
    "on_PB_showRois_clicked\0on_ROI_list_itemClicked\0"
    "QListWidgetItem*\0item\0delete_roi\0"
    "memory_dealloc\0on_PB_renameRoi_pressed\0"
    "on_ROI_list_itemDoubleClicked\0"
    "OnItemsCommitData\0QWidget*\0pLineEdit\0"
    "ROI_statistics\0std::tuple<float,float,float>\0"
    "points\0image\0on_PB_measure_pressed\0"
    "closeDialog\0plotROIS\0set_reference_area\0"
    "multi_measure\0color_generator\0h\0s\0v\0"
    "randomCurveSymbolGenerator\0QwtSymbol*\0"
    "saveImageAs\0str\0saveAllFrames\0"
    "savePlotAsImage\0clearAll\0"
    "on_PB_updatePos_pressed\0"
    "on_PB_plot_excel_pressed\0"
    "on_PB_saveSelected_clicked\0on_PB_merge\0"
    "on_PB_pdfReport\0on_cB_selection_toggled\0"
    "checked\0PB_saveAsDICOM_pressed\0"
    "actionExit_triggered\0"
    "on_actionExit_to_Main_Menu_triggered\0"
    "on_PB_dicomViewer_clicked\0on_cB_fusion\0"
    "on_cB_xray\0setCheckstateXray\0"
    "setCheckstateOptical\0ms_sliderValueChangedMin\0"
    "sB_max_changed\0sB_min_changed\0"
    "removeBackground\0addXrayBackground\0"
    "addOpticalBackground\0opacityValueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PostProcessing[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      60,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  314,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,  315,    2, 0x0a /* Public */,
       4,    1,  318,    2, 0x0a /* Public */,
       5,    1,  321,    2, 0x0a /* Public */,
       6,    1,  324,    2, 0x0a /* Public */,
       7,    1,  327,    2, 0x0a /* Public */,
       8,    0,  330,    2, 0x0a /* Public */,
       9,    1,  331,    2, 0x0a /* Public */,
      10,    1,  334,    2, 0x0a /* Public */,
      11,    0,  337,    2, 0x0a /* Public */,
      12,    1,  338,    2, 0x08 /* Private */,
      13,    1,  341,    2, 0x08 /* Private */,
      14,    1,  344,    2, 0x08 /* Private */,
      15,    1,  347,    2, 0x08 /* Private */,
      16,    1,  350,    2, 0x08 /* Private */,
      17,    1,  353,    2, 0x08 /* Private */,
      18,    0,  356,    2, 0x08 /* Private */,
      19,    1,  357,    2, 0x08 /* Private */,
      20,    1,  360,    2, 0x08 /* Private */,
      23,    0,  363,    2, 0x08 /* Private */,
      24,    0,  364,    2, 0x08 /* Private */,
      25,    0,  365,    2, 0x08 /* Private */,
      26,    1,  366,    2, 0x08 /* Private */,
      27,    1,  369,    2, 0x08 /* Private */,
      30,    2,  372,    2, 0x08 /* Private */,
      30,    2,  377,    2, 0x08 /* Private */,
      34,    0,  382,    2, 0x08 /* Private */,
      35,    1,  383,    2, 0x08 /* Private */,
      36,    0,  386,    2, 0x08 /* Private */,
      37,    0,  387,    2, 0x08 /* Private */,
      38,    0,  388,    2, 0x08 /* Private */,
      39,    3,  389,    2, 0x08 /* Private */,
      43,    0,  396,    2, 0x08 /* Private */,
      45,    0,  397,    2, 0x08 /* Private */,
      45,    1,  398,    2, 0x08 /* Private */,
      47,    0,  401,    2, 0x08 /* Private */,
      48,    0,  402,    2, 0x08 /* Private */,
      48,    1,  403,    2, 0x08 /* Private */,
      49,    0,  406,    2, 0x08 /* Private */,
      50,    0,  407,    2, 0x08 /* Private */,
      51,    0,  408,    2, 0x08 /* Private */,
      52,    0,  409,    2, 0x08 /* Private */,
      53,    0,  410,    2, 0x08 /* Private */,
      54,    0,  411,    2, 0x08 /* Private */,
      55,    1,  412,    2, 0x08 /* Private */,
      57,    1,  415,    2, 0x08 /* Private */,
      58,    0,  418,    2, 0x08 /* Private */,
      59,    0,  419,    2, 0x08 /* Private */,
      60,    0,  420,    2, 0x08 /* Private */,
      61,    1,  421,    2, 0x08 /* Private */,
      62,    1,  424,    2, 0x08 /* Private */,
      63,    0,  427,    2, 0x08 /* Private */,
      64,    0,  428,    2, 0x08 /* Private */,
      65,    1,  429,    2, 0x08 /* Private */,
      66,    1,  432,    2, 0x08 /* Private */,
      67,    1,  435,    2, 0x08 /* Private */,
      68,    0,  438,    2, 0x08 /* Private */,
      69,    0,  439,    2, 0x08 /* Private */,
      70,    0,  440,    2, 0x08 /* Private */,
      71,    1,  441,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 28,   29,
    0x80000000 | 31, QMetaType::QPolygonF, QMetaType::Int,   32,   33,
    0x80000000 | 31, QMetaType::QRectF, QMetaType::Int,    2,   33,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   40,   41,   42,
    0x80000000 | 44,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   46,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   56,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   56,
    QMetaType::Void, QMetaType::Bool,   56,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void PostProcessing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PostProcessing *_t = static_cast<PostProcessing *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closedWindow(); break;
        case 1: _t->directFileLoader((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ImageSlider((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->combobox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->Init((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->sliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->LoadStudy_triggered(); break;
        case 7: _t->selectActivityPerROI((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->selectCountsPerROI((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->loadLastStudy(); break;
        case 10: _t->on_pb_rectROI_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_pb_ellipseROI_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_pb_freeROI_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_PB_ShowLabels_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->ShowContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 15: _t->ShowContextMenu2((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 16: _t->addROItoList(); break;
        case 17: _t->on_PB_showRois_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->on_ROI_list_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 19: _t->delete_roi(); break;
        case 20: _t->memory_dealloc(); break;
        case 21: _t->on_PB_renameRoi_pressed(); break;
        case 22: _t->on_ROI_list_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 23: _t->OnItemsCommitData((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 24: { std::tuple<float,float,float> _r = _t->ROI_statistics((*reinterpret_cast< QPolygonF(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< std::tuple<float,float,float>*>(_a[0]) = std::move(_r); }  break;
        case 25: { std::tuple<float,float,float> _r = _t->ROI_statistics((*reinterpret_cast< QRectF(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< std::tuple<float,float,float>*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->on_PB_measure_pressed(); break;
        case 27: _t->closeDialog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->plotROIS(); break;
        case 29: { float _r = _t->set_reference_area();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 30: _t->multi_measure(); break;
        case 31: _t->color_generator((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 32: { QwtSymbol* _r = _t->randomCurveSymbolGenerator();
            if (_a[0]) *reinterpret_cast< QwtSymbol**>(_a[0]) = std::move(_r); }  break;
        case 33: _t->saveImageAs(); break;
        case 34: _t->saveImageAs((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 35: _t->saveAllFrames(); break;
        case 36: _t->savePlotAsImage(); break;
        case 37: _t->savePlotAsImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 38: _t->clearAll(); break;
        case 39: _t->on_PB_updatePos_pressed(); break;
        case 40: _t->on_PB_plot_excel_pressed(); break;
        case 41: _t->on_PB_saveSelected_clicked(); break;
        case 42: _t->on_PB_merge(); break;
        case 43: _t->on_PB_pdfReport(); break;
        case 44: _t->on_cB_selection_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 45: _t->PB_saveAsDICOM_pressed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 46: _t->actionExit_triggered(); break;
        case 47: _t->on_actionExit_to_Main_Menu_triggered(); break;
        case 48: _t->on_PB_dicomViewer_clicked(); break;
        case 49: _t->on_cB_fusion((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 50: _t->on_cB_xray((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 51: _t->setCheckstateXray(); break;
        case 52: _t->setCheckstateOptical(); break;
        case 53: _t->ms_sliderValueChangedMin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 54: _t->sB_max_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 55: _t->sB_min_changed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 56: _t->removeBackground(); break;
        case 57: _t->addXrayBackground(); break;
        case 58: _t->addOpticalBackground(); break;
        case 59: _t->opacityValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PostProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PostProcessing::closedWindow)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PostProcessing::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PostProcessing.data,
      qt_meta_data_PostProcessing,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PostProcessing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PostProcessing::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PostProcessing.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PostProcessing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 60)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 60;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 60)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 60;
    }
    return _id;
}

// SIGNAL 0
void PostProcessing::closedWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
