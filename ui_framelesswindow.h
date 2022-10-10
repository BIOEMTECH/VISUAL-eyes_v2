/********************************************************************************
** Form generated from reading UI file 'framelesswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMELESSWINDOW_H
#define UI_FRAMELESSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "framelesswindow/windowdragger.h"

QT_BEGIN_NAMESPACE

class Ui_FramelessWindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *windowFrame;
    QVBoxLayout *verticalLayout;
    WindowDragger *windowTitlebar;
    QHBoxLayout *horizontalLayout;
    QToolButton *closeButton;
    QToolButton *minimizeButton;
    QToolButton *maximizeButton;
    QToolButton *restoreButton;
    QLabel *titleText;
    QLabel *spacer;
    QWidget *windowContent;

    void setupUi(QWidget *FramelessWindow)
    {
        if (FramelessWindow->objectName().isEmpty())
            FramelessWindow->setObjectName(QStringLiteral("FramelessWindow"));
        FramelessWindow->resize(1553, 1300);
        QFont font;
        font.setPointSize(10);
        FramelessWindow->setFont(font);
        FramelessWindow->setAutoFillBackground(false);
        verticalLayout_2 = new QVBoxLayout(FramelessWindow);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(15, 15, 15, 15);
        windowFrame = new QWidget(FramelessWindow);
        windowFrame->setObjectName(QStringLiteral("windowFrame"));
        windowFrame->setAutoFillBackground(false);
        windowFrame->setStyleSheet(QStringLiteral("#windowFrame{border:1px solid palette(highlight); border-radius:5px 5px 5px 5px; background-color:palette(Window);}"));
        verticalLayout = new QVBoxLayout(windowFrame);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        windowTitlebar = new WindowDragger(windowFrame);
        windowTitlebar->setObjectName(QStringLiteral("windowTitlebar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(windowTitlebar->sizePolicy().hasHeightForWidth());
        windowTitlebar->setSizePolicy(sizePolicy);
        windowTitlebar->setMinimumSize(QSize(0, 0));
        windowTitlebar->setAutoFillBackground(false);
        windowTitlebar->setStyleSheet(QStringLiteral("#windowTitlebar{border: 0px none palette(base); border-top-left-radius:5px; border-top-right-radius:5px; background-color:palette(shadow); height:20px;}"));
        horizontalLayout = new QHBoxLayout(windowTitlebar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        closeButton = new QToolButton(windowTitlebar);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        closeButton->setFont(font1);
        closeButton->setStyleSheet(QLatin1String("#closeButton{\n"
"  background-color:none;\n"
"  border:none;\n"
"  width:16px;\n"
"  height:16px;\n"
"  padding:4px;\n"
"  image:url(:/images/icon_window_close.png);\n"
"  border-top-right-radius: 5px;\n"
"}\n"
"#closeButton:hover{\n"
"  background-color:palette(alternate-base);\n"
"}\n"
"##closeButton:pressed{\n"
"  background-color:palette(highlight);\n"
"}"));

        horizontalLayout->addWidget(closeButton);

        minimizeButton = new QToolButton(windowTitlebar);
        minimizeButton->setObjectName(QStringLiteral("minimizeButton"));
        minimizeButton->setFont(font1);
        minimizeButton->setStyleSheet(QLatin1String("#minimizeButton{\n"
"  background-color:none;\n"
"  border:none;\n"
"  width:16px;\n"
"  height:16px;\n"
"  padding:4px;\n"
"  image:url(:/images/icon_window_minimize.png);\n"
"}\n"
"#minimizeButton:hover{\n"
"  background-color:palette(alternate-base);\n"
"}\n"
"#minimizeButton:pressed{\n"
"  background-color:palette(highlight);\n"
"}"));

        horizontalLayout->addWidget(minimizeButton);

        maximizeButton = new QToolButton(windowTitlebar);
        maximizeButton->setObjectName(QStringLiteral("maximizeButton"));
        maximizeButton->setStyleSheet(QLatin1String("#maximizeButton{\n"
"  background-color:none;\n"
"  border:none;\n"
"  width:16px;\n"
"  height:16px;\n"
"  padding:4px;\n"
"  image:url(:/images/icon_window_maximize.png);\n"
"}\n"
"#maximizeButton:hover{\n"
"  background-color:palette(alternate-base);\n"
"}\n"
"##maximizeButton:pressed{\n"
"  background-color:palette(highlight);\n"
"}"));

        horizontalLayout->addWidget(maximizeButton);

        restoreButton = new QToolButton(windowTitlebar);
        restoreButton->setObjectName(QStringLiteral("restoreButton"));
        restoreButton->setStyleSheet(QLatin1String("#restoreButton{\n"
"  background-color:none;\n"
"  border:none;\n"
"  width:16px;\n"
"  height:16px;\n"
"  padding:4px;\n"
"  image:url(:/images/icon_window_restore.png);\n"
"}\n"
"#restoreButton:hover{\n"
"  background-color:palette(alternate-base);\n"
"}\n"
"#restoreButton:pressed{\n"
"  background-color:palette(highlight);\n"
"}"));

        horizontalLayout->addWidget(restoreButton);

        titleText = new QLabel(windowTitlebar);
        titleText->setObjectName(QStringLiteral("titleText"));
        titleText->setFont(font1);
        titleText->setStyleSheet(QLatin1String("  padding-left:5px;\n"
"  color:rgb(153,153,153);"));
        titleText->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(titleText);

        spacer = new QLabel(windowTitlebar);
        spacer->setObjectName(QStringLiteral("spacer"));
        spacer->setMinimumSize(QSize(4, 0));
        spacer->setMaximumSize(QSize(4, 16777215));

        horizontalLayout->addWidget(spacer);


        verticalLayout->addWidget(windowTitlebar);

        windowContent = new QWidget(windowFrame);
        windowContent->setObjectName(QStringLiteral("windowContent"));
        windowContent->setAutoFillBackground(false);
        windowContent->setStyleSheet(QLatin1String("#windowContent{\n"
"  border: 0px none palette(base);\n"
"  border-radius:0px 0px 5px 5px;\n"
"}"));

        verticalLayout->addWidget(windowContent);


        verticalLayout_2->addWidget(windowFrame);


        retranslateUi(FramelessWindow);

        QMetaObject::connectSlotsByName(FramelessWindow);
    } // setupUi

    void retranslateUi(QWidget *FramelessWindow)
    {
        FramelessWindow->setWindowTitle(QString());
        minimizeButton->setText(QString());
        maximizeButton->setText(QString());
        restoreButton->setText(QString());
        titleText->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FramelessWindow: public Ui_FramelessWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMELESSWINDOW_H
