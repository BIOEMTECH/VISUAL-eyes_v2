/********************************************************************************
** Form generated from reading UI file 'PostProcessing.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSTPROCESSING_H
#define UI_POSTPROCESSING_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PostProcessing
{
public:
    QAction *action_loadStudy;
    QAction *actionExit_to_Main_Menu;
    QAction *actionLoad_Last_Study;
    QAction *actionLoad_Last_Study_2;
    QWidget *centralwidget;
    QTabWidget *TW_procTools;
    QWidget *ProcessingTools;
    QGroupBox *gB_SaveSection;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *PB_saveAs;
    QPushButton *PB_plot_excel;
    QPushButton *PB_saveAllFrames;
    QPushButton *PB_saveSelected;
    QPushButton *PB_savePlot;
    QPushButton *PB_dicomViewer;
    QPushButton *PB_merge;
    QPushButton *PB_pdfReport;
    QGroupBox *gB_ROIManager;
    QListWidget *ROI_list;
    QWidget *widget;
    QGridLayout *gridLayout_5;
    QPushButton *PB_updatePos;
    QPushButton *PB_ShowLabels;
    QPushButton *PB_showRois;
    QPushButton *PB_plotRois;
    QPushButton *PB_deleteRoi;
    QPushButton *PB_addRoi;
    QPushButton *PB_refArea;
    QPushButton *PB_measure;
    QPushButton *PB_renameRoi;
    QGroupBox *gB_RoiSelection;
    QLabel *L_RoiType;
    QPushButton *pb_rectROI;
    QPushButton *pb_reset_4;
    QPushButton *pb_ellipseROI;
    QPushButton *pb_freeROI;
    QGroupBox *gB_ImageSettings;
    QSlider *opacitySlider;
    QLabel *opacityLabel;
    QSlider *horizontalSlider_contrast_min;
    QSlider *horizontalSlider_contrast;
    QLabel *l_contrast_2;
    QLabel *l_contrast_3;
    QDoubleSpinBox *sB_max;
    QDoubleSpinBox *sB_min;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_4;
    QLabel *L_choosecM;
    QComboBox *CB_colormaps;
    QGroupBox *gB_SaveSection_2;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_7;
    QLabel *l_something;
    QLabel *l_contrast_6;
    QLabel *l_AnimalID;
    QLabel *l_contrast_5;
    QLabel *l_contrast_7;
    QLabel *l_contrast_4;
    QLabel *l_InjectDateTime;
    QLabel *l_Name;
    QLabel *l_StudID;
    QLabel *l_injectiveAct;
    QLabel *l_InjectAct;
    QLabel *l_Radio;
    QWidget *StudyInfo;
    QLabel *L_Age;
    QRadioButton *rb_mCi;
    QLabel *L_StudyDate;
    QLineEdit *LE_age;
    QLabel *L_breed;
    QLineEdit *LE_p_name;
    QLabel *L_species;
    QLabel *L_studyID;
    QLabel *L_animalMarking;
    QLabel *L_InitActivity;
    QLineEdit *LE_species;
    QLabel *L_InjPath;
    QRadioButton *rb_mBq_2;
    QLineEdit *LE_strain;
    QLabel *L_AnimalID;
    QDateEdit *dE_studyDate;
    QLabel *L_radioNuclide;
    QLabel *L_weight;
    QLineEdit *LE_weight;
    QLabel *L_InjDate;
    QLabel *L_RadioPharma;
    QLineEdit *LE_SName;
    QLineEdit *le_marking;
    QLabel *L_studyName;
    QLineEdit *LE_r_pharma;
    QDateTimeEdit *dTime_ingection;
    QLineEdit *LE_studyID;
    QDoubleSpinBox *dSB_activity;
    QLabel *L_project;
    QComboBox *CB_radioNuclide;
    QComboBox *CB_ing_path;
    QLabel *L_InjActivity;
    QLineEdit *LE_project;
    QTextEdit *TE_comments;
    QLabel *L_comments;
    QRadioButton *rb_male;
    QLabel *L_gender;
    QRadioButton *rb_female;
    QDoubleSpinBox *dSB_volume;
    QLabel *L_InjVol;
    QLabel *L_ul;
    QRadioButton *rB_fDynamic;
    QLabel *l_frame;
    QLineEdit *LE_frame;
    QLineEdit *LE_expDuration;
    QLabel *L_Duration;
    QLineEdit *LE_mod;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *dSB_injActivity;
    QLineEdit *dTE_aqTime;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLabel *label_3;
    QScrollBar *horizontalScrollBar_2;
    QToolButton *tB_playStack;
    QCheckBox *cB_selection;
    QCheckBox *cB_fusion;
    QRadioButton *radioButtonAcivityPerROI;
    QRadioButton *radioButtonCountsPerROI;
    QCheckBox *cB_xray;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_3;
    QMenuBar *menubar;
    QMenu *menuOptions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PostProcessing)
    {
        if (PostProcessing->objectName().isEmpty())
            PostProcessing->setObjectName(QStringLiteral("PostProcessing"));
        PostProcessing->resize(1250, 725);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PostProcessing->sizePolicy().hasHeightForWidth());
        PostProcessing->setSizePolicy(sizePolicy);
        PostProcessing->setMinimumSize(QSize(1232, 725));
        PostProcessing->setMaximumSize(QSize(1250, 725));
        QFont font;
        font.setPointSize(10);
        PostProcessing->setFont(font);
        action_loadStudy = new QAction(PostProcessing);
        action_loadStudy->setObjectName(QStringLiteral("action_loadStudy"));
        action_loadStudy->setShortcutContext(Qt::ApplicationShortcut);
        action_loadStudy->setMenuRole(QAction::ApplicationSpecificRole);
        action_loadStudy->setPriority(QAction::HighPriority);
        actionExit_to_Main_Menu = new QAction(PostProcessing);
        actionExit_to_Main_Menu->setObjectName(QStringLiteral("actionExit_to_Main_Menu"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/if_Back_32435.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit_to_Main_Menu->setIcon(icon);
        actionLoad_Last_Study = new QAction(PostProcessing);
        actionLoad_Last_Study->setObjectName(QStringLiteral("actionLoad_Last_Study"));
        actionLoad_Last_Study_2 = new QAction(PostProcessing);
        actionLoad_Last_Study_2->setObjectName(QStringLiteral("actionLoad_Last_Study_2"));
        centralwidget = new QWidget(PostProcessing);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        TW_procTools = new QTabWidget(centralwidget);
        TW_procTools->setObjectName(QStringLiteral("TW_procTools"));
        TW_procTools->setGeometry(QRect(10, 360, 1231, 321));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TW_procTools->sizePolicy().hasHeightForWidth());
        TW_procTools->setSizePolicy(sizePolicy1);
        TW_procTools->setTabShape(QTabWidget::Rounded);
        ProcessingTools = new QWidget();
        ProcessingTools->setObjectName(QStringLiteral("ProcessingTools"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ProcessingTools->sizePolicy().hasHeightForWidth());
        ProcessingTools->setSizePolicy(sizePolicy2);
        gB_SaveSection = new QGroupBox(ProcessingTools);
        gB_SaveSection->setObjectName(QStringLiteral("gB_SaveSection"));
        gB_SaveSection->setGeometry(QRect(717, 9, 501, 161));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(gB_SaveSection->sizePolicy().hasHeightForWidth());
        gB_SaveSection->setSizePolicy(sizePolicy3);
        layoutWidget = new QWidget(gB_SaveSection);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 31, 484, 121));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        PB_saveAs = new QPushButton(layoutWidget);
        PB_saveAs->setObjectName(QStringLiteral("PB_saveAs"));
        PB_saveAs->setFont(font);

        gridLayout->addWidget(PB_saveAs, 0, 0, 1, 1);

        PB_plot_excel = new QPushButton(layoutWidget);
        PB_plot_excel->setObjectName(QStringLiteral("PB_plot_excel"));
        PB_plot_excel->setFont(font);

        gridLayout->addWidget(PB_plot_excel, 0, 1, 1, 1);

        PB_saveAllFrames = new QPushButton(layoutWidget);
        PB_saveAllFrames->setObjectName(QStringLiteral("PB_saveAllFrames"));
        PB_saveAllFrames->setFont(font);

        gridLayout->addWidget(PB_saveAllFrames, 0, 2, 1, 1);

        PB_saveSelected = new QPushButton(layoutWidget);
        PB_saveSelected->setObjectName(QStringLiteral("PB_saveSelected"));
        PB_saveSelected->setFont(font);

        gridLayout->addWidget(PB_saveSelected, 1, 0, 1, 1);

        PB_savePlot = new QPushButton(layoutWidget);
        PB_savePlot->setObjectName(QStringLiteral("PB_savePlot"));
        PB_savePlot->setFont(font);

        gridLayout->addWidget(PB_savePlot, 1, 1, 1, 1);

        PB_dicomViewer = new QPushButton(layoutWidget);
        PB_dicomViewer->setObjectName(QStringLiteral("PB_dicomViewer"));

        gridLayout->addWidget(PB_dicomViewer, 1, 2, 1, 1);

        PB_merge = new QPushButton(layoutWidget);
        PB_merge->setObjectName(QStringLiteral("PB_merge"));

        gridLayout->addWidget(PB_merge, 2, 0, 1, 1);

        PB_pdfReport = new QPushButton(layoutWidget);
        PB_pdfReport->setObjectName(QStringLiteral("PB_pdfReport"));

        gridLayout->addWidget(PB_pdfReport, 2, 1, 1, 1);

        gB_ROIManager = new QGroupBox(ProcessingTools);
        gB_ROIManager->setObjectName(QStringLiteral("gB_ROIManager"));
        gB_ROIManager->setGeometry(QRect(392, 9, 314, 271));
        sizePolicy3.setHeightForWidth(gB_ROIManager->sizePolicy().hasHeightForWidth());
        gB_ROIManager->setSizePolicy(sizePolicy3);
        ROI_list = new QListWidget(gB_ROIManager);
        ROI_list->setObjectName(QStringLiteral("ROI_list"));
        ROI_list->setGeometry(QRect(10, 30, 131, 231));
        sizePolicy3.setHeightForWidth(ROI_list->sizePolicy().hasHeightForWidth());
        ROI_list->setSizePolicy(sizePolicy3);
        widget = new QWidget(gB_ROIManager);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(150, 30, 151, 231));
        gridLayout_5 = new QGridLayout(widget);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        PB_updatePos = new QPushButton(widget);
        PB_updatePos->setObjectName(QStringLiteral("PB_updatePos"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(PB_updatePos->sizePolicy().hasHeightForWidth());
        PB_updatePos->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(PB_updatePos, 3, 0, 1, 1);

        PB_ShowLabels = new QPushButton(widget);
        PB_ShowLabels->setObjectName(QStringLiteral("PB_ShowLabels"));
        sizePolicy4.setHeightForWidth(PB_ShowLabels->sizePolicy().hasHeightForWidth());
        PB_ShowLabels->setSizePolicy(sizePolicy4);
        PB_ShowLabels->setCheckable(false);

        gridLayout_5->addWidget(PB_ShowLabels, 4, 0, 1, 1);

        PB_showRois = new QPushButton(widget);
        PB_showRois->setObjectName(QStringLiteral("PB_showRois"));
        sizePolicy4.setHeightForWidth(PB_showRois->sizePolicy().hasHeightForWidth());
        PB_showRois->setSizePolicy(sizePolicy4);
        PB_showRois->setCheckable(false);

        gridLayout_5->addWidget(PB_showRois, 6, 0, 1, 1);

        PB_plotRois = new QPushButton(widget);
        PB_plotRois->setObjectName(QStringLiteral("PB_plotRois"));
        PB_plotRois->setCheckable(true);

        gridLayout_5->addWidget(PB_plotRois, 8, 0, 1, 1);

        PB_deleteRoi = new QPushButton(widget);
        PB_deleteRoi->setObjectName(QStringLiteral("PB_deleteRoi"));
        sizePolicy4.setHeightForWidth(PB_deleteRoi->sizePolicy().hasHeightForWidth());
        PB_deleteRoi->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(PB_deleteRoi, 1, 0, 1, 1);

        PB_addRoi = new QPushButton(widget);
        PB_addRoi->setObjectName(QStringLiteral("PB_addRoi"));
        sizePolicy4.setHeightForWidth(PB_addRoi->sizePolicy().hasHeightForWidth());
        PB_addRoi->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(PB_addRoi, 0, 0, 1, 1);

        PB_refArea = new QPushButton(widget);
        PB_refArea->setObjectName(QStringLiteral("PB_refArea"));
        PB_refArea->setCheckable(true);

        gridLayout_5->addWidget(PB_refArea, 5, 0, 1, 1);

        PB_measure = new QPushButton(widget);
        PB_measure->setObjectName(QStringLiteral("PB_measure"));

        gridLayout_5->addWidget(PB_measure, 7, 0, 1, 1);

        PB_renameRoi = new QPushButton(widget);
        PB_renameRoi->setObjectName(QStringLiteral("PB_renameRoi"));
        sizePolicy4.setHeightForWidth(PB_renameRoi->sizePolicy().hasHeightForWidth());
        PB_renameRoi->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(PB_renameRoi, 2, 0, 1, 1);

        gB_RoiSelection = new QGroupBox(ProcessingTools);
        gB_RoiSelection->setObjectName(QStringLiteral("gB_RoiSelection"));
        gB_RoiSelection->setGeometry(QRect(9, 9, 371, 135));
        sizePolicy.setHeightForWidth(gB_RoiSelection->sizePolicy().hasHeightForWidth());
        gB_RoiSelection->setSizePolicy(sizePolicy);
        L_RoiType = new QLabel(gB_RoiSelection);
        L_RoiType->setObjectName(QStringLiteral("L_RoiType"));
        L_RoiType->setGeometry(QRect(17, 25, 100, 16));
        pb_rectROI = new QPushButton(gB_RoiSelection);
        pb_rectROI->setObjectName(QStringLiteral("pb_rectROI"));
        pb_rectROI->setGeometry(QRect(10, 50, 112, 36));
        sizePolicy.setHeightForWidth(pb_rectROI->sizePolicy().hasHeightForWidth());
        pb_rectROI->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/logos/rectangular-geometrical-shape-outline.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_rectROI->setIcon(icon1);
        pb_rectROI->setIconSize(QSize(32, 32));
        pb_rectROI->setCheckable(true);
        pb_rectROI->setAutoExclusive(false);
        pb_reset_4 = new QPushButton(gB_RoiSelection);
        pb_reset_4->setObjectName(QStringLiteral("pb_reset_4"));
        pb_reset_4->setEnabled(true);
        pb_reset_4->setGeometry(QRect(10, 90, 351, 36));
        sizePolicy3.setHeightForWidth(pb_reset_4->sizePolicy().hasHeightForWidth());
        pb_reset_4->setSizePolicy(sizePolicy3);
        pb_ellipseROI = new QPushButton(gB_RoiSelection);
        pb_ellipseROI->setObjectName(QStringLiteral("pb_ellipseROI"));
        pb_ellipseROI->setGeometry(QRect(130, 50, 112, 36));
        sizePolicy.setHeightForWidth(pb_ellipseROI->sizePolicy().hasHeightForWidth());
        pb_ellipseROI->setSizePolicy(sizePolicy);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/logos/ellipse-vector-format.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_ellipseROI->setIcon(icon2);
        pb_ellipseROI->setIconSize(QSize(32, 32));
        pb_ellipseROI->setCheckable(true);
        pb_ellipseROI->setAutoExclusive(false);
        pb_freeROI = new QPushButton(gB_RoiSelection);
        pb_freeROI->setObjectName(QStringLiteral("pb_freeROI"));
        pb_freeROI->setGeometry(QRect(250, 50, 112, 36));
        sizePolicy.setHeightForWidth(pb_freeROI->sizePolicy().hasHeightForWidth());
        pb_freeROI->setSizePolicy(sizePolicy);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/logos/irregular-line-of-straight-lines-and-angles.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_freeROI->setIcon(icon3);
        pb_freeROI->setIconSize(QSize(32, 32));
        pb_freeROI->setCheckable(true);
        pb_freeROI->setAutoExclusive(false);
        gB_ImageSettings = new QGroupBox(ProcessingTools);
        gB_ImageSettings->setObjectName(QStringLiteral("gB_ImageSettings"));
        gB_ImageSettings->setGeometry(QRect(9, 148, 371, 131));
        sizePolicy1.setHeightForWidth(gB_ImageSettings->sizePolicy().hasHeightForWidth());
        gB_ImageSettings->setSizePolicy(sizePolicy1);
        opacitySlider = new QSlider(gB_ImageSettings);
        opacitySlider->setObjectName(QStringLiteral("opacitySlider"));
        opacitySlider->setGeometry(QRect(74, 110, 190, 19));
        opacitySlider->setOrientation(Qt::Horizontal);
        opacityLabel = new QLabel(gB_ImageSettings);
        opacityLabel->setObjectName(QStringLiteral("opacityLabel"));
        opacityLabel->setGeometry(QRect(17, 110, 51, 16));
        horizontalSlider_contrast_min = new QSlider(gB_ImageSettings);
        horizontalSlider_contrast_min->setObjectName(QStringLiteral("horizontalSlider_contrast_min"));
        horizontalSlider_contrast_min->setGeometry(QRect(74, 85, 190, 19));
        sizePolicy4.setHeightForWidth(horizontalSlider_contrast_min->sizePolicy().hasHeightForWidth());
        horizontalSlider_contrast_min->setSizePolicy(sizePolicy4);
        horizontalSlider_contrast_min->setOrientation(Qt::Horizontal);
        horizontalSlider_contrast = new QSlider(gB_ImageSettings);
        horizontalSlider_contrast->setObjectName(QStringLiteral("horizontalSlider_contrast"));
        horizontalSlider_contrast->setGeometry(QRect(74, 60, 190, 19));
        sizePolicy4.setHeightForWidth(horizontalSlider_contrast->sizePolicy().hasHeightForWidth());
        horizontalSlider_contrast->setSizePolicy(sizePolicy4);
        horizontalSlider_contrast->setOrientation(Qt::Horizontal);
        l_contrast_2 = new QLabel(gB_ImageSettings);
        l_contrast_2->setObjectName(QStringLiteral("l_contrast_2"));
        l_contrast_2->setGeometry(QRect(17, 61, 30, 16));
        sizePolicy.setHeightForWidth(l_contrast_2->sizePolicy().hasHeightForWidth());
        l_contrast_2->setSizePolicy(sizePolicy);
        l_contrast_3 = new QLabel(gB_ImageSettings);
        l_contrast_3->setObjectName(QStringLiteral("l_contrast_3"));
        l_contrast_3->setGeometry(QRect(17, 86, 27, 16));
        sizePolicy.setHeightForWidth(l_contrast_3->sizePolicy().hasHeightForWidth());
        l_contrast_3->setSizePolicy(sizePolicy);
        sB_max = new QDoubleSpinBox(gB_ImageSettings);
        sB_max->setObjectName(QStringLiteral("sB_max"));
        sB_max->setGeometry(QRect(270, 60, 92, 19));
        sB_min = new QDoubleSpinBox(gB_ImageSettings);
        sB_min->setObjectName(QStringLiteral("sB_min"));
        sB_min->setGeometry(QRect(270, 85, 92, 19));
        layoutWidget1 = new QWidget(gB_ImageSettings);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(18, 30, 209, 28));
        gridLayout_4 = new QGridLayout(layoutWidget1);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        L_choosecM = new QLabel(layoutWidget1);
        L_choosecM->setObjectName(QStringLiteral("L_choosecM"));
        sizePolicy.setHeightForWidth(L_choosecM->sizePolicy().hasHeightForWidth());
        L_choosecM->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(L_choosecM, 0, 0, 1, 1);

        CB_colormaps = new QComboBox(layoutWidget1);
        CB_colormaps->addItem(QString());
        CB_colormaps->addItem(QString());
        CB_colormaps->addItem(QString());
        CB_colormaps->addItem(QString());
        CB_colormaps->addItem(QString());
        CB_colormaps->setObjectName(QStringLiteral("CB_colormaps"));
        sizePolicy4.setHeightForWidth(CB_colormaps->sizePolicy().hasHeightForWidth());
        CB_colormaps->setSizePolicy(sizePolicy4);

        gridLayout_4->addWidget(CB_colormaps, 0, 1, 1, 1);

        gB_SaveSection_2 = new QGroupBox(ProcessingTools);
        gB_SaveSection_2->setObjectName(QStringLiteral("gB_SaveSection_2"));
        gB_SaveSection_2->setGeometry(QRect(717, 170, 501, 111));
        sizePolicy3.setHeightForWidth(gB_SaveSection_2->sizePolicy().hasHeightForWidth());
        gB_SaveSection_2->setSizePolicy(sizePolicy3);
        gridLayout_8 = new QGridLayout(gB_SaveSection_2);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        l_something = new QLabel(gB_SaveSection_2);
        l_something->setObjectName(QStringLiteral("l_something"));
        sizePolicy.setHeightForWidth(l_something->sizePolicy().hasHeightForWidth());
        l_something->setSizePolicy(sizePolicy);

        gridLayout_7->addWidget(l_something, 3, 2, 1, 1);

        l_contrast_6 = new QLabel(gB_SaveSection_2);
        l_contrast_6->setObjectName(QStringLiteral("l_contrast_6"));
        sizePolicy.setHeightForWidth(l_contrast_6->sizePolicy().hasHeightForWidth());
        l_contrast_6->setSizePolicy(sizePolicy);

        gridLayout_7->addWidget(l_contrast_6, 1, 2, 1, 1);

        l_AnimalID = new QLabel(gB_SaveSection_2);
        l_AnimalID->setObjectName(QStringLiteral("l_AnimalID"));

        gridLayout_7->addWidget(l_AnimalID, 3, 1, 1, 1);

        l_contrast_5 = new QLabel(gB_SaveSection_2);
        l_contrast_5->setObjectName(QStringLiteral("l_contrast_5"));
        sizePolicy.setHeightForWidth(l_contrast_5->sizePolicy().hasHeightForWidth());
        l_contrast_5->setSizePolicy(sizePolicy);

        gridLayout_7->addWidget(l_contrast_5, 4, 0, 1, 1);

        l_contrast_7 = new QLabel(gB_SaveSection_2);
        l_contrast_7->setObjectName(QStringLiteral("l_contrast_7"));
        sizePolicy.setHeightForWidth(l_contrast_7->sizePolicy().hasHeightForWidth());
        l_contrast_7->setSizePolicy(sizePolicy);

        gridLayout_7->addWidget(l_contrast_7, 3, 0, 1, 1);

        l_contrast_4 = new QLabel(gB_SaveSection_2);
        l_contrast_4->setObjectName(QStringLiteral("l_contrast_4"));
        sizePolicy.setHeightForWidth(l_contrast_4->sizePolicy().hasHeightForWidth());
        l_contrast_4->setSizePolicy(sizePolicy);

        gridLayout_7->addWidget(l_contrast_4, 1, 0, 1, 1);

        l_InjectDateTime = new QLabel(gB_SaveSection_2);
        l_InjectDateTime->setObjectName(QStringLiteral("l_InjectDateTime"));

        gridLayout_7->addWidget(l_InjectDateTime, 3, 3, 1, 1);

        l_Name = new QLabel(gB_SaveSection_2);
        l_Name->setObjectName(QStringLiteral("l_Name"));

        gridLayout_7->addWidget(l_Name, 4, 1, 1, 1);

        l_StudID = new QLabel(gB_SaveSection_2);
        l_StudID->setObjectName(QStringLiteral("l_StudID"));

        gridLayout_7->addWidget(l_StudID, 1, 1, 1, 1);

        l_injectiveAct = new QLabel(gB_SaveSection_2);
        l_injectiveAct->setObjectName(QStringLiteral("l_injectiveAct"));
        sizePolicy.setHeightForWidth(l_injectiveAct->sizePolicy().hasHeightForWidth());
        l_injectiveAct->setSizePolicy(sizePolicy);

        gridLayout_7->addWidget(l_injectiveAct, 4, 2, 1, 1);

        l_InjectAct = new QLabel(gB_SaveSection_2);
        l_InjectAct->setObjectName(QStringLiteral("l_InjectAct"));

        gridLayout_7->addWidget(l_InjectAct, 4, 3, 1, 1);

        l_Radio = new QLabel(gB_SaveSection_2);
        l_Radio->setObjectName(QStringLiteral("l_Radio"));

        gridLayout_7->addWidget(l_Radio, 1, 3, 1, 1);


        gridLayout_8->addLayout(gridLayout_7, 0, 0, 1, 1);

        TW_procTools->addTab(ProcessingTools, QString());
        StudyInfo = new QWidget();
        StudyInfo->setObjectName(QStringLiteral("StudyInfo"));
        sizePolicy2.setHeightForWidth(StudyInfo->sizePolicy().hasHeightForWidth());
        StudyInfo->setSizePolicy(sizePolicy2);
        L_Age = new QLabel(StudyInfo);
        L_Age->setObjectName(QStringLiteral("L_Age"));
        L_Age->setGeometry(QRect(10, 131, 51, 20));
        rb_mCi = new QRadioButton(StudyInfo);
        rb_mCi->setObjectName(QStringLiteral("rb_mCi"));
        rb_mCi->setGeometry(QRect(911, 250, 47, 20));
        rb_mCi->setFocusPolicy(Qt::ClickFocus);
        rb_mCi->setCheckable(false);
        rb_mCi->setAutoExclusive(true);
        L_StudyDate = new QLabel(StudyInfo);
        L_StudyDate->setObjectName(QStringLiteral("L_StudyDate"));
        L_StudyDate->setGeometry(QRect(10, 71, 91, 20));
        LE_age = new QLineEdit(StudyInfo);
        LE_age->setObjectName(QStringLiteral("LE_age"));
        LE_age->setGeometry(QRect(120, 131, 161, 20));
        LE_age->setReadOnly(true);
        L_breed = new QLabel(StudyInfo);
        L_breed->setObjectName(QStringLiteral("L_breed"));
        L_breed->setGeometry(QRect(9, 161, 71, 20));
        LE_p_name = new QLineEdit(StudyInfo);
        LE_p_name->setObjectName(QStringLiteral("LE_p_name"));
        LE_p_name->setGeometry(QRect(121, 101, 161, 20));
        LE_p_name->setReadOnly(true);
        L_species = new QLabel(StudyInfo);
        L_species->setObjectName(QStringLiteral("L_species"));
        L_species->setGeometry(QRect(320, 161, 131, 20));
        L_studyID = new QLabel(StudyInfo);
        L_studyID->setObjectName(QStringLiteral("L_studyID"));
        L_studyID->setGeometry(QRect(10, 31, 111, 20));
        L_animalMarking = new QLabel(StudyInfo);
        L_animalMarking->setObjectName(QStringLiteral("L_animalMarking"));
        L_animalMarking->setGeometry(QRect(320, 101, 151, 20));
        L_InitActivity = new QLabel(StudyInfo);
        L_InitActivity->setObjectName(QStringLiteral("L_InitActivity"));
        L_InitActivity->setGeometry(QRect(681, 250, 111, 20));
        LE_species = new QLineEdit(StudyInfo);
        LE_species->setObjectName(QStringLiteral("LE_species"));
        LE_species->setGeometry(QRect(461, 161, 181, 20));
        LE_species->setReadOnly(true);
        L_InjPath = new QLabel(StudyInfo);
        L_InjPath->setObjectName(QStringLiteral("L_InjPath"));
        L_InjPath->setGeometry(QRect(950, 221, 111, 20));
        rb_mBq_2 = new QRadioButton(StudyInfo);
        rb_mBq_2->setObjectName(QStringLiteral("rb_mBq_2"));
        rb_mBq_2->setGeometry(QRect(851, 250, 53, 20));
        rb_mBq_2->setMouseTracking(true);
        rb_mBq_2->setFocusPolicy(Qt::ClickFocus);
        rb_mBq_2->setCheckable(false);
        rb_mBq_2->setAutoExclusive(true);
        LE_strain = new QLineEdit(StudyInfo);
        LE_strain->setObjectName(QStringLiteral("LE_strain"));
        LE_strain->setGeometry(QRect(121, 161, 161, 20));
        LE_strain->setReadOnly(true);
        L_AnimalID = new QLabel(StudyInfo);
        L_AnimalID->setObjectName(QStringLiteral("L_AnimalID"));
        L_AnimalID->setGeometry(QRect(10, 101, 91, 20));
        dE_studyDate = new QDateEdit(StudyInfo);
        dE_studyDate->setObjectName(QStringLiteral("dE_studyDate"));
        dE_studyDate->setGeometry(QRect(120, 71, 161, 20));
        QFont font1;
        font1.setPointSize(9);
        dE_studyDate->setFont(font1);
        dE_studyDate->setFocusPolicy(Qt::ClickFocus);
        dE_studyDate->setContextMenuPolicy(Qt::DefaultContextMenu);
        dE_studyDate->setFrame(true);
        dE_studyDate->setReadOnly(true);
        dE_studyDate->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 0, 0)));
        dE_studyDate->setCalendarPopup(false);
        L_radioNuclide = new QLabel(StudyInfo);
        L_radioNuclide->setObjectName(QStringLiteral("L_radioNuclide"));
        L_radioNuclide->setGeometry(QRect(10, 221, 111, 20));
        L_weight = new QLabel(StudyInfo);
        L_weight->setObjectName(QStringLiteral("L_weight"));
        L_weight->setGeometry(QRect(320, 131, 131, 20));
        LE_weight = new QLineEdit(StudyInfo);
        LE_weight->setObjectName(QStringLiteral("LE_weight"));
        LE_weight->setGeometry(QRect(461, 131, 181, 20));
        LE_weight->setReadOnly(true);
        L_InjDate = new QLabel(StudyInfo);
        L_InjDate->setObjectName(QStringLiteral("L_InjDate"));
        L_InjDate->setGeometry(QRect(320, 251, 151, 20));
        L_RadioPharma = new QLabel(StudyInfo);
        L_RadioPharma->setObjectName(QStringLiteral("L_RadioPharma"));
        L_RadioPharma->setGeometry(QRect(320, 221, 181, 20));
        LE_SName = new QLineEdit(StudyInfo);
        LE_SName->setObjectName(QStringLiteral("LE_SName"));
        LE_SName->setGeometry(QRect(460, 31, 181, 20));
        LE_SName->setFrame(true);
        LE_SName->setReadOnly(true);
        le_marking = new QLineEdit(StudyInfo);
        le_marking->setObjectName(QStringLiteral("le_marking"));
        le_marking->setGeometry(QRect(461, 101, 181, 20));
        le_marking->setReadOnly(true);
        L_studyName = new QLabel(StudyInfo);
        L_studyName->setObjectName(QStringLiteral("L_studyName"));
        L_studyName->setGeometry(QRect(320, 31, 141, 20));
        LE_r_pharma = new QLineEdit(StudyInfo);
        LE_r_pharma->setObjectName(QStringLiteral("LE_r_pharma"));
        LE_r_pharma->setGeometry(QRect(461, 221, 181, 20));
        LE_r_pharma->setReadOnly(true);
        dTime_ingection = new QDateTimeEdit(StudyInfo);
        dTime_ingection->setObjectName(QStringLiteral("dTime_ingection"));
        dTime_ingection->setGeometry(QRect(460, 251, 181, 20));
        dTime_ingection->setFont(font1);
        dTime_ingection->setFocusPolicy(Qt::ClickFocus);
        dTime_ingection->setReadOnly(true);
        dTime_ingection->setCalendarPopup(false);
        LE_studyID = new QLineEdit(StudyInfo);
        LE_studyID->setObjectName(QStringLiteral("LE_studyID"));
        LE_studyID->setGeometry(QRect(120, 31, 161, 20));
        LE_studyID->setFrame(false);
        LE_studyID->setReadOnly(true);
        dSB_activity = new QDoubleSpinBox(StudyInfo);
        dSB_activity->setObjectName(QStringLiteral("dSB_activity"));
        dSB_activity->setGeometry(QRect(771, 250, 69, 20));
        dSB_activity->setReadOnly(true);
        dSB_activity->setMaximum(1e+08);
        L_project = new QLabel(StudyInfo);
        L_project->setObjectName(QStringLiteral("L_project"));
        L_project->setGeometry(QRect(320, 71, 141, 20));
        CB_radioNuclide = new QComboBox(StudyInfo);
        CB_radioNuclide->setObjectName(QStringLiteral("CB_radioNuclide"));
        CB_radioNuclide->setGeometry(QRect(120, 221, 161, 20));
        CB_radioNuclide->setMaxVisibleItems(50);
        CB_ing_path = new QComboBox(StudyInfo);
        CB_ing_path->setObjectName(QStringLiteral("CB_ing_path"));
        CB_ing_path->setGeometry(QRect(1060, 221, 151, 20));
        CB_ing_path->setMaxVisibleItems(50);
        L_InjActivity = new QLabel(StudyInfo);
        L_InjActivity->setObjectName(QStringLiteral("L_InjActivity"));
        L_InjActivity->setGeometry(QRect(680, 221, 131, 20));
        LE_project = new QLineEdit(StudyInfo);
        LE_project->setObjectName(QStringLiteral("LE_project"));
        LE_project->setGeometry(QRect(461, 71, 181, 20));
        LE_project->setFrame(true);
        LE_project->setReadOnly(true);
        TE_comments = new QTextEdit(StudyInfo);
        TE_comments->setObjectName(QStringLiteral("TE_comments"));
        TE_comments->setGeometry(QRect(680, 131, 531, 71));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(TE_comments->sizePolicy().hasHeightForWidth());
        TE_comments->setSizePolicy(sizePolicy5);
        TE_comments->setReadOnly(true);
        L_comments = new QLabel(StudyInfo);
        L_comments->setObjectName(QStringLiteral("L_comments"));
        L_comments->setGeometry(QRect(680, 101, 122, 17));
        sizePolicy.setHeightForWidth(L_comments->sizePolicy().hasHeightForWidth());
        L_comments->setSizePolicy(sizePolicy);
        rb_male = new QRadioButton(StudyInfo);
        rb_male->setObjectName(QStringLiteral("rb_male"));
        rb_male->setGeometry(QRect(140, 192, 39, 20));
        rb_male->setMouseTracking(false);
        rb_male->setFocusPolicy(Qt::ClickFocus);
        rb_male->setCheckable(false);
        rb_male->setAutoExclusive(true);
        L_gender = new QLabel(StudyInfo);
        L_gender->setObjectName(QStringLiteral("L_gender"));
        L_gender->setGeometry(QRect(10, 191, 71, 20));
        rb_female = new QRadioButton(StudyInfo);
        rb_female->setObjectName(QStringLiteral("rb_female"));
        rb_female->setGeometry(QRect(180, 192, 34, 20));
        rb_female->setMouseTracking(false);
        rb_female->setFocusPolicy(Qt::ClickFocus);
        rb_female->setCheckable(false);
        rb_female->setAutoExclusive(true);
        dSB_volume = new QDoubleSpinBox(StudyInfo);
        dSB_volume->setObjectName(QStringLiteral("dSB_volume"));
        dSB_volume->setGeometry(QRect(118, 251, 91, 20));
        dSB_volume->setReadOnly(true);
        dSB_volume->setMaximum(1e+08);
        L_InjVol = new QLabel(StudyInfo);
        L_InjVol->setObjectName(QStringLiteral("L_InjVol"));
        L_InjVol->setGeometry(QRect(10, 251, 131, 20));
        L_ul = new QLabel(StudyInfo);
        L_ul->setObjectName(QStringLiteral("L_ul"));
        L_ul->setGeometry(QRect(220, 251, 16, 20));
        rB_fDynamic = new QRadioButton(StudyInfo);
        rB_fDynamic->setObjectName(QStringLiteral("rB_fDynamic"));
        rB_fDynamic->setGeometry(QRect(680, 61, 281, 20));
        rB_fDynamic->setCheckable(false);
        l_frame = new QLabel(StudyInfo);
        l_frame->setObjectName(QStringLiteral("l_frame"));
        l_frame->setGeometry(QRect(960, 31, 131, 21));
        LE_frame = new QLineEdit(StudyInfo);
        LE_frame->setObjectName(QStringLiteral("LE_frame"));
        LE_frame->setGeometry(QRect(1100, 31, 111, 20));
        LE_frame->setReadOnly(true);
        LE_expDuration = new QLineEdit(StudyInfo);
        LE_expDuration->setObjectName(QStringLiteral("LE_expDuration"));
        LE_expDuration->setGeometry(QRect(821, 31, 121, 20));
        LE_expDuration->setReadOnly(true);
        L_Duration = new QLabel(StudyInfo);
        L_Duration->setObjectName(QStringLiteral("L_Duration"));
        L_Duration->setGeometry(QRect(680, 31, 121, 20));
        LE_mod = new QLineEdit(StudyInfo);
        LE_mod->setObjectName(QStringLiteral("LE_mod"));
        LE_mod->setGeometry(QRect(1060, 251, 151, 20));
        LE_mod->setReadOnly(true);
        label = new QLabel(StudyInfo);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(979, 249, 111, 20));
        label_2 = new QLabel(StudyInfo);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(320, 191, 131, 17));
        dSB_injActivity = new QLineEdit(StudyInfo);
        dSB_injActivity->setObjectName(QStringLiteral("dSB_injActivity"));
        dSB_injActivity->setGeometry(QRect(810, 221, 121, 20));
        dSB_injActivity->setReadOnly(true);
        dTE_aqTime = new QLineEdit(StudyInfo);
        dTE_aqTime->setObjectName(QStringLiteral("dTE_aqTime"));
        dTE_aqTime->setGeometry(QRect(460, 191, 181, 20));
        dTE_aqTime->setReadOnly(true);
        TW_procTools->addTab(StudyInfo, QString());
        LE_studyID->raise();
        L_Age->raise();
        rb_mCi->raise();
        L_StudyDate->raise();
        LE_age->raise();
        L_breed->raise();
        LE_p_name->raise();
        L_species->raise();
        L_studyID->raise();
        L_animalMarking->raise();
        L_InitActivity->raise();
        LE_species->raise();
        L_InjPath->raise();
        rb_mBq_2->raise();
        LE_strain->raise();
        L_AnimalID->raise();
        dE_studyDate->raise();
        L_radioNuclide->raise();
        L_weight->raise();
        LE_weight->raise();
        L_InjDate->raise();
        L_RadioPharma->raise();
        LE_SName->raise();
        le_marking->raise();
        L_studyName->raise();
        LE_r_pharma->raise();
        dTime_ingection->raise();
        dSB_activity->raise();
        L_project->raise();
        CB_radioNuclide->raise();
        CB_ing_path->raise();
        L_InjActivity->raise();
        LE_project->raise();
        TE_comments->raise();
        L_comments->raise();
        rb_male->raise();
        L_gender->raise();
        rb_female->raise();
        dSB_volume->raise();
        L_InjVol->raise();
        L_ul->raise();
        rB_fDynamic->raise();
        l_frame->raise();
        LE_frame->raise();
        LE_expDuration->raise();
        L_Duration->raise();
        LE_mod->raise();
        label->raise();
        label_2->raise();
        dSB_injActivity->raise();
        dTE_aqTime->raise();
        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(670, 0, 571, 321));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(630, 0, 31, 31));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/icons/letter-r-48.png")));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(630, 260, 31, 31));
        label_3->setFrameShape(QFrame::NoFrame);
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/icons/letter-l-48.png")));
        horizontalScrollBar_2 = new QScrollBar(centralwidget);
        horizontalScrollBar_2->setObjectName(QStringLiteral("horizontalScrollBar_2"));
        horizontalScrollBar_2->setGeometry(QRect(10, 320, 581, 20));
        horizontalScrollBar_2->setOrientation(Qt::Horizontal);
        tB_playStack = new QToolButton(centralwidget);
        tB_playStack->setObjectName(QStringLiteral("tB_playStack"));
        tB_playStack->setGeometry(QRect(10, 320, 24, 23));
        cB_selection = new QCheckBox(centralwidget);
        cB_selection->setObjectName(QStringLiteral("cB_selection"));
        cB_selection->setGeometry(QRect(10, 290, 241, 31));
        cB_fusion = new QCheckBox(centralwidget);
        cB_fusion->setObjectName(QStringLiteral("cB_fusion"));
        cB_fusion->setGeometry(QRect(360, 290, 121, 31));
        radioButtonAcivityPerROI = new QRadioButton(centralwidget);
        radioButtonAcivityPerROI->setObjectName(QStringLiteral("radioButtonAcivityPerROI"));
        radioButtonAcivityPerROI->setGeometry(QRect(990, 340, 131, 23));
        radioButtonCountsPerROI = new QRadioButton(centralwidget);
        radioButtonCountsPerROI->setObjectName(QStringLiteral("radioButtonCountsPerROI"));
        radioButtonCountsPerROI->setGeometry(QRect(820, 340, 151, 23));
        cB_xray = new QCheckBox(centralwidget);
        cB_xray->setObjectName(QStringLiteral("cB_xray"));
        cB_xray->setGeometry(QRect(500, 290, 91, 31));
        layoutWidget3 = new QWidget(centralwidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 0, 621, 291));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        PostProcessing->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PostProcessing);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1250, 24));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        PostProcessing->setMenuBar(menubar);
        statusbar = new QStatusBar(PostProcessing);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        PostProcessing->setStatusBar(statusbar);
        QWidget::setTabOrder(cB_selection, cB_fusion);
        QWidget::setTabOrder(cB_fusion, tB_playStack);
        QWidget::setTabOrder(tB_playStack, TW_procTools);
        QWidget::setTabOrder(TW_procTools, pb_rectROI);
        QWidget::setTabOrder(pb_rectROI, pb_ellipseROI);
        QWidget::setTabOrder(pb_ellipseROI, pb_freeROI);
        QWidget::setTabOrder(pb_freeROI, pb_reset_4);
        QWidget::setTabOrder(pb_reset_4, CB_colormaps);
        QWidget::setTabOrder(CB_colormaps, horizontalSlider_contrast);
        QWidget::setTabOrder(horizontalSlider_contrast, ROI_list);
        QWidget::setTabOrder(ROI_list, PB_addRoi);
        QWidget::setTabOrder(PB_addRoi, PB_deleteRoi);
        QWidget::setTabOrder(PB_deleteRoi, PB_renameRoi);
        QWidget::setTabOrder(PB_renameRoi, PB_updatePos);
        QWidget::setTabOrder(PB_updatePos, PB_ShowLabels);
        QWidget::setTabOrder(PB_ShowLabels, PB_refArea);
        QWidget::setTabOrder(PB_refArea, PB_showRois);
        QWidget::setTabOrder(PB_showRois, PB_measure);
        QWidget::setTabOrder(PB_measure, PB_plotRois);
        QWidget::setTabOrder(PB_plotRois, PB_saveAs);
        QWidget::setTabOrder(PB_saveAs, PB_savePlot);
        QWidget::setTabOrder(PB_savePlot, PB_plot_excel);
        QWidget::setTabOrder(PB_plot_excel, PB_dicomViewer);
        QWidget::setTabOrder(PB_dicomViewer, LE_studyID);
        QWidget::setTabOrder(LE_studyID, LE_p_name);
        QWidget::setTabOrder(LE_p_name, LE_age);
        QWidget::setTabOrder(LE_age, LE_strain);
        QWidget::setTabOrder(LE_strain, CB_radioNuclide);
        QWidget::setTabOrder(CB_radioNuclide, dSB_volume);
        QWidget::setTabOrder(dSB_volume, LE_SName);
        QWidget::setTabOrder(LE_SName, LE_project);
        QWidget::setTabOrder(LE_project, le_marking);
        QWidget::setTabOrder(le_marking, LE_weight);
        QWidget::setTabOrder(LE_weight, LE_species);
        QWidget::setTabOrder(LE_species, LE_r_pharma);
        QWidget::setTabOrder(LE_r_pharma, rB_fDynamic);
        QWidget::setTabOrder(rB_fDynamic, TE_comments);
        QWidget::setTabOrder(TE_comments, LE_expDuration);
        QWidget::setTabOrder(LE_expDuration, LE_frame);
        QWidget::setTabOrder(LE_frame, dSB_activity);
        QWidget::setTabOrder(dSB_activity, CB_ing_path);
        QWidget::setTabOrder(CB_ing_path, LE_mod);

        menubar->addAction(menuOptions->menuAction());
        menuOptions->addAction(action_loadStudy);
        menuOptions->addAction(actionLoad_Last_Study_2);
        menuOptions->addAction(actionExit_to_Main_Menu);

        retranslateUi(PostProcessing);

        TW_procTools->setCurrentIndex(0);
        CB_colormaps->setCurrentIndex(0);
        CB_radioNuclide->setCurrentIndex(-1);
        CB_ing_path->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(PostProcessing);
    } // setupUi

    void retranslateUi(QMainWindow *PostProcessing)
    {
        PostProcessing->setWindowTitle(QApplication::translate("PostProcessing", "VISUAL-eyes", nullptr));
        action_loadStudy->setText(QApplication::translate("PostProcessing", "Load Study ...", nullptr));
        actionExit_to_Main_Menu->setText(QApplication::translate("PostProcessing", "Exit to Main Menu ...", nullptr));
        actionLoad_Last_Study->setText(QApplication::translate("PostProcessing", "Load Last Study ... ", nullptr));
        actionLoad_Last_Study_2->setText(QApplication::translate("PostProcessing", "Load Last Study ...", nullptr));
        gB_SaveSection->setTitle(QApplication::translate("PostProcessing", "Reporting", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_saveAs->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Saves a single frame.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_saveAs->setText(QApplication::translate("PostProcessing", "Save Frame As..", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_plot_excel->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Saves the data for the ROIs in the ROI list. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_plot_excel->setText(QApplication::translate("PostProcessing", "Export data (Excel)", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_saveAllFrames->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Saves all frames. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_saveAllFrames->setText(QApplication::translate("PostProcessing", "Save All Frames As", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_saveSelected->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Saves selected frames. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_saveSelected->setText(QApplication::translate("PostProcessing", "Save Selected Frames", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_savePlot->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Saves the plot. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_savePlot->setText(QApplication::translate("PostProcessing", "Save Plot As..", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_dicomViewer->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Opens a DICOM viewer (if available). </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_dicomViewer->setText(QApplication::translate("PostProcessing", "Open DICOM Viewer", nullptr));
        PB_merge->setText(QApplication::translate("PostProcessing", "Merge frames", nullptr));
        PB_pdfReport->setText(QApplication::translate("PostProcessing", "Save Pdf report", nullptr));
        gB_ROIManager->setTitle(QApplication::translate("PostProcessing", "ROI Manager", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_updatePos->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to update the position of a ROI that has been moved. This should be pressed every time after moving a ROI.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_updatePos->setText(QApplication::translate("PostProcessing", "Update position", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_ShowLabels->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to see the labels of the ROIs.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_ShowLabels->setText(QApplication::translate("PostProcessing", "Show labels", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_showRois->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to hide/see all ROIs. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_showRois->setText(QApplication::translate("PostProcessing", "Hide ROIs", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_plotRois->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to plot the ROIs in the list. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_plotRois->setText(QApplication::translate("PostProcessing", "Plot ROIs", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_deleteRoi->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to delete a ROI from the list.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_deleteRoi->setText(QApplication::translate("PostProcessing", "Delete", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_addRoi->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to add a ROI in the list.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_addRoi->setText(QApplication::translate("PostProcessing", "Add ROI", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_refArea->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to make a selected ROI  Reference Area. Double click to deselect the ROI from being Reference Area. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_refArea->setText(QApplication::translate("PostProcessing", "Set reference area", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_measure->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to see details  of a selected ROI.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_measure->setText(QApplication::translate("PostProcessing", "Measure", nullptr));
#ifndef QT_NO_TOOLTIP
        PB_renameRoi->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to rename a selected ROI from the list. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_renameRoi->setText(QApplication::translate("PostProcessing", "Rename", nullptr));
        gB_RoiSelection->setTitle(QApplication::translate("PostProcessing", "ROI Selection", nullptr));
        L_RoiType->setText(QApplication::translate("PostProcessing", "Select ROI Type:", nullptr));
#ifndef QT_NO_TOOLTIP
        pb_rectROI->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to select a rectangular ROI in the image. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        pb_rectROI->setText(QApplication::translate("PostProcessing", "rect", nullptr));
#ifndef QT_NO_TOOLTIP
        pb_reset_4->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to reset. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        pb_reset_4->setText(QApplication::translate("PostProcessing", "Reset", nullptr));
#ifndef QT_NO_TOOLTIP
        pb_ellipseROI->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to select a ellipsoid ROI in the image. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        pb_ellipseROI->setText(QApplication::translate("PostProcessing", "EllipseROI", nullptr));
#ifndef QT_NO_TOOLTIP
        pb_freeROI->setToolTip(QApplication::translate("PostProcessing", "<html><head/><body><p>Press to draw an arbitrary ROI in the image. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        pb_freeROI->setText(QApplication::translate("PostProcessing", "Draw", nullptr));
        gB_ImageSettings->setTitle(QApplication::translate("PostProcessing", "Image Settings", nullptr));
        opacityLabel->setText(QApplication::translate("PostProcessing", "Opacity:", nullptr));
        l_contrast_2->setText(QApplication::translate("PostProcessing", "Max:", nullptr));
        l_contrast_3->setText(QApplication::translate("PostProcessing", "Min:", nullptr));
        L_choosecM->setText(QApplication::translate("PostProcessing", "Choose ColorMap:", nullptr));
        CB_colormaps->setItemText(0, QApplication::translate("PostProcessing", "GrayScale", nullptr));
        CB_colormaps->setItemText(1, QApplication::translate("PostProcessing", "Royal", nullptr));
        CB_colormaps->setItemText(2, QApplication::translate("PostProcessing", "Jet", nullptr));
        CB_colormaps->setItemText(3, QApplication::translate("PostProcessing", "Red Hot", nullptr));
        CB_colormaps->setItemText(4, QApplication::translate("PostProcessing", "Smart", nullptr));

        gB_SaveSection_2->setTitle(QApplication::translate("PostProcessing", "Study info", nullptr));
        l_something->setText(QApplication::translate("PostProcessing", "Injected date-time:", nullptr));
        l_contrast_6->setText(QApplication::translate("PostProcessing", "Radionuclide:", nullptr));
        l_AnimalID->setText(QApplication::translate("PostProcessing", "-", nullptr));
        l_contrast_5->setText(QApplication::translate("PostProcessing", "Name:", nullptr));
        l_contrast_7->setText(QApplication::translate("PostProcessing", "Animal ID:", nullptr));
        l_contrast_4->setText(QApplication::translate("PostProcessing", "Study ID:", nullptr));
        l_InjectDateTime->setText(QApplication::translate("PostProcessing", "-", nullptr));
        l_Name->setText(QApplication::translate("PostProcessing", "-", nullptr));
        l_StudID->setText(QApplication::translate("PostProcessing", "-", nullptr));
        l_injectiveAct->setText(QApplication::translate("PostProcessing", "Injected activity:", nullptr));
        l_InjectAct->setText(QApplication::translate("PostProcessing", "-", nullptr));
        l_Radio->setText(QApplication::translate("PostProcessing", "-", nullptr));
        TW_procTools->setTabText(TW_procTools->indexOf(ProcessingTools), QApplication::translate("PostProcessing", "Processing Tools", nullptr));
        L_Age->setText(QApplication::translate("PostProcessing", "Age:", nullptr));
        rb_mCi->setText(QApplication::translate("PostProcessing", "\316\274Ci", nullptr));
        L_StudyDate->setText(QApplication::translate("PostProcessing", "Study Date:", nullptr));
        L_breed->setText(QApplication::translate("PostProcessing", "Breed:", nullptr));
        L_species->setText(QApplication::translate("PostProcessing", "Species:", nullptr));
        L_studyID->setText(QApplication::translate("PostProcessing", "Study ID:", nullptr));
        L_animalMarking->setText(QApplication::translate("PostProcessing", "Animal Marking:", nullptr));
        L_InitActivity->setText(QApplication::translate("PostProcessing", "Initial Activity:", nullptr));
        L_InjPath->setText(QApplication::translate("PostProcessing", "Injection Path:", nullptr));
        rb_mBq_2->setText(QApplication::translate("PostProcessing", "MBq", nullptr));
        L_AnimalID->setText(QApplication::translate("PostProcessing", "Animal ID:", nullptr));
        L_radioNuclide->setText(QApplication::translate("PostProcessing", "Radionuclide:", nullptr));
        L_weight->setText(QApplication::translate("PostProcessing", "Weight:", nullptr));
        L_InjDate->setText(QApplication::translate("PostProcessing", "Injection Date-Time:", nullptr));
        L_RadioPharma->setText(QApplication::translate("PostProcessing", "Radiopharmaceutical:", nullptr));
        L_studyName->setText(QApplication::translate("PostProcessing", "Study Name:", nullptr));
        L_project->setText(QApplication::translate("PostProcessing", "Project:", nullptr));
        L_InjActivity->setText(QApplication::translate("PostProcessing", "Injected Activity:", nullptr));
        L_comments->setText(QApplication::translate("PostProcessing", "Comments:", nullptr));
        rb_male->setText(QApplication::translate("PostProcessing", "M", nullptr));
        L_gender->setText(QApplication::translate("PostProcessing", "Gender:", nullptr));
        rb_female->setText(QApplication::translate("PostProcessing", "F", nullptr));
        L_InjVol->setText(QApplication::translate("PostProcessing", "Injected volume:", nullptr));
        L_ul->setText(QApplication::translate("PostProcessing", "ul", nullptr));
        rB_fDynamic->setText(QApplication::translate("PostProcessing", "Dynamic Frame Time Protocol", nullptr));
        l_frame->setText(QApplication::translate("PostProcessing", "Frame Duration:", nullptr));
        L_Duration->setText(QApplication::translate("PostProcessing", "Exp.  Duration:", nullptr));
        label->setText(QApplication::translate("PostProcessing", "Modality:", nullptr));
        label_2->setText(QApplication::translate("PostProcessing", "Acq. Time:", nullptr));
        TW_procTools->setTabText(TW_procTools->indexOf(StudyInfo), QApplication::translate("PostProcessing", "Study Information", nullptr));
        label_4->setText(QString());
        label_3->setText(QString());
        tB_playStack->setText(QString());
        cB_selection->setText(QString());
        cB_fusion->setText(QApplication::translate("PostProcessing", "Optical fusion", nullptr));
        radioButtonAcivityPerROI->setText(QApplication::translate("PostProcessing", "Activity per ROI", nullptr));
        radioButtonCountsPerROI->setText(QApplication::translate("PostProcessing", "Counts/min per ROI", nullptr));
        cB_xray->setText(QApplication::translate("PostProcessing", "Xray fusion", nullptr));
        menuOptions->setTitle(QApplication::translate("PostProcessing", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PostProcessing: public Ui_PostProcessing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSTPROCESSING_H
