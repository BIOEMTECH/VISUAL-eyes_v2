/********************************************************************************
** Form generated from reading UI file 'calibrationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATIONDIALOG_H
#define UI_CALIBRATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
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

class Ui_calibrationDialog
{
public:
    QGridLayout *gridLayout_13;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_12;
    QPushButton *PB_previous;
    QPushButton *PB_next;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_10;
    QPushButton *PB_clear;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_8;
    QCheckBox *cb_calibration;
    QFrame *line_3;
    QDoubleSpinBox *dSB_volume;
    QLineEdit *LE_studyID;
    QWidget *widget_2;
    QGridLayout *gridLayout_4;
    QRadioButton *rb_mCi_2;
    QRadioButton *rb_mBq_2;
    QLabel *label;
    QDoubleSpinBox *dSB_activity;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_22;
    QLabel *label_33;
    QLabel *label_32;
    QCheckBox *cb_validation;
    QLabel *label1;
    QTextEdit *TE_comments;
    QComboBox *CB_radioNuclide;
    QLabel *label_35;
    QDateTimeEdit *dTime_ingection;
    QLabel *lb_collimator;
    QComboBox *cB_collimator;

    void setupUi(QDialog *calibrationDialog)
    {
        if (calibrationDialog->objectName().isEmpty())
            calibrationDialog->setObjectName(QStringLiteral("calibrationDialog"));
        calibrationDialog->resize(480, 520);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(calibrationDialog->sizePolicy().hasHeightForWidth());
        calibrationDialog->setSizePolicy(sizePolicy);
        calibrationDialog->setMaximumSize(QSize(480, 520));
        QFont font;
        font.setPointSize(10);
        calibrationDialog->setFont(font);
        gridLayout_13 = new QGridLayout(calibrationDialog);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        horizontalSpacer = new QSpacerItem(500, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_13->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        PB_previous = new QPushButton(calibrationDialog);
        PB_previous->setObjectName(QStringLiteral("PB_previous"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/if_Back_32435.png"), QSize(), QIcon::Normal, QIcon::Off);
        PB_previous->setIcon(icon);

        gridLayout_12->addWidget(PB_previous, 0, 0, 1, 1);

        PB_next = new QPushButton(calibrationDialog);
        PB_next->setObjectName(QStringLiteral("PB_next"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/if_Next_32435.png"), QSize(), QIcon::Normal, QIcon::Off);
        PB_next->setIcon(icon1);

        gridLayout_12->addWidget(PB_next, 0, 1, 1, 1);


        gridLayout_13->addLayout(gridLayout_12, 1, 1, 1, 1);

        groupBox = new QGroupBox(calibrationDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_10 = new QGridLayout(groupBox);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        PB_clear = new QPushButton(groupBox);
        PB_clear->setObjectName(QStringLiteral("PB_clear"));

        gridLayout_10->addWidget(PB_clear, 2, 0, 1, 2);

        groupBox_4 = new QGroupBox(groupBox);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_9 = new QGridLayout(groupBox_4);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        cb_calibration = new QCheckBox(groupBox_4);
        cb_calibration->setObjectName(QStringLiteral("cb_calibration"));

        gridLayout_8->addWidget(cb_calibration, 2, 3, 1, 1);

        line_3 = new QFrame(groupBox_4);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line_3, 0, 0, 1, 4);

        dSB_volume = new QDoubleSpinBox(groupBox_4);
        dSB_volume->setObjectName(QStringLiteral("dSB_volume"));
        dSB_volume->setMaximum(10000);

        gridLayout_8->addWidget(dSB_volume, 8, 2, 1, 1);

        LE_studyID = new QLineEdit(groupBox_4);
        LE_studyID->setObjectName(QStringLiteral("LE_studyID"));
        LE_studyID->setEnabled(false);

        gridLayout_8->addWidget(LE_studyID, 3, 2, 1, 1);

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


        gridLayout_8->addWidget(widget_2, 9, 3, 1, 1);

        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_8->addWidget(label, 2, 0, 1, 2);

        dSB_activity = new QDoubleSpinBox(groupBox_4);
        dSB_activity->setObjectName(QStringLiteral("dSB_activity"));
        dSB_activity->setMaximum(10000);

        gridLayout_8->addWidget(dSB_activity, 9, 2, 1, 1);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_8->addWidget(label_7, 10, 0, 1, 1);

        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_8->addWidget(label_6, 8, 3, 1, 1);

        label_22 = new QLabel(groupBox_4);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout_8->addWidget(label_22, 4, 0, 1, 1);

        label_33 = new QLabel(groupBox_4);
        label_33->setObjectName(QStringLiteral("label_33"));

        gridLayout_8->addWidget(label_33, 8, 0, 1, 1);

        label_32 = new QLabel(groupBox_4);
        label_32->setObjectName(QStringLiteral("label_32"));

        gridLayout_8->addWidget(label_32, 6, 0, 1, 1);

        cb_validation = new QCheckBox(groupBox_4);
        cb_validation->setObjectName(QStringLiteral("cb_validation"));

        gridLayout_8->addWidget(cb_validation, 2, 2, 1, 1);

        label1 = new QLabel(groupBox_4);
        label1->setObjectName(QStringLiteral("label1"));

        gridLayout_8->addWidget(label1, 3, 0, 1, 1);

        TE_comments = new QTextEdit(groupBox_4);
        TE_comments->setObjectName(QStringLiteral("TE_comments"));

        gridLayout_8->addWidget(TE_comments, 11, 0, 1, 4);

        CB_radioNuclide = new QComboBox(groupBox_4);
        CB_radioNuclide->setObjectName(QStringLiteral("CB_radioNuclide"));

        gridLayout_8->addWidget(CB_radioNuclide, 6, 2, 1, 1);

        label_35 = new QLabel(groupBox_4);
        label_35->setObjectName(QStringLiteral("label_35"));

        gridLayout_8->addWidget(label_35, 9, 0, 1, 2);

        dTime_ingection = new QDateTimeEdit(groupBox_4);
        dTime_ingection->setObjectName(QStringLiteral("dTime_ingection"));
        dTime_ingection->setFocusPolicy(Qt::ClickFocus);
        dTime_ingection->setCalendarPopup(true);

        gridLayout_8->addWidget(dTime_ingection, 4, 2, 1, 1);

        lb_collimator = new QLabel(groupBox_4);
        lb_collimator->setObjectName(QStringLiteral("lb_collimator"));

        gridLayout_8->addWidget(lb_collimator, 5, 0, 1, 1);

        cB_collimator = new QComboBox(groupBox_4);
        cB_collimator->setObjectName(QStringLiteral("cB_collimator"));

        gridLayout_8->addWidget(cB_collimator, 5, 2, 1, 1);


        gridLayout_9->addLayout(gridLayout_8, 0, 0, 1, 1);


        gridLayout_10->addWidget(groupBox_4, 1, 0, 1, 2);


        gridLayout_13->addWidget(groupBox, 0, 0, 1, 2);

        QWidget::setTabOrder(CB_radioNuclide, dSB_volume);
        QWidget::setTabOrder(dSB_volume, dSB_activity);
        QWidget::setTabOrder(dSB_activity, TE_comments);
        QWidget::setTabOrder(TE_comments, PB_clear);
        QWidget::setTabOrder(PB_clear, PB_previous);
        QWidget::setTabOrder(PB_previous, PB_next);

        retranslateUi(calibrationDialog);

        QMetaObject::connectSlotsByName(calibrationDialog);
    } // setupUi

    void retranslateUi(QDialog *calibrationDialog)
    {
        calibrationDialog->setWindowTitle(QApplication::translate("calibrationDialog", "Study details", nullptr));
        PB_previous->setText(QApplication::translate("calibrationDialog", " Back", nullptr));
        PB_next->setText(QApplication::translate("calibrationDialog", "Next", nullptr));
        groupBox->setTitle(QString());
        PB_clear->setText(QApplication::translate("calibrationDialog", "Clear all fields", nullptr));
        groupBox_4->setTitle(QApplication::translate("calibrationDialog", "Info", nullptr));
        cb_calibration->setText(QApplication::translate("calibrationDialog", "Calibration", nullptr));
#ifndef QT_NO_TOOLTIP
        dSB_volume->setToolTip(QApplication::translate("calibrationDialog", "<html><head/><body><p>The volume of the enjected radio nuclide. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        LE_studyID->setToolTip(QApplication::translate("calibrationDialog", "<html><head/><body><p>The ID of the experiment is given automatically by the software and is used for storing it in the database.  </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rb_mCi_2->setText(QApplication::translate("calibrationDialog", "\316\274Ci", nullptr));
        rb_mBq_2->setText(QApplication::translate("calibrationDialog", "MBq", nullptr));
        label->setText(QApplication::translate("calibrationDialog", "Type of study:", nullptr));
#ifndef QT_NO_TOOLTIP
        dSB_activity->setToolTip(QApplication::translate("calibrationDialog", "<html><head/><body><p>The activity as measured after the injection. The value is used to calculate the decay correction. If the value is zero, the decay will not be taken into account. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("calibrationDialog", "Comments:", nullptr));
        label_6->setText(QApplication::translate("calibrationDialog", "ul", nullptr));
        label_22->setText(QApplication::translate("calibrationDialog", "Date/time:", nullptr));
        label_33->setText(QApplication::translate("calibrationDialog", "Flood volume:", nullptr));
        label_32->setText(QApplication::translate("calibrationDialog", "Radionuclide:", nullptr));
        cb_validation->setText(QApplication::translate("calibrationDialog", "Validation", nullptr));
        label1->setText(QApplication::translate("calibrationDialog", "ID:", nullptr));
#ifndef QT_NO_TOOLTIP
        TE_comments->setToolTip(QApplication::translate("calibrationDialog", "<html><head/><body><p><span style=\" font-family:'Sans Serif';\">Set any comments relevant to this experiment.</span></p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        TE_comments->setHtml(QApplication::translate("calibrationDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
#ifndef QT_NO_TOOLTIP
        CB_radioNuclide->setToolTip(QApplication::translate("calibrationDialog", "<html><head/><body><p>The radio nuclide used in the experiment. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_35->setToolTip(QApplication::translate("calibrationDialog", "<html><head/><body><p>The value of the injected activity as computed after the injection. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_35->setText(QApplication::translate("calibrationDialog", "Flood activity:", nullptr));
#ifndef QT_NO_TOOLTIP
        dTime_ingection->setToolTip(QApplication::translate("calibrationDialog", "<html><head/><body><p>The injection date/time. Injection time is used to compute the time for the decay correction. Note that in order to account for the decay correction the &quot;Injection activity&quot; must be different than zero.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        lb_collimator->setText(QApplication::translate("calibrationDialog", "Collimator:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class calibrationDialog: public Ui_calibrationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONDIALOG_H
