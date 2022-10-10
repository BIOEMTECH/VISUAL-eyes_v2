#ifndef CAMERAWORKER_H
#define CAMERAWORKER_H

#include <QObject>
#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/stitching.hpp>
#include <chrono>
#include <string>
#include <QLabel>
#include <QFileDialog>
#include <QLineEdit>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>
#include <QTime>
#include "boost/circular_buffer.hpp"
#include <QSemaphore>
#include <iostream>
#include <fstream>
#include <QProcess>

#include "headers/imageCapture.hpp"
#include "readinputinfo.h"

using namespace std;

class CameraWorker:public QObject
{
    Q_OBJECT
public:
    explicit CameraWorker(cv::VideoCapture &cap, QString &name,int&mod,ReadInputInfo * inputInfo);
    ~CameraWorker();
    QString str;
    std::string filename;
    int MOD;
    cv::Mat frame;

signals:
    void finishedRec();
    void insertBed();

public slots:
    void startWriting();
    void record();
    void init();

private slots:
    void stopRecording();
    void optical_reconstruction();
    void createXray();

private:
    //cv::VideoWriter writer;
    boost::circular_buffer<cv::Mat> frame_BUFFER{1000};
    cv::Size frameSize;
    cv::VideoCapture cap;
    QTimer *timer;
    cv::Mat m_snap1,m_snap2,m_snap3;
    vector<cv::Mat> tst_writer;
    int m_x0;
    int m_y0;
    int m_width;
    int m_height;
    double m_exposure;
    ReadInputInfo * m_readInputInfo;
    cv::VideoWriter writer;
    void mf_setLastFrame();
    int m_iLastFrame;
};

#endif // CAMERAWORKER_H
