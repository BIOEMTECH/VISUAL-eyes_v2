/********************************************************************************
** Form generated from reading UI file 'gamma_eye.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMMA_EYE_H
#define UI_GAMMA_EYE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gamma_eye
{
public:
    QAction *actionNew_Study;
    QAction *actionGo_back_to_main_menu;
    QAction *actionInsert_Bed;
    QAction *actionEject_Bed;
    QAction *actionCalibrate_Bed_Position;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *active_tab;
    QFrame *frameSummed;
    QWidget *layoutWidget;
    QHBoxLayout *summed;
    QLabel *label_82;
    QLabel *label_83;
    QLabel *label_84;
    QLabel *label_85;
    QLineEdit *LE_currFrame;
    QProgressBar *frame_progress;
    QLabel *label;
    QLabel *label_2;
    QCheckBox *cb_fusion;
    QFrame *frameCorr;
    QWidget *layoutWidget1;
    QHBoxLayout *corrected;
    QGroupBox *groupBox_5;
    QPushButton *PB_eject;
    QLabel *label_141;
    QLabel *label_142;
    QCommandLinkButton *PB_stopDAQ;
    QLabel *LE_finishTime;
    QLabel *LE_startTime;
    QCommandLinkButton *PB_startDAQ;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QLabel *label_143;
    QLabel *label_145;
    QLabel *opacityLabel;
    QLabel *label_144;
    QSlider *horizontalSlider;
    QComboBox *cb_colormap;
    QSlider *hsContrastB;
    QSlider *opacitySlider;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_2;
    QLabel *TL_animalID;
    QLabel *label_138;
    QLabel *label_21;
    QLabel *LE_frameRate;
    QLabel *label_136;
    QLabel *TL_studyID;
    QLabel *TL_project;
    QLabel *label_22;
    QLabel *label_140;
    QLabel *TL_studyName;
    QLabel *LE_duration;
    QLabel *label_139;
    QLabel *label_137;
    QLabel *LE_radioNuclide;
    QLabel *label_23;
    QLabel *LE_injectActivity;
    QCheckBox *cb_xray;
    QWidget *proc_tab_2;
    QLabel *label_86;
    QLabel *label_87;
    QFrame *frame;
    QGridLayout *gridLayout_37;
    QVBoxLayout *Energy_Spectrum;
    QFrame *Ra;
    QGridLayout *gridLayout_38;
    QHBoxLayout *Raw;
    QLabel *LE_counts;
    QWidget *tab;
    QGroupBox *validationStatus;
    QLabel *lb_status;
    QLabel *statusIcon;
    QGroupBox *detectorElements;
    QWidget *layoutWidget3;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLabel *lb_detElemHead;
    QLabel *label_8;
    QGroupBox *energyResolution;
    QWidget *layoutWidget_3;
    QFormLayout *formLayout_3;
    QLabel *lb_resolution;
    QLabel *lb_cfov;
    QWidget *layoutWidget_5;
    QHBoxLayout *correctedHead_layout;
    QWidget *layoutWidget4;
    QFormLayout *formLayout;
    QLabel *label_15;
    QProgressBar *daq_progress;
    QMenuBar *menubar;
    QMenu *menu_Eye;
    QMenu *menuMouse_Bed_Controls;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gamma_eye)
    {
        if (gamma_eye->objectName().isEmpty())
            gamma_eye->setObjectName(QStringLiteral("gamma_eye"));
        gamma_eye->resize(1270, 730);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gamma_eye->sizePolicy().hasHeightForWidth());
        gamma_eye->setSizePolicy(sizePolicy);
        gamma_eye->setMinimumSize(QSize(1270, 730));
        gamma_eye->setMaximumSize(QSize(1270, 730));
        QFont font;
        font.setPointSize(10);
        gamma_eye->setFont(font);
        actionNew_Study = new QAction(gamma_eye);
        actionNew_Study->setObjectName(QStringLiteral("actionNew_Study"));
        actionNew_Study->setShortcutContext(Qt::ApplicationShortcut);
        actionNew_Study->setMenuRole(QAction::ApplicationSpecificRole);
        actionNew_Study->setPriority(QAction::HighPriority);
        actionGo_back_to_main_menu = new QAction(gamma_eye);
        actionGo_back_to_main_menu->setObjectName(QStringLiteral("actionGo_back_to_main_menu"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/if_Back_32435.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGo_back_to_main_menu->setIcon(icon);
        actionInsert_Bed = new QAction(gamma_eye);
        actionInsert_Bed->setObjectName(QStringLiteral("actionInsert_Bed"));
        actionInsert_Bed->setShortcutContext(Qt::ApplicationShortcut);
        actionInsert_Bed->setMenuRole(QAction::ApplicationSpecificRole);
        actionInsert_Bed->setPriority(QAction::HighPriority);
        actionEject_Bed = new QAction(gamma_eye);
        actionEject_Bed->setObjectName(QStringLiteral("actionEject_Bed"));
        actionCalibrate_Bed_Position = new QAction(gamma_eye);
        actionCalibrate_Bed_Position->setObjectName(QStringLiteral("actionCalibrate_Bed_Position"));
        centralwidget = new QWidget(gamma_eye);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(9, 18, 1250, 631));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(1250, 621));
        tabWidget->setMaximumSize(QSize(1250, 700));
        QFont font1;
        font1.setFamily(QStringLiteral("FreeSans"));
        tabWidget->setFont(font1);
        active_tab = new QWidget();
        active_tab->setObjectName(QStringLiteral("active_tab"));
        frameSummed = new QFrame(active_tab);
        frameSummed->setObjectName(QStringLiteral("frameSummed"));
        frameSummed->setGeometry(QRect(654, 40, 580, 290));
        frameSummed->setFrameShape(QFrame::StyledPanel);
        frameSummed->setFrameShadow(QFrame::Raised);
        layoutWidget = new QWidget(frameSummed);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 581, 291));
        summed = new QHBoxLayout(layoutWidget);
        summed->setObjectName(QStringLiteral("summed"));
        summed->setContentsMargins(0, 0, 0, 0);
        label_82 = new QLabel(active_tab);
        label_82->setObjectName(QStringLiteral("label_82"));
        label_82->setGeometry(QRect(30, 340, 131, 17));
        label_83 = new QLabel(active_tab);
        label_83->setObjectName(QStringLiteral("label_83"));
        label_83->setGeometry(QRect(30, 10, 181, 17));
        label_84 = new QLabel(active_tab);
        label_84->setObjectName(QStringLiteral("label_84"));
        label_84->setGeometry(QRect(654, 341, 91, 20));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_84->sizePolicy().hasHeightForWidth());
        label_84->setSizePolicy(sizePolicy1);
        label_85 = new QLabel(active_tab);
        label_85->setObjectName(QStringLiteral("label_85"));
        label_85->setGeometry(QRect(650, 10, 591, 17));
        sizePolicy.setHeightForWidth(label_85->sizePolicy().hasHeightForWidth());
        label_85->setSizePolicy(sizePolicy);
        LE_currFrame = new QLineEdit(active_tab);
        LE_currFrame->setObjectName(QStringLiteral("LE_currFrame"));
        LE_currFrame->setGeometry(QRect(652, 364, 101, 21));
        LE_currFrame->setReadOnly(true);
        frame_progress = new QProgressBar(active_tab);
        frame_progress->setObjectName(QStringLiteral("frame_progress"));
        frame_progress->setGeometry(QRect(30, 360, 581, 25));
        frame_progress->setValue(0);
        label = new QLabel(active_tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(616, 301, 31, 31));
        label->setFrameShape(QFrame::NoFrame);
        label->setPixmap(QPixmap(QString::fromUtf8(":/icons/letter-l-48.png")));
        label_2 = new QLabel(active_tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(615, 40, 31, 31));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/icons/letter-r-48.png")));
        cb_fusion = new QCheckBox(active_tab);
        cb_fusion->setObjectName(QStringLiteral("cb_fusion"));
        cb_fusion->setGeometry(QRect(400, 10, 111, 20));
        frameCorr = new QFrame(active_tab);
        frameCorr->setObjectName(QStringLiteral("frameCorr"));
        frameCorr->setGeometry(QRect(30, 40, 580, 290));
        frameCorr->setFrameShape(QFrame::StyledPanel);
        frameCorr->setFrameShadow(QFrame::Raised);
        layoutWidget1 = new QWidget(frameCorr);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 581, 291));
        corrected = new QHBoxLayout(layoutWidget1);
        corrected->setObjectName(QStringLiteral("corrected"));
        corrected->setContentsMargins(0, 0, 0, 0);
        groupBox_5 = new QGroupBox(active_tab);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(30, 420, 581, 171));
        PB_eject = new QPushButton(groupBox_5);
        PB_eject->setObjectName(QStringLiteral("PB_eject"));
        PB_eject->setGeometry(QRect(491, 60, 71, 71));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/Eject button.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral(":/icons/Disable Eject button.png"), QSize(), QIcon::Disabled, QIcon::Off);
        PB_eject->setIcon(icon1);
        PB_eject->setIconSize(QSize(60, 60));
        label_141 = new QLabel(groupBox_5);
        label_141->setObjectName(QStringLiteral("label_141"));
        label_141->setGeometry(QRect(13, 51, 70, 16));
        label_142 = new QLabel(groupBox_5);
        label_142->setObjectName(QStringLiteral("label_142"));
        label_142->setGeometry(QRect(13, 30, 65, 16));
        PB_stopDAQ = new QCommandLinkButton(groupBox_5);
        PB_stopDAQ->setObjectName(QStringLiteral("PB_stopDAQ"));
        PB_stopDAQ->setEnabled(true);
        PB_stopDAQ->setGeometry(QRect(413, 60, 61, 61));
        QFont font2;
        font2.setFamily(QStringLiteral("FreeSerif"));
        PB_stopDAQ->setFont(font2);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/Stop button.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QStringLiteral(":/icons/Disable Stop button.png"), QSize(), QIcon::Disabled, QIcon::Off);
        PB_stopDAQ->setIcon(icon2);
        PB_stopDAQ->setIconSize(QSize(50, 50));
        LE_finishTime = new QLabel(groupBox_5);
        LE_finishTime->setObjectName(QStringLiteral("LE_finishTime"));
        LE_finishTime->setGeometry(QRect(89, 51, 221, 16));
        LE_startTime = new QLabel(groupBox_5);
        LE_startTime->setObjectName(QStringLiteral("LE_startTime"));
        LE_startTime->setGeometry(QRect(89, 30, 16, 16));
        PB_startDAQ = new QCommandLinkButton(groupBox_5);
        PB_startDAQ->setObjectName(QStringLiteral("PB_startDAQ"));
        PB_startDAQ->setEnabled(true);
        PB_startDAQ->setGeometry(QRect(332, 60, 61, 61));
        PB_startDAQ->setFont(font1);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/Play button.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QStringLiteral(":/icons/Disable Play button.png"), QSize(), QIcon::Disabled, QIcon::Off);
        PB_startDAQ->setIcon(icon3);
        PB_startDAQ->setIconSize(QSize(50, 50));
        layoutWidget2 = new QWidget(groupBox_5);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(15, 74, 127, 91));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_143 = new QLabel(layoutWidget2);
        label_143->setObjectName(QStringLiteral("label_143"));

        verticalLayout->addWidget(label_143);

        label_145 = new QLabel(layoutWidget2);
        label_145->setObjectName(QStringLiteral("label_145"));

        verticalLayout->addWidget(label_145);

        opacityLabel = new QLabel(layoutWidget2);
        opacityLabel->setObjectName(QStringLiteral("opacityLabel"));

        verticalLayout->addWidget(opacityLabel);

        label_144 = new QLabel(layoutWidget2);
        label_144->setObjectName(QStringLiteral("label_144"));

        verticalLayout->addWidget(label_144);

        horizontalSlider = new QSlider(groupBox_5);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(111, 80, 191, 16));
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedAppearance(false);
        horizontalSlider->setInvertedControls(false);
        cb_colormap = new QComboBox(groupBox_5);
        cb_colormap->addItem(QString());
        cb_colormap->addItem(QString());
        cb_colormap->addItem(QString());
        cb_colormap->addItem(QString());
        cb_colormap->addItem(QString());
        cb_colormap->setObjectName(QStringLiteral("cb_colormap"));
        cb_colormap->setGeometry(QRect(111, 140, 111, 23));
        hsContrastB = new QSlider(groupBox_5);
        hsContrastB->setObjectName(QStringLiteral("hsContrastB"));
        hsContrastB->setGeometry(QRect(111, 100, 191, 16));
        hsContrastB->setOrientation(Qt::Horizontal);
        hsContrastB->setInvertedAppearance(false);
        hsContrastB->setInvertedControls(false);
        opacitySlider = new QSlider(groupBox_5);
        opacitySlider->setObjectName(QStringLiteral("opacitySlider"));
        opacitySlider->setGeometry(QRect(111, 120, 191, 16));
        opacitySlider->setOrientation(Qt::Horizontal);
        groupBox_6 = new QGroupBox(active_tab);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(650, 420, 561, 161));
        gridLayout_2 = new QGridLayout(groupBox_6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        TL_animalID = new QLabel(groupBox_6);
        TL_animalID->setObjectName(QStringLiteral("TL_animalID"));

        gridLayout_2->addWidget(TL_animalID, 2, 1, 1, 1);

        label_138 = new QLabel(groupBox_6);
        label_138->setObjectName(QStringLiteral("label_138"));

        gridLayout_2->addWidget(label_138, 1, 0, 1, 1);

        label_21 = new QLabel(groupBox_6);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout_2->addWidget(label_21, 1, 2, 1, 1);

        LE_frameRate = new QLabel(groupBox_6);
        LE_frameRate->setObjectName(QStringLiteral("LE_frameRate"));

        gridLayout_2->addWidget(LE_frameRate, 1, 3, 1, 1);

        label_136 = new QLabel(groupBox_6);
        label_136->setObjectName(QStringLiteral("label_136"));

        gridLayout_2->addWidget(label_136, 0, 0, 1, 1);

        TL_studyID = new QLabel(groupBox_6);
        TL_studyID->setObjectName(QStringLiteral("TL_studyID"));

        gridLayout_2->addWidget(TL_studyID, 0, 1, 1, 1);

        TL_project = new QLabel(groupBox_6);
        TL_project->setObjectName(QStringLiteral("TL_project"));

        gridLayout_2->addWidget(TL_project, 3, 1, 1, 1);

        label_22 = new QLabel(groupBox_6);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout_2->addWidget(label_22, 2, 2, 1, 1);

        label_140 = new QLabel(groupBox_6);
        label_140->setObjectName(QStringLiteral("label_140"));

        gridLayout_2->addWidget(label_140, 3, 0, 1, 1);

        TL_studyName = new QLabel(groupBox_6);
        TL_studyName->setObjectName(QStringLiteral("TL_studyName"));

        gridLayout_2->addWidget(TL_studyName, 1, 1, 1, 1);

        LE_duration = new QLabel(groupBox_6);
        LE_duration->setObjectName(QStringLiteral("LE_duration"));

        gridLayout_2->addWidget(LE_duration, 0, 3, 1, 1);

        label_139 = new QLabel(groupBox_6);
        label_139->setObjectName(QStringLiteral("label_139"));

        gridLayout_2->addWidget(label_139, 2, 0, 1, 1);

        label_137 = new QLabel(groupBox_6);
        label_137->setObjectName(QStringLiteral("label_137"));

        gridLayout_2->addWidget(label_137, 0, 2, 1, 1);

        LE_radioNuclide = new QLabel(groupBox_6);
        LE_radioNuclide->setObjectName(QStringLiteral("LE_radioNuclide"));

        gridLayout_2->addWidget(LE_radioNuclide, 2, 3, 1, 1);

        label_23 = new QLabel(groupBox_6);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_2->addWidget(label_23, 3, 2, 1, 1);

        LE_injectActivity = new QLabel(groupBox_6);
        LE_injectActivity->setObjectName(QStringLiteral("LE_injectActivity"));

        gridLayout_2->addWidget(LE_injectActivity, 3, 3, 1, 1);

        cb_xray = new QCheckBox(active_tab);
        cb_xray->setObjectName(QStringLiteral("cb_xray"));
        cb_xray->setGeometry(QRect(520, 10, 91, 20));
        tabWidget->addTab(active_tab, QString());
        proc_tab_2 = new QWidget();
        proc_tab_2->setObjectName(QStringLiteral("proc_tab_2"));
        label_86 = new QLabel(proc_tab_2);
        label_86->setObjectName(QStringLiteral("label_86"));
        label_86->setGeometry(QRect(20, 30, 241, 17));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_86->sizePolicy().hasHeightForWidth());
        label_86->setSizePolicy(sizePolicy2);
        label_87 = new QLabel(proc_tab_2);
        label_87->setObjectName(QStringLiteral("label_87"));
        label_87->setGeometry(QRect(583, 30, 101, 17));
        sizePolicy1.setHeightForWidth(label_87->sizePolicy().hasHeightForWidth());
        label_87->setSizePolicy(sizePolicy1);
        frame = new QFrame(proc_tab_2);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(20, 53, 450, 300));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_37 = new QGridLayout(frame);
        gridLayout_37->setObjectName(QStringLiteral("gridLayout_37"));
        Energy_Spectrum = new QVBoxLayout();
        Energy_Spectrum->setObjectName(QStringLiteral("Energy_Spectrum"));

        gridLayout_37->addLayout(Energy_Spectrum, 0, 0, 1, 1);

        Ra = new QFrame(proc_tab_2);
        Ra->setObjectName(QStringLiteral("Ra"));
        Ra->setGeometry(QRect(583, 53, 600, 300));
        Ra->setFrameShape(QFrame::StyledPanel);
        Ra->setFrameShadow(QFrame::Raised);
        gridLayout_38 = new QGridLayout(Ra);
        gridLayout_38->setObjectName(QStringLiteral("gridLayout_38"));
        Raw = new QHBoxLayout();
        Raw->setObjectName(QStringLiteral("Raw"));

        gridLayout_38->addLayout(Raw, 0, 0, 1, 1);

        LE_counts = new QLabel(proc_tab_2);
        LE_counts->setObjectName(QStringLiteral("LE_counts"));
        LE_counts->setGeometry(QRect(9, 346, 16, 18));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(LE_counts->sizePolicy().hasHeightForWidth());
        LE_counts->setSizePolicy(sizePolicy3);
        tabWidget->addTab(proc_tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        validationStatus = new QGroupBox(tab);
        validationStatus->setObjectName(QStringLiteral("validationStatus"));
        validationStatus->setGeometry(QRect(720, 260, 191, 141));
        lb_status = new QLabel(validationStatus);
        lb_status->setObjectName(QStringLiteral("lb_status"));
        lb_status->setGeometry(QRect(60, 30, 81, 16));
        statusIcon = new QLabel(validationStatus);
        statusIcon->setObjectName(QStringLiteral("statusIcon"));
        statusIcon->setGeometry(QRect(60, 49, 85, 85));
        detectorElements = new QGroupBox(tab);
        detectorElements->setObjectName(QStringLiteral("detectorElements"));
        detectorElements->setGeometry(QRect(720, 80, 321, 61));
        layoutWidget3 = new QWidget(detectorElements);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(11, 31, 231, 21));
        formLayout_2 = new QFormLayout(layoutWidget3);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget3);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        lb_detElemHead = new QLabel(layoutWidget3);
        lb_detElemHead->setObjectName(QStringLiteral("lb_detElemHead"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lb_detElemHead);

        label_8 = new QLabel(tab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(130, 20, 141, 17));
        energyResolution = new QGroupBox(tab);
        energyResolution->setObjectName(QStringLiteral("energyResolution"));
        energyResolution->setGeometry(QRect(720, 170, 321, 61));
        layoutWidget_3 = new QWidget(energyResolution);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(12, 32, 281, 20));
        formLayout_3 = new QFormLayout(layoutWidget_3);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        lb_resolution = new QLabel(layoutWidget_3);
        lb_resolution->setObjectName(QStringLiteral("lb_resolution"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, lb_resolution);

        lb_cfov = new QLabel(layoutWidget_3);
        lb_cfov->setObjectName(QStringLiteral("lb_cfov"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, lb_cfov);

        layoutWidget_5 = new QWidget(tab);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(120, 40, 421, 461));
        correctedHead_layout = new QHBoxLayout(layoutWidget_5);
        correctedHead_layout->setObjectName(QStringLiteral("correctedHead_layout"));
        correctedHead_layout->setContentsMargins(0, 0, 0, 0);
        tabWidget->addTab(tab, QString());
        layoutWidget4 = new QWidget(centralwidget);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(9, 660, 1251, 27));
        formLayout = new QFormLayout(layoutWidget4);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(layoutWidget4);
        label_15->setObjectName(QStringLiteral("label_15"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_15);

        daq_progress = new QProgressBar(layoutWidget4);
        daq_progress->setObjectName(QStringLiteral("daq_progress"));
        daq_progress->setValue(0);

        formLayout->setWidget(0, QFormLayout::FieldRole, daq_progress);

        gamma_eye->setCentralWidget(centralwidget);
        menubar = new QMenuBar(gamma_eye);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1270, 22));
        menu_Eye = new QMenu(menubar);
        menu_Eye->setObjectName(QStringLiteral("menu_Eye"));
        menuMouse_Bed_Controls = new QMenu(menubar);
        menuMouse_Bed_Controls->setObjectName(QStringLiteral("menuMouse_Bed_Controls"));
        gamma_eye->setMenuBar(menubar);
        statusbar = new QStatusBar(gamma_eye);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        gamma_eye->setStatusBar(statusbar);

        menubar->addAction(menu_Eye->menuAction());
        menubar->addAction(menuMouse_Bed_Controls->menuAction());
        menu_Eye->addAction(actionGo_back_to_main_menu);
        menuMouse_Bed_Controls->addAction(actionInsert_Bed);
        menuMouse_Bed_Controls->addAction(actionEject_Bed);
        menuMouse_Bed_Controls->addAction(actionCalibrate_Bed_Position);

        retranslateUi(gamma_eye);

        tabWidget->setCurrentIndex(0);
        cb_colormap->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(gamma_eye);
    } // setupUi

    void retranslateUi(QMainWindow *gamma_eye)
    {
        gamma_eye->setWindowTitle(QApplication::translate("gamma_eye", "MainWindow", nullptr));
        actionNew_Study->setText(QApplication::translate("gamma_eye", "New Study", nullptr));
        actionGo_back_to_main_menu->setText(QApplication::translate("gamma_eye", "Exit to main menu..", nullptr));
        actionInsert_Bed->setText(QApplication::translate("gamma_eye", "Insert bed", nullptr));
        actionEject_Bed->setText(QApplication::translate("gamma_eye", "Eject bed", nullptr));
        actionCalibrate_Bed_Position->setText(QApplication::translate("gamma_eye", "Calibrate bed position", nullptr));
#ifndef QT_NO_TOOLTIP
        frameSummed->setToolTip(QApplication::translate("gamma_eye", "<html><head/><body><p>The sum of all frames. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_82->setText(QApplication::translate("gamma_eye", "Frame progress", nullptr));
        label_83->setText(QApplication::translate("gamma_eye", "Live  image", nullptr));
        label_84->setText(QApplication::translate("gamma_eye", "Current frame", nullptr));
        label_85->setText(QApplication::translate("gamma_eye", "Summed image", nullptr));
#ifndef QT_NO_TOOLTIP
        LE_currFrame->setToolTip(QApplication::translate("gamma_eye", "<html><head/><body><p>Shows the number of the current frame appearing in the &quot;Live image&quot;. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label->setText(QString());
        label_2->setText(QString());
#ifndef QT_NO_TOOLTIP
        cb_fusion->setToolTip(QApplication::translate("gamma_eye", "<html><head/><body><p>Tick to fuse nuclear and optical images. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        cb_fusion->setText(QApplication::translate("gamma_eye", " Optical fusion", nullptr));
#ifndef QT_NO_TOOLTIP
        frameCorr->setToolTip(QApplication::translate("gamma_eye", "<html><head/><body><p>Live image. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        groupBox_5->setToolTip(QApplication::translate("gamma_eye", "<html><head/><body><p>The controls for the experiment and the nuclear imaging. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        groupBox_5->setTitle(QApplication::translate("gamma_eye", "Controls", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_eject->setToolTip(QApplication::translate("gamma_eye", "<html><head/><body><p>Press to eject the bed. If pressed during an experiment, the experiment will be terminated. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_eject->setText(QString());
        label_141->setText(QApplication::translate("gamma_eye", "Finish time:", nullptr));
        label_142->setText(QApplication::translate("gamma_eye", "Start time:", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_stopDAQ->setToolTip(QApplication::translate("gamma_eye", "<html><head/><body><p>Press to stop the experiment. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_stopDAQ->setText(QString());
        LE_finishTime->setText(QString());
        LE_startTime->setText(QString());
#ifndef QT_NO_TOOLTIP
        PB_startDAQ->setToolTip(QApplication::translate("gamma_eye", "<html><head/><body><p>Press to start the experiment. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_startDAQ->setText(QString());
        label_143->setText(QApplication::translate("gamma_eye", "Contrast (Live):", nullptr));
        label_145->setText(QApplication::translate("gamma_eye", "Contrast (Sum.):", nullptr));
        opacityLabel->setText(QApplication::translate("gamma_eye", "Opacity:", nullptr));
        label_144->setText(QApplication::translate("gamma_eye", "Color map:", nullptr));
        cb_colormap->setItemText(0, QApplication::translate("gamma_eye", "GrayScale", nullptr));
        cb_colormap->setItemText(1, QApplication::translate("gamma_eye", "Royal", nullptr));
        cb_colormap->setItemText(2, QApplication::translate("gamma_eye", "Jet", nullptr));
        cb_colormap->setItemText(3, QApplication::translate("gamma_eye", "Red Hot", nullptr));
        cb_colormap->setItemText(4, QApplication::translate("gamma_eye", "Smart", nullptr));

#ifndef QT_NO_TOOLTIP
        groupBox_6->setToolTip(QApplication::translate("gamma_eye", "<html><head/><body><p>General info about the experiment as these were inserted in the &quot;Details window&quot;. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        groupBox_6->setTitle(QApplication::translate("gamma_eye", "Info", nullptr));
        TL_animalID->setText(QString());
        label_138->setText(QApplication::translate("gamma_eye", "Study name:", nullptr));
        label_21->setText(QApplication::translate("gamma_eye", "Frame per:", nullptr));
        LE_frameRate->setText(QString());
        label_136->setText(QApplication::translate("gamma_eye", "Study ID:", nullptr));
        TL_studyID->setText(QString());
        TL_project->setText(QString());
        label_22->setText(QApplication::translate("gamma_eye", "Radionuclide:", nullptr));
        label_140->setText(QApplication::translate("gamma_eye", "Project:", nullptr));
        TL_studyName->setText(QString());
        LE_duration->setText(QString());
        label_139->setText(QApplication::translate("gamma_eye", "Animal ID:", nullptr));
        label_137->setText(QApplication::translate("gamma_eye", "Study duration:", nullptr));
        LE_radioNuclide->setText(QString());
        label_23->setText(QApplication::translate("gamma_eye", "Injected activity: ", nullptr));
        LE_injectActivity->setText(QString());
#ifndef QT_NO_TOOLTIP
        cb_xray->setToolTip(QApplication::translate("gamma_eye", "<html><head/><body><p>Tick to fuse nuclear and optical images. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        cb_xray->setText(QApplication::translate("gamma_eye", "Xray fusion", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(active_tab), QApplication::translate("gamma_eye", "Live acquisition", nullptr));
        label_86->setText(QApplication::translate("gamma_eye", "Energy spectrum (counts/KeV)", nullptr));
        label_87->setText(QApplication::translate("gamma_eye", "Raw data", nullptr));
        LE_counts->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(proc_tab_2), QApplication::translate("gamma_eye", "Raw imaging", nullptr));
        validationStatus->setTitle(QApplication::translate("gamma_eye", "Validation status", nullptr));
        lb_status->setText(QString());
        statusIcon->setText(QString());
        detectorElements->setTitle(QApplication::translate("gamma_eye", "Detector elements processed", nullptr));
        label_3->setText(QApplication::translate("gamma_eye", "Head :", nullptr));
        lb_detElemHead->setText(QString());
        label_8->setText(QApplication::translate("gamma_eye", "Corrected energy", nullptr));
        energyResolution->setTitle(QApplication::translate("gamma_eye", "Energy resolution", nullptr));
        lb_resolution->setText(QApplication::translate("gamma_eye", "CFOV:", nullptr));
        lb_cfov->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("gamma_eye", "Validation results", nullptr));
        label_15->setText(QApplication::translate("gamma_eye", "Study progress:", nullptr));
        menu_Eye->setTitle(QApplication::translate("gamma_eye", "\316\263-Eye", nullptr));
        menuMouse_Bed_Controls->setTitle(QApplication::translate("gamma_eye", "Mouse Bed Controls", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamma_eye: public Ui_gamma_eye {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMMA_EYE_H
