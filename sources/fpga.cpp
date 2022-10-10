///////////////////////////////////////////////////////////////////////////
///
///	@file fpga.cpp
///	@brief fpga communication-error handling and command posting in script
///
///	@author Aphrodite Toufa
/// @date   Created: 07.12.2018
/// @date   Updated: 29.7.2019
///
////////////////////////////////////////////////////////////////////////////
#include "headers/fpga.h"

fpga::fpga(QObject *parent) : QObject(parent), m_bIsFinished(false)
{
    disconnected = false;
    exitPressed=false;
    stopPressed=false;
    crashed = false;
    script_bat = new QProcess(this);
    init_script = new QProcess(this);
    timer = new QTimer(this);
    lsusb = new QTimer(this);
    download = new QTimer(this);
    download->setTimerType(Qt::PreciseTimer);
    modality=-1;

    connect(timer,SIGNAL(timeout()),this,SLOT(check_xmd_connectionState()));
    connect(download,SIGNAL(timeout()),this,SLOT(timeForDownloadElapsed()));
    connect(lsusb,SIGNAL(timeout()),this,SLOT(check_usb_whileDownload()));
}

bool fpga::check_lsusb()
{
    QString output;
    QString bash_cmnd="lsusb\n\r";
    QProcess proc;

    proc.start(bash_cmnd);
    proc.waitForFinished();
    output = proc.readAllStandardOutput();

    if(output.contains( "ID 0403:c5a8") || output.contains("ID 0403:6010") )//||output.contains("ID 2341:0043"))
        return true;
    else
        return false;
}

void fpga::check_usb_whileDownload()
{
    if(!check_lsusb()) {
        lsusb->stop();
        download->stop();
        kill_process(2);
        emit sendErrorCode(1);
    }
}

void fpga::Initialize_ADC_SPECT()
{
    QString appPath = QDir::currentPath();
    QString program = appPath.append("/external_code/./adc_init");

    init_script->start( program );
    init_script->waitForFinished( 100000 );
    connect(init_script, SIGNAL( finished(int) ), this, SLOT( initScript_finished(int) ) );
}
/*
void fpga::Initialize_ADC_PET()
{
    QString appPath = QDir::currentPath();
    QString program = appPath.append("/external_code/./adc_init_PET");

    init_script->start( program );
    connect(init_script, SIGNAL( finished(int) ),this, SLOT( initScript_finished(int) ) );
}
*/
void fpga::initScript_finished( int ) {
    m_bIsFinished = true;
    emit initialisationComplete();
}

bool fpga::isFPGAInited() { return m_bIsFinished; }

void fpga::download_SPECT_FPGA_script()
{
    modality=1;
    downloaded=false;
    crashed=false;
    QString path =  QDir::currentPath();
    path.append("/scripts/script_SPECT.bat");

    QString tt = "bash "+path;

    script_bat->setProcessChannelMode(QProcess::MergedChannels);
    script_bat->start(tt,QIODevice::ReadWrite);
    connect(script_bat,SIGNAL(started()),this,SLOT(started()));
}
/*
void fpga::download_PET_FPGA_script()
{
    modality = 2;
    downloaded = false;
    crashed = false;
    QString path =  QDir::currentPath();
    path.append("/scripts/script_PET.bat");

    QString tt = "bash " + path;

    script_bat->setProcessChannelMode(QProcess::MergedChannels);
    script_bat->start(tt,QIODevice::ReadWrite);

    connect(script_bat,SIGNAL(started()),this,SLOT(started()));
}
*/
void fpga::started()
{
    connect(script_bat,SIGNAL(readyReadStandardOutput()),this,SLOT(check_downState()));
    connect(script_bat,SIGNAL(readyReadStandardError()),this,SLOT(check_downState()));

    if(modality==1) {
        download->setInterval(65000);
        download->start();
    }
    else if(modality==2) {
        download->setInterval(65000);
        download->start();
    }

    lsusb->start();
}

void fpga::run()
{
    QString out;
    lsusb->stop();
    stopPressed = false;
    script_bat->write("dow uTxTest.elf\n\r");
    script_bat->waitForBytesWritten( 60000 );
    script_bat->write("run\n\r");
    script_bat->waitForBytesWritten( 30000 );

    QTime dieTime2 = QTime::currentTime().addSecs(6);
    while( QTime::currentTime() < dieTime2 )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    emit readyRead();
    //  timer->setInterval(1000);
    timer->start(500);
}

void fpga::stop()
{
    if (!exitPressed) {
        QString out;
        script_bat->write("stop\n\r");
        script_bat->waitForBytesWritten();

        disconnected = true;
        stopPressed=true;
    }
}

void fpga::exit()
{
    QString output;

    script_bat->write("exit\n\r");
    script_bat->waitForBytesWritten();
    script_bat->waitForFinished();
    script_bat->terminate();
    script_bat->close();
    //  qDebug() << script_bat->exitStatus();
    delete script_bat;

    exitPressed=true;
}

void fpga::terminate()
{
    if(!exitPressed) { //&& script_bat->state()==QProcess::Running)

        if(timer->isActive())
            timer->stop();

        if( lsusb->isActive())
            lsusb->stop();

        if(download->isActive())
            download->stop();

        script_bat->write("exit\n\r");
        script_bat->waitForBytesWritten();

        script_bat->terminate();

        fpga::connect(script_bat,SIGNAL(finished(int)),this,SLOT(script_batFinished(int)));
    }
}

void fpga::script_batFinished(int  /*err*/)
{
    qDebug() << script_bat->exitStatus();
    script_bat->deleteLater();
    emit exitBash();
}

void fpga::check_downState()
{
    if(!downloaded) {
        output += script_bat->readAll().data();
        qDebug() << output;

        if(output.contains("Connected to \"mb\" target.")||output.contains("Starting GDB server for \"mb\" target")) {
            emit downloadSuccesfull();
            downloaded=true;
            download->stop();
        }
        else if(output.contains("Cable is LOCKED. Retrying...")) {
            lsusb->stop();
            download->stop();
            emit sendErrorCode(2);
            kill_process(1);
            cleanCable();
        }
    }
    else if(downloaded&&!crashed) {
        QString xmd_output = script_bat->readAllStandardOutput();
        qDebug() << "xmd output: " << xmd_output;

        if(xmd_output.contains("control tranfer failed.")){ // || xmd_output.contains("Cannot perform the Debug Command") || xmd_output.contains("ERROR: Unable to Stop Processor"))
            fpgaError();
            timer->stop();

            if(!stopPressed) {
                emit sendErrorCode(3);
                kill_process(2);
            }
            else if(stopPressed) {
                emit sendErrorCode(1);
                kill_process(2);
            }
        }
    }
}

bool fpga::isOK()
{
    if(!downloaded) {
        output += script_bat->readAll().data();
        qDebug() << output;

        if(output.contains("Connected to \"mb\" target.")||output.contains("Starting GDB server for \"mb\" target")) {
            downloaded=true;
            download->stop();
        }
        else if(output.contains("Cable is LOCKED. Retrying...")) {
            lsusb->stop();
            download->stop();
            emit sendErrorCode(2);
            kill_process(1);
            cleanCable();
            downloaded = false;
        }
    }
    else if(downloaded&&!crashed) {
        QString xmd_output = script_bat->readAllStandardOutput();
        qDebug() << "xmd output: " << xmd_output;

        if(xmd_output.contains("control tranfer failed.")){ // || xmd_output.contains("Cannot perform the Debug Command") || xmd_output.contains("ERROR: Unable to Stop Processor"))
            fpgaError();
            timer->stop();

            if(!stopPressed) {
                emit sendErrorCode(3);
                kill_process(2);
                downloaded = false;
            }
            else if(stopPressed) {
                emit sendErrorCode(1);
                kill_process(2);
                downloaded = false;
            }
        }
    }
    return downloaded;
}

void fpga::timeForDownloadElapsed()
{
    std::cout << " FPGA downloaded lapsed..." << std::endl;

    download->stop();

    qDebug() << output;

    if(!downloaded) {
        if((!output.contains("Connected to \"mb\" target.")||!output.contains("Starting GDB server for \"mb\" target")) && \
                !output.contains("Cable is LOCKED. Retrying...")) {
            lsusb->stop();
            emit sendErrorCode(4);
            kill_process(1);
        }
        else if(output.contains("Connected to \"mb\" target.") || output.contains("Starting GDB server for \"mb\" target") ){
            emit downloadSuccesfull();
            downloaded=true;
        }
    }
}


void fpga::check_xmd_connectionState()
{
    if(!check_lsusb()){
        fpgaError();
        timer->stop();

        if (!stopPressed) {
            emit sendErrorCode(3);
            kill_process(2);
        }
        else if (stopPressed) {
            emit sendErrorCode(1);
            kill_process(2);
        }
    }
}

void fpga::fpgaError()
{
    crashed = true;
}

void fpga::kill_process(int  /*dev*/)
{
    script_bat->terminate();
    script_bat->close();

    delete script_bat;
    script_bat = new QProcess(this);
}

void fpga::cleanCable()
{
    QString path =  QDir::currentPath();
    QProcess proc;
    proc.start(path.append("/scripts/./cleancablelock"));

    while(!proc.waitForStarted(-1))
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    while(!proc.waitForFinished(-1))
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    QString out = proc.readAllStandardOutput();
}



