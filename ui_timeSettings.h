/********************************************************************************
** Form generated from reading UI file 'timeSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMESETTINGS_H
#define UI_TIMESETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_timeSettings
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;
    QRadioButton *rb_userDefined;
    QRadioButton *rb_studyProt;
    QComboBox *cB_expTime_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *cb_frameUnit;
    QLabel *label_41;
    QSpinBox *sB_duration;
    QSpinBox *sB_frame;
    QComboBox *cb_expUnit;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_3;
    QPushButton *PB_prev;
    QPushButton *PB_ok;

    void setupUi(QDialog *timeSettings)
    {
        if (timeSettings->objectName().isEmpty())
            timeSettings->setObjectName(QStringLiteral("timeSettings"));
        timeSettings->resize(321, 211);
        QFont font;
        font.setPointSize(10);
        timeSettings->setFont(font);
        gridLayout_5 = new QGridLayout(timeSettings);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        groupBox = new QGroupBox(timeSettings);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        rb_userDefined = new QRadioButton(groupBox);
        rb_userDefined->setObjectName(QStringLiteral("rb_userDefined"));
        rb_userDefined->setAutoExclusive(false);

        gridLayout_2->addWidget(rb_userDefined, 0, 0, 1, 1);

        rb_studyProt = new QRadioButton(groupBox);
        rb_studyProt->setObjectName(QStringLiteral("rb_studyProt"));

        gridLayout_2->addWidget(rb_studyProt, 1, 0, 1, 1);

        cB_expTime_2 = new QComboBox(groupBox);
        cB_expTime_2->setObjectName(QStringLiteral("cB_expTime_2"));

        gridLayout_2->addWidget(cB_expTime_2, 1, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cb_frameUnit = new QComboBox(groupBox);
        cb_frameUnit->setObjectName(QStringLiteral("cb_frameUnit"));
        cb_frameUnit->setInsertPolicy(QComboBox::InsertAtCurrent);
        cb_frameUnit->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        cb_frameUnit->setFrame(true);

        gridLayout->addWidget(cb_frameUnit, 1, 2, 1, 1);

        label_41 = new QLabel(groupBox);
        label_41->setObjectName(QStringLiteral("label_41"));

        gridLayout->addWidget(label_41, 1, 0, 1, 1);

        sB_duration = new QSpinBox(groupBox);
        sB_duration->setObjectName(QStringLiteral("sB_duration"));
        sB_duration->setMaximum(3600);
        sB_duration->setSingleStep(10);

        gridLayout->addWidget(sB_duration, 0, 1, 1, 1);

        sB_frame = new QSpinBox(groupBox);
        sB_frame->setObjectName(QStringLiteral("sB_frame"));
        sB_frame->setMaximum(3600);
        sB_frame->setSingleStep(10);

        gridLayout->addWidget(sB_frame, 1, 1, 1, 1);

        cb_expUnit = new QComboBox(groupBox);
        cb_expUnit->setObjectName(QStringLiteral("cb_expUnit"));
        cb_expUnit->setInsertPolicy(QComboBox::InsertAtCurrent);
        cb_expUnit->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        cb_expUnit->setFrame(true);

        gridLayout->addWidget(cb_expUnit, 0, 2, 1, 1);


        gridLayout_4->addLayout(gridLayout, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(140, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        PB_prev = new QPushButton(timeSettings);
        PB_prev->setObjectName(QStringLiteral("PB_prev"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/if_Back_32435.png"), QSize(), QIcon::Normal, QIcon::Off);
        PB_prev->setIcon(icon);

        gridLayout_3->addWidget(PB_prev, 0, 0, 1, 1);

        PB_ok = new QPushButton(timeSettings);
        PB_ok->setObjectName(QStringLiteral("PB_ok"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/check.png"), QSize(), QIcon::Normal, QIcon::Off);
        PB_ok->setIcon(icon1);

        gridLayout_3->addWidget(PB_ok, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_3, 1, 1, 1, 1);

        QWidget::setTabOrder(rb_userDefined, rb_studyProt);
        QWidget::setTabOrder(rb_studyProt, cB_expTime_2);
        QWidget::setTabOrder(cB_expTime_2, sB_duration);
        QWidget::setTabOrder(sB_duration, cb_expUnit);
        QWidget::setTabOrder(cb_expUnit, sB_frame);
        QWidget::setTabOrder(sB_frame, cb_frameUnit);
        QWidget::setTabOrder(cb_frameUnit, PB_prev);
        QWidget::setTabOrder(PB_prev, PB_ok);

        retranslateUi(timeSettings);

        cb_frameUnit->setCurrentIndex(-1);
        cb_expUnit->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(timeSettings);
    } // setupUi

    void retranslateUi(QDialog *timeSettings)
    {
        timeSettings->setWindowTitle(QApplication::translate("timeSettings", "Study details", nullptr));
        groupBox->setTitle(QApplication::translate("timeSettings", "Time protocol", nullptr));
#ifndef QT_NO_TOOLTIP
        rb_userDefined->setToolTip(QApplication::translate("timeSettings", "<html><head/><body><p>Select to set the &quot;Experiment duration&quot; and the &quot;Save frame every&quot; entries manually.  </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rb_userDefined->setText(QApplication::translate("timeSettings", "User defined", nullptr));
#ifndef QT_NO_TOOLTIP
        rb_studyProt->setToolTip(QApplication::translate("timeSettings", "<html><head/><body><p>Select to use a predifined experimental protocol. Two choises are available: </p><p>i) Dynamic: The &quot;Experiment duartion&quot; is 60 min and the frames are saved every 120 sec.</p><p>ii) Fast dynamic:   The &quot;Experiment duartion&quot; is 60 min and the frames are saved from 0 to 1 min every  10 sec,  0 to 5 min every 30 sec, 5 to 10 min every 60 sec and 10 to 60 min every 120 sec</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        rb_studyProt->setText(QApplication::translate("timeSettings", "Study protocol:", nullptr));
        label->setText(QApplication::translate("timeSettings", "Experiment duration:", nullptr));
#ifndef QT_NO_TOOLTIP
        cb_frameUnit->setToolTip(QApplication::translate("timeSettings", "<html><head/><body><p>Select between units. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_41->setText(QApplication::translate("timeSettings", "Save frame every:", nullptr));
#ifndef QT_NO_TOOLTIP
        sB_duration->setToolTip(QApplication::translate("timeSettings", "<html><head/><body><p>The exprimental time. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sB_frame->setToolTip(QApplication::translate("timeSettings", "<html><head/><body><p>The time step that a frame wiil be saved. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        cb_expUnit->setToolTip(QApplication::translate("timeSettings", "<html><head/><body><p>Select between units. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        PB_prev->setText(QApplication::translate("timeSettings", " Back", nullptr));
        PB_ok->setText(QApplication::translate("timeSettings", "Finish", nullptr));
    } // retranslateUi

};

namespace Ui {
    class timeSettings: public Ui_timeSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMESETTINGS_H
