/********************************************************************************
** Form generated from reading UI file 'operatorDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPERATORDIALOG_H
#define UI_OPERATORDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_operatorDialog
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_47;
    QComboBox *CB_hospital;
    QCheckBox *checkbox_Inst;
    QLineEdit *LE_institute;
    QPushButton *pb_addInst;
    QLabel *label_46;
    QComboBox *CB_phycisian;
    QCheckBox *checkbox_OP;
    QLineEdit *LE_op;
    QPushButton *pb_addOp;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_3;
    QPushButton *PB_cancel;
    QPushButton *PB_next;

    void setupUi(QDialog *operatorDialog)
    {
        if (operatorDialog->objectName().isEmpty())
            operatorDialog->setObjectName(QStringLiteral("operatorDialog"));
        operatorDialog->resize(530, 145);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(operatorDialog->sizePolicy().hasHeightForWidth());
        operatorDialog->setSizePolicy(sizePolicy);
        operatorDialog->setMinimumSize(QSize(530, 145));
        QFont font;
        font.setPointSize(10);
        operatorDialog->setFont(font);
        gridLayout_4 = new QGridLayout(operatorDialog);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox = new QGroupBox(operatorDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_47 = new QLabel(groupBox);
        label_47->setObjectName(QStringLiteral("label_47"));

        gridLayout->addWidget(label_47, 0, 0, 2, 2);

        CB_hospital = new QComboBox(groupBox);
        CB_hospital->setObjectName(QStringLiteral("CB_hospital"));
        CB_hospital->setEditable(false);
        CB_hospital->setMaxVisibleItems(100);
        CB_hospital->setInsertPolicy(QComboBox::InsertAtTop);

        gridLayout->addWidget(CB_hospital, 1, 1, 1, 1);

        checkbox_Inst = new QCheckBox(groupBox);
        checkbox_Inst->setObjectName(QStringLiteral("checkbox_Inst"));

        gridLayout->addWidget(checkbox_Inst, 1, 2, 1, 1);

        LE_institute = new QLineEdit(groupBox);
        LE_institute->setObjectName(QStringLiteral("LE_institute"));
        LE_institute->setEnabled(false);

        gridLayout->addWidget(LE_institute, 1, 3, 1, 1);

        pb_addInst = new QPushButton(groupBox);
        pb_addInst->setObjectName(QStringLiteral("pb_addInst"));
        pb_addInst->setEnabled(false);

        gridLayout->addWidget(pb_addInst, 1, 4, 1, 1);

        label_46 = new QLabel(groupBox);
        label_46->setObjectName(QStringLiteral("label_46"));

        gridLayout->addWidget(label_46, 2, 0, 1, 1);

        CB_phycisian = new QComboBox(groupBox);
        CB_phycisian->setObjectName(QStringLiteral("CB_phycisian"));
        CB_phycisian->setEditable(false);
        CB_phycisian->setMaxVisibleItems(100);
        CB_phycisian->setInsertPolicy(QComboBox::InsertAtTop);

        gridLayout->addWidget(CB_phycisian, 2, 1, 1, 1);

        checkbox_OP = new QCheckBox(groupBox);
        checkbox_OP->setObjectName(QStringLiteral("checkbox_OP"));

        gridLayout->addWidget(checkbox_OP, 2, 2, 1, 1);

        LE_op = new QLineEdit(groupBox);
        LE_op->setObjectName(QStringLiteral("LE_op"));
        LE_op->setEnabled(false);

        gridLayout->addWidget(LE_op, 2, 3, 1, 1);

        pb_addOp = new QPushButton(groupBox);
        pb_addOp->setObjectName(QStringLiteral("pb_addOp"));
        pb_addOp->setEnabled(false);

        gridLayout->addWidget(pb_addOp, 2, 4, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(335, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        PB_cancel = new QPushButton(operatorDialog);
        PB_cancel->setObjectName(QStringLiteral("PB_cancel"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        PB_cancel->setIcon(icon);

        gridLayout_3->addWidget(PB_cancel, 0, 0, 1, 1);

        PB_next = new QPushButton(operatorDialog);
        PB_next->setObjectName(QStringLiteral("PB_next"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/if_Next_32435.png"), QSize(), QIcon::Normal, QIcon::Off);
        PB_next->setIcon(icon1);

        gridLayout_3->addWidget(PB_next, 0, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 1, 1, 1, 1);


        retranslateUi(operatorDialog);

        CB_hospital->setCurrentIndex(-1);
        CB_phycisian->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(operatorDialog);
    } // setupUi

    void retranslateUi(QDialog *operatorDialog)
    {
        operatorDialog->setWindowTitle(QApplication::translate("operatorDialog", "Pre-Study Settings", nullptr));
        groupBox->setTitle(QApplication::translate("operatorDialog", "Select or add your institute/operator", nullptr));
        label_47->setText(QApplication::translate("operatorDialog", "Institute:", nullptr));
#ifndef QT_NO_TOOLTIP
        CB_hospital->setToolTip(QApplication::translate("operatorDialog", "<html><head/><body><p>The institute name that the operator belongs to. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        checkbox_Inst->setToolTip(QApplication::translate("operatorDialog", "<html><head/><body><p>Tick to add a new institute. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        checkbox_Inst->setText(QString());
#ifndef QT_NO_TOOLTIP
        LE_institute->setToolTip(QApplication::translate("operatorDialog", "<html><head/><body><p>The name od the new institure. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pb_addInst->setToolTip(QApplication::translate("operatorDialog", "<html><head/><body><p>Press to add the new institute. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        pb_addInst->setText(QApplication::translate("operatorDialog", "Add Institute", nullptr));
        label_46->setText(QApplication::translate("operatorDialog", "Operator:", nullptr));
#ifndef QT_NO_TOOLTIP
        CB_phycisian->setToolTip(QApplication::translate("operatorDialog", "<html><head/><body><p>The name of the operatore performing the experiment. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        checkbox_OP->setToolTip(QApplication::translate("operatorDialog", "<html><head/><body><p>Tick to add a new operator. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        checkbox_OP->setText(QString());
#ifndef QT_NO_TOOLTIP
        LE_op->setToolTip(QApplication::translate("operatorDialog", "<html><head/><body><p>The name of the operator to be added. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pb_addOp->setToolTip(QApplication::translate("operatorDialog", "<html><head/><body><p>Press to add the new operator. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        pb_addOp->setText(QApplication::translate("operatorDialog", "Add Operator", nullptr));
        PB_cancel->setText(QApplication::translate("operatorDialog", "Cancel", nullptr));
        PB_next->setText(QApplication::translate("operatorDialog", "Next", nullptr));
    } // retranslateUi

};

namespace Ui {
    class operatorDialog: public Ui_operatorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPERATORDIALOG_H
