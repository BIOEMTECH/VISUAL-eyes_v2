#ifndef PETSYSCONNECTION_H
#define PETSYSCONNECTION_H

#include <QObject>
#include <QProcess>
#include <QThread>
#include <QDebug>
#include <QTime>
#include <QApplication>

class PETsysConnection:public QObject
{
    Q_OBJECT

public:
    explicit PETsysConnection(QObject *parent = 0);
    ~PETsysConnection();


signals:
    void petsysConIsOK();
    void sendError(int);


public slots:
    void openDaq();
    void initDaq();
    void closeDaq();
    void readInitOut();
    void readDaqOut();
    bool getFPGA_status();


private slots:
    void killDaqInstances();
    void setFPGA_status(bool);

private:

    QProcess * daqCommunication;
    QProcess * initSystem;
    QString sockOpenCommand;
    int m_pid;
    bool fpga_status;

};

#endif // PETSYSCONNECTION_H
