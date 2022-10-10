////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file SPECTworker.cpp
///
///	@brief worker thread responsible for live data aquisition and SPECT reconstruction-frame image files saving.
///
///	@author Aphrodite Toufa
/// @date   Created: 07.12.2018
/// @date   Updated: 29.7.2019
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "headers/SPECTworker.h"
#include <QFile>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <sstream>
#include <QDebug>
#include <QMessageBox>
#include <QElapsedTimer>
#include "boost/format.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Includes/dicomEncoder.hpp"



SPECTworker::SPECTworker(QSemaphore *fb, QSemaphore *ub, QMutex *_globalMutex, boost::circular_buffer<quint32>* _BUFFER, QString _str,
                         QString _corDir, QString _deconvDir, QString nucFolder, QString nucName, QDateTime dateTime, double energetics,
                         ReadInputInfo* inputInfo, bool calibrationMode, bool validationOn, spectIsotope studyIsotope)
                         :m_calibrationMode(calibrationMode),m_validationOn(validationOn)
{
    qRegisterMetaType<QVector<qreal>>("QVector<qreal>");
    qRegisterMetaType<QPolygonF>("QPolygonF");
    qRegisterMetaType<cv::Mat>("cv::Mat");

    BUFFER        =  _BUFFER;
    freeBytes     = fb;
    usedBytes     = ub;
    globalMutex   = _globalMutex;


    correctedDir  = _corDir;
    m_qsDeconvDir = _deconvDir;

    rawDir = _str;
    m_qsNuclidedFolder = nucFolder;
    m_qsNuclideName = nucName;

    m_qdtInjectionDateTime = dateTime;
    m_dActivity = energetics;

    m_pReadInputInfo = inputInfo;
    m_spectIsotope=studyIsotope;


    if(m_calibrationMode){
        m_validationFilePath=rawDir;
        m_validationFilePath.remove("/LIST_MODE");
        m_validationFilePath.remove("/IMAGES/RAW");
        m_validationFilePath.append("/RawValidationData.txt");
    }

}

SPECTworker::~SPECTworker()
{
    resetAll();
    cleanup();

#ifdef QT_DEBUG
    qDebug()<< "SPECT destructor reached.";
#endif
}

bool SPECTworker::isAlive()
{
    bool live = true;
    QMutexLocker locker(&mutex);

    live =! stopped;
    return live;
}

bool SPECTworker :: isNotFrame()
{
    bool notFrame = true;
    QMutexLocker locker(&mutex);

    notFrame =! restart;
    return notFrame;
}

void SPECTworker::frameStop()
{
    QMutexLocker locker(&mutex);
    restart=true;
}

void SPECTworker::stopImaging()
{
    QMutexLocker locker(&mutex);
    stopped=true;
}

void SPECTworker:: memory_allocation()
{

    grid_pixel=veyesUtils::allocate_2D_array<int>(output_size_x,output_size_y);
    currentRawMat=veyesUtils::allocate_2D_array<int>(output_size_x,output_size_y);
    veyesUtils::clear_2D_array<int>(grid_pixel,output_size_x,output_size_y);
    veyesUtils::clear_2D_array<int>(currentRawMat,output_size_x,output_size_y);


    summed_flood20=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    energy_lut=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
//  For Pb
    summed_flood201=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    energy_lut1=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    summed_flood202=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    energy_lut2=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);

    summed_floodUpSc=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    energy_lutUpSc=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    summed_floodLowSc=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    energy_lutLowSc=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);



    summed_total=veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    summed_total1 =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    summed_total2 =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);

    summed_totalUpSc =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    summed_totalLowSc =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);

    cumulative_corrected =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    cumulative_corrected1 =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    cumulative_corrected2 =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);

    cumulative_correctedUpSc =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    cumulative_correctedLowSc =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    corrected_with_energy_mat =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    corrected_with_energy_mat1 =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    corrected_with_energy_mat2 =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    corrected_with_energy_matUpSc =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    corrected_with_energy_matLowSc =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    summed_with_energy_mat =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    summed_with_energy_mat1 =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    summed_with_energy_mat2 =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);

    summed_with_energy_matUpSc =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);
    summed_with_energy_matLowSc =veyesUtils::allocate_2D_array<double>(crystal_pixels_x,crystal_pixels_y);

    tempCorWithEnrgMat=veyesUtils::allocate_2D_array<double>(5*crystal_pixels_x,5*crystal_pixels_y);


    veyesUtils::clear_2D_array<int>(summed_flood20,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<int>(energy_lut,crystal_pixels_x,crystal_pixels_y);
    //  For Pb
    veyesUtils::clear_2D_array<int>(summed_flood201,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<int>(energy_lut1,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<int>(summed_flood202,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<int>(energy_lut2,crystal_pixels_x,crystal_pixels_y);

    veyesUtils::clear_2D_array<int>(summed_floodUpSc,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<int>(energy_lutUpSc,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<int>(summed_floodLowSc,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<int>(energy_lutLowSc,crystal_pixels_x,crystal_pixels_y);



     veyesUtils::clear_2D_array<double>(summed_total,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(summed_total1,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(summed_total2,crystal_pixels_x,crystal_pixels_y);

     veyesUtils::clear_2D_array<double>(summed_totalUpSc,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(summed_totalLowSc,crystal_pixels_x,crystal_pixels_y);

     veyesUtils::clear_2D_array<double>(cumulative_corrected,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(cumulative_corrected1,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(cumulative_corrected2,crystal_pixels_x,crystal_pixels_y);

     veyesUtils::clear_2D_array<double>(cumulative_correctedUpSc,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(cumulative_correctedLowSc,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(corrected_with_energy_mat,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(corrected_with_energy_mat1,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(corrected_with_energy_mat2,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(corrected_with_energy_matUpSc,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(corrected_with_energy_matLowSc,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(summed_with_energy_mat,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(summed_with_energy_mat1,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(summed_with_energy_mat2,crystal_pixels_x,crystal_pixels_y);

     veyesUtils::clear_2D_array<double>(summed_with_energy_matUpSc,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<double>(summed_with_energy_matLowSc,crystal_pixels_x,crystal_pixels_y);

     veyesUtils::clear_2D_array<double>(tempCorWithEnrgMat,5*crystal_pixels_x,5*crystal_pixels_y);


    energy = new int[ADC_range];
}

void SPECTworker::loadCalibrationFiles()
{
    QString path =  QDir::currentPath();
    QString qsStrPath1 = "/SPECT_calibration_files/";
    path.append( qsStrPath1 + m_qsNuclidedFolder + "/" );
    QDir toCheckPath( path);
    if ( !toCheckPath.exists() ){
        QMessageBox msg;
        msg.critical(nullptr, "VISUAL-eyes", "The path:" + path + " for the calibration file for the nucleid does not exist. Plese check.");
        return ;
    }
    QString file1,file11,file12,file2,file3,file31,file32, file1UpSc, file1LowSc, file3UpSc, file3LowSc;
    file1 = path;
    file11 = path;
    file12 = path;
    file2 = path;
    file3 = path;
    file31 = path;
    file32 = path;
    file1UpSc = path;
    file1LowSc = path;
    file3UpSc = path;
    file3LowSc = path;

    if (m_spectIsotope.getType()==0){
        file1.append(m_spectIsotope.getFloodG());
        file2.append(m_spectIsotope.getGrid());
        file3.append(m_spectIsotope.getEnergyG());

    }else if(m_spectIsotope.getType()==1){
        file11.append(m_spectIsotope.getFloodX() );
        file12.append(m_spectIsotope.getFloodG());
        file1UpSc.append(m_spectIsotope.getFloodUpScatterX());
        file1LowSc.append(m_spectIsotope.getFloodLowScatterX());
        file2.append(m_spectIsotope.getGrid());
        file31.append(m_spectIsotope.getEnergyX());
        file32.append(m_spectIsotope.getEnergyG());
        file3UpSc.append(m_spectIsotope.getEnergyUpScatterX());
        file3LowSc.append(m_spectIsotope.getEnergyLowScatterX());
    }else{
        file11.append(m_spectIsotope.getFloodG());
        file1UpSc.append(m_spectIsotope.getFloodUpScatterG());
        file1LowSc.append(m_spectIsotope.getFloodLowScatterG());
        file2.append(m_spectIsotope.getGrid());
        file31.append(m_spectIsotope.getEnergyG());
        file3UpSc.append(m_spectIsotope.getEnergyUpScatterG());
        file3LowSc.append(m_spectIsotope.getEnergyLowScatterG());
    }

   /* CALIBRATION FILES EPIC FOR CE SPECT*/
   FILE * file_summed_flood20	= std::fopen(file1.toStdString().c_str(),"r"); //calibration file
   FILE * file_summed_flood201	= std::fopen(file11.toStdString().c_str(),"r"); //calibration file
   FILE * file_summed_flood202	= std::fopen(file12.toStdString().c_str(),"r"); //calibration file
   FILE * file_summed_floodUpSc	= std::fopen(file1UpSc.toStdString().c_str(),"r"); //calibration file
   FILE * file_summed_floodLowSc	= std::fopen(file1LowSc.toStdString().c_str(),"r"); //calibration file

   FILE * file_grid_pixel		= std::fopen(file2.toStdString().c_str(),"r"); //calibration file
   FILE * file_energy			= std::fopen(file3.toStdString().c_str(),"r");	//calibration file
   FILE * file_energy1			= std::fopen(file31.toStdString().c_str(),"r");	//calibration file
   FILE * file_energy2			= std::fopen(file32.toStdString().c_str(),"r");	//calibration file
   FILE * file_energyUpSc			= std::fopen(file3UpSc.toStdString().c_str(),"r");	//calibration file
   FILE * file_energyLowSc			= std::fopen(file3LowSc.toStdString().c_str(),"r");	//calibration file

   // Check if the files have been opened, else close Visual-Eyes
   if ( !file_summed_flood20 || !file_summed_flood201 || !file_summed_floodUpSc){
       QMessageBox msg;
       msg.setIcon(QMessageBox::Critical);
       msg.setWindowFlags(Qt::WindowStaysOnTopHint);
       msg.setText("Cannot locate calibration files for summed flood.Visual-Eyes will be terminated.");
       msg.setStandardButtons(QMessageBox::Ok);
       exit(1);
   }

   if ( !file_summed_flood20 || !file_summed_flood201 || !file_summed_floodUpSc){
       QMessageBox msg;
       msg.setIcon(QMessageBox::Critical);
       msg.setWindowFlags(Qt::WindowStaysOnTopHint);
       msg.setText("Cannot locate calibration files for grid pixel.Visual-Eyes will be terminated.");
       msg.setStandardButtons(QMessageBox::Ok);
       exit(1);
   }

   if ( !file_summed_flood20 || !file_summed_flood201 || !file_summed_floodUpSc){
       QMessageBox msg;
       msg.setIcon(QMessageBox::Critical);
       msg.setWindowFlags(Qt::WindowStaysOnTopHint);
       msg.setText("Cannot locate calibration files for energy.Visual-Eyes will be terminated.");
       msg.setStandardButtons(QMessageBox::Ok);
       exit(1);
   }


    for (int m1 = 0; m1 < output_size_x; m1++){
        for (int m2 = 0; m2 < output_size_y; m2++)
            std::fscanf(file_grid_pixel, "%d ",&grid_pixel[m1][m2]);
    }

    if(m_spectIsotope.getType()==1){
        for (int m1 = 0; m1 < crystal_pixels_x; m1++){
            for (int m2 = 0; m2 < crystal_pixels_y; m2++){
                   std::fscanf(file_summed_flood201, "%d ",&summed_flood201[m1][m2]);
                   std::fscanf(file_summed_flood202, "%d ",&summed_flood202[m1][m2]);

                   std::fscanf(file_summed_floodUpSc, "%d ",&summed_floodUpSc[m1][m2]);
                   std::fscanf(file_summed_floodLowSc, "%d ",&summed_floodLowSc[m1][m2]);
                   std::fscanf(file_energy1, "%d ",&energy_lut1[m1][m2]);
                   std::fscanf(file_energy2, "%d ",&energy_lut2[m1][m2]);
                   std::fscanf(file_energyUpSc, "%d ",&energy_lutUpSc[m1][m2]);
                   std::fscanf(file_energyLowSc, "%d ",&energy_lutLowSc[m1][m2]);
            }
        }
    }
    else if(m_spectIsotope.getType()==2){
        for (int m1 = 0; m1 < crystal_pixels_x; m1++){
            for (int m2 = 0; m2 < crystal_pixels_y; m2++){
                   std::fscanf(file_summed_flood201, "%d ",&summed_flood201[m1][m2]);
                   std::fscanf(file_summed_floodUpSc, "%d ",&summed_floodUpSc[m1][m2]);
                   std::fscanf(file_summed_floodLowSc, "%d ",&summed_floodLowSc[m1][m2]);
                   std::fscanf(file_energy1, "%d ",&energy_lut1[m1][m2]);
                   std::fscanf(file_energyUpSc, "%d ",&energy_lutUpSc[m1][m2]);
                   std::fscanf(file_energyLowSc, "%d ",&energy_lutLowSc[m1][m2]);
            }
        }
    }
    else {
        for (int m1 = 0; m1 < crystal_pixels_x; m1++){
            for (int m2 = 0; m2 < crystal_pixels_y; m2++){
                   std::fscanf(file_summed_flood20, "%d ",&summed_flood20[m1][m2]);
                   std::fscanf(file_energy, "%d ",&energy_lut[m1][m2]);
            }
        }
    }

    if(!m_calibrationMode){

         QString OptDir = m_qsDeconvDir;
         OptDir.remove("/IMAGES/FINAL");
         std::string xrayFile = OptDir.toStdString() + "/Xray.png";
         OptDir.append("/optical.png");
         std::string opFile = OptDir.toStdString();

         optical_img = cv::imread(opFile,CV_LOAD_IMAGE_GRAYSCALE);
         xray_img = cv::imread(xrayFile,CV_LOAD_IMAGE_GRAYSCALE);
         QMap< QString, int > qmFlips;
         qmFlips.insert( "x", 0 );
         qmFlips.insert( "y", 1 );

         cv::rotate(optical_img,optical_img, cv::ROTATE_90_CLOCKWISE);
         cv::rotate( xray_img,xray_img, cv::ROTATE_90_CLOCKWISE);

         if ( m_pReadInputInfo->getFlips().size() > 0){
             foreach ( QString flip, m_pReadInputInfo->getFlips() ){
                 if(flip!=""){
                     cv::flip(optical_img,optical_img, qmFlips[ flip ] );
                     cv::flip(xray_img,xray_img, qmFlips[ flip ] );
                 }
             }
         }


         fusionDir = rawDir;
         fusionDir.append("/CORRECTED/FUSION");

         fusionDeconvDir = m_qsDeconvDir;
         fusionDeconvDir.append("/FUSION");

         QString local= QDir::currentPath().append("/colormap/royal.lut");
         lutFilename = local.toStdString();
    }
}

void SPECTworker::Initialise()
{
    stopped=false;
    restart=false;
    y_count = 0;
    maxEn =0;
    frameCounter=1;
    first=true;

    memory_allocation();
    resetAll();
    loadCalibrationFiles();

    it = 8;
    contrast=0;
    contrast_min=0;

    double res0 = m_pReadInputInfo->getDeconvRes0(); //  2.2; //resolution at 0mm
    double arg = m_pReadInputInfo->getDeconvArg(); // 0.025;
    int dist1 = m_pReadInputInfo->getDeconvDist1(); // 10; //lower bound of distance from the collimator(mm)
    int dist2 = m_pReadInputInfo->getDeconvDist2(); // 30; //upper bound of distance from the collimator(mm)
    double pixelSize = m_pReadInputInfo->getDeconvPixelSize();// 1.7;
    int psfWidth = crystal_pixels_y;
    int psfHeight = crystal_pixels_y;

    ob = new bioemtec::rlDeconv(psfHeight, psfWidth, dist1, dist2, res0, arg, pixelSize);
}

void SPECTworker::run()
{
    ////////////////////////////////////////////////////////////////////////
    /////////////////////* Processing */////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    ///
    if(isAlive()){
        if(isNotFrame()){
            if(usedBytes->tryAcquire(1, 50)){
                if(globalMutex->tryLock(50)) {
                    int items = int(BUFFER->size());
                    Visualisation(items/2);

                    globalMutex->unlock();
                    freeBytes->release(1);
                }
            }
        }
        else {
            frameCounter++;
            y_count++;

            if(!first )
                std::fclose(fp);

            QString number = QString("%1").arg(frameCounter, 3, 10, QChar('0'));
            QString filename = "/Rawframe" + number+".txt"; // + "_" + QTime::currentTime().toString("hhmmss")+".txt";
            m_qdtSaveTime = QDateTime().currentDateTime(); //Since we want to the date time at the point that the txt is saved
            QString total = rawDir + "/LIST_MODE" + filename;
            QByteArray ba = total.toLocal8Bit();
            char *str = ba.data();

            fp = std::fopen(str,"w");
            frame_print( y_count );
            mf_deconvolution( y_count, m_pReadInputInfo->getDeconvIterations() );
            pinakas_dealllocation();
            restart=false;

#ifdef QT_DEBUG
            qDebug() << "frame time!";
#endif

        }
    }
    else{
        if(!first )
            std::fclose(fp);
        if(restart){
            y_count++;
            frame_print( y_count );
            mf_deconvolution( y_count, m_pReadInputInfo->getDeconvIterations() );

            print_sum();
        }
        else{
            /////
            print_sum();
        }

        emit stopProcessing();
#ifdef QT_DEBUG
        qDebug() << "I stopped SPECTworker online";
#endif
    }
}

void SPECTworker :: cleanup()
{

    veyesUtils::delete_2D_array(grid_pixel,output_size_x);
    veyesUtils::delete_2D_array(currentRawMat,output_size_x);


    veyesUtils::delete_2D_array(summed_flood20,crystal_pixels_x);
    veyesUtils::delete_2D_array(energy_lut,crystal_pixels_x);
    veyesUtils::delete_2D_array(summed_flood201,crystal_pixels_x);
    veyesUtils::delete_2D_array(energy_lut1,crystal_pixels_x);
    veyesUtils::delete_2D_array(summed_flood202,crystal_pixels_x);
    veyesUtils::delete_2D_array(energy_lut2,crystal_pixels_x);

    veyesUtils::delete_2D_array(summed_floodUpSc,crystal_pixels_x);
    veyesUtils::delete_2D_array(energy_lutUpSc,crystal_pixels_x);
    veyesUtils::delete_2D_array(summed_floodLowSc,crystal_pixels_x);
    veyesUtils::delete_2D_array(energy_lutLowSc,crystal_pixels_x);


    veyesUtils::delete_2D_array(summed_total,crystal_pixels_x);
    veyesUtils::delete_2D_array(summed_total1,crystal_pixels_x);
    veyesUtils::delete_2D_array(summed_total2,crystal_pixels_x);
    veyesUtils::delete_2D_array(cumulative_corrected,crystal_pixels_x);
    veyesUtils::delete_2D_array(cumulative_corrected1,crystal_pixels_x);
    veyesUtils::delete_2D_array(cumulative_corrected2,crystal_pixels_x);

    veyesUtils::delete_2D_array(corrected_with_energy_mat,crystal_pixels_x);
    veyesUtils::delete_2D_array(summed_with_energy_mat,crystal_pixels_x);
    veyesUtils::delete_2D_array(summed_with_energy_matUpSc,crystal_pixels_x);
    veyesUtils::delete_2D_array(summed_with_energy_matLowSc,crystal_pixels_x);
    veyesUtils::delete_2D_array(tempCorWithEnrgMat,5*crystal_pixels_x);

    delete [] energy;

}

void SPECTworker::pinakas_dealllocation()
{
    for(int i=0;i<crystal_pixels_x;i++){
        for(int j=0;j<crystal_pixels_y;j++){
            summed_with_energy_mat[i][j]=0;
            summed_with_energy_mat1[i][j]=0;
            summed_with_energy_mat2[i][j]=0;
            summed_with_energy_matUpSc[i][j]=0;
            summed_with_energy_matLowSc[i][j]=0;
            corrected_with_energy_mat[i][j]=0;
            corrected_with_energy_mat1[i][j]=0;
            corrected_with_energy_mat2[i][j]=0;
            corrected_with_energy_matUpSc[i][j]=0;
            corrected_with_energy_matLowSc[i][j]=0;
        }
    }
}

void SPECTworker::Visualisation(int events)
{
    quint32 XaXbSigs, YcYdSigs;
    quint16 tempXa, tempXb, tempYc, tempYd;
    int  scaled_energy = 0, cor_i=0, cor_j=0;
    int pos_x2=0, pos_y2=0;
    double   xcog, ycog, d1, d2,cor_en;
    unsigned int 	mask1 = 0xFFFF0000L, mask2 = 0xFFFFL;
    int i=0;
    int	 en, en_new, addX, addY, temp, grid;
    int *x1, *x2, *y1, *y2, xc=0,yc=0;
    double dEnWinUp=0.0, dEnWinLow=0.0, dEnWinUpX=0.0, dEnWinLowX=0.0,dEnWinUpG=0.0, dEnWinLowG=0.0, dEnWinUpXsc=0.0, dEnWinLowXsc=0.0, dEnWinUpGsc=0.0, dEnWinLowGsc=0.0;

    if (m_spectIsotope.getType()==0){
        dEnWinUp = m_spectIsotope.getEnWinUpG();
        dEnWinLow = m_spectIsotope.getEnWinLowG();
    }else if(m_spectIsotope.getType()==1){
        dEnWinUpX = m_spectIsotope.getEnWinUpX();
        dEnWinLowX = m_spectIsotope.getEnWinLowX();
        dEnWinUpXsc =m_spectIsotope.getEnWinUpScatterX();
        dEnWinLowXsc =m_spectIsotope.getEnWinLowScatterX();
        dEnWinUpG =m_spectIsotope.getEnWinUpG();
        dEnWinLowG =m_spectIsotope.getEnWinLowG();
    }else{
        dEnWinUpGsc =m_spectIsotope.getEnWinUpScatterG();
        dEnWinLowGsc = m_spectIsotope.getEnWinLowScatterG();
        dEnWinUpG =m_spectIsotope.getEnWinUpG();
        dEnWinLowG=m_spectIsotope.getEnWinLowG();
    }

    x1 = new int[events];
    x2 = new int[events];
    y1 = new int[events];
    y2 = new int[events];

    temp = 0;
    grid = 0;
    cor_i = 0;
    cor_j = 0;

    int sum_energy = 0;

    if ( first ){
        QString number = QString("%1").arg(frameCounter, 3, 10, QChar('0'));
        QString filename = "/Rawframe" + number + ".txt"; // "_"+QTime::currentTime().toString("hh:mm:ss")+".txt";
//        filename.replace(":","_");
        m_qdtSaveTime = QDateTime().currentDateTime(); //Since we want to the date time at the point that the txt is saved

        QString dest = rawDir;
        QString total = dest + "/LIST_MODE" + filename;
        //QByteArray ba = total.toLocal8Bit();
        //char *str = ba.data();
        fp = std::fopen(total.toStdString().c_str(),"w");
        first=false;
    }
    if(!BUFFER->empty()){
        if(events>=2){
            for(i=0;i<events;i++){
                XaXbSigs = BUFFER->front();
                BUFFER->pop_front();
                YcYdSigs = BUFFER->front();
                BUFFER->pop_front();

                std::fprintf(fp,"%.8X\n%.8X\n",XaXbSigs,YcYdSigs);

                tempXa = quint16((XaXbSigs & mask1 ) >> 16);
                tempXb = quint16(XaXbSigs & mask2);

                tempYc = quint16((YcYdSigs & mask1) >> 16);
                tempYd = quint16(YcYdSigs & mask2);


                y1[i] = tempXa - 2048;   //first compute yc,yd signals and then xa,xb as data come from the stack
                if(y1[i] > 65000)
                    y1[i] = 0;

                y2[i] = tempXb - 2048;
                if(y2[i] > 65000)
                    y2[i] =0;

                x1[i] = tempYc - 2048;
                if(x1[i] > 65000)
                    x1[i] =0;

                x2[i] = tempYd - 2048;
                if(x2[i] > 65000)
                    x2[i] =0;

                sum_energy =x1[i]+x2[i]+y1[i]+y2[i];
                en = sum_energy / 4;

                if((en >= 60) && (en < 1600)){
                    scaled_energy =int(sum_energy / 16);

                    d1   = x1[i]-x2[i]; //cha[j]+chb[j]-chc[j]-chd[j];
                    d2   = y1[i]-y2[i]; //-chb[j]-chc[j];
                    xcog = double(d1)/(x1[i]+x2[i]);
                    ycog = double(d2)/(y1[i]+y2[i]);

                    xc         = int((350 * xcog + 0.5) + 256);
                    yc         = int((700 * ycog + 0.5) + 512);


                    if (en > 0 && xc > -1 && yc > -1 && xc < output_size_x && yc < output_size_y) {
                        currentRawMat[xc][yc] = currentRawMat[xc][yc] + 1;

                        addX = 0;
                        addY = 0;
                        temp = grid_pixel[xc][yc];

                        while(temp > 2900){
                            switch (temp)
                            {
                            case 3000:
                                addX = rand() % -2 + 2;
                                addY = 0;
                                break;
                            case 3100:
                                addY = rand() % -2 + 2;
                                addX = 0;
                                break;
                            case 3200:
                                addX = rand() % -2 + 2;
                                addY = rand() % -2 + 2;
                                break;
                            }

                            yc = yc + addY;
                            xc = xc + addX;
                            temp = grid_pixel[xc][yc];
                        }

                        grid = temp;
                        cor_j = int(grid / crystal_pixels_y);
                        pos_x2 = int(grid / crystal_pixels_y);
                        if (cor_j == crystal_pixels_x){
                            cor_j = crystal_pixels_x - 1;
                            pos_x2 = crystal_pixels_x - 1;
                        }
                        cor_i = int(grid % crystal_pixels_y);
                        pos_y2 = int(grid % crystal_pixels_y);
                        if (cor_i == crystal_pixels_y){
                            cor_i = crystal_pixels_y - 1;
                            pos_y2 = crystal_pixels_y - 1;
                        }

                        if ((energy_lut[cor_j][cor_i] != 0)||(energy_lut1[cor_j][cor_i] != 0)){

                            if (m_spectIsotope.getType()==0){
                                cor_en =m_spectIsotope.getEnergyPeak() / double(energy_lut[cor_j][cor_i]);

                            }else{
                                cor_en =m_spectIsotope.getEnergyPeak() / double(energy_lut1[cor_j][cor_i]);
                            }
                            en_new = int(cor_en * scaled_energy);

                            if(m_calibrationMode){
                                 validation_file.open(m_validationFilePath.toStdString(), std::ios_base::app);
                                 validation_file <<grid <<" "<< en_new << std::endl;
                                 validation_file.close();
                            }



                            energy[en_new]++;
                        }
                        if (m_spectIsotope.getType()==1){
                            if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinUpG) * energy_lut1[cor_j][cor_i])
                                    && (scaled_energy > (1 - dEnWinLowG) * energy_lut1[cor_j][cor_i]))
                            {
                                summed_with_energy_mat1[cor_j][cor_i] = summed_with_energy_mat1[cor_j][cor_i] + 1;
                                summed_total1[pos_x2][pos_y2] = summed_total1[pos_x2][pos_y2] + 1;
                                totalNumberOfEvents++;
                                staticTotalNumberOfEvents++;
                            }

                            if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinUpX) * energy_lut2[cor_j][cor_i])
                                    && (scaled_energy > (1 - dEnWinLowX) * energy_lut2[cor_j][cor_i]))
                            {
                                summed_with_energy_mat2[cor_j][cor_i] = summed_with_energy_mat2[cor_j][cor_i] + 1;
                                summed_total2[pos_x2][pos_y2] = summed_total2[pos_x2][pos_y2] + 1;
                                totalNumberOfEvents++;
                                staticTotalNumberOfEvents++;
                            }

                            if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinUpXsc) * energy_lutUpSc[cor_j][cor_i])
                                    && (scaled_energy > (1 - dEnWinUpXsc) * energy_lutUpSc[cor_j][cor_i]))
                            {
                                summed_with_energy_matUpSc[cor_j][cor_i] = summed_with_energy_matUpSc[cor_j][cor_i] + 1;
                                summed_totalUpSc[pos_x2][pos_y2] = summed_totalUpSc[pos_x2][pos_y2] + 1;
                                totalNumberOfEvents++;
                                staticTotalNumberOfEvents++;
                            }

                            if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinLowXsc) * energy_lutLowSc[cor_j][cor_i])
                                    && (scaled_energy > (1 - dEnWinLowXsc) * energy_lutLowSc[cor_j][cor_i]))
                            {
                                summed_with_energy_matLowSc[cor_j][cor_i] = summed_with_energy_matLowSc[cor_j][cor_i] + 1;
                                summed_totalLowSc[pos_x2][pos_y2] = summed_totalLowSc[pos_x2][pos_y2] + 1;
                                totalNumberOfEvents++;
                                staticTotalNumberOfEvents++;
                            }
                        }
                        else if (m_spectIsotope.getType()==2){
                            if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinUpG) * energy_lut1[cor_j][cor_i])
                                    && (scaled_energy > (1 - dEnWinLowG) * energy_lut1[cor_j][cor_i]))
                            {
                                summed_with_energy_mat1[cor_j][cor_i] = summed_with_energy_mat1[cor_j][cor_i] + 1;
                                summed_total1[pos_x2][pos_y2] = summed_total1[pos_x2][pos_y2] + 1;
                                totalNumberOfEvents++;
                                staticTotalNumberOfEvents++;
                            }


                            if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinUpGsc) * energy_lutUpSc[cor_j][cor_i])
                                    && (scaled_energy > (1 - dEnWinUpGsc) * energy_lutUpSc[cor_j][cor_i]))
                            {
                                summed_with_energy_matUpSc[cor_j][cor_i] = summed_with_energy_matUpSc[cor_j][cor_i] + 1;
                                summed_totalUpSc[pos_x2][pos_y2] = summed_totalUpSc[pos_x2][pos_y2] + 1;
                                totalNumberOfEvents++;
                                staticTotalNumberOfEvents++;
                            }

                            if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinLowGsc) * energy_lutLowSc[cor_j][cor_i])
                                    && (scaled_energy > (1 - dEnWinLowGsc) * energy_lutLowSc[cor_j][cor_i]))
                            {
                                summed_with_energy_matLowSc[cor_j][cor_i] = summed_with_energy_matLowSc[cor_j][cor_i] + 1;
                                summed_totalLowSc[pos_x2][pos_y2] = summed_totalLowSc[pos_x2][pos_y2] + 1;
                                totalNumberOfEvents++;
                                staticTotalNumberOfEvents++;
                            }
                        }else {
                            if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinUp) * energy_lut[cor_j][cor_i])
                                    && (scaled_energy > (1 - dEnWinLow) * energy_lut[cor_j][cor_i]))
                            {
                                summed_with_energy_mat[cor_j][cor_i] = summed_with_energy_mat[cor_j][cor_i] + 1;
                                summed_total[pos_x2][pos_y2] = summed_total[pos_x2][pos_y2] + 1;
                                totalNumberOfEvents++;
                                staticTotalNumberOfEvents++;
                            }
                        }

                    }
                }
            }

            double s_20 = 0.0,s_tot = 0.0;
            double c_20 = 0.0,c_tot = 0.0;
            double s_20_1 = 0.0, c_20_1 = 0.0;
            double s_20_2 = 0.0, c_20_2 = 0.0;
            double s_20_3 = 0.0, c_20_3 = 0.0;
            double s_20_4 = 0.0, c_20_4 = 0.0;
            double s_tot_1 = 0.0, c_tot_1 = 0.0;
            double s_tot_2 = 0.0, c_tot_2 = 0.0;
            double s_tot_3 = 0.0, c_tot_3 = 0.0;
            double s_tot_4 = 0.0, c_tot_4 = 0.0;
            double f,f_t;
            double f1=0.0, f2=0.0, f3=0.0, f4=0.0;
            double f1_t=0.0, f2_t=0.0, f3_t=0.0, f4_t=0.0;
            if(m_spectIsotope.getType()==1){
            //Here the figures that are plotted in live imaging are created.
                      for(int i=2;i<crystal_pixels_x-2;i++){
                          for(int j=2;j<crystal_pixels_y-2;j++){
                              if(summed_flood201[i][j] > 40){
                                  corrected_with_energy_mat1[i][j] = double(10280 * summed_with_energy_mat1[i][j] / summed_flood201[i][j]);
                                  cumulative_corrected1[i][j] = double(10280 * summed_total1[i][j] / summed_flood201[i][j]);
                              }
                              if(summed_flood202[i][j] > 40){
                                  corrected_with_energy_mat2[i][j] = double(10280 * summed_with_energy_mat2[i][j] / summed_flood202[i][j]);                           
                                  cumulative_corrected2[i][j] = double(10280 * summed_total2[i][j] / summed_flood202[i][j]);

                              }
                              if(summed_floodUpSc[i][j] > 40){
                                  corrected_with_energy_matUpSc[i][j] = double(10280 * summed_with_energy_matUpSc[i][j] / summed_floodUpSc[i][j]);
                                  cumulative_correctedUpSc[i][j] = double(10280 * summed_totalUpSc[i][j] / summed_floodUpSc[i][j]);

                              }
                              if(summed_floodUpSc[i][j] > 40){
                                  corrected_with_energy_matLowSc[i][j] = double(10280 * summed_with_energy_matLowSc[i][j] / summed_floodLowSc[i][j]);
                                  cumulative_correctedLowSc[i][j] = double(10280 * summed_totalLowSc[i][j] / summed_floodLowSc[i][j]);

                              }


                          }
                      }

            }
            else if(m_spectIsotope.getType()==2){

                      for(int i=2;i<crystal_pixels_x-2;i++){
                          for(int j=2;j<crystal_pixels_y-2;j++){
                              if(summed_flood201[i][j] > 40){
                                  corrected_with_energy_mat1[i][j] = double(10280 * summed_with_energy_mat1[i][j] / summed_flood201[i][j]);
                                  cumulative_corrected1[i][j] = double(10280 * summed_total1[i][j] / summed_flood201[i][j]);
                              }
                              if(summed_floodUpSc[i][j] > 40){
                                  corrected_with_energy_matUpSc[i][j] = double(10280 * summed_with_energy_matUpSc[i][j] / summed_floodUpSc[i][j]);
                                  cumulative_correctedUpSc[i][j] = double(10280 * summed_totalUpSc[i][j] / summed_floodUpSc[i][j]);

                              }
                              if(summed_floodUpSc[i][j] > 40){
                                  corrected_with_energy_matLowSc[i][j] = double(10280 * summed_with_energy_matLowSc[i][j] / summed_floodLowSc[i][j]);
                                  cumulative_correctedLowSc[i][j] = double(10280 * summed_totalLowSc[i][j] / summed_floodLowSc[i][j]);

                              }


                          }

                      }


            }
            else{
                      for(int i=2;i<crystal_pixels_x-2;i++){
                          for(int j=2;j<crystal_pixels_y-2;j++){
                              if(summed_flood20[i][j] > 40){
                                  corrected_with_energy_mat[i][j] = double(10280 * summed_with_energy_mat[i][j] / summed_flood20[i][j]);
                                  cumulative_corrected[i][j] = double(10280 * summed_total[i][j] / summed_flood20[i][j]);
                              }
                          }
                      }
            }
            if(m_spectIsotope.getType()==1){
                for(int i=0;i<crystal_pixels_x;i++){
                    for(int j=0;j<crystal_pixels_y;j++){
                        s_20_1  += summed_with_energy_mat1[i][j];
                        s_tot_1 += summed_total1[i][j];
                        c_20_1  += corrected_with_energy_mat1[i][j];
                        c_tot_1 += cumulative_corrected1[i][j];

                        s_20_2  += summed_with_energy_mat2[i][j];
                        s_tot_2 += summed_total2[i][j];
                        c_20_2  += corrected_with_energy_mat2[i][j];
                        c_tot_2  += cumulative_corrected2[i][j];

                        s_20_3  += summed_with_energy_matUpSc[i][j];
                        s_tot_3 += summed_totalUpSc[i][j];
                        c_20_3  += corrected_with_energy_matUpSc[i][j];
                        c_tot_3  += cumulative_correctedUpSc[i][j];

                        s_20_4  += summed_with_energy_matLowSc[i][j];
                        s_tot_4 += summed_totalLowSc[i][j];
                        c_20_4  += corrected_with_energy_matLowSc[i][j];
                        c_tot_4  += cumulative_correctedLowSc[i][j];
                    }
                }
            }
            else if(m_spectIsotope.getType()==2){
                for(int i=0;i<crystal_pixels_x;i++){
                    for(int j=0;j<crystal_pixels_y;j++){
                        s_20_1  += summed_with_energy_mat1[i][j];
                        s_tot_1 += summed_total1[i][j];
                        c_20_1  += corrected_with_energy_mat1[i][j];
                        c_tot_1 += cumulative_corrected1[i][j];

                        s_20_3  += summed_with_energy_matUpSc[i][j];
                        s_tot_3 += summed_totalUpSc[i][j];
                        c_20_3  += corrected_with_energy_matUpSc[i][j];
                        c_tot_3  += cumulative_correctedUpSc[i][j];

                        s_20_4  += summed_with_energy_matLowSc[i][j];
                        s_tot_4 += summed_totalLowSc[i][j];
                        c_20_4  += corrected_with_energy_matLowSc[i][j];
                        c_tot_4  += cumulative_correctedLowSc[i][j];
                    }
                }
            }
            else{
                for(int i=0;i<crystal_pixels_x;i++){
                    for(int j=0;j<crystal_pixels_y;j++){
                        s_20 +=  summed_with_energy_mat[i][j];
                        s_tot += summed_total[i][j];
                        c_20  += corrected_with_energy_mat[i][j];
                        c_tot += cumulative_corrected[i][j];
                    }
                }
            }

            f =c_20/s_20;
            f_t = c_tot/s_tot;

            f1 = c_20_1 / s_20_1;
            f2 = c_20_2 / s_20_2;
            f3 = c_20_3 / s_20_3;
            f4 = c_20_4 / s_20_4;

            f1_t = c_tot_1 / s_tot_1;
            f2_t = c_tot_2 / s_tot_2;
            f3_t = c_tot_3 / s_tot_3;
            f4_t = c_tot_4 / s_tot_4;


            if(m_spectIsotope.getType()==1){
                for(int i=0;i<crystal_pixels_x;i++){
                    for(int j=0;j<crystal_pixels_y;j++){
                        corrected_with_energy_mat1[i][j] = corrected_with_energy_mat1[i][j] / f1;
                        corrected_with_energy_mat2[i][j] = corrected_with_energy_mat2[i][j] / f2;
                        corrected_with_energy_matUpSc[i][j] = corrected_with_energy_matUpSc[i][j] / f3;
                        corrected_with_energy_matLowSc[i][j] = corrected_with_energy_matLowSc[i][j] / f4;
                        cumulative_corrected1[i][j] = cumulative_corrected1[i][j] / f1_t;
                        cumulative_corrected2[i][j] = cumulative_corrected2[i][j] / f2_t;
                        cumulative_correctedUpSc[i][j] = cumulative_correctedUpSc[i][j] / f3_t;
                        cumulative_correctedLowSc[i][j] = cumulative_correctedLowSc[i][j] / f4_t;
                    }
                }

                for(int i=2;i<crystal_pixels_x-2;i++){
                    for(int j=2;j<crystal_pixels_y-2;j++){
                        corrected_with_energy_mat2[i][j] = corrected_with_energy_mat2[i][j] -
                                (dEnWinLowX/(2*dEnWinLowXsc))*corrected_with_energy_matLowSc[i][j] - (dEnWinUpX/(4*dEnWinUpXsc))*corrected_with_energy_matUpSc[i][j];

                        cumulative_corrected2[i][j] = cumulative_corrected2[i][j] -
                                (dEnWinLowX/(2*dEnWinLowXsc))*cumulative_correctedLowSc[i][j] - (dEnWinUpX/(4*dEnWinUpXsc))*cumulative_correctedUpSc[i][j];

                        corrected_with_energy_mat[i][j] = corrected_with_energy_mat1[i][j]*corrected_with_energy_mat2[i][j];
                        cumulative_corrected[i][j] = cumulative_corrected1[i][j]*cumulative_corrected2[i][j];


                        if (corrected_with_energy_mat[i][j] < 0.0)
                            corrected_with_energy_mat[i][j]=0.0;
                        if (cumulative_corrected[i][j] < 0.0)
                            cumulative_corrected[i][j]=0.0;

                    }
                }

            }
            else if (m_spectIsotope.getType()==2){
                for(int i=0;i<crystal_pixels_x;i++){
                    for(int j=0;j<crystal_pixels_y;j++){
                        corrected_with_energy_mat1[i][j] = corrected_with_energy_mat1[i][j] / f1;
                        corrected_with_energy_matUpSc[i][j] = corrected_with_energy_matUpSc[i][j] / f3;
                        corrected_with_energy_matLowSc[i][j] = corrected_with_energy_matLowSc[i][j] / f4;
                        cumulative_corrected1[i][j] = cumulative_corrected1[i][j] / f1_t;
                        cumulative_correctedUpSc[i][j] = cumulative_correctedUpSc[i][j] / f3_t;
                        cumulative_correctedLowSc[i][j] = cumulative_correctedLowSc[i][j] / f4_t;
                    }
                }

                for(int i=2;i<crystal_pixels_x-2;i++){
                    for(int j=2;j<crystal_pixels_y-2;j++){
                        corrected_with_energy_mat[i][j] = corrected_with_energy_mat1[i][j] -
                                (dEnWinLowG/(2*dEnWinLowGsc))*corrected_with_energy_matLowSc[i][j] - (dEnWinUpG/(4*dEnWinUpGsc))*corrected_with_energy_matUpSc[i][j];
                        cumulative_corrected[i][j] = cumulative_corrected1[i][j] -
                                (dEnWinLowG/(2*dEnWinLowGsc))*cumulative_correctedLowSc[i][j] - (dEnWinUpG/(4*dEnWinUpGsc))*cumulative_correctedUpSc[i][j];


                        if (corrected_with_energy_mat[i][j] < 0.0)
                            corrected_with_energy_mat[i][j]=0.0;
                        if (cumulative_corrected[i][j] < 0.0)
                            cumulative_corrected[i][j]=0.0;

                    }
                }
            }
            else {
                for(int i=0;i<crystal_pixels_x;i++){
                    for(int j=0;j<crystal_pixels_y;j++){
                        corrected_with_energy_mat[i][j] = corrected_with_energy_mat[i][j] / f;
                        cumulative_corrected[i][j] = cumulative_corrected[i][j] / f_t;
                    }
                }
            }

        }
    }
}

void SPECTworker::imagingData()
{
    QVector<qreal> rawVMatrix, corVMatrix, sumCorVMatrix;
    double maxRaw = 0;

    for (int i=0; i < output_size_x; i++){
        for(int j=0; j < output_size_y; j++){
            if(currentRawMat[i][j] > maxRaw)
                maxRaw=(currentRawMat[i][j]);
            rawVMatrix.append(currentRawMat[i][j]);
        }
    }

    for(int i=0; i < output_size_x; i++){
        if(energy[i] > maxEn){
            maxEn = energy[i];
        }
        points << QPointF(i, energy[i]);
    }


    double maxCor = 0.0;
    for (int i = 0; i < crystal_pixels_x; i++){ // change to default again i=0 , j=0
         for(int j = 0; j < crystal_pixels_y; j++){
             if(corrected_with_energy_mat[i][j] > maxCor)
                 maxCor=(corrected_with_energy_mat[i][j]);
             corVMatrix.append(corrected_with_energy_mat[i][j]);
         }
     }

    if(contrast != 0.00){
        double con_percentage = maxCor*contrast;
        maxCor = maxCor-con_percentage;
    }


    double maxSumCor = 0.0;
    for (int i=0; i<5*crystal_pixels_x; i++){
        for(int j=0;j<5*crystal_pixels_y;j++){
            if( tempCorWithEnrgMat[i][j] > maxSumCor)
                maxSumCor=(tempCorWithEnrgMat[i][j]);
            sumCorVMatrix.append(tempCorWithEnrgMat[i][j]);
        }
    }

    emit sendImagingDataProgress(rawVMatrix,corVMatrix,sumCorVMatrix,points,maxRaw,maxCor,maxSumCor,maxEn);

    rawVMatrix.clear();
    corVMatrix.clear();
    sumCorVMatrix.clear();
    points.clear();

}

//Here the frame figure are printed
void SPECTworker::frame_print(int frame)
{

    cv::Mat matIn=veyesUtils::array2D_to_cvmat(corrected_with_energy_mat,crystal_pixels_x,crystal_pixels_y,mf_decayCorrection());
    cv::Mat matOutFinal=veyesUtils::image_conversion(matIn,m_scale1_x,m_scale1_y,crystal_pixels_x,crystal_pixels_y);
    cv::Mat matOutCorrected=veyesUtils::image_conversion(matIn,m_scale2_x,m_scale2_y,crystal_pixels_x,crystal_pixels_y);


    QString number = QString("%1").arg(frame, 3, 10, QChar('0'));
    QString filename = "/Correctedframe"+number+".txt";
    QString dest = rawDir + "/CORRECTED";
    QString total = dest.append(filename);
    veyesUtils::write_txt_image(total.toStdString(),matOutFinal, m_scale1_x * crystal_pixels_x,m_scale1_y * crystal_pixels_y);

    if (!m_calibrationMode){
            QString fusionOut = "/fussedOpticalImg"+number+".png";
            QString fDir = fusionDir;
            fDir.remove("FUSION");
            fDir.append("XRAY");
            std::string fussedXray = fDir.toStdString() +"/fussedXrayImg"+ number.toStdString()+".png";
            fDir.remove("XRAY");
            fDir.append("FUSION");
            fDir.append(fusionOut);
            std::string fussed = fDir.toStdString();

            cv::Mat fussedCorrected = imageFusion::fusion(optical_img, matOutCorrected, lutFilename);
            cv::Mat fussedXrayCorrected = imageFusion::fusion(xray_img, matOutCorrected, lutFilename);
            cv::imwrite(fussed, fussedCorrected);
            cv::imwrite(fussedXray, fussedXrayCorrected);
    }
    matIn.release();
    matOutCorrected.release();
    matOutFinal.release();

}

QVector<qreal> SPECTworker::mf_deconvolution( int iterations )
{
    double res0 = m_pReadInputInfo->getDeconvRes0(); //  2.2; //resolution at 0mm
    double arg = m_pReadInputInfo->getDeconvArg(); // 0.025;
    int dist1 = m_pReadInputInfo->getDeconvDist1(); // 10; //lower bound of distance from the collimator(mm)
    int dist2 = m_pReadInputInfo->getDeconvDist2(); // 30; //upper bound of distance from the collimator(mm)
    double pixelSize = m_pReadInputInfo->getDeconvPixelSize();// 1.7;

    //const int interpRows = m_scale1_x * crystal_pixels_x;
    const int interpCols = m_scale1_y * crystal_pixels_y;

    bioemtec::rlDeconv d(interpCols, interpCols, dist1, dist2, res0, arg, pixelSize);


    cv::Mat inputImageMat=veyesUtils::array2D_to_cvmat(corrected_with_energy_mat,crystal_pixels_x,crystal_pixels_y,mf_decayCorrection());
    cv::Mat matOutFinal=veyesUtils::image_conversion(inputImageMat,m_scale1_x,m_scale1_y,crystal_pixels_x,crystal_pixels_y);

    Mat outputImageMat; //do it CV_32F
    //Perform the convolution
    d.deconv(matOutFinal, outputImageMat, iterations, m_pReadInputInfo->getDeconvDampar(), m_pReadInputInfo->getDeconvHistAdj() );

    QVector<qreal> sumCorVMatrix;
    for (int i=0; i<matOutFinal.rows;  i++){
        for(int j=0;j<matOutFinal.cols; j++)
            sumCorVMatrix.append( matOutFinal.at<float> (i, j) );
    }

    return sumCorVMatrix;
}

void SPECTworker::mf_deconvolution( int frame, int iterations )
{
    double res0 = m_pReadInputInfo->getDeconvRes0(); //  2.2; //resolution at 0mm
    double arg = m_pReadInputInfo->getDeconvArg(); // 0.025;
    int dist1 = m_pReadInputInfo->getDeconvDist1(); // 10; //lower bound of distance from the collimator(mm)
    int dist2 = m_pReadInputInfo->getDeconvDist2(); // 30; //upper bound of distance from the collimator(mm)
    double pixelSize = m_pReadInputInfo->getDeconvPixelSize();// 1.7;


    //const int interpRows = scaleX * crystal_pixels_x;
    const int interpCols = m_scale1_y * crystal_pixels_y;

    bioemtec::rlDeconv d(interpCols, interpCols, dist1, dist2, res0, arg, pixelSize);

    cv::Mat inputImageMat=veyesUtils::array2D_to_cvmat(corrected_with_energy_mat,crystal_pixels_x,crystal_pixels_y,mf_decayCorrection());
    cv::Mat matOutFinal=veyesUtils::image_conversion(inputImageMat,m_scale1_x,m_scale1_y,crystal_pixels_x,crystal_pixels_y);
    cv::Mat outputImageMat;
    //Perform the convolution
    d.deconv(matOutFinal, outputImageMat, iterations, m_pReadInputInfo->getDeconvDampar(), m_pReadInputInfo->getDeconvHistAdj() );


    int gaussFactor=m_pReadInputInfo->getGaussKernel();
    cv::GaussianBlur(outputImageMat,outputImageMat,cv::Size(gaussFactor,gaussFactor),0);


    QString number = QString("%1").arg(frame, 3, 10, QChar('0'));
    QString filename = "/Finalframe" + number + ".txt";

    QString dest = m_qsDeconvDir;
    QString total = dest.append(filename);
    std::string str = total.toStdString();
    veyesUtils::write_txt_image(str,outputImageMat,outputImageMat.rows,outputImageMat.cols);

    for (int i = 0; i < outputImageMat.rows; i++)
        for (int j = 0; j < outputImageMat.cols; j++)
            tempCorWithEnrgMat[i][j] += outputImageMat.at<float>(i,j);


    cv::Mat matOutFinal2=veyesUtils::image_conversion(outputImageMat,m_scale2_x,m_scale2_y,crystal_pixels_x,crystal_pixels_y);

    if (!m_calibrationMode){
        cv::Mat fussedDeconv = imageFusion::fusion(optical_img, matOutFinal2, lutFilename);
        cv::Mat fussedXrayDeconv = imageFusion::fusion(xray_img, matOutFinal2, lutFilename);
        QString fusionOut = "/fussedOpticalImg" + number + ".png";
        QString fDir = fusionDeconvDir;
        fDir.remove("FUSION");
        fDir.append("XRAY");
        std::string fussedXray = fDir.toStdString() +"/fussedXrayImg" + number.toStdString() + ".png";
        fDir.remove("XRAY");
        fDir.append("FUSION");
        fDir.append(fusionOut);
        std::string fussed = fDir.toStdString();
        cv::imwrite(fussed, fussedDeconv);
        cv::imwrite(fussedXray, fussedXrayDeconv);
    }
    inputImageMat.release();
    outputImageMat.release();
    matOutFinal.release();
    matOutFinal2.release();
}


void SPECTworker::calculate_flood(QString rawFileIn){

    QString file1,file11,file12,fileUpSc,fileLowSc;
    QString fileRn1,fileRn11,fileRn12,fileRnUpSc,fileRnLowSc;
    QByteArray floodBa,floodBa11,floodBa12,floodBaUpSc,floodBaLowSc;
    const char *floodFileOut,* floodFile11,* floodFile12,* floodFileUpSc,* floodFileLowSc;

    QString path =  QDir::currentPath();
    QString qsStrPath1 = "/SPECT_calibration_files/";
    path.append( qsStrPath1 + m_qsNuclidedFolder + "/" );
    file1 = path;
    file11 = path;
    file12 = path;
    fileUpSc = path;
    fileLowSc = path;

    double dEnWinUp=0.0, dEnWinLow=0.0, dEnWinUpX=0.0, dEnWinLowX=0.0,dEnWinUpG=0.0, dEnWinLowG=0.0, dEnWinUpXsc=0.0, dEnWinLowXsc=0.0, dEnWinUpGsc=0.0, dEnWinLowGsc=0.0;


    if (m_spectIsotope.getType()==0){
        dEnWinUp = m_spectIsotope.getEnWinUpG();
        dEnWinLow = m_spectIsotope.getEnWinLowG();
    }else if(m_spectIsotope.getType()==1){
        dEnWinUpX = m_spectIsotope.getEnWinUpX();
        dEnWinLowX = m_spectIsotope.getEnWinLowX();
        dEnWinUpXsc =m_spectIsotope.getEnWinUpScatterX();
        dEnWinLowXsc =m_spectIsotope.getEnWinLowScatterX();
        dEnWinUpG =m_spectIsotope.getEnWinUpG();
        dEnWinLowG =m_spectIsotope.getEnWinLowG();
    }else{
        dEnWinUpGsc =m_spectIsotope.getEnWinUpScatterG();
        dEnWinLowGsc = m_spectIsotope.getEnWinLowScatterG();
        dEnWinUpG =m_spectIsotope.getEnWinUpG();
        dEnWinLowG=m_spectIsotope.getEnWinLowG();
    }



    if (m_spectIsotope.getType()==0){
        file1.append(m_spectIsotope.getFloodG());
    }else if(m_spectIsotope.getType()==1){
        file11.append(m_spectIsotope.getFloodX() );
        file12.append(m_spectIsotope.getFloodG());
        fileUpSc.append(m_spectIsotope.getFloodUpScatterX());
        fileLowSc.append(m_spectIsotope.getFloodLowScatterX());

    }else{
        file11.append(m_spectIsotope.getFloodG());
        fileUpSc.append(m_spectIsotope.getFloodUpScatterG());
        fileLowSc.append(m_spectIsotope.getFloodLowScatterG());
    }

    if(m_spectIsotope.getType()==1){
        fileRn11 = file11;
        fileRn11.remove(".txt");
        fileRn11.append(".bk");
        QFile::copy(file11,fileRn11);
        fileRn12 = file12;
        fileRn12.remove(".txt");
        fileRn12.append(".bk");
        QFile::copy(file12,fileRn12);
        qDebug() << "File 1" << file12 << endl;
        qDebug() << "File 2" << fileRn12 << endl;

        fileRnUpSc = fileUpSc;
        fileRnUpSc.remove(".txt");
        fileRnUpSc.append(".bk");
        QFile::copy(fileUpSc,fileRnUpSc);

        qDebug() << "File 1" << fileUpSc << endl;
        qDebug() << "File 2" << fileRnUpSc << endl;

        fileRnLowSc = fileLowSc;
        fileRnLowSc.remove(".txt");
        fileRnLowSc.append(".bk");
        QFile::copy(fileLowSc,fileRnLowSc);
        qDebug() << "File 1" << fileLowSc << endl;
        qDebug() << "File 2" << fileRnLowSc << endl;

        floodBa11 = file11.toLocal8Bit();
        floodFile11 = floodBa11.data();

        floodBa12 = file12.toLocal8Bit();
        floodFile12 = floodBa12.data();

        floodBaUpSc = fileUpSc.toLocal8Bit();
        floodFileUpSc = floodBaUpSc.data();

        floodBaLowSc = fileLowSc.toLocal8Bit();
        floodFileLowSc = floodBaLowSc.data();
    }else if(m_spectIsotope.getType()==2){
        fileRn11 = file11;
        fileRn11.remove(".txt");
        fileRn11.append(".bk");
        QFile::copy(file11,fileRn11);

        fileRnUpSc = fileUpSc;
        fileRnUpSc.remove(".txt");
        fileRnUpSc.append(".bk");
        QFile::copy(fileUpSc,fileRnUpSc);

        fileRnLowSc = fileLowSc;
        fileRnLowSc.remove(".txt");
        fileRnLowSc.append(".bk");
        QFile::copy(fileLowSc,fileRnLowSc);

        floodBa11 = file11.toLocal8Bit();
        floodFile11 = floodBa11.data();

        floodBaUpSc = fileUpSc.toLocal8Bit();
        floodFileUpSc = floodBaUpSc.data();

        floodBaLowSc = fileLowSc.toLocal8Bit();
        floodFileLowSc = floodBaLowSc.data();
    }else{
        fileRn1 = file1;
        fileRn1.remove(".txt");
        fileRn1.append(".bk");
        QFile::copy(file1,fileRn1);
        floodBa = file1.toLocal8Bit();
        floodFileOut = floodBa.data();

    }



    QByteArray ba = rawFileIn.toLocal8Bit();
    const char *rawFileName = ba.data();
    FILE *file_in			            = fopen (rawFileName,"r"); //flood point

////////////////////////////////////////////////////////////////////////
/////////////////////////* OUTPUT FILES *///////////////////////////////
////////////////////////////////////////////////////////////////////////




    unsigned int 	hex;
    unsigned int 	mask1 = 0xFFFF0000, mask2 = 0x0000FFFF;
    unsigned int 	*hex_data, *temp1, *temp2;
    long long 		count, count1, count2, numberOfLines;
    unsigned short 	*x1, *x2, *y1, *y2;
    int 			en = 0;

    int 			*crystal_energies, *local_crystal_max;
    int 			**cog_image, **summed_mat, **summed_energy_mat;

    int             **summed_energy_mat_x, **summed_energy_mat_g, **summed_energy_mat_x_sclow, **summed_energy_mat_x_scup;
    int             **summed_energy_mat_g_sclow, **summed_energy_mat_g_scup;

    int 			total_crystal_channels;
    int 			sum_energy, cor_i, cor_j, crystal_no, total_crystals, scaled_energy;
    int 			temp = 0, addX = 0, addY = 0;

    float 			xcog, ycog, d1, d2;
    short int 		xc, yc;
    long long 		iCounter = 0, jCounter = 0;



    total_crystals          =  crystal_pixels_x * crystal_pixels_y;
    total_crystal_channels  =  total_crystals * ADC_chan;
    crystal_energies    = (int*) malloc (total_crystal_channels * sizeof(int));
    local_crystal_max   = (int*) malloc (total_crystals * sizeof(int));


////////////////////////////////////////////////////////////////////////
/////////////* PROCESS DATA FROM FLOOD WITHOUT COLLIMATOR */////////////
////////////////////////////////////////////////////////////////////////

    numberOfLines           =  veyesUtils::returnTheNumberOfLines(file_in);
    printf("Total number of lines = %lld\n", numberOfLines);

    hex_data 			= (unsigned int*) malloc (numberOfLines * sizeof(unsigned int));
    temp1 				= (unsigned int*) malloc ((numberOfLines/2) * sizeof(unsigned int));
    temp2 				= (unsigned int*) malloc ((numberOfLines/2) * sizeof(unsigned int));
    x1	 				= (unsigned short*) malloc ((numberOfLines/2) * sizeof(unsigned short ));
    x2	 				= (unsigned short*) malloc ((numberOfLines/2) * sizeof(unsigned short ));
    y1	 				= (unsigned short*) malloc ((numberOfLines/2) * sizeof(unsigned short ));
    y2	 				= (unsigned short*) malloc ((numberOfLines/2) * sizeof(unsigned short ));
////////////////////////////////////////////////////////////////////////
/////* Get data from file and store them to array as integers */////////
////////////////////////////////////////////////////////////////////////

    fseek (file_in, 0, SEEK_SET);
    count = 0;
    while (fscanf(file_in, "%x", &hex) == 1)
    {
        hex_data[count++] = hex;
    }

////////////////////////////////////////////////////////////////////////
/////////////* Seperate ADCs data using masks */////////////////////////
////////////////////////////////////////////////////////////////////////

    count1 = 0;
    count2 = 0;
    for (count1 = 0; count1 <= numberOfLines - 4; count1 += 2)
    {
      temp1[count2] = hex_data[count1] & mask1;
      temp1[count2] >>= 16;
      y1[count2] = temp1[count2] - 2048 ;
      if (y1[count2] > 65000)
      {
          y1[count2] = 0;
      }
      y2[count2] = (hex_data[count1] & mask2) - 2048;
      if (y2[count2] > 65000)
      {
          y2[count2] = 0;
      }
      temp2[count2] = hex_data[count1+1] & mask1;
      temp2[count2] >>= 16;
      x1[count2] = temp2[count2] - 2048;
      if (x1[count2] > 65000)
      {
          x1[count2] = 0;
      }
      x2[count2] = (hex_data[count1+1] & mask2) - 2048;
      if (x2[count2] > 65000)
      {
          x2[count2] = 0;
      }
      count2++;
    }

////////////////////////////////////////////////////////////////////////
//////////////////////* Allocate memory  *//////////////////////////////
////////////////////////////////////////////////////////////////////////

    cog_image=veyesUtils::allocate_2D_array<int>(output_size_x,output_size_y);
    summed_mat=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    summed_energy_mat=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    summed_energy_mat_x=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    summed_energy_mat_g=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    summed_energy_mat_x_sclow=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    summed_energy_mat_x_scup=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    summed_energy_mat_g_sclow=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);
    summed_energy_mat_g_scup=veyesUtils::allocate_2D_array<int>(crystal_pixels_x,crystal_pixels_y);


////////////////////////////////////////////////////////////////////////
///////////////////////* Initialization *///////////////////////////////
////////////////////////////////////////////////////////////////////////

     veyesUtils::clear_2D_array<int>(cog_image,output_size_x,output_size_y);
     veyesUtils::clear_2D_array<int>(summed_mat,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<int>(summed_energy_mat,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<int>(summed_energy_mat_x,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<int>(summed_energy_mat_g,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<int>(summed_energy_mat_x_sclow,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<int>(summed_energy_mat_x_scup,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<int>(summed_energy_mat_g_sclow,crystal_pixels_x,crystal_pixels_y);
     veyesUtils::clear_2D_array<int>(summed_energy_mat_g_scup,crystal_pixels_x,crystal_pixels_y);


    printf("Read pixel_grid .................... OK\n");
    printf("Initiate COG file ................. OK\n");
    printf("Initiate SUMMED file .............. OK\n");
    printf("Initiate SUMMED WITH ENERGY file .. OK\n");
    printf("Initiate ENERGY_LUT file .......... OK\n");
    printf("Initiate ENERGY file .............. OK\n");
    printf("Read crystal_energies_LUT_new ........ OK\n");


////////////////////////////////////////////////////////////////////////
/////////////////////////* Process data *///////////////////////////////
////////////////////////////////////////////////////////////////////////

    for (iCounter = 0; iCounter < (numberOfLines / 2); iCounter++)
    {

        sum_energy = x1[iCounter] + x2[iCounter] + y1[iCounter] + y2[iCounter];
        en = sum_energy / 4;
        if ((en >= 60) && (en < 1600))
        {
            scaled_energy = sum_energy / ADC_chan_energy; // 0 < scaled_energy < 1024

            d1         = x1[iCounter] - x2[iCounter];
            d2         = y1[iCounter] - y2[iCounter];
            xcog       = float(d1 / (x1[iCounter] + x2[iCounter]));
            ycog       = float(d2 / (y1[iCounter] + y2[iCounter]));

            xc         = int((350 * xcog + 0.5) + 256);
            yc         = int((700 * ycog + 0.5) + 512);

            if ((en > 0) && (xc > 0) && (yc > 0) && (xc < output_size_x) && (yc < output_size_y))
            {
               addX = 0;
               addY = 0;

               cog_image[xc][yc]++;

               temp = grid_pixel[xc][yc];

                while(temp > 2900)
                {
                    switch (temp)
                    {
                        case 3000:
                           addX = rand() % -2 + 2;
                           addY = 0;
                           break;
                        case 3100:
                           addY = rand() % -2 + 2;
                           addX = 0;
                           break;
                        case 3200:
                           addX = rand() % -2 + 2;
                           addY = rand() % -2 + 2;
                           break;
                    }
                    yc	  = yc + addY;
                    xc	  = xc + addX;
                    temp  = grid_pixel[xc][yc];

                 }

                 crystal_no = temp;


                 cor_j		= int(crystal_no / crystal_pixels_y);
                 cor_i		= int(crystal_no % crystal_pixels_y);



                //edw bazoyme anapoda ta i,j gia na einai idia h eikona me thn gl

                if ((cor_i > 0 || cor_j > 0) && (cor_i < crystal_pixels_y || cor_j < crystal_pixels_x))
                {
                    summed_mat[cor_j][cor_i]++;

                    scaled_energy = int(sum_energy / ADC_chan_energy);


                    if (m_spectIsotope.getType()==1){
                        if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinUpX) * energy_lut2[cor_j][cor_i])
                                && (scaled_energy > (1 - dEnWinLowX) * energy_lut2[cor_j][cor_i]))
                        {
                            summed_energy_mat_x[cor_j][cor_i] = summed_energy_mat_x[cor_j][cor_i] + 1;
                        }
                        if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinUpG) * energy_lut1[cor_j][cor_i])
                                && (scaled_energy > (1 - dEnWinLowG) * energy_lut1[cor_j][cor_i]))
                        {
                            summed_energy_mat_g[cor_j][cor_i] = summed_energy_mat_g[cor_j][cor_i] + 1;
                        }
                        if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinLowXsc) * energy_lutLowSc[cor_j][cor_i])
                                && (scaled_energy > (1 - dEnWinLowXsc) * energy_lutLowSc[cor_j][cor_i]))
                        {
                            summed_energy_mat_x_sclow[cor_j][cor_i] = summed_energy_mat_x_sclow[cor_j][cor_i] + 1;
                        }
                        if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinUpXsc) * energy_lutUpSc[cor_j][cor_i])
                                && (scaled_energy > (1 - dEnWinUpXsc) * energy_lutUpSc[cor_j][cor_i]))
                        {
                            summed_energy_mat_x_scup[cor_j][cor_i] = summed_energy_mat_x_scup[cor_j][cor_i] + 1;

                        }
                    }
                    else if (m_spectIsotope.getType()==2){
                        if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinUpG) * energy_lut1[cor_j][cor_i])
                                && (scaled_energy > (1 - dEnWinLowG) * energy_lut1[cor_j][cor_i]))
                        {
                            summed_energy_mat_g[cor_j][cor_i] = summed_energy_mat_g[cor_j][cor_i] + 1;
                        }


                        if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinUpGsc) * energy_lutUpSc[cor_j][cor_i])
                                && (scaled_energy > (1 - dEnWinUpGsc) * energy_lutUpSc[cor_j][cor_i]))
                        {
                            summed_energy_mat_g_scup[cor_j][cor_i] = summed_energy_mat_g_scup[cor_j][cor_i] + 1;
                        }

                        if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinLowGsc) * energy_lutLowSc[cor_j][cor_i])
                                && (scaled_energy > (1 - dEnWinLowGsc) * energy_lutLowSc[cor_j][cor_i]))
                        {
                            summed_energy_mat_g_sclow[cor_j][cor_i] = summed_energy_mat_g_sclow[cor_j][cor_i] + 1;
                        }

                    }else {
                        if ((scaled_energy > 0) && (scaled_energy < (1 + dEnWinUp) * energy_lut[cor_j][cor_i])
                                && (scaled_energy > (1 - dEnWinLow) * energy_lut[cor_j][cor_i]))
                        {
                            summed_energy_mat[cor_j][cor_i]++;
                        }
                    }




                }
            }
        }
    }
    printf ("end: %lld\n", iCounter);


    if (m_spectIsotope.getType()==1){
        FILE *file_summed_with_energy_image_g           = fopen(floodFile11,"w");
        FILE *file_summed_with_energy_image_x           = fopen(floodFile12,"w");
        FILE *file_summed_with_energy_image_x_sclow     = fopen(floodFileLowSc,"w");
        FILE *file_summed_with_energy_image_x_scup      = fopen(floodFileUpSc,"w");

        for (iCounter = 0; iCounter < crystal_pixels_x; iCounter++)
        {
            for (jCounter = 0; jCounter < crystal_pixels_y; jCounter++)
            {
                fprintf(file_summed_with_energy_image_x, "%d ", summed_energy_mat_x[iCounter][jCounter]);
                fprintf(file_summed_with_energy_image_g, "%d ", summed_energy_mat_g[iCounter][jCounter]);
                fprintf(file_summed_with_energy_image_x_sclow, "%d ", summed_energy_mat_x_sclow[iCounter][jCounter]);
                fprintf(file_summed_with_energy_image_x_scup, "%d ", summed_energy_mat_x_scup[iCounter][jCounter]);
            }

            fprintf(file_summed_with_energy_image_x, "\n");
            fprintf(file_summed_with_energy_image_g, "\n");
            fprintf(file_summed_with_energy_image_x_sclow, "\n");
            fprintf(file_summed_with_energy_image_x_scup, "\n");

        }
        fclose(file_summed_with_energy_image_x);
        fclose(file_summed_with_energy_image_g);
        fclose(file_summed_with_energy_image_x_sclow);
        fclose(file_summed_with_energy_image_x_scup);
    }
    else if (m_spectIsotope.getType()==2){
        FILE *file_summed_with_energy_image_g           = fopen(floodFile11,"w");
        FILE *file_summed_with_energy_image_g_sclow     = fopen(floodFileLowSc,"w");
        FILE *file_summed_with_energy_image_g_scup      = fopen(floodFileUpSc,"w");

        for (iCounter = 0; iCounter < crystal_pixels_x; iCounter++)
        {
            for (jCounter = 0; jCounter < crystal_pixels_y; jCounter++)
            {
                fprintf(file_summed_with_energy_image_g, "%d ", summed_energy_mat_g[iCounter][jCounter]);
                fprintf(file_summed_with_energy_image_g_sclow, "%d ", summed_energy_mat_g_sclow[iCounter][jCounter]);
                fprintf(file_summed_with_energy_image_g_scup, "%d ", summed_energy_mat_g_scup[iCounter][jCounter]);
            }

            fprintf(file_summed_with_energy_image_g, "\n");
            fprintf(file_summed_with_energy_image_g_sclow, "\n");
            fprintf(file_summed_with_energy_image_g_scup, "\n");

        }
        fclose(file_summed_with_energy_image_g);
        fclose(file_summed_with_energy_image_g_sclow);
        fclose(file_summed_with_energy_image_g_scup);
    }else{
        FILE *file_summed_with_energy_image = fopen(floodFileOut,"w");
        for (iCounter = 0; iCounter < crystal_pixels_x; iCounter++)
        {
            for (jCounter = 0; jCounter < crystal_pixels_y; jCounter++)
            {
                fprintf(file_summed_with_energy_image, "%d ", summed_energy_mat[iCounter][jCounter]);
            }
            fprintf(file_summed_with_energy_image, "\n");
        }
        fclose(file_summed_with_energy_image);
//        free(summed_energy_mat);

    }

    printf("Out SUMMED WITH ENERGY ... OK\n");

////////////////////////////////////////////////////////////////////////
///////////////////* Free allocated memory *////////////////////////////
////////////////////////////////////////////////////////////////////////

    free(hex_data); free(x1); free(x2); free(y1); free(y2); free(temp1); free(temp2);
    free(crystal_energies); free(local_crystal_max);

////////////////////////////////////////////////////////////////////////
///////////////////////* Close files *//////////////////////////////////
////////////////////////////////////////////////////////////////////////
    qDebug() << "Not entering here !! "<<endl;

    veyesUtils::delete_2D_array<int>(cog_image,output_size_x);
    veyesUtils::delete_2D_array<int>(summed_mat,crystal_pixels_x);
    veyesUtils::delete_2D_array<int>(summed_energy_mat,crystal_pixels_x);
    veyesUtils::delete_2D_array<int>(summed_energy_mat_x,crystal_pixels_x);
    veyesUtils::delete_2D_array<int>(summed_energy_mat_g,crystal_pixels_x);
    veyesUtils::delete_2D_array<int>(summed_energy_mat_x_sclow,crystal_pixels_x);
    veyesUtils::delete_2D_array<int>(summed_energy_mat_x_scup,crystal_pixels_x);
    veyesUtils::delete_2D_array<int>(summed_energy_mat_g_sclow,crystal_pixels_x);
    veyesUtils::delete_2D_array<int>(summed_energy_mat_g_scup,crystal_pixels_x);


    return;
}


//Here the summed figures are printed
void SPECTworker::print_sum()
{

    cv::Mat matIn=veyesUtils::array2D_to_cvmat(cumulative_corrected,crystal_pixels_x,crystal_pixels_y,mf_decayCorrection());
    cv::Mat matOutFinal=veyesUtils::image_conversion(matIn,m_scale1_x,m_scale1_y,crystal_pixels_x,crystal_pixels_y);
    cv::Mat matOutFinal2=veyesUtils::image_conversion(matIn,m_scale2_x,m_scale2_y,crystal_pixels_x,crystal_pixels_y);

    QString filename = "/SummedCorrectedframe.txt";
    QString total = rawDir + "/CORRECTED" + filename;
    veyesUtils::write_txt_image(total.toStdString(),matOutFinal,m_scale1_x*crystal_pixels_x,m_scale1_y*crystal_pixels_y);

    if(!m_calibrationMode){
        QString fusionOut = "/fussedOpticalSummedImg.png";
        QString fDir = fusionDir;
        fDir.remove("FUSION");
        fDir.append("XRAY");
        std::string xrayFussed = fDir.toStdString()+"/fussedXraySummedImg.png";
        fDir.remove("XRAY");
        fDir.append("FUSION");
        fDir.append(fusionOut);
        std::string fussed = fDir.toStdString();
        cv::Mat fussedSummed = imageFusion::fusion(optical_img, matOutFinal2, lutFilename);
        cv::Mat fussedXraySummed = imageFusion::fusion(xray_img, matOutFinal2, lutFilename);
        cv::imwrite( fussed, fussedSummed );
        cv::imwrite( xrayFussed, fussedXraySummed );
    }

    // Deconvolution starts here!!!!
    double res0 = m_pReadInputInfo->getDeconvRes0(); //  2.2; //resolution at 0mm
    double arg = m_pReadInputInfo->getDeconvArg(); // 0.025;
    int dist1 = m_pReadInputInfo->getDeconvDist1(); // 10; //lower bound of distance from the collimator(mm)
    int dist2 = m_pReadInputInfo->getDeconvDist2(); // 30; //upper bound of distance from the collimator(mm)
    double pixelSize = m_pReadInputInfo->getDeconvPixelSize();// 1.7;

    //For the deconvolution ==> No need since tempCorWithEnrgMat is already deconvoluted
    bioemtec::rlDeconv d(m_scale1_x * crystal_pixels_y,m_scale1_y * crystal_pixels_y, dist1, dist2, res0, arg, pixelSize);


    //Perform the convolution
    cv::Mat outputImageMat;
    int iterations = 8;
    d.deconv(matOutFinal, outputImageMat, iterations, 4, 0);


    filename = "/SummedFinalframe.txt";
    total = m_qsDeconvDir + filename;
    FILE * file = fopen(total.toStdString().c_str(),"w");
    if ( file ){
        for (int i = 0; i < m_scale1_x * crystal_pixels_x; i++){
            for (int j = 0; j < m_scale1_y * crystal_pixels_y; j++)
                fprintf(file, "%f ", tempCorWithEnrgMat[ i ][ j ] );
            fprintf(file, "\n");
        }
        std::fclose( file );
    }

    cv::Mat matInForFusion=veyesUtils::array2D_to_cvmat(tempCorWithEnrgMat,m_scale1_x * crystal_pixels_x,m_scale1_y * crystal_pixels_y,1);

    cv::Mat matOutFinal3(m_scale2_x*crystal_pixels_x,m_scale2_y*crystal_pixels_y, CV_32F);
    cv::Mat matRs=veyesUtils::image_conversion(matInForFusion,m_scale2_x,m_scale2_y,crystal_pixels_x,crystal_pixels_y);

    int gaussFactor=m_pReadInputInfo->getGaussKernel();
    cv::GaussianBlur(matRs,matOutFinal3,cv::Size(gaussFactor,gaussFactor),0);
    if(!m_calibrationMode){
        QString fusionOut = "/finalOpticalSummedImg.png";
        QString fDir = fusionDeconvDir;
        fDir.remove("FUSION");
        fDir.append("XRAY");
        std::string fussedXrayDec = fDir.toStdString()+"/finalXraySummedImg.png";
        fDir.remove("XRAY");
        fDir.append("FUSION");
        fDir.append(fusionOut);
        std::string fussedDec = fDir.toStdString();
        //Not using corrected matrix anymore
        //Replaced with matrix used in fusion summed
        cv::Mat fussedDeconv = imageFusion::fusion(optical_img,matOutFinal3, lutFilename);
        cv::Mat fussedXrayDeconv = imageFusion::fusion(xray_img,matOutFinal3, lutFilename);

        cv::imwrite(fussedDec, fussedDeconv);
        cv::imwrite(fussedXrayDec, fussedXrayDeconv);
    }
    if(m_calibrationMode && !m_validationOn){
        QString number = QString("%1").arg(1, 3, 10, QChar('0'));
        QString rawfile = "/Rawframe" + number + ".txt";
        QString rawFilePath = rawDir + "/LIST_MODE" + rawfile;

        calculate_flood(rawFilePath);
    }

    emit imageFinished();
    matIn.release();
    matOutFinal.release();
    matOutFinal2.release();
    matOutFinal3.release();
}

void SPECTworker::receiveContrast(double _contrast)
{
    QMutexLocker locker(&mutex);
    contrast =_contrast;
}

void SPECTworker::resetAll()
{
    totalNumberOfEvents=0;   
    veyesUtils::clear_2D_array<double>(summed_total,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(summed_total1,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(summed_total2,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(summed_totalUpSc,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(summed_totalLowSc,crystal_pixels_x,crystal_pixels_y);

    veyesUtils::clear_2D_array<double>(cumulative_corrected,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(cumulative_corrected1,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(cumulative_corrected2,crystal_pixels_x,crystal_pixels_y);

    veyesUtils::clear_2D_array<double>(cumulative_correctedUpSc,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(cumulative_correctedLowSc,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(corrected_with_energy_mat,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(corrected_with_energy_mat1,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(corrected_with_energy_mat2,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(corrected_with_energy_matUpSc,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(corrected_with_energy_matLowSc,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(summed_with_energy_mat,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(summed_with_energy_mat1,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(summed_with_energy_mat2,crystal_pixels_x,crystal_pixels_y);

    veyesUtils::clear_2D_array<double>(summed_with_energy_matUpSc,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<double>(summed_with_energy_matLowSc,crystal_pixels_x,crystal_pixels_y);
    veyesUtils::clear_2D_array<int>(currentRawMat,output_size_x,output_size_y);
    for(int i=0;i<output_size_x;i++)
        energy[i] = 0;
}


double SPECTworker::mf_decayCorrection()
{
    //Decay correction
    double dDecay = 0.0;
    double lambda = 0.0;
    double t =  m_qdtInjectionDateTime.secsTo( m_qdtSaveTime );

    if ( m_dActivity < 1.e-10 )
        return 1.0;

    if ( t > 1e-10 ) {
        lambda=m_spectIsotope.getLambda();
    }
    else
        return 1.0;

    dDecay = exp( -lambda*t  );

#ifdef QT_DEBUG
    qDebug()<< "Decay" << 1.0/dDecay << "Time:" << t;
#endif

    return 1.0/dDecay;
}
