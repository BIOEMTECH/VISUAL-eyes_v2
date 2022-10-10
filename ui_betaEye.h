/********************************************************************************
** Form generated from reading UI file 'betaEye.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BETAEYE_H
#define UI_BETAEYE_H

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

class Ui_betaEye
{
public:
    QAction *actionExit_to_Main_Menu;
    QAction *actionInsert_Bed;
    QAction *actionEject_bed;
    QAction *actionCalibrate_bed_position;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label_63;
    QProgressBar *daq_progress;
    QTabWidget *tabWidget;
    QWidget *active_tab_5;
    QLabel *label_30;
    QProgressBar *frame_progress;
    QLabel *label_31;
    QLabel *label_32;
    QLineEdit *LE_currFrame;
    QLabel *label_33;
    QFrame *frame_14;
    QWidget *layoutWidget_4;
    QHBoxLayout *FrameLayout;
    QLabel *label_4;
    QLabel *label_5;
    QCheckBox *cb_fusion;
    QCheckBox *cb_xray;
    QGroupBox *groupBox_8;
    QLabel *label_149;
    QLabel *TL_studyID;
    QLabel *label_150;
    QLabel *LE_duration;
    QLabel *label_151;
    QLabel *TL_studyName;
    QLabel *label_22;
    QLabel *LE_frameRate;
    QLabel *label_152;
    QLabel *TL_animalID;
    QLabel *label_153;
    QLabel *TL_project;
    QLabel *label_24;
    QLabel *LE_radioNuclide;
    QLabel *LE_injectActivity;
    QLabel *label_23;
    QGroupBox *groupBox;
    QPushButton *PB_eject;
    QLabel *label_145;
    QLabel *label_146;
    QCommandLinkButton *PB_stopDAQ;
    QLabel *LE_finishTime;
    QSlider *horizontalSlider;
    QLabel *LE_startTime;
    QCommandLinkButton *PB_startDAQ;
    QComboBox *cb_colormap;
    QSlider *hsContrastB;
    QSlider *opacitySlider;
    QWidget *layoutWidget_9;
    QVBoxLayout *verticalLayout;
    QLabel *label_147;
    QLabel *label_154;
    QLabel *opacityLabel;
    QLabel *label_148;
    QFrame *frame;
    QWidget *layoutWidget_10;
    QHBoxLayout *liveLayout;
    QWidget *proc_tab_5;
    QLabel *label_34;
    QFrame *frame_2;
    QGridLayout *gridLayout_13;
    QHBoxLayout *RawLayout_2;
    QLabel *LE_counts;
    QFrame *frame_16;
    QGridLayout *gridLayout_14;
    QVBoxLayout *Energy_Spectrum_Layout;
    QLabel *label_35;
    QFrame *frame_17;
    QGridLayout *gridLayout_15;
    QHBoxLayout *RawLayout;
    QFrame *frame_18;
    QGridLayout *gridLayout_16;
    QVBoxLayout *Energy_Spectrum_Layout_2;
    QLabel *label_36;
    QWidget *tab;
    QLabel *label_7;
    QLabel *label_8;
    QWidget *layoutWidget;
    QHBoxLayout *rawHead1_layout;
    QWidget *layoutWidget_2;
    QHBoxLayout *correctedHead1_layout;
    QWidget *layoutWidget_5;
    QHBoxLayout *rawHead2_layout;
    QWidget *layoutWidget_6;
    QHBoxLayout *correctedHead2_layout;
    QLabel *label_11;
    QWidget *layoutWidget_7;
    QHBoxLayout *resolutionHead1_layout;
    QWidget *layoutWidget_8;
    QHBoxLayout *resolutionHead2_layout;
    QGroupBox *detectorElements;
    QWidget *layoutWidget1;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *lb_detElemHead1;
    QLabel *label_13;
    QLabel *lb_detElemHead2;
    QGroupBox *energyResolution;
    QWidget *layoutWidget2;
    QFormLayout *formLayout_2;
    QLabel *label_14;
    QLabel *lb_cfov;
    QGroupBox *validationStatus;
    QLabel *lb_status;
    QLabel *statusIcon;
    QLabel *lb_head1;
    QLabel *lb_head2;
    QLabel *lb_energyRes;
    QMenuBar *menubar;
    QMenu *menu_Eye;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *betaEye)
    {
        if (betaEye->objectName().isEmpty())
            betaEye->setObjectName(QStringLiteral("betaEye"));
        betaEye->resize(1259, 707);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(betaEye->sizePolicy().hasHeightForWidth());
        betaEye->setSizePolicy(sizePolicy);
        actionExit_to_Main_Menu = new QAction(betaEye);
        actionExit_to_Main_Menu->setObjectName(QStringLiteral("actionExit_to_Main_Menu"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/if_Back_32435.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit_to_Main_Menu->setIcon(icon);
        actionInsert_Bed = new QAction(betaEye);
        actionInsert_Bed->setObjectName(QStringLiteral("actionInsert_Bed"));
        actionEject_bed = new QAction(betaEye);
        actionEject_bed->setObjectName(QStringLiteral("actionEject_bed"));
        actionCalibrate_bed_position = new QAction(betaEye);
        actionCalibrate_bed_position->setObjectName(QStringLiteral("actionCalibrate_bed_position"));
        centralwidget = new QWidget(betaEye);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_63 = new QLabel(centralwidget);
        label_63->setObjectName(QStringLiteral("label_63"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_63->sizePolicy().hasHeightForWidth());
        label_63->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_63, 1, 0, 1, 1);

        daq_progress = new QProgressBar(centralwidget);
        daq_progress->setObjectName(QStringLiteral("daq_progress"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(daq_progress->sizePolicy().hasHeightForWidth());
        daq_progress->setSizePolicy(sizePolicy2);
        daq_progress->setValue(0);

        gridLayout->addWidget(daq_progress, 1, 1, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(1241, 611));
        QFont font;
        font.setFamily(QStringLiteral("FreeSans"));
        tabWidget->setFont(font);
        active_tab_5 = new QWidget();
        active_tab_5->setObjectName(QStringLiteral("active_tab_5"));
        label_30 = new QLabel(active_tab_5);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(640, 350, 101, 20));
        sizePolicy1.setHeightForWidth(label_30->sizePolicy().hasHeightForWidth());
        label_30->setSizePolicy(sizePolicy1);
        frame_progress = new QProgressBar(active_tab_5);
        frame_progress->setObjectName(QStringLiteral("frame_progress"));
        frame_progress->setGeometry(QRect(20, 370, 571, 25));
        sizePolicy.setHeightForWidth(frame_progress->sizePolicy().hasHeightForWidth());
        frame_progress->setSizePolicy(sizePolicy);
        frame_progress->setValue(0);
        label_31 = new QLabel(active_tab_5);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(20, 10, 171, 17));
        sizePolicy.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy);
        label_32 = new QLabel(active_tab_5);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(20, 350, 141, 17));
        sizePolicy1.setHeightForWidth(label_32->sizePolicy().hasHeightForWidth());
        label_32->setSizePolicy(sizePolicy1);
        LE_currFrame = new QLineEdit(active_tab_5);
        LE_currFrame->setObjectName(QStringLiteral("LE_currFrame"));
        LE_currFrame->setGeometry(QRect(640, 370, 91, 21));
        sizePolicy.setHeightForWidth(LE_currFrame->sizePolicy().hasHeightForWidth());
        LE_currFrame->setSizePolicy(sizePolicy);
        LE_currFrame->setReadOnly(true);
        label_33 = new QLabel(active_tab_5);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(640, 10, 601, 17));
        sizePolicy1.setHeightForWidth(label_33->sizePolicy().hasHeightForWidth());
        label_33->setSizePolicy(sizePolicy1);
        frame_14 = new QFrame(active_tab_5);
        frame_14->setObjectName(QStringLiteral("frame_14"));
        frame_14->setGeometry(QRect(640, 40, 576, 288));
        sizePolicy1.setHeightForWidth(frame_14->sizePolicy().hasHeightForWidth());
        frame_14->setSizePolicy(sizePolicy1);
        frame_14->setFrameShape(QFrame::StyledPanel);
        frame_14->setFrameShadow(QFrame::Raised);
        layoutWidget_4 = new QWidget(frame_14);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(0, 0, 581, 291));
        sizePolicy1.setHeightForWidth(layoutWidget_4->sizePolicy().hasHeightForWidth());
        layoutWidget_4->setSizePolicy(sizePolicy1);
        FrameLayout = new QHBoxLayout(layoutWidget_4);
        FrameLayout->setObjectName(QStringLiteral("FrameLayout"));
        FrameLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(active_tab_5);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(600, 37, 31, 31));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setFrameShape(QFrame::NoFrame);
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/icons/letter-l-48.png")));
        label_5 = new QLabel(active_tab_5);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(600, 301, 31, 31));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/icons/letter-r-48.png")));
        cb_fusion = new QCheckBox(active_tab_5);
        cb_fusion->setObjectName(QStringLiteral("cb_fusion"));
        cb_fusion->setGeometry(QRect(370, 10, 111, 23));
        cb_xray = new QCheckBox(active_tab_5);
        cb_xray->setObjectName(QStringLiteral("cb_xray"));
        cb_xray->setGeometry(QRect(490, 10, 101, 23));
        groupBox_8 = new QGroupBox(active_tab_5);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(640, 400, 581, 171));
        sizePolicy1.setHeightForWidth(groupBox_8->sizePolicy().hasHeightForWidth());
        groupBox_8->setSizePolicy(sizePolicy1);
        label_149 = new QLabel(groupBox_8);
        label_149->setObjectName(QStringLiteral("label_149"));
        label_149->setGeometry(QRect(30, 40, 60, 17));
        sizePolicy1.setHeightForWidth(label_149->sizePolicy().hasHeightForWidth());
        label_149->setSizePolicy(sizePolicy1);
        TL_studyID = new QLabel(groupBox_8);
        TL_studyID->setObjectName(QStringLiteral("TL_studyID"));
        TL_studyID->setGeometry(QRect(121, 32, 161, 18));
        sizePolicy1.setHeightForWidth(TL_studyID->sizePolicy().hasHeightForWidth());
        TL_studyID->setSizePolicy(sizePolicy1);
        label_150 = new QLabel(groupBox_8);
        label_150->setObjectName(QStringLiteral("label_150"));
        label_150->setGeometry(QRect(314, 40, 101, 17));
        sizePolicy1.setHeightForWidth(label_150->sizePolicy().hasHeightForWidth());
        label_150->setSizePolicy(sizePolicy1);
        LE_duration = new QLabel(groupBox_8);
        LE_duration->setObjectName(QStringLiteral("LE_duration"));
        LE_duration->setGeometry(QRect(430, 32, 131, 18));
        sizePolicy1.setHeightForWidth(LE_duration->sizePolicy().hasHeightForWidth());
        LE_duration->setSizePolicy(sizePolicy1);
        label_151 = new QLabel(groupBox_8);
        label_151->setObjectName(QStringLiteral("label_151"));
        label_151->setGeometry(QRect(30, 68, 85, 17));
        sizePolicy1.setHeightForWidth(label_151->sizePolicy().hasHeightForWidth());
        label_151->setSizePolicy(sizePolicy1);
        TL_studyName = new QLabel(groupBox_8);
        TL_studyName->setObjectName(QStringLiteral("TL_studyName"));
        TL_studyName->setGeometry(QRect(120, 60, 161, 18));
        sizePolicy1.setHeightForWidth(TL_studyName->sizePolicy().hasHeightForWidth());
        TL_studyName->setSizePolicy(sizePolicy1);
        label_22 = new QLabel(groupBox_8);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(314, 68, 105, 17));
        sizePolicy1.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy1);
        LE_frameRate = new QLabel(groupBox_8);
        LE_frameRate->setObjectName(QStringLiteral("LE_frameRate"));
        LE_frameRate->setGeometry(QRect(431, 60, 131, 18));
        sizePolicy1.setHeightForWidth(LE_frameRate->sizePolicy().hasHeightForWidth());
        LE_frameRate->setSizePolicy(sizePolicy1);
        label_152 = new QLabel(groupBox_8);
        label_152->setObjectName(QStringLiteral("label_152"));
        label_152->setGeometry(QRect(30, 97, 67, 17));
        sizePolicy1.setHeightForWidth(label_152->sizePolicy().hasHeightForWidth());
        label_152->setSizePolicy(sizePolicy1);
        TL_animalID = new QLabel(groupBox_8);
        TL_animalID->setObjectName(QStringLiteral("TL_animalID"));
        TL_animalID->setGeometry(QRect(121, 89, 161, 16));
        sizePolicy1.setHeightForWidth(TL_animalID->sizePolicy().hasHeightForWidth());
        TL_animalID->setSizePolicy(sizePolicy1);
        label_153 = new QLabel(groupBox_8);
        label_153->setObjectName(QStringLiteral("label_153"));
        label_153->setGeometry(QRect(31, 125, 50, 17));
        sizePolicy1.setHeightForWidth(label_153->sizePolicy().hasHeightForWidth());
        label_153->setSizePolicy(sizePolicy1);
        TL_project = new QLabel(groupBox_8);
        TL_project->setObjectName(QStringLiteral("TL_project"));
        TL_project->setGeometry(QRect(121, 117, 171, 18));
        sizePolicy1.setHeightForWidth(TL_project->sizePolicy().hasHeightForWidth());
        TL_project->setSizePolicy(sizePolicy1);
        label_24 = new QLabel(groupBox_8);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(315, 121, 129, 18));
        LE_radioNuclide = new QLabel(groupBox_8);
        LE_radioNuclide->setObjectName(QStringLiteral("LE_radioNuclide"));
        LE_radioNuclide->setGeometry(QRect(431, 87, 131, 17));
        LE_injectActivity = new QLabel(groupBox_8);
        LE_injectActivity->setObjectName(QStringLiteral("LE_injectActivity"));
        LE_injectActivity->setGeometry(QRect(432, 110, 61, 18));
        label_23 = new QLabel(groupBox_8);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(315, 96, 129, 17));
        groupBox = new QGroupBox(active_tab_5);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 400, 571, 171));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        PB_eject = new QPushButton(groupBox);
        PB_eject->setObjectName(QStringLiteral("PB_eject"));
        PB_eject->setGeometry(QRect(479, 61, 72, 66));
        sizePolicy.setHeightForWidth(PB_eject->sizePolicy().hasHeightForWidth());
        PB_eject->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/Eject button.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QStringLiteral(":/icons/Disable Eject button.png"), QSize(), QIcon::Disabled, QIcon::Off);
        PB_eject->setIcon(icon1);
        PB_eject->setIconSize(QSize(60, 60));
        label_145 = new QLabel(groupBox);
        label_145->setObjectName(QStringLiteral("label_145"));
        label_145->setGeometry(QRect(13, 51, 91, 16));
        sizePolicy1.setHeightForWidth(label_145->sizePolicy().hasHeightForWidth());
        label_145->setSizePolicy(sizePolicy1);
        label_146 = new QLabel(groupBox);
        label_146->setObjectName(QStringLiteral("label_146"));
        label_146->setGeometry(QRect(13, 30, 81, 16));
        sizePolicy1.setHeightForWidth(label_146->sizePolicy().hasHeightForWidth());
        label_146->setSizePolicy(sizePolicy1);
        PB_stopDAQ = new QCommandLinkButton(groupBox);
        PB_stopDAQ->setObjectName(QStringLiteral("PB_stopDAQ"));
        PB_stopDAQ->setEnabled(true);
        PB_stopDAQ->setGeometry(QRect(399, 60, 61, 61));
        sizePolicy1.setHeightForWidth(PB_stopDAQ->sizePolicy().hasHeightForWidth());
        PB_stopDAQ->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamily(QStringLiteral("FreeSerif"));
        PB_stopDAQ->setFont(font1);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/Stop button.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QStringLiteral(":/icons/Disable Stop button.png"), QSize(), QIcon::Disabled, QIcon::Off);
        PB_stopDAQ->setIcon(icon2);
        PB_stopDAQ->setIconSize(QSize(50, 50));
        LE_finishTime = new QLabel(groupBox);
        LE_finishTime->setObjectName(QStringLiteral("LE_finishTime"));
        LE_finishTime->setGeometry(QRect(89, 51, 16, 16));
        sizePolicy1.setHeightForWidth(LE_finishTime->sizePolicy().hasHeightForWidth());
        LE_finishTime->setSizePolicy(sizePolicy1);
        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(130, 74, 171, 16));
        sizePolicy.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedAppearance(false);
        horizontalSlider->setInvertedControls(false);
        LE_startTime = new QLabel(groupBox);
        LE_startTime->setObjectName(QStringLiteral("LE_startTime"));
        LE_startTime->setGeometry(QRect(89, 30, 16, 16));
        sizePolicy1.setHeightForWidth(LE_startTime->sizePolicy().hasHeightForWidth());
        LE_startTime->setSizePolicy(sizePolicy1);
        PB_startDAQ = new QCommandLinkButton(groupBox);
        PB_startDAQ->setObjectName(QStringLiteral("PB_startDAQ"));
        PB_startDAQ->setEnabled(true);
        PB_startDAQ->setGeometry(QRect(320, 60, 61, 61));
        sizePolicy1.setHeightForWidth(PB_startDAQ->sizePolicy().hasHeightForWidth());
        PB_startDAQ->setSizePolicy(sizePolicy1);
        PB_startDAQ->setFont(font);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/Play button.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QStringLiteral(":/icons/Disable Play button.png"), QSize(), QIcon::Disabled, QIcon::Off);
        PB_startDAQ->setIcon(icon3);
        PB_startDAQ->setIconSize(QSize(50, 50));
        cb_colormap = new QComboBox(groupBox);
        cb_colormap->addItem(QString());
        cb_colormap->addItem(QString());
        cb_colormap->addItem(QString());
        cb_colormap->addItem(QString());
        cb_colormap->addItem(QString());
        cb_colormap->setObjectName(QStringLiteral("cb_colormap"));
        cb_colormap->setGeometry(QRect(130, 140, 111, 21));
        sizePolicy.setHeightForWidth(cb_colormap->sizePolicy().hasHeightForWidth());
        cb_colormap->setSizePolicy(sizePolicy);
        hsContrastB = new QSlider(groupBox);
        hsContrastB->setObjectName(QStringLiteral("hsContrastB"));
        hsContrastB->setGeometry(QRect(130, 97, 171, 16));
        sizePolicy.setHeightForWidth(hsContrastB->sizePolicy().hasHeightForWidth());
        hsContrastB->setSizePolicy(sizePolicy);
        hsContrastB->setOrientation(Qt::Horizontal);
        hsContrastB->setInvertedAppearance(false);
        hsContrastB->setInvertedControls(false);
        opacitySlider = new QSlider(groupBox);
        opacitySlider->setObjectName(QStringLiteral("opacitySlider"));
        opacitySlider->setGeometry(QRect(130, 120, 171, 16));
        opacitySlider->setOrientation(Qt::Horizontal);
        layoutWidget_9 = new QWidget(groupBox);
        layoutWidget_9->setObjectName(QStringLiteral("layoutWidget_9"));
        layoutWidget_9->setGeometry(QRect(10, 72, 117, 88));
        verticalLayout = new QVBoxLayout(layoutWidget_9);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_147 = new QLabel(layoutWidget_9);
        label_147->setObjectName(QStringLiteral("label_147"));
        sizePolicy1.setHeightForWidth(label_147->sizePolicy().hasHeightForWidth());
        label_147->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(label_147);

        label_154 = new QLabel(layoutWidget_9);
        label_154->setObjectName(QStringLiteral("label_154"));
        sizePolicy1.setHeightForWidth(label_154->sizePolicy().hasHeightForWidth());
        label_154->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(label_154);

        opacityLabel = new QLabel(layoutWidget_9);
        opacityLabel->setObjectName(QStringLiteral("opacityLabel"));

        verticalLayout->addWidget(opacityLabel);

        label_148 = new QLabel(layoutWidget_9);
        label_148->setObjectName(QStringLiteral("label_148"));
        sizePolicy1.setHeightForWidth(label_148->sizePolicy().hasHeightForWidth());
        label_148->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(label_148);

        frame = new QFrame(active_tab_5);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(20, 40, 576, 288));
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        layoutWidget_10 = new QWidget(frame);
        layoutWidget_10->setObjectName(QStringLiteral("layoutWidget_10"));
        layoutWidget_10->setGeometry(QRect(0, 0, 581, 291));
        sizePolicy1.setHeightForWidth(layoutWidget_10->sizePolicy().hasHeightForWidth());
        layoutWidget_10->setSizePolicy(sizePolicy1);
        liveLayout = new QHBoxLayout(layoutWidget_10);
        liveLayout->setObjectName(QStringLiteral("liveLayout"));
        liveLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget->addTab(active_tab_5, QString());
        proc_tab_5 = new QWidget();
        proc_tab_5->setObjectName(QStringLiteral("proc_tab_5"));
        label_34 = new QLabel(proc_tab_5);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(30, 10, 251, 17));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_34->sizePolicy().hasHeightForWidth());
        label_34->setSizePolicy(sizePolicy3);
        frame_2 = new QFrame(proc_tab_5);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(550, 300, 580, 260));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_13 = new QGridLayout(frame_2);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        RawLayout_2 = new QHBoxLayout();
        RawLayout_2->setObjectName(QStringLiteral("RawLayout_2"));

        gridLayout_13->addLayout(RawLayout_2, 0, 0, 1, 1);

        LE_counts = new QLabel(proc_tab_5);
        LE_counts->setObjectName(QStringLiteral("LE_counts"));
        LE_counts->setGeometry(QRect(9, 351, 16, 18));
        sizePolicy3.setHeightForWidth(LE_counts->sizePolicy().hasHeightForWidth());
        LE_counts->setSizePolicy(sizePolicy3);
        frame_16 = new QFrame(proc_tab_5);
        frame_16->setObjectName(QStringLiteral("frame_16"));
        frame_16->setGeometry(QRect(20, 30, 430, 260));
        frame_16->setFrameShape(QFrame::StyledPanel);
        frame_16->setFrameShadow(QFrame::Raised);
        gridLayout_14 = new QGridLayout(frame_16);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        Energy_Spectrum_Layout = new QVBoxLayout();
        Energy_Spectrum_Layout->setObjectName(QStringLiteral("Energy_Spectrum_Layout"));

        gridLayout_14->addLayout(Energy_Spectrum_Layout, 0, 0, 1, 1);

        label_35 = new QLabel(proc_tab_5);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(549, 10, 101, 17));
        sizePolicy1.setHeightForWidth(label_35->sizePolicy().hasHeightForWidth());
        label_35->setSizePolicy(sizePolicy1);
        frame_17 = new QFrame(proc_tab_5);
        frame_17->setObjectName(QStringLiteral("frame_17"));
        frame_17->setGeometry(QRect(550, 30, 580, 260));
        frame_17->setFrameShape(QFrame::StyledPanel);
        frame_17->setFrameShadow(QFrame::Raised);
        gridLayout_15 = new QGridLayout(frame_17);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        RawLayout = new QHBoxLayout();
        RawLayout->setObjectName(QStringLiteral("RawLayout"));

        gridLayout_15->addLayout(RawLayout, 0, 0, 1, 1);

        frame_18 = new QFrame(proc_tab_5);
        frame_18->setObjectName(QStringLiteral("frame_18"));
        frame_18->setGeometry(QRect(20, 300, 430, 260));
        frame_18->setFrameShape(QFrame::StyledPanel);
        frame_18->setFrameShadow(QFrame::Raised);
        gridLayout_16 = new QGridLayout(frame_18);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        Energy_Spectrum_Layout_2 = new QVBoxLayout();
        Energy_Spectrum_Layout_2->setObjectName(QStringLiteral("Energy_Spectrum_Layout_2"));

        gridLayout_16->addLayout(Energy_Spectrum_Layout_2, 0, 0, 1, 1);

        label_36 = new QLabel(proc_tab_5);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(750, 10, 141, 17));
        sizePolicy1.setHeightForWidth(label_36->sizePolicy().hasHeightForWidth());
        label_36->setSizePolicy(sizePolicy1);
        tabWidget->addTab(proc_tab_5, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(40, 10, 111, 17));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(320, 10, 141, 17));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 30, 261, 261));
        rawHead1_layout = new QHBoxLayout(layoutWidget);
        rawHead1_layout->setObjectName(QStringLiteral("rawHead1_layout"));
        rawHead1_layout->setContentsMargins(0, 0, 0, 0);
        layoutWidget_2 = new QWidget(tab);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(310, 30, 261, 261));
        correctedHead1_layout = new QHBoxLayout(layoutWidget_2);
        correctedHead1_layout->setObjectName(QStringLiteral("correctedHead1_layout"));
        correctedHead1_layout->setContentsMargins(0, 0, 0, 0);
        layoutWidget_5 = new QWidget(tab);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(30, 300, 261, 261));
        rawHead2_layout = new QHBoxLayout(layoutWidget_5);
        rawHead2_layout->setObjectName(QStringLiteral("rawHead2_layout"));
        rawHead2_layout->setContentsMargins(0, 0, 0, 0);
        layoutWidget_6 = new QWidget(tab);
        layoutWidget_6->setObjectName(QStringLiteral("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(310, 300, 261, 261));
        correctedHead2_layout = new QHBoxLayout(layoutWidget_6);
        correctedHead2_layout->setObjectName(QStringLiteral("correctedHead2_layout"));
        correctedHead2_layout->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(tab);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(620, 10, 231, 17));
        layoutWidget_7 = new QWidget(tab);
        layoutWidget_7->setObjectName(QStringLiteral("layoutWidget_7"));
        layoutWidget_7->setGeometry(QRect(620, 30, 291, 371));
        resolutionHead1_layout = new QHBoxLayout(layoutWidget_7);
        resolutionHead1_layout->setObjectName(QStringLiteral("resolutionHead1_layout"));
        resolutionHead1_layout->setContentsMargins(0, 0, 0, 0);
        layoutWidget_8 = new QWidget(tab);
        layoutWidget_8->setObjectName(QStringLiteral("layoutWidget_8"));
        layoutWidget_8->setGeometry(QRect(930, 30, 291, 371));
        resolutionHead2_layout = new QHBoxLayout(layoutWidget_8);
        resolutionHead2_layout->setObjectName(QStringLiteral("resolutionHead2_layout"));
        resolutionHead2_layout->setContentsMargins(0, 0, 0, 0);
        detectorElements = new QGroupBox(tab);
        detectorElements->setObjectName(QStringLiteral("detectorElements"));
        detectorElements->setGeometry(QRect(630, 420, 321, 81));
        layoutWidget1 = new QWidget(detectorElements);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 30, 281, 44));
        formLayout = new QFormLayout(layoutWidget1);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        lb_detElemHead1 = new QLabel(layoutWidget1);
        lb_detElemHead1->setObjectName(QStringLiteral("lb_detElemHead1"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lb_detElemHead1);

        label_13 = new QLabel(layoutWidget1);
        label_13->setObjectName(QStringLiteral("label_13"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_13);

        lb_detElemHead2 = new QLabel(layoutWidget1);
        lb_detElemHead2->setObjectName(QStringLiteral("lb_detElemHead2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lb_detElemHead2);

        energyResolution = new QGroupBox(tab);
        energyResolution->setObjectName(QStringLiteral("energyResolution"));
        energyResolution->setGeometry(QRect(630, 500, 321, 61));
        layoutWidget2 = new QWidget(energyResolution);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(12, 32, 281, 20));
        formLayout_2 = new QFormLayout(layoutWidget2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(layoutWidget2);
        label_14->setObjectName(QStringLiteral("label_14"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_14);

        lb_cfov = new QLabel(layoutWidget2);
        lb_cfov->setObjectName(QStringLiteral("lb_cfov"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lb_cfov);

        validationStatus = new QGroupBox(tab);
        validationStatus->setObjectName(QStringLiteral("validationStatus"));
        validationStatus->setGeometry(QRect(990, 420, 191, 141));
        lb_status = new QLabel(validationStatus);
        lb_status->setObjectName(QStringLiteral("lb_status"));
        lb_status->setGeometry(QRect(60, 30, 81, 16));
        statusIcon = new QLabel(validationStatus);
        statusIcon->setObjectName(QStringLiteral("statusIcon"));
        statusIcon->setGeometry(QRect(60, 49, 85, 85));
        lb_head1 = new QLabel(tab);
        lb_head1->setObjectName(QStringLiteral("lb_head1"));
        lb_head1->setGeometry(QRect(10, 160, 81, 21));
        lb_head2 = new QLabel(tab);
        lb_head2->setObjectName(QStringLiteral("lb_head2"));
        lb_head2->setGeometry(QRect(10, 410, 111, 17));
        lb_energyRes = new QLabel(tab);
        lb_energyRes->setObjectName(QStringLiteral("lb_energyRes"));
        lb_energyRes->setGeometry(QRect(580, 180, 141, 17));
        tabWidget->addTab(tab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 2);

        betaEye->setCentralWidget(centralwidget);
        menubar = new QMenuBar(betaEye);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1259, 20));
        menu_Eye = new QMenu(menubar);
        menu_Eye->setObjectName(QStringLiteral("menu_Eye"));
        betaEye->setMenuBar(menubar);
        statusbar = new QStatusBar(betaEye);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        betaEye->setStatusBar(statusbar);

        menubar->addAction(menu_Eye->menuAction());
        menu_Eye->addSeparator();
        menu_Eye->addAction(actionExit_to_Main_Menu);

        retranslateUi(betaEye);

        tabWidget->setCurrentIndex(0);
        cb_colormap->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(betaEye);
    } // setupUi

    void retranslateUi(QMainWindow *betaEye)
    {
        betaEye->setWindowTitle(QApplication::translate("betaEye", "MainWindow", nullptr));
        actionExit_to_Main_Menu->setText(QApplication::translate("betaEye", "Exit to Main Menu", nullptr));
        actionInsert_Bed->setText(QApplication::translate("betaEye", "Insert bed", nullptr));
        actionEject_bed->setText(QApplication::translate("betaEye", "Eject bed", nullptr));
        actionCalibrate_bed_position->setText(QApplication::translate("betaEye", "Calibrate bed position", nullptr));
        label_63->setText(QApplication::translate("betaEye", "Study Progress:", nullptr));
        label_30->setText(QApplication::translate("betaEye", "Current frame", nullptr));
        label_31->setText(QApplication::translate("betaEye", "Live image ", nullptr));
        label_32->setText(QApplication::translate("betaEye", "Frame Progress", nullptr));
        label_33->setText(QApplication::translate("betaEye", "Summed image", nullptr));
        label_4->setText(QString());
        label_5->setText(QString());
        cb_fusion->setText(QApplication::translate("betaEye", "Optical fusion", nullptr));
        cb_xray->setText(QApplication::translate("betaEye", "Xray fusion", nullptr));
        groupBox_8->setTitle(QApplication::translate("betaEye", "Info", nullptr));
        label_149->setText(QApplication::translate("betaEye", "Study ID:", nullptr));
        TL_studyID->setText(QString());
        label_150->setText(QApplication::translate("betaEye", "Study Duration:", nullptr));
        LE_duration->setText(QString());
        label_151->setText(QApplication::translate("betaEye", "Study Name:", nullptr));
        TL_studyName->setText(QString());
        label_22->setText(QApplication::translate("betaEye", "Frame Duration:", nullptr));
        LE_frameRate->setText(QString());
        label_152->setText(QApplication::translate("betaEye", "Animal ID:", nullptr));
        TL_animalID->setText(QString());
        label_153->setText(QApplication::translate("betaEye", "Project:", nullptr));
        TL_project->setText(QString());
        label_24->setText(QApplication::translate("betaEye", "Injected activity: ", nullptr));
        LE_radioNuclide->setText(QString());
        LE_injectActivity->setText(QString());
        label_23->setText(QApplication::translate("betaEye", "Radionuclide:", nullptr));
        groupBox->setTitle(QApplication::translate("betaEye", "Controls", nullptr));
        PB_eject->setText(QString());
        label_145->setText(QApplication::translate("betaEye", "Finish Time:", nullptr));
        label_146->setText(QApplication::translate("betaEye", "Start Time:", nullptr));
        PB_stopDAQ->setText(QString());
        LE_finishTime->setText(QString());
        LE_startTime->setText(QString());
        PB_startDAQ->setText(QString());
        cb_colormap->setItemText(0, QApplication::translate("betaEye", "GrayScale", nullptr));
        cb_colormap->setItemText(1, QApplication::translate("betaEye", "Royal", nullptr));
        cb_colormap->setItemText(2, QApplication::translate("betaEye", "Jet", nullptr));
        cb_colormap->setItemText(3, QApplication::translate("betaEye", "Red Hot", nullptr));
        cb_colormap->setItemText(4, QApplication::translate("betaEye", "Smart", nullptr));

        label_147->setText(QApplication::translate("betaEye", "Contrast (Live):", nullptr));
        label_154->setText(QApplication::translate("betaEye", "Contrast (Sum.):", nullptr));
        opacityLabel->setText(QApplication::translate("betaEye", "Opacity", nullptr));
        label_148->setText(QApplication::translate("betaEye", "Color map:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(active_tab_5), QApplication::translate("betaEye", "Live Acquisition", nullptr));
        label_34->setText(QApplication::translate("betaEye", "Energy Spectrum (counts/KeV):", nullptr));
        LE_counts->setText(QString());
        label_35->setText(QApplication::translate("betaEye", "Raw Data:", nullptr));
        label_36->setText(QApplication::translate("betaEye", "Coincidecies/sec:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(proc_tab_5), QApplication::translate("betaEye", "Raw Imaging", nullptr));
        label_7->setText(QApplication::translate("betaEye", "Raw energy", nullptr));
        label_8->setText(QApplication::translate("betaEye", "Corrected energy", nullptr));
        label_11->setText(QApplication::translate("betaEye", "Energy resolution", nullptr));
        detectorElements->setTitle(QApplication::translate("betaEye", "Detector elements processed", nullptr));
        label_2->setText(QApplication::translate("betaEye", "Head 1:", nullptr));
        lb_detElemHead1->setText(QString());
        label_13->setText(QApplication::translate("betaEye", "Head 2:", nullptr));
        lb_detElemHead2->setText(QString());
        energyResolution->setTitle(QApplication::translate("betaEye", "Energy resolution", nullptr));
        label_14->setText(QApplication::translate("betaEye", "CFOV:", nullptr));
        lb_cfov->setText(QString());
        validationStatus->setTitle(QApplication::translate("betaEye", "Validation status", nullptr));
        lb_status->setText(QString());
        statusIcon->setText(QString());
        lb_head1->setText(QString());
        lb_head2->setText(QString());
        lb_energyRes->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("betaEye", "Validation results", nullptr));
        menu_Eye->setTitle(QApplication::translate("betaEye", "\316\262-Eye", nullptr));
    } // retranslateUi

};

namespace Ui {
    class betaEye: public Ui_betaEye {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BETAEYE_H
