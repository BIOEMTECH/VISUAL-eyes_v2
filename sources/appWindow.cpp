#include "headers/appWindow.h"
#include "ui_appWindow.h"
#include "headers/readinputinfo.h"

appWindow::appWindow(QWidget *parent) :
    QMainWindow(parent),
    ui( new Ui::appWindow )
{
    ui->setupUi(this);

    m_pReadInputInfo = 0;
    m_pReadInputInfo = new ReadInputInfo();
    m_pReadInputInfo->readFile();


    //place dialog window on the center of the screen
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());

    connect(ui->calibration, SIGNAL( clicked() ), this, SLOT( calibrationClicked()));
    connect(ui->imaging, SIGNAL( clicked() ), this, SLOT( imagingClicked()));
    connect(ui->postImage, SIGNAL( clicked() ), this, SLOT( postProcessingClicked() ));
    connect(ui->actionInfo, SIGNAL( triggered( bool ) ), this, SLOT( printHelp() ) );
}

void appWindow::printHelp()
{
    const char date[] = __DATE__;
    const char time[]=__TIME__;

    QString qsDate(date);
    QString qsTime(time);

    QMessageBox::information(this,"Visual-Eyes info","Visual-Eyes software for PETsys.\n Version 2.3.0 compiled on: " + qsDate +", " + qsTime );
}

appWindow::~appWindow()
{
    if ( ui )
    delete ui;

    if ( m_pReadInputInfo )
        delete m_pReadInputInfo;
}

void appWindow::Init()
{

    QImage postProcImg = QImage(":/icons/PostProcessing_v2.png");
    QPixmap pixMapPostImg = QPixmap::fromImage( postProcImg );
    ui->postImage->setPixmap( pixMapPostImg );
    ui->postImage->setScaledContents(true);

    QImage gammaEyeImg = QImage(":/icons/red.png");
    QPixmap pixMapRed = QPixmap::fromImage( gammaEyeImg );

    QImage betaEyeImg = QImage(":/icons/betaEye.png");
    QPixmap pixMapBlue = QPixmap::fromImage( betaEyeImg );

    QImage calibrationImg = QImage(":/icons/calibration.png");
    QPixmap pixMapCalib = QPixmap::fromImage( calibrationImg );


    if ( m_pReadInputInfo->getSystemName().contains("SCC") ) { //Which means beta

        ui->imaging->setPixmap( pixMapBlue );
        ui->imaging->setScaledContents(true);

        ui->calibration->setPixmap(pixMapCalib);
        ui->calibration->setScaledContents(true);

        //ui->redImg->setDisabled(true);
    }else{
        //ui->betaImg->setDisabled(true);
        ui->imaging->setPixmap(pixMapRed);
        ui->imaging->setScaledContents(true);
        ui->calibration->setPixmap(pixMapCalib );
        ui->calibration->setScaledContents(true);
    }

    //layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void appWindow::imagingClicked()
{
    ///Start gamma or beta in imaging mode
    startWindow(false);
}

void appWindow::calibrationClicked()
{
    ///Start gamma or beta in calibration mode
    startWindow(true);
}


void appWindow::startWindow(bool calibrationMode){

    FramelessWindow *framelessWindow = new FramelessWindow();
    framelessWindow->setWindowIcon(this->style()->standardIcon( QStyle::SP_DesktopIcon) );

    if ( m_pReadInputInfo->getSystemName().contains("SCC") ) { //Which means beta

        framelessWindow->resize(1259, 705);

        betaEye *beta = new betaEye(m_pReadInputInfo, calibrationMode);
        framelessWindow->setContent(beta);

        betaWindowControls(beta,framelessWindow);

    }else{

        framelessWindow->resize(1259, 730);

        gamma_eye *gamma = new gamma_eye( m_pReadInputInfo, calibrationMode);
        framelessWindow->setContent(gamma);

        gammaWindowControls(gamma,framelessWindow);

    }

    framelessWindow->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->hide();
    framelessWindow->show();
}

void appWindow::gammaWindowControls(gamma_eye * gamma,FramelessWindow * window){

    connect(window,SIGNAL(closedWindow()),gamma,SLOT(closeWin()));
    connect(gamma,SIGNAL(exitToMainWindow()),window,SLOT(close()));
    connect(gamma,SIGNAL(exitToMainWindow()),this,SLOT(returnAndshow()));

    connect(this,SIGNAL(exitAndDelete()),window,SLOT(deleteLater()));
    connect(this,SIGNAL(exitAndDelete()),gamma,SLOT(deleteLater()));

    connect(gamma,SIGNAL(exitProgram()),window,SLOT(close()));
    connect(gamma,SIGNAL(exitProgram()),this,SLOT(on_actionExit_Program_triggered()));

}

void appWindow::betaWindowControls(betaEye * beta,FramelessWindow * window){

    connect(window,SIGNAL(closedWindow()),beta,SLOT(closeWin()));
    connect(beta,SIGNAL(exitToMainWindow()),window,SLOT(close()));
    connect(beta,SIGNAL(exitToMainWindow()),this,SLOT(returnAndshow()));

    connect(this,SIGNAL(exitAndDelete()),window,SLOT(deleteLater()));
    connect(this,SIGNAL(exitAndDelete()),beta,SLOT(deleteLater()));

    connect(beta,SIGNAL(exitProgram()),window,SLOT(close()));
    connect(beta,SIGNAL(exitProgram()),this,SLOT(on_actionExit_Program_triggered()));

}

void appWindow::beyeRestart()
{
    imagingClicked();
}

void appWindow ::postProcessingClicked()
{
    PostProcessing *post = new PostProcessing( m_pReadInputInfo );
    this->hide();
    post->show();
    connect(post,SIGNAL(closedWindow()),this,SLOT(returnAndshow()));
    connect(this,SIGNAL(exitAndDelete()),post,SLOT(deleteLater()));
}

void appWindow::returnAndshow()
{
    this->show();
    emit exitAndDelete();
}

void appWindow::on_actionExit_Program_triggered(){ this->close(); }

void appWindow::on_actionSearch_Database_triggered()
{
    Search * database = new Search(m_pReadInputInfo, this);
    database->Init();
    database->show();
}
