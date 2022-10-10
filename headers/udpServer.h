////////////////////////////////////////////////////////////////////////
/////
/////	@file UDPServer.h
/////	@brief HeaderFile UDPServer
/////
/////	@author Aphrodite Toufa
///// @date   Created: 06.10.2017
/////
////////////////////////////////////////////////////////////////////////




#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QUdpSocket>
#include <QtNetwork/QUdpSocket>
#include <QSemaphore>
#include <QWaitCondition>
#include <QTime>
#include <QStack>
#include <fstream>
#include <iostream>
#include <sstream>
#include <QTimer>
#include "boost/circular_buffer.hpp"
#include "qtermwidget5/qtermwidget.h"



class udpServer : public QObject
{
    Q_OBJECT
public:
    explicit udpServer(QSemaphore* =0, QSemaphore * =0, QMutex* = 0, boost::circular_buffer<quint32> * = 0);

    ~udpServer();



    QSemaphore     *freeBytes;
    QSemaphore     *usedBytes;
    QMutex         *globalMutex;


    boost::circular_buffer<quint32> *circularBuffer;


    QUdpSocket *udpSocket;








signals:

    void finished();
    void bataclan();
    void started();
    void readyStart();




public slots:
    void setupSocket();
    void stop();
    void ProcessDatagram();





private:

   bool isAlive();




   QMutex mutex;



   volatile bool stopped;

};

#endif // UDPSERVER_H

