/********************************************************************************
** Form generated from reading UI file 'PlotSelector.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTSELECTOR_H
#define UI_PLOTSELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_PlotSelector
{
public:
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QRadioButton *radioButtonEnergetic;
    QLabel *label;
    QFrame *line;
    QRadioButton *radioButtonCountPerMin;

    void setupUi(QDialog *PlotSelector)
    {
        if (PlotSelector->objectName().isEmpty())
            PlotSelector->setObjectName(QStringLiteral("PlotSelector"));
        PlotSelector->resize(197, 122);
        gridLayout_2 = new QGridLayout(PlotSelector);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        frame = new QFrame(PlotSelector);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioButtonEnergetic = new QRadioButton(frame);
        radioButtonEnergetic->setObjectName(QStringLiteral("radioButtonEnergetic"));

        gridLayout->addWidget(radioButtonEnergetic, 3, 0, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        line = new QFrame(frame);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 2, 0, 1, 1);

        radioButtonCountPerMin = new QRadioButton(frame);
        radioButtonCountPerMin->setObjectName(QStringLiteral("radioButtonCountPerMin"));

        gridLayout->addWidget(radioButtonCountPerMin, 4, 0, 1, 1);


        gridLayout_2->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(PlotSelector);

        QMetaObject::connectSlotsByName(PlotSelector);
    } // setupUi

    void retranslateUi(QDialog *PlotSelector)
    {
        PlotSelector->setWindowTitle(QApplication::translate("PlotSelector", "Dialog", nullptr));
        radioButtonEnergetic->setText(QApplication::translate("PlotSelector", "Energetic", nullptr));
        label->setText(QApplication::translate("PlotSelector", "Show plot for:", nullptr));
        radioButtonCountPerMin->setText(QApplication::translate("PlotSelector", "Counts/min per ROI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlotSelector: public Ui_PlotSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTSELECTOR_H
