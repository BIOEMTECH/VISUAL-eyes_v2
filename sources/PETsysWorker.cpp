#include "headers/PETsysWorker.h"
#include <QDebug>


const int PETsysWorker:: SIZE_X_PET = 512;
const int PETsysWorker:: SIZE_Y_PET = 1024;

const int PETsysWorker:: image_SIZE_X = 72;
const int PETsysWorker:: image_SIZE_Y = 144;

const int PETsysWorker:: CRYSTALS_X = 24;
const int PETsysWorker:: CRYSTALS_Y = 48;

const int PETsysWorker:: NO_CHANNELS = 1024;
const int PETsysWorker:: MAX_ENERGY = 8192;




PETsysWorker::PETsysWorker(ReadInputInfo * inputInfo, boost::circular_buffer<EventMsg> * circularBuffer, QString rawDirectory,QString corDirectory,QString nucName,
                           QDateTime qTime1, double activity, QString radioUnit, int exp_duration, int frame_time, castor * castor_frame, bool calibrationMode, bool validationOn, petIsotope studyIsotope){

    qRegisterMetaType<QVector<qreal>>("QVector<qreal>");
    qRegisterMetaType<QPolygonF>("QPolygonF");

    m_calibrationMode=calibrationMode;
    m_validationOn=validationOn;
    m_corDirectory=corDirectory;
    m_rawDirectory=rawDirectory;
    m_qsNuclideName = nucName;

    // This is the time in sec from the injection until the user hits play. This is t1 in the decay formula for the first time.
    m_dt1 = qTime1.secsTo( QDateTime().currentDateTime() );

    // This is the actuall time from the injection until the user hits play. This is used to compute t2 in the decay formula for the first time.
    m_qTime1 = qTime1;

    m_activity = activity;
    m_frameTime = frame_time;
    m_frameStop = exp_duration/frame_time;
    m_activityUnit = radioUnit;


    m_petIsotope=studyIsotope;
    m_readInputInfoPET=inputInfo;
    m_circularBuffer=circularBuffer;
    m_frameCounter=0;
    m_img_scale_factor=4.375;

    m_acceptance = std::tan(m_readInputInfoPET->getAcceptanceAngle() * 0.01745329);
    m_head_separation_distance = 65;
    m_projPix2mm = 0.766666667;

    if(m_calibrationMode){
        m_validationFilePath=rawDirectory;
        m_validationFilePath.remove("/IMAGES/RAW/LIST_MODE");
        m_validationFilePath.append("/RawValidationData.txt");
    }

    m_dlambda=m_petIsotope.getLambda();
    m_dpreExp=m_petIsotope.getPreExp();

    /*
    if ( m_qsNuclideName.trimmed().compare("F-18(110 min)") == 0 ){
        m_dlambda = m_readInputInfoPET->getF18_lambda(); //sec
        m_dpreExp = m_readInputInfoPET->getF18_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Ga-68(68.3 min)") == 0 ){
        m_dlambda = m_readInputInfoPET->getGa68_lambda(); //sec
        m_dpreExp = m_readInputInfoPET->getGa68_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("C-11(20.4 min)") == 0 ){
        m_dlambda = m_readInputInfoPET->getC11_lambda(); //sec
        m_dpreExp = m_readInputInfoPET->getC11_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("N-13(10 min)") == 0 ){
        m_dlambda = m_readInputInfoPET->getN13_lambda(); //sec
        m_dpreExp = m_readInputInfoPET->getN13_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("O-15(2.03 min)") == 0 ){
        m_dlambda = m_readInputInfoPET->getO15_lambda(); //sec
        m_dpreExp = m_readInputInfoPET->getO15_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Cu-62(9.73 min)") == 0 ) {
        m_dlambda = m_readInputInfoPET->getCu62_lambda(); //sec
        m_dpreExp = m_readInputInfoPET->getCu62_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Cu-64(12.7 h)") == 0 ) {
        m_dlambda = m_readInputInfoPET->getCu64_lambda(); //sec
        m_dpreExp = m_readInputInfoPET->getCu64_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Zr-89(74.8 h)") == 0 ) {
        m_dlambda = m_readInputInfoPET->getZr89_lambda(); //sec
        m_dpreExp = m_readInputInfoPET->getZr89_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Rb-82(1.25 min)") == 0 ) {
        m_dlambda = m_readInputInfoPET->getRb82_lambda(); //sec
        m_dpreExp = m_readInputInfoPET->getRb82_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("I-124(4.2 days)") == 0 ) {
        m_dlambda = m_readInputInfoPET->getI124_lambda(); //sec
        m_dpreExp = m_readInputInfoPET->getI124_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Br-76(16.3 h)") == 0 ) {
        m_dlambda = m_readInputInfoPET->getBr76_lambda(); //sec
        m_dpreExp = m_readInputInfoPET->getBr76_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Tb-152(17.5 h)") == 0 ) {
        m_dlambda = m_readInputInfoPET->getTb152_lambda(); //sec
        m_dpreExp = m_readInputInfoPET->getTb152_preExp();
    }
    */
    m_castorFrame=castor_frame;
}

PETsysWorker::~PETsysWorker(){
    qDebug() << "~PETsysWorker() "<<endl;
    clear_matrices();
    memory_deallocation();
}


void PETsysWorker::initialise()
{

    // A is always in uCi
    double A = 0.0;
    if ( m_activityUnit == "MBq")
        A = 27.027*m_activity*(1.-exp(-m_dlambda*m_frameTime))/(exp(m_dlambda*m_dt1)*m_dlambda*m_frameTime);
    else
        A = m_activity*(1.-exp(-m_dlambda*m_frameTime))/(exp(m_dlambda*m_dt1)*m_dlambda*m_frameTime);

    m_doDecay = true;
    if ( A >= m_readInputInfoPET->getNuclide_lim3() )
        m_doDecay = false;


    m_castorFrame->setTime1( m_dt1 );
    m_castorFrame->setdt( m_frameTime );
    m_castorFrame->setActivity( m_activity );
    m_castorFrame->setNuclideName( m_qsNuclideName );
    m_castorFrame->doDecay( m_doDecay );


    memory_allocation();
    clear_matrices();
    loadCalibrationFiles();
}

void PETsysWorker::loadCalibrationFiles()
{
    QString calibration_file_path =  QDir::currentPath();
    QString gridHeadA,gridHeadB,energyA,energyB;

    calibration_file_path.append("/PET_calibration_files/Nuclide/");

    gridHeadA = calibration_file_path;
    gridHeadB = calibration_file_path;
    energyA = calibration_file_path;
    energyB = calibration_file_path;


    gridHeadA.append( m_readInputInfoPET->getGridAFileName() );
    gridHeadB.append( m_readInputInfoPET->getGridBFileName() );
    energyA.append( m_readInputInfoPET->getEnergiesAFileName() );
    energyB.append( m_readInputInfoPET->getEnergiesBFileName() );


    FILE *file_head_A_lut_grid	= std::fopen(gridHeadA.toStdString().c_str(),"r");	//calibration file
    FILE *file_head_B_lut_grid  = std::fopen(gridHeadB.toStdString().c_str(),"r");	//calibration file
    FILE *head_A_energy			= std::fopen(energyA.toStdString().c_str(),"r");	//calibration file
    FILE *head_B_energy			= std::fopen(energyB.toStdString().c_str(),"r");	//calibration file

    qDebug() << "test before calib" << endl;
    for (int m1 = 0; m1 < SIZE_X_PET; m1++) {
        for (int m2 = 0; m2 < SIZE_Y_PET; m2++){
            std::fscanf(file_head_A_lut_grid, "%d ",&grid_lut_head_A[m1][m2]);
            std::fscanf(file_head_B_lut_grid, "%d ",&grid_lut_head_B[m1][m2]);
        }
    }


    for (int m1 = 0; m1 < CRYSTALS_X; m1++){
        for (int m2 = 0; m2 < CRYSTALS_Y; m2++){
            std::fscanf(head_A_energy, "%d ",&energy_lut_head_A[m1][m2]);
            std::fscanf(head_B_energy, "%d ",&energy_lut_head_B[m1][m2]);
        }
    }
     qDebug() << "test after calib" << endl;

    QString opticalImgDir = m_corDirectory;
    opticalImgDir.remove("/IMAGES/FINAL");
    std::string xrayFile =  opticalImgDir.toStdString() + "/Xray.png";
    std::string opticalFile =  opticalImgDir.toStdString() + "/optical.png";

    optical_img=cv::imread(opticalFile, cv::IMREAD_GRAYSCALE);
    xray_img=cv::imread(xrayFile,cv::IMREAD_GRAYSCALE);


    QMap< QString, int > qmFlips;
    qmFlips.insert( "x", 0 );
    qmFlips.insert( "y", 1 );

    cv::rotate(optical_img,optical_img,cv::ROTATE_90_CLOCKWISE);
    cv::rotate(xray_img,xray_img,cv::ROTATE_90_CLOCKWISE);
    if(m_readInputInfoPET->getFlips().size() >0){
        foreach ( QString flip, m_readInputInfoPET->getFlips()){
            if(flip!=""){
                cv::flip(optical_img, optical_img, qmFlips[ flip ] );
                cv::flip(xray_img, xray_img, qmFlips[ flip ] );
            }
       }
    }

    m_castorFrame->setFrameStop(m_frameStop);
    m_castorFrame->setOpticalImg(optical_img);
    m_castorFrame->setXrayImg(xray_img);

    m_fusionDirectory = m_corDirectory;
    m_fusionDirectory.append("/FUSION");

    lutFilename = QDir::currentPath().append("/colormap/royal.lut").toStdString();
}

void PETsysWorker::stopToFrame(){
    m_frameCounter++;
    m_dt1+=m_frameTime;

    print_frame(m_frameCounter);
    reset_live();
}

void PETsysWorker::stopImaging(){
    print_sum();
    emit stopProcessing();
}

void PETsysWorker::frameReconstruction(){
    QString number=QString("%1").arg(m_frameCounter,3,10,QChar('0'));
    QString rawFileName="Rawframe"+number+".bdat";
    QString rawframePath=m_rawDirectory;
    rawframePath.append("/Raw"+number);
    QString rawSummedPath=m_rawDirectory;
    rawSummedPath.append("/Summed");
    m_qsCastorFilename=rawFileName;

    m_castorFrame->setTime1(m_dt1);
    m_castorFrame->setRawFilePath(rawframePath);
    m_castorFrame->setSumRawFilePath(rawSummedPath);
    emit castor_frame(m_qsCastorFilename);

    qDebug() << "FILE FOR CASTOR "<<  m_qsCastorFilename <<  endl;
    if (m_frameStop==m_frameCounter){
        stopImaging();
    }
}


void PETsysWorker::print_sum(){
    QString rawDir =  m_rawDirectory;
    rawDir.remove("/LIST_MODE");
    rawDir.append("/CORRECTED");

    float decay_correction= veyesUtils::mf_decayCorrection(m_readInputInfoPET->useExpDecay(), m_doDecay,m_activity,m_activityUnit,
    m_dlambda,m_dt1,m_frameTime,m_dtInjectionTime.secsTo(QDateTime().currentDateTime()), m_dpreExp, m_readInputInfoPET->getNuclide_lim3());


    cv::Mat summed_image=veyesUtils::array2D_to_cvmat<int>(summed_matrix,image_SIZE_X,image_SIZE_Y,decay_correction);
    cv::Mat resized_img = veyesUtils::image_conversion(summed_image,m_img_scale_factor,m_img_scale_factor,image_SIZE_X,image_SIZE_Y);
    QString txtImg_filename = rawDir+ "/SummedImg.txt";
    veyesUtils::write_txt_image(txtImg_filename.toStdString(),resized_img,int(m_img_scale_factor*image_SIZE_X),int(m_img_scale_factor* image_SIZE_Y));
    if(!m_calibrationMode){
        ///Save fussed images only for imaging studies
        cv::Mat fussedSummed = imageFusion::fusion(optical_img,resized_img,lutFilename);
        cv::Mat xraySummed = imageFusion::fusion(xray_img,resized_img,lutFilename);

        QString fusionOut = "/fussedOpticalSummedImg.png";
        QString xrayOut = "/fussedXraySummedImg.png";
        std::string xrayFussed = rawDir.toStdString()+ "/XRAY"+ xrayOut.toStdString();
        std::string fussed = rawDir.toStdString()+ "/FUSION"+ fusionOut.toStdString();
        cv::imwrite(fussed,fussedSummed);
        cv::imwrite(xrayFussed,xraySummed);
        fussedSummed.release();
        xraySummed.release();
    }
    summed_image.release();
    resized_img.release();
}



void PETsysWorker::print_frame(int frame){

     QString dest = m_rawDirectory;
     dest.remove("/LIST_MODE");
     dest.append("/CORRECTED");
     QString number = QString("%1").arg(frame, 3, 10, QChar('0'));
     QString filename = "/CorrectedframePET"+number+".txt";//+QString::number(ID)+"_"+QDate::currentDate().toString();


     float decay_correction= veyesUtils::mf_decayCorrection(m_readInputInfoPET->useExpDecay(), m_doDecay,m_activity,m_activityUnit,
     m_dlambda,m_dt1,m_frameTime,m_dtInjectionTime.secsTo(QDateTime().currentDateTime()), m_dpreExp, m_readInputInfoPET->getNuclide_lim3());

     cv::Mat live_image=veyesUtils::array2D_to_cvmat<int>(live_matrix,image_SIZE_X,image_SIZE_Y,decay_correction);
     cv::Mat resized_img = veyesUtils::image_conversion(live_image,m_img_scale_factor,m_img_scale_factor,image_SIZE_X,image_SIZE_Y);

     QString txtImg_frame = dest + filename;
     if (live_matrix){
         veyesUtils::write_txt_image(txtImg_frame.toStdString(),resized_img,int(m_img_scale_factor*image_SIZE_X),int(m_img_scale_factor* image_SIZE_Y));
     }

     if(!m_calibrationMode){
         ///Save fused images only for imaging studies
         cv::Mat fussedCorrected = imageFusion::fusion(optical_img,resized_img,lutFilename);
         cv::Mat fussedXrayCorrected = imageFusion::fusion(xray_img,resized_img,lutFilename);

         QString fusionOut = "/fussedOpticalImg"+ number + ".png";
         QString xrayOut = "/fussedXrayImg"+ number + ".png";
         std::string xrayFussed = dest.toStdString() + "/XRAY" + xrayOut.toStdString();
         QString fDir = dest + "/FUSION";
         fDir.append(fusionOut);
         std::string fussed = fDir.toStdString();
         cv::imwrite(fussed,fussedCorrected);
         cv::imwrite(xrayFussed,fussedXrayCorrected);
         fussedCorrected.release();
         fussedXrayCorrected.release();
     }

     live_image.release();
     resized_img.release();


}

void PETsysWorker::receiveContrast(double contrast )
{
    QMutexLocker locker(&mutex);
    m_livecontrast =contrast;
}

void PETsysWorker::imagingData()
{
    double maxRawA=0.0,maxRawB=0.0;
    int maxEnA=0,maxEnB= 0;
    double maxCor = 0.0;//,maxCorSummed = 0.0;



    for (int i=0; i<SIZE_X_PET; i++){
        for(int j=0; j<SIZE_Y_PET; j++){
            if(double(raw_head_A[i][j]) > maxRawA)
                maxRawA=double(raw_head_A[i][j]);
            rawMatrixA.append(double(raw_head_A[i][j]));
        }
    }

    for (int i=0; i<SIZE_X_PET; i++) {
        for(int j=0; j<SIZE_Y_PET; j++) {
            if(double(raw_head_B[i][j]) > double(maxRawB))
                maxRawB=double(raw_head_B[i][j]);
            rawMatrixB.append(double(raw_head_B[i][j]));
        }
    }

    for(int i=0; i< MAX_ENERGY; i++){
        if(energy_head_A[i] > maxEnA)
            maxEnA = energy_head_A[i];

        if(energy_head_B[i] > maxEnB)
            maxEnB = energy_head_B[i];

        pointsA << QPointF(i, energy_head_A[i]);
        pointsB << QPointF(i, energy_head_B[i]);
    }


    for (int i=0; i<image_SIZE_X; i++) {
        for(int j=0;j<image_SIZE_Y;j++) {
            if(double(live_matrix[i][j])  > maxCor)
                maxCor=double(live_matrix[i][j]);

            correctedMatrix.append(double(live_matrix[i][j]));
        }
    }

    if(m_livecontrast != 0){
        double contrast_percentage = maxCor*m_livecontrast;
        maxCor = maxCor-contrast_percentage;
    }

    emit sendImagingDataProgress(rawMatrixA,rawMatrixB,correctedMatrix,pointsA, pointsB, maxRawA, maxRawB,maxCor, maxEnA, maxEnB);

    clear_qvector(rawMatrixA);
    clear_qvector(rawMatrixB);
    clear_qvector(correctedMatrix);
    clear_qpolygon(pointsA);
    clear_qpolygon(pointsB);

}

void PETsysWorker::run()
{
    PET_online();
}


void PETsysWorker::PET_online(){
    if(!m_circularBuffer->empty()){
        bool upDown = false, leftRight = false, flipflop = false;
        int energy_A=0,energy_B=0;
        int head_A_x = 0, head_A_y = 0, head_B_x = 0, head_B_y = 0;


        EventMsg newMsg=m_circularBuffer->front();
        m_circularBuffer->pop_front();

        head_A_y = int(10*newMsg.x_cog2);
        head_A_x = int(10*newMsg.y_cog2);
        head_B_y = int(10*newMsg.x_cog1);
        head_B_x = int(10*newMsg.y_cog1);
        energy_A = int(10*newMsg.energy2);
        energy_B = int(10*newMsg.energy1);

        rawEvent newRawEvent{newMsg.x_cog1,newMsg.y_cog1,newMsg.energy1,newMsg.x_cog2,newMsg.y_cog2,newMsg.energy2};

        QString number = QString("%1").arg(m_frameCounter+1, 3, 10, QChar('0'));
        QString filename = "/Rawframe"+number+".bdat";
        QString destinationPath = m_rawDirectory;

        destinationPath.append("/Raw" + number);
        QDir destinationDir( destinationPath );
        if ( !destinationDir.exists() )
            destinationDir.mkdir( destinationPath );

        destinationPath.append(filename);

        rawFrameOut = fopen(destinationPath.toStdString().c_str(), "a+b");
        fwrite(&newRawEvent, sizeof(newRawEvent), 1,rawFrameOut);
        fclose(rawFrameOut);

        if (head_A_x >= 0 && head_A_y >= 0 && head_B_x >= 0 && head_B_y >= 0 && head_A_x < SIZE_X_PET && head_A_y
                < SIZE_Y_PET && head_B_x < SIZE_X_PET && head_B_y < SIZE_Y_PET) {

            int cor_energy_A=0,cor_energy_B=0;
            short int crystal_A_x=0, crystal_A_y=0, crystal_B_x=0, crystal_B_y= 0;


            std::tie(crystal_A_x,crystal_A_y)=calculate_crystal_coordinates(grid_lut_head_A,head_A_x,head_A_y,upDown,leftRight,flipflop);
            std::tie(crystal_B_x,crystal_B_y)=calculate_crystal_coordinates(grid_lut_head_B,head_B_x,head_B_y,upDown,leftRight,flipflop);

            // Correct (scale) energy

            cor_energy_A=scale_energy(energy_lut_head_A,energy_A,crystal_A_x,crystal_A_y);
            cor_energy_B=scale_energy(energy_lut_head_B,energy_B,crystal_B_x,crystal_B_y);

            if (cor_energy_A > 0 && cor_energy_A < 2048)
               energy_head_A[cor_energy_A]++;

            if (cor_energy_B > 0 && cor_energy_B < 2048)
               energy_head_B[cor_energy_B]++;

            if (energy_A > 0 && energy_A < 2048 && energy_B > 0 && energy_B < 2048) {
                raw_head_A[head_A_x][head_A_y] ++;
                raw_head_B[head_B_x][head_B_y] ++;
            }



            if(m_calibrationMode){
                 validation_file.open(m_validationFilePath.toStdString(), std::ios_base::app);
                 if(energy_A > 0 && energy_A <= 3000 && cor_energy_A <= 3000 &&  energy_B > 0 && energy_B <= 3000 && cor_energy_B <= 3000 && cor_energy_A > 0 && cor_energy_B > 0){

                         int crystal_IDA = crystal_A_x * CRYSTALS_Y + crystal_A_y;
                         int crystal_IDB = crystal_B_x * CRYSTALS_Y + crystal_B_y;
                         validation_file << crystal_IDA <<" "<< cor_energy_A  <<" " << energy_A << " " << crystal_IDB << " " << cor_energy_B  <<" " << energy_B << std::endl;
                 }
                 validation_file.close();
            }

            crystal_A_x = rand() % 3 + (3*crystal_A_x);
            crystal_A_y = rand() % 3 + (3*crystal_A_y);
            crystal_B_x = rand() % 3 + (3*crystal_B_x);
            crystal_B_y = rand() % 3 + (3*crystal_B_y);

            if (cor_energy_B >= m_readInputInfoPET->getEnergyWindowLow() && cor_energy_B <= m_readInputInfoPET->getEnergyWindowUp() && cor_energy_A >= m_readInputInfoPET->getEnergyWindowLow() && cor_energy_A <= m_readInputInfoPET->getEnergyWindowUp()) {
                // The energy of the event is inside the window.
                // Find the displacement of the detectors for small images.
                double delta_x = crystal_A_x-crystal_B_x;
                double delta_y = crystal_A_y-crystal_B_y;
                double displacement = sqrt(pow(delta_x,2) + pow(delta_y,2));
                double tang = (displacement * m_projPix2mm) / (m_head_separation_distance);

                // Comprare to the acceptance angle
                if (tang <= m_acceptance) {
                    double position_x = double(crystal_A_x) - (delta_x/2.0);
                    double position_y = double(crystal_A_y) - (delta_y/2.0);

                    live_matrix[int(round(position_x))][int(round(position_y))]++;
                    summed_matrix[int(round(position_x))][int(round(position_y))]++;
                }
            }



       }

    }

}


void PETsysWorker::memory_allocation()
{

    /** Calibration matrices
    **/

    grid_lut_head_A=veyesUtils::allocate_2D_array<int>(SIZE_X_PET,SIZE_Y_PET);
    grid_lut_head_B=veyesUtils::allocate_2D_array<int>(SIZE_X_PET,SIZE_Y_PET);

    energy_lut_head_A=veyesUtils::allocate_2D_array<int>(CRYSTALS_X,CRYSTALS_Y);
    energy_lut_head_B=veyesUtils::allocate_2D_array<int>(CRYSTALS_X,CRYSTALS_Y);

    /** Raw head matrix
    **/
    raw_head_A=veyesUtils::allocate_2D_array<int>(SIZE_X_PET,SIZE_Y_PET);
    raw_head_B=veyesUtils::allocate_2D_array<int>(SIZE_X_PET,SIZE_Y_PET);

    /** Energy spectrums
    **/
    energy_head_A=new int[MAX_ENERGY];
    energy_head_B=new int[MAX_ENERGY];

    /** Live imaging
    **/
    live_matrix=veyesUtils::allocate_2D_array<int>(image_SIZE_X,image_SIZE_Y);
    summed_matrix=veyesUtils::allocate_2D_array<int>(image_SIZE_X,image_SIZE_Y);

}

void PETsysWorker::clear_matrices(){
    /** Initialize calibration matrices
    **/
    veyesUtils::clear_2D_array<int>(grid_lut_head_A,SIZE_X_PET,SIZE_Y_PET);
    veyesUtils::clear_2D_array<int>(grid_lut_head_B,SIZE_X_PET,SIZE_Y_PET);

    veyesUtils::clear_2D_array<int>(energy_lut_head_A,CRYSTALS_X,CRYSTALS_Y);
    veyesUtils::clear_2D_array<int>(energy_lut_head_B,CRYSTALS_X,CRYSTALS_Y);

    /** Raw head matrix
    **/
    veyesUtils::clear_2D_array<int>(raw_head_A,SIZE_X_PET,SIZE_Y_PET);
    veyesUtils::clear_2D_array<int>(raw_head_B,SIZE_X_PET,SIZE_Y_PET);

    /** Energy spectrums
    **/
    veyesUtils::clear_1D_array<int>(energy_head_A,MAX_ENERGY);
    veyesUtils::clear_1D_array<int>(energy_head_B,MAX_ENERGY);

    /** Live imaging
    **/
    veyesUtils::clear_2D_array<int>(live_matrix,image_SIZE_X,image_SIZE_Y);
    veyesUtils::clear_2D_array<int>(summed_matrix,image_SIZE_X,image_SIZE_Y);

    clear_qvector(rawMatrixA);
    clear_qvector(rawMatrixB);
    clear_qvector(correctedMatrix);
    clear_qpolygon(pointsA);
    clear_qpolygon(pointsB);

}

void PETsysWorker::reset_live(){

    veyesUtils::clear_2D_array<int>(live_matrix,image_SIZE_X,image_SIZE_Y);
    clear_qvector(correctedMatrix);
    qDebug() <<"Reset matrix" <<endl;
}





void PETsysWorker::memory_deallocation()
{

    veyesUtils::delete_2D_array<int>(grid_lut_head_A,SIZE_X_PET);
    veyesUtils::delete_2D_array<int>(grid_lut_head_B,SIZE_X_PET);
    veyesUtils::delete_2D_array<int>(energy_lut_head_A,CRYSTALS_X);
    veyesUtils::delete_2D_array<int>(energy_lut_head_B,CRYSTALS_X);
    veyesUtils::delete_2D_array<int>(raw_head_A,SIZE_X_PET);
    veyesUtils::delete_2D_array<int>(raw_head_B,SIZE_X_PET);
    veyesUtils::delete_2D_array<int>(live_matrix,image_SIZE_X);
    veyesUtils::delete_2D_array<int>(summed_matrix,image_SIZE_X);

    delete [] energy_head_A;
    delete [] energy_head_B;
}

void PETsysWorker::clear_qvector(QVector<qreal> &image_vector) {
    if(!image_vector.isEmpty())
        image_vector.clear();
}

void PETsysWorker::clear_qpolygon(QPolygonF &image_polygon) {
    if(!image_polygon.isEmpty())
        image_polygon.clear();
}

std::tuple<int,int>  PETsysWorker::calculate_crystal_coordinates(int ** crystal_map,int head_x, int head_y, bool &updown, bool &leftright, bool &flipflop){

    static const int gridHorizLine = -1;
    static const int gridVertLine  = -2;
    static const int gridCrossLine = -3;

    int temp=0, addX=0, addY=0;
    int currentXPixel=0, currentYPixel=0;
    int crystal_x=0, crystal_y=0;

    temp = crystal_map[head_x][head_y];
    currentXPixel = head_x;
    currentYPixel = head_y;

    while(temp < 0)
    {
           switch (temp)
           {

               case gridHorizLine:
                   addX = (updown ^= true) ? -1 : 1;
                   addY = 0;
                   break;
               case gridVertLine:
                   addY = (leftright ^= true) ? -1 : 1;
                   addX = 0;
                   break;
               case gridCrossLine:
                   if (flipflop)
                   {

                       addX = (updown ^= true) ? -1: 1;
                       addY = (leftright ^= false) ? -1 : 1;
                   }
                   else if(!flipflop)
                   {

                       addX = (updown ^= false) ? -1 : 1;
                       addY = (leftright ^= false) ? -1 : 1;
                   }
                   flipflop= !flipflop;
                   break;
            }

            currentYPixel =+addY;
            currentXPixel =+addX;

            if (currentYPixel >= SIZE_Y_PET)
               currentYPixel = head_y;

            if (currentYPixel < 0)
               currentYPixel = 0;

            if (currentXPixel >= SIZE_X_PET)
               currentXPixel = head_x;

            if (currentXPixel < 0)
               currentXPixel = 0;
            temp = crystal_map[currentXPixel][currentYPixel];

    }


    crystal_x = static_cast<int>( (float)(temp) / (float)(CRYSTALS_Y));
    crystal_y = static_cast<int>( std::fmod( (float)(temp), (float)( CRYSTALS_Y)));

    return std::make_tuple(crystal_x,crystal_y);
}

int PETsysWorker::scale_energy(int ** energy_peaks,int energy, int crystal_x, int crystal_y){
    // Correct (scale) energy
    float tmp =   511.0 * energy / energy_peaks[crystal_x][crystal_y];
    return static_cast<int>(tmp + 0.5);
}
