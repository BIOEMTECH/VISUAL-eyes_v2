/********************************************************************************
** Form generated from reading UI file 'calibrationExit.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATIONEXIT_H
#define UI_CALIBRATIONEXIT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_calibrationExit
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *PB_Exit;

    void setupUi(QDialog *calibrationExit)
    {
        if (calibrationExit->objectName().isEmpty())
            calibrationExit->setObjectName(QStringLiteral("calibrationExit"));
        calibrationExit->resize(532, 48);
        QFont font;
        font.setPointSize(10);
        calibrationExit->setFont(font);
        widget = new QWidget(calibrationExit);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(11, 10, 511, 29));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        PB_Exit = new QPushButton(widget);
        PB_Exit->setObjectName(QStringLiteral("PB_Exit"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/logos/211686-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        PB_Exit->setIcon(icon);

        gridLayout->addWidget(PB_Exit, 0, 2, 1, 1);


        retranslateUi(calibrationExit);

        QMetaObject::connectSlotsByName(calibrationExit);
    } // setupUi

    void retranslateUi(QDialog *calibrationExit)
    {
        calibrationExit->setWindowTitle(QApplication::translate("calibrationExit", "CALIBRATE-Eyes", nullptr));
        label->setText(QApplication::translate("calibrationExit", "Calibration files have been updated successfully! Please press exit.", nullptr));
        PB_Exit->setText(QApplication::translate("calibrationExit", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class calibrationExit: public Ui_calibrationExit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONEXIT_H
