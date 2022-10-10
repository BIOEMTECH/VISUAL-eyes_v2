#include "headers/PETsysConnection.h"

PETsysConnection::PETsysConnection(QObject *){

    m_pid = 0;
    fpga_status=true;

    daqCommunication = new QProcess(this);
    initSystem = new QProcess(this);



    connect(daqCommunication, SIGNAL(readyRead()), this, SLOT(readDaqOut()));
    connect(initSystem, SIGNAL(readyReadStandardOutput()), this, SLOT(readInitOut()));
}

PETsysConnection::~PETsysConnection(){}

void PETsysConnection::openDaq(){

    killDaqInstances();

    qDebug() << "Opening daqd ........ " << endl;

    sockOpenCommand = "daqd --socket-name /tmp/d.sock --daq-type GBE";
    daqCommunication->setProcessChannelMode(QProcess::MergedChannels);
    daqCommunication->start(sockOpenCommand,QIODevice::ReadWrite);
    daqCommunication->waitForReadyRead();
    m_pid = daqCommunication->pid();
    QString output = daqCommunication->readAllStandardOutput();

    qDebug() << "Daqd PID    "<< m_pid  << "  " << endl;

}


void PETsysConnection::initDaq(){
    initSystem->setProcessChannelMode(QProcess::MergedChannels);
    initSystem->start("init_system",QIODevice::ReadWrite);
    initSystem->waitForFinished();
}


void PETsysConnection::closeDaq(){
    qDebug() << "closing connection " << endl;

    if(m_pid)
        daqCommunication->kill();
}

void PETsysConnection::readDaqOut(){

    QString output = daqCommunication->readAll().data();
    qDebug() << output;
    if(output.contains("ERROR")){
        setFPGA_status(false);
        //emit sendError(1);
    }else{
        setFPGA_status(true);
    }
}

void PETsysConnection::setFPGA_status(bool status){
    fpga_status=status;
}

bool PETsysConnection::getFPGA_status(){
    return fpga_status;
}

void PETsysConnection::readInitOut(){
    QString output = initSystem->readAll().data();
    qDebug() << "Initializing daqd ........ " << endl;
    qDebug() << output << endl;
    emit petsysConIsOK();
}

void PETsysConnection::killDaqInstances(){

    QString tmpPid;
    QStringList outputList;
    QString bash_cmd = "pidof daqd";


    QProcess checkRunning, killDaq, deleteInstances;
    checkRunning.start(bash_cmd);
    checkRunning.waitForFinished();

    tmpPid = checkRunning.readAllStandardOutput();

    QString kill_cmd = "kill " + tmpPid.trimmed();

    qDebug() << kill_cmd <<  endl;
    QString delSock = "rm -fr /tmp/d.sock";
    QString delSharedMem = "rm -fr /dev/shm/daqd_shm";
    killDaq.start(kill_cmd);
    killDaq.waitForFinished();

    deleteInstances.start(delSock);
    deleteInstances.waitForFinished();

    deleteInstances.start(delSharedMem);
    deleteInstances.waitForFinished();
}


