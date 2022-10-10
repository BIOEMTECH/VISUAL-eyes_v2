#ifndef CASTORFRAME_H
#define CASTORFRAME_H
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

class castorFrame: public QObject
{
    Q_OBJECT

public:
    castorFrame(ReadInputInfo*);
   ~castorFrame();

    void setOpticalImg(cv::Mat);
    void setXrayImg(cv::Mat);

    //These are needed for the decay correction
    void setActivity( double );
    void setTime1(double );
    void setdt( double );
    void setNuclideName( QString );
    void setActivityUnit( QString );
    void doDecay(bool);
    void setInjectionTime( QDateTime );
    void setRawFilePath(QString);
    void setOutputPath(QString);

public slots:
    void runCastor();
    void createFilesForCastor( QString );
    void saveImg();

private:

    QProcess* m_castorFilesCreator;
    QProcess* m_castorProc;

    ReadInputInfo* m_readInfo;

    float*** input_img;
    float*** flipped_img;
    float** final_image;

    int m_iPixelsX;
    int m_iPixelsY;
    int m_iPixelsZ;
    int m_iStartSl = 25;
    int m_iStopSl = 85;

    QString m_calibrationFileCastor;
    QString m_raw_frame_path;
    QString m_output_path;
    QString m_output_filename;

    cv::Mat m_opticalImg;
    cv::Mat m_xrayImg;
    std::string m_sLutFilename;

    QDateTime m_qDateTime1;
    QDateTime m_qDateTime2;
    double m_dActivity;
    double m_dt;

    QString m_qsNuclideName;
    double m_dDecay;
    double m_dt1;

    float mf_countsToActivity( float );
    float mf_activityToCounts( float );
    float mf_decayCorrection();

    QString m_sActivityUnit;
    double m_dlambda;
    double m_dpreExp;

    float m_fCounts;
    bool m_bDoDecay;
    QDateTime m_qdtInjectionTime;
    double m_img_scale_factor;

};

#endif // CASTORFRAME_H


