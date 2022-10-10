#include "headers/mergedialog.h"
#include "ui_mergedialog.h"
#include <QProgressDialog>

mergeDialog::mergeDialog(ReadInputInfo* inputInfo, QWidget *parent , QString frameDirectory, QString opticalPath, QString xrayPath, QString postProcPath, QString destinationPath, QString id, bool isBeta) :
    QDialog(parent),
    ui(new Ui::mergeDialog),
    m_readInputInfo( inputInfo )
{
    ui->setupUi(this);

    m_FrameDirectory = frameDirectory;
    m_OpticalPath = opticalPath;
    m_xrayPath = xrayPath;
    m_DestDirectory = destinationPath;
    m_postProcessDir=postProcPath;
    m_study = id;
    m_isBeta = isBeta;



    allFramesSelected=true;


    QDir frameDir(m_FrameDirectory);
    QStringList filter;
    filter<<"*.txt";
    frameDir.setNameFilters(filter);
    m_allFramesList =frameDir.entryList(filter,QDir::Files|QDir::NoSymLinks);
    m_frameNameList =m_allFramesList;


    foreach (QString currentFile, m_frameNameList) {
        if ( currentFile.contains("FinalSummed.txt") || currentFile.contains("SummedFinalframe.txt")){
            m_frameNameList.removeAll(currentFile);
            m_remainFrames.append(currentFile);
        }
        else if ( !currentFile.contains("Finalframe") )
            m_frameNameList.removeAll(currentFile);
    }


    int conversionFactor = m_frameNameList.size();

    QList<int> items;
    for (int i = 1; i < conversionFactor ; i++) {
         if(conversionFactor%i==0){
             items.append(i);
         }
    }
    std::sort(items.begin(), items.end());
    foreach(int item, items){
         ui->cB_convFactor->addItem(QString::number(item));
    }


//    ui->cB_convFactor->setDisabled(true);
//    ui->lE_destFile->setText("Finalframe001.txt");
//    ui->lE_destFile->setDisabled(true);
//    ui->pB_merge->setDisabled(true);
//    ui->pB_ok->setDisabled(true);

//    m_mergeFrameCount = 1;
//    connect(ui->cB_convFactor,SIGNAL(currentIndexChanged(int)),this,SLOT(cB_convFactor_currentIndexChanged(int)),Qt::UniqueConnection);
}

mergeDialog::~mergeDialog()
{
    delete ui;
}
/*
void mergeDialog::setFrameDir( QString frameDirectory)
{
    m_FrameDirectory = frameDirectory;
}

void mergeDialog::setPathTOptical( QString opticalPath )
{
    m_OpticalPath = opticalPath;
}

void mergeDialog::setPathToXray( QString xrayPath )
{
    m_xrayPath = xrayPath;
}

void mergeDialog::setDest_directory( QString destinationPath, QString id)
{
    m_study = id;
    m_DestDirectory = destinationPath;
}

void mergeDialog::setPostProcPath(QString postProcPath){
    m_postProcessDir = postProcPath;
}
*/
void mergeDialog::saveInfoFile()
{
    QSqlQuery q;
    QString deviceid, date,startTime,finTime,comments,duration,frame,exp_tU,frame_tU;
    QString name, animal_name, breed, species, age, weight, gender, r_pharma, volume;
    QString activity, injection_date,path_id, isFastDynamic;
    QString Operator, collimator, radionuclide, project, injected_activity, marking, fileDirectory;
    QDateTime injTconv;
    int radioUnit, nuclideId;
    QString string="SELECT * FROM Study JOIN Collimator ON Collimator.collimator_id LIKE Study.collimator_id JOIN radionuclide ON radionuclide.nuclide_id = Study.nuclide_id WHERE study_id ="+m_study;
    //QString string = "SELECT * FROM Study WHERE Study.study_id= " + m_study;
    q.exec(string);
    QString filename = m_DestDirectory+"/StudyInfo.txt";
    QFile file;
    file.setFileName(filename);

    QTextStream out(&file);
    if(file.open(QIODevice::WriteOnly))
    {

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
            nuclideId = q.value("nuclide_id").toInt();
            exp_tU = q.value("timeUnit_exp").toString();
            frame_tU = q.value("timeUnit_frame").toString();
            project = q.value("project").toString();
            injected_activity = q.value("injected_activity").toString();
            comments = q.value("comments").toString();
            marking = q.value("marking").toString();
            fileDirectory = q.value("fileDirectory").toString();
            radioUnit = q.value("radioUnit").toInt();
            isFastDynamic =q.value("fastDynamic").toString();
            radionuclide=q.value("nuclide_name").toString();
            collimator=q.value("coll_name").toString();

            out << "ID: " << m_study << "\n";
            out << "Device: " << deviceid << endl;
            out << "Image Flip: " << m_readInputInfo->getFlips().join(",").trimmed() << endl;
            out << "Name: " << name << endl;
            out << "Project: " << project << endl;
            out << "Animal name: " << animal_name << endl;
            out << "Breed: " << breed << endl;
            out << "Species: " << species << endl;
            out << "Age: " << age << endl;
            out << "Marking: " << marking << endl;
            out << "Weight: " << weight << endl;
            out << "Gender: " << gender << endl;
            if (collimator!="NA")
                out << "Collimator: " << collimator << endl;
            out << "Radionuclide: " << radionuclide << endl;
            spectIsotope chosenIsotope=m_readInputInfo->getSpectIsotope(collimator,radionuclide);
            out << "Limits: " << chosenIsotope.getLimit1() << " " << chosenIsotope.getLimit2() << endl;
            out << "Activity parameters a: " <<chosenIsotope.getA1() << " " << chosenIsotope.getA2() << " " << chosenIsotope.getA3() << endl;
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
            if ( radioUnit == 0)
                out << "Radio unit: " << "MBq" << endl;
            else
                out << "Radio unit: " << "uCi" << endl;

            out << "Date: " << date << "\n";
            out << "Start Time: " << startTime << "\n";
            out << "Finish Time: " << finTime << "\n";
            out << "Fast Dynamic: " << "No" << endl;

            if(allFramesSelected){
                float nFactor=m_frameNameList.size()/ui->cB_convFactor->currentText().toFloat();
                float frameFloat=frame.toFloat()*nFactor;
                int frameTime=  static_cast<int>(frameFloat);
                out << "Experiment Duration: " << duration << " " << exp_tU << "\n";
                out << "Frame Duration: " << QString::number(frameTime) << " " << frame_tU <<"\n\n";
            }
            else{
                out << "Experiment Duration: " <<  duration << " " << exp_tU  << "\n";
                QString output="Frame Duration: ";
                for (int i = 1; i < m_frameTimes.size(); ++i) {
                    int frameTime=frame.toInt()*m_frameTimes[i].toInt();
                    output+="frame"+QString::number(i)+": "+QString::number(frameTime)+" ";
                }
                out << output << frame_tU <<"\n\n";

            }
            out << "Comments: " << comments ;
        }
        else {
            QString infoFilePath = m_FrameDirectory;
            if(infoFilePath.contains("/IMAGES/FINAL")){
                infoFilePath.remove("/IMAGES/FINAL");
                infoFilePath.append("/StudyInfo.txt");
            }
            QFile studyInfoFile(infoFilePath);

            if(!studyInfoFile.open(QIODevice::ReadOnly))
                QMessageBox::information(0,"error",studyInfoFile.errorString());



            int fastD=0;
            float frameDuration;
            QString frameUnit;
            QTextStream in(&studyInfoFile);
            while(!in.atEnd()) {
                QString line = in.readLine();
                if ( line.isEmpty() ) continue;


                QString simpleLine = line.simplified();
                QStringList fields = simpleLine.split(":");

                if ( fields[ 0 ].compare("Fast Dynamic") == 0 ){
                    out << line << "\n";
                    if (fields[ 1 ].trimmed()=="Yes")
                        fastD =1;
                }



                if ( fields[ 0 ].compare("Frame Duration") == 0 ){
                    if ( fields.size() >= 2 && !fields[ 1 ].isEmpty() ){
                        QString trimFields;
                        QStringList ValUnit;
                        if (fastD==1){
                            QString temp  = fields[2].trimmed();
                            QStringList tempL= temp.split(",");
                            trimFields=tempL[0].remove("sec");
                            frameDuration=trimFields.toFloat();
                            frameUnit ="sec";
                            out << line <<"\n\n";
                        }else {
                            trimFields = fields[ 1 ].trimmed();
                            ValUnit = trimFields.split(" ");
                            QString trimmedValUnit = ValUnit[0].trimmed();
                            frameDuration = trimmedValUnit.toFloat();
                            frameUnit = ValUnit[1].trimmed();

                            float nFactor=m_frameNameList.size()/ui->cB_convFactor->currentText().toFloat();
                            float frameFloat=frameDuration*nFactor;
                            int frameTime=  static_cast<int>(frameFloat);
                            out << "Frame Duration: " << QString::number(frameTime) << " " << frameUnit <<"\n\n";
                       }


                    }
                }
                else {
                    out << line << "\n";
                }


            }
            studyInfoFile.close();

        }
    }
    file.close();
}

void  mergeDialog::on_pB_ok_clicked(){
    int count = m_mergeFrameCount;
    QTime waitTime1;

    QProgressDialog fileLoadProgress("Merging frames ...",nullptr,0,5,this);
    fileLoadProgress.setMinimumDuration(0);
    waitTime1 = QTime::currentTime().addSecs(1);
    while( QTime::currentTime() < waitTime1 ){
         QApplication::processEvents();
    }
    fileLoadProgress.setValue(0);

    waitTime1 = QTime::currentTime().addSecs(1);
    while( QTime::currentTime() < waitTime1 ){
    QApplication::processEvents();
    }
    fileLoadProgress.setValue(1);

    waitTime1 = QTime::currentTime().addMSecs(500);
    while( QTime::currentTime() < waitTime1 ){
      QApplication::processEvents();
    }
    fileLoadProgress.setValue(2);
    if (allFramesSelected){

        addFrames();
        waitTime1 = QTime::currentTime().addMSecs(500);
        while( QTime::currentTime() < waitTime1 ){
          QApplication::processEvents();
        }
        fileLoadProgress.setValue(3);
        saveSumDICOM();
        waitTime1 = QTime::currentTime().addMSecs(500);
        while( QTime::currentTime() < waitTime1 ){
          QApplication::processEvents();
        }
        fileLoadProgress.setValue(4);

    }
    QString dicomSrcDir = m_FrameDirectory;
    dicomSrcDir.remove("/IMAGES/FINAL");
    dicomSrcDir.append("/POST_PROCESSING/DICOM");
    QString xraySrcPath = m_FrameDirectory + "/XRAY";
    QString fusionSrcPath = m_FrameDirectory + "/FUSION";
    QString xrayDstPath = m_DestDirectory + "/XRAY";
    QString fusionDstPath = m_DestDirectory + "/FUSION";
    foreach(QString frameFile,m_remainFrames){
        if (frameFile.contains("FinalSummed.txt") || frameFile.contains("SummedFinalframe.txt") ){
            int lastFrameNew;
            if (allFramesSelected){
                lastFrameNew= ui->cB_convFactor->currentText().toInt() + 1;
            }else{
                lastFrameNew= count;
            }
            QFile::copy(m_FrameDirectory + "/" + frameFile,m_DestDirectory + "/" +frameFile);
            QFile::copy(dicomSrcDir + "/frame"+ QString::number(m_allFramesList.size()) +".dcm",m_postProcessDir + "/DICOM/frame" + QString::number(lastFrameNew) +".dcm");
            if (m_isBeta){
               QFile::copy(fusionSrcPath + "/FinalOpticalSummed.png",fusionDstPath + "/FinalOpticalSummed.png");
               QFile::copy(xraySrcPath + "/FinalXraySummed.png",xrayDstPath +"/FinalXraySummed.png");
            }else {
               QFile::copy(fusionSrcPath + "/finalOpticalSummedImg.png",fusionDstPath + "/finalOpticalSummedImg.png");
               QFile::copy(xraySrcPath + "/finalXraySummedImg.png",xrayDstPath + "/finalXraySummedImg.png");
            }

        }
        else {
            QString newNumber = QString("%1").arg(count, 3, 10, QChar('0'));
            QFile::copy(m_FrameDirectory + "/" + frameFile,m_DestDirectory + "/Finalframe" + newNumber +".txt");
            QString frameNumber=frameFile;
            frameNumber.remove("Finalframe");
            frameNumber.remove(".txt");
            QString frameIt=frameNumber;
            QString frameItNew=newNumber;
            frameIt.remove(QRegExp("^[0]*"));
            m_frameTimes.insert(count,"1");
            QFile::copy(dicomSrcDir + "/frame"+ frameIt +".dcm",m_postProcessDir + "/DICOM/frame" + frameItNew.remove(QRegExp("^[0]*")) +".dcm");
            if (m_isBeta){
               QFile::copy(fusionSrcPath + "/FinalframeOptical"+ frameNumber +".png",fusionDstPath + "/FinalframeOptical" + newNumber +".png");
               QFile::copy(xraySrcPath + "/FinalframeXray"+ frameNumber +".png",xrayDstPath + "/FinalframeXray" + newNumber +".png");
            }else {
               QFile::copy(fusionSrcPath + "/fussedOpticalImg"+ frameNumber +".png",fusionDstPath + "/fussedOpticalImg" + newNumber +".png");
               QFile::copy(xraySrcPath + "/fussedXrayImg"+ frameNumber +".png",xrayDstPath + "/fussedXrayImg" + newNumber +".png");
           }
           count+=1;
        }
    }
    fileLoadProgress.setValue(5);
    saveInfoFile();
    m_allFramesList.clear();
    m_remainFrames.clear();
    m_frameNameList.clear();
    m_frameNames.clear();
    m_frameTimes.clear();
    QMessageBox msgBox;
    msgBox.setText("Merged frames are saved in " + m_DestDirectory);
    msgBox.exec();
    this->close();
}


void  mergeDialog::on_pB_cancel_clicked(){

    ui->cB_convFactor->clear();
    allFramesSelected=false;
    m_allFramesList.clear();
    m_remainFrames.clear();
    m_frameNameList.clear();
    m_frameNames.clear();
    QDir tempDir1(m_DestDirectory);
    tempDir1.removeRecursively();
    QDir tempDir2(m_postProcessDir);
    tempDir2.removeRecursively();
    this->close();
}




void mergeDialog::saveSumDICOM(){



    QSqlQuery q;
    QString marking, animal_name, date, startTime, gender, comments, nuclideUnit;
    QString injected_activity, weight;
    double pixel_size = 1.7;
    QString pix = QString::number(pixel_size);
    bioemtec::dicomEncoder enc;
    QString dicomDir= m_postProcessDir + "/DICOM";

    QProcess createDicom;
    QString test="dcmodify -m \"(0028,0030)=1.7\\1.7\" -nb " ;
    std::string text=test.toStdString();
    QString exeCommands = QString::fromUtf8(text.c_str());

    QString load ="SELECT * FROM Study WHERE study_id = "+ m_study;

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
    int iFrame=0;
    if (ui->cB_convFactor->currentText()=="1"){
        cv::Mat iMatImg = m_sumFrames[0];
        uint16_t inputImage[ iMatImg.rows * iMatImg.cols ];
        double max=0.0,min=0.0;
        cv::minMaxLoc(iMatImg, &min, &max);
        if (max > 65535.0){
            for ( int m = 0; m < iMatImg.rows; m++)
                for(int j = 0; j < iMatImg.cols; j++)
                    inputImage[ m*iMatImg.cols + j ] = static_cast<uint16_t>(iMatImg.at<float>(m,j)*(65535.0/max));

        }
        else{
            for ( int m = 0; m < iMatImg.rows; m++)
                for(int j = 0; j < iMatImg.cols; j++)
                    inputImage[ m*iMatImg.cols + j ] = static_cast<uint16_t>(iMatImg.at<float>(m,j));
        }


        QString filename = m_givenFilename;
        if (filename.contains(".txt") && filename.contains("Finalframe")){
            filename.replace(".txt",".dcm");
            filename.remove("Finalframe");
            filename.remove( QRegExp("^[0]*") );
            filename.push_front("frame");
        }
        QString testDir = dicomDir+ "/" +filename;
        std::vector<float> dimensions;
        dimensions.push_back(iMatImg.rows);
        dimensions.push_back(iMatImg.cols);
        enc.encoder(testDir.toStdString(), stringList, dimensions, inputImage );

        createDicom.execute( exeCommands + " " + testDir);


    }else{
        foreach(cv::Mat iMatImg, m_sumFrames){
            uint16_t inputImage[ iMatImg.rows * iMatImg.cols ];

            double max=0.0,min=0.0;
            cv::minMaxLoc(iMatImg, &min, &max);
            if (max > 65535.0){
                for ( int m = 0; m < iMatImg.rows; m++)
                    for(int j = 0; j < iMatImg.cols; j++)
                        inputImage[ m*iMatImg.cols + j ] = static_cast<uint16_t>(iMatImg.at<float>(m,j)*(65535.0/max));

            }
            else{
                for ( int m = 0; m < iMatImg.rows; m++)
                    for(int j = 0; j < iMatImg.cols; j++)
                        inputImage[ m*iMatImg.cols + j ] = static_cast<uint16_t>(iMatImg.at<float>(m,j));
            }


            iFrame+=1;

            QString testDir = dicomDir+"/frame"+QString::number(iFrame)+".dcm";
            std::vector<float> dimensions;
            dimensions.push_back(iMatImg.rows);
            dimensions.push_back(iMatImg.cols);
            enc.encoder(testDir.toStdString(), stringList, dimensions, inputImage );

            createDicom.execute( exeCommands + " " + testDir);
        }


    }





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


     cv::Mat opticaImg,xrayImg;
     std::string opFile = m_OpticalPath.toStdString();
     std::string xFile = m_xrayPath.toStdString();
     opticaImg = cv::imread( opFile,cv::IMREAD_GRAYSCALE);
     xrayImg = cv::imread( xFile,cv::IMREAD_GRAYSCALE);
     QMap< QString, int > qmFlips;
     qmFlips.insert( "x", 0 );
     qmFlips.insert( "y", 1 );

     cv::rotate( opticaImg, opticaImg, cv::ROTATE_90_CLOCKWISE);
     cv::rotate( xrayImg, xrayImg, cv::ROTATE_90_CLOCKWISE);
     if( m_readInputInfo->getFlips().size() >0){
          foreach ( QString flip,   m_readInputInfo->getFlips() ){
              if(flip!=""){
                    cv::flip(opticaImg, opticaImg, qmFlips[ flip ] );
                    cv::flip(xrayImg, xrayImg, qmFlips[ flip ] );
              }
          }
     }


     cv::normalize(opticaImg, opticaImg, 0, 255, cv::NORM_MINMAX);
     cv::normalize(xrayImg, xrayImg, 0, 255, cv::NORM_MINMAX);
     opticaImg.convertTo(opticaImg, CV_16UC1);
     xrayImg.convertTo(xrayImg, CV_16UC1);
     cv::resize(opticaImg, opticaImg, cv::Size(cols, rows), 0, 0, cv::INTER_CUBIC);
     cv::resize(xrayImg, xrayImg, cv::Size(cols, rows), 0, 0, cv::INTER_CUBIC);
     QString optOut = dicomDir+"/optical.dcm";
     QString xOut = dicomDir+"/xray.dcm";

     size_t len = opticaImg.total()*opticaImg.elemSize(); // in bytes
     uint16_t *outImg = new uint16_t[ len ];
     memcpy( outImg, opticaImg.ptr< uint16_t>(), len );

     size_t lenX = xrayImg.total()*xrayImg.elemSize();
     uint16_t *outXImg = new uint16_t[ lenX ];
     memcpy( outXImg, xrayImg.ptr< uint16_t>(), lenX );

     std::vector<float> dimensions;
     dimensions.push_back( rows);
     dimensions.push_back( cols);
     enc.encoder( optOut.toStdString(), optList, dimensions, outImg);
     enc.encoder( xOut.toStdString(), optList, dimensions, outXImg);
     createDicom.execute( exeCommands + " " + optOut);
     createDicom.execute( exeCommands + " " + xOut);

}



void mergeDialog::addFrames(){


    if (m_isBeta){
        rows = 315;
        cols = 631;
        xfusion = 567;
        yfusion = 283;
    }
    else{
        rows = 145;
        cols = 291;
        xfusion = 580;
        yfusion = 290;

    }
    QString lutPath= QCoreApplication::applicationDirPath();
    lutPath.append("/colormap/royal.lut");
    std::string lutFilename = lutPath.toStdString();
    std::string opFile = m_OpticalPath.toStdString();
    std::string xFile = m_xrayPath.toStdString();

    cv::Mat optical_img = cv::imread(opFile,cv::IMREAD_GRAYSCALE);
    cv::Mat xray_img=cv::imread(xFile,cv::IMREAD_GRAYSCALE);
    cv::rotate(optical_img,optical_img, cv::ROTATE_90_CLOCKWISE);
    cv::rotate(xray_img,xray_img, cv::ROTATE_90_CLOCKWISE);

    QMap< QString, int > qmFlips;
    qmFlips.insert( "x", 0 );
    qmFlips.insert( "y", 1 );

    if ( m_readInputInfo->getFlips().size() > 0){
        foreach ( QString flip, m_readInputInfo->getFlips() ){
            if(flip!=""){
                cv::flip(optical_img,optical_img, qmFlips[ flip.trimmed() ] );
                cv::flip(xray_img,xray_img, qmFlips[ flip.trimmed() ] );
            }
        }
    }

    QString destDirectory = m_DestDirectory;
    QString fusionDirPath = m_DestDirectory + "/FUSION";
    QString dicomDirPath = m_postProcessDir + "/DICOM";
    QString xrayDirPath = m_DestDirectory + "/XRAY";

    QDir rawDir( m_DestDirectory );
    if ( !rawDir.exists() )
        rawDir.mkdir( destDirectory );

    QDir fusionDir(fusionDirPath);
    if (!fusionDir.exists()){
        fusionDir.mkdir(fusionDirPath);
    }
    QDir dicomDir(dicomDirPath);
    if (!dicomDir.exists()){
        dicomDir.mkdir(dicomDirPath);
    }
    QDir xrayDir(xrayDirPath);
    if (!xrayDir.exists()){
        xrayDir.mkdir(xrayDirPath);
    }

    foreach(QString frame, m_frameNameList){
        cv::Mat rawMat;
        rawMat = cv::Mat::zeros(rows, cols, CV_32F);
        QFile File(m_FrameDirectory + "/" + frame);
        QByteArray byteArray;
        //  File.open(QFile::ReadOnly);
        QTextStream textStream(&byteArray,QIODevice::ReadOnly);
        if( File.exists() && File.open( QIODevice::ReadOnly ) ){
            byteArray= File.readAll();
            File.close();

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

            for(int i =0; i< col_num;i++){
                list_item.append(fields.at(i));
            }

            row_num++;
        }

        for(int i=0;i<row_num;i++){
            for(int j=0;j<col_num;j++){
                rawMat.at<float>(i, j) = c.toFloat(list_item.at(cnt),&ok);
                cnt++;
            }
        }


        m_rawFrames.append(rawMat);

    }

    if (ui->cB_convFactor->currentText()=="1"){

        cv::Mat sumMat= cv::Mat::zeros(rows, cols, CV_32F);;
        cv::add(m_rawFrames[0],m_rawFrames[1],sumMat);

        if (m_rawFrames.size()>2){
            for(int i=2; i<m_rawFrames.size();i++){
                cv::add(sumMat,m_rawFrames[i],sumMat);
            }
        }

        std::FILE *file = 0;
        m_givenFilename = "Finalframe001.txt";
        QString total =m_DestDirectory + "/" + m_givenFilename;

        std::string str = total.toStdString();
        file = std::fopen(str.c_str(),"w");
        if ( file ){
               for (int i = 0; i < sumMat.rows; i++){
                   for (int j = 0; j < sumMat.cols; j++){
                       fprintf(file, "%f ", sumMat.at<float> (i, j));
                   }
                   fprintf(file, "\n");
               }
               std::fclose( file );
        }
        m_sumFrames.append(sumMat);
        double min, max;
        cv::minMaxLoc(sumMat, &min, &max);
        cv::Mat matOut(yfusion,xfusion, CV_32F);
        cv::resize(sumMat,matOut,matOut.size(),10,10,cv::INTER_CUBIC);
        cv::Mat matOutFinal(yfusion,xfusion, CV_32F);
        cv::threshold(matOut,matOutFinal,0, max, cv::THRESH_TOZERO);
        QString fusionFile= m_givenFilename;
        QString xrayFile= m_givenFilename;
        if(m_isBeta){
            fusionFile.replace("Finalframe","FinalframeOptical");
            xrayFile.replace("Finalframe","FinalframeXray");
        }else{
            fusionFile.replace("Finalframe","fussedOpticalImg");
            xrayFile.replace("Finalframe","fussedXrayImg");
        }
        fusionFile.replace(".txt",".png");
        xrayFile.replace(".txt",".png");
        cv::Mat fussed = imageFusion::fusion(optical_img, matOutFinal, lutFilename);
        cv::Mat xray = imageFusion::fusion(xray_img, matOutFinal, lutFilename);
        QString fusionFilename = "/"+ fusionFile;
        QString fDir = fusionDirPath;
        fDir.append(fusionFilename);
        std::string fussedFname = fDir.toStdString();
        cv::imwrite(fussedFname, fussed);

        QString xrayFilename = "/"+ xrayFile;
        QString xDir = xrayDirPath;
        xDir.append(xrayFilename);
        std::string xrayFname = xDir.toStdString();
        cv::imwrite(xrayFname, xray);

    }
    else{
        int nFactor=m_frameNameList.size()/ui->cB_convFactor->currentText().toInt();
        int frameCounter = 0;
        for(int i=0; i < m_rawFrames.size(); i+=nFactor){
            cv::Mat sumMat  = cv::Mat::zeros(rows, cols, CV_32F);;
            cv::add(m_rawFrames[i],m_rawFrames[i+1],sumMat);


            if (nFactor > 2){
                for(int j=i+2; j<i+nFactor;j++){
                    cv::add(sumMat,m_rawFrames[j],sumMat);
                }
            }
            frameCounter++;
            m_sumFrames.append(sumMat);

            std::FILE *file = 0;
            QString number = QString("%1").arg(frameCounter, 3, 10, QChar('0'));
            QString filename = "/Finalframe" + number + ".txt";
            QString total =m_DestDirectory + "/" +filename;

            std::string str = total.toStdString();
            file = std::fopen(str.c_str(),"w");
            if ( file ){
                   for (int i = 0; i < sumMat.rows; i++){
                       for (int j = 0; j < sumMat.cols; j++){
                           fprintf(file, "%f ", sumMat.at<float> (i, j));
                       }
                       fprintf(file, "\n");
                   }
                   std::fclose( file );
            }
            double min, max;
            cv::minMaxLoc(sumMat, &min, &max);
            cv::Mat matOut(yfusion,xfusion, CV_32F);
            cv::resize(sumMat,matOut,matOut.size(),10,10,cv::INTER_CUBIC);
            cv::Mat matOutFinal(yfusion,xfusion, CV_32F);
            cv::threshold(matOut,matOutFinal,0, max, cv::THRESH_TOZERO);

            cv::Mat fussed = imageFusion::fusion(optical_img, matOutFinal, lutFilename);
            QString fusionFilename;
            if(m_isBeta){
                fusionFilename = "/FinalframeOptical" + number + ".png";
            }else{
                fusionFilename = "/fussedOpticalImg" + number + ".png";
            }
            QString fDir = fusionDirPath;
            fDir.append(fusionFilename);
            std::string fussedFname = fDir.toStdString();
            cv::imwrite(fussedFname, fussed);


            cv::Mat xray = imageFusion::fusion(xray_img, matOutFinal, lutFilename);
            QString xrayFilename;
            if(m_isBeta){
                xrayFilename = "/FinalframeXray" + number + ".png";
            }else{
                xrayFilename = "/fussedXrayImg" + number + ".png";
            }
            QString xDir = xrayDirPath;
            xDir.append(xrayFilename);
            std::string xrayFname = xDir.toStdString();
            cv::imwrite(xrayFname, xray);
            sumMat.release();
        }

    }
}

void mergeDialog::closeEvent(QCloseEvent * event) {
    ui->cB_convFactor->clear();
//    ui->lE_destFile->setText("Finalframe001.txt");
//    ui->lE_frameList->clear();
    allFramesSelected=false;
    m_allFramesList.clear();
    m_remainFrames.clear();
    m_frameNameList.clear();
    m_frameNames.clear();
    this->close();
}
