#ifndef CASTOR_H
#define CASTOR_H
#include <QObject>
#include <deque>
#include <QDir>
#include <QVector3D>
#include <QProcess>
#include <QTextStream>
#include <QMutex>
#include <QDateTime>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/core/core.hpp>
#include "headers/readinputinfo.h"
#include "headers/imageFusion.hpp"
#include "headers/veyesutils.h"

#include <QObject>

class castor: public QObject
{
    Q_OBJECT

public:
    castor(ReadInputInfo*,bool,bool);
   ~castor();

    const int pixels_X=60;
    const int pixels_Y=60;
    const int pixels_Z=120;
    const int start_slice=5;
    const int stop_slice=55;
    const double img_scale_factor= 5.25;


    double dMaxCor;
    QVector<qreal> summedImgFinal;

    void setOpticalImg(cv::Mat);
    void setXrayImg(cv::Mat);

    //These are needed for the decay correction
    inline bool isCastorSummedFinished(){ return m_finishedSummed; }
    void setActivity(double);
    void setTime1(double);
    void setdt(double);
    void setNuclideName(QString);
    void setActivityUnit(QString);
    void doDecay(bool);
    void setInjectionTime( QDateTime );
    void setRawFilePath(QString);
    void setSumRawFilePath(QString);
    void setOutputPath(QString);
    void setFrameStop(int);

public slots:
    void createFilesForCastor(QString);
    void runCastor();
    void saveImg();

signals:
    void sumImgComputed(QVector<qreal>);

private:
    QProcess* m_castorFilesCreator;
    QProcess* m_castorProc;

    ReadInputInfo* m_readInfo;

    bool m_finishedSummed;

    float*** flood_img;
    float*** flipped_flood;
    float*** input_img;
    float*** flipped_img;
    float*** corrected_img;
    float** final_image;
    float** summed_image;

    QString m_calibrationFileCastor;
    QString m_raw_filepath;
    QString m_sum_filepath;
    QString m_output_filepath;
    QString m_output_filename;

    cv::Mat m_opticalImg;
    cv::Mat m_xrayImg;
    std::string m_lutFilename;

    QDateTime m_qDateTime1;
    QDateTime m_qDateTime2;
    double m_dActivity;
    double m_dt;

    QString m_qsNuclideName;
    double m_dDecay;
    double m_dt1;

    float mf_decayCorrection();
    void write_fussed(cv::Mat, cv::Mat, std::string);
    void write_flood(QString);

    QString m_sActivityUnit;
    double m_dlambda;
    double m_dpreExp;

    float m_fCounts;
    bool m_bDoDecay;
    QDateTime m_qdtInjectionTime;

    int  m_frameCounter;
    int  m_frameStop;
    bool m_calibrationMode;
    bool m_validationOn;

};

#endif // CASTOR_H


