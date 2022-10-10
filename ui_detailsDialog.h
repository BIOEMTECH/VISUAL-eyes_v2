/********************************************************************************
** Form generated from reading UI file 'detailsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETAILSDIALOG_H
#define UI_DETAILSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_detailsDialog
{
public:
    QGridLayout *gridLayout_13;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_10;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_8;
    QLabel *label_35;
    QLabel *label_4;
    QLabel *label_6;
    QWidget *widget_2;
    QGridLayout *gridLayout_4;
    QRadioButton *rb_mCi_2;
    QRadioButton *rb_mBq_2;
    QDateTimeEdit *dTime_ingection;
    QComboBox *CB_radioNuclide;
    QLabel *label_39;
    QDoubleSpinBox *dSB_injActivity;
    QTextEdit *TE_comments;
    QLabel *label_42;
    QComboBox *CB_ing_path;
    QLabel *label_7;
    QLabel *label_32;
    QDoubleSpinBox *dSB_volume;
    QFrame *line_3;
    QLineEdit *LE_r_pharma;
    QLabel *label_33;
    QLabel *lb_collimator;
    QComboBox *cB_collimator;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_6;
    QFrame *line_2;
    QLabel *label_2;
    QLineEdit *LE_animal_id;
    QLabel *label_3;
    QLineEdit *le_marking;
    QLabel *label_24;
    QLineEdit *LE_breed;
    QLabel *label_5;
    QLineEdit *LE_species;
    QLabel *label_25;
    QWidget *widget_5;
    QGridLayout *gridLayout_2;
    QRadioButton *rb_female;
    QRadioButton *rb_male;
    QLabel *label_26;
    QLineEdit *LE_age;
    QLabel *label_27;
    QLineEdit *LE_weight;
    QLabel *label_9;
    QPushButton *PB_clear;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout;
    QDateEdit *dE_studyDate;
    QLabel *label1;
    QFrame *line;
    QLineEdit *LE_SName;
    QLabel *label_8;
    QLineEdit *LE_project;
    QLabel *label_22;
    QLabel *label;
    QLineEdit *LE_studyID;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_12;
    QPushButton *PB_previous;
    QPushButton *PB_next;

    void setupUi(QDialog *detailsDialog)
    {
        if (detailsDialog->objectName().isEmpty())
            detailsDialog->setObjectName(QStringLiteral("detailsDialog"));
        detailsDialog->resize(699, 587);
        QFont font;
        font.setPointSize(10);
        detailsDialog->setFont(font);
        gridLayout_13 = new QGridLayout(detailsDialog);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        groupBox = new QGroupBox(detailsDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_10 = new QGridLayout(groupBox);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_9 = new QGridLayout(groupBox_4);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        label_35 = new QLabel(groupBox_4);
        label_35->setObjectName(QStringLiteral("label_35"));

        gridLayout_8->addWidget(label_35, 5, 0, 1, 2);

        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_8->addWidget(label_4, 3, 0, 1, 2);

        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_8->addWidget(label_6, 4, 3, 1, 1);

        widget_2 = new QWidget(groupBox_4);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout_4 = new QGridLayout(widget_2);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        rb_mCi_2 = new QRadioButton(widget_2);
        rb_mCi_2->setObjectName(QStringLiteral("rb_mCi_2"));
        rb_mCi_2->setFocusPolicy(Qt::ClickFocus);
        rb_mCi_2->setChecked(true);
        rb_mCi_2->setAutoRepeat(false);
        rb_mCi_2->setAutoExclusive(true);

        gridLayout_4->addWidget(rb_mCi_2, 0, 1, 1, 1);

        rb_mBq_2 = new QRadioButton(widget_2);
        rb_mBq_2->setObjectName(QStringLiteral("rb_mBq_2"));
        rb_mBq_2->setMouseTracking(true);
        rb_mBq_2->setFocusPolicy(Qt::ClickFocus);
        rb_mBq_2->setAutoExclusive(true);

        gridLayout_4->addWidget(rb_mBq_2, 0, 0, 1, 1);


        gridLayout_8->addWidget(widget_2, 5, 3, 1, 1);

        dTime_ingection = new QDateTimeEdit(groupBox_4);
        dTime_ingection->setObjectName(QStringLiteral("dTime_ingection"));
        dTime_ingection->setFocusPolicy(Qt::ClickFocus);
        dTime_ingection->setCalendarPopup(true);

        gridLayout_8->addWidget(dTime_ingection, 6, 2, 1, 2);

        CB_radioNuclide = new QComboBox(groupBox_4);
        CB_radioNuclide->setObjectName(QStringLiteral("CB_radioNuclide"));

        gridLayout_8->addWidget(CB_radioNuclide, 2, 2, 1, 2);

        label_39 = new QLabel(groupBox_4);
        label_39->setObjectName(QStringLiteral("label_39"));

        gridLayout_8->addWidget(label_39, 6, 0, 1, 2);

        dSB_injActivity = new QDoubleSpinBox(groupBox_4);
        dSB_injActivity->setObjectName(QStringLiteral("dSB_injActivity"));
        dSB_injActivity->setMaximum(10000);

        gridLayout_8->addWidget(dSB_injActivity, 5, 2, 1, 1);

        TE_comments = new QTextEdit(groupBox_4);
        TE_comments->setObjectName(QStringLiteral("TE_comments"));

        gridLayout_8->addWidget(TE_comments, 9, 0, 1, 4);

        label_42 = new QLabel(groupBox_4);
        label_42->setObjectName(QStringLiteral("label_42"));

        gridLayout_8->addWidget(label_42, 7, 0, 1, 1);

        CB_ing_path = new QComboBox(groupBox_4);
        CB_ing_path->setObjectName(QStringLiteral("CB_ing_path"));

        gridLayout_8->addWidget(CB_ing_path, 7, 1, 1, 3);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_8->addWidget(label_7, 8, 0, 1, 1);

        label_32 = new QLabel(groupBox_4);
        label_32->setObjectName(QStringLiteral("label_32"));

        gridLayout_8->addWidget(label_32, 2, 0, 1, 2);

        dSB_volume = new QDoubleSpinBox(groupBox_4);
        dSB_volume->setObjectName(QStringLiteral("dSB_volume"));
        dSB_volume->setMaximum(10000);

        gridLayout_8->addWidget(dSB_volume, 4, 2, 1, 1);

        line_3 = new QFrame(groupBox_4);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_3, 0, 0, 1, 4);

        LE_r_pharma = new QLineEdit(groupBox_4);
        LE_r_pharma->setObjectName(QStringLiteral("LE_r_pharma"));

        gridLayout_8->addWidget(LE_r_pharma, 3, 2, 1, 2);

        label_33 = new QLabel(groupBox_4);
        label_33->setObjectName(QStringLiteral("label_33"));

        gridLayout_8->addWidget(label_33, 4, 0, 1, 1);

        lb_collimator = new QLabel(groupBox_4);
        lb_collimator->setObjectName(QStringLiteral("lb_collimator"));

        gridLayout_8->addWidget(lb_collimator, 1, 0, 1, 2);

        cB_collimator = new QComboBox(groupBox_4);
        cB_collimator->setObjectName(QStringLiteral("cB_collimator"));

        gridLayout_8->addWidget(cB_collimator, 1, 2, 1, 2);


        gridLayout_9->addLayout(gridLayout_8, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_4, 0, 1, 3, 1);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_7 = new QGridLayout(groupBox_3);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        line_2 = new QFrame(groupBox_3);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_6->addWidget(line_2, 0, 0, 1, 3);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_6->addWidget(label_2, 1, 0, 1, 1);

        LE_animal_id = new QLineEdit(groupBox_3);
        LE_animal_id->setObjectName(QStringLiteral("LE_animal_id"));

        gridLayout_6->addWidget(LE_animal_id, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_6->addWidget(label_3, 2, 0, 1, 1);

        le_marking = new QLineEdit(groupBox_3);
        le_marking->setObjectName(QStringLiteral("le_marking"));

        gridLayout_6->addWidget(le_marking, 2, 1, 1, 1);

        label_24 = new QLabel(groupBox_3);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_6->addWidget(label_24, 3, 0, 1, 1);

        LE_breed = new QLineEdit(groupBox_3);
        LE_breed->setObjectName(QStringLiteral("LE_breed"));

        gridLayout_6->addWidget(LE_breed, 3, 1, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_6->addWidget(label_5, 4, 0, 1, 1);

        LE_species = new QLineEdit(groupBox_3);
        LE_species->setObjectName(QStringLiteral("LE_species"));

        gridLayout_6->addWidget(LE_species, 4, 1, 1, 1);

        label_25 = new QLabel(groupBox_3);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout_6->addWidget(label_25, 5, 0, 1, 1);

        widget_5 = new QWidget(groupBox_3);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        gridLayout_2 = new QGridLayout(widget_5);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        rb_female = new QRadioButton(widget_5);
        rb_female->setObjectName(QStringLiteral("rb_female"));
        rb_female->setMouseTracking(false);
        rb_female->setFocusPolicy(Qt::ClickFocus);
        rb_female->setChecked(true);
        rb_female->setAutoExclusive(true);

        gridLayout_2->addWidget(rb_female, 0, 1, 1, 1);

        rb_male = new QRadioButton(widget_5);
        rb_male->setObjectName(QStringLiteral("rb_male"));
        rb_male->setMouseTracking(false);
        rb_male->setFocusPolicy(Qt::ClickFocus);
        rb_male->setAutoExclusive(true);

        gridLayout_2->addWidget(rb_male, 0, 0, 1, 1);


        gridLayout_6->addWidget(widget_5, 5, 1, 1, 1);

        label_26 = new QLabel(groupBox_3);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout_6->addWidget(label_26, 6, 0, 1, 1);

        LE_age = new QLineEdit(groupBox_3);
        LE_age->setObjectName(QStringLiteral("LE_age"));

        gridLayout_6->addWidget(LE_age, 6, 1, 1, 1);

        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout_6->addWidget(label_27, 7, 0, 1, 1);

        LE_weight = new QLineEdit(groupBox_3);
        LE_weight->setObjectName(QStringLiteral("LE_weight"));

        gridLayout_6->addWidget(LE_weight, 7, 1, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_6->addWidget(label_9, 7, 2, 1, 1);


        gridLayout_7->addLayout(gridLayout_6, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_3, 2, 0, 1, 1);

        PB_clear = new QPushButton(groupBox);
        PB_clear->setObjectName(QStringLiteral("PB_clear"));

        gridLayout_10->addWidget(PB_clear, 3, 0, 1, 2);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        dE_studyDate = new QDateEdit(groupBox_2);
        dE_studyDate->setObjectName(QStringLiteral("dE_studyDate"));
        dE_studyDate->setFocusPolicy(Qt::ClickFocus);
        dE_studyDate->setContextMenuPolicy(Qt::DefaultContextMenu);
        dE_studyDate->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(0, 0, 0)));
        dE_studyDate->setCalendarPopup(true);

        gridLayout->addWidget(dE_studyDate, 3, 2, 1, 1);

        label1 = new QLabel(groupBox_2);
        label1->setObjectName(QStringLiteral("label1"));

        gridLayout->addWidget(label1, 1, 0, 2, 1);

        line = new QFrame(groupBox_2);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 0, 0, 1, 3);

        LE_SName = new QLineEdit(groupBox_2);
        LE_SName->setObjectName(QStringLiteral("LE_SName"));

        gridLayout->addWidget(LE_SName, 4, 2, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 5, 0, 1, 1);

        LE_project = new QLineEdit(groupBox_2);
        LE_project->setObjectName(QStringLiteral("LE_project"));

        gridLayout->addWidget(LE_project, 5, 2, 1, 1);

        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout->addWidget(label_22, 3, 0, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 4, 0, 1, 1);

        LE_studyID = new QLineEdit(groupBox_2);
        LE_studyID->setObjectName(QStringLiteral("LE_studyID"));
        LE_studyID->setEnabled(false);

        gridLayout->addWidget(LE_studyID, 2, 2, 1, 1);


        gridLayout_5->addLayout(gridLayout, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_2, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer, 1, 0, 1, 1);


        gridLayout_13->addWidget(groupBox, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(500, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_13->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        PB_previous = new QPushButton(detailsDialog);
        PB_previous->setObjectName(QStringLiteral("PB_previous"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/if_Back_32435.png"), QSize(), QIcon::Normal, QIcon::Off);
        PB_previous->setIcon(icon);

        gridLayout_12->addWidget(PB_previous, 0, 0, 1, 1);

        PB_next = new QPushButton(detailsDialog);
        PB_next->setObjectName(QStringLiteral("PB_next"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/if_Next_32435.png"), QSize(), QIcon::Normal, QIcon::Off);
        PB_next->setIcon(icon1);

        gridLayout_12->addWidget(PB_next, 0, 1, 1, 1);


        gridLayout_13->addLayout(gridLayout_12, 1, 1, 1, 1);

        QWidget::setTabOrder(LE_studyID, LE_SName);
        QWidget::setTabOrder(LE_SName, LE_project);
        QWidget::setTabOrder(LE_project, LE_animal_id);
        QWidget::setTabOrder(LE_animal_id, le_marking);
        QWidget::setTabOrder(le_marking, LE_breed);
        QWidget::setTabOrder(LE_breed, LE_species);
        QWidget::setTabOrder(LE_species, LE_age);
        QWidget::setTabOrder(LE_age, LE_weight);
        QWidget::setTabOrder(LE_weight, CB_radioNuclide);
        QWidget::setTabOrder(CB_radioNuclide, LE_r_pharma);
        QWidget::setTabOrder(LE_r_pharma, dSB_volume);
        QWidget::setTabOrder(dSB_volume, dSB_injActivity);
        QWidget::setTabOrder(dSB_injActivity, CB_ing_path);
        QWidget::setTabOrder(CB_ing_path, TE_comments);
        QWidget::setTabOrder(TE_comments, PB_clear);
        QWidget::setTabOrder(PB_clear, PB_previous);
        QWidget::setTabOrder(PB_previous, PB_next);

        retranslateUi(detailsDialog);

        QMetaObject::connectSlotsByName(detailsDialog);
    } // setupUi

    void retranslateUi(QDialog *detailsDialog)
    {
        detailsDialog->setWindowTitle(QApplication::translate("detailsDialog", "Study details", nullptr));
        groupBox->setTitle(QString());
        groupBox_4->setTitle(QApplication::translate("detailsDialog", "Administration info", nullptr));
#ifndef QT_NO_TOOLTIP
        label_35->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The value of the injected activity as computed after the injection. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_35->setText(QApplication::translate("detailsDialog", "Injected activity:", nullptr));
        label_4->setText(QApplication::translate("detailsDialog", "Radiopharmaceutical:", nullptr));
        label_6->setText(QApplication::translate("detailsDialog", "ul", nullptr));
        rb_mCi_2->setText(QApplication::translate("detailsDialog", "\316\274Ci", nullptr));
        rb_mBq_2->setText(QApplication::translate("detailsDialog", "MBq", nullptr));
#ifndef QT_NO_TOOLTIP
        dTime_ingection->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The injection date/time. Injection time is used to compute the time for the decay correction. Note that in order to account for the decay correction the &quot;Injection activity&quot; must be different than zero.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        CB_radioNuclide->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The radio nuclide used in the experiment. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_39->setText(QApplication::translate("detailsDialog", "Injection date/time:", nullptr));
#ifndef QT_NO_TOOLTIP
        dSB_injActivity->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The activity as measured after the injection. The value is used to calculate the decay correction. If the value is zero, the decay will not be taken into account. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        TE_comments->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p><span style=\" font-family:'Sans Serif';\">Set any comments relevant to this experiment.</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        TE_comments->setHtml(QApplication::translate("detailsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label_42->setText(QApplication::translate("detailsDialog", "Injection path:", nullptr));
#ifndef QT_NO_TOOLTIP
        CB_ing_path->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>Select the part of the animal that is the entry point of the injection. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("detailsDialog", "Comments:", nullptr));
        label_32->setText(QApplication::translate("detailsDialog", "Radionuclide:", nullptr));
#ifndef QT_NO_TOOLTIP
        dSB_volume->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The volume of the enjected radio nuclide. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        LE_r_pharma->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The name of the radio pharmaceutical. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_33->setText(QApplication::translate("detailsDialog", "Injected volume:", nullptr));
        lb_collimator->setText(QApplication::translate("detailsDialog", "Collimator:", nullptr));
        groupBox_3->setTitle(QApplication::translate("detailsDialog", "Animal info", nullptr));
        label_2->setText(QApplication::translate("detailsDialog", "ID:", nullptr));
#ifndef QT_NO_TOOLTIP
        LE_animal_id->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The ID of the animal. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("detailsDialog", "Animal marking:", nullptr));
#ifndef QT_NO_TOOLTIP
        le_marking->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The mark of the animal. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_24->setText(QApplication::translate("detailsDialog", "Breed:", nullptr));
#ifndef QT_NO_TOOLTIP
        LE_breed->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The breed of the animal. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("detailsDialog", "Species:", nullptr));
#ifndef QT_NO_TOOLTIP
        LE_species->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The species that the animal participating in the experiment belongs to. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_25->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The gender of the animal.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_25->setText(QApplication::translate("detailsDialog", "Gender:", nullptr));
        rb_female->setText(QApplication::translate("detailsDialog", "F", nullptr));
        rb_male->setText(QApplication::translate("detailsDialog", "M", nullptr));
        label_26->setText(QApplication::translate("detailsDialog", "Age:", nullptr));
#ifndef QT_NO_TOOLTIP
        LE_age->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The age of the animal.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_27->setText(QApplication::translate("detailsDialog", "Weight:", nullptr));
#ifndef QT_NO_TOOLTIP
        LE_weight->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The weight of the animal. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        LE_weight->setText(QString());
        label_9->setText(QApplication::translate("detailsDialog", "gr", nullptr));
        PB_clear->setText(QApplication::translate("detailsDialog", "Clear all fields", nullptr));
        groupBox_2->setTitle(QApplication::translate("detailsDialog", "Study info", nullptr));
#ifndef QT_NO_TOOLTIP
        dE_studyDate->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The date of the experiment. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label1->setText(QApplication::translate("detailsDialog", "ID:", nullptr));
#ifndef QT_NO_TOOLTIP
        LE_SName->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The name of the experiment. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("detailsDialog", "Project:", nullptr));
#ifndef QT_NO_TOOLTIP
        LE_project->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The name of the project that this experiment belongs too. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_22->setText(QApplication::translate("detailsDialog", " Date:", nullptr));
        label->setText(QApplication::translate("detailsDialog", " Name:", nullptr));
#ifndef QT_NO_TOOLTIP
        LE_studyID->setToolTip(QApplication::translate("detailsDialog", "<html><head/><body><p>The ID of the experiment is given automatically by the software and is used for storing it in the database.  </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_previous->setText(QApplication::translate("detailsDialog", " Back", nullptr));
        PB_next->setText(QApplication::translate("detailsDialog", "Next", nullptr));
    } // retranslateUi

};

namespace Ui {
    class detailsDialog: public Ui_detailsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETAILSDIALOG_H
