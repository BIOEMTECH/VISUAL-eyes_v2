#include "headers/betaEye.h"
#include "ui_betaEye.h"
#include "opencv2/opencv.hpp"

betaEye::betaEye(ReadInputInfo* inputInfo, bool calibrationMode ,QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::betaEye),
    m_pReadInputInfoBeta(inputInfo),
    m_calibrationMode(calibrationMode),
    m_bCastorSummedFinished(false)
{
    ui->setupUi(this);

    contrastPercentageSummed = 0.0;
    m_dMaxCor = 0.0;

    layout()->setMenuBar(ui->menubar);
    ui->menubar->show();

    setWindowFlags(Qt::WindowOverridesSystemGestures);

    qRegisterMetaType<QVector<qreal>>("QVector<qreal>");
    qRegisterMetaType<QPolygonF>("QPolygonF");

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
    initilization();
}


betaEye::~betaEye(){
    delete_qwt_plots_and_globals();
    if(ui)
        delete ui;
}


void betaEye::initilization(){

    m_dActivity = 0.0;
    nextStudy = new continueStudy(this);
    exitCalib = new calibrationExit(this);
    contrastPercentage = 0.0;

    duration_time=0;
    frame_time=0;
    counter=0;
    frameProgress=0;
    fastDynamic=false;
    noTimeSettings =false;
    frameCount= 0;

    firstSummed2=false;
    aboutToExit=false;
    arduinoConfigured=false;
    timeFinishBtnPressed=false;
    bedMoved=false;
    m_bedCalibrated =false;

    BUFFER=nullptr;
    m_castorFrame=nullptr;

    PETsys = new PETsysConnection();

    connect(ui->opacitySlider, SIGNAL(valueChanged(int)), this, SLOT( opacityValueChanged(int)));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this, SLOT(sliderValueChanged(int))); //connect the change of the slider with the value percentage we want to contrast the image. The change in the slider is incemental by 10
    connect(ui->hsContrastB ,SIGNAL(valueChanged(int)),this, SLOT(sliderSummedValueChanged(int))); //connect the change of the slider with the value percentage we want to contrast the summed image. The change in the slider is incemental by 10
    connect(ui->cb_colormap,SIGNAL(currentIndexChanged(int)),this,SLOT(cb_ColorMap_currentIndexChanged(int))); //select the colormap from the combobox and apply it in the image.

    QTime waitTime;
    waitTime = QTime::currentTime().addSecs(10);

    QMessageBox init_msg;
    init_msg.setIcon(QMessageBox::Information);
    init_msg.setText("Initializing hardware. \nPlease wait...");
    init_msg.setStandardButtons(QMessageBox::NoButton);
    init_msg.show();
    while( QTime::currentTime() <= waitTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents);


    PETsys->openDaq();
    if(PETsys->getFPGA_status()==false){
        waitTime = QTime::currentTime().addSecs(30);
        while( QTime::currentTime() <= waitTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents);

        PETsys->openDaq();
    }


    bed = new arduino(m_pReadInputInfoBeta, this, 2); // arduino class instance with initialization value that determines the device. 1 is SPECT , 2 is PET
    sensor_temperature= new temperatureControl(m_pReadInputInfoBeta);

    // Hardware connection check. We cannot proceed if the hardware is not connected, it will stay in a loop asking to connect the harware until it is connected.
    if( bed->check_connection() == false || PETsys->getFPGA_status()==false) { // check if the arduino device appear in the usb connected devices.
        while( bed->check_connection() == false || PETsys->getFPGA_status()==false) {  // if not, show a message to the user that prompts him to connect the hardware
            QMessageBox msg;
            msg.setIcon(QMessageBox::Critical);
            msg.setWindowFlags(Qt::WindowStaysOnTopHint);
            msg.setText("Error: The hardware is not connected, please check cable connections and press Retry.");
            msg.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
            qint32 ch;
            QTime dieTime;

            ch = msg.exec();

            switch(ch) {
            case QMessageBox::Retry: //if we connect the device and press retry waits some ms and goes back to the loop to check again.
            {
                init_msg.close();
                msg.hide();
                dieTime = QTime::currentTime().addMSecs(200);
                QMessageBox msg;
                msg.setIcon(QMessageBox::Information);
                msg.setWindowFlags(Qt::WindowStaysOnTopHint);
                msg.setText("Please check cable connections and press ok.If problem persists restart beta-eye system.");
                msg.setStandardButtons(QMessageBox::Ok);

                while( QTime::currentTime() < dieTime ){}
                msg.exec();
            }
                break;
            case QMessageBox::Cancel: //if we press cancel we exit the programm completely
            {
                std::exit(EXIT_FAILURE);
            }
            default:
                break;
            }
        }
    }
    init_msg.close();
    connect(bed,SIGNAL(server_IsOpen()),this,SLOT(arduino_State()));
    connect(PETsys,SIGNAL(sendError(int)),this,SLOT(fpgaErrorMsg(int))); //grab errors from the fpga process
    if(m_calibrationMode){
        calibrationCycle();
        qDebug() << "calibration" << endl;
    }else{
        qDebug() << "study" << endl;
        studyCycle();
    }
}


void betaEye::fpgaErrorMsg(int errorCode)
{
    if (errorCode==1) {
        QMessageBox* msgBox = new QMessageBox( this );
        msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        msgBox->setWindowTitle( tr("Error") );
        msgBox->setButtonText(1,"Exit");
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->setText( tr("Failed to receive reply from FPGA. Please check cable connections and press restart!") );
        msgBox->setModal(true); // if you want it non-modal
        msgBox->open( this, SLOT(CameraErrorMsgAction(QAbstractButton*)));
    }
}

void betaEye::calibrationCycle(){
    opDialog = new operatorDialog(this);
    calibTime = new calibrationTime(this);
    calibDetails = new calibrationDialog(m_pReadInputInfoBeta,"betaEye", this);

    configureArduino();

    connect(this,SIGNAL(sendStudyDir(QString)),bed,SLOT(getStudyDir(QString))); // send project directory to arduino so the thread we start will know where to save the optical image later on.
    connect(this,SIGNAL(bedInsertSignal(bool)),bed,SLOT(bedIn(bool)));
    connect(bed,SIGNAL(letBedIn()),this,SLOT(insertCapture())); // arduino informs that the mouse bed is out so we can insert the mouse bed and start the capture procedure
    connect(bed,SIGNAL( make_Start_btn_Avail() ),this,SLOT(getCameraFeedback())); // get feedback from the camera if the image reconstruction was successful or not.
    connect(bed,SIGNAL(insertBedWithoutVid()),this,SLOT(insertNoCapture())); // insert the bed without initiating the video capture process
    connect(bed,SIGNAL(showDialogUntilOut()),this,SLOT(exitBedDialog())); //eject bed before closing the program

    connect(bed,SIGNAL(sendCameraError(int)),this,SLOT(errorMsg(int))); //grab camera bind error
    connect(bed,SIGNAL(closeTimeDialog()),this,SLOT(bedEjectState()),Qt::UniqueConnection);
    connect(bed,SIGNAL(ejectSent()),this,SLOT(arduinoSocketState()),Qt::UniqueConnection);


    connect(ui->PB_startDAQ,SIGNAL(pressed()),this,SLOT(PB_startDAQ_clicked()));
    connect(ui->PB_stopDAQ,SIGNAL(pressed()),this,SLOT(stopAquisition())); // stop the aquisition manually



    connect(opDialog,SIGNAL(sendName(QString)),this,SLOT(getOperator(QString))); // get the current user

    connect(opDialog,SIGNAL(nextPressed()),calibDetails,SLOT(show())); // open study detail dialog
    connect(opDialog,SIGNAL(exitToMainMenu()),this,SLOT(on_actionExit_to_Main_Menu_triggered())); // close the main dialog from the operator dialog
    connect(calibDetails,SIGNAL(previousPressed()),opDialog,SLOT(show())); // go back to operator dialog

    connect(calibDetails, SIGNAL( nextPressed() ),calibTime, SLOT( show() ) ); //open time settings dialog
    connect(calibDetails, SIGNAL( sendCalibrationID( QString,bool) ),this,SLOT(getCalibrationID(QString,bool))); // get study id
    connect(calibDetails, SIGNAL( sendDacayInfo( const QString, const QString, const QString, QDateTime, const double, QString ) ), this, SLOT( setDecayInfo( const QString, const QString, const QString, QDateTime, const double, QString ) ) );

    connect(calibTime, SIGNAL( previousPressed()), calibDetails, SLOT(show())); // go back to details dialog from time dialog
    connect(calibTime, SIGNAL( sendTimeSettings( int, int, QString, QString, bool ) ), calibDetails, SLOT( getTimeSettings(int, int, QString, QString, bool) ) ); //send time parameters and aquisition protocol to the detailsDialog class in order to include them in the database query when we save the study.
    connect(calibTime, SIGNAL( sendTimeSettings( int, int, QString, QString, bool ) ), this, SLOT(acquisitionData(int,int,QString,QString,bool))); //get time parameters and aquisition protocol in order to configure the aquisition

    connect(calibTime,SIGNAL(finishPressed()),this,SLOT(timeFinishedPressed()));

    connect( this, SIGNAL( openTimeSettings() ), calibTime, SLOT( show() ) ); //open time settings dialog
    connect( this, SIGNAL( closeTimeSettings() ), calibTime, SLOT( hide()) ); //hide time settings dialog

    connect(this,SIGNAL(saveStudyToDatabase(QString,QString,QString,QString)),calibDetails,SLOT(save_Session(QString,QString,QString,QString))); //after the aquisition is finished execute the query in the database to save the study's information

    // in this case we press exit after the aquisition so this just cleanup
    connect(exitCalib,SIGNAL(exit()),opDialog,SLOT(close()));
    connect(exitCalib,SIGNAL(exit()),calibDetails,SLOT(close()));
    connect(exitCalib,SIGNAL(exit()),calibTime,SLOT(close()));
    connect(exitCalib,SIGNAL(exit()),this,SLOT(closeWin()));

    connect(this,SIGNAL(terminatePETsysCon()),PETsys,SLOT(closeDaq()));

    connect(this,SIGNAL(exit()),opDialog,SLOT(close()));
    connect(this,SIGNAL(exit()),calibDetails,SLOT(close()));
    connect(this,SIGNAL(exit()),calibTime,SLOT(close()));


}



void betaEye::studyCycle(){

    // the dialog classes instances we use to set a study
    opDialog = new operatorDialog(this);
    time = new timeSettings(true, this);
    study_details = new detailsDialog(m_pReadInputInfoBeta,"betaEye", this);

    configureArduino();

    connect(this,SIGNAL(sendStudyDir(QString)),bed,SLOT(getStudyDir(QString))); // send project directory to arduino so the thread we start will know where to save the optical image later on.
    connect(this,SIGNAL(bedInsertSignal(bool)),bed,SLOT(bedIn(bool)));
    connect(bed,SIGNAL(letBedIn()),this,SLOT(insertCapture())); // arduino informs that the mouse bed is out so we can insert the mouse bed and start the capture procedure
    connect(bed,SIGNAL( make_Start_btn_Avail() ),this,SLOT(getCameraFeedback())); // get feedback from the camera if the image reconstruction was successful or not.
    connect(bed,SIGNAL(insertBedWithoutVid()),this,SLOT(insertNoCapture())); // insert the bed without initiating the video capture process
    connect(bed,SIGNAL(showDialogUntilOut()),this,SLOT(exitBedDialog())); //eject bed before closing the program

    connect(bed,SIGNAL(sendCameraError(int)),this,SLOT(errorMsg(int))); //grab camera bind error
    connect(bed,SIGNAL(initCam()),this,SLOT(bedEjectState()),Qt::UniqueConnection);
    connect(bed,SIGNAL(ejectSent()),this,SLOT(arduinoSocketState()),Qt::UniqueConnection);


    connect(ui->PB_startDAQ,SIGNAL(pressed()),this,SLOT(PB_startDAQ_clicked()));
    connect(ui->PB_stopDAQ,SIGNAL(pressed()),this,SLOT(stopAquisition())); // stop the aquisition manually

    connect(ui->cb_fusion,SIGNAL(clicked()),this,SLOT(setCheckstateOptical()),Qt::UniqueConnection);
    connect(ui->cb_xray,SIGNAL(clicked()),this,SLOT(setCheckstateXray()),Qt::UniqueConnection);



    connect(opDialog,SIGNAL(sendName(QString)),this,SLOT(getOperator(QString))); // get the current user

    connect(opDialog,SIGNAL(nextPressed()),study_details,SLOT(show())); // open study detail dialog
    connect(opDialog,SIGNAL(exitToMainMenu()),this,SLOT(on_actionExit_to_Main_Menu_triggered())); // close the main dialog from the operator dialog
    connect(study_details,SIGNAL(previousPressed()),opDialog,SLOT(show())); // go back to operator dialog

    connect(study_details, SIGNAL( nextPressed() ),time, SLOT( show() ) ); //open time settings dialog
    connect(study_details, SIGNAL( sendStudyID( QString,QString,QString,QString) ),this,SLOT(getStudyID(QString,QString,QString,QString))); // get study id
    connect(study_details, SIGNAL( sendDacayInfo( const QString, const QString, QDateTime, const double, QString ) ), this, SLOT( setDecayInfo( const QString, const QString, QDateTime, const double, QString ) ) );

    connect(time, SIGNAL( previousPressed()), study_details, SLOT(show())); // go back to details dialog from time dialog
    connect(time, SIGNAL( sendTimeSettings( int, int, QString, QString, bool ) ), study_details, SLOT( getTimeSettings(int, int, QString, QString, bool) ) ); //send time parameters and aquisition protocol to the detailsDialog class in order to include them in the database query when we save the study.
    connect(time, SIGNAL( sendTimeSettings( int, int, QString, QString, bool ) ), this, SLOT(acquisitionData(int,int,QString,QString,bool))); //get time parameters and aquisition protocol in order to configure the aquisition

    connect(time,SIGNAL(finishPressed()),this,SLOT(timeFinishedPressed()));

    connect( this, SIGNAL( openTimeSettings() ), time, SLOT( show() ) ); //open time settings dialog
    connect( this, SIGNAL( closeTimeSettings() ), time, SLOT( hide()) ); //hide time settings dialog

    connect(this,SIGNAL(saveStudyToDatabase(QString,QString,QString,QString)),study_details,SLOT(save_Session(QString,QString,QString,QString))); //after the aquisition is finished execute the query in the database to save the study's information

    // complete new study after aquisition
    connect(nextStudy,SIGNAL(followUp()),study_details,SLOT(show())); //after aquisition is finished open details dialog to setup the new study and proceed form there.
    connect(nextStudy,SIGNAL(followUp()),this,SLOT(disableStartButton())); // we are in start/stop state everything so from the FPGA we are ok, just check if the camera capture is succesfull.
    connect(nextStudy,SIGNAL(followUp()),this,SLOT(reset())); // clear the data from the previous study

    // repeate same study after aquisition
    connect(nextStudy,SIGNAL(restartStudy()),time,SLOT(show())); // repeat a study with the exact same details and time parameters, just open the time dialog to proceed from there.
    connect(nextStudy,SIGNAL(restartStudy()),study_details,SLOT(requestNewStudyID())); //generate a new id for the new study
    connect(nextStudy,SIGNAL(restartStudy()),this,SLOT(reset()));  // clear the data form the previous study
    connect(nextStudy,SIGNAL(restartStudy()),this,SLOT(disableStartButton())); // we are in start/stop state everything so from the FPGA we are ok, just check if the camera capture is succesfull.

    // in this case we press exit after the aquisition so this just cleanup
    connect(nextStudy,SIGNAL(exit()),opDialog,SLOT(close()));
    connect(nextStudy,SIGNAL(exit()),study_details,SLOT(close()));
    connect(nextStudy,SIGNAL(exit()),time,SLOT(close()));
    connect(nextStudy,SIGNAL(exit()),this,SLOT(closeWin()));

    connect(this,SIGNAL(terminatePETsysCon()),PETsys,SLOT(closeDaq()));

    connect(this,SIGNAL(exit()),opDialog,SLOT(close()));
    connect(this,SIGNAL(exit()),study_details,SLOT(close()));
    connect(this,SIGNAL(exit()),time,SLOT(close()));



}

void betaEye::configureArduino(){

    QTime dieTime;
    dieTime = QTime::currentTime().addSecs(5);

    bool initStarted=false;

    while( QTime::currentTime() <= dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents);

        if( QTime::currentTime() == dieTime ) {
            while(!arduinoConfigured) {
                QCoreApplication::processEvents(QEventLoop::AllEvents);
                if ( !initStarted ) {
                    bed->configure_ttyACM0();
                    bed->reset();
                    initStarted=true;
                }
            }
       }
    }

    PETsys->initDaq(); // initiate the programming of the FPGA (PET DAQ)
    opDialog->show(); //show the operator dialog
}


void betaEye::getOperator(QString name){ deviceOPerator = name; }

void betaEye::getStudyID(QString ID,QString name,QString patient,QString proj)
{
    StudyID = ID;
    studyName = name;
    animal = patient;
    project = proj;
}

void betaEye::getCalibrationID(QString ID,bool validationOn)
{
    StudyID = ID;
    studyName = "Flood experiment";
    project = " ";
    m_validationOn=validationOn;

    qDebug() << "Validation " << m_validationOn <<endl;
    exitCalib->setTypeOfStudy(m_validationOn);
}


void betaEye::insertCapture()
{
    QMessageBox* msgBox = new QMessageBox( this );
    msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
    msgBox->setStandardButtons( QMessageBox::Ok );
    msgBox->setWindowTitle( tr("Info") );
    if(m_calibrationMode)
        msgBox->setText( tr("Acquisition time setting are all set. Please ensure that the flood phantom was placed correctly and press ok, to insert the bed inside the system.") );
    else
        msgBox->setText( tr("Acquisition time setting are all set. Please prepare the mouse and press ok when you are ready, to insert the bed inside the system.") );

    msgBox->setModal( false );
    msgBox->open( this, SLOT(msgBoxClosed(QAbstractButton*)) ); // connect to this function when ok is pressed on the message dialog to open another confirmation message.
}

void betaEye::insertNoCapture()
{
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

void betaEye::exitBedDialog()
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

void betaEye::msgBoxBedIn(QAbstractButton*)
{
    if(aboutToExit)
    {
        emit exit();
        emit terminatePETsysCon();
        if(m_calibrationMode)
            bed->calibInsert_bed();
        else
            bed->onlyMoveBedIn();

        bed->exit();
        emit exitToMainWindow();
    }
    else{
        if(m_calibrationMode)
            bed->calibInsert_bed();
        else
            bed->onlyMoveBedIn();
    }

}

void betaEye::msgBoxClosed(QAbstractButton*)
{
    if(m_calibrationMode)
        bed->calibInsert_bed();
    else
        bed->insert_bed();
    emit bedInsertSignal(true);
}

void betaEye::msgBox2Closed(QAbstractButton*){
    if(m_calibrationMode)
        bed->calibInsert_bed();
    else
        bed->insert_bed();
}



void betaEye::enableStartButton()
{
    ui->PB_startDAQ->setEnabled(true);
}

void betaEye::closeWin(){
    qDebug() << "before close window " <<endl;
    aboutToExit=true;
    if(m_calibrationMode)
        bed->calibEject_bed();
    else
        bed->onlyMoveBedOut();
    qDebug() << "close window " <<endl;
}


void betaEye::on_actionExit_to_Main_Menu_triggered()
{
    emit terminatePETsysCon();
    if(m_calibrationMode)
        bed->calibInsert_bed();
    else
        bed->onlyMoveBedIn();
    bed->exit();
    emit exitToMainWindow();
}

void betaEye::on_PB_eject_clicked() {
    if(m_calibrationMode)
        bed->calibEject_bed();
    else
        bed->onlyMoveBedOut();
}


void betaEye::timeFinishedPressed(){ timeFinishBtnPressed=true; }


void betaEye::errorMsg(int errorCode)
{
    if (errorCode==5) {
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


void betaEye::CameraErrorMsgAction(QAbstractButton*) { std::exit(EXIT_FAILURE); } //exit application

void betaEye::acquisitionData(int duration,int frame, QString d_unit, QString f_unit, bool fDynamic)
{

    m_castorFrame = new castor( m_pReadInputInfoBeta, m_calibrationMode, m_validationOn);
    m_castorFrame->setActivityUnit( m_sActivityUnit );
    fastDynamic= fDynamic; // see if we use the fast dynamic time protocol




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
        // convert the duration and frame time  to seconds depending the time unit
        if( d_unit=="sec")
            duration_time = duration;
        else if(d_unit=="min")
            duration_time = duration*60;

        //frame_time is in sec always
        if ( f_unit=="sec" )
            frame_time = frame;
        else if ( f_unit=="min" )
            frame_time = frame*60;
    }




    if(frame_time ==0 || duration_time ==0){ // check if the parameters are set
        QMessageBox* msgBox = new QMessageBox( this );
        msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        msgBox->setStandardButtons( QMessageBox::Ok );
        msgBox->setWindowTitle( tr("Attention") );
        msgBox->setText( tr("Please define an experiment time duration and frame time duration before starting the aquisition.") );
        msgBox->setModal(false);
        msgBox->open( this, SIGNAL(openTimeSettings()));//re-open the time dialog to set the duration and frame time
    }  //error messgae if user does not set the time parameters at all
    else {
        if(duration_time % frame_time == 0) {
            //set range for the duration and frame progress bars
            ui->daq_progress->setMinimum(0);
            ui->daq_progress->setMaximum(duration_time);

            ui->frame_progress->setMinimum(0);
            ui->frame_progress->setMaximum(frame_time);

            // fill these fields with indormation about the study
            ui->LE_frameRate->setText(QString::number(frame)+" "+f_unit);
            ui->LE_duration->setText(QString::number(duration)+" "+d_unit);
            ui->TL_studyID->setText(StudyID);
            ui->TL_studyName->setText(studyName);
            ui->TL_animalID->setText(animal);
            ui->TL_project->setText(project);

            directoryCreation(); // create the directories where the files from the aquisition are going to be saved

            //After the creation of the directories set the outpath for the castor file
            m_castorFrame->setOutputPath(qsCastorDir);


            ui->LE_radioNuclide->setText( m_qsNuclideName );
            ui->LE_injectActivity->setText( QString::number( m_dActivity ) + " " + m_sActivityUnit );

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


            if ( noTimeSettings ) {
                ui->PB_startDAQ->setEnabled(true);
                noTimeSettings = false;
            }
        }  //error message if user select an invalid experiment and frame time duration.
        else {
            QMessageBox* msgBox = new QMessageBox( this );
            msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
            msgBox->setStandardButtons( QMessageBox::Ok );
            msgBox->setWindowTitle( tr("Attention") );
            msgBox->setText( tr("Please select an experiment time duration and frame time duration that their combination gives a complete division.") );
            msgBox->setModal(false);
            msgBox->open( this, SIGNAL(openTimeSettings()));//re-open the time dialog to set a correct combination
        }



    }

}



void betaEye::startAquisition()
{

    if(duration_time!=0 && frame_time!=0){
        BUFFER  = new boost::circular_buffer<EventMsg>(400000000); // set initial size of the circular buffer

        char * myfifo = "/tmp/hitfifo";
        mkfifo(myfifo, 0666);
        qDebug() << "Initiating threads " <<endl;
        initiateThreads();

        //QString pathName = QStandardPaths::locate(QStandardPaths::DocumentsLocation,"VISUAL-eyes",QStandardPaths::LocateDirectory);
        QLocale locale(QLocale::English);
        QString date = locale.toString(QDateTime::currentDateTime(), "dd.MM.yyyy hh:mm:ss AP");

        ui->LE_startTime->setText( date );
        ui->LE_startTime->adjustSize();

        counter++;

        if( fastDynamic )
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
        msgBox->setText( tr("Time settings were omitted! Please select time parameters and try again.") );
        msgBox->setModal(false); // if you want it non-modal
        msgBox->open( this, SIGNAL(openTimeSettings()));
    }
}


void betaEye::cb_ColorMap_currentIndexChanged(int val)
{
    if(val!=2)
        cM->BlackBased(val);
    else
        cM->BlueBased(val);

    correctedPlot_spectrogram->setColorMap(cM);
    summedCorrectedPlot_spectrogram->setColorMap(cM);
    rawPlot1_spectrogram->setColorMap(cM);
    rawPlot2_spectrogram->setColorMap(cM);

    correctedPlot->replot();
    if(counter!=0)
        summedCorrectedPlot->replot();

    RawPlot1->replot();
    RawPlot2->replot();
}

void betaEye::qwt_plots()
{
    cM = new ColorMap();
    cM->BlackBased(1);


    correctedPlot = new QwtPlot(this);
    correctedPlot->setAutoDelete(true);
    correctedPlot->setAxisScale(QwtPlot::xBottom, 0.0,image_SIZE_Y,0 );
    correctedPlot->setAxisScale(QwtPlot::yLeft,image_SIZE_X,0.0,0 );
    correctedPlot->enableAxis(QwtPlot::xBottom,false);
    correctedPlot->enableAxis(QwtPlot::yLeft,false);
    correctedPlot->plotLayout()->setAlignCanvasToScales(true);

    ui->liveLayout->addWidget(correctedPlot);

    correctedPlot_spectrogram = new QwtPlotSpectrogram();
    correctedPlot_spectrogram->setColorMap(cM);
    correctedPlot_spectrogram->setRenderThreadCount(1);
    correctedPlot_spectrogram->attach(correctedPlot);


    summedCorrectedPlot= new QwtPlot(this);
    summedCorrectedPlot->setAutoDelete(true);
    summedCorrectedPlot->setAxisScale(QwtPlot::xBottom, 0.0,image_SIZE_Y_Castor,0 );
    summedCorrectedPlot->setAxisScale(QwtPlot::yLeft,image_SIZE_X_Castor,0.0,0 );
    summedCorrectedPlot->enableAxis( QwtPlot::xBottom,false);
    summedCorrectedPlot->enableAxis( QwtPlot::yLeft,false);
    summedCorrectedPlot->plotLayout()->setAlignCanvasToScales(true);

    ui->FrameLayout->addWidget(summedCorrectedPlot);

    summedCorrectedPlot_spectrogram = new QwtPlotSpectrogram();
    summedCorrectedPlot_spectrogram->setColorMap(cM);
    summedCorrectedPlot_spectrogram->setRenderThreadCount(1);
    summedCorrectedPlot_spectrogram->attach(summedCorrectedPlot);


    RawPlot1= new QwtPlot(this);
    RawPlot1->setAutoDelete(true);
    RawPlot1->plotLayout()->setAlignCanvasToScales( true );
    RawPlot1->setAxisScale(QwtPlot::xBottom, 0.0, output_size_y_PET,0 );
    RawPlot1->setAxisScale(QwtPlot::yLeft,output_size_x_PET,0.0,0 );
    RawPlot1->enableAxis(QwtPlot::xBottom, false);
    RawPlot1->enableAxis(QwtPlot::yLeft,false);

    ui->RawLayout->addWidget(RawPlot1);

    rawPlot1_spectrogram = new QwtPlotSpectrogram();
    rawPlot1_spectrogram->setColorMap(cM);
    rawPlot1_spectrogram->setRenderThreadCount(1);
    rawPlot1_spectrogram->attach(RawPlot1);

    RawPlot2= new QwtPlot(this);
    RawPlot2->setAutoDelete(true);
    RawPlot2->setAxisScale(QwtPlot::xBottom, 0.0, output_size_y_PET,0 );
    RawPlot2->setAxisScale(QwtPlot::yLeft,output_size_x_PET,0.0,0 );
    RawPlot2->plotLayout()->setAlignCanvasToScales( true );
    RawPlot2->enableAxis(QwtPlot::xBottom, false);
    RawPlot2->enableAxis(QwtPlot::yLeft,false);

    ui->RawLayout_2->addWidget(RawPlot2);

    rawPlot2_spectrogram = new QwtPlotSpectrogram();
    rawPlot2_spectrogram->setColorMap(cM);
    rawPlot2_spectrogram->setRenderThreadCount(1);
    rawPlot2_spectrogram->attach(RawPlot2);

    rawMatrix1 = new QwtMatrixRasterData();
    rawMatrix2 = new QwtMatrixRasterData();


    rawMatrix1->setInterval( Qt::XAxis, QwtInterval( 0, output_size_y_PET) );
    rawMatrix1->setInterval( Qt::YAxis, QwtInterval( 0,output_size_x_PET) );

    rawMatrix1->setInterval( Qt::ZAxis, QwtInterval( 0, 0) );
    rawMatrix2->setInterval( Qt::ZAxis, QwtInterval( 0, 0) );

    rawMatrix2->setInterval( Qt::XAxis, QwtInterval( 0, output_size_y_PET) );
    rawMatrix2->setInterval( Qt::YAxis, QwtInterval( 0,output_size_x_PET) );


    energyPlot1=new QwtPlot(this);
    energyPlot1->setAutoDelete(true);

    energyPlot1->setAxisScale(QwtPlot::xBottom,0,2048,0);
    energyPlot1->setAxisScale(QwtPlot::yLeft,0,0,0);
    energyPlot1->plotLayout()->setAlignCanvasToScales(true);

    ui->Energy_Spectrum_Layout->addWidget(energyPlot1);

    curve1 = new QwtPlotCurve();
    curve1->setPen( Qt::black, 1);
    curve1->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    curve1->attach(energyPlot1);

    energyPlot2=new QwtPlot(this);
    energyPlot2->setAutoDelete(true);

    energyPlot2->setAxisScale(QwtPlot::xBottom,0,2048,0);
    energyPlot2->setAxisScale(QwtPlot::yLeft,0,0,0);
    energyPlot2->plotLayout()->setAlignCanvasToScales(true);

    ui->Energy_Spectrum_Layout_2->addWidget(energyPlot2);

    curve2 = new QwtPlotCurve();
    curve2->setPen( Qt::black, 1);
    curve2->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    curve2->attach(energyPlot2);


    liveMatrix = new QwtMatrixRasterData();
    summedMatrix = new QwtMatrixRasterData();

    liveMatrix->setInterval( Qt::XAxis, QwtInterval( 0,image_SIZE_Y) );
    liveMatrix->setInterval( Qt::YAxis, QwtInterval( 0,image_SIZE_X));

    summedMatrix->setInterval( Qt::XAxis, QwtInterval( 0, image_SIZE_Y_Castor) );
    summedMatrix->setInterval( Qt::YAxis, QwtInterval( 0, image_SIZE_X_Castor) );


    liveMatrix->setInterval( Qt::ZAxis, QwtInterval( 0, 0) );
    summedMatrix->setInterval(Qt::ZAxis, QwtInterval( 0, 0));

    if(m_calibrationMode){
        qwt_validation_plots();
    }

}


void betaEye::qwt_validation_plots(){
    /**
       Qwt validation plots
    */

    rawHead1=new QwtPlot(this);
    rawHead1->setAutoDelete(true);

    rawHead1->setAxisScale(QwtPlot::xBottom,0,2048,0);
    rawHead1->setAxisScale(QwtPlot::yLeft,0,0,0);
    rawHead1->plotLayout()->setAlignCanvasToScales(true);

    ui->rawHead1_layout->addWidget(rawHead1);

    rawCurve1 = new QwtPlotCurve();
    rawCurve1->setPen( Qt::black, 1);
    rawCurve1->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    rawCurve1->attach(rawHead1);

    rawHead2=new QwtPlot(this);
    rawHead2->setAutoDelete(true);

    rawHead2->setAxisScale(QwtPlot::xBottom,0,2048,0);
    rawHead2->setAxisScale(QwtPlot::yLeft,0,0,0);
    rawHead2->plotLayout()->setAlignCanvasToScales(true);

    ui->rawHead2_layout->addWidget(rawHead2);

    rawCurve2 = new QwtPlotCurve();
    rawCurve2->setPen( Qt::black, 1);
    rawCurve2->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    rawCurve2->attach(rawHead2);



    correctedHead1=new QwtPlot(this);
    correctedHead1->setAutoDelete(true);

    correctedHead1->setAxisScale(QwtPlot::xBottom,0,2048,0);
    correctedHead1->setAxisScale(QwtPlot::yLeft,0,0,0);
    correctedHead1->plotLayout()->setAlignCanvasToScales(true);

    ui->correctedHead1_layout->addWidget(correctedHead1);

    correctedCurve1 = new QwtPlotCurve();
    correctedCurve1->setPen( Qt::black, 1);
    correctedCurve1->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    correctedCurve1->attach(correctedHead1);

    correctedHead2=new QwtPlot(this);
    correctedHead2->setAutoDelete(true);

    correctedHead2->setAxisScale(QwtPlot::xBottom,0,2048,0);
    correctedHead2->setAxisScale(QwtPlot::yLeft,0,0,0);
    correctedHead2->plotLayout()->setAlignCanvasToScales(true);

    ui->correctedHead2_layout->addWidget(correctedHead2);

    correctedCurve2 = new QwtPlotCurve();
    correctedCurve2->setPen( Qt::black, 1);
    correctedCurve2->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    correctedCurve2->attach(correctedHead2);


    resolutionHead1=new QwtPlot(this);
    resolutionHead1->setAutoDelete(true);

    resolutionHead1->setAxisScale(QwtPlot::xBottom,10,50,0);
    resolutionHead1->setAxisScale(QwtPlot::yLeft,0,0,0);
    resolutionHead1->plotLayout()->setAlignCanvasToScales(true);

    ui->resolutionHead1_layout->addWidget(resolutionHead1);

    resolutionCurve1 = new QwtPlotCurve();
    resolutionCurve1->setPen( Qt::black, 1);
    resolutionCurve1->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    resolutionCurve1->attach(resolutionHead1);

    resolutionHead2=new QwtPlot(this);
    resolutionHead2->setAutoDelete(true);

    resolutionHead2->setAxisScale(QwtPlot::xBottom,10,50,0);
    resolutionHead2->setAxisScale(QwtPlot::yLeft,0,0,0);
    resolutionHead2->plotLayout()->setAlignCanvasToScales(true);

    ui->resolutionHead2_layout->addWidget(resolutionHead2);

    resolutionCurve2 = new QwtPlotCurve();
    resolutionCurve2->setPen( Qt::black, 1);
    resolutionCurve2->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    resolutionCurve2->attach(resolutionHead2);
}


void betaEye::setBackgroundImages(){

    /**
        Set optical and xray image path
   **/
    m_opticalImagePath = Storage.path() + "/optical.png";
    m_xrayImagePath = Storage.path() + "/Xray.png";

    /**
        Read images to cv matrix
   **/
    m_opticalImageMat= cv::imread(m_opticalImagePath.toStdString(),cv::IMREAD_GRAYSCALE);
    m_xrayImageMat=cv::imread(m_xrayImagePath.toStdString(),cv::IMREAD_GRAYSCALE);

    /**
        Perform image flips
   **/
    QMap< QString, int > qmFlips;
    qmFlips.insert( "x", 0 );
    qmFlips.insert( "y", 1 );

    cv::rotate( m_opticalImageMat, m_opticalImageMat, cv::ROTATE_90_CLOCKWISE);
    cv::rotate( m_xrayImageMat,  m_xrayImageMat, cv::ROTATE_90_CLOCKWISE);
    if ( m_pReadInputInfoBeta->getFlips().size() > 0){
       foreach ( QString flip,  m_pReadInputInfoBeta->getFlips() ){
           if(flip!=""){
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


    cv::resize(m_opticalImageMat, m_opticalImageMat, cv::Size(576, 288), 0, 0, cv::INTER_CUBIC);
    cv::resize( m_xrayImageMat,  m_xrayImageMat, cv::Size(576, 288), 0, 0, cv::INTER_CUBIC);

    m_opticalImageMat.convertTo(m_opticalImageMat, CV_8U);
    m_xrayImageMat.convertTo(m_xrayImageMat, CV_8U);

}

void betaEye::on_cb_fusion(bool checked)
{
    if ( checked ) {
        if (m_opticalImageMat.empty()){
            correctedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
            summedCorrectedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
         }else{
            ui->opacitySlider->setEnabled(true);
            addOpticalBackground();
         }
    }
    else if ( !checked ) {
        removeBackground();
        correctedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
        summedCorrectedPlot->setCanvasBackground(QBrush(QColor(53,53,53)));
    }
}

void betaEye::addOpticalBackground(){

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

void betaEye::removeBackground(){

    correctedPlot_spectrogram->setAlpha(255);
    summedCorrectedPlot_spectrogram->setAlpha(255);
    ui->opacitySlider->setDisabled(true);
}

void betaEye::addXrayBackground(){
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


void betaEye::opacityValueChanged(int){
    int val = ui->opacitySlider->value();
    correctedPlot_spectrogram->setAlpha(val);
    summedCorrectedPlot_spectrogram->setAlpha(val);
}

void betaEye::setCheckstateOptical(){
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

void betaEye::setCheckstateXray(){
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

void betaEye::on_cb_xray(bool checked)
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

void betaEye::setDecayInfo( const QString collimator, const QString folder, const QString name, QDateTime dateTime, const double activity, QString actUnit )
{
    // Folder is not used in beta-eye but is needed in gamma-eye
    m_qsNuclidedFolder = folder;
    m_qsNuclideName = name;
    m_qdtInjectionDateTime = dateTime;
    m_dActivity = activity;
    m_sActivityUnit = actUnit;

    m_newIsotope = m_pReadInputInfoBeta->getPetIsotope(m_qsNuclideName);
}

void betaEye::getCameraFeedback()
{
    if(sensor_temperature->init_system()){
        if (sensor_temperature->check_temperature()){
            ui->PB_startDAQ->setEnabled(true);
        }else {
            sensor_temperature->close_electronics();
            sensors_state();
        }
    }else{
           fpga_state();
    }
}

void betaEye::bedEjectState()
{
    bedMoved=true;
    emit closeTimeSettings();
}

void betaEye::disableStartButton()
{
    ui->PB_startDAQ->setEnabled(false);
}

void betaEye::stopWithError()
{
    emit onPressedStop();
    QLocale locale(QLocale::English);
    QString date = locale.toString(QDateTime::currentDateTime(), "dd.MM.yyyy hh:mm:ss AP");
    ui->LE_finishTime->setText(date);

    counter=0;
    ui->LE_currFrame->clear();
    frame_time=0;
    duration_time=0;

    ui->daq_progress->reset();
    ui->frame_progress->reset();

    if(!BUFFER->empty())
        BUFFER->clear();

    ui->PB_stopDAQ->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
    ui->hsContrastB->setEnabled(false);

    emit saveStudyToDatabase(corrD,deviceOPerator,ui->LE_startTime->text(),ui->LE_finishTime->text());
    if(m_calibrationMode)
        calibrationInfoGenerator();
    else
        infoFileGenerator();

    fastDynamic=false;
}

void betaEye::PB_startDAQ_clicked()
{
    if(!m_calibrationMode)
        setBackgroundImages();
    ui->cb_fusion->setEnabled(true);
    ui->cb_xray->setEnabled(true);

    if(duration_time!=0 && frame_time!=0) {//check time parameters
        ui->PB_startDAQ->setEnabled(false);//disable start button
        timeFinishBtnPressed=false;
        bedMoved=false;
    }
    else {
        QMessageBox* msgBox = new QMessageBox( this );
        msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        msgBox->setStandardButtons( QMessageBox::Ok );
        msgBox->setWindowTitle( tr("Error") );
        msgBox->setText( tr("Time settings were omitted!Please select time parameters and try again.") );
        msgBox->setModal(false);
        msgBox->open( this, SIGNAL(openTimeSettings())); //re-open time setting dialog.
    }
    startAquisition();
}

void betaEye::sliderValueChanged(int)
{
    int val = ui->horizontalSlider->value();
    val =  100 - val;
    contrastPercentage = (double)val/(double)100;
    emit sendContrast(contrastPercentage);
}

void betaEye::sliderSummedValueChanged( int )
{
    QVector<qreal> tempStore = m_summedImg;

    // Calculate first the m_dMaxCor for performing the contrast adjustement
    int val = ui->hsContrastB->value();
    val =  100 - val;
    contrastPercentageSummed = (double)val/(double)100;

    m_dMaxCor = 0.0;
    for ( int i = 0; i < m_summedImg.size(); i++){
        if ( m_summedImg[ i ] >= m_dMaxCor)
            m_dMaxCor = m_summedImg[ i ];
    }

    double con_percentage = m_dMaxCor*contrastPercentageSummed;
    m_dMaxCor = m_dMaxCor - con_percentage;

    summedMatrix->setValueMatrix(tempStore,image_SIZE_Y_Castor);
    summedMatrix->setResampleMode(summedMatrix->BilinearInterpolation);
    summedMatrix->setInterval( Qt::ZAxis, QwtInterval( 0, m_dMaxCor) );
    summedCorrectedPlot_spectrogram->setColorMap(cM);
    summedCorrectedPlot_spectrogram->setData(summedMatrix);
    tempStore.clear();
    summedCorrectedPlot->replot();

}

void betaEye:: arduino_State(){ arduinoConfigured=true; }

void betaEye::arduinoSocketState()
{
    if ( timeFinishBtnPressed && !bedMoved ){
        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setAttribute( Qt::WA_DeleteOnClose );
        msgBox->setWindowTitle( tr("Error") );
        msgBox->setButtonText(1,"Restart");
        msgBox->setIcon(QMessageBox::Critical);
        msgBox->setText( tr("Connection to hardware has been disturbed. Please check cable connections and press restart!") );
        msgBox->setModal(true);
        msgBox->open( this, SLOT(RestartApplication()));
    }
}

void betaEye::sensors_state(){
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setAttribute( Qt::WA_DeleteOnClose );
    msgBox->setWindowTitle( tr("Error") );
    msgBox->setButtonText(1,"Restart");
    msgBox->setIcon(QMessageBox::Critical);
    msgBox->setText( tr("Sensors' temperature is too high. Please switch off the device and contact BIOEMTECH's support.") );
    msgBox->setModal(true);
    msgBox->open( this, SLOT(RestartApplication()));
}

void betaEye::fpga_state(){
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setAttribute( Qt::WA_DeleteOnClose );
    msgBox->setWindowTitle( tr("Error") );
    msgBox->setButtonText(1,"Restart");
    msgBox->setIcon(QMessageBox::Critical);
    msgBox->setText( tr("FPGA connection is lost. Please please check cable connections and press Restart.") );
    msgBox->setModal(true);
    msgBox->open( this, SLOT(RestartApplication()));
}

void betaEye::RestartApplication()
{
    reset();
    emit exit();
    if(m_calibrationMode)
        bed->calibInsert_bed();
    else
        bed->onlyMoveBedIn();
    bed->exit();
    this->close();
    emit exitToMainWindow();
}

void betaEye::calibrationInfoGenerator()
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
        qDebug() << radioUnit << endl;

    }

    QString filename = Storage.absolutePath().append("/CalibrationInfo.txt");
    QFile file;
    file.setFileName(filename);

    QTextStream out(&file);
    if(file.open(QIODevice::WriteOnly))
    {
        out << "ID: " << StudyID << "\n";
        out << "Device: " << deviceid << endl;
        out << "System: " << m_pReadInputInfoBeta->getSystemName() << endl;
        out << "Image Flip: " << m_pReadInputInfoBeta->getFlips().join(",") << endl;
        out << "Name: " << "Flood experiment" << endl;
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




void betaEye::infoFileGenerator()
{
    QSqlQuery q;
    QString deviceid, date,startTime,finTime,comments,duration,frame,exp_tU,frame_tU;
    QString name, animal_name, breed, species, age, weight, gender, r_pharma, volume;
    QString activity, injection_date,path_id, isFastDynamic;
    QString Operator, project, injected_activity, marking, fileDirectory;
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
        qDebug() << radioUnit << endl;
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
        out << "System: " << m_pReadInputInfoBeta->getSystemName() << endl;
        out << "Image Flip: " << m_pReadInputInfoBeta->getFlips().join(",") << endl;
        out << "Name: " << name << endl;
        out << "Project: " << project << endl;
        out << "Animal name: " << animal_name << endl;
        out << "Breed: " << breed << endl;
        out << "Species: " << species << endl;
        out << "Age: " << age << endl;
        out << "Marking: " << marking << endl;
        out << "Weight: " << weight << endl;
        out << "Gender: " << gender << endl;
        out << "Radionuclide: " << m_qsNuclideName << endl;
        if ( radioUnit == 0)
            out << "Radio unit: " << "MBq" << endl;
        else
            out << "Radio unit: " << "uCi" << endl;

        out << "Radiopharmaceutical: " << r_pharma << endl;
        out << "Limits: " << m_pReadInputInfoBeta->getNuclide_lim1() << " " << m_pReadInputInfoBeta->getNuclide_lim2() << endl;
        out << "Activity parameters a: " << m_pReadInputInfoBeta->getNuclide_a1() << " " << m_pReadInputInfoBeta->getNuclide_a2() << " " << m_pReadInputInfoBeta->getNuclide_a3() << endl;
        out << "Activity parameters b: " << m_pReadInputInfoBeta->getNuclide_b1() << " " << m_pReadInputInfoBeta->getNuclide_b2() << " " << m_pReadInputInfoBeta->getNuclide_b3() << endl;
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
        if ( radioUnit == 0)
            out << "Radio unit: " << "MBq" << endl;
        else
            out << "Radio unit: " << "uCi" << endl;

        out << "Date: " << date << "\n";
        out << "Start Time: " << startTime << "\n";
        out << "Finish Time: " << finTime << "\n";
        if ( isFastDynamic == "0")
            out << "Fast Dynamic: " << "No" << endl;
        else
            out << "Fast Dynamic: " << "Yes" << endl;

        if ( fastDynamic ) {
            out << "Experiment Duration: " << "60" << " " << "min" << "\n";
            out << "Frame Duration: " << "0-1 min: 10sec ,"<< " "<< " 1-5 min: 30sec ," << " "<< "5-10 min: 60sec ," << " " << "10-60 min: 120 sec ," << "\n\n";
        }
        else{
            out << "Experiment Duration: " << duration << " " << exp_tU << "\n";
            out << "Frame Duration: " << frame << " " << frame_tU <<"\n\n";
        }
        out << "Comments: " << comments ;
    }
    file.close();
}

void betaEye::initiateThreads()
{

    contrastPercentage = 0.0;

    QTimer *timeServer = new QTimer();
    timeServer->setInterval(0);

    qDebug() << "Checkpoint 1 " << endl;


    petsysDAQ * petsysDAQworker = new petsysDAQ(m_pReadInputInfoBeta,duration_time, rawD);
    daqThread=new QThread();

    readRawDataPipe * rawDataWorker = new readRawDataPipe(BUFFER);
    rawDataThread = new QThread();

    connect(daqThread, SIGNAL(started()), petsysDAQworker, SLOT(startAcqSipm()));
    connect(rawDataThread, SIGNAL(started()),rawDataWorker, SLOT(postProc()));

    petsysDAQworker->moveToThread(daqThread);
    rawDataWorker->moveToThread(rawDataThread);

    rawDataThread->start(QThread::TimeCriticalPriority);
    daqThread->start(QThread::TimeCriticalPriority);


    DAQcounter *daqCount = new DAQcounter(duration_time,frame_time,fastDynamic);
    counterThread = new QThread();

    connect(petsysDAQworker,SIGNAL(daqStarted()),daqCount,SLOT(Initiate()));
    connect(daqCount,SIGNAL(DAQprogressBarValueChanged(int)),ui->daq_progress,SLOT(setValue(int)));
    connect(daqCount,SIGNAL(frameProgressBarValueChanged(int)),ui->frame_progress,SLOT(setValue(int)));
    connect(daqCount,SIGNAL(displayProgress()),ui->daq_progress,SLOT(update()));
    connect(daqCount,SIGNAL(displayProgress()),ui->frame_progress,SLOT(update()));
    connect(daqCount,SIGNAL(replotFrame()),this,SLOT(frameReplot()));
    connect(daqCount,SIGNAL(sendNewFrameTime(int)),this,SLOT(getNewFrameTime(int)));
    connect(daqCount,SIGNAL(stopEverthing()),this,SLOT(stopAquisition()));
    connect(this,SIGNAL(onPressedStop()),daqCount,SLOT(stopTimer()));
    connect(counterThread, SIGNAL(finished()), daqCount, SLOT(deleteLater()));
    connect(counterThread, SIGNAL(finished()), counterThread, SLOT(deleteLater()));

    daqCount->moveToThread(counterThread);

    qDebug() << "Starting worker " << endl;
    m_castorFrame->setInjectionTime(m_qdtInjectionDateTime);

    PETsysWorker * worker= new PETsysWorker(m_pReadInputInfoBeta,BUFFER, rawD, corrD, m_qsNuclideName, m_qdtInjectionDateTime, m_dActivity,
                                                m_sActivityUnit, duration_time, frame_time, m_castorFrame, m_calibrationMode, m_validationOn,m_newIsotope);


    CastorFrameThread =new QThread();
    PETthread = new QThread();



    QTimer *progress = new QTimer();
    progress->setInterval(500);


    connect( PETthread, SIGNAL( started() ), worker, SLOT( initialise() ));
    connect( PETthread, SIGNAL( started() ), progress, SLOT(start() ) );

    connect( m_castorFrame, SIGNAL( sumImgComputed(QVector<qreal>)), this, SLOT( updateSummedImgPlot(QVector<qreal>)));
    connect( worker, SIGNAL(castor_frame(QString)), m_castorFrame, SLOT(createFilesForCastor(QString)));

    connect( CastorFrameThread, SIGNAL( finished() ), m_castorFrame, SLOT( deleteLater() ) );
    connect( CastorFrameThread, SIGNAL( finished() ), CastorFrameThread, SLOT( deleteLater() ) );

    m_castorFrame->moveToThread( CastorFrameThread );
    CastorFrameThread->start( QThread::TimeCriticalPriority );

    connect( rawDataWorker, SIGNAL(sendEvent()), worker, SLOT(run()));
    connect( this, SIGNAL( sendTimeToframe() ), worker, SLOT(stopToFrame()));
    connect( this, SIGNAL( sendTimeToframe() ), worker, SLOT(frameReconstruction()));
    connect( this, SIGNAL( onPressedStop() ), worker, SLOT( stopImaging() ) );

    connect( progress, SIGNAL(timeout()), worker,SLOT(imagingData()));

    connect( this, SIGNAL( sendContrast( double ) ), worker, SLOT( receiveContrast( double ) ) ) ;
    connect( worker, SIGNAL(sendImagingDataProgress(QVector<qreal>,QVector<qreal>,QVector<qreal>,QPolygonF,QPolygonF,double,double,double,int,int)),
             this, SLOT(plotsUpdate(QVector<qreal>,QVector<qreal>,QVector<qreal>,QPolygonF,QPolygonF,double,double,double,int,int)),Qt::QueuedConnection);

    connect( worker, SIGNAL( stopProcessing() ), progress, SLOT( stop() ) );
    connect( worker, SIGNAL( stopProcessing() ), PETthread, SLOT( quit() ) );


    connect(petsysDAQworker, SIGNAL(daqFinished()), daqThread, SLOT(quit()));
    connect(petsysDAQworker, SIGNAL(daqFinished()), petsysDAQworker, SLOT(deleteLater()));
    connect(daqThread, SIGNAL(finished()), daqThread, SLOT(deleteLater()));



    connect(rawDataWorker, SIGNAL(post_finished()), rawDataThread, SLOT(quit()));
    connect(rawDataWorker, SIGNAL(post_finished()), rawDataWorker, SLOT(deleteLater()));
    connect(rawDataThread, SIGNAL(finished()), rawDataThread, SLOT(deleteLater()));



    connect( PETthread, SIGNAL( finished() ), worker, SLOT( deleteLater() ) );
    connect( PETthread, SIGNAL( finished() ), progress, SLOT( deleteLater() ) );
    connect( PETthread, SIGNAL( finished() ), PETthread, SLOT( deleteLater() ) );


    worker->moveToThread( PETthread );
    progress->moveToThread( PETthread );
    PETthread->start( QThread::TimeCriticalPriority );
    counterThread->start(QThread::TimeCriticalPriority);

}

void betaEye::getNewFrameTime(int frameTime)
{
    frame_time = frameTime;
    ui->frame_progress->reset();
    ui->frame_progress->setMinimum(0);
    ui->frame_progress->setMaximum(frame_time);
    ui->LE_frameRate->setText(QString::number(frame_time)+" "+"sec");
}

void betaEye::frameReplot()
{
    emit sendTimeToframe();

    firstSummed2=true;
    qDebug() << " BUFFER size at frame  "  << BUFFER->size() << endl;

    frameProgress=0;
    ui->frame_progress->reset();

    counter++;

    if(fastDynamic)
        ui->LE_currFrame->setText(QString::number(counter)+"/"+QString::number(44)+" Frame");
    else
        ui->LE_currFrame->setText(QString::number(counter)+"/"+QString::number(duration_time/frame_time)+" Frame");
}


void betaEye::directoryCreation()
{

    QString pathName;
    if(m_calibrationMode)
        pathName = QStandardPaths::locate(QStandardPaths::DocumentsLocation,"CALIBRATE-eyes",QStandardPaths::LocateDirectory);
    else
        pathName = QStandardPaths::locate(QStandardPaths::DocumentsLocation,"VISUAL-eyes",QStandardPaths::LocateDirectory);

    //QLocale locale(QLocale::English);
    //QString date = locale.toString(QDateTime::currentDateTime(), "dd.MM.yyyy hh:mm:ss AP");

    //QString Op;

    pathName.append("/b-eye");
    pathName.append("/" + deviceOPerator);
    pathName.append("/" + StudyID);
    Storage.setPath(pathName);

    img.setPath(Storage.absolutePath());
    img.mkpath("IMAGES");
    img.setPath(img.absolutePath().append("/IMAGES"));

    rawdataDir.setPath(img.absolutePath());
    rawdataDir.mkdir("RAW");
    rawdataDir.setPath(rawdataDir.absolutePath().append("/RAW"));

    raw.setPath(rawdataDir.absolutePath());
    raw.mkdir("LIST_MODE");
    raw.setPath(raw.absolutePath().append("/LIST_MODE"));

    corrected.setPath(rawdataDir.absolutePath());
    corrected.mkdir("CORRECTED");
    corrected.setPath(corrected.absolutePath().append("/CORRECTED"));

    castorDir.setPath(img.absolutePath());
    castorDir.mkdir("FINAL");
    castorDir.setPath( castorDir.absolutePath().append("/FINAL"));

    if(!m_calibrationMode){
        QDir fusion_cor = corrected;
        fusion_cor.mkdir("FUSION");
        fusion_cor.mkdir("XRAY");
        fusion_cor.setPath(fusion_cor.absolutePath().append("/FUSION"));

        QDir fusion_final = castorDir;
        fusion_final.mkdir("FUSION");
        fusion_final.mkdir("XRAY");
        fusion_final.setPath(fusion_final.absolutePath().append("/FUSION"));

        post.setPath(Storage.absolutePath());
        post.mkdir("POST_PROCESSING");
        post.setPath(post.absolutePath().append("/POST_PROCESSING"));

        QDir temp(post.absolutePath());
        postD = temp.absolutePath();
        post.setPath(post.absolutePath());
        post.mkdir("Report_Images");
        post.mkdir("DICOM");
        post.setPath(post.absolutePath().append("/Report_Images"));
    }
    rawD = raw.absolutePath();
    corrD = castorDir.absolutePath();
    qsCastorDir = castorDir.absolutePath();

    emit sendStudyDir(Storage.absolutePath());
    qDebug() << "Creating directories..." << endl;
}

void betaEye::stopAquisition()
{
    m_bCastorSummedFinished=false;
    emit onPressedStop();

    qDebug() << "Checkpoint 1" << endl;

    QString pathName = QStandardPaths::locate(QStandardPaths::DocumentsLocation,"VISUAL-eyes",QStandardPaths::LocateDirectory);
    QLocale locale(QLocale::English);
    QString date = locale.toString(QDateTime::currentDateTime(), "dd.MM.yyyy hh:mm:ss AP");

    qDebug() << "Checkpoint 2" << endl;

    ui->LE_finishTime->setText(date);
    ui->LE_finishTime->adjustSize();

    contrastPercentage = 0.0;
    m_dMaxCor  = 0.0;

    qDebug() << "Checkpoint 3" << endl;

    counter=0;
    ui->LE_currFrame->clear();
    frame_time=0;
    duration_time=0;

    ui->daq_progress->reset();
    ui->frame_progress->reset();

    qDebug() << "Checkpoint 4" << endl;

    qDebug() << " BUFFER size before stop  "  << BUFFER->size() << endl;

    ui->PB_stopDAQ->setEnabled(false);
    if (firstSummed2){
        QTime waitTime;
        waitTime = QTime::currentTime().addSecs(20);

        QMessageBox message;
        message.setIcon(QMessageBox::Information);
        message.setText("Reconstructing final image. \nPlease wait...");
        message.setStandardButtons(QMessageBox::NoButton);
        message.show();
        while(!m_bCastorSummedFinished){
            if(QTime::currentTime() >= waitTime)
                m_bCastorSummedFinished=true;

            QCoreApplication::processEvents(QEventLoop::AllEvents);
        }
        message.close();
    }


    ui->horizontalSlider->setEnabled(false);
    ui->hsContrastB->setEnabled(false);
    ui->opacitySlider->setEnabled(false);

    if(m_calibrationMode)
        betaEvaluation();

    emit saveStudyToDatabase(corrD,deviceOPerator,ui->LE_startTime->text(),ui->LE_finishTime->text());
    if(m_calibrationMode){
        calibrationInfoGenerator();
    }else{

        infoFileGenerator();
        saveDICOM();
    }

    qDebug() << " BUFFER size before stop  "  << BUFFER->size() << endl;
    //if(!BUFFER->empty())
    //    BUFFER->clear();

    if(m_calibrationMode){
        exitCalib->show();
    }else{
        nextStudy->show();
    }
    fastDynamic=false;
}

void betaEye::reset(){
    qDebug() << "Reseting matrices .. " << endl;
    QVector<qreal> rawMatrixA;
    rawMatrixA.fill(0);
    QVector<qreal> rawMatrixB;
    rawMatrixB.fill(0);
    QVector<qreal> corMatrix,sumMatrix;
    corMatrix.fill(0);
    sumMatrix.fill(0);
    QPolygonF spectrumHeadA;
    spectrumHeadA.fill(QPoint(0,0));
    QPolygonF spectrumHeadB;
    spectrumHeadB.fill(QPoint(0,0));

    contrastPercentageSummed = 0.0;
    m_dMaxCor = 0.0;


    plotsUpdate(rawMatrixA,rawMatrixB,corMatrix,spectrumHeadA,spectrumHeadB,0.0,0.0,0.0,0,0);
    updateSummedImgPlot(sumMatrix); // the update for the summed



    // clear the QLabels
    ui->LE_frameRate->clear();
    ui->LE_duration->clear();
    ui->LE_startTime->clear();
    ui->LE_finishTime->clear();
    ui->LE_counts->clear();
    ui->LE_currFrame->clear();

    // reset the process bars
    ui->frame_progress->reset();
    ui->daq_progress->reset();

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
    if(BUFFER!=nullptr){
        if(!BUFFER->empty())
            BUFFER->clear();
    }

    if(m_castorFrame!=nullptr){
        delete m_castorFrame;
    }

}


void betaEye::delete_qwt_plots_and_globals()
{
    delete nextStudy;
    delete exitCalib;
    delete PETsys;
    delete bed;
    delete sensor_temperature;
    delete opDialog;
    if(!m_calibrationMode){
        delete study_details;
        delete time;
    }
    qDebug() << "OK delete study details"<< endl;
//    delete BUFFER;
    delete rawMatrix1;
    delete rawMatrix2;
    delete liveMatrix;
    delete summedMatrix;

    ui->liveLayout->removeWidget(correctedPlot);
    ui->FrameLayout->removeWidget(summedCorrectedPlot);
    ui->Energy_Spectrum_Layout->removeWidget(energyPlot1);
    ui->Energy_Spectrum_Layout_2->removeWidget(energyPlot2);
    ui->RawLayout->removeWidget(RawPlot1);
    ui->RawLayout_2->removeWidget(RawPlot2);

    correctedPlot->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    summedCorrectedPlot->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    energyPlot1->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    energyPlot2->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    RawPlot1->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    RawPlot2->detachItems(QwtPlotItem::Rtti_PlotItem,false);

    delete correctedPlot;
    delete summedCorrectedPlot;
    delete energyPlot1;
    delete energyPlot2;
    delete RawPlot1;
    delete RawPlot2;
    if(m_calibrationMode)
        delete_qwt_validation_plots();

}


void betaEye::delete_qwt_validation_plots(){

    delete calibDetails;
    delete calibTime;
    /** Delete qwt validation plots
    */
    ui->rawHead1_layout->removeWidget(rawHead1);
    ui->rawHead2_layout->removeWidget(rawHead2);
    ui->correctedHead1_layout->removeWidget(correctedHead1);
    ui->correctedHead2_layout->removeWidget(correctedHead2);
    ui->resolutionHead1_layout->removeWidget(resolutionHead1);
    ui->resolutionHead2_layout->removeWidget(resolutionHead2);

    rawHead1->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    rawHead2->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    correctedHead1->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    correctedHead2->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    resolutionHead1->detachItems(QwtPlotItem::Rtti_PlotItem,false);
    resolutionHead2->detachItems(QwtPlotItem::Rtti_PlotItem,false);

    delete rawHead1;
    delete rawHead2;
    delete correctedHead1;
    delete correctedHead2;
    delete resolutionHead1;
    delete resolutionHead2;


}

void betaEye::updateSummedImgPlot( QVector<qreal> summmedCorMatrix)
{
    if(!m_summedImg.isEmpty())
        m_summedImg.clear();
    m_summedImg.resize(summmedCorMatrix.size());
    for(int i = 0; i <  summmedCorMatrix.size(); i++)
        m_summedImg[i] =  summmedCorMatrix[i];

    sliderSummedValueChanged( 0 );
    m_bCastorSummedFinished = true;
}


void betaEye::plotsUpdate(QVector<qreal> rawVMatrixA, QVector<qreal> rawVMatrixB, QVector<qreal> correctedMatrix, QPolygonF pointsA, QPolygonF pointsB, double maxRawA, double maxRawB,double maxCorrected,int maxEnA, int maxEnB)
{

//    qDebug() << "Update plots ... " << endl;
    rawMatrix1->setValueMatrix(rawVMatrixA,output_size_y_PET);
    rawMatrix1->setResampleMode(rawMatrix1->BilinearInterpolation);
    rawMatrix1->setInterval( Qt::ZAxis, QwtInterval( 0, maxRawA) );

    rawPlot1_spectrogram->setColorMap(cM);
    rawPlot1_spectrogram->setData(rawMatrix1);

    rawVMatrixA.clear();

    rawMatrix2->setValueMatrix(rawVMatrixB,output_size_y_PET);
    rawMatrix2->setResampleMode(rawMatrix2->BilinearInterpolation);
    rawMatrix2->setInterval( Qt::ZAxis, QwtInterval( 0, maxRawB) );

    rawPlot2_spectrogram->setColorMap(cM);
    rawPlot2_spectrogram->setData(rawMatrix2);

    rawVMatrixB.clear();

    energyPlot1->setAxisScale( QwtPlot::yLeft,0,maxEnA,0); //Scale the y-axis
    energyPlot1->plotLayout()->setAlignCanvasToScales(true);

    curve1->setSamples(pointsA);

    pointsA.clear();

    energyPlot2->setAxisScale( QwtPlot::yLeft,0,maxEnB,0); //Scale the y-axis
    energyPlot2->plotLayout()->setAlignCanvasToScales(true);

    curve2->setSamples(pointsB);

    pointsB.clear();

    energyPlot1->replot();
    energyPlot2->replot();

    RawPlot1->replot();
    RawPlot2->replot();

    if(ui->cb_fusion->isChecked()){
        addOpticalBackground();
    }else if(ui->cb_xray->isChecked()){
        addXrayBackground();
    }

    liveMatrix->setValueMatrix(correctedMatrix,image_SIZE_Y);
    liveMatrix->setResampleMode(liveMatrix->BilinearInterpolation);
    liveMatrix->setInterval( Qt::ZAxis, QwtInterval( 0, maxCorrected) );
    correctedPlot_spectrogram->setColorMap(cM);
    correctedPlot_spectrogram->setData(liveMatrix);
    correctedMatrix.clear();
    correctedPlot->replot();

    summedCorrectedPlot->replot();


}

void betaEye::saveDICOM()
{
    QSqlQuery q;
    QString marking, animal_name, date, startTime, gender, comments, nuclideUnit;
    QString injected_activity, weight;
    double pixel_size = 1.7;
    int imgX=0, imgY=0;
    QString pix = QString::number(pixel_size);
    bioemtec::dicomEncoder enc;
    QString dicomDir= post.path();
    dicomDir.replace("Report_Images","DICOM");
    QProcess createDicom;
    QString test="dcmodify -m \"(0028,0030)=1.7\\1.7\" -nb " ;
    std::string text=test.toStdString();
    QString exeCommands = QString::fromUtf8(text.c_str());


    QString load = "SELECT * FROM Study WHERE study_id = " + StudyID;

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
    m_stringList.push_back(marking.toStdString());
    m_stringList.push_back(animal_name.toStdString());
    m_stringList.push_back(date.remove("-").toStdString());
    QStringList spl = startTime.split(" ");
    QString h_only;

    for ( int i =0;i < spl.count(); i++ ) {
        if( i == 1 )
            h_only = spl.at(1);
    }
    m_stringList.push_back( h_only.toStdString() );
    m_stringList.push_back("");
    m_stringList.push_back(gender.toStdString());
    m_stringList.push_back(comments.toStdString());
    m_stringList.push_back(injected_activity.toStdString());
    m_stringList.push_back(weight.toStdString());
    m_stringList.push_back("PT");
    pix = QString::number(pixel_size);
    m_stringList.push_back(pix.toStdString());



    QStringList txtFilter;
    txtFilter << "*.txt";
    QStringList txtImages = castorDir.entryList(txtFilter,QDir::Files|QDir::NoSymLinks);
    QString txtFilePath = castorDir.path();
    txtImages.sort();


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
        enc.encoder(testDir.toStdString(), m_stringList, dimensions, inputImage );
        imgX=col_num;
        imgY=row_num;
        iMatrix.clear();
        byteArray.clear();

        createDicom.execute( exeCommands + " " + testDir);


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
    if (imgX==0){
         imgX=631;
         imgY=315;
     }

     cv::Mat opticalImg,xrayImg;
     std::string opFile = optDir.toStdString();
     optDir.remove("optical.png");
     optDir.append("Xray.png");
     std::string xrayFile = optDir.toStdString();
     optDir.remove("Xray.png");
     optDir.append("optical.png");
     opticalImg = cv::imread( opFile,cv::IMREAD_GRAYSCALE);
     xrayImg = cv::imread( xrayFile,cv::IMREAD_GRAYSCALE);


     QMap< QString, int > qmFlips;
     qmFlips.insert( "x", 0 );
     qmFlips.insert( "y", 1 );

     cv::rotate( opticalImg, opticalImg, cv::ROTATE_90_CLOCKWISE);
     cv::rotate( xrayImg, xrayImg, cv::ROTATE_90_CLOCKWISE);
     if ( m_pReadInputInfoBeta->getFlips().size() > 0){
        foreach ( QString flip,  m_pReadInputInfoBeta->getFlips() ){
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

     cv::resize(opticalImg, opticalImg, cv::Size(imgX, imgY), 0, 0, cv::INTER_CUBIC);
     cv::resize(xrayImg, xrayImg, cv::Size(imgX, imgY), 0, 0, cv::INTER_CUBIC);


     // in bytes


     size_t len = opticalImg.total()*opticalImg.elemSize();
     uint16_t *outOImg = new uint16_t[ len ];
     memcpy( outOImg, opticalImg.ptr< uint16_t>(), len );

     size_t lenX = xrayImg.total()*xrayImg.elemSize();
     uint16_t *outXImg = new uint16_t[ lenX ];
     memcpy( outXImg, xrayImg.ptr< uint16_t>(), lenX );

     std::vector<float> dimensions;
     dimensions.push_back( imgY);
     dimensions.push_back( imgX);
     enc.encoder( optOut.toStdString(), optList, dimensions, outOImg);
     enc.encoder( optXOut.toStdString(), optList, dimensions, outXImg);

     createDicom.execute( exeCommands + " " + optOut + " " + optXOut);

}

void betaEye::betaEvaluation() {

    // input txt file in the following format: ID1,En1,ID2,En2
    QString filenameIn = Storage.absolutePath()+"/RawValidationData.txt";
    std::ifstream InFile;
    InFile.open(filenameIn.toStdString());

    qDebug() << "Validation file path "<< filenameIn << endl;


    QTime waitTime1;
    bool enoughDataH1=false,enoughDataH2=false;
    bool validStatus=false;
    QPolygonF enHead1,enHead2, enRawHead1, enRawHead2, enResHead1, enResHead2;

    QProgressDialog validationProgress("System validation ...",nullptr,0,6,this);
    validationProgress.setMinimumDuration(0);

    waitTime1 = QTime::currentTime().addMSecs(500);
    while( QTime::currentTime() < waitTime1 ){
      QApplication::processEvents();
    }
    validationProgress.setValue(0);

    //Variables Declaration

    const int NumberMaximumID = 1152;
    long int countEvents=0;
    int ID1,ID2=0; ///////////####### initialize IDs
    float En1,En2,En1_RAW,En2_RAW=0;



    float photopeak_Head1_h1[NumberMaximumID],photopeak_Head2_h2[NumberMaximumID];
    float sigma_Head1_h1[NumberMaximumID],sigma_Head2_h2[NumberMaximumID];
    float FWHM_Head1_h1[NumberMaximumID],FWHM_Head2_h2[NumberMaximumID];
    float entries_Head1_h1[NumberMaximumID],entries_Head2_h2[NumberMaximumID];

    //Histograms Declaration

    TH1F** h1 = new TH1F*[NumberMaximumID];
    TH1F** h2 = new TH1F*[NumberMaximumID];

    TH1F *Head1_Av_En_Res = new TH1F("histogram","Average Energy Res Head 1",30, 10, 50);
    TH1F *Head2_Av_En_Res = new TH1F("histogram","Average Energy Res Head 2",30, 10, 50);


    int maxEnergy=2000;
    int rawHist1[maxEnergy],rawHist2[maxEnergy],corHist1[maxEnergy],corHist2[maxEnergy];
    int i=0;
    int maxRawH1=0, maxRawH2=0, maxCorH1=0, maxCorH2=0;
    while(i<maxEnergy){
        rawHist1[i]=0;
        rawHist2[i]=0;
        corHist1[i]=0;
        corHist2[i]=0;
        i++;
    }

    waitTime1 = QTime::currentTime().addMSecs(500);
    while( QTime::currentTime() < waitTime1 ){
      QApplication::processEvents();
    }
    validationProgress.setValue(1);



    for (int i=0; i < NumberMaximumID; i++)
    {
        h1[i] = new TH1F(TString::Format("h1_%d", i), "Head 1", 200, 0.,2000);
        h2[i] = new TH1F(TString::Format("h2_%d", i), "Head 2", 200, 0.,2000);
    }
    waitTime1 = QTime::currentTime().addMSecs(100);
    while( QTime::currentTime() < waitTime1 ){
      QApplication::processEvents();
    }
    validationProgress.setValue(2);

    double maxCorEnergyH1=0.0,maxCorEnergyH2=0.0;
    while(InFile) //read txt file and store energy in histograms
    {
    if (InFile >> ID1 >> En1 >> En1_RAW >> ID2 >> En2 >> En2_RAW) ///////###### add an if so not to crash if txt is empty (probably needs revision at some point)
         {
            countEvents++;
            h1[ID1]->Fill(En1);
            h2[ID2]->Fill(En2);
            rawHist1[int(En1_RAW)]++;
            rawHist2[int(En2_RAW)]++;
            corHist1[int(En1)]++;
            corHist2[int(En2)]++;
            if (En1>maxCorEnergyH1)
                maxCorEnergyH1=En1;
            if (En2>maxCorEnergyH2)
                maxCorEnergyH2=En2;
//            std::cout << corHist1[int(En1)] << " "<<corHist2[int(En2)] << " "<<rawHist1[int(En1_RAW)]<< " " <<rawHist2[int(En2_RAW)]<< std::endl;

        }
    }
    std::cout << "Total Events recorded: " << countEvents <<std::endl;


    validationProgress.setValue(3);
    int det_elements_processed_head2=1;
    int det_elements_processed_head1=1;
    double maxEnResHead1=0.0, maxEnResHead2=0.0;

    for (int i=0; i < NumberMaximumID; i++)
    {

                entries_Head1_h1[i]= h1[i]->GetEntries();
                if (entries_Head1_h1[i]>500)
                {
                    h1[i] ->Smooth();
                    photopeak_Head1_h1[i] = veyesUtils::searchPhotopeak(h1[i]);
                    if (photopeak_Head1_h1[i]> 400 && photopeak_Head1_h1[i]< 600) //////////////add an extra if to avoid bad fitting that might lead to crash
                    {
                         h1[i]->Fit("gaus", "Q", "Q",photopeak_Head1_h1[i]- 100.0, photopeak_Head1_h1[i] + 100.0); //fit the photopeak //Carefull
                         sigma_Head1_h1[i]=h1[i]->GetFunction("gaus")->GetParameter(2);
                         FWHM_Head1_h1[i]=100*2.35*sigma_Head1_h1[i]/photopeak_Head1_h1[i];
                         Head1_Av_En_Res->Fill(FWHM_Head1_h1[i]);
                         det_elements_processed_head1++;
                         enoughDataH1=true;

                    }
                }


                entries_Head2_h2[i]= h2[i]->GetEntries();
                if (entries_Head2_h2[i]>500)
                {
                    //enoughDataH2=true; ////## update this condition in the next if...
                    h2[i] ->Smooth();
                    photopeak_Head2_h2[i] = veyesUtils::searchPhotopeak(h2[i]);
                    if (photopeak_Head2_h2[i]> 400 && photopeak_Head2_h2[i]< 600) //////////////add an extra if to avoid bad fitting that might lead to crash
                    {
                         h2[i]->Fit("gaus", "Q", "Q",photopeak_Head2_h2[i]- 100.0, photopeak_Head2_h2[i] + 100.0); //fit the photopeak //Carefull
                         sigma_Head2_h2[i]=h2[i]->GetFunction("gaus")->GetParameter(2);
                         FWHM_Head2_h2[i]=100*2.35*sigma_Head2_h2[i]/photopeak_Head2_h2[i];
                         Head2_Av_En_Res->Fill(FWHM_Head2_h2[i]);
                         det_elements_processed_head2++;
                         enoughDataH2=true;
                   }
                }
    }
    waitTime1 = QTime::currentTime().addMSecs(100);
    while( QTime::currentTime() < waitTime1 ){
      QApplication::processEvents();
    }
    validationProgress.setValue(5);


    double cfov=0.0;
    int maxBinsH1=0, maxBinsH2=0;
    double resHeadA=0.0, resHeadB=0.0;
//    double factorH1=0.0,factorH2=0.0;
    if(enoughDataH1){
        Head1_Av_En_Res->Smooth();
        maxBinsH1=Head1_Av_En_Res->GetNbinsX();
//        factorH1=maxCorEnergyH1/maxBinsH1;
        i=0;
        while(i < maxBinsH1){
                enResHead1 << QPointF(Head1_Av_En_Res->GetBin(i)*1.33+10, Head1_Av_En_Res->GetBinContent(i));
                std::cout << Head2_Av_En_Res->GetBin(i) << " "<<  Head2_Av_En_Res->GetBinContent(i)<<std::endl;
                if(Head1_Av_En_Res->GetBinContent(i) > maxEnResHead1)
                    maxEnResHead1 = Head1_Av_En_Res->GetBinContent(i);

                i++;
        }
        resHeadA=Head1_Av_En_Res->GetMean();
    }
    if(enoughDataH2){
        Head2_Av_En_Res->Smooth();
        maxBinsH2=Head2_Av_En_Res->GetNbinsX();
//        factorH2=maxCorEnergyH2/maxBinsH2;
        i=0;
        while(i < maxBinsH2){
                enResHead2 << QPointF(Head2_Av_En_Res->GetBin(i)*1.33+10, Head2_Av_En_Res->GetBinContent(i));
                std::cout << Head2_Av_En_Res->GetBin(i) <<" " <<Head2_Av_En_Res->GetBinContent(i)<<std::endl;
                if(Head2_Av_En_Res->GetBinContent(i) > maxEnResHead2)
                    maxEnResHead2 = Head2_Av_En_Res->GetBinContent(i);

                i++;
        }
        cfov =Head2_Av_En_Res->GetMean();
        resHeadB=cfov;
    }



    if (det_elements_processed_head1>100 && det_elements_processed_head2>100 && Head1_Av_En_Res->GetMean()>9 && Head1_Av_En_Res->GetMean()<26 && Head2_Av_En_Res->GetMean()>9 && Head2_Av_En_Res->GetMean()<26)
    {
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

        if (corHist1[i] > maxCorH1)
            maxCorH1=corHist1[i];
        if ( corHist2[i] > maxCorH2)
            maxCorH2= corHist2[i];
        if (rawHist1[i] > maxRawH1)
            maxRawH1=rawHist1[i];
        if (rawHist2[i] > maxRawH2)
            maxRawH2=rawHist2[i];

        enHead1 << QPointF(i,corHist1[i]);
        enHead2 << QPointF(i,  corHist2[i]);
        enRawHead1 << QPointF(i,rawHist1[i]);
        enRawHead2 << QPointF(i, rawHist2[i]);
        i++;

    }


    ui->lb_detElemHead1->setText(QString::number(det_elements_processed_head1)+" / 882");
    ui->lb_detElemHead2->setText(QString::number(det_elements_processed_head2)+" / 882");
    ui->lb_cfov->setText(QString::number(cfov)+" %");


    rawHead1->setAxisScale( QwtPlot::yLeft,0,maxRawH1,0); //Scale the y-axis
    rawHead1->plotLayout()->setAlignCanvasToScales(true);
    rawCurve1->setSamples(enRawHead1);
    rawHead1->replot();

    rawHead2->setAxisScale( QwtPlot::yLeft,0,maxRawH2,0); //Scale the y-axis
    rawHead2->plotLayout()->setAlignCanvasToScales(true);
    rawCurve2->setSamples(enRawHead2);
    rawHead2->replot();


    correctedHead1->setAxisScale( QwtPlot::yLeft,0,maxCorH1,0); //Scale the y-axis
    correctedHead1->plotLayout()->setAlignCanvasToScales(true);
    correctedCurve1->setSamples(enHead1);
    correctedHead1->replot();

    correctedHead2->setAxisScale( QwtPlot::yLeft,0,maxCorH2,0); //Scale the y-axis
    correctedHead2->plotLayout()->setAlignCanvasToScales(true);
    correctedCurve2->setSamples(enHead2);
    correctedHead2->replot();

    resolutionHead1->setAxisScale( QwtPlot::yLeft,0,int(maxEnResHead1),0); //Scale the y-axis
    resolutionHead1->plotLayout()->setAlignCanvasToScales(true);
    resolutionCurve1->setSamples(enResHead1);
    resolutionHead1->replot();

    resolutionHead2->setAxisScale( QwtPlot::yLeft,0,int(maxEnResHead2),0); //Scale the y-axis
    resolutionHead2->plotLayout()->setAlignCanvasToScales(true);
    resolutionCurve2->setSamples(enResHead2);
    resolutionHead2->replot();

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

    pdf_report(resHeadA,resHeadB);

    /*for(int i=0; i<NumberMaximumID;i++){
        delete[] h1[i];
        delete[] h2[i];
    }
    delete [] h1;
    delete [] h2;*/
    return;
}


void betaEye::pdf_report(double resA, double resB)
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


    QString radionuclide = "Radionuclide: ";
    radionuclide += ui->LE_radioNuclide->text() +"\n";
    painter.drawText(QRect(3200,begin_text_h+950,3000,200), Qt::AlignLeft, radionuclide);

    QString activity = "Activity: ";
    activity +=ui->LE_injectActivity->text() +"\n";
    painter.drawText(QRect(3200,begin_text_h+1250,3000,200), Qt::AlignLeft, activity);

    QString duration = "Experiment duration: ";
    duration += ui->LE_duration->text()+"\n";
    painter.drawText(QRect(3200,begin_text_h+1550,3000,200), Qt::AlignLeft, duration);


    QString system = "System: ";
    system += m_pReadInputInfoBeta->getSystemName()+"\n";
    painter.drawText(QRect(6400,begin_text_h+950,3000,200), Qt::AlignLeft, system);


    painter.drawText(QRect(0,begin_text_h+2000,8917,200), Qt::AlignLeft, "Head A");
    painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(0,begin_text_h+2250,8917,begin_text_h+2260);



    QPixmap rawHead1_img=rawHead1->grab();
    QPixmap corHead1_img=correctedHead1->grab();
    QPixmap resHead1_img=resolutionHead1->grab();
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 6));
    painter.drawText(QRect(0,begin_text_h+2450,1500,200),Qt::AlignLeft,"Raw energy (counts/KeV)");
    painter.drawText(QRect(2200,begin_text_h+2450,1500,200),Qt::AlignLeft,"Corrected energy(counts/KeV)");
    painter.drawText(QRect(4400,begin_text_h+2450,1500,200),Qt::AlignLeft,"Energy resolution");

    painter.drawPixmap(QRect(0,begin_text_h+2600,2000,2000),rawHead1_img);
    painter.drawPixmap(QRect(2200,begin_text_h+2600,2000,2000),corHead1_img);
    painter.drawPixmap(QRect(4400,begin_text_h+2600,2000,2000),resHead1_img);
    painter.setFont(QFont("Times", 8));
    QString elementHeadA="Detector elements processed: "+ui->lb_detElemHead1->text();
    painter.drawText(QRect(6600,begin_text_h+2600,2000,2000),elementHeadA);
    QString resHeadA="Energy resolution: "+QString::number(resA)+" %";
    painter.drawText(QRect(6600,begin_text_h+3000,2000,2000),resHeadA);


    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 10));
    painter.drawText(QRect(0,begin_text_h+4700,8917,200), Qt::AlignLeft, "Head B");
    painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(0,begin_text_h+4950,8917,begin_text_h+4890);


    QPixmap rawHead2_img=rawHead2->grab();
    QPixmap corHead2_img=correctedHead2->grab();
    QPixmap resHead2_img=resolutionHead2->grab();
    painter.setFont(QFont("Times", 6));
    painter.drawText(QRect(0,begin_text_h+5150,1500,200),Qt::AlignLeft,"Raw energy (counts/KeV)");
    painter.drawText(QRect(2200,begin_text_h+5150,1500,200),Qt::AlignLeft,"Corrected energy(counts/KeV)");
    painter.drawText(QRect(4400,begin_text_h+5150,1500,200),Qt::AlignLeft,"Energy resolution");

    painter.drawPixmap(QRect(0,begin_text_h+5300,2000,2000),rawHead2_img);
    painter.drawPixmap(QRect(2200,begin_text_h+5300,2000,2000),corHead2_img);
    painter.drawPixmap(QRect(4400,begin_text_h+5300,2000,2000),resHead2_img);
    QString elementHeadB="Detector elements processed: "+ui->lb_detElemHead2->text();
    painter.setFont(QFont("Times", 8));
    painter.drawText(QRect(6600,begin_text_h+5300,2000,2000),elementHeadB);

    QString resHeadB="Energy resolution: "+QString::number(resB)+" %";
    painter.drawText(QRect(6600,begin_text_h+5700,2000,2000),resHeadB);


    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 10));
    painter.drawText(QRect(0,begin_text_h+7500,8917,200), Qt::AlignLeft, "General");
    painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(0,begin_text_h+7750,8917,begin_text_h+7760);

    QString resolution="Energy resolution CFOV: " +ui->lb_cfov->text();
    painter.setFont(QFont("Times", 8));
    painter.drawText(QRect(0,begin_text_h+7900,8917,2000),resolution);


    painter.setFont(QFont("Times", 10));
    painter.drawText(QRect(0,begin_text_h+8200,8917,200), Qt::AlignLeft, "Validation status");
    painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(0,begin_text_h+8450,8917,begin_text_h+8460);


    QString status=ui->lb_status->text();
    painter.setFont(QFont("Times", 8));
    painter.drawText(QRect(0,begin_text_h+8600,2000,200),status);
    QPixmap pixmap_status= *ui->statusIcon->pixmap();
    pixmap_status.scaled(500,500);
    painter.drawPixmap(QRect(0,begin_text_h+8800,500,500),pixmap_status);
    painter.end();


}
