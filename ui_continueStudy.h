/********************************************************************************
** Form generated from reading UI file 'continueStudy.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTINUESTUDY_H
#define UI_CONTINUESTUDY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_continueStudy
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *PB_restart;
    QPushButton *PB_Exit;
    QPushButton *PB_InitiateStudy;

    void setupUi(QDialog *continueStudy)
    {
        if (continueStudy->objectName().isEmpty())
            continueStudy->setObjectName(QStringLiteral("continueStudy"));
        continueStudy->resize(242, 149);
        QFont font;
        font.setPointSize(10);
        continueStudy->setFont(font);
        gridLayout_2 = new QGridLayout(continueStudy);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox = new QGroupBox(continueStudy);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        PB_restart = new QPushButton(groupBox);
        PB_restart->setObjectName(QStringLiteral("PB_restart"));

        gridLayout->addWidget(PB_restart, 1, 0, 1, 1);

        PB_Exit = new QPushButton(groupBox);
        PB_Exit->setObjectName(QStringLiteral("PB_Exit"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/logos/211686-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        PB_Exit->setIcon(icon);

        gridLayout->addWidget(PB_Exit, 2, 0, 1, 1);

        PB_InitiateStudy = new QPushButton(groupBox);
        PB_InitiateStudy->setObjectName(QStringLiteral("PB_InitiateStudy"));
        PB_InitiateStudy->setIcon(icon);

        gridLayout->addWidget(PB_InitiateStudy, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        QWidget::setTabOrder(PB_InitiateStudy, PB_restart);
        QWidget::setTabOrder(PB_restart, PB_Exit);

        retranslateUi(continueStudy);

        QMetaObject::connectSlotsByName(continueStudy);
    } // setupUi

    void retranslateUi(QDialog *continueStudy)
    {
        continueStudy->setWindowTitle(QApplication::translate("continueStudy", "VISUAL-Eyes", nullptr));
        groupBox->setTitle(QString());
        PB_restart->setText(QApplication::translate("continueStudy", "Repeat same study", nullptr));
        PB_Exit->setText(QApplication::translate("continueStudy", "Exit", nullptr));
        PB_InitiateStudy->setText(QApplication::translate("continueStudy", "Continue to next study", nullptr));
    } // retranslateUi

};

namespace Ui {
    class continueStudy: public Ui_continueStudy {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTINUESTUDY_H
