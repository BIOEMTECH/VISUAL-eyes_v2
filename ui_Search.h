/********************************************************************************
** Form generated from reading UI file 'Search.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCH_H
#define UI_SEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Search
{
public:
    QGridLayout *gridLayout_5;
    QToolBox *toolBox;
    QWidget *page;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QDateEdit *qd_startDate;
    QLabel *label_2;
    QDateEdit *qd_endDate;
    QPushButton *pb_dateSearch;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QGroupBox *CheckBoxes;
    QGridLayout *gridLayout_2;
    QLineEdit *LE_animal;
    QCheckBox *check_marking;
    QLabel *label_6;
    QComboBox *cB_nuclide;
    QLabel *label;
    QCheckBox *check_name;
    QCheckBox *check_nuclide;
    QPushButton *pb_comboSearch;
    QLabel *label_5;
    QCheckBox *check_Inpath;
    QCheckBox *check_op;
    QCheckBox *check_animal;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_8;
    QComboBox *cB_op;
    QLineEdit *LE_marking;
    QLineEdit *LE_name;
    QComboBox *cB_inj_path;
    QWidget *page_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_6;
    QTableView *TV_studies;

    void setupUi(QDialog *Search)
    {
        if (Search->objectName().isEmpty())
            Search->setObjectName(QStringLiteral("Search"));
        Search->resize(580, 491);
        QFont font;
        font.setPointSize(10);
        Search->setFont(font);
        gridLayout_5 = new QGridLayout(Search);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        toolBox = new QToolBox(Search);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        toolBox->setPalette(palette);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 279, 418));
        gridLayout_4 = new QGridLayout(page);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        qd_startDate = new QDateEdit(groupBox);
        qd_startDate->setObjectName(QStringLiteral("qd_startDate"));
        qd_startDate->setCalendarPopup(true);

        gridLayout->addWidget(qd_startDate, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        qd_endDate = new QDateEdit(groupBox);
        qd_endDate->setObjectName(QStringLiteral("qd_endDate"));
        qd_endDate->setCalendarPopup(true);

        gridLayout->addWidget(qd_endDate, 0, 3, 1, 1);

        pb_dateSearch = new QPushButton(groupBox);
        pb_dateSearch->setObjectName(QStringLiteral("pb_dateSearch"));

        gridLayout->addWidget(pb_dateSearch, 1, 0, 1, 4);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 211, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        CheckBoxes = new QGroupBox(groupBox_2);
        CheckBoxes->setObjectName(QStringLiteral("CheckBoxes"));
        gridLayout_2 = new QGridLayout(CheckBoxes);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        LE_animal = new QLineEdit(CheckBoxes);
        LE_animal->setObjectName(QStringLiteral("LE_animal"));

        gridLayout_2->addWidget(LE_animal, 1, 3, 1, 1);

        check_marking = new QCheckBox(CheckBoxes);
        check_marking->setObjectName(QStringLiteral("check_marking"));

        gridLayout_2->addWidget(check_marking, 2, 0, 1, 1);

        label_6 = new QLabel(CheckBoxes);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 2, 1, 1, 1);

        cB_nuclide = new QComboBox(CheckBoxes);
        cB_nuclide->setObjectName(QStringLiteral("cB_nuclide"));
        cB_nuclide->setEditable(true);

        gridLayout_2->addWidget(cB_nuclide, 4, 3, 2, 1);

        label = new QLabel(CheckBoxes);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 3, 1, 1, 1);

        check_name = new QCheckBox(CheckBoxes);
        check_name->setObjectName(QStringLiteral("check_name"));

        gridLayout_2->addWidget(check_name, 0, 0, 1, 1);

        check_nuclide = new QCheckBox(CheckBoxes);
        check_nuclide->setObjectName(QStringLiteral("check_nuclide"));

        gridLayout_2->addWidget(check_nuclide, 4, 0, 1, 1);

        pb_comboSearch = new QPushButton(CheckBoxes);
        pb_comboSearch->setObjectName(QStringLiteral("pb_comboSearch"));

        gridLayout_2->addWidget(pb_comboSearch, 7, 0, 1, 4);

        label_5 = new QLabel(CheckBoxes);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 1, 1, 1, 1);

        check_Inpath = new QCheckBox(CheckBoxes);
        check_Inpath->setObjectName(QStringLiteral("check_Inpath"));

        gridLayout_2->addWidget(check_Inpath, 5, 0, 2, 1);

        check_op = new QCheckBox(CheckBoxes);
        check_op->setObjectName(QStringLiteral("check_op"));

        gridLayout_2->addWidget(check_op, 3, 0, 1, 1);

        check_animal = new QCheckBox(CheckBoxes);
        check_animal->setObjectName(QStringLiteral("check_animal"));

        gridLayout_2->addWidget(check_animal, 1, 0, 1, 1);

        label_7 = new QLabel(CheckBoxes);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 4, 1, 1, 2);

        label_4 = new QLabel(CheckBoxes);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 0, 1, 1, 1);

        label_8 = new QLabel(CheckBoxes);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 5, 1, 2, 2);

        cB_op = new QComboBox(CheckBoxes);
        cB_op->setObjectName(QStringLiteral("cB_op"));
        cB_op->setEditable(true);

        gridLayout_2->addWidget(cB_op, 3, 3, 1, 1);

        LE_marking = new QLineEdit(CheckBoxes);
        LE_marking->setObjectName(QStringLiteral("LE_marking"));

        gridLayout_2->addWidget(LE_marking, 2, 3, 1, 1);

        LE_name = new QLineEdit(CheckBoxes);
        LE_name->setObjectName(QStringLiteral("LE_name"));

        gridLayout_2->addWidget(LE_name, 0, 3, 1, 1);

        cB_inj_path = new QComboBox(CheckBoxes);
        cB_inj_path->setObjectName(QStringLiteral("cB_inj_path"));
        cB_inj_path->setEditable(true);

        gridLayout_2->addWidget(cB_inj_path, 6, 3, 1, 1);


        gridLayout_3->addWidget(CheckBoxes, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 1, 0, 1, 1);

        toolBox->addItem(page, QStringLiteral("Search by"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 278, 413));
        toolBox->addItem(page_2, QStringLiteral(""));

        gridLayout_5->addWidget(toolBox, 0, 0, 1, 1);

        tabWidget = new QTabWidget(Search);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_6 = new QGridLayout(tab);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        TV_studies = new QTableView(tab);
        TV_studies->setObjectName(QStringLiteral("TV_studies"));

        gridLayout_6->addWidget(TV_studies, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout_5->addWidget(tabWidget, 0, 1, 1, 1);

        QWidget::setTabOrder(qd_startDate, qd_endDate);
        QWidget::setTabOrder(qd_endDate, pb_dateSearch);
        QWidget::setTabOrder(pb_dateSearch, check_name);
        QWidget::setTabOrder(check_name, LE_name);
        QWidget::setTabOrder(LE_name, check_animal);
        QWidget::setTabOrder(check_animal, LE_animal);
        QWidget::setTabOrder(LE_animal, check_marking);
        QWidget::setTabOrder(check_marking, LE_marking);
        QWidget::setTabOrder(LE_marking, check_op);
        QWidget::setTabOrder(check_op, cB_op);
        QWidget::setTabOrder(cB_op, check_nuclide);
        QWidget::setTabOrder(check_nuclide, cB_nuclide);
        QWidget::setTabOrder(cB_nuclide, check_Inpath);
        QWidget::setTabOrder(check_Inpath, cB_inj_path);
        QWidget::setTabOrder(cB_inj_path, pb_comboSearch);
        QWidget::setTabOrder(pb_comboSearch, tabWidget);
        QWidget::setTabOrder(tabWidget, TV_studies);

        retranslateUi(Search);

        toolBox->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Search);
    } // setupUi

    void retranslateUi(QDialog *Search)
    {
        Search->setWindowTitle(QApplication::translate("Search", "Search database", nullptr));
#ifndef QT_NO_TOOLTIP
        groupBox->setToolTip(QApplication::translate("Search", "<html><head/><body><p>Select the time interval to search in the database. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("Search", "date:", nullptr));
        label_3->setText(QApplication::translate("Search", "from:", nullptr));
        label_2->setText(QApplication::translate("Search", "to:", nullptr));
        pb_dateSearch->setText(QApplication::translate("Search", "Search", nullptr));
        groupBox_2->setTitle(QApplication::translate("Search", "keywords:", nullptr));
#ifndef QT_NO_TOOLTIP
        CheckBoxes->setToolTip(QApplication::translate("Search", "<html><head/><body><p>Tick the keyword type that the search will be performed. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        check_marking->setText(QString());
        label_6->setText(QApplication::translate("Search", "Marking:", nullptr));
        label->setText(QApplication::translate("Search", "Operator:", nullptr));
        check_name->setText(QString());
        check_nuclide->setText(QString());
        pb_comboSearch->setText(QApplication::translate("Search", "Search", nullptr));
        label_5->setText(QApplication::translate("Search", "Animal ID:", nullptr));
        check_Inpath->setText(QString());
        check_op->setText(QString());
        check_animal->setText(QString());
        label_7->setText(QApplication::translate("Search", "Radionuclide:", nullptr));
        label_4->setText(QApplication::translate("Search", "Study name:", nullptr));
        label_8->setText(QApplication::translate("Search", "Injection path:", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("Search", "Search by", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_2), QString());
#ifndef QT_NO_TOOLTIP
        TV_studies->setToolTip(QApplication::translate("Search", "<html><head/><body><p>The table containing the results found. </p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Search", "Studies found", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Search: public Ui_Search {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_H
