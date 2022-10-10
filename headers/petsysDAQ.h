#ifndef PETSYSDAQ_H
#define PETSYSDAQ_H

#include <QObject>
#include <QThread>
#include <QTime>
#include <QProcess>
#include <QStack>
#include <fstream>
#include <iostream>
#include <sstream>
#include <QTimer>
#include <boost/circular_buffer.hpp>
#include <vector>
#include <string>
#include "headers/readinputinfo.h"

class petsysDAQ: public QObject
{
    Q_OBJECT
public:
    explicit petsysDAQ(ReadInputInfo*, int, QString);
    ~petsysDAQ();

signals:
    void daqStarted();
    void daqFinished();

public slots:
    void stopDaq();
    void startAcqSipm();
    void readDaqOut();

private slots:

    void printStarted();
    void printFinished(int);


private:

    QProcess * acqProcess;
    QString m_daqTime;
    QString m_rawFile;
    QString m_configFilePath;
    ReadInputInfo * m_readInputInfo;
};

#endif // PETSYSDAQ_H
