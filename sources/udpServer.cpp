////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file udpServer.cpp
///
///	@brief producer thread representing a udp server that aquires the raw data arriving to the UDP port through the ethernet cable.
///
///	@author Aphrodite Toufa
/// @date   Created: 07.12.2018
/// @date   Updated: 29.7.2019
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "headers/udpServer.h"
#include "boost/circular_buffer.hpp"
#include "boost/format.hpp"
#include <QtNetwork/QUdpSocket>
#include <QDataStream>
#include <QMutexLocker>
#include <QCoreApplication>
#include <QMessageBox>
#include <QUdpSocket>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <sstream>
#include <QFile>
#include <netinet/in.h>
#include <QBuffer>
#include <QNetworkDatagram>
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

udpServer::udpServer( QSemaphore *fb, QSemaphore *ub, QMutex *_globalMutex,boost::circular_buffer<quint32> *_circularBuffer)
{
    stopped = false;
    freeBytes   = fb;
    usedBytes   = ub;
    globalMutex = _globalMutex;
    circularBuffer = _circularBuffer;
}

udpServer::~udpServer(){}

void udpServer::setupSocket()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(2000,QUdpSocket::DontShareAddress);
}

void udpServer::ProcessDatagram() // main function
{
    QByteArray Datagram;
    quint64 RecvBuffer;
    quint32 SigValue;

    if(isAlive()){
        if(udpSocket->waitForReadyRead(5)){
            while(udpSocket->hasPendingDatagrams()){
                Datagram.resize(udpSocket->pendingDatagramSize());
                RecvBuffer = udpSocket->readDatagram(Datagram.data(),Datagram.size());
                Datagram.resize(RecvBuffer);
                QDataStream dataStream(&Datagram,QIODevice::ReadOnly);
                dataStream.setByteOrder(QDataStream::BigEndian);
//                qDebug() << Datagram.size();
                freeBytes->acquire(1);
                globalMutex->lock();
                while(!dataStream.atEnd()){
                    dataStream >> SigValue;
                    circularBuffer->push_back(SigValue);

                }
                globalMutex->unlock();
                usedBytes->release(1);
            }
        }
    }
    else {
        qDebug() << "server stopped!";
        emit finished();
        udpSocket->close();
        udpSocket->deleteLater();
    }
}

bool udpServer::isAlive()
{
    bool live = true;
    QMutexLocker locker(&mutex);
    live =! stopped;
    return live;
}

void udpServer::stop()
{
    QMutexLocker locker(&mutex);
    stopped=true;
}


