#include "headers/castorframe.h"

castorFrame::castorFrame( ReadInputInfo* readInit):
m_castorProc(nullptr), m_castorFilesCreator(nullptr),
m_iPixelsX(120), m_iPixelsY(110), m_iPixelsZ(240), m_iStartSl(25), m_iStopSl(85),
m_bDoDecay(true), m_dlambda(0.0), m_dpreExp(0.0)
{
    QString qsPath = QDir::currentPath();

    qRegisterMetaType<QVector<qreal>>("QVector<qreal>");
    m_img_scale_factor=2.625;

    m_readInfo = readInit;

    m_calibrationFileCastor = qsPath.append("/PET_calibration_files/CASToR/sensitivity_120_110_240_it1.hdr");

    m_castorFilesCreator = new QProcess;
    m_castorProc = new QProcess;


    QString local= QDir::currentPath().append("/colormap/royal.lut");
    m_sLutFilename = local.toStdString();

    input_img=veyesUtils::allocate_3D_array<float>(m_iPixelsX,m_iPixelsY,m_iPixelsZ);
    flipped_img=veyesUtils::allocate_3D_array<float>(m_iPixelsX,m_iPixelsY,m_iPixelsZ);
    final_image=veyesUtils::allocate_2D_array<float>(m_iPixelsX,m_iPixelsZ);
}


castorFrame::~castorFrame()
{
    veyesUtils::delete_3D_array<float>(input_img,m_iPixelsX,m_iPixelsY);
    veyesUtils::delete_3D_array<float>(flipped_img,m_iPixelsX,m_iPixelsY);
    veyesUtils::delete_2D_array<float>(final_image,m_iPixelsX);

    if ( m_castorProc )
        delete m_castorProc;

    if ( m_castorFilesCreator )
        delete m_castorFilesCreator;
}


void castorFrame::setActivityUnit( QString unit ){
    m_sActivityUnit = unit;
}

void castorFrame::setOpticalImg( cv::Mat opticalImg )
{
    m_opticalImg = opticalImg;
}

void castorFrame::setXrayImg( cv::Mat xrayImg )
{
    m_xrayImg = xrayImg;
}

void castorFrame::setOutputPath( QString pathOut )
{
    m_output_path = pathOut;
}

// Set the path where the raw image is stored.
// This changes depending on the number of frame.
void castorFrame::setRawFilePath( QString pathRaw )
{
    m_raw_frame_path = pathRaw;
    QString tempPath = pathRaw;

    //Create the recon folder
    QDir tempReconDir( tempPath.append("/recon") );
    if ( !tempReconDir.exists() )
        tempReconDir.mkdir( tempPath );
}


void castorFrame::createFilesForCastor( QString filename )
{
    QString exeCommands = "./external_code/CastorFilesCreator " + m_raw_frame_path + "/" + filename + " " + m_raw_frame_path;
    m_output_filename = filename;
    m_output_filename = m_output_filename.replace("Raw","Final");

    m_castorFilesCreator->execute( exeCommands );

    QFile frameFile(m_raw_frame_path + "/" + filename);
    if(frameFile.exists()){
        frameFile.remove();
    }
    runCastor();
}

void castorFrame::runCastor()
{
    QString output_path =m_raw_frame_path;
    output_path.append("/recon");

    QString exeCommands = "castor-recon -opti MLEM -proj distanceDriven -it "+m_readInfo->getCastorIter()+":" + m_readInfo->getCastorSubsets() + " -df " +
            m_raw_frame_path + "/header.Cdh -dout " +
            output_path + " -vb 0 -th 0 -dim 120,110,240 -vox 0.41,0.55,0.41 -sens " +
            m_calibrationFileCastor +" -conv gaussian,0.975,0.975,3::psf"  ;

    m_castorProc->execute( exeCommands );
    saveImg();
}


void castorFrame::saveImg()
{
    //Read the header file to find the number of counts
    QString qsFileName = m_raw_frame_path + "/header.Cdh";
    QString qsDataCdfName = m_raw_frame_path + "/data.Cdf";
    QFile dataFile(qsDataCdfName);
    if ( dataFile.open( QIODevice::ReadOnly ) ){
        if ( dataFile.size() == 0)
            return;
    }


    int iNumOfEvents = veyesUtils::read_castor_header(m_raw_frame_path + "/header.Cdh");

    std::string inputImgPath = m_raw_frame_path.toStdString() + "/recon/recon_it1.img";
    FILE* img = fopen( inputImgPath.c_str(), "rb" );

    if ( img == nullptr )
        std::cout << "WARNING: Could not open image in " + inputImgPath << std::endl;

    //Final Image divided/corrected per slice
    veyesUtils::clear_3D_array<float>(input_img,m_iPixelsX,m_iPixelsY,m_iPixelsZ);
    veyesUtils::clear_3D_array<float>(flipped_img,m_iPixelsX,m_iPixelsY,m_iPixelsZ);
    veyesUtils::clear_2D_array<float>(final_image,m_iPixelsX,m_iPixelsZ);


    for ( int i = 0; i< m_iPixelsZ; i++)
        for ( int j = 0; j< m_iPixelsY; j++)
            for (int k = 0; k < m_iPixelsX; k++)
                fread( &input_img[k][j][i], sizeof(float), 1, img);
    fclose( img );


    //Flip the image matrix
    for ( int i = 0; i< m_iPixelsZ; i++)
        for ( int j = 0; j< m_iPixelsY; j++)
            for (int k = 0; k < m_iPixelsX; k++)
                flipped_img [k][j][i] = input_img[ m_iPixelsX - 1 - k][j][i];


    //Produce the final 2d image//
    for ( int i = 0; i< m_iPixelsZ; i++){
        for ( int j = m_iStartSl; j< m_iStopSl; j++){
            for (int k = 0; k < m_iPixelsX; k++){
                final_image [k][i] += flipped_img[k][j][i];
            }
        }
    }

    float image_sum=veyesUtils::sum_2D_array<float>(final_image,m_iPixelsX,m_iPixelsZ);

    float dAlpha=float(iNumOfEvents)/image_sum;

    for (int i = 0; i < m_iPixelsX; i++ ){
        for (int j = 0; j < m_iPixelsZ; j++ ){
            final_image[ i ][ j ]=  final_image[ i ][ j ]*dAlpha;
        }
    }



    //Now everything is set for storing the final image
    QString outputFile = m_output_path + "/" + m_output_filename;
    FILE* output = fopen( outputFile.toStdString().c_str(), "w" );
    if ( output == nullptr ) {
        std::cout << " Could not write final image in " + m_output_path.toStdString() << std::endl;
        return;
    }

    //Create the FUSION images and store them
    //------------------------------------------------------------

    cv::Mat matIn=veyesUtils::array2D_to_cvmat<float>(final_image,m_iPixelsX,m_iPixelsZ,mf_decayCorrection());
    cv::Mat resized_img = veyesUtils::image_conversion(matIn,m_img_scale_factor,m_img_scale_factor,m_iPixelsX,m_iPixelsZ);

    for ( int i = 0; i< m_img_scale_factor*m_iPixelsX; i++){
        for ( int j = 0; j< m_img_scale_factor*m_iPixelsZ; j++)
            fprintf( output, "%f ", resized_img.at<float>(i,j)  );

        fprintf(output, "\n");
    }
    fclose( output );

    QString fileName = m_output_filename.replace("txt", "png");
    QString opticalName = fileName.replace("Finalframe", "FinalframeOptical");
    QString xrayName = fileName.replace("FinalframeOptical", "FinalframeXray");

    cv::Mat fussedSummed = imageFusion::fusion( m_opticalImg, resized_img, m_sLutFilename);
    std::string fussed = m_output_path.toStdString() + "/FUSION" +"/"+ opticalName.toStdString();
    cv::Mat fussedXraySummed = imageFusion::fusion( m_xrayImg, resized_img, m_sLutFilename);
    std::string xrayFussed = m_output_path.toStdString() + "/XRAY" +"/"+ xrayName.toStdString();

    cv::imwrite(fussed,fussedSummed);
    cv::imwrite(xrayFussed,fussedXraySummed);

    matIn.release();
    resized_img.release();
}

void castorFrame::setTime1( double t1 )
{
    m_dt1 = t1;
}

void castorFrame::setdt( double dt )
{
    m_dt = dt;
}

void castorFrame::setActivity( double activity )
{
    m_dActivity = activity;
}

void castorFrame::setNuclideName( QString name )
{
    m_qsNuclideName = name;

    if ( m_qsNuclideName.trimmed().compare("F-18(110 min)") == 0 ){
        m_dlambda = m_readInfo->getF18_lambda(); //sec
        m_dpreExp = m_readInfo->getF18_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Ga-68(68.3 min)") == 0 ){
        m_dlambda = m_readInfo->getGa68_lambda(); //sec
        m_dpreExp = m_readInfo->getGa68_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("C-11(20.4 min)") == 0 ){
        m_dlambda = m_readInfo->getC11_lambda(); //sec
        m_dpreExp = m_readInfo->getC11_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("N-13(10 min)") == 0 ){
        m_dlambda = m_readInfo->getN13_lambda(); //sec
        m_dpreExp = m_readInfo->getN13_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("O-15(2.03 min)") == 0 ){
        m_dlambda = m_readInfo->getO15_lambda(); //sec
        m_dpreExp = m_readInfo->getO15_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Cu-62(9.73 min)") == 0 ) {
        m_dlambda = m_readInfo->getCu62_lambda(); //sec
        m_dpreExp = m_readInfo->getCu62_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Cu-64(12.7 h)") == 0 ) {
        m_dlambda = m_readInfo->getCu64_lambda(); //sec
        m_dpreExp = m_readInfo->getCu64_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Zr-89(74.8 h)") == 0 ) {
        m_dlambda = m_readInfo->getZr89_lambda(); //sec
        m_dpreExp = m_readInfo->getZr89_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Rb-82(1.25 min)") == 0 ) {
        m_dlambda = m_readInfo->getRb82_lambda(); //sec
        m_dpreExp = m_readInfo->getRb82_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("I-124(4.2 days)") == 0 ) {
        m_dlambda = m_readInfo->getI124_lambda(); //sec
        m_dpreExp = m_readInfo->getI124_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Br-76(16.3 h)") == 0 ) {
        m_dlambda = m_readInfo->getBr76_lambda(); //sec
        m_dpreExp = m_readInfo->getBr76_preExp();
    }
    else if ( m_qsNuclideName.trimmed().compare("Tb-152(17.5 h)") == 0 ) {
        m_dlambda = m_readInfo->getTb152_lambda(); //sec
        m_dpreExp = m_readInfo->getTb152_preExp();
    }
}

void castorFrame::doDecay( bool decay ) {
    m_bDoDecay = decay;
}

float castorFrame::mf_countsToActivity( float x ){
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

        //        if ( A > 0. && A <= m_readInfo->getNuclide_lim1() && x > 0 ){
        if ( m_fCounts < 351 )
            return x;
        return ( m_readInfo->getNuclide_a1()*x + m_readInfo->getNuclide_b1() );
    }

    return x;
}

float castorFrame::mf_activityToCounts( float y ){
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
        return ( ( y - m_readInfo->getNuclide_b1() )/m_readInfo->getNuclide_a1() );
    }

    return y;
}

void castorFrame::setInjectionTime(QDateTime inject ){
    m_qdtInjectionTime = inject;
}

float castorFrame::mf_decayCorrection()
{
    double t = 0.0;
    if ( m_dActivity < 1.e-10 )
        return 1.0;

    //Convert always to uCi to check
    double A = 0.0;
    if ( m_readInfo->useExpDecay() ){
        if ( m_bDoDecay ){
            t = m_qdtInjectionTime.secsTo( QDateTime().currentDateTime() );

            if ( m_sActivityUnit == "MBq")
                A = 27.027*m_dpreExp*exp( -m_dlambda*t );
            else
                A = m_dpreExp*exp( -m_dlambda*t );

            if ( A > m_readInfo->getNuclide_lim3() ) return 1.0;

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






