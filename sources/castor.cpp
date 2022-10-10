#include "headers/castor.h"

castor::castor( ReadInputInfo* readInit, bool calibrationMode, bool validationOn):
m_castorProc(nullptr), m_castorFilesCreator(nullptr), m_finishedSummed(false),
m_bDoDecay(true), m_dlambda(0.0), m_dpreExp(0.0), m_calibrationMode(calibrationMode), m_validationOn(validationOn)
{
    qRegisterMetaType<QVector<qreal>>("QVector<qreal>");
    m_readInfo = readInit;
    m_frameCounter=0;

    m_calibrationFileCastor = QDir::currentPath().append("/PET_calibration_files/CASToR/Flood22_31_1it8sub_sensitivity.hdr");

    m_castorFilesCreator = new QProcess;
    m_castorProc = new QProcess;

    QString castorFloodPath = m_calibrationFileCastor;
    castorFloodPath.remove("/Flood22_31_1it8sub_sensitivity.hdr");
    castorFloodPath.append( "/" + m_readInfo->getCastorFloodFileName() );


    m_lutFilename = QDir::currentPath().append("/colormap/royal.lut").toStdString();

    flood_img=veyesUtils::allocate_3D_array<float>(pixels_X,pixels_Y,pixels_Z);
    veyesUtils::clear_3D_array<float>(flood_img,pixels_X,pixels_Y,pixels_Z);
    veyesUtils::read_img(castorFloodPath.toStdString(),flood_img,pixels_X,pixels_Y,pixels_Z);

    flipped_flood=veyesUtils::allocate_3D_array<float>(pixels_X,pixels_Y,pixels_Z);
    veyesUtils::clear_3D_array<float>(flipped_flood,pixels_X,pixels_Y,pixels_Z);

    for ( int i = 0; i< pixels_Z; i++)
        for ( int j = 0; j< pixels_Y; j++)
            for (int k = 0; k < pixels_X; k++)
                flipped_flood[k][j][i] = flood_img[pixels_X-1-k][j][i];


    veyesUtils::delete_3D_array<float>(flood_img,pixels_X,pixels_Y);
    input_img=veyesUtils::allocate_3D_array<float>(pixels_X,pixels_Y,pixels_Z);
    flipped_img=veyesUtils::allocate_3D_array<float>(pixels_X,pixels_Y,pixels_Z);
    corrected_img=veyesUtils::allocate_3D_array<float>(pixels_X,pixels_Y,pixels_Z);
    final_image=veyesUtils::allocate_2D_array<float>(pixels_X,pixels_Z);
    summed_image=veyesUtils::allocate_2D_array<float>(pixels_X,pixels_Z);
    veyesUtils::clear_2D_array<float>(summed_image,pixels_X,pixels_Z);
}

castor::~castor()
{
    qDebug() << "Exiting castor .... " << endl;
    veyesUtils::delete_3D_array<float>(flipped_flood,pixels_X,pixels_Y);
    veyesUtils::delete_3D_array<float>(input_img,pixels_X,pixels_Y);
    veyesUtils::delete_3D_array<float>(corrected_img,pixels_X,pixels_Y);
    veyesUtils::delete_3D_array<float>(flipped_img,pixels_X,pixels_Y);
    veyesUtils::delete_2D_array<float>(final_image,pixels_X);
    veyesUtils::delete_2D_array<float>(summed_image,pixels_X);

    if(m_castorProc){
        qDebug() << "deleting castor proc" << endl;
        delete m_castorProc;
    }


    if(m_castorFilesCreator)
        delete m_castorFilesCreator;
}

void castor::setActivityUnit( QString unit ){
    m_sActivityUnit = unit;
}

void castor::setOpticalImg( cv::Mat opticalImg )
{
    m_opticalImg = opticalImg;
}

void castor::setXrayImg( cv::Mat xrayImg )
{
    m_xrayImg = xrayImg;
}

void castor::setFrameStop(int frame_stop){
    m_frameStop = frame_stop;
}

void castor::setOutputPath( QString pathOut )
{
    m_output_filepath = pathOut;
}

void castor::setRawFilePath( QString pathRaw )
{
    m_raw_filepath = pathRaw;
    QString tempPath = pathRaw;
    //Create the recon folder
    QDir tempReconDir( tempPath.append("/recon") );
    if ( !tempReconDir.exists() )
        tempReconDir.mkdir( tempPath );
}

void castor::setSumRawFilePath( QString pathSumRaw )
{
    m_sum_filepath =pathSumRaw;

}


void castor::createFilesForCastor(QString filename)
{
    QTime myTimer;
    myTimer.start();

    m_frameCounter++;
    qDebug() << m_frameCounter <<endl;
    QString exeCommands = "./external_code/CastorFilesCreator " + m_raw_filepath + "/" + filename + " " + m_raw_filepath;
    m_output_filename = filename;
    m_output_filename = m_output_filename.replace("Raw","Final");
    m_output_filename = m_output_filename.replace("bdat","txt");

    m_castorFilesCreator->execute( exeCommands );
    int nMilliseconds = myTimer.elapsed();
    qDebug() << "elapsed time cfc milli " << nMilliseconds;
    runCastor();

    if(!m_readInfo->getPrintMode()){

        QFile frameFile(m_raw_filepath + "/" + filename);
        if(frameFile.exists()){
            frameFile.remove();
        }
        if (m_frameCounter==m_frameStop) {
            QFile sumFile(m_sum_filepath + "/RawSummed.bdat");
            if(sumFile.exists()){
                sumFile.remove();
            }
        }
    }

}

void castor::runCastor()
{
    QTime myTimer;
    myTimer.start();
    m_finishedSummed=false;
    QString output_path =m_raw_filepath;
    output_path.append("/recon");

    QString exeCommands = "castor-recon -opti MLEM -proj distanceDriven -it "+m_readInfo->getCastorIter()+":" + m_readInfo->getCastorSubsets() + " -df " +
            m_raw_filepath + "/header.Cdh -dout " +
            output_path + " -vb 0 -th 0 -sens " +
            m_calibrationFileCastor +" -conv gaussian,1.2,1.2,4::sieve"  ;
    m_castorProc->execute( exeCommands );
    int nMilliseconds = myTimer.elapsed();
    qDebug() << "elapsed time castor milli " << nMilliseconds;
    myTimer.start();
    saveImg();
    nMilliseconds = myTimer.elapsed();
    qDebug() << "elapsed time image milli " << nMilliseconds;

    m_finishedSummed = true;
    emit sumImgComputed(summedImgFinal);

}


void castor::saveImg()
{
    //Read the header file to find the number of counts
    QString qsFileName = m_raw_filepath + "/header.Cdh";
    QString qsDataCdfName = m_raw_filepath + "/data.Cdf";
    QFile dataFile(qsDataCdfName);
    QFile headerFile(qsFileName);
    if ( dataFile.open( QIODevice::ReadOnly ) ){
        if ( dataFile.size() == 0)
            return;
    }


    int iNumOfEvents = veyesUtils::read_castor_header(m_raw_filepath + "/header.Cdh");

    //Final Image divided/corrected per slice
    veyesUtils::clear_3D_array<float>(input_img,pixels_X,pixels_Y,pixels_Z);
    veyesUtils::clear_3D_array<float>(flipped_img,pixels_X,pixels_Y,pixels_Z);
    veyesUtils::clear_3D_array<float>(corrected_img,pixels_X,pixels_Y,pixels_Z);
    veyesUtils::clear_2D_array<float>(final_image,pixels_X,pixels_Z);

    std::string input_imgpath = m_raw_filepath.toStdString() + "/recon/recon_it1.img";

    if(m_calibrationMode && !m_validationOn){
        write_flood(m_raw_filepath+"/recon/recon_it1.img");
    }

    veyesUtils::read_img(input_imgpath,input_img,pixels_X,pixels_Y,pixels_Z);


    //Flip the image matrix
    for ( int i = 0; i< pixels_Z; i++)
        for ( int j = 0; j< pixels_Y; j++)
            for (int k = 0; k < pixels_X; k++)
                flipped_img [k][j][i] = input_img[ pixels_X-1-k][j][i];




    float sum_image[pixels_Y], sum_flood[pixels_Y], mean_image[pixels_Y], mean_flood[pixels_Y];

    for (int i = 0; i < pixels_Y; i++){
        sum_image[i] = 0;
        sum_flood[i] = 0;
        mean_image[i] = 0;
        mean_flood[i] = 0;
    }


    //Compute the mean value for each slice of the image and the flood image//
    for ( int i = 0; i< pixels_Z; i++){
        for ( int j = 0; j< pixels_Y; j++){
            for (int k = 0; k < pixels_X; k++){
                sum_image[j] = flipped_img[k][j][i] + sum_image[j];
                sum_flood[j] = flipped_flood[k][j][i] + sum_flood[j];
            }
        }
    }
    for ( int j = 0; j< pixels_Y; j++){
        mean_image[j] = sum_image[j] / float(pixels_X*pixels_Z);
        mean_flood[j] = sum_flood[j] / float(pixels_X*pixels_Z);
    }

    veyesUtils::img_smoothing(flipped_img,flipped_flood,mean_image,mean_flood,pixels_X,pixels_Y,pixels_Z);
    veyesUtils::img_smoothing(flipped_img,flipped_flood,mean_image,mean_flood,pixels_X,pixels_Y,pixels_Z);


    //Set the pixels of the contour to zero//

    for ( int i = 0; i< pixels_Z; i++){
        for ( int j = 0; j< pixels_Y; j++){
            flipped_img[0][j][i]=0;
            flipped_flood[0][j][i]=0;
            flipped_img[pixels_X-1][j][i]=0;
            flipped_flood[pixels_X-1][j][i]=0;
        }
    }

    for ( int k = 0; k< pixels_X; k++){
        for ( int j = 0; j< pixels_Y; j++){
            flipped_img[k][j][0]=0;
            flipped_flood[k][j][0]=0;
            flipped_img[k][j][pixels_Z-1]=0;
            flipped_flood[k][j][pixels_Z-1]=0;
        }
    }



    for ( int i = 0; i< pixels_Z; i++){
        for ( int j = 0; j< pixels_Y; j++){
            for (int k = 0; k < pixels_X; k++){
                if ((flipped_img[k][j][i] > (mean_image[j]/2)) && (flipped_flood[k][j][i] > (mean_flood[j]/2))){
                    corrected_img[k][j][i]=mean_flood[j]*(flipped_img[k][j][i] / flipped_flood[k][j][i]);
                }
                else{
                    corrected_img[k][j][i]=flipped_img[k][j][i];
                }
            }
        }
    }

    //Produce the final 2d image//
    for ( int i = 0; i< pixels_Z; i++){
        for ( int j = start_slice; j< pixels_Y; j++){
            for (int k = 0; k < pixels_X; k++){
                final_image[k][i] += corrected_img[k][j][i];
            }
        }
    }






    float sum = veyesUtils::sum_2D_array(final_image,pixels_X,pixels_Z);
    float mean = sum/float(pixels_X*pixels_Z);





    for ( int i = 1; i< pixels_Z-1; i++){
            for (int k = 1; k < pixels_Y-1; k++){
                if (((i < 5) || (i > pixels_Z-5)) || ((k < 5) || (k >pixels_X-5))){
                    if (final_image[k][i] > 10*mean){
                        final_image[k][i] = (final_image[k-1][i]+ final_image[k-1][i+1]
                                            + final_image[k-1][i-1] + final_image[k][i-1]
                                            + final_image[k][i+1] + final_image[k+1][i]
                                            + final_image[k+1][i+1] + final_image[k+1][i-1])/8;
                    }
                }
            }
    }



    sum = veyesUtils::sum_2D_array(final_image,pixels_X,pixels_Z);
    float dAlpha=float(iNumOfEvents)/sum;

    for (int i = 0; i < pixels_Z; i++ ){
        for (int k = 0; k < pixels_X; k++ ){
            final_image[k][i] = final_image[k][i]*dAlpha;
        }
    }



    for ( int i = 1; i< pixels_Z-1; i++){
            for (int k = 1; k < pixels_X-1; k++){
                    if ((final_image[k][i] > 0) && (final_image[k-1][i] == 0) && (final_image [ k-1 ][ i+1 ] == 0) &&
                    (final_image[k-1][ i-1 ] == 0) && (final_image[ k ][ i-1 ] == 0) && (final_image [ k ][ i+1 ] == 0) &&
                    (final_image[k+1][i] == 0) && (final_image[k+1][i+1] == 0) && (final_image [ k+1 ][ i-1 ] == 0))
                    {
                        final_image[ k ][ i ] = 0;
                    }
                    else if ((final_image[ k ][ i ] > 0) && (final_image[ k-1 ][ i ] > 0) && (final_image[ k-1 ][ i+1 ] == 0) &&
                    (final_image[ k-1 ][ i-1 ] == 0) && (final_image[ k ][ i-1 ] == 0) && (final_image[ k ][ i+1 ] == 0) &&
                    (final_image[ k+1 ][ i ] == 0) && (final_image[ k+1 ][ i+1 ] == 0) && (final_image[ k+1 ][ i-1 ] == 0))
                    {
                        final_image[ k ][ i ] = 0;
                        final_image[ k-1 ][ i ] = 0;
                    }
                    else if ((final_image[ k ][ i ] > 0) && (final_image[ k-1 ][ i ] == 0) && (final_image[ k-1 ][ i+1 ] > 0) &&
                    (final_image[ k-1 ][ i-1 ] == 0) && (final_image[ k ][ i-1 ] == 0) && (final_image[ k ][ i+1 ] == 0) &&
                    (final_image[ k+1 ][ i ] == 0) && (final_image[ k+1 ][ i+1 ] == 0) && (final_image[ k+1 ][ i-1 ] == 0))
                    {
                        final_image[ k ][ i ] = 0;
                        final_image[ k-1 ][ i+1 ] = 0;
                    }
                    else if ((final_image[ k ][ i ] > 0) && (final_image[ k-1 ][ i ] == 0) && (final_image [ k-1 ][ i+1 ] == 0) &&
                    (final_image[ k-1 ][ i-1 ] > 0) && (final_image [ k ][ i-1 ] == 0) && (final_image[ k ][ i+1 ] == 0) &&
                    (final_image[ k+1 ][ i ] == 0) && (final_image [ k+1 ][ i+1 ] == 0) && (final_image[ k+1 ][ i-1 ] == 0))
                    {
                        final_image[ k ][ i ] = 0;
                        final_image[ k-1 ][ i-1 ] = 0;
                    }
                    else if ((final_image[ k ][ i ] > 0) && (final_image[ k-1 ][ i ] == 0) && (final_image[ k-1 ][ i+1 ] == 0) &&
                    (final_image[ k-1 ][ i-1 ] == 0) && (final_image[ k ][ i-1 ] > 0) && (final_image[ k ][ i+1 ] == 0) &&
                    (final_image[ k+1 ][ i ] == 0) && (final_image[ k+1 ][ i+1 ] == 0) && (final_image[ k+1 ][ i-1 ] == 0))
                    {
                        final_image[ k ][ i ] = 0;
                        final_image[ k ][ i-1 ] = 0;
                    }
                    else if ((final_image [ k ][ i ] > 0) && (final_image [ k-1 ][ i ] == 0) && (final_image [ k-1 ][ i+1 ] == 0) &&
                    (final_image [ k-1 ][ i-1 ] == 0) && (final_image [ k ][ i-1 ] == 0) && (final_image [ k ][ i+1 ] > 0) &&
                    (final_image [ k+1 ][ i ] == 0) && (final_image [ k+1 ][ i+1 ] == 0) && (final_image [ k+1 ][ i-1 ] == 0))
                    {
                        final_image[ k ][ i ] = 0;
                        final_image[ k ][ i+1 ] = 0;
                    }
                    else if ((final_image [ k ][ i ] > 0) && (final_image [ k-1 ][ i ] == 0) && (final_image [ k-1 ][ i+1 ] == 0) &&
                    (final_image [ k-1 ][ i-1 ] == 0) && (final_image [ k ][ i-1 ] == 0) && (final_image [ k ][ i+1 ] == 0) &&
                    (final_image [ k+1 ][ i ] > 0) && (final_image [ k+1 ][ i+1 ] == 0) && (final_image [ k+1 ][ i-1 ] == 0))
                    {
                        final_image[ k ][ i ] = 0;
                        final_image[ k+1 ][ i ] = 0;
                    }
                    else if ((final_image [ k ][ i ] > 0) && (final_image [ k-1 ][ i ] == 0) && (final_image [ k-1 ][ i+1 ] == 0) &&
                    (final_image[ k-1 ][ i-1 ] == 0) && (final_image [ k ][ i-1 ] == 0) && (final_image [ k ][ i+1 ] == 0) &&
                    (final_image[ k+1 ][ i ] == 0) && (final_image [ k+1 ][ i+1 ] > 0) && (final_image [ k+1 ][ i-1 ] == 0))
                    {
                        final_image[ k ][ i ] = 0;
                        final_image[ k+1 ][ i+1 ] = 0;
                    }
                    else if ((final_image [ k ][ i ] > 0) && (final_image [ k-1 ][ i ] == 0) && (final_image [ k-1 ][ i+1 ] == 0) &&
                    (final_image[ k-1 ][ i-1 ] == 0) && (final_image [ k ][ i-1 ] == 0) && (final_image [ k ][ i+1 ] == 0) &&
                    (final_image[ k+1 ][ i ] == 0) && (final_image [ k+1 ][ i+1 ] == 0) && (final_image [ k+1 ][ i-1 ] > 0))
                    {
                        final_image[ k ][ i ] = 0;
                        final_image[ k+1 ][ i-1 ] = 0;
                    }

            }
    }


    veyesUtils::to_zero(final_image,pixels_X,pixels_Z);
    veyesUtils::to_zero(final_image,pixels_X,pixels_Z);

    for (int i = 0; i < pixels_Z; i++ ){
        for (int k = 0; k < pixels_X; k++ ){
            summed_image[k][i] = summed_image[k][i] +final_image[k][i];
        }
    }





    summedImgFinal.clear();
    dMaxCor = 0.0;
    for (int i = 0; i < pixels_X; i++){
        for(int j = 0; j <  pixels_Z; j++){
            if( double( summed_image[i][j]) > dMaxCor)
                dMaxCor=double(summed_image[i][j]);
            summedImgFinal.append( summed_image[i][j] );
        }
    }


    float decay_correction= veyesUtils::mf_decayCorrection(m_readInfo->useExpDecay(), m_bDoDecay,m_dActivity,m_sActivityUnit,
    m_dlambda,m_dt1,m_dt,m_qdtInjectionTime.secsTo( QDateTime().currentDateTime()), m_dpreExp, m_readInfo->getNuclide_lim3());


    cv::Mat matIn=veyesUtils::array2D_to_cvmat<float>(final_image,pixels_X,pixels_Z,decay_correction);
    cv::Mat resized_img = veyesUtils::image_conversion(matIn,img_scale_factor,img_scale_factor,pixels_X,pixels_Z);

    cv::Mat sumIn=veyesUtils::array2D_to_cvmat<float>(summed_image,pixels_X,pixels_Z,decay_correction);
    cv::Mat sum_img = veyesUtils::image_conversion(sumIn,img_scale_factor,img_scale_factor,pixels_X,pixels_Z);

    QString outputFile = m_output_filepath + "/" + m_output_filename;
    veyesUtils::write_txt_image(outputFile.toStdString(),resized_img,int(img_scale_factor*pixels_X), int(img_scale_factor*pixels_Z));

    QString summedFile = m_output_filepath + "/FinalSummed.txt";
    veyesUtils::write_txt_image(summedFile.toStdString(),sum_img,int(img_scale_factor*pixels_X), int(img_scale_factor*pixels_Z));

    if(!m_calibrationMode){
        ///Save fused images only for imaging studies
        QString fileName = m_output_filename.replace("txt", "png");
        QString opticalName, xrayName, sumOpticalName, sumXrayName;

        sumOpticalName="FinalOpticalSummed.png";
        sumXrayName="FinalXraySummed.png";
        opticalName = fileName.replace("Finalframe", "FinalframeOptical");
        xrayName = fileName.replace("FinalframeOptical", "FinalframeXray");


        std::string fussedFile = m_output_filepath.toStdString() + "/FUSION" +"/"+ opticalName.toStdString();
        write_fussed(resized_img,m_opticalImg,fussedFile);

        std::string xrayFile = m_output_filepath.toStdString() + "/XRAY" +"/"+ xrayName.toStdString();
        write_fussed(resized_img,m_xrayImg,xrayFile);

        std::string sumFussedFile = m_output_filepath.toStdString() + "/FUSION" +"/"+ sumOpticalName.toStdString();
        write_fussed(sum_img,m_opticalImg,sumFussedFile);

        std::string sumXrayFile = m_output_filepath.toStdString() + "/XRAY" +"/"+ sumXrayName.toStdString();
        write_fussed(sum_img,m_xrayImg,sumXrayFile);
    }

    sumIn.release();
    sum_img.release();
    matIn.release();
    resized_img.release();
}

void castor::write_flood(QString newCastorFlood){

    QString castor_file=m_readInfo->getCastorFloodFileName();
    QString castor_file_bak=m_readInfo->getCastorFloodFileName();
    QString castor_filepath=QDir::currentPath()+"/PET_calibration_files/CASToR/";

    castor_file_bak.remove(".img");

    QDir castor_dir(castor_filepath);
    QStringList filters, castorFiles;
    filters << "*.bk" ;
    castorFiles =castor_dir.entryList(filters,QDir::Files|QDir::NoSymLinks);

    castor_file_bak.append("_"+ QString::number(castorFiles.size())+ ".bk" );

    QFile::rename(castor_filepath + castor_file, castor_filepath + castor_file_bak);
    if (QFile::exists(newCastorFlood))
        QFile::copy(newCastorFlood, castor_filepath+castor_file);

}

void castor::write_fussed(cv::Mat foreground, cv::Mat background, std::string filename)
{
    cv::Mat fussed_img =  imageFusion::fusion( background, foreground, m_lutFilename);
    if ( QFile::exists(  QString::fromStdString(filename)))
        QFile::remove( QString::fromStdString(filename));
    cv::imwrite(filename,fussed_img);
}


void castor::setTime1( double t1 )
{
    m_dt1 = t1;
}

void castor::setdt( double dt )
{
    m_dt = dt;
}

void castor::setActivity( double activity )
{
    m_dActivity = activity;
}

void castor::setNuclideName( QString name )
{
    m_qsNuclideName = name;
    petIsotope newIsotope=m_readInfo->getPetIsotope(name);
    m_dlambda=newIsotope.getLambda();
    m_dpreExp=newIsotope.getPreExp();
    /*
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
    }*/
}

void castor::doDecay( bool decay ) {
    m_bDoDecay = decay;
}


void castor::setInjectionTime(QDateTime inject ){
    m_qdtInjectionTime = inject;
}




