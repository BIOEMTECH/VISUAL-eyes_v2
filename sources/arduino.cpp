/////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file arduino.cpp
///
///	@brief handles connection and communication with arduino in order to move bed and mandate
/// the embbedded camera's function , for fusion image construnction, creating a separate m_Thread
///
///	@author Aphrodite Toufa
/// @date   Created: 07.12.2018
/// @date   Updated: 29.7.2019
///
//////////////////////////////////////////////////////////////////////////////////////////////////
#include "headers/arduino.h"
#include <QMessageBox>
#include "headers/readinputinfo.h"
#include <QElapsedTimer>
using namespace std;

arduino::arduino(ReadInputInfo* inputInfo, QObject *parent, int mod) : QObject(parent), m_pReadInputInfo( inputInfo )
{
    server_proc = new QProcess(this);
    init_proc = new QProcess(this);
    modality = mod;
    mo_chkpoint = false;
    bo_chkpoint = false;
    moveAndRec = false;
    moved = false;
    m_moveIn =false;
    m_calibrationMode=false;

    if ( inputInfo->getSystemName().contains("SCC") ) { //Which means beta
        m_isBeta = true;
    }else{
        m_isBeta = false;
    }

    m_CamWorker = nullptr;
    m_Thread = nullptr;
}

arduino::~arduino()
{
    delete server_proc;
}

bool arduino::check_connection()
{
    QString output;
    QString path = QDir::currentPath();

    QString lsusb = "lsusb\n\r";
    QProcess proc;
    proc.start( lsusb );
    proc.waitForFinished();
    output = proc.readAllStandardOutput();

#ifdef QT_DEBUG
    qDebug() << output;
#endif

    if( output.contains("ID 2341:0043") || output.contains("ID 2341:0243") )
        return true;

    return false;
}

void arduino::configure_ttyACM0()
{

    QString ttyDev_conf = " stty -F " + m_pReadInputInfo->getArduinoCom() + " cs8 115200 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts ";
    init_proc->start(ttyDev_conf);
    connect(init_proc,SIGNAL(finished(int)),this,SLOT(start_listening(int)));
}

void arduino::calibrate(){
    runProcess("/scripts/calibrate\n\r");
}

void arduino::calibCalibrate(){
    m_calibrationMode=true;
    runProcess("/scripts/c_calibrate\n\r");
}


void arduino::reset(){
    runProcess("/scripts/reset\n\r");
}

void arduino::runProcess(QString command){
    QProcess proc;
    QString path =  QDir::currentPath();
    QString script = path.append(command);
    proc.start(script);
    proc.waitForFinished();
}

void arduino::start_listening(int)
{
    QString path =  QDir::currentPath();
    QString listen_socket = path.append("/scripts/listen\n\r");
    server_proc->start(listen_socket);
    connect(server_proc,SIGNAL(started()),this,SLOT(process_started()));
}

void arduino::process_started()
{
    connect( server_proc, SIGNAL( readyRead() ),this, SLOT( check_bedPosition() ) );
    if(m_isBeta){
        connect( this, SIGNAL( initCam() ), this, SLOT( CapInit() ) );
    }else{
        connect( this, SIGNAL( initGammaCam() ), this, SLOT( CapInit() ) );
    }

    emit server_IsOpen();
}

void arduino::insert_bed()
{
    moveAndRec=true;
    if(m_isBeta) 
    	emit startREC();

    runProcess("/scripts/insert_bed\n\r");
}

void arduino::calibInsert_bed(){
    moveAndRec=false;
    runProcess("/scripts/c_insert_bed\n\r");
}

void arduino::calibEject_bed(){
    moveAndRec=false;
    runProcess("/scripts/c_eject_bed\n\r");
}

void arduino::onlyMoveBedIn()
{
    moveAndRec=false;
    runProcess("/scripts/insert_bed\n\r");
}

void arduino::eject_bed()
{
    moveAndRec=true;
    runProcess("/scripts/eject_bed\n\r");

    QTime dieTime2 = QTime::currentTime().addSecs(2);
    while( QTime::currentTime() < dieTime2 )
        QCoreApplication::processEvents(QEventLoop::AllEvents);

    emit ejectSent();
}

void arduino::onlyMoveBedOut()
{
    moveAndRec=false;
    runProcess("/scripts/eject_bed\n\r");

}

void arduino::bedIn(bool moveIn){
   m_moveIn=moveIn;
}

void arduino::changeVoltage(QString voltage)
{
    QString script="/scripts/";
    script.append(voltage);
    runProcess(script);

}

void arduino :: getStudyDir(QString sDir){ DIR = sDir; }

void arduino::CapInit()
{
    QString path =  QDir::currentPath();
    QString listen = path.append("/scripts/findCameraID\n\r");
    QProcess camera_script;
    camera_script.start( listen );
    camera_script.waitForFinished();

    QString script_out = camera_script.readAll().data();
    QStringList listedCameras = script_out.split("\n");

    int camID=-1;

    for(int i=0;i<listedCameras.count();i++) {
        QString strTocheck = listedCameras.at(i);

#ifdef QT_DEBUG
        qDebug() << listedCameras.at(i);
#endif

        if ( strTocheck.contains( m_pReadInputInfo->getCameraID() ) ){
            QStringList str;
            QString copy = strTocheck;

            str = copy.split(" -> ../../video");

#ifdef QT_DEBUG
            qDebug() << str;
#endif

            for(int i=0;i<str.size();i++) {
                if( i==1 ) {
                    QString in = str.at(i);
                    QString out = in.remove("\n");
                    camID = out.toInt();
                    qDebug() << camID;
                }
            }
            break;
        }
    }

    if(camID!=-1)
        m_VideoCapture.open(camID);

    if ( m_VideoCapture.isOpened() ){

#ifdef QT_DEBUG
        qDebug() << "Camera successfully connected.";
#endif
        double fps=0; 
        int width, height; 
        if(m_isBeta){
            fps = 15;
            width =  640;//640, 960
            height = 480;//480, 540
        }else{
            fps = 0;
            width =  1280;
            height = 720; 
        }
        m_VideoCapture.set(cv::CAP_PROP_FPS,fps);
        m_VideoCapture.set(cv::CAP_PROP_FRAME_WIDTH,width);
        m_VideoCapture.set(cv::CAP_PROP_FRAME_HEIGHT,height);
        if(m_isBeta){
            initThreadCam();
        }else{
            threadGammaCam();
        }
    }
    else
        void sendCameraError(int);
}

void arduino::initThreadCam()
{
    m_Thread = new QThread();
    m_CamWorker = new CameraWorker( m_VideoCapture, DIR, modality,m_pReadInputInfo);

    connect(m_Thread,SIGNAL( started() ), m_CamWorker,SLOT(init()) );
    connect(this, SIGNAL( startREC() ), m_CamWorker, SLOT(startWriting()) );
    connect(this, SIGNAL( stopRecording() ), m_CamWorker, SLOT(stopRecording()));
    connect(m_CamWorker,SIGNAL( finishedRec() ), this, SLOT( cameraRecord()  ) );
    connect(m_CamWorker, SIGNAL( finishedRec() ), m_Thread, SLOT(quit() ) );
    connect(m_Thread, SIGNAL( finished() ), m_CamWorker, SLOT( deleteLater() ));
    connect(m_Thread, SIGNAL( finished() ), m_Thread, SLOT( deleteLater() ) );

    m_CamWorker->moveToThread(m_Thread);
    m_Thread->start( QThread::TimeCriticalPriority );
}

void arduino::threadGammaCam()
{
    m_Thread = new QThread();
    m_gammaCamera = new gammaCamera( m_VideoCapture, DIR, modality,m_pReadInputInfo);

    connect(this, SIGNAL( takeSnap() ),m_gammaCamera, SLOT(snapshot()) );
    connect(m_gammaCamera, SIGNAL( finishedCapture() ), m_Thread, SLOT(quit() ) );
    connect(m_gammaCamera,SIGNAL( finishedCapture() ), this, SLOT( cameraRecord()  ) );
    connect(m_Thread, SIGNAL( finished() ),m_gammaCamera, SLOT( deleteLater() ));
    connect(m_Thread, SIGNAL( finished() ), m_Thread, SLOT( deleteLater() ) );

    m_gammaCamera->moveToThread(m_Thread);
    m_Thread->start( QThread::TimeCriticalPriority );
}

void arduino::cameraRecord()
{
    m_VideoCapture.release();

#ifdef QT_DEBUG
    qDebug() << "Camera successfully disconnected";
#endif

    emit make_Start_btn_Avail();
}

void arduino::exit()
{
    server_proc->terminate();
    server_proc->close();

#ifdef QT_DEBUG
    qDebug() << server_proc->exitStatus();
#endif

    emit terminateCamera();
}

std::string getLastLine(std::ifstream& in)
{
    std::string line;
    while (in >> std::ws && std::getline(in, line)); // skip empty lines
    return line;
}

void arduino::check_bedPosition()
{
    QString server_output;
    server_output = server_proc->readAll().data();

#ifdef QT_DEBUG
    qDebug() << " " << "arduino output:" << server_output;
#endif

    if ( moveAndRec ) {
        QString copy = server_output;
        QRegExp sep("(\r\n)");
        QStringList pieces =  copy.split(sep);

        for(int i=0;i<pieces.count();i++) {

            if( pieces.at(i).contains("mi") || pieces.at(i).contains("i") || m_moveIn) {
                qDebug()<< " " << "broken text: " << pieces.at(i); //Nikos: Check to be in Debug mode

                //m_Thread->start( QThread::TimeCriticalPriority );

                if ( mo_chkpoint && bo_chkpoint ) {
                    startTime= QTime::currentTime();

#ifdef QT_DEBUG
                    qDebug() << "start emitted ";
#endif
                    mo_chkpoint = false;
                    bo_chkpoint = false;
                }
                m_moveIn=false;
                moved = true;
                break;
            }
            else if( pieces.at(i).contains("mo") ) {
#ifdef QT_DEBUG
                qDebug()<< " " << "broken text: " << pieces.at(i) ;
#endif
                if( m_VideoCapture.isOpened() ) {
                    m_VideoCapture.release();
#ifdef QT_DEBUG
                    qDebug() << "Camera successfully disconnected";
#endif
                }
                if(m_isBeta){
                    emit initCam();
                }else{
                    emit initGammaCam();
                }
                mo_chkpoint = true;
                break;
            }
            else if ( pieces.at(i).contains("bo") ) {
                //emit enableInBtn(true);
                emit letBedIn();
                bo_chkpoint = true;
#ifdef QT_DEBUG
                qDebug()<< " " << "broken text: " << pieces.at(i);
#endif
            }
            else if(pieces.at(i).contains("bf") && moved){
                if(m_isBeta){
                    emit stopRecording();
                }else{
                    emit takeSnap();
                }


#ifdef QT_DEBUG
                qDebug()<< " " << "broken text: " << pieces.at(i);
#endif
                moved = false;
            }
        }
    }
    else if( !moveAndRec ) {
        QString copy = server_output;
        QRegExp sep("(\r\n)");
        QStringList pieces =  copy.split(sep);
        for(int i=0;i<pieces.count();i++) {
            if ( pieces.at(i).contains("mo") ) {
                if(m_calibrationMode)
                    emit closeTimeDialog();

                emit showDialogUntilOut();

#ifdef QT_DEBUG
                qDebug()<< " " << "moving out w/o m_VideoCaptureture: " << pieces.at(i);
#endif
            }
            else if ( pieces.at(i).contains("bo") ) {
                emit insertBedWithoutVid();


#ifdef QT_DEBUG
                qDebug()<< " " << "bed is out no vid: " << pieces.at(i);
#endif
            }else if(pieces.at(i).contains("mi")){
                moved=true;
            }else if(pieces.at(i).contains("bf")&& m_calibrationMode && moved){
                emit make_Start_btn_Avail();
                moved=false;
#ifdef QT_DEBUG
                qDebug()<< " " << "bed is in for calibration: " << pieces.at(i);
#endif
            }
        }
    }
}
