#include "headers/CameraWorker.h"
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>


CameraWorker::CameraWorker(cv::VideoCapture &capture, QString &name, int &mod, ReadInputInfo * inputInfo)
{

    cap = capture;
    str = name;
    MOD = mod;
    m_readInputInfo=inputInfo;
    mf_setLastFrame();

}

CameraWorker::~CameraWorker(){
}


void CameraWorker::mf_setLastFrame(){
    QString local =  QDir::currentPath();

    std::string configFilename;

    if ( MOD == 1 )
        configFilename = local.toStdString().append("/config/SPECT/imageCapture.cfg");
    else if ( MOD == 2 )
        configFilename = local.toStdString().append("/config/PET/imageCapture.cfg");

    ifstream config;
    config.open( configFilename, ios::in );
    if (config.is_open()) {
        char data[256];
        string numString;
        config >> numString;
//        this->scannerSliceUpperLeftestPoint.x = stoi(numString);
        config.getline(data, 256);

        config >> numString;
 //       this->scannerSliceUpperLeftestPoint.y = stoi(numString);
        config.getline(data, 256);
 //       cout << "Scanner Slice Upper Leftest Point: (" << this->scannerSliceUpperLeftestPoint.x
 //               << ", " << this->scannerSliceUpperLeftestPoint.y << ")" << endl;

        config >> numString;
 //       this->scannerSliceLength = stoi(numString);
        config.getline(data, 256);
 //       cout << "Scanner Slice Length: " << this->scannerSliceLength << endl;

        config >> numString;
  //      this->scannerSliceWidth = stoi(numString);
        config.getline(data, 256);
 //       cout << "Scanner Slice Width: " << this->scannerSliceWidth << endl;

        config >> numString;
 //       this->extraSliceWidth = stoi(numString);
        config.getline(data, 256);
  //      cout << "Extra Slice Width: " << this->extraSliceWidth << endl;

        config >> numString;
   //     this->firstFrame = stoi(numString);
        config.getline(data, 256);
        cout << endl;
 //       cout << "First Frame: " << this->firstFrame << endl;

        config >> numString;
        m_iLastFrame = stoi(numString);
        config.getline(data, 256);
        cout << "Last Frame: " << m_iLastFrame << endl;

        config >> numString;
  //      int motionTemp = stoi(numString);
        config.getline(data, 256);
        config.close();
    }
    else {
        cout << "Unable to open configuration file" << endl;
        config.close();
        exit(-1);
    }
}
void CameraWorker::startWriting()
{
    timer->start();
}

void CameraWorker::init()
{
    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer, SIGNAL( timeout() ), this, SLOT(record()));

    QString copy = str;
    QString file = "/Vid00.avi";
    copy.append( file );
    filename =  copy.toStdString();
    cv::Size frameSize(static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)),static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT)));
    int fcc =  cv::VideoWriter::fourcc('I','4','2','0');// CV_FOURCC('M','J','P','G');
    writer = cv::VideoWriter(filename,fcc,cap.get(cv::CAP_PROP_FPS),frameSize);
}

void CameraWorker::record()
{
    cap.read(frame);
    frame_BUFFER.push_back(frame.clone());
//    #ifdef QT_DEBUG
        qDebug() << "Frame: " << frame_BUFFER.size();
//    #endif

}

void CameraWorker::optical_reconstruction()
{
    for(boost::circular_buffer<cv::Mat>::iterator it = frame_BUFFER.begin(); it!=frame_BUFFER.end();++it)
        writer.write(*it);

    writer.release();
    frame_BUFFER.clear();

    QString local =  QDir::currentPath();
    std::string configFilename;

    configFilename = local.toStdString().append("/config/PET/imageCapture.cfg");

    std::string path = str.toStdString();
    std::string videoFilename = filename;
    std::string outputImageFilename = path + "/optical.png";
    cv::Mat outputImage;

    bioemtec::imageCapture imgCap( configFilename );
    outputImage = imgCap.fromVideoToImage( videoFilename );

    // Write the image as png
    cv::flip( outputImage, outputImage, 1 );
    cv::imwrite(outputImageFilename, outputImage);

    if ( QFile::remove( QString::fromStdString( filename ) ) ){
        qDebug() << "Finished recording ...";
        createXray();
        emit finishedRec();
    }


}


void CameraWorker::stopRecording()
{
    timer->stop();
    timer->deleteLater();
    delete timer;
//    m_record=false;
    optical_reconstruction();
}

void CameraWorker::createXray(){

    QString path =str;
    QString outputImageFilename = path + "/optical.png";
    QString xrayInputResized = path + "/opticalRs.png";
    QString xrayFilePath = path + "/Xray.png";
    cv::Mat opticalImage, xrayInputImg, xrayImage;

    // Open optical.png and resize
    opticalImage = cv::imread(outputImageFilename.toStdString());
    cv::resize(opticalImage, xrayInputImg, cv::Size(512, 1024), cv::INTER_CUBIC);
    cv::imwrite(xrayInputResized.toStdString(),xrayInputImg);
    //Rename optical
    QFile::rename(outputImageFilename, path +  "/optical.tmp");
    // Store current directory and MLmodel directory
    QString currentPath = QDir::currentPath();
    QString exePath = currentPath +"/external_code/pix2pix_test_integration";
    QProcess  xrayGenerate;
    QString execommands;
    execommands = "python3 test.py --dataroot " + xrayInputResized.remove("opticalRs.png")
            + " --name model_latest --model test --netG unet_256 --direction AtoB --dataset_mode single --norm batch --gpu_ids -1 --load_size 512 --crop_size 512";
    if (!QDir::setCurrent(exePath))
        qDebug() << "Could not change the current working directory" << endl;
    else {

        xrayGenerate.execute(execommands);
        xrayGenerate.waitForFinished();

        QFile xrayFile(QDir::currentPath()+"/results/model_latest/test_latest/images/opticalRs_fake.png");
        if (xrayFile.exists()){
            xrayFile.copy(path +"/Xray.png");
        }
        QDir outImgDir(QDir::currentPath()+"/results/model_latest/test_latest/images/");
        outImgDir.setNameFilters(QStringList() << "*.png");
        outImgDir.setFilter(QDir::Files);
        for(const QString &dirFile: outImgDir.entryList()) {
          outImgDir.remove(dirFile);
        }
        xrayImage = cv::imread(xrayFilePath.toStdString());
        cv::resize(xrayImage,xrayImage, cv::Size(512, 1024), cv::INTER_CUBIC);
        cv::imwrite(xrayFilePath.toStdString(),xrayImage);
        QDir::setCurrent(currentPath);

        QString invert_command="python3 ./scripts/invert_xray.py -i " + path + "/Xray.png";
        xrayGenerate.execute(invert_command);
        xrayGenerate.waitForFinished();
    }
    QFile::rename(path +  "/optical.tmp",outputImageFilename);
    QFile::remove(xrayInputResized + "/opticalRs.png");
}
