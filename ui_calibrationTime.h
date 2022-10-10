/********************************************************************************
** Form generated from reading UI file 'calibrationTime.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATIONTIME_H
#define UI_CALIBRATIONTIME_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_calibrationTime
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QComboBox *cb_expUnit;
    QSpinBox *sB_duration;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_3;
    QPushButton *PB_prev;
    QPushButton *PB_ok;

    void setupUi(QDialog *calibrationTime)
    {
        if (calibrationTime->objectName().isEmpty())
            calibrationTime->setObjectName(QStringLiteral("calibrationTime"));
        calibrationTime->resize(321, 128);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(calibrationTime->sizePolicy().hasHeightForWidth());
        calibrationTime->setSizePolicy(sizePolicy);
        calibrationTime->setMinimumSize(QSize(321, 128));
        calibrationTime->setMaximumSize(QSize(321, 128));
        QFont font;
        font.setPointSize(10);
        calibrationTime->setFont(font);
        gridLayout_5 = new QGridLayout(calibrationTime);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        groupBox = new QGroupBox(calibrationTime);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));

        gridLayout_4->addLayout(gridLayout_2, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cb_expUnit = new QComboBox(groupBox);
        cb_expUnit->setObjectName(QStringLiteral("cb_expUnit"));
        cb_expUnit->setInsertPolicy(QComboBox::InsertAtCurrent);
        cb_expUnit->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        cb_expUnit->setFrame(true);

        gridLayout->addWidget(cb_expUnit, 0, 2, 1, 1);

        sB_duration = new QSpinBox(groupBox);
        sB_duration->setObjectName(QStringLiteral("sB_duration"));
        sB_duration->setMaximum(3600);
        sB_duration->setSingleStep(10);

        gridLayout->addWidget(sB_duration, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(140, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        PB_prev = new QPushButton(calibrationTime);
        PB_prev->setObjectName(QStringLiteral("PB_prev"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/if_Back_32435.png"), QSize(), QIcon::Normal, QIcon::Off);
        PB_prev->setIcon(icon);

        gridLayout_3->addWidget(PB_prev, 0, 0, 1, 1);

        PB_ok = new QPushButton(calibrationTime);
        PB_ok->setObjectName(QStringLiteral("PB_ok"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/check.png"), QSize(), QIcon::Normal, QIcon::Off);
        PB_ok->setIcon(icon1);

        gridLayout_3->addWidget(PB_ok, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_3, 1, 1, 1, 1);

        QWidget::setTabOrder(sB_duration, cb_expUnit);
        QWidget::setTabOrder(cb_expUnit, PB_prev);
        QWidget::setTabOrder(PB_prev, PB_ok);

        retranslateUi(calibrationTime);

        cb_expUnit->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(calibrationTime);
    } // setupUi

    void retranslateUi(QDialog *calibrationTime)
    {
        calibrationTime->setWindowTitle(QApplication::translate("calibrationTime", "Study details", nullptr));
        groupBox->setTitle(QApplication::translate("calibrationTime", "Time protocol", nullptr));
#ifndef QT_NO_TOOLTIP
        cb_expUnit->setToolTip(QApplication::translate("calibrationTime", "<html><head/><body><p>Select between units. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sB_duration->setToolTip(QApplication::translate("calibrationTime", "<html><head/><body><p>The exprimental time. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("calibrationTime", "Experiment duration:", nullptr));
        PB_prev->setText(QApplication::translate("calibrationTime", " Back", nullptr));
        PB_ok->setText(QApplication::translate("calibrationTime", "Finish", nullptr));
    } // retranslateUi

};

namespace Ui {
    class calibrationTime: public Ui_calibrationTime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONTIME_H
