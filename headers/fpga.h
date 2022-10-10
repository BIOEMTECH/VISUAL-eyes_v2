#ifndef FPGA_H
#define FPGA_H

#include <QObject>
#include <QProcess>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QRegExp>
#include <QTimer>
#include <QCoreApplication>
#include <fstream>
#include <iostream>
#include <QProcess>
#include <QTextStream>
#include <QTime>
#include <QDebug>
#include <QDir>
#include "qtermwidget5/qtermwidget.h"

class fpga:public QObject
{
    Q_OBJECT
public:
    explicit fpga(QObject *parent = nullptr);
    QProcess *script_bat;
    QProcess *init_script;

    bool isFPGAInited();
    bool isOK();

signals:
    void readyRead();
    void sendErrorCode(int);
    void downloadSuccesfull();
    void exitBash();
    void initialisationComplete();

public slots:
  bool check_lsusb();
  void download_SPECT_FPGA_script();
//  void download_PET_FPGA_script();
  void check_downState();
  void exit();
  void check_xmd_connectionState();
  void run();
  void stop();
  void terminate();
  void Initialize_ADC_SPECT();
//  void Initialize_ADC_PET();
  void kill_process(int);
  void check_usb_whileDownload();
  void started();

private slots:
 void fpgaError();
 void cleanCable();
 void script_batFinished(int);
 void timeForDownloadElapsed();
 void initScript_finished(int);

private:
  volatile bool connected{};
  volatile bool disconnected;
  bool stopPressed;
  bool exitPressed;
  bool crashed;
  QTimer *timer,*lsusb,*download;
  bool first=true;
  bool downloaded;
  int modality;
  QMessageBox *mes;
  QString output,xmd_output;
  bool m_bIsFinished;
};

#endif // FPGA_H
