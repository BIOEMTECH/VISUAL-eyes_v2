#ifndef GAMMACAMERA_H
#define GAMMACAMERA_H

#include <QObject>
#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/cvstd.hpp>
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

#include "headers/imageFusion.hpp"
#include "readinputinfo.h"

using namespace std;

class gammaCamera:public QObject
{
    Q_OBJECT
public:
    explicit gammaCamera(cv::VideoCapture &cap, QString &name,int&mod, ReadInputInfo* inputInfo);
    ~gammaCamera();
    QString str;
    std::string filename;
    int MOD;

signals:
    void finishedCapture();

private slots:

    void snapshot();
    void createXray();

private:
    cv::VideoWriter writer;
    cv::Size frameSize;
    cv::VideoCapture cap;
    int m_x0;
    int m_y0;
    int m_width;
    int m_height;
    double m_exposure;
    ReadInputInfo * m_readInputInfo;
};

#endif // GAMMACAMERA_H
