    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file gamma_eye.cpp
///
///	@brief main aquisition window with plots for g-eye(SPECT), that handles the live data aquisition and imaging
/// All main separated threads that are resposible for SPECT reconstruction start from here.
///
///
///	@author Aphrodite Toufa
/// @date   Created: 07.12.2018
/// @date   Updated: 29.7.2019
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QLocale>
#include "headers/gamma_eye.h"
#include "ui_gamma_eye.h"
#include <QDebug>

gamma_eye::gamma_eye(ReadInputInfo* inputInfo, bool calibrationMode, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::gamma_eye),
    m_pReadInputInfoGamma(inputInfo),
    m_calibrationMode(calibrationMode)
{
    m_dMaxCor = 0.0;
    m_dContrastPercentageSummed = 0.0;

    ui->setupUi(this);
    ui->menuMouse_Bed_Controls->menuAction()->setVisible(false);

    qRegisterMetaType<QVector<qreal>>("QVector<qreal>");
    qRegisterMetaType<QPolygonF>("QPolygonF");
    qRegisterMetaType<cv::Mat>("cv::Mat");

    ui->horizontalSlider->setFocusPolicy(Qt::StrongFocus);
    ui->horizontalSlider->setRange(0,100);
    ui->horizontalSlider->setTickPosition(QSlider::TicksBothSides);
    ui->horizontalSlider->setValue(100);
    ui->horizontalSlider->setTickInterval(10);
    ui->horizontalSlider->setSingleStep(10);
    ui->horizontalSlider->setEnabled(false);

    ui->hsContrastB->setFocusPolicy(Qt::StrongFocus);
    ui->hsContrastB->setRange(0,100);
    ui->hsContrastB->setTickPosition(QSlider::TicksBothSides);
    ui->hsContrastB->setValue(100);
    ui->hsContrastB->setTickInterval(10);
    ui->hsContrastB->setSingleStep(10);
    ui->hsContrastB->setEnabled(false);

    ui->opacitySlider->setFocusPolicy(Qt::StrongFocus);
    ui->opacitySlider->setRange(50,255);
    ui->opacitySlider->setTickPosition(QSlider::TicksBothSides);
    ui->opacitySlider->setValue(150);
    ui->opacitySlider->setTickInterval(10);
    ui->opacitySlider->setSingleStep(5);

    ui->opacitySlider->setEnabled(false);



    ui->PB_startDAQ->setEnabled(false);
    ui->PB_stopDAQ->setEnabled(false);

    ui->cb_fusion->setEnabled(false);
    ui->cb_xray->setEnabled(false);

    /// Calibration hide fusion and deactivate opacity

    if(m_calibrationMode){
        ui->cb_fusion->hide();
        ui->cb_xray->hide();
        ui->opacityLabel->hide();
        ui->opacitySlider->hide();
    }else{
        ///Hide the validation results tab
        ui->tabWidget->removeTab(2);
    }
    qwt_plots();
    Initiate();
}

gamma_eye::~gamma_eye()
{
    delete_qwt_plots_and_globals();
    delete ui;
}

void gamma_eye::qwt_plots()
{
    //Colormap instance, default colormap is royal (same with ImageJ Royal)
    cM=new ColorMap();
    cM->BlackBased(1);

    //Qwt Plot for the corrected image
    correctedPlot = new QwtPlot(this);
    //the dimensions of the plot are the crystal's grid x and y dimensions
    correctedPlot->setAxisScale(QwtPlot::xBottom, 0.0,crystal_pixels_y,0 ); // we want the start point of the axes x,y(0,0) to be on the upper left point of the plot
    correctedPlot->setAxisScale(QwtPlot::yLeft,crystal_pixels_x,0.0,0 ); // that's why we set the dimensions of the plot this way.
    correctedPlot->plotLayout()->setAlignCanvasToScales(true);
    correctedPlot->enableAxis(QwtPlot::xBottom,false);
    correctedPlot->enableAxis(QwtPlot::yLeft,false);

    ui->corrected->addWidget(correctedPlot); // add qwt plot to layout

    //Spectrogram for corrected plot
    correctedPlot_spectrogram = new QwtPlotSpectrogram();
    correctedPlot_spectrogram->setColorMap(cM);
    correctedPlot_spectrogram->setRenderThreadCount(1); // use system 1 thread for rendering plot
    correctedPlot_spectrogram->attach(correctedPlot);

    //Qwt Plot for cumulative/summed image
    summedCorrectedPlot= new  QwtPlot(this);
    summedCorrectedPlot->setAxisScale(QwtPlot::xBottom, 0.0,crystal_pixels_y,0 );
    summedCorrectedPlot->setAxisScale(QwtPlot::yLeft,crystal_pixels_x,0.0,0 );
    summedCorrectedPlot->plotLayout()->setAlignCanvasToScales( true );
    summedCorrectedPlot->enableAxis( QwtPlot::xBottom,false);
    summedCorrectedPlot->enableAxis( QwtPlot::yLeft,false);

    ui->summed->addWidget(summedCorrectedPlot); //add plot to layout

    //Spectrogram for cumulative/summed plot
    summedCorrectedPlot_spectrogram = new  QwtPlotSpectrogram();
    summedCorrectedPlot_spectrogram->setColorMap(cM);
    summedCorrectedPlot_spectrogram->setRenderThreadCount(1); // use system 1 thread for rendering plot
    summedCorrectedPlot_spectrogram->attach(summedCorrectedPlot);

    //energy plot
    energyPlot=new QwtPlot(this);

    energyPlot->setAxisScale(QwtPlot::xBottom,0,output_size_x,0); //Scale the x-axis
    energyPlot->setAxisScale(QwtPlot::yLeft,0,0,0);

    energyPlot->plotLayout()->setAlignCanvasToScales(true);

    ui->Energy_Spectrum->addWidget(energyPlot); //add plot to the layout

    // the graph of the energy plot, we are constructing a histogram
    curve = new  QwtPlotCurve();
    curve->setPen( Qt::black, 1);
    curve->setRenderThreadCount(1);
    curve->setRenderHint(QwtPlotItem::RenderAntialiased, true );
    curve->attach(energyPlot);

    // Qwt plot for the raw data image, we see the direct data from the crystals
    RawPlot= new QwtPlot(this);
    RawPlot->plotLayout()->setAlignCanvasToScales( true );
    RawPlot->setAxisScale(QwtPlot::xBottom, 0.0,output_size_y,0 );
    RawPlot->setAxisScale(QwtPlot::yLeft,output_size_x,0.0,0 );
    RawPlot->enableAxis(QwtPlot::xBottom, false);
    RawPlot->enableAxis(QwtPlot::yLeft,false);

    ui->Raw->addWidget(RawPlot);

    rawPlot_spectrogram = new QwtPlotSpectrogram();
    rawPlot_spectrogram->setColorMap(cM);
    rawPlot_spectrogram->setRenderThreadCount(1); // use system 1 thread for rendering plot
    rawPlot_spectrogram->attach(RawPlot);

    rawMatrix = new QwtMatrixRasterData();
    corMatrix = new  QwtMatrixRasterData();
    sumCorMatrix = new  QwtMatrixRasterData();

    rawMatrix->setInterval( Qt::XAxis, QwtInterval( 0,output_size_y) );
    rawMatrix->setInterval( Qt::YAxis, QwtInterval( 0,output_size_x) );

    corMatrix->setInterval( Qt::XAxis, QwtInterval( 0,crystal_pixels_y) );
    corMatrix->setInterval( Qt::YAxis, QwtInterval( 0,crystal_pixels_x));

    sumCorMatrix->setInterval( Qt::XAxis, QwtInterval( 0, crystal_pixels_y) );
    sumCorMatrix->setInterval( Qt::YAxis, QwtInterval( 0, crystal_pixels_x) );

    rawMatrix->setInterval( Qt::ZAxis, QwtInterval( 0, 0) );
    corMatrix->setInterval( Qt::ZAxis, QwtInterval( 0, 0) );
    sumCorMatrix->setInterval(Qt::ZAxis, QwtInterval( 0, 0));

    if(m_calibrationMode){
        qwt_validation_plots();
    }
    PlotItemsAttached=true;
}

void gamma_eye::qwt_validation_plots(){
    /**
       Qwt validation plots
    */

    correctedHead=new QwtPlot(this);
    correctedHead->setAutoDelete(true);

    correctedHead->setAxisScale(QwtPlot::xBottom,0,2048,0);
    correctedHead->setAxisScale(QwtPlot::yLeft,0,0,0);
    correctedHead->plotLayout()->setAlignCanvasToScales(true);

    ui->correctedHead_layout->addWidget(correctedHead);

    correctedCurve = new QwtPlotCurve();
    correctedCurve->setPen( Qt::black, 1);
    correctedCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    correctedCurve->attach(correctedHead);

}

void gamma_eye::Initiate()
{
    m_dActivity = 0.0;
    nextStudy = new continueStudy(this);
    exitCalib = new calibrationExit(this);
    deviceOPeratorID=0;
    duration_time=0;
    frame_time=0;
    counter=0;
    DAQdurationProgress=0;
    frameProgress=0;

    fastDynamic = false;
    noTimeSettings = false;
    frameCount= 0;
    okFromCam = false;
    okFromFPGA=false;


    aboutToExit=false;
    arduinoConfigured=false;
    FPGAconfigured=false;
    timeFinishBtnPressed=false;
    bedMoved=false;
    m_bedCalibrated =false;

    freeBytes   = new QSemaphore(64000);
    usedBytes   = new QSemaphore(0);
    globalMutex = new QMutex();

    BUFFER  = new boost::circular_buffer<quint32>(64000);

    connect(ui->opacitySlider, SIGNAL(valueChanged(int)), this, SLOT( opacityValueChanged(int)));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int)));
    connect(ui->hsContrastB, SIGNAL(valueChanged(int)), this, SLOT(sliderSummedValueChanged(int)));
    connect(ui->cb_colormap,SIGNAL(currentIndexChanged(int)),this,SLOT(cb_ColorMap_currentIndexChanged(int)));

    FPGA= new fpga(this);
    bed = new arduino(m_pReadInputInfoGamma, this,1);

    if( !FPGA->check_lsusb() || !bed->check_connection() ) {
        while( !FPGA->check_lsusb() || !bed->check_connection() ) {
            QMessageBox msg;
            msg.setIcon(QMessageBox::Critical);
            msg.setWindowFlags(Qt::WindowStaysOnTopHint);
            msg.setText("Error: The hardware is not connected, please check cable connections and press Retry.");
            msg.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
            qint32 ch;
            QTime dieTime;

            ch = msg.exec();

            switch(ch)
            {
            case QMessageBox::Retry:
            {
                msg.hide();
                dieTime = QTime::currentTime().addMSecs(200);
                QMessageBox msg;
                msg.setIcon(QMessageBox::Information);
                msg.setWindowFlags(Qt::WindowStaysOnTopHint);
                msg.setText("Please check cable connections and press ok. If problem persists restart gamma-eye system.");
                msg.setStandardButtons(QMessageBox::Ok);

                while( QTime::currentTime() < dieTime ){}
                msg.exec();
            }
                break;
            case QMessageBox::Cancel:
                std::exit(EXIT_FAILURE);
            default: //Nikos: Check this!
                break;
            }
        }
    }

    connect( bed, SIGNAL(server_IsOpen() ),this,SLOT(arduino_initState()));
    connect( FPGA, SIGNAL(initialisationComplete()),this,SLOT(FPGA_initState()));

    if(m_calibrationMode)
        calibrationCycle();
    else
        StudyCycle();
}

void gamma_eye::arduino_initState(){ arduinoConfigured=true; }

void gamma_eye::FPGA_initState(){ FPGAconfigured=true; }

void gamma_eye::StudyCycle()
{
    opDialog = new operatorDialog(this);
    time = new timeSettings(this);
    study_details = new detailsDialog(m_pReadInputInfoGamma,"gammaEye", this);
    m_validationOn=false;

    configureArduino();

    connect(this,SIGNAL(sendStudyDir(QString)),bed,SLOT(getStudyDir(QString)));
    connect(bed,SIGNAL(letBedIn()),this,SLOT(insertCapture()));
    connect(this,SIGNAL(bedInsertSignal(bool)),bed,SLOT(bedIn(bool)));
    connect(bed,SIGNAL( make_Start_btn_Avail() ),this,SLOT( getCameraFeedback()) );
    connect(bed,SIGNAL(insertBedWithoutVid()),this,SLOT(insertNoCapture()));
    connect(bed,SIGNAL(showDialogUntilOut()),this,SLOT(exitBedDialog()));

    connect(bed,SIGNAL( sendCameraError(int) ), this, SLOT(fpgaErrorMsg(int)) );

    connect(bed,SIGNAL(initGammaCam()),this, SLOT(bedEjectState()), Qt::UniqueConnection);
    connect(bed,SIGNAL(ejectSent()),this, SLOT(arduinoSocketState()), Qt::UniqueConnection);

    connect(FPGA,SIGNAL(sendErrorCode(int)),this,SLOT(fpgaErrorMsg(int)));

   // connect(FPGA,SIGNAL( downloadSuccesfull() ), this, SLOT( enableButton() ) );
    connect(FPGA,SIGNAL(exitBash()),this, SIGNAL(exitToMainWindow()));
    connect(FPGA,SIGNAL(exitBash()),this,SLOT(close()));

    connect(ui->PB_startDAQ,SIGNAL(pressed()),this,SLOT(PB_startDAQ_clicked()));
    connect(FPGA,SIGNAL(readyRead()),this,SLOT(startAquisition()));

    connect(ui->cb_fusion,SIGNAL(clicked()),this,SLOT(setCheckstateOptical()));
    connect(ui->cb_xray,SIGNAL(clicked()),this,SLOT(setCheckstateXray()));

    connect(ui->PB_stopDAQ,SIGNAL(pressed()),this,SLOT(stopAquisition()));
    connect(this,SIGNAL(onPressedStop()),FPGA,SLOT(stop()));

    connect(this, SIGNAL( terminate_fpga() ), FPGA, SLOT( terminate() ) );

    connect(opDialog,SIGNAL(sendName(QString)),this,SLOT(getOperator(QString)));

    connect(opDialog,SIGNAL(nextPressed()),study_details,SLOT(show()));
    connect(opDialog,SIGNAL(exitToMainMenu()),this,SLOT(on_actionGo_back_to_main_menu_triggered()));

    connect( study_details,SIGNAL(previousPressed()),opDialog,SLOT(show()));

    connect( study_details, SIGNAL( nextPressed()),time,SLOT(show()));
    connect( study_details, SIGNAL( sendStudyID(QString,QString,QString,QString)),this,SLOT( getStudyID( QString, QString, QString, QString ) ) );
    connect( study_details, SIGNAL( sendNuclide(QString) ), this, SLOT( changeVoltage(QString) ) );
    connect( study_details, SIGNAL( sendDacayInfo( const QString, const QString, const QString, QDateTime, const double, QString ) ), this, SLOT( setDecayInfo( const QString, const QString, const QString, QDateTime, const double, QString ) ) );

    connect(time, SIGNAL(previousPressed()), study_details,SLOT(show()));
    connect(time, SIGNAL(sendTimeSettings(int,int, QString,QString,bool)), study_details,SLOT(getTimeSettings(int,int, QString,QString,bool)));
    connect(time, SIGNAL(sendTimeSettings(int,int, QString,QString,bool)),this,SLOT(AquisitionData(int,int,QString,QString,bool)));

    connect(time,SIGNAL(finishPressed()),this,SLOT(timeFinishedPressed()));

    connect(this,SIGNAL(closeTimeSettings()),time,SLOT(hide()));
    connect(this,SIGNAL(openTimeSettings()),time,SLOT(show()));

    connect(this, SIGNAL(saveStudyToDatabase(QString,QString,QString,QString)), study_details,SLOT(save_Session(QString,QString,QString,QString)));

    connect(nextStudy,SIGNAL(followUp()),study_details,SLOT(show()));
    connect(nextStudy,SIGNAL(followUp()),this,SLOT(enableButton()));
    connect(nextStudy,SIGNAL(followUp()),this,SLOT(reset()));
    //


    connect(nextStudy,SIGNAL(restartStudy()),time,SLOT(show()));
    connect(nextStudy,SIGNAL(restartStudy()),study_details,SLOT(requestNewStudyID()));
    connect(nextStudy,SIGNAL(restartStudy()),this,SLOT(reset()));
    connect(nextStudy,SIGNAL(restartStudy()),this,SLOT(disableStartButton()));
    //


    connect(nextStudy,SIGNAL(exit()),opDialog,SLOT(close()));
    connect(nextStudy,SIGNAL(exit()),study_details,SLOT(close()));
    connect(nextStudy,SIGNAL(exit()),time,SLOT(close()));
    connect(nextStudy,SIGNAL(exit()),this,SLOT(closeWin()));
    connect(nextStudy,SIGNAL(exit()),this,SLOT(reset()));
   //

    connect(this,SIGNAL(exit()),opDialog,SLOT(close()));
    connect(this,SIGNAL(exit()),study_details,SLOT(close()));
    connect(this,SIGNAL(exit()),time,SLOT(close()));
}


void gamma_eye::calibrationCycle()
{
    opDialog = new operatorDialog(this);
    calibTime = new calibrationTime(this);
    calibDetails = new calibrationDialog(m_pReadInputInfoGamma,"gammaEye", this);

    configureArduino();

    connect(this,SIGNAL(sendStudyDir(QString)),bed,SLOT(getStudyDir(QString)));
    connect(bed,SIGNAL(letBedIn()),this,SLOT(insertNoCapture()));
    connect(this,SIGNAL(bedInsertSignal(bool)),bed,SLOT(bedIn(bool)));
    connect(bed,SIGNAL( make_Start_btn_Avail() ),this,SLOT( getCameraFeedback()) );
    connect(bed,SIGNAL(insertBedWithoutVid()),this,SLOT(insertNoCapture()));
    connect(bed,SIGNAL(showDialogUntilOut()),this,SLOT(exitBedDialog()));

    connect(bed,SIGNAL( sendCameraError(int) ), this, SLOT(fpgaErrorMsg(int)) );

    connect(bed,SIGNAL(initGammaCam()),this, SLOT(bedEjectState()), Qt::UniqueConnection);
    connect(bed,SIGNAL(ejectSent()),this, SLOT(arduinoSocketState()), Qt::UniqueConnection);

    connect(FPGA,SIGNAL(sendErrorCode(int)),this,SLOT(fpgaErrorMsg(int)));

    connect(FPGA,SIGNAL(exitBash()),this, SIGNAL(exitToMainWindow()));
    connect(FPGA,SIGNAL(exitBash()),this,SLOT(close()));




    connect(ui->PB_startDAQ,SIGNAL(pressed()),this,SLOT(PB_startDAQ_clicked()));
    connect(FPGA,SIGNAL(readyRead()),this,SLOT(startAquisition()));

    connect(ui->cb_fusion,SIGNAL(clicked()),this,SLOT(setCheckstateOptical()));
    connect(ui->cb_xray,SIGNAL(clicked()),this,SLOT(setCheckstateXray()));

    connect(ui->PB_stopDAQ,SIGNAL(pressed()),this,SLOT(stopAquisition()));
    connect(this,SIGNAL(onPressedStop()),FPGA,SLOT(stop()));

    connect(this, SIGNAL( terminate_fpga() ), FPGA, SLOT( terminate() ) );

    connect(opDialog,SIGNAL(sendName(QString)),this,SLOT(getOperator(QString)));

    connect(opDialog,SIGNAL(nextPressed()),calibDetails,SLOT(show()));
    connect(opDialog,SIGNAL(exitToMainMenu()),this,SLOT(on_actionGo_back_to_main_menu_triggered()));

    connect( calibDetails,SIGNAL(previousPressed()),opDialog,SLOT(show()));

    connect( calibDetails, SIGNAL( nextPressed()),calibTime,SLOT(show()));
    connect( calibDetails, SIGNAL( sendCalibrationID(QString,bool)),this,SLOT(getCalibrationID(QString,bool)) );
    connect( calibDetails, SIGNAL( sendNuclide(int) ), this, SLOT( changeVoltage(int) ) );
    connect( calibDetails, SIGNAL( sendDacayInfo( const QString, const QString, const QString, QDateTime, const double, QString ) ), this, SLOT( setDecayInfo( const QString, const QString, const QString, QDateTime, const double, QString ) ) );

    connect(calibTime, SIGNAL(previousPressed()), calibDetails,SLOT(show()));
    connect(calibTime, SIGNAL(sendTimeSettings(int,int, QString,QString,bool)), calibDetails,SLOT(getTimeSettings(int,int, QString,QString,bool)));
    connect(calibTime, SIGNAL(sendTimeSettings(int,int, QString,QString,bool)),this,SLOT(AquisitionData(int,int,QString,QString,bool)));

    connect(calibTime,SIGNAL(finishPressed()),this,SLOT(timeFinishedPressed()));

    connect(this,SIGNAL(closeTimeSettings()),calibTime,SLOT(hide()));
    connect(this,SIGNAL(openTimeSettings()),calibTime,SLOT(show()));

    connect(this, SIGNAL(saveStudyToDatabase(QString,QString,QString,QString)), calibDetails,SLOT(save_Session(QString,QString,QString,QString)));



    connect(exitCalib,SIGNAL(exit()),opDialog,SLOT(close()));
    connect(exitCalib,SIGNAL(exit()),calibDetails,SLOT(close()));
    connect(exitCalib,SIGNAL(exit()),calibTime,SLOT(close()));
    connect(exitCalib,SIGNAL(exit()),this,SLOT(closeWin()));
    connect(exitCalib,SIGNAL(exit()),this,SLOT(reset()));
   //

    connect(this,SIGNAL(exit()),opDialog,SLOT(close()));
    connect(this,SIGNAL(exit()),calibDetails,SLOT(close()));
    connect(this,SIGNAL(exit()),calibTime,SLOT(close()));
}

void gamma_eye::configureArduino(){

    QTime dieTime = QTime::currentTime().addSecs(20);
    QMessageBox mes;
    mes.setIcon(QMessageBox::Information);
    mes.setText("Initializing hardware. \nPlease wait...");
    mes.setStandardButtons(QMessageBox::NoButton);
    mes.show();

    bool initStarted=false;
    while( QTime::currentTime() <= dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents);

        if(QTime::currentTime() == dieTime) {
            while(!FPGAconfigured && !arduinoConfigured) {
                QCoreApplication::processEvents(QEventLoop::AllEvents);
                if(!initStarted) {
                    FPGA->Initialize_ADC_SPECT();
                    bed->configure_ttyACM0();
                    bed->reset();
                    initStarted=true;
                }
            }
        }
    }
    mes.close();

    opDialog->show();
    FPGA->download_SPECT_FPGA_script();
}

void gamma_eye::getOperator(QString name) { deviceOPerator = name;}

void gamma_eye::setDecayInfo( const QString collimator, const QString folder, const QString name, QDateTime dateTime, const double activity, QString actUnit )
{
    m_qsNuclidedFolder = collimator+"/"+folder;
    m_qsCollimator=collimator;
    m_qsNuclideName = name;
    m_qdtInjectionDateTime = dateTime;
    m_dActivity = activity;
    m_sActivityUnit = actUnit;
    m_newIsotope = m_pReadInputInfoGamma->getSpectIsotope(collimator,m_qsNuclideName);

}

void gamma_eye::getStudyID(QString ID, QString name,QString patient,QString proj)
{
    StudyID = ID;
    studyName = name;
    animal = patient;
    project = proj;
}

void gamma_eye::getCalibrationID(QString ID,bool validationOn)
{
    StudyID = ID;
    studyName = "Flood experiment";
    project = " ";
    m_validationOn=validationOn;
    exitCalib->setTypeOfStudy(m_validationOn);
}

void gamma_eye::changeVoltage(QString voltage_script){ bed->changeVoltage( voltage_script ); }

void gamma_eye::timeFinishedPressed(){ timeFinishBtnPressed = true; }

void gamma_eye::bedEjectState()
{
    bedMoved = true;
    emit closeTimeSettings();
}

void gamma_eye::arduinoSocketState()
{
    //This is not needed!!!
/*    if( timeFinishBtnPressed && !bedMoved) {
        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setAttribute( Qt::WA_DeleteOnClose );
        msgBox->setStandardButtons( QMessageBox::Ok );
        msgBox->setWindowTitle( tr("Information") );
        msgBox->setText( tr("Something is wrong with a component's serial connection.Please press ok to restart the program.") );
        msgBox->setModal(false);
        msgBox->open( this, SLOT(RestartApplication()));
    }*/
}

void gamma_eye::AquisitionData(int duration,int frame, QString d_unit,QString f_unit, bool fDynamic)
{
    fastDynamic= fDynamic;

    if(m_calibrationMode){
        if ( d_unit == "min" )
            duration_time = duration*60;
        else if ( d_unit == "hr" )
            duration_time = duration*3600;

        if ( f_unit == "min" )
            frame_time = frame*60;
        else if ( f_unit == "hr" )
            frame_time = frame*3600;
    }else{
        if ( d_unit == "sec" )
            duration_time = duration;
        else if ( d_unit == "min" )
            duration_time = duration*60;

        if ( f_unit == "sec" )
            frame_time = frame;
        else if ( f_unit == "min" )
            frame_time = frame*60;
    }

    if ( frame_time ==0 || duration_time ==0) {
        QMessageBox* msgBox = new QMessageBox( this );
        msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        msgBox->setStandardButtons( QMessageBox::Ok );
        msgBox->setWindowTitle( tr("Attention") );
        msgBox->setText( tr("Please define an experiment time duration and frame time duration before starting the aquisition.") );
        msgBox->setModal(false); // if you want it non-modal
        msgBox->open( this, SIGNAL(openTimeSettings()));
    }  //error messgae if user does not choose an duration and time combination
    else {
        if( duration_time % frame_time == 0 ) {
            ui->daq_progress->setMinimum(0);
            ui->daq_progress->setMaximum(duration_time);
            ui->frame_progress->setMinimum(0);
            ui->frame_progress->setMaximum(frame_time);

            ui->LE_frameRate->setText(QString::number(frame) + " "+ f_unit);
            ui->LE_duration->setText(QString::number(duration) + " "+ d_unit);
            ui->TL_studyID->setText(StudyID);
            ui->TL_studyName->setText(studyName);
            ui->TL_animalID->setText(animal);
            ui->TL_project->setText(project);

            ui->LE_radioNuclide->setText( m_qsNuclideName );
            ui->LE_injectActivity->setText( QString::number( m_dActivity ) + " " +  m_sActivityUnit );

            directoryCreation();


            if(m_calibrationMode){
                if(!m_bedCalibrated){
                    bed->calibCalibrate();
                    QTime waitTime = QTime::currentTime().addSecs(2);
                    while(QTime::currentTime()< waitTime) {
                        QCoreApplication::processEvents(QEventLoop::AllEvents);
                    }
                    m_bedCalibrated=true;
                }
                bed->calibEject_bed(); //eject bed and start the capturing process
            }
            else{
                bed->eject_bed(); //eject bed and start the capturing process
            }

            if( noTimeSettings ) {
                ui->PB_startDAQ->setEnabled(true);
                noTimeSettings=false;
            }
        }  //error message if user select an invalid experiment and frame time duration.
        else  {
            QMessageBox* msgBox = new QMessageBox( this );
            msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
            msgBox->setStandardButtons( QMessageBox::Ok );
            msgBox->setWindowTitle( tr("Attention") );
            msgBox->setText( tr("Please select an experiment time duration and frame time duration that their combination gives a complete division.") );
            msgBox->setModal(false); // if you want it non-modal
            msgBox->open( this, SIGNAL(openTimeSettings() ) );
        }



    }
}

void gamma_eye::insertCapture()
{
    QMessageBox* msgBox = new QMessageBox( this );
    msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
    msgBox->setStandardButtons( QMessageBox::Ok );
    msgBox->setWindowTitle( tr("Info") );
    if(m_calibrationMode)
        msgBox->setText( tr("Acquisition time setting are all set. Please ensure that the flood phantom was placed correctly and press ok, to insert the bed inside the system.") );
    else
        msgBox->setText( tr("Acquisition time setting are all set. Please prepare the mouse and press ok when you are ready, to insert the bed inside the system.") );

    msgBox->setModal(false); // if you want it non-modal
    msgBox->open( this, SLOT(msgBoxClosed(QAbstractButton*)) );
}

void gamma_eye::insertNoCapture()
{
    if (msgInBox )
        msgInBox->reject();

    QMessageBox* msgBox = new QMessageBox( this );
    msgBox->setAttribute( Qt::WA_DeleteOnClose );
    msgBox->setStandardButtons( QMessageBox::Ok );
    msgBox->setWindowTitle( tr("Info") );
    if(m_calibrationMode)
        msgBox->setText( tr("Please press ok, when you are ready, to insert the bed back inside.") );
    else
        msgBox->setText( tr("Please press ok, when you are ready, to insert the mouse bed back inside.") );
    msgBox->setModal( false );
    msgBox->open( this, SLOT(msgBoxBedIn(QAbstractButton*)) );
}

void gamma_eye::exitBedDialog()
{
    msgInBox= new QMessageBox( this );
    msgInBox->setAttribute( Qt::WA_DeleteOnClose );
    msgInBox->setStandardButtons(QMessageBox::NoButton);
    msgInBox->setWindowTitle( tr("Info") );

    if(m_calibrationMode)
        msgInBox->setText( tr("Moving bed out, please remove phantom...") );
    else
        msgInBox->setText( tr("Moving bed out, please retrieve mouse...") );
    msgInBox->setModal(true);
    msgInBox->show();
}

void gamma_eye::msgBoxBedIn(QAbstractButton*)
{
    if ( aboutToExit ) {
        emit exit();
        emit terminate_fpga();
        if(m_calibrationMode)
            bed->calibInsert_bed();
        else
            bed->onlyMoveBedIn();
        bed->exit();
    }
    else{
        if(m_calibrationMode)
            bed->calibInsert_bed();
        else
            bed->onlyMoveBedIn();
    }
}

void gamma_eye::msgBoxClosed(QAbstractButton*){
    if(m_calibrationMode)
        bed->calibInsert_bed();
    else
        bed->insert_bed();
    emit bedInsertSignal(true);
}

void gamma_eye::msgBox2Closed(QAbstractButton*){
    if(m_calibrationMode)
        bed->calibInsert_bed();
    else
        bed->insert_bed();
}

void gamma_eye::getCameraFeedback() //NIKOS
{
    bool bCont = FPGA->isOK();

    if ( bCont || ui->PB_startDAQ->isEnabled() )
        ui->PB_startDAQ->setEnabled(true);
}

void gamma_eye::directoryCreation()
{
    QString pathName;
    if(m_calibrationMode)
        pathName = QStandardPaths::locate(QStandardPaths::DocumentsLocation,"CALIBRATE-eyes",QStandardPaths::LocateDirectory);
    else
        pathName= QStandardPaths::locate(QStandardPaths::DocumentsLocation,"VISUAL-eyes",QStandardPaths::LocateDirectory);


    QLocale locale(QLocale::English);
    QString date = locale.toString(QDateTime::currentDateTime(), "ddMMyyyy_hhmmssAP");

    QString Op;
    pathName.append("/g-eye");
    pathName.append("/"+deviceOPerator);
    pathName.append("/" + StudyID);
    Storage.setPath(pathName);

    img.setPath(Storage.absolutePath());
    img.mkpath("IMAGES");
    img.setPath(img.absolutePath().append("/IMAGES"));

    rawdata.setPath(img.absolutePath());
    rawdata.mkdir("RAW");
    rawdata.setPath(rawdata.absolutePath().append("/RAW"));

    raw.setPath(rawdata.absolutePath());
    raw.mkdir("LIST_MODE");
    raw.setPath(raw.absolutePath().append("/LIST_MODE"));

    corrected.setPath(rawdata.absolutePath());
    corrected.mkdir("CORRECTED");
    corrected.setPath(corrected.absolutePath().append("/CORRECTED"));

    deconvoluted.setPath(img.absolutePath());
    deconvoluted.mkdir("FINAL");
    deconvoluted.setPath(deconvoluted.absolutePath().append("/FINAL"));

    QDir fusion = corrected;
    fusion.mkdir("FUSION");
    fusion.mkdir("XRAY");
    fusion.setPath(fusion.absolutePath().append("/FUSION"));

    QDir fusionDeconv = deconvoluted;
    fusionDeconv.mkdir("FUSION");
    fusionDeconv.mkdir("XRAY");
    fusionDeconv.setPath(fusionDeconv.absolutePath().append("/FUSION"));

    post.setPath(Storage.absolutePath());
    post.mkdir("POST_PROCESSING");
    post.setPath(post.absolutePath().append("/POST_PROCESSING"));

    QDir temp(post.absolutePath());

    postD = temp.absolutePath();

    post.setPath(post.absolutePath());
    post.mkdir("DICOM");
    post.mkdir("Report_Images");
    post.setPath(post.absolutePath().append("/Report_Images"));

    rawD = rawdata.absolutePath();
//    corrD = corrected.absolutePath();
    corrD = deconvoluted.absolutePath();
    m_qsDeconvDir = deconvoluted.absolutePath();

    emit sendStudyDir( Storage.absolutePath() );
}

void gamma_eye::infoFileGenerator()
{
    QSqlQuery q;
    QString date,startTime,finTime,comments,duration,frame,exp_tU,frame_tU;
    QString name, animal_name, breed, species, age, weight, gender, r_pharma, volume;
    QString deviceid, activity, injection_date,path_id, isFastDynamic;
    QString Device, mod_name, Operator, Radionuclide, project, injected_activity, marking, fileDirectory;
    QDateTime injTconv;
    int radioUnit;

    QString string = "SELECT * FROM Study WHERE Study.study_id= " + StudyID;
    q.exec(string);
    if ( q.next() ) {
        deviceid= q.value("deviceid").toString();
        date = q.value("date").toString();
        name = q.value("name").toString();
        animal_name = q.value("animal_name").toString();
        breed = q.value("breed").toString();
        species = q.value("species").toString();
        age = q.value("age").toString();
        weight = q.value("weight").toString();
        path_id = q.value("path_id").toString();
        if( q.value("gender").toInt()==0)
            gender="F";
        else
            gender="M";
        r_pharma = q.value("r_pharma").toString();
        volume = q.value("volume").toString();
        activity = q.value("activity").toString();
        injection_date = q.value("injection_date").toString();
        injTconv = QDateTime::fromString(injection_date,"yyyy-MM-ddThh:mm:ss.zzz");
        injection_date =injTconv.toString("dd.MM.yyyy hh:mm:ss AP");
        duration = q.value("exp_duration").toString();
        frame = q.value("frame").toString();
        startTime = q.value("start_time").toString();
        finTime = q.value("fin_time").toString();
        Operator = q.value("operator_name").toString();
        exp_tU = q.value("timeUnit_exp").toString();
        frame_tU = q.value("timeUnit_frame").toString();
        project = q.value("project").toString();
        injected_activity = q.value("injected_activity").toString();
        comments = q.value("comments").toString();
        marking = q.value("marking").toString();
        fileDirectory = q.value("fileDirectory").toString();
        radioUnit = q.value("radioUnit").toInt();
        isFastDynamic =q.value("fastDynamic").toString();
    }

    QString filename = Storage.absolutePath().append("/StudyInfo.txt");
    QFile file;
    file.setFileName(filename);

    QTextStream out(&file);
    if(file.open(QIODevice::WriteOnly))
    {
        out << "ID: " << StudyID << "\n";
        out << "Device: " << deviceid << endl;
        out << "System: " << m_pReadInputInfoGamma->getSystemName() << endl;
        out << "Image Flip: " << m_pReadInputInfoGamma->getFlips().join(",") << endl;
        out << "Name: " << name << endl;
        out << "Project: " << project << endl;
        out << "Animal name: " << animal_name << endl;
        out << "Breed: " << breed << endl;
        out << "Species: " << species << endl;
        out << "Age: " << age << endl;
        out << "Marking: " << marking << endl;
        out << "Weight: " << weight << endl;
        out << "Gender: " << gender << endl;
        out << "Collimator: " << m_qsCollimator << endl;
        out << "Radionuclide: " << m_qsNuclideName << endl;
        if ( radioUnit == 0)
            out << "Radio unit: " << "MBq" << endl;
        else
            out << "Radio unit: " << "uCi" << endl;
        

        out << "Radiopharmaceutical: " << r_pharma << endl;
        spectIsotope chosenIsotope=m_pReadInputInfoGamma->getSpectIsotope(m_qsCollimator,m_qsNuclideName);

        out << "Limits: " << chosenIsotope.getLimit1()<< " " << chosenIsotope.getLimit2() << endl;
        out << "Activity parameters a: " << chosenIsotope.getA1() << " " << chosenIsotope.getA2() << " " << chosenIsotope.getA3() << endl;
        out << "Activity parameters b: " << chosenIsotope.getB1() << " " << chosenIsotope.getB2() << " " << chosenIsotope.getB3() << endl;


        out << "Volume: " << volume << endl;
        if ( path_id == "1")
            out << "Injection path: " << "Intravenous" << endl;
        else if ( path_id == "2")
            out << "Injection path: " << "Intraperitoneal" << endl;
        else if ( path_id == "3")
            out << "Injection path: " << "Inhalation" << endl;
        else if ( path_id == "4")
            out << "Injection path: " << "Intramuscular" << endl;
        else if ( path_id == "5")
            out << "Injection path: " << "Ingestion" << endl;
        else if ( path_id == "6")
            out << "Injection path: " << "Intratracheal" << endl;

        out << "Injected activity:" << injected_activity << endl;
        out << "Injection date: " << injection_date << endl;
        out << "Operator: " << Operator << endl;
        out << "Experiment time unit: " << exp_tU << endl;
        out << "Frame time unit: " << frame_tU << endl;
        out << "Date: " << date << "\n";
        out << "Start Time: " << startTime << "\n";
        out << "Finish Time: " << finTime << "\n";
        if ( isFastDynamic == "0")
            out << "Fast Dynamic: " << "No" << endl;
        else
            out << "Fast Dynamic: " << "Yes" << endl;

        if ( fastDynamic ) {
            out << "Experiment Duration: " << "60" << " " << "min" << "\n";
            out << "Frame Duration: " << "0-1 min: 10sec ,"<< " "<< " 1-5 min: 30sec ," << " "<< "5-10 min: 60sec ," << " " << "10-60 min: 120 sec " << "\n\n";
        }
        else{
            out << "Experiment Duration: " << duration << " " << exp_tU << "\n";
            out << "Frame Duration: " << frame << " " << frame_tU <<"\n\n";
        }
        out << "Comments: " << comments ;
    }
    file.close();
}


void gamma_eye::calibrationInfoGenerator()
{
    QSqlQuery q;
    QString dateTimeConv,startTime,finTime,comments,duration,frame,exp_tU,frame_tU;
    QString name, volume, deviceid, activity, date_time;
    QString Operator, fileDirectory;
    QDateTime dTconv;
    int radioUnit;

    QString string = "SELECT * FROM Calibration WHERE Calibration.study_id= " + StudyID;
    q.exec(string);
    if ( q.next() ) {
        deviceid= q.value("deviceid").toString();
        name = q.value("name").toString();
        volume = q.value("volume").toString();
        activity = q.value("activity").toString();
        date_time = q.value("date_time").toString();
        dTconv = QDateTime::fromString(date_time,"yyyy-MM-ddThh:mm:ss.zzz");
        dateTimeConv =dTconv.toString("dd.MM.yyyy hh:mm:ss AP");
        duration = q.value("exp_duration").toString();
        frame = q.value("frame").toString();
        startTime = q.value("start_time").toString();
        finTime = q.value("fin_time").toString();
        Operator = q.value("operator_name").toString();
        exp_tU = q.value("timeUnit_exp").toString();
        frame_tU = q.value("timeUnit_frame").toString();
        comments = q.value("comments").toString();
        fileDirectory = q.value("fileDirectory").toString();
        radioUnit = q.value("radioUnit").toInt();


    }

    QString filename = Storage.absolutePath().append("/CalibrationInfo.txt");
    QFile file;
    file.setFileName(filename);

    QTextStream out(&file);
    if(file.open(QIODevice::WriteOnly))
    {
        out << "ID: " << StudyID << "\n";
        out << "Device: " << deviceid << endl;
        out << "System: " << m_pReadInputInfoGamma->getSystemName() << endl;
        out << "Image Flip: " << m_pReadInputInfoGamma->getFlips().join(",") << endl;
        out << "Name: " << "Flood experiment" << endl;
        out << "Collimator: " << m_qsCollimator << endl;
        out << "Radionuclide: " << m_qsNuclideName << endl;
        if ( radioUnit == 0)
            out << "Radio unit: " << "MBq" << endl;
        else
            out << "Radio unit: " << "uCi" << endl;

        out << "Volume: " << volume << endl;
        out << "Activity:" << activity << endl;
        out << "Date/time : " << dateTimeConv << endl;
        out << "Operator: " << Operator << endl;
        out << "Experiment time unit: " << exp_tU << endl;
        out << "Frame time unit: " << frame_tU << endl;
        out << "Start Time: " << startTime << "\n";
        out << "Finish Time: " << finTime << "\n";
        out << "Experiment Duration: " << duration << " " << exp_tU << "\n";
        out << "Frame Duration: " << frame << " " << frame_tU <<"\n\n";
        out << "Comments: " << comments ;
    }
    file.close();
}

void gamma_eye::disableStartButton()
{
    ui->PB_startDAQ->setEnabled(false);
}

void gamma_eye::PB_startDAQ_clicked()
{
    if(!m_calibrationMode)
        setBackgroundImages();
    ui->cb_fusion->setEnabled(true);
    ui->cb_xray->setEnabled(true);
    if( duration_time != 0 && frame_time != 0 ) {
        ui->PB_startDAQ->setEnabled(false);
        timeFinishBtnPressed=false;
        bedMoved=false;
        FPGA->run();
    }
    else {
        QMessageBox* msgBox = new QMessageBox( this );
        msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        msgBox->setStandardButtons( QMessageBox::Ok );
        msgBox->setWindowTitle( tr("Error") );
        msgBox->setText( tr("Time setting were omitted!Please select time parameters and try again.") );
        msgBox->setModal(false); // if you want it non-modal
        msgBox->open( this, SIGNAL(openTimeSettings()));
    }
}

void gamma_eye::setBackgroundImages(){

    /**
        Set optical and xray image path
   **/
    m_opticalImagePath = Storage.path() + "/optical.png";
    m_xrayImagePath = Storage.path() + "/Xray.png";

    /**
        Read images to cv matrix
   **/
    m_opticalImageMat= cv::imread(m_opticalImagePath.toStdString(),CV_LOAD_IMAGE_GRAYSCALE);
    m_xrayImageMat=cv::imread(m_xrayImagePath.toStdString(),CV_LOAD_IMAGE_GRAYSCALE);
    /**
        Perform image flips
   **/
    QMap< QString, int > qmFlips;
    qmFlips.insert( "x", 0 );
    qmFlips.insert( "y", 1 );


    cv::rotate( m_opticalImageMat, m_opticalImageMat, cv::ROTATE_90_CLOCKWISE);
    cv::rotate( m_xrayImageMat,  m_xrayImageMat, cv::ROTATE_90_CLOCKWISE);
    if ( m_pReadInputInfoGamma->getFlips().size() > 0){
       foreach ( QString flip,  m_pReadInputInfoGamma->getFlips() ){
           if(flip!=""){
               qDebug() << "flip " << flip << endl;
               cv::flip( m_opticalImageMat, m_opticalImageMat, qmFlips[ flip ] );
               cv::flip( m_xrayImageMat,  m_xrayImageMat, qmFlips[ flip ] );
           }
       }
    }

    /**
        Convert images to CV_8U and resize for plotting
   **/

    cv::normalize(m_opticalImageMat, m_opticalImageMat, 0, 255, cv::NORM_MINMAX);
    cv::normalize(m_xrayImageMat, m_xrayImageMat, 0, 255, cv::NORM_MINMAX);


    cv::resize(m_opticalImageMat, m_opticalImageMat, cv::Size(580, 290), 0, 0, cv::INTER_CUBIC);
    cv::resize( m_xrayImageMat,  m_xrayImageMat, cv::Size(580, 290), 0, 0, cv::INTER_CUBIC);

    m_opticalImageMat.convertTo(m_opticalImageMat, CV_8U);
    m_xrayImageMat.convertTo(m_xrayImageMat, CV_8U);

}



void gamma_eye::InitiateThreads()
{
    QTimer *timeServer = new QTimer();
    timeServer->setInterval(0);
    udpServer *serverWorker = new udpServer(freeBytes,usedBytes,globalMutex,BUFFER);
    udpThread = new QThread();

    connect(udpThread,SIGNAL(started()),serverWorker,SLOT(setupSocket()));
    connect(udpThread,SIGNAL(started()),timeServer,SLOT(start()));
    connect(timeServer,SIGNAL(timeout()),serverWorker,SLOT(ProcessDatagram()));

    connect(this,SIGNAL(onPressedStop()),serverWorker,SLOT(stop()));
    connect(serverWorker,SIGNAL(finished()),timeServer,SLOT(stop()));
    connect(serverWorker,SIGNAL(finished()),udpThread,SLOT(quit()));

    connect(udpThread, SIGNAL(finished()), serverWorker, SLOT(deleteLater()));
    connect(udpThread, SIGNAL(finished()), timeServer, SLOT(deleteLater()));
    connect(udpThread, SIGNAL(finished()), udpThread, SLOT(deleteLater()));

    serverWorker->moveToThread(udpThread);
    timeServer->moveToThread(udpThread);

    udpThread->start(QThread::TimeCriticalPriority);

    DAQcounter *daqCount = new DAQcounter(duration_time,frame_time,fastDynamic);

    counterThread = new QThread();

    connect(counterThread,SIGNAL(started()),daqCount,SLOT(Initiate()));
    connect(daqCount,SIGNAL(DAQprogressBarValueChanged(int)),ui->daq_progress,SLOT(setValue(int)));
    connect(daqCount,SIGNAL(frameProgressBarValueChanged(int)),ui->frame_progress,SLOT(setValue(int)));
    connect(daqCount,SIGNAL(displayProgress()),ui->daq_progress,SLOT(update()));
    connect(daqCount,SIGNAL(displayProgress()),ui->frame_progress,SLOT(update()));
    connect(daqCount,SIGNAL(replotFrame()),this,SLOT(frameReplot()));
    connect(daqCount,SIGNAL(sendNewFrameTime(int)),this,SLOT(getNewFrameTime(int)));
    connect(daqCount,SIGNAL(stopEverthing()),this,SLOT(stopAquisition()));
    connect(this,SIGNAL(onPressedStop()),daqCount,SLOT(stopTimer()));
    connect(daqCount,SIGNAL(finished()),counterThread,SLOT(quit()));
    connect(counterThread, SIGNAL(finished()), daqCount, SLOT(deleteLater()));
    connect(counterThread, SIGNAL(finished()), counterThread, SLOT(deleteLater()));

    daqCount->moveToThread(counterThread);

    counterThread->start(QThread::TimeCriticalPriority);

    QTimer *timer = new QTimer();
    timer->setInterval(0);

    QTimer *progress = new QTimer();
    progress->setInterval(500);

    SPECTworker *worker = new SPECTworker(freeBytes,usedBytes,globalMutex,BUFFER, rawD, corrD, m_qsDeconvDir, m_qsNuclidedFolder, m_qsNuclideName, m_qdtInjectionDateTime,
                                          m_dActivity, m_pReadInputInfoGamma, m_calibrationMode,m_validationOn,m_newIsotope);
    SPECTthread = new QThread();

    connect(SPECTthread, SIGNAL( started( ) ), worker, SLOT( Initialise() ) );
    connect(SPECTthread, SIGNAL(started()),timer,SLOT(start()));
    connect(SPECTthread, SIGNAL(started()),progress,SLOT(start()));

    connect(timer,SIGNAL(timeout()),worker,SLOT(run()));
    connect(progress,SIGNAL(timeout()),worker,SLOT(imagingData()));
    connect(this,SIGNAL(sendFrameStop()),worker,SLOT(frameStop()));

    connect(worker,SIGNAL(sendImagingDataProgress(QVector<qreal>,QVector<qreal>,QVector<qreal>,QPolygonF,double,double,double,int)),this,SLOT(plotsUpdate(QVector<qreal>,QVector<qreal>,QVector<qreal>,QPolygonF,double,double,double,int)),Qt::QueuedConnection);

    connect(this,SIGNAL(sendContrast(double)),worker,SLOT(receiveContrast(double)));
    ///TEST
    connect(this,SIGNAL(updateSummed()), worker,SLOT( imagingData() ));
    ///TEST

    connect(this, SIGNAL(onPressedStop()), worker,SLOT( stopImaging() ) );
    connect(worker, SIGNAL(stopProcessing()), progress,SLOT( stop() ) );
    connect(worker, SIGNAL(stopProcessing()), timer,SLOT( stop() ) );

    connect(this,SIGNAL(stopProcessing()), worker,SLOT( imagingData() ));

    connect(worker, SIGNAL(stopProcessing() ), SPECTthread, SLOT( quit() ) );

    connect(SPECTthread, SIGNAL( finished() ), worker, SLOT( deleteLater() ) );
    connect(SPECTthread, SIGNAL( finished() ), timer, SLOT( deleteLater() ) );
    connect(SPECTthread, SIGNAL( finished() ), progress, SLOT( deleteLater() ) );
    connect(SPECTthread, SIGNAL( finished() ), SPECTthread, SLOT( deleteLater() ) );
    
    if(!m_calibrationMode)
        connect(worker,SIGNAL(imageFinished()),this,SLOT(saveDICOM()));

    worker->moveToThread(SPECTthread);
    timer->moveToThread(SPECTthread);
    progress->moveToThread(SPECTthread);

    SPECTthread->start(QThread::TimeCriticalPriority);
}

void gamma_eye::sliderValueChanged(int)
{
    int val = ui->horizontalSlider->value();
    val =  100 - val;

    contrastPercentage = static_cast<double>(val)/static_cast<double>(100);
    emit sendContrast( contrastPercentage );
}

void gamma_eye::sliderSummedValueChanged( int )
{
    int val = ui->hsContrastB->value();
    val =  100 - val;
    m_dContrastPercentageSummed = static_cast<double>(val)/static_cast<double>(100);

    m_dMaxCor = 0.0;
    QVector<qreal> temp;
    for ( int i = 0; i < m_qvrSummedImg.size(); i++){
        if ( m_qvrSummedImg[ i ] > m_dMaxCor )
            m_dMaxCor = m_qvrSummedImg[ i ];

        temp.append( m_qvrSummedImg[ i ] );
    }

    double con_percentage = m_dMaxCor*m_dContrastPercentageSummed;
    m_dMaxCor = m_dMaxCor - con_percentage;


    sumCorMatrix->setValueMatrix( temp, crystal_pixels_y*5 ); //Because we use the deconvouted
    sumCorMatrix->setInterval( Qt::ZAxis, QwtInterval( 0, m_dMaxCor) );
    sumCorMatrix->setResampleMode(sumCorMatrix->BilinearInterpolation);
    summedCorrectedPlot_spectrogram->setColorMap(cM);
    summedCorrectedPlot_spectrogram->setData( sumCorMatrix );
    temp.clear();
    summedCorrectedPlot->replot();

}

void gamma_eye::cb_ColorMap_currentIndexChanged(int val)
{
    if(val!=2)
        cM->BlackBased(val);
    else
        cM->BlueBased(val);

    correctedPlot_spectrogram->setColorMap(cM);
    summedCorrectedPlot_spectrogram->setColorMap(cM);
    rawPlot_spectrogram->setColorMap(cM);

    correctedPlot->replot();
    if(counter!=0)
        summedCorrectedPlot->replot();

    RawPlot->replot();
}

void gamma_eye::startAquisition()
{
    if(duration_time!=0 && frame_time!=0) {

        qDebug() << "Started running ...";

        InitiateThreads();
        counter++;

        QLocale locale(QLocale::English);
        QString date = locale.toString(QDateTime::currentDateTime(), "dd.MM.yyyy hh:mm:ss AP");

        ui->LE_startTime->setText( date ) ;
        ui->LE_startTime->adjustSize();

        if ( fastDynamic )
            ui->LE_currFrame->setText(QString::number(counter)+"/"+QString::number(44)+" Frame");
        else
            ui->LE_currFrame->setText(QString::number(counter)+"/"+QString::number(duration_time/frame_time)+" Frame");

        ui->PB_stopDAQ->setEnabled(true);
        ui->horizontalSlider->setEnabled(true);
        ui->hsContrastB->setEnabled(true);
        if (ui->cb_fusion->isChecked() || ui->cb_xray->isChecked())
            ui->opacitySlider->setEnabled(true);

    }
    else {
        QMessageBox* msgBox = new QMessageBox( this );
        msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        msgBox->setStandardButtons( QMessageBox::Ok );
        msgBox->setWindowTitle( tr("Error") );
        msgBox->setText( tr("Time setting were omitted!Please select time parameters and try again.") );
        msgBox->setModal(false); // if you want it non-modal
        msgBox->open( this, SIGNAL(openTimeSettings()));

    }
}

void gamma_eye::stopAquisition()
{
    emit updateSummed();
    QTime waitTime = QTime::currentTime().addMSecs(200);
    while( QTime::currentTime() < waitTime ){}

    emit onPressedStop();

    QLocale locale(QLocale::English);
    ui->LE_finishTime->setText(  locale.toString(QDateTime::currentDateTime(), "dd.MM.yyyy hh:mm:ss AP") );
    ui->LE_finishTime->adjustSize();


//    firstSummed=false;
    counter=0;
    ui->LE_currFrame->clear();
    frame_time=0;
    duration_time=0;


    ui->daq_progress->reset();
    ui->frame_progress->reset();

    freeBytes->release(64000);
    usedBytes->release(0);

    BUFFER->clear();

    ui->PB_stopDAQ->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
    ui->hsContrastB->setEnabled(false);
    ui->opacitySlider->setEnabled(false);

    if(m_calibrationMode && m_newIsotope.getType()==0)
        gammaEvaluation();

    emit saveStudyToDatabase( corrD, deviceOPerator, ui->LE_startTime->text(), ui->LE_finishTime->text());
    if(m_calibrationMode){
        calibrationInfoGenerator();
        exitCalib->show();
    }else{
        infoFileGenerator();
        nextStudy->show();
    }


    fastDynamic=false;
}

void gamma_eye::stopWithError()
{

    emit updateSummed();

    emit onPressedStop();
    QLocale locale(QLocale::English);
    QString date = locale.toString(QDateTime::currentDateTime(), "dd.MM.yyyy hh:mm:ss AP");
    ui->LE_finishTime->setText(  date );
    ui->LE_finishTime->adjustSize();

    counter=0;
    ui->LE_currFrame->clear();
    frame_time=0;
    duration_time=0;

    ui->daq_progress->reset();
    ui->frame_progress->reset();

    freeBytes->release(64000);
    usedBytes->release(0);

    BUFFER->clear();

    ui->PB_stopDAQ->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
    ui->hsContrastB->setEnabled(false);

    emit saveStudyToDatabase(corrD,deviceOPerator,ui->LE_startTime->text(),ui->LE_finishTime->text());
    if(m_calibrationMode){
        calibrationInfoGenerator();
    }else{
        infoFileGenerator();
    }
    fastDynamic=false;
}

void gamma_eye::plotsUpdate(QVector<qreal>rawVMatrix, QVector<qreal>corVMatrix, QVector<qreal>sumCorVMatrix, QPolygonF points, double maxRaw, double maxCor, double maxSumCor, int maxEn)
{
    //Store the sumMatrix
    m_qvrSummedImg.clear();
    m_qvrSummedImg.resize( sumCorVMatrix.size() );
    for ( int i = 0; i < sumCorVMatrix.size(); i++){
        m_qvrSummedImg[ i ] = sumCorVMatrix[ i ];
    }
    
    energyPlot->setAxisScale( QwtPlot::yLeft,0,maxEn,0); //Scale the y-axis
    energyPlot->plotLayout()->setAlignCanvasToScales(true);

    curve->setSamples(points);

    points.clear();

    rawMatrix->setValueMatrix(rawVMatrix,output_size_y);
    rawMatrix->setResampleMode(rawMatrix->BilinearInterpolation);
    rawMatrix->setInterval( Qt::ZAxis, QwtInterval( 0, maxRaw) );

    rawPlot_spectrogram->setColorMap(cM);
    rawPlot_spectrogram->setData(rawMatrix);
    rawVMatrix.clear();


    energyPlot->replot();
    RawPlot->replot();


            /////////Metatropi monadas MBq->μCi //
            //         1 MBq = 27 μCi           //
            //         1 μCi = 0.037ΜBq         //
            /////////////////////////////////////



    if(ui->cb_fusion->isChecked()){
        addOpticalBackground();
    }else if(ui->cb_xray->isChecked()){
        addXrayBackground();
    }



    corMatrix->setValueMatrix(corVMatrix,crystal_pixels_y);
    corMatrix->setResampleMode(corMatrix->BilinearInterpolation);
    corMatrix->setInterval( Qt::ZAxis, QwtInterval( 0, maxCor) );
    correctedPlot_spectrogram->setColorMap(cM);
    correctedPlot_spectrogram->setData(corMatrix);
    corVMatrix.clear();
    correctedPlot->replot();

    for ( int i = 0; i < sumCorVMatrix.size(); i++){
        if ( sumCorVMatrix[ i ] > m_dMaxCor )
            m_dMaxCor = sumCorVMatrix[ i ];
    }
    double con_percentage = m_dMaxCor*m_dContrastPercentageSummed;
    m_dMaxCor = m_dMaxCor - con_percentage;

    sumCorMatrix->setValueMatrix( sumCorVMatrix, crystal_pixels_y*5); //Because we use the deconvouted
    sumCorMatrix->setResampleMode(sumCorMatrix->BilinearInterpolation);
    sumCorMatrix->setInterval( Qt::ZAxis, QwtInterval( 0, m_dMaxCor) );
    summedCorrectedPlot_spectrogram->setColorMap(cM);
    summedCorrectedPlot_spectrogram->setData(sumCorMatrix);
    sumCorVMatrix.clear();
    summedCorrectedPlot->replot();

}

void gamma_eye::getNewFrameTime(int frameTime)
{
    frame_time = frameTime;
    ui->frame_progress->reset();
    ui->frame_progress->setMinimum(0);
    ui->frame_progress->setMaximum(frame_time);
    ui->LE_frameRate->setText(QString::number(frame_time)+" "+"sec");
}

void gamma_eye::frameReplot()
{
    emit sendFrameStop();
//    firstSummed=true;
    summedCorrectedPlot->replot();
    frameProgress=0;
    ui->frame_progress->reset();
    counter++;

    if(fastDynamic)
        ui->LE_currFrame->setText(QString::number(counter)+"/"+QString::number(44)+" Frame");
    else
        ui->LE_currFrame->setText(QString::number(counter)+"/"+QString::number(duration_time/frame_time)+" Frame");
}

void gamma_eye::delete_qwt_plots_and_globals()
{
    delete exitCalib;
    delete nextStudy;
    delete FPGA;
    delete bed;
    delete opDialog;

    if(!m_calibrationMode){
        delete study_details;
        delete time;
    }
    delete BUFFER;
    delete rawMatrix;
    delete corMatrix;
    delete sumCorMatrix;
    ui->corrected->removeWidget(correctedPlot);
    ui->summed->removeWidget(summedCorrectedPlot);
    ui->Energy_Spectrum->removeWidget(energyPlot);
    ui->Raw->removeWidget(RawPlot);
    correctedPlot->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    summedCorrectedPlot->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    energyPlot->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    RawPlot->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    delete correctedPlot;
    delete summedCorrectedPlot;
    delete energyPlot;
    delete RawPlot;
}


void gamma_eye::delete_qwt_validation_plots(){

    delete calibDetails;
    delete calibTime;
    /** Delete qwt validation plots
    */
    ui->correctedHead_layout->removeWidget(correctedHead);
    correctedHead->detachItems(QwtPlotItem::Rtti_PlotItem,false);

    delete correctedHead;
}



void gamma_eye::closeWin()
{
    reset();    
    aboutToExit=true;
    if(m_calibrationMode)
        bed->calibEject_bed();
    else
        bed->onlyMoveBedOut();
}

void gamma_eye::fpgaErrorMsg(int errorCode)
{
    if(errorCode==1) {
        QMessageBox* msgBox = new QMessageBox( this );
        msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        msgBox->setWindowTitle( tr("Error") );
        msgBox->setButtonText(1,"Restart");
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->setText( tr("Connection to hardware has been disturbed. Please check cable connections and press restart!") );
        msgBox->setModal(true); // if you want it non-modal
        // msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
        msgBox->open( this, SLOT(errorMsgAction(QAbstractButton*)));
    }
    else if(errorCode==2) {
        QMessageBox* msgBox = new QMessageBox( this );
        msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        msgBox->setWindowTitle( tr("Error") );
        msgBox->setButtonText(1,"Restart");
        // msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->setText( tr("Attention: Cable is locked! Please press Restart to reconfigure connection. If problem persists restart gamma-eye system and laptop.") );
        msgBox->setModal(true); // if you want it non-modal
        msgBox->open( this, SLOT(errorMsgAction(QAbstractButton*)));
    }
    else if(errorCode==3) {
        stopWithError();
        //reset();

        QMessageBox* msgBox = new QMessageBox( this );
        msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        msgBox->setWindowTitle( tr("Error") );
        msgBox->setButtonText(1,"Restart");
        // msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->setText( tr("Connection to hardware has been disturbed. Please check cable connections and press restart!") );
        msgBox->setModal(true); // if you want it non-modal
        msgBox->open( this, SLOT(errorMsgAction(QAbstractButton*)));
    }
    else if(errorCode==4) {
        QMessageBox* msgBox = new QMessageBox( this );
        msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        msgBox->setWindowTitle( tr("Error") );
        msgBox->setButtonText(1,"Restart");
        // msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->setText( tr("Connection to hardware is not found. Please check cable connections and press restart. If problem persists restart laptop and system or contact technical support. ") );
        msgBox->setModal(true); // if you want it non-modal
        msgBox->open( this, SLOT(errorMsgAction(QAbstractButton*)));
    }
    else if (errorCode==5) {
        QMessageBox* msgBox = new QMessageBox( this );
        msgBox->setAttribute( Qt::WA_DeleteOnClose );
        msgBox->setWindowTitle( tr("Error") );
        msgBox->setButtonText(1,"Exit");
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->setText( tr("Connection to a hardware component is lost irreversibly. The program will exit, please start the software again to continue. ") );
        msgBox->setModal(true); // if you want it non-modal
        msgBox->open( this, SLOT(CameraErrorMsgAction(QAbstractButton*)));
    }
}

void gamma_eye::errorMsgAction(QAbstractButton*)
{
    RestartApplication();
}

void gamma_eye::CameraErrorMsgAction(QAbstractButton*)
{
    std::exit(EXIT_FAILURE);
}

void gamma_eye::reset()
{
    QVector<qreal> rawMatrix;
    rawMatrix.fill(0);
    QVector<qreal> corMatrix;
    corMatrix.fill(0);
    QVector<qreal> sumCorzeroVMatrix;
    sumCorzeroVMatrix.fill(0);
    QPolygonF poly;
    poly.fill(QPoint(0,0));


    plotsUpdate(rawMatrix,corMatrix,sumCorzeroVMatrix,poly,0.0,0.0,0.0,0);



    ui->LE_frameRate->clear();
    ui->LE_duration->clear();
    ui->LE_startTime->clear();
    ui->LE_finishTime->clear();
    ui->LE_counts->clear();
    ui->LE_currFrame->clear();
    //ui.LE_sensitivity->clear();
    ui->daq_progress->reset();
    ui->frame_progress->reset();

    ui->TL_animalID->clear();
    ui->TL_project->clear();
    ui->TL_studyID->clear();
    ui->TL_studyName->clear();

    correctedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
    correctedPlot->replot();
    summedCorrectedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
    summedCorrectedPlot->replot();

    ui->opacitySlider->setDisabled(true);
    m_xrayImageMat.release();
    m_opticalImageMat.release();

//    firstReplot=true;
}

void gamma_eye::on_actionGo_back_to_main_menu_triggered()
{
    //  this->close();
    // emit exitToMainWindow();

    emit terminate_fpga();
    bed->onlyMoveBedIn();
    bed->exit();
}

void gamma_eye::RestartApplication()
{
    reset();
    emit exit();

    bed->onlyMoveBedIn();
    bed->exit();
    this->close();
    emit exitToMainWindow();
}

void gamma_eye::on_actionInsert_Bed_triggered(){ bed->onlyMoveBedIn(); }

void gamma_eye::on_actionEject_Bed_triggered(){ bed->onlyMoveBedOut(); }

void gamma_eye::on_actionCalibrate_Bed_Position_triggered()
{
    bed->exit();
    bed->configure_ttyACM0();
    bed->calibrate();
}

void gamma_eye::on_PB_eject_clicked(){ bed->onlyMoveBedOut();}

void gamma_eye::on_cb_fusion(bool checked)
{
    if ( checked ) {
        if (m_opticalImageMat.empty()){
            correctedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
            summedCorrectedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
            qDebug() << "optical empty !!!!!! "<< endl;
         }else{
            ui->opacitySlider->setEnabled(true);
            addOpticalBackground();
            cv::imwrite("test.png",m_opticalImageMat);
         }
    }
    else if ( !checked ) {
        removeBackground();
        correctedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
        summedCorrectedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
    }
}

void gamma_eye::on_cb_xray(bool checked)
{
    if ( checked ) {
        if (m_xrayImageMat.empty()){
            correctedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
            summedCorrectedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
         }else{
            ui->opacitySlider->setEnabled(true);
            addXrayBackground();
         }
    }
    else if ( !checked ) {
        removeBackground();
        correctedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
        summedCorrectedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
    }
}

void gamma_eye::addOpticalBackground(){

    QPalette palette;
    QImage opticalQImg(static_cast<const uchar *>(m_opticalImageMat.data), m_opticalImageMat.cols, m_opticalImageMat.rows, QImage::Format_Grayscale8);
    palette.setBrush(correctedPlot->canvas()->backgroundRole(), QBrush(opticalQImg));

    correctedPlot->setCanvasBackground(QBrush(opticalQImg));
    correctedPlot->canvas()->setPalette(palette);

    summedCorrectedPlot->setCanvasBackground(QBrush(opticalQImg));
    summedCorrectedPlot->canvas()->setPalette(palette);

    correctedPlot_spectrogram->setAlpha(ui->opacitySlider->value());
    summedCorrectedPlot_spectrogram->setAlpha(ui->opacitySlider->value());
}

void gamma_eye::removeBackground(){

    correctedPlot_spectrogram->setAlpha(255);
    summedCorrectedPlot_spectrogram->setAlpha(255);
    ui->opacitySlider->setDisabled(true);
}

void gamma_eye::addXrayBackground(){
    QPalette palette;
    QImage xrayQImg(static_cast<const uchar *>(m_xrayImageMat.data), m_xrayImageMat.cols, m_xrayImageMat.rows, QImage::Format_Grayscale8);
    palette.setBrush(correctedPlot->canvas()->backgroundRole(), QBrush(xrayQImg));

    correctedPlot->setCanvasBackground(QBrush(xrayQImg));
    correctedPlot->canvas()->setPalette(palette);

    summedCorrectedPlot->setCanvasBackground(QBrush(xrayQImg));
    summedCorrectedPlot->canvas()->setPalette(palette);

    correctedPlot_spectrogram->setAlpha(ui->opacitySlider->value());
    summedCorrectedPlot_spectrogram->setAlpha(ui->opacitySlider->value());
}

void gamma_eye::opacityValueChanged(int){
    int val = ui->opacitySlider->value();
    correctedPlot_spectrogram->setAlpha(val);
    summedCorrectedPlot_spectrogram->setAlpha(val);
}

void gamma_eye::setCheckstateOptical(){
    if( m_isOpticalChecked ){
       ui->cb_fusion->setCheckable(false);
       ui->cb_fusion->setChecked(false);
       m_isOpticalChecked = false;
       on_cb_fusion(false);
    }
    else {
       ui->cb_fusion->setCheckable(true);
       ui->cb_fusion->setChecked(true);
       m_isOpticalChecked = true;
       on_cb_fusion(true);

       ui->cb_xray->setChecked(false);
       m_isXrayChecked = false;
    }
}

void gamma_eye::setCheckstateXray(){
    if( m_isXrayChecked ){
      ui->cb_xray->setCheckable(false);
      ui->cb_xray->setChecked(false);
      m_isXrayChecked = false;
      on_cb_xray(false);
    }
    else {
      ui->cb_xray->setCheckable(true);
      ui->cb_xray->setChecked(true);
      m_isXrayChecked = true;
      on_cb_xray(true);

      ui->cb_fusion->setChecked(false);
      m_isOpticalChecked = false;
    }
}

void gamma_eye::saveDICOM()
{
    QSqlQuery q;
    QString marking, animal_name, date, startTime, gender, comments, nuclideUnit;
    QString injected_activity, weight;
    double pixel_size = 1.7;
    QString pix = QString::number(pixel_size);
    bioemtec::dicomEncoder enc;
    QString dicomDir= post.path();
    dicomDir.replace("Report_Images","DICOM");
    QProcess * createDicom;
    QString test="dcmodify -m \"(0028,0030)=1.7\\1.7\" -nb " ;
    std::string text=test.toStdString();
    QString exeCommands = QString::fromUtf8(text.c_str());

    QString load = "SELECT Study.date, Study.name, Study.animal_name, Study.breed, Study.species, \
                      Study.age, Study.weight, Study.gender, Study.r_pharma ,Study.volume ,Study.activity, \
                      Study.injection_date, InjectionPath.name as Path, Study.exp_duration, \
                      Study.frame, Study.start_time, \
                      Study.fin_time , device.name as Device, modality.mod_name, Study.timeUnit_exp, Study.timeUnit_frame,\
                      Study.operator_name, radionuclide.nuclide_name, Study.project, \
                      Study.injected_activity, Study.comments, Study.marking, Study.fileDirectory FROM Study INNER JOIN InjectionPath ON \
                      Study.path_id = InjectionPath.path_id INNER JOIN device ON Study.deviceid = device.deviceid \
                      INNER JOIN modality ON Study.id_modality = modality.id_modality INNER JOIN radionuclide ON \
                      Study.nuclide_id = radionuclide.nuclide_id WHERE Study.study_id= " + StudyID;


    q.exec(load);
    if( q.next() ) {
        marking=q.value("marking").toString();
        animal_name = q.value("animal_name").toString();
        date = q.value("date").toString();
        startTime = q.value("start_time").toString();
        if( q.value("gender").toInt()==0)
            gender="F";
        else
            gender="M";

        comments = q.value("comments").toString();
        if ( q.value("radioUnit").toInt() == 0 )
           nuclideUnit = "MBq";
        else
           nuclideUnit = "uCi";
        injected_activity = q.value("injected_activity").toString()+ " " + nuclideUnit;
        weight = q.value("weight").toString();
    }
    weight= weight +" gr";
    std::vector<std::string> stringList;
    stringList.push_back(marking.toStdString());
    stringList.push_back(animal_name.toStdString());
    stringList.push_back(date.toStdString());
    QStringList spl = startTime.split(" ");
    QString h_only;
    QString hour;
    for ( int i =0;i < spl.count(); i++ ) {
        if( i == 1 )
            h_only = spl.at(1);
    }
    stringList.push_back( h_only.toStdString() );
    stringList.push_back("");
    stringList.push_back(gender.toStdString());
    stringList.push_back(comments.toStdString());
    stringList.push_back(injected_activity.toStdString());
    stringList.push_back(weight.toStdString());
    stringList.push_back("ST");
    stringList.push_back(pix.toStdString());

    QStringList txtFilter;
    txtFilter << "*.txt";
    QStringList txtImages = deconvoluted.entryList(txtFilter,QDir::Files|QDir::NoSymLinks);
    QString txtFilePath = deconvoluted.path();
    txtImages.sort();
    /*
    int j=0;
    for (int i=0; i < txtImages.size() -1; i++){
        j=i+1;
        txtImages.swap(i,j);
    }
    */

    int iFrame =0;
    foreach(QString txtFile, txtImages){
        QString iFile =(txtFilePath+"/"+txtFile);
        QFile File(iFile);
        QByteArray byteArray;
        QTextStream textStream(&byteArray,QIODevice::ReadOnly);
        if( File.exists() && File.open( QIODevice::ReadOnly ) ){
            byteArray= File.readAll();
            File.close();
        }
        else{
#ifdef QT_DEBUG
            qDebug("Failed to open file for reading.");
            break;
#endif
        }
        int row_num=0,col_num=0,cnt=0;
        QString line;
        QStringList fields;
        QStringList list_item;
        QLocale c (QLocale::C);
        bool ok;
        while( !textStream.atEnd() ){
            line = textStream.readLine();
            fields = line.split(" ");

            col_num = fields.size();
            for(int i =0; i< col_num;i++)
                list_item.append(fields.at(i));

            row_num++;
        }

        QVector<qreal> iMatrix;
        for(int i=0;i<row_num;i++){
            for(int j=0;j<col_num;j++){
                iMatrix.append( c.toFloat(list_item.at(cnt),&ok));
                cnt++;
            }
        }


        uint16_t inputImage[iMatrix.size()];
        double max = *std::max_element(iMatrix.constBegin(), iMatrix.constEnd());
        if (max > 65535.0){
            for ( int m = 0; m < iMatrix.size(); m++)
                inputImage[ m ] = static_cast<uint16_t>(iMatrix[m]*(65535.0/max));
        }
        else{
            for ( int m = 0; m < iMatrix.size(); m++)
                inputImage[ m ] = static_cast<uint16_t>(iMatrix[m]);
        }

        iFrame+=1;

        QString testDir = dicomDir+"/frame"+QString::number(iFrame)+".dcm";
        std::vector<float> dimensions;
        dimensions.push_back(row_num);
        dimensions.push_back(col_num);
        enc.encoder(testDir.toStdString(), stringList, dimensions, inputImage );
        createDicom->execute( exeCommands + " " + testDir);


        iMatrix.clear();
        byteArray.clear();

    }




    QString optDir = postD.remove("/POST_PROCESSING");
    QString optOut = dicomDir+"/optical.dcm";
    QString optXOut = dicomDir+"/xray.dcm";
    optDir.append("/optical.png");

    std::vector<std::string> optList;
    optList.push_back("Dummy1");
    optList.push_back("Dummy2");
    optList.push_back("Dummy3");
    optList.push_back("Dummy4");
    optList.push_back("");
    optList.push_back("Dummy5");
    optList.push_back("Dummy6");
    optList.push_back("Dummy7");
    optList.push_back("Dummy8");
    optList.push_back("Dummy9");
    optList.push_back(pix.toStdString());

    if ( !QFile::exists( optDir ) ){
            QMessageBox msgBox;
            msgBox.setWindowTitle("VISUAL-eyes");
            msgBox.setText("Could not find optical image in its default position: " + optDir + "\nPress OK to select the file with the optical image to be saved in DICOM format.");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            msgBox.addButton(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);

            if(msgBox.exec() == QMessageBox::Ok)
                optDir = QFileDialog::getOpenFileName(this, tr("Select Optical Image "), optDir.remove("/optical.png"), tr("Portable Network Graphics file (*.png)"));
            else
                return;
     }

    cv::Mat opticalImg,xrayImg;
    optDir.remove("optical.png");
    optDir.append("Xray.png");
    std::string xrayFile = optDir.toStdString();
    optDir.remove("Xray.png");
    optDir.append("optical.png");
    std::string opFile = optDir.toStdString();
    opticalImg = cv::imread( opFile,CV_LOAD_IMAGE_GRAYSCALE);
    xrayImg = cv::imread( xrayFile,CV_LOAD_IMAGE_GRAYSCALE);

    QMap< QString, int > qmFlips;
    qmFlips.insert( "x", 0 );
    qmFlips.insert( "y", 1 );

    cv::rotate( opticalImg, opticalImg, cv::ROTATE_90_CLOCKWISE);
    cv::rotate( xrayImg, xrayImg, cv::ROTATE_90_CLOCKWISE);
    if ( m_pReadInputInfoGamma->getFlips().size() > 0){
       foreach ( QString flip,  m_pReadInputInfoGamma->getFlips() ){
           if(flip!=""){
               cv::flip( opticalImg, opticalImg, qmFlips[ flip ] );
               cv::flip( xrayImg, xrayImg, qmFlips[ flip ] );
           }
       }
    }
     cv::normalize(opticalImg, opticalImg, 0, 255, cv::NORM_MINMAX);
     cv::normalize(xrayImg, xrayImg, 0, 255, cv::NORM_MINMAX);
     opticalImg.convertTo(opticalImg, CV_16UC1);
     xrayImg.convertTo(xrayImg, CV_16UC1);
     cv::resize(opticalImg, opticalImg, cv::Size(5*crystal_pixels_y, 5*crystal_pixels_x), 0, 0, cv::INTER_CUBIC);
     cv::resize(xrayImg, xrayImg, cv::Size(5*crystal_pixels_y, 5*crystal_pixels_x), 0, 0, cv::INTER_CUBIC);
     size_t len = opticalImg.total()*opticalImg.elemSize(); // in bytes
     size_t lenX = xrayImg.total()*xrayImg.elemSize();
     uint16_t *outOImg = new uint16_t[ len ];
     memcpy( outOImg, opticalImg.ptr< uint16_t>(), len );
     uint16_t *outXImg = new uint16_t[ lenX ];
     memcpy( outXImg, xrayImg.ptr< uint16_t>(), lenX );
     std::vector<float> dimensions;
     dimensions.push_back(5*crystal_pixels_x);
     dimensions.push_back(5*crystal_pixels_y);
     enc.encoder( optOut.toStdString(), optList, dimensions, outOImg);
     enc.encoder( optXOut.toStdString(), optList, dimensions, outXImg);
     createDicom->execute( exeCommands + " " + optOut + " " + optXOut);

}


void gamma_eye::gammaEvaluation() {

    // input txt file in the following format: ID1,En1,ID2,En2
    QString filenameIn = Storage.absolutePath()+"/RawValidationData.txt";
    std::ifstream InFile;
    InFile.open(filenameIn.toStdString());

    qDebug() << "Validation file path "<< filenameIn << endl;

    QTime waitTime1;
    bool validStatus=false;
    QPolygonF enHead;

    QProgressDialog validationProgress("System validation ...",nullptr,0,6,this);
    validationProgress.setMinimumDuration(0);

    waitTime1 = QTime::currentTime().addMSecs(500);
    while( QTime::currentTime() < waitTime1 ){
      QApplication::processEvents();
    }
    validationProgress.setValue(0);

    //Variables Declaration

    const int NumberMaximumID = 1685;
    long int countEvents=0;
    int ID1=0; ///////////####### initialize IDs
    float En1;
    float lower_limit=15;
    float window= 0.10;
    float FWHM_Head1_h1_best=30;



    float photopeak_Head1_h1[NumberMaximumID];
    float sigma_Head1_h1[NumberMaximumID];
    float FWHM_Head1_h1[NumberMaximumID];
    float entries_Head1_h1[NumberMaximumID];

    //Histograms Declaration

    TH1F** h1 = new TH1F*[NumberMaximumID];
    for (int i=0; i < NumberMaximumID; i++){
        h1[i] = new TH1F(TString::Format("h1_%d", i), "Head 1", 200, 0.,500);
        FWHM_Head1_h1[i]=0;
    }
    TH1F *Head_Av_En_Res = new TH1F("histogram","Average Energy Res Head",30, 10, 50);


    int maxEnergy=2000;
    int corHist[maxEnergy];
    int i=0;
    int maxCorH1=0;
    while(i<maxEnergy){
        corHist[i]=0;
        i++;
    }

    waitTime1 = QTime::currentTime().addMSecs(500);
    while( QTime::currentTime() < waitTime1 ){
      QApplication::processEvents();
    }
    validationProgress.setValue(1);



    double maxCorEnergyH1=0.0;
    while(InFile) //read txt file and store energy in histograms
    {
    if (InFile >> ID1 >> En1) ///////###### add an if so not to crash if txt is empty (probably needs revision at some point)
         {
            countEvents++;
            h1[ID1]->Fill(En1);
            corHist[int(En1)]++;

            if (En1>maxCorEnergyH1)
                maxCorEnergyH1=En1;
        }
    }
    std::cout << "Total Events recorded: " << countEvents <<std::endl;


    validationProgress.setValue(2);

    int det_elements_processed_head=1;

    for (int i=0; i < NumberMaximumID; i++){
            h1[i] ->Smooth();
            entries_Head1_h1[i]= h1[i]->GetEntries();
            if (entries_Head1_h1[i]>2000){

                 photopeak_Head1_h1[i] = searchPhotopeak_T1(h1[i],float(m_newIsotope.getEnergyPeak()));
                 double peak_range_low= m_newIsotope.getEnergyPeak() -  m_newIsotope.getEnergyPeak()*0.2;
                 double peak_range_up= m_newIsotope.getEnergyPeak() +  m_newIsotope.getEnergyPeak()*0.2;

                if (photopeak_Head1_h1[i] > peak_range_low && photopeak_Head1_h1[i] <  peak_range_up)
                {
                        h1[i]->Fit("gaus", "Q", "Q",photopeak_Head1_h1[i]- window*photopeak_Head1_h1[i], photopeak_Head1_h1[i] +window*photopeak_Head1_h1[i]);
                        sigma_Head1_h1[i]=h1[i]->GetFunction("gaus")->GetParameter(2);
                        FWHM_Head1_h1[i]=100*2.35*sigma_Head1_h1[i]/photopeak_Head1_h1[i];
                        if (FWHM_Head1_h1[i]>50 &&FWHM_Head1_h1[i]<lower_limit){
                            FWHM_Head1_h1[i]=0;
                        }
                        Head_Av_En_Res->Fill(FWHM_Head1_h1[i]);
                        det_elements_processed_head++;

                       }
            }
   }





    waitTime1 = QTime::currentTime().addMSecs(100);
    while( QTime::currentTime() < waitTime1 ){
      QApplication::processEvents();
    }
    validationProgress.setValue(3);


    double resHeadA=0.0;



    sort(FWHM_Head1_h1, FWHM_Head1_h1+1685);
    int l=0;
    for (int k=0; k < NumberMaximumID; k++) {
        if (l<20 && FWHM_Head1_h1[k]>lower_limit) {
                FWHM_Head1_h1_best+=FWHM_Head1_h1[k];
                l++;
        }
     }

    FWHM_Head1_h1_best=FWHM_Head1_h1_best/l;




    if (det_elements_processed_head>200 && Head_Av_En_Res->GetMean()>14 && Head_Av_En_Res->GetMean()<37){
            validStatus=true;
    }else{
            validStatus=false;
    }

    waitTime1 = QTime::currentTime().addMSecs(100);
    while( QTime::currentTime() < waitTime1 ){
      QApplication::processEvents();
    }
    validationProgress.setValue(6);

    i=0;
    while (i<maxEnergy) {

        if (corHist[i] > maxCorH1)
            maxCorH1=corHist[i];

        enHead << QPointF(i,corHist[i]);
        i++;

    }

    ui->lb_detElemHead->setText(QString::number(det_elements_processed_head)+" / 1684");
    ui->lb_resolution->setText("Energy resolution at " +QString::number(m_newIsotope.getEnergyPeak())+" keV: ");
    ui->lb_cfov->setText(QString::number(FWHM_Head1_h1_best)+" %");



    correctedHead->setAxisScale( QwtPlot::yLeft,0,maxCorH1,0); //Scale the y-axis
    correctedHead->plotLayout()->setAlignCanvasToScales(true);
    correctedCurve->setSamples(enHead);
    correctedHead->replot();


    if(validStatus){
        ui->lb_status->setText("Success");
        QImage successImg = QImage(":/icons/success.png");
        QPixmap pixmapSuccess = QPixmap::fromImage(  successImg );
        ui->statusIcon->setPixmap(pixmapSuccess.scaled(85,85,Qt::KeepAspectRatio));
    }else{
        ui->lb_status->setText("Failed");
        QImage failImg = QImage(":/icons/fail.png");
        QPixmap pixmapFail = QPixmap::fromImage(  failImg );
        ui->statusIcon->setPixmap(pixmapFail.scaled(85,85,Qt::KeepAspectRatio));
    }
    ui->lb_status->setAlignment(Qt::AlignCenter);
    QFont font = ui->lb_status->font();
    font.setWeight(60);
    QMessageBox msgBox;
    msgBox.setText("System validation completed!");
    msgBox.exec();

    pdf_report(resHeadA);

    /*for(int i=0; i<NumberMaximumID;i++){
        delete[] h1[i];
        delete[] h2[i];
    }
    delete [] h1;
    delete [] h2;*/
    return;
}


float gamma_eye::searchPhotopeak_T1(TH1F* histo, float peak) { //new

    TSpectrum* s2 = new TSpectrum(3, 3);
    int nfounds = s2->Search(histo, 6, "nobackground", 0.05);
    double* xPositionsPeaks = s2->GetPositionX();
    float peak_out=0;


        for (int i = 0; i < nfounds; i++)
        {

        cout <<i<<" "<< nfounds<<" "<< xPositionsPeaks[i] << endl;

            if ( xPositionsPeaks[i] < peak+0.10*peak && xPositionsPeaks[i] > peak-0.10*peak )
                {
                    peak_out=xPositionsPeaks[i];
                }


        }

        return peak_out;
}


void gamma_eye::pdf_report(double resA)
{


    ///// open file dialog for the user to name the expoted report
    QString report_filepath = Storage.absolutePath()+"/ValidationReport.pdf"; /// store directory is the users documents every time

    QPdfWriter writer(report_filepath);
    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setPageMargins(QMargins(30, 30, 30, 30));

    QPainter painter(&writer);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 18));
    QPixmap logo;
    logo.load(":icons/BIOEMTECH_GREY.png");
    logo.scaled(2700,726,Qt::KeepAspectRatio);

    painter.drawPixmap(QRect(0,0,2700,726), logo);

    QString title = "System Validation Report";

    int begin_text_h=700;
    painter.drawText(QRect(0,begin_text_h,8917,350), Qt::AlignCenter, title);


    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 10));
    painter.drawText(QRect(0,begin_text_h+600,8917,200), Qt::AlignLeft, "Validation Info");

    painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(0,begin_text_h+850,8917,begin_text_h+860);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 10));

    QString date = "Date: ";
    date += QDateTime::currentDateTime().toString("MMM-ddd-yyyy hh:mm:ss") +"\n";
    painter.drawText(QRect(0,begin_text_h+950,3000,200), Qt::AlignLeft, date);


    QString study_id = "Study ID: ";
    study_id += ui->TL_studyID->text()+"\n";
    painter.drawText(QRect(0,begin_text_h+1250,3000,200), Qt::AlignLeft, study_id);


    QString study_name = "Study name: ";
    study_name += ui->TL_studyName->text() + "\n";
    painter.drawText(QRect(0,begin_text_h+1550,3000,200), Qt::AlignLeft, study_name);

    QString collimator = "Collimator: ";
    collimator += m_qsCollimator +"\n";
    painter.drawText(QRect(3200,begin_text_h+950,3000,200), Qt::AlignLeft, collimator);

    QString radionuclide = "Radionuclide: ";
    radionuclide += ui->LE_radioNuclide->text() +"\n";
    painter.drawText(QRect(3200,begin_text_h+1250,3000,200), Qt::AlignLeft, radionuclide);

    QString activity = "Activity: ";
    activity +=ui->LE_injectActivity->text() +"\n";
    painter.drawText(QRect(3200,begin_text_h+1550,3000,200), Qt::AlignLeft, activity);

    QString duration = "Experiment duration: ";
    duration += ui->LE_duration->text()+"\n";
    painter.drawText(QRect(6400,begin_text_h+950,3000,200), Qt::AlignLeft, duration);


    QString system = "System: ";
    system += m_pReadInputInfoGamma->getSystemName()+"\n";
    painter.drawText(QRect(6400,begin_text_h+1250,3000,200), Qt::AlignLeft, system);


    painter.drawText(QRect(0,begin_text_h+2000,8917,200), Qt::AlignLeft, "Head ");
    painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(0,begin_text_h+2250,8917,begin_text_h+2260);



    QPixmap corHead1_img=correctedHead->grab();
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 6));
    painter.drawText(QRect(0,begin_text_h+2450,1500,200),Qt::AlignLeft,"Corrected energy(counts/KeV)");

    painter.drawPixmap(QRect(0,begin_text_h+2600,2800,2800),corHead1_img);
    painter.setFont(QFont("Times", 8));
    QString elementHeadA="Detector elements processed: "+ui->lb_detElemHead->text();
    painter.drawText(QRect(3000,begin_text_h+2600,2500,2500),elementHeadA);
    QString resHeadA="Energy resolution: "+QString::number(resA)+" %";
    painter.drawText(QRect(3000,begin_text_h+3000,2500,2500),resHeadA);




    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 10));
    painter.drawText(QRect(0,begin_text_h+5500,8917,200), Qt::AlignLeft, "General");
    painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(0,begin_text_h+5750,8917,begin_text_h+5760);

    QString resolution=ui->lb_resolution->text() +ui->lb_cfov->text();
    painter.setFont(QFont("Times", 8));
    painter.drawText(QRect(0,begin_text_h+5900,8917,2000),resolution);


    painter.setFont(QFont("Times", 10));
    painter.drawText(QRect(0,begin_text_h+6200,8917,200), Qt::AlignLeft, "Validation status");
    painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(0,begin_text_h+6450,8917,begin_text_h+6460);


    QString status=ui->lb_status->text();
    painter.setFont(QFont("Times", 8));
    painter.drawText(QRect(0,begin_text_h+6600,2000,200),status);
    QPixmap pixmap_status= *ui->statusIcon->pixmap();
    pixmap_status.scaled(500,500);
    painter.drawPixmap(QRect(0,begin_text_h+6800,500,500),pixmap_status);
    painter.end();


}
