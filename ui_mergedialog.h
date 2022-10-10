/********************************************************************************
** Form generated from reading UI file 'mergedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MERGEDIALOG_H
#define UI_MERGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mergeDialog
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QComboBox *cB_convFactor;
    QLabel *label_3;
    QPushButton *pB_cancel;
    QPushButton *pB_ok;

    void setupUi(QDialog *mergeDialog)
    {
        if (mergeDialog->objectName().isEmpty())
            mergeDialog->setObjectName(QStringLiteral("mergeDialog"));
        mergeDialog->resize(300, 50);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mergeDialog->sizePolicy().hasHeightForWidth());
        mergeDialog->setSizePolicy(sizePolicy);
        mergeDialog->setMaximumSize(QSize(300, 50));
        widget = new QWidget(mergeDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 282, 27));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        cB_convFactor = new QComboBox(widget);
        cB_convFactor->setObjectName(QStringLiteral("cB_convFactor"));

        gridLayout->addWidget(cB_convFactor, 0, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        pB_cancel = new QPushButton(widget);
        pB_cancel->setObjectName(QStringLiteral("pB_cancel"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_cancel->setIcon(icon);

        gridLayout->addWidget(pB_cancel, 0, 3, 1, 1);

        pB_ok = new QPushButton(widget);
        pB_ok->setObjectName(QStringLiteral("pB_ok"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/check.png"), QSize(), QIcon::Normal, QIcon::Off);
        pB_ok->setIcon(icon1);

        gridLayout->addWidget(pB_ok, 0, 4, 1, 1);


        retranslateUi(mergeDialog);

        QMetaObject::connectSlotsByName(mergeDialog);
    } // setupUi

    void retranslateUi(QDialog *mergeDialog)
    {
        mergeDialog->setWindowTitle(QApplication::translate("mergeDialog", "Merge Frames", nullptr));
        label_2->setText(QApplication::translate("mergeDialog", "Merge to ", nullptr));
        label_3->setText(QApplication::translate("mergeDialog", "frames", nullptr));
        pB_cancel->setText(QString());
        pB_ok->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class mergeDialog: public Ui_mergeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MERGEDIALOG_H
