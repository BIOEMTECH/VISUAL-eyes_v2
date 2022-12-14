////////////////////////////////////////////////////////////////////////
/////
/////	@file SPECTworker.h
/////	@brief headerFile SPECTworker
/////
/////	@author Aphrodite Toufa
///// @date   Created: 13.10.2017
/////
////////////////////////////////////////////////////////////////////////

#ifndef SPECTWORKER_H
#define SPECTWORKER_H

#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QSemaphore>
#include <QWaitCondition>
#include <QReadWriteLock>
#include <QStack>
#include <QFile>
#include <QTime>
#include <QDir>


#include "qwt_plot.h"
#include "qwt_plot_histogram.h"
#include "qwt_raster_data.h"
#include "qwt_matrix_raster_data.h"
#include "qwt_raster_data.h"

#include "boost/circular_buffer.hpp"

#include <fstream>
#include <iostream>
#include <sstream>


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "headers/rlDeconv.hpp"
#include "headers/imageFusion.hpp"

#include "readinputinfo.h"
#include "veyesutils.h"
#include "isotope.h"

using namespace std;
using namespace cv;

class SPECTworker : public QObject
{
    Q_OBJECT
public:
    explicit SPECTworker(QSemaphore*, QSemaphore*, QMutex*, boost::circular_buffer<quint32>*, QString, QString, QString, QString, QString, QDateTime, double, ReadInputInfo*, bool, bool, spectIsotope);
    ~SPECTworker();

    static const int output_size_x = 512;
    static const int output_size_y = 1024;
    static const int crystal_pixels_x = 29;
    static const int crystal_pixels_y = 58;
    static const int ADC_range = 2048;
    static const int ADC_chan  = 512;
    static const int ADC_chan_energy = 16;


    QMutex         *globalMutex;
    qint64         totalNumberOfEvents, staticTotalNumberOfEvents;
    QSemaphore     *freeBytes;
    QSemaphore     *usedBytes;

    QPolygonF points;
    boost::circular_buffer<quint32>* BUFFER;

    quint16 flag;
    int y_count;

    /////////// SPECT CALIBRATION ARRAYS //////
    int  **grid_pixel;
    int   **energy_lut;
    int   **energy_lut1;
    int   **energy_lut2;
    int   **summed_flood20;
    int   **summed_flood201;
    int   **summed_flood202;

    int   **energy_lutUpSc;
    int   **energy_lutLowSc;
    int   **summed_floodUpSc;
    int   **summed_floodLowSc;
    ////////////////////////////////////////////

    /////////// SPECT ARRAYS //////////////////
    double **corrected_with_energy_mat;
    double **cumulative_corrected;
    double **corrected_with_energy_mat1;
    double **corrected_with_energy_matUpSc;
    double **cumulative_corrected1;
    double **cumulative_correctedUpSc;
    double **corrected_with_energy_mat2;
    double **corrected_with_energy_matLowSc;
    double **cumulative_corrected2;
    double **cumulative_correctedLowSc;
    double **summed_total;
    double **summed_total1;
    double **summed_total2;
    double **summed_totalUpSc;
    double **summed_totalLowSc;
    double **summed_with_energy_mat;
    double **summed_with_energy_mat1;
    double **summed_with_energy_mat2;
    double **summed_with_energy_matUpSc;
    double **summed_with_energy_matLowSc;
    double **tempCorWithEnrgMat;
    int  **currentRawMat;
    int *energy;

    ////////////////////////////////////////////
    int maxEn;
    bioemtec::rlDeconv *ob;
    int it;
    double contrast,contrast_min;
    int frameCounter;
    QString correctedDir,rawDir,fusionDir, m_qsDeconvDir;
    QString fusionDeconvDir;
    cv::Mat optical_img;
    cv::Mat xray_img;
    std::FILE *fp;
    std::string lutFilename;

signals:
    // void finishedAppending();
    void stopProcessing();
    void sendImagingDataProgress(QVector<qreal>,QVector<qreal>,QVector<qreal>,QPolygonF,double,double,double,int);
    void imageFinished();

public slots:
    void frameStop();
    void receiveContrast(double);
    void stopImaging();
    void run();
    void imagingData();
    void Initialise();

private:
    void calculate_flood(QString);
    bool isAlive();
    void memory_allocation();
    void loadCalibrationFiles();
    void pinakas_dealllocation();
    void Visualisation(int);
    void resetAll();
    void cleanup();

    bool isNotFrame();
    void frame_print(int);
    void print_sum();

    volatile bool restart;
    volatile bool last;
    volatile bool stopped;
    bool first;

    QMutex mutex;
    QMutex zero_Mutex;

    QString m_qsNuclidedFolder;
    QString m_qsNuclideName;
    QDateTime m_qdtInjectionDateTime;
    QDateTime m_qdtSaveTime;
    double m_dActivity;

    double mf_decayCorrection();
    void mf_deconvolution(int, int);
    //void mf_deconvolution( int );
    QVector<qreal> mf_deconvolution( int );

    std::ofstream validation_file;
    QString m_validationFilePath;
    ReadInputInfo* m_pReadInputInfo;
    spectIsotope m_spectIsotope;
    bool m_calibrationMode;
    bool m_validationOn;
    const int m_scale1_x=5, m_scale1_y=5;
    const int m_scale2_x=10, m_scale2_y=10;
};


#endif // SPECTWORKER_H





