#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include "gamma_eye.h"
#include "betaEye.h"
#include "PostProcessing.h"
#include "headers/Search.h"
#include "framelesswindow/framelesswindow.h"
#include "DarkStyle.h"
#include <QRect>
#include <QDesktopWidget>
#include <QMessageBox>
#include "headers/readinputinfo.h"

namespace Ui {
class appWindow;
}

class appWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit appWindow(QWidget *parent = 0);
    ~appWindow();

signals:
    void exitAndDelete();

public slots:
    void Init();
    void printHelp();

private slots:
    void imagingClicked();
    void calibrationClicked();
    void postProcessingClicked();
    void startWindow(bool);
    void gammaWindowControls(gamma_eye *,FramelessWindow *);
    void betaWindowControls(betaEye *,FramelessWindow *);

    void beyeRestart();
    void returnAndshow();
    void on_actionExit_Program_triggered();
    void on_actionSearch_Database_triggered();

private:
    Ui::appWindow *ui;
    ReadInputInfo* m_pReadInputInfo;
};

#endif // APPWINDOW_H
