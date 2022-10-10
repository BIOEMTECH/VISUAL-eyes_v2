#include "headers/petsysDAQ.h"
#include "boost/circular_buffer.hpp"
#include "boost/format.hpp"
#include <QDataStream>
#include <QMutexLocker>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <sstream>
#include <QFile>
#include <netinet/in.h>
#include <QBuffer>
#include <iomanip>
#include <QDir>
#include <pwd.h>
#include <malloc.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


petsysDAQ::petsysDAQ(ReadInputInfo* inputInfo, int acqTime, QString rawDirectory):m_readInputInfo(inputInfo)
{

    m_daqTime = QString::number(acqTime);
    m_configFilePath = "./PET_calibration_files/PETsysCalibration/config.ini";

    m_rawFile=rawDirectory+"/Summed/RawSummed.bdat";
    QString procOutPath=rawDirectory+"/Summed";
    QDir procOutDir(procOutPath);
    if(!procOutDir.exists()){
       procOutDir.mkdir(procOutPath);
    }

    acqProcess = new QProcess(this);

    connect(acqProcess,SIGNAL(readyRead()), this, SLOT(readDaqOut()));
    connect(acqProcess, SIGNAL(started()),this,SLOT(printStarted()));
    connect(acqProcess, SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(printFinished(int)));

}

petsysDAQ::~petsysDAQ(){}

void petsysDAQ::startAcqSipm()
{

    qDebug() << "petsysDAQ::startAcqSipm()" <<endl;
    QString acqCommand = "acquire_sipm_data_with_monitoring --config "+m_configFilePath+" --mode qdc --time "+ m_daqTime+" --enable-hw-trigger" ;
    acqCommand+=" --monitor-toc "+ m_rawFile+" --energy-window-up "+QString::number(m_readInputInfo->getRawEnergyUp())+" --energy-window-low "+QString::number(m_readInputInfo->getRawEnergyLow());
    acqCommand+=" --time-window "+ QString::number(m_readInputInfo->getTimeWindow());

    acqProcess->start(acqCommand);
    acqProcess->waitForFinished();
}


void petsysDAQ::stopDaq()
{
    acqProcess->terminate();
    acqProcess->close();
}

void petsysDAQ::printStarted()
{
    qDebug() << "SCRIPT STARTED !!!" <<endl;
    //emit daqStarted();
}

void petsysDAQ::printFinished(int exitStatus)
{
    qDebug() << "ACQUISITION FINISHED !!!  " << exitStatus << endl;
    emit daqFinished();
}

void petsysDAQ::readDaqOut()
{
    QString output = acqProcess->readAll().data();
    if(output.contains("DAQ_START"))
        emit daqStarted();

}

