#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QProcess>
#include "headers/database_connection.h"
#include "headers/appWindow.h"

int main( int argc, char *argv[] )
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR","1");

    QApplication visual_eyes(argc, argv);
    visual_eyes.setWindowIcon(QIcon(":/icons/program_icon.png"));
    visual_eyes.setApplicationName("VISUAL-eyes");
    visual_eyes.setOrganizationName("Bioemtech");

    appWindow mainwindow;
    auto path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir d(path);
    if (!QDir("VISUAL-eyes").exists())
        d.mkdir("VISUAL-eyes");

    database_connection con;
    if (!con.enstablish_con()){
        QMessageBox msgBox;
        msgBox.critical(nullptr, "VISUAL-eyes", "Connection to database could not be established.");
        return 1;
    }
    else{
        mainwindow.show();
        mainwindow.Init();
    }
    return visual_eyes.exec();
}
