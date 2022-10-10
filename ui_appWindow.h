/********************************************************************************
** Form generated from reading UI file 'appWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPWINDOW_H
#define UI_APPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <clickablelabel.h>

QT_BEGIN_NAMESPACE

class Ui_appWindow
{
public:
    QAction *actionExit_Program;
    QAction *actionSearch_Database;
    QAction *actionInfo;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QFrame *line_2;
    ClickableLabel *postImage;
    QLabel *label_2;
    QWidget *widget1;
    QGridLayout *gridLayout;
    QLabel *label;
    ClickableLabel *imaging;
    QFrame *line;
    QLabel *lb_calibration;
    QFrame *line_3;
    ClickableLabel *calibration;
    QMenuBar *menubar;
    QMenu *menuMain_Menu;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *appWindow)
    {
        if (appWindow->objectName().isEmpty())
            appWindow->setObjectName(QStringLiteral("appWindow"));
        appWindow->resize(510, 473);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(appWindow->sizePolicy().hasHeightForWidth());
        appWindow->setSizePolicy(sizePolicy);
        appWindow->setMinimumSize(QSize(510, 473));
        appWindow->setMaximumSize(QSize(510, 473));
        QFont font;
        font.setPointSize(10);
        appWindow->setFont(font);
        actionExit_Program = new QAction(appWindow);
        actionExit_Program->setObjectName(QStringLiteral("actionExit_Program"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit_Program->setIcon(icon);
        actionSearch_Database = new QAction(appWindow);
        actionSearch_Database->setObjectName(QStringLiteral("actionSearch_Database"));
        actionSearch_Database->setShortcutContext(Qt::ApplicationShortcut);
        actionSearch_Database->setMenuRole(QAction::ApplicationSpecificRole);
        actionSearch_Database->setPriority(QAction::HighPriority);
        actionInfo = new QAction(appWindow);
        actionInfo->setObjectName(QStringLiteral("actionInfo"));
        centralwidget = new QWidget(appWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setContextMenuPolicy(Qt::NoContextMenu);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        widget = new QWidget(frame);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 240, 471, 161));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        line_2 = new QFrame(widget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_2, 1, 0, 1, 1);

        postImage = new ClickableLabel(widget);
        postImage->setObjectName(QStringLiteral("postImage"));

        gridLayout_3->addWidget(postImage, 2, 0, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 0, 0, 1, 1);

        widget1 = new QWidget(frame);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(11, 14, 471, 221));
        gridLayout = new QGridLayout(widget1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        imaging = new ClickableLabel(widget1);
        imaging->setObjectName(QStringLiteral("imaging"));

        gridLayout->addWidget(imaging, 2, 0, 1, 1);

        line = new QFrame(widget1);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 1);

        lb_calibration = new QLabel(widget1);
        lb_calibration->setObjectName(QStringLiteral("lb_calibration"));

        gridLayout->addWidget(lb_calibration, 0, 1, 1, 1);

        line_3 = new QFrame(widget1);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 1, 1, 1, 1);

        calibration = new ClickableLabel(widget1);
        calibration->setObjectName(QStringLiteral("calibration"));

        gridLayout->addWidget(calibration, 2, 1, 1, 1);


        horizontalLayout->addWidget(frame);

        appWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(appWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 510, 24));
        menuMain_Menu = new QMenu(menubar);
        menuMain_Menu->setObjectName(QStringLiteral("menuMain_Menu"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        appWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(appWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        appWindow->setStatusBar(statusbar);

        menubar->addAction(menuMain_Menu->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuMain_Menu->addAction(actionSearch_Database);
        menuMain_Menu->addAction(actionExit_Program);
        menuHelp->addAction(actionInfo);

        retranslateUi(appWindow);

        QMetaObject::connectSlotsByName(appWindow);
    } // setupUi

    void retranslateUi(QMainWindow *appWindow)
    {
        actionExit_Program->setText(QApplication::translate("appWindow", "Exit Program..", nullptr));
        actionSearch_Database->setText(QApplication::translate("appWindow", "Search Database", nullptr));
        actionInfo->setText(QApplication::translate("appWindow", "Info", nullptr));
        postImage->setText(QString());
        label_2->setText(QApplication::translate("appWindow", " Image processing", nullptr));
        label->setText(QApplication::translate("appWindow", "  Live  imaging", nullptr));
        imaging->setText(QString());
        lb_calibration->setText(QApplication::translate("appWindow", "Calibration", nullptr));
        calibration->setText(QString());
        menuMain_Menu->setTitle(QApplication::translate("appWindow", "Main menu", nullptr));
        menuHelp->setTitle(QApplication::translate("appWindow", "Help", nullptr));
        Q_UNUSED(appWindow);
    } // retranslateUi

};

namespace Ui {
    class appWindow: public Ui_appWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPWINDOW_H
