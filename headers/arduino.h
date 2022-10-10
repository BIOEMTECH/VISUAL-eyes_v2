#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QDir>
#include <QProcess>
#include <QCoreApplication>
#include <QDebug>
#include <chrono>
#include <fstream>
#include <iostream>
#include <QThread>
#include <QTextCodec>

#include <headers/CameraWorker.h>
#include "headers/gammacamera.h"
#include "readinputinfo.h"

class arduino : public QObject
{
    Q_OBJECT

public:
    explicit arduino(ReadInputInfo*, QObject *parent = nullptr,int=0);
    ~arduino();
    QProcess *server_proc,*init_proc;
    QString DIR;
    QString output;
    int modality;

    void reset();

signals:
    void terminateCamera();
    void stopRecording();
    void takeSnap();//g-eye
    void sendDir(QString);
    void startREC();
    void writeFrames();
    void initCam();
    void initGammaCam();
    void closeTimeDialog();

    void enableInBtn(bool);
    void enableOutBtn(bool);
    void letBedIn();
    void make_Start_btn_Avail();
    void insertBedWithoutVid();
    void showDialogUntilOut();
    void sendCameraError(int);
    void server_IsOpen();
    void ejectSent();
    void calibrated();


public slots:
    bool check_connection();
    void configure_ttyACM0();
    void insert_bed();
    void eject_bed();
    void calibInsert_bed();
    void calibEject_bed();
    void exit();
    void cameraRecord();
    void initThreadCam();
    void threadGammaCam(); //for g-eye
    void getStudyDir(QString);
    void check_bedPosition();
    void onlyMoveBedIn();
    void onlyMoveBedOut();
    void CapInit();
    void changeVoltage(QString);
    void start_listening(int);
    void process_started();
    void calibrate();
    void calibCalibrate();
    void bedIn(bool);

private:

    void runProcess(QString);
    CameraWorker *m_CamWorker;
    gammaCamera * m_gammaCamera;
    cv::VideoCapture m_VideoCapture;
    QThread *m_Thread;
    bool mo_chkpoint,bo_chkpoint,moveAndRec,moved;
    std::chrono::high_resolution_clock::time_point t1,t2;
    int duration;
    bool m_moveIn;
    bool m_isBeta;
    ReadInputInfo* m_pReadInputInfo;
    QTime startTime;
    bool m_calibrationMode;
};

#endif // ARDUINO_H

