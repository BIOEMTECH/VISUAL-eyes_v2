#include "headers/gammacamera.h"
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>


gammaCamera::gammaCamera(cv::VideoCapture &capture, QString &name, int &mod, ReadInputInfo* inputInfo)
{

    cap = capture;
    str = name;
    MOD = mod;
    m_readInputInfo =inputInfo;

}

gammaCamera::~gammaCamera()
{
 //   delete ui;
}

void gammaCamera::snapshot()
{
    cv::Mat frame;
    QString copy = str;
    QString file = "/optical.png";
    copy.append( file );
    filename =  copy.toStdString();

    QTime dieTime = QTime::currentTime().addSecs(2);
    while( QTime::currentTime() < dieTime ){
           cap.read(frame);
    }
    cap.read(frame);

    frame.convertTo(frame,CV_8UC3);

//    QString original_image=str +"/original.png";
//    cv::imwrite(original_image.toStdString(),frame);

    int x0=0,y0=0,width=0,height=0;

    QStringList image_crop=m_readInputInfo->getCrop();
    x0=image_crop[0].toInt();
    y0=image_crop[1].toInt();
    width=image_crop[2].toInt();
    height=image_crop[3].toInt();
    cv::Rect myROI(x0,y0,width,height);

    cv::Mat croppedImage = frame(myROI);

    cv::rotate(croppedImage,croppedImage,cv::ROTATE_90_COUNTERCLOCKWISE);


    cv::imwrite(filename,croppedImage);
    createXray();
    emit finishedCapture();


}


void gammaCamera::createXray(){

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
