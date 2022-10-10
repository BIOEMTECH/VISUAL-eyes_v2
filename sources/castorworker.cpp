#include "headers/castorworker.h"
#include <QApplication>

CastorWorker::CastorWorker( ReadInputInfo* readInitInput ):
    dMaxCor( 0.0 ),m_iPixelsX(120), m_iPixelsY(110), m_iPixelsZ(240),
    m_bFinishedSummed(false), m_iStartSl(25), m_iStopSl(85), m_bDoDecay(true), m_dlambda(0.0), m_dpreExp(0.0)
{
    QString qsPath = QDir::currentPath();

    qRegisterMetaType<QVector<qreal>>("QVector<qreal>");
    m_img_scale_factor=2.625;

    m_pReadInfo = readInitInput;

    m_qsCalibrFileCastor = qsPath.append("/PET_calibration_files/CASToR/sensitivity_120_110_240_it1.hdr");

    m_pCastorProcSummed = new QProcess;
    m_procCastorFilesCreatorSummed = new QProcess;




    input_summed_img=veyesUtils::allocate_3D_array<float>(m_iPixelsX,m_iPixelsY,m_iPixelsZ);
    flipped_img=veyesUtils::allocate_3D_array<float>(m_iPixelsX,m_iPixelsY,m_iPixelsZ);
    final_image_norm=veyesUtils::allocate_2D_array<float>(m_iPixelsX,m_iPixelsZ);


    QString local= QDir::currentPath().append("/colormap/royal.lut");
    m_sLutFilename = local.toStdString();
}

CastorWorker::~CastorWorker()
{

    veyesUtils::delete_3D_array<float>(input_summed_img,m_iPixelsX,m_iPixelsY);
    veyesUtils::delete_3D_array<float>(flipped_img,m_iPixelsX,m_iPixelsY);
    veyesUtils::delete_2D_array<float>(final_image_norm,m_iPixelsX);

    if ( m_pCastorProcSummed )
        delete m_pCastorProcSummed;

    if ( m_procCastorFilesCreatorSummed )
        delete m_procCastorFilesCreatorSummed;

    if ( m_SummedFile )
        m_SummedFile=nullptr;
        //fclose( m_SummedFile );
}
void CastorWorker::clearFilePaths()
{
    m_qsSummedRawPath.clear();
    m_qsFileName.clear();
    m_qsOutputPath.clear();
}

void CastorWorker::setActivityUnit( QString unit ){
    m_sActivityUnit = unit;
}

void CastorWorker::setOpticalImg( cv::Mat opticalImg )
{
    m_mOpticalImg = opticalImg;
}

void CastorWorker::setXrayImg( cv::Mat xrayImg )
{
    m_mXrayImg = xrayImg;
}

void CastorWorker::setSummedRawPath( QString pathSummedRaw )
{
    m_qsSummedRawPath = pathSummedRaw;
    m_qsSummedRawPath.append("/Summed");

    QDir tempSummedDir( m_qsSummedRawPath );
    if ( !tempSummedDir.exists() ){
        tempSummedDir.mkdir( m_qsSummedRawPath );
    }

    QString tempPath = m_qsSummedRawPath;
    //Create the recon folder for summed
    QDir tempReconDir( tempPath.append("/recon") );
    if ( !tempReconDir.exists() )
        tempReconDir.mkdir( tempPath );

    // check if path exists and if yes: Is it a file and no directory?
    QString finalPathSummedRaw = pathSummedRaw + "/Summed/RawSummed.txt";
    bool fileExists = QFileInfo::exists( finalPathSummedRaw) && QFileInfo( finalPathSummedRaw ).isFile();
    if ( !fileExists )
        m_SummedFile = fopen( finalPathSummedRaw.toStdString().c_str(),"w" );
    else {
        QFile::remove( finalPathSummedRaw );
        m_SummedFile = fopen( finalPathSummedRaw.toStdString().c_str(),"w" );
    }
}


void CastorWorker::setOutputFilePath( QString pathOut )
{
    m_qsOutputPath = pathOut;
}


void CastorWorker::saveImgSummed()
{
    QString exeCommands = "./external_code/CastorFilesCreator " + m_qsSummedRawPath + "/RawSummed.txt " + m_qsSummedRawPath;
    m_procCastorFilesCreatorSummed->execute( exeCommands );
    runCastorForSummed();
}

void CastorWorker::runCastorForSummed()
{
    m_bFinishedSummed = false;
    QString outPath = m_qsSummedRawPath;
    outPath.append("/recon");

    QString exeCommands = "castor-recon -opti MLEM -proj distanceDriven -it "+m_pReadInfo->getCastorIter()+":" + m_pReadInfo->getCastorSubsets() + " -df " +
            m_qsSummedRawPath + "/header.Cdh -dout " +
            outPath + " -vb 0 -th 0 -dim 120,110,240 -vox 0.41,0.55,0.41 -sens " +
            m_qsCalibrFileCastor+ " -conv gaussian,0.975,0.975,3::psf";

    m_pCastorProcSummed->execute( exeCommands );
    computeSummedImg();
    m_bFinishedSummed = true;
    emit sumImgComputed( qvSummedImgFinal);
}

void CastorWorker::computeSummedImg()
{
    // Check if the we read ...
    QString qsDataCdfName = m_qsSummedRawPath + "/data.Cdf";
    QFile dataFile(qsDataCdfName);
    QString headerFileName=m_qsSummedRawPath+"/header.Cdh";
    QFile headerFile(headerFileName);

    /*if ( dataFile.open( QIODevice::ReadOnly ) ){
        dataFile.flush();
        if ( dataFile.size() == 0){

            //--------- Create the Fussed Image -----------m_qsSummedRawPath----------------------------------------------------//
            cv::Mat matInSummed=veyesUtils::array2D_to_cvmat<float>(final_image_norm,m_iPixelsX,m_iPixelsZ,mf_decayCorrection());
            cv::Mat resized_img = veyesUtils::image_conversion(matInSummed,m_img_scale_factor,m_img_scale_factor,m_iPixelsX,m_iPixelsZ);

            mFussedImg = imageFusion::fusion( m_mOpticalImg, resized_img, m_sLutFilename);
            //--------- Create the Fussed Image ---------------------------------------------------------------//

            std::string fussed = m_qsOutputPath.toStdString() + "/FUSION/FinalOpticalSummed.png";
            if ( QFile::exists(  QString::fromStdString( fussed ) ) )
                QFile::remove( QString::fromStdString( fussed ) );
            cv::imwrite(fussed, mFussedImg);

            qDebug() << "Creating fussed image!!" << QTime::currentTime() << endl;


            //--------- Create the Xray Fussed Image ---------------------------------------------------------------//

            mXrayFussedImg = imageFusion::fusion( m_mXrayImg, resized_img, m_sLutFilename);

            std::string xrayFussed = m_qsOutputPath.toStdString() + "/XRAY/FinalXraySummed.png";
            if ( QFile::exists(  QString::fromStdString( xrayFussed ) ) )
                QFile::remove( QString::fromStdString( xrayFussed ) );
            cv::imwrite(xrayFussed, mXrayFussedImg);

            std::cout << "Something is wrong with the number of events in the summed image. Check data.Cdf file." << std::endl;
            return;
        }
    } else {
        std::cout << "Could not open " + m_qsSummedRawPath.toStdString() + "/data.Cdf file." << std::endl;
        return;
    }*/

    /*QString qsRawFileName = m_qsSummedRawPath + "/RawSummed.txt";
    QFile rawFile(qsRawFileName);

    if ( rawFile.open( QIODevice::ReadOnly ) ){
        rawFile.flush();
        if ( rawFile.size() == 0){
            std::cout << "Something is wrong with the number of events in the summed image. Check RawSummed.txt file." << std::endl;
            return;
        }
    }
    else {
        std::cout << "Could not open " + m_qsSummedRawPath.toStdString() + "/RawSummed.txt file." << std::endl;
        return;
    }*/

    //Read the header file to find the number of counts
    int iNumOfEvents = veyesUtils::read_castor_header(m_qsSummedRawPath+"/header.Cdh");

    std::string inputImgPath = m_qsSummedRawPath.toStdString() + "/recon/recon_it1.img";
    FILE* img = fopen( inputImgPath.c_str(), "rb" );

    if ( img == nullptr ) {
        std::cout << " Could not open image in " + inputImgPath << std::endl;
        return;
    }
    veyesUtils::clear_3D_array(input_summed_img,m_iPixelsX,m_iPixelsY,m_iPixelsZ);
    veyesUtils::clear_3D_array(flipped_img,m_iPixelsX,m_iPixelsY,m_iPixelsZ);
    veyesUtils::clear_2D_array(final_image_norm,m_iPixelsX,m_iPixelsZ);

    //read the binary file produced by Castor
    //This is how matlab stores the image matrix
    for ( int i = 0; i< m_iPixelsZ; i++)
        for ( int j = 0; j< m_iPixelsY; j++)
            for (int k = 0; k < m_iPixelsX; k++)
                fread( &input_summed_img[k][j][i], sizeof(float), 1, img);
    fclose( img );


    //Flip the image matrix
    for ( int i = 0; i< m_iPixelsX; i++)
        for ( int j = 0; j< m_iPixelsY; j++)
            for (int k = 0; k < m_iPixelsZ; k++)
                flipped_img[i][j][k] = input_summed_img[m_iPixelsX-1-i][j][k];



    //Produce the final 2d image//
    for ( int i = 0; i< m_iPixelsX; i++){
        for ( int j = m_iStartSl; j< m_iStopSl; j++){
            for (int k = 0; k < m_iPixelsZ; k++){
                final_image_norm[i][k] += flipped_img[i][j][k];
            }
        }
    }

    float sum=veyesUtils::sum_2D_array<float>(final_image_norm,m_iPixelsX,m_iPixelsZ);
    float dAlpha=float(iNumOfEvents)/sum;

    for (int i = 0; i < m_iPixelsX; i++ ){
        for (int k = 0; k < m_iPixelsZ; k++ ){
            final_image_norm[i][k] = final_image_norm[i][k]*dAlpha; //uint32_t( round( Final_Image[ k ][ i ]*dAlpha ) );
        }
    }


    //Now everything is set for storing the final image
    QString outputFile = m_qsOutputPath + "/" + "FinalSummed.txt";
    FILE* output = fopen( outputFile.toStdString().c_str(), "w" );

    if ( output == nullptr ) {
        std::cout << " Could not write final image in " + m_qsOutputPath.toStdString() << std::endl;
        return;
    }


    cv::Mat matIn= veyesUtils::array2D_to_cvmat<float>(final_image_norm,m_iPixelsX,m_iPixelsZ,mf_decayCorrection());
    cv::Mat resized_img = veyesUtils::image_conversion(matIn,m_img_scale_factor,m_img_scale_factor,m_iPixelsX,m_iPixelsZ);


    for ( int i = 0; i< m_img_scale_factor*m_iPixelsX; i++){
        for ( int j = 0; j< m_img_scale_factor*m_iPixelsZ; j++)
            fprintf(output, "%f ", resized_img.at<float>(i,j) );
        fprintf(output, "\n");
    }
    fclose( output );

    matIn.release();
    resized_img.release();



    qvSummedImgFinal.clear();
    dMaxCor = 0.0;
    for (int i = 0; i < m_iPixelsX; i++){
        for(int j = 0; j <  m_iPixelsZ; j++){
            if( double( final_image_norm[i][j]) > dMaxCor)
                dMaxCor=double( final_image_norm[i][j] );
            qvSummedImgFinal.append( final_image_norm[ i ][ j ] );
        }
    }

    dataFile.remove();
    headerFile.remove();


    //--------- Resize image castor PET -----------m_qsSummedRawPath----------------------------------------------------//
    cv::Mat matInSummed=veyesUtils::array2D_to_cvmat(final_image_norm,m_iPixelsX,m_iPixelsZ,mf_decayCorrection());
    resized_img = veyesUtils::image_conversion(matInSummed,m_img_scale_factor,m_img_scale_factor,m_iPixelsX,m_iPixelsZ);


    mFussedImg = imageFusion::fusion( m_mOpticalImg, resized_img, m_sLutFilename);
    //--------- Create the Fussed Image ---------------------------------------------------------------//
    std::string fussed = m_qsOutputPath.toStdString() + "/FUSION/FinalOpticalSummed.png";
    if ( QFile::exists(  QString::fromStdString( fussed ) ) )
        QFile::remove( QString::fromStdString( fussed ) );
    cv::imwrite(fussed, mFussedImg);



    mXrayFussedImg = imageFusion::fusion( m_mXrayImg, resized_img, m_sLutFilename);
    //--------- Create the Fussed Image ---------------------------------------------------------------//
    std::string xrayFussed = m_qsOutputPath.toStdString() + "/XRAY/FinalXraySummed.png";
    if ( QFile::exists(  QString::fromStdString( xrayFussed ) ) )
        QFile::remove( QString::fromStdString( xrayFussed ) );
    cv::imwrite(xrayFussed, mXrayFussedImg);
    qDebug() << "summed computed" << endl;
}


void CastorWorker::setTime1( double t1 )
{
    m_dt1 = t1;
}

void CastorWorker::setdt( double dt )
{
    m_dt = dt;
}

void CastorWorker::setActivity( double activity )
{
    m_dActivity = activity;
}

void CastorWorker::setNuclideName( QString name )
{
    m_qsNuclideName = name;

    if ( m_qsNuclideName.trimmed().compare("F-18(110 min)") == 0 ){
        m_dlambda = m_pReadInfo->getF18_lambda(); //sec
        m_dpreExp = m_pReadInfo->getF18_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Ga-68(68.3 min)") == 0 ){
        m_dlambda = m_pReadInfo->getGa68_lambda(); //sec
        m_dpreExp = m_pReadInfo->getGa68_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("C-11(20.4 min)") == 0 ){
        m_dlambda = m_pReadInfo->getC11_lambda(); //sec
        m_dpreExp = m_pReadInfo->getC11_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("N-13(10 min)") == 0 ){
        m_dlambda = m_pReadInfo->getN13_lambda(); //sec
        m_dpreExp = m_pReadInfo->getN13_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("O-15(2.03 min)") == 0 ){
        m_dlambda = m_pReadInfo->getO15_lambda(); //sec
        m_dpreExp = m_pReadInfo->getO15_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Cu-62(9.73 min)") == 0 ) {
        m_dlambda = m_pReadInfo->getCu62_lambda(); //sec
        m_dpreExp = m_pReadInfo->getCu62_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Cu-64(12.7 h)") == 0 ) {
        m_dlambda = m_pReadInfo->getCu64_lambda(); //sec
        m_dpreExp = m_pReadInfo->getCu64_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Zr-89(74.8 h)") == 0 ) {
        m_dlambda = m_pReadInfo->getZr89_lambda(); //sec
        m_dpreExp = m_pReadInfo->getZr89_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Rb-82(1.25 min)") == 0 ) {
        m_dlambda = m_pReadInfo->getRb82_lambda(); //sec
        m_dpreExp = m_pReadInfo->getRb82_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("I-124(4.2 days)") == 0 ) {
        m_dlambda = m_pReadInfo->getI124_lambda(); //sec
        m_dpreExp = m_pReadInfo->getI124_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Br-76(16.3 h)") == 0 ) {
        m_dlambda = m_pReadInfo->getBr76_lambda(); //sec
        m_dpreExp = m_pReadInfo->getBr76_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Tb-152(17.5 h)") == 0 ) {
        m_dlambda = m_pReadInfo->getTb152_lambda(); //sec
        m_dpreExp = m_pReadInfo->getTb152_preExp();
    }
}

void CastorWorker::doDecay( bool decay ) {
    m_bDoDecay = decay;
}

float CastorWorker::mf_countsToActivity( float x ){
    if ( m_dActivity < 1.e-10 || x == 0)
        return x;

    if ( m_bDoDecay ){
        m_fCounts = x;

        //Convert always to uCi to check
        double A = 0.0;
        if ( m_sActivityUnit == "MBq")
            A = 27.027*m_dActivity*( 1. - exp( -m_dlambda*m_dt )  ) / ( exp( m_dlambda*m_dt1 )*m_dlambda*m_dt );
        else
            A = m_dActivity*( 1. - exp( -m_dlambda*m_dt )  ) / ( exp( m_dlambda*m_dt1 )*m_dlambda*m_dt );

        //        if ( A > 0. && A <= m_pReadInfo->getNuclide_lim1() && x > 0 ){
        if ( m_fCounts < 351 )
            return x;
        return ( m_pReadInfo->getNuclide_a1()*x + m_pReadInfo->getNuclide_b1() );
    }

    return x;
}

float CastorWorker::mf_activityToCounts( float y ){
    if ( m_dActivity < 1.e-10 || m_fCounts == 0 )
        return y;

    if ( m_bDoDecay ){
        //Convert always to uCi to check
        double A = 0.0;
        if ( m_sActivityUnit == "MBq")
            A = 27.027*m_dActivity*( 1. - exp( -m_dlambda*m_dt )  ) / ( exp( m_dlambda*m_dt1 )*m_dlambda*m_dt );
        else
            A = m_dActivity*( 1. - exp( -m_dlambda*m_dt )  ) / ( exp( m_dlambda*m_dt1 )*m_dlambda*m_dt );

        if ( m_fCounts < 351 )
            return y;
        return ( ( y - m_pReadInfo->getNuclide_b1() )/m_pReadInfo->getNuclide_a1() );
    }

    return y;
}

void CastorWorker::setInjectionTime(QDateTime inject ){
    m_qdtInjectionTime = inject;
}

float CastorWorker::mf_decayCorrection()
{
    double t = 0.0;
    if ( m_dActivity < 1.e-10 )
        return 1.0;

    //Convert always to uCi to check
    double A = 0.0;
    if ( m_pReadInfo->useExpDecay() ){
        if ( m_bDoDecay ){
            t = m_qdtInjectionTime.secsTo( QDateTime().currentDateTime() );

            if ( m_sActivityUnit == "MBq")
                A = 27.027*m_dpreExp*exp( -m_dlambda*t );
            else
                A = m_dpreExp*exp( -m_dlambda*t );

            if ( A > m_pReadInfo->getNuclide_lim3() ) return 1.0;

#ifdef QT_DEBUG
            qDebug()<< "Castor Decay" << A << "t: " << t;
#endif
            if ( t > 1e-13 )
                return A;
        }
        else
            return 1.0;
    }
    else {
        if ( m_bDoDecay ){
            if ( m_sActivityUnit == "MBq")
                A = 27.027*m_dActivity*( 1. - exp( -m_dlambda*m_dt )  ) / ( exp( m_dlambda*m_dt1 )*m_dlambda*m_dt );
            else
                A = m_dActivity*( 1. - exp( -m_dlambda*m_dt )  ) / ( exp( m_dlambda*m_dt1 )*m_dlambda*m_dt );

#ifdef QT_DEBUG
            qDebug()<< "Castor Decay" << exp( m_dlambda*m_dt1 )*m_dlambda*m_dt /( 1. - exp( -m_dlambda*m_dt ) ) << "t1: " << m_dt1 << "dt: " << m_dt;
#endif

            if ( m_dt1 > 1e-13 )
                return exp( m_dlambda*m_dt1 )*m_dlambda*m_dt /( 1. - exp( -m_dlambda*m_dt )  );
            else
                return 1.0;
        }
        else
            return 1.0;
    }

    return 1.0;
}






