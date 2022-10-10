#ifndef PETSYSWORKER_H
#define PETSYSWORKER_H
#include <QDateTime>
#include <QObject>
#include <QSemaphore>
#include <QMutex>
#include <QDir>
#include "qwt_plot.h"
#include "qwt_plot_histogram.h"
#include "qwt_raster_data.h"
#include "qwt_matrix_raster_data.h"
#include "qwt_raster_data.h"

#include "headers/readinputinfo.h"
#include "headers/readRawDataPipe.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "headers/imageFusion.hpp"
#include <cmath>
#include <tuple>
#include "headers/castor.h"
#include "headers/veyesutils.h"

class PETsysWorker : public QObject
{
    Q_OBJECT
public:
    explicit PETsysWorker(ReadInputInfo *, boost::circular_buffer<EventMsg> *, QString, QString, QString, QDateTime, double, QString, int, int,castor *, bool, bool, petIsotope);
    ~PETsysWorker();

    static const int SIZE_Y_PET;
    static const int SIZE_X_PET;
    static const int image_SIZE_X;
    static const int image_SIZE_Y;
    static const int CRYSTALS_X;
    static const int CRYSTALS_Y;
    static const int NO_CHANNELS;
    static const int MAX_ENERGY;



    boost::circular_buffer<EventMsg> *m_circularBuffer;


    ////////////////PET ARRAYS ////////////////////

    int** raw_head_A;
    int** raw_head_B;

    int* energy_head_A;
    int* energy_head_B;

    int** live_matrix;
    int** summed_matrix;


    ////////////////CALIBRATION ARRAYS ////////////////////
    int** grid_lut_head_A;
    int** grid_lut_head_B;
    int** energy_lut_head_A;
    int** energy_lut_head_B;

    ////////////////IMAGING ////////////////////
    QPolygonF pointsA,pointsB;
    QVector<qreal>  rawMatrixA,rawMatrixB,correctedMatrix;

signals:
    void stopProcessing();
    void sendImagingDataProgress(QVector<qreal>,QVector<qreal>,QVector<qreal>,QPolygonF,QPolygonF,double,double,double,int,int);
    void castor_frame(QString);
    //void castor_summed(QString);

public slots:
    void run();
    void initialise();
    void frameReconstruction();
    void stopToFrame();
    void imagingData();
    void receiveContrast(double);
    void stopImaging();



private:
    void PET_online();
    void clear_matrices();
    void memory_allocation();
    void memory_deallocation();
    void loadCalibrationFiles();
    void print_frame(int);
    void print_sum();
    void reset_live();

    std::tuple<int,int> calculate_crystal_coordinates(int **,int, int, bool &, bool &, bool &);
    int scale_energy(int **,int, int, int);
    void clear_qvector(QVector<qreal>&);
    void clear_qpolygon(QPolygonF&);


    bool m_calibrationMode;
    bool m_validationOn;
    std::ofstream validation_file;
    QString m_validationFilePath;

    castor * m_castorFrame;
    QString m_qsCastorFilename;

    // The two time instances needed by the decay correction in beta
    QDateTime m_qTime1;
    QString m_corDirectory, m_rawDirectory, m_fusionDirectory;
    QString m_qsNuclideName;

    // This is the time in sec from the injection until the user hits play. This is t1 in the decay formula for the first time.
    double m_dt1;
    double m_dlambda;
    double m_dpreExp;

    double m_activity;

    double m_frameTime;

    QString m_activityUnit;

    ReadInputInfo * m_readInputInfoPET;
    petIsotope m_petIsotope;
    FILE * rawFrameOut;
    QMutex mutex;
    int m_frameCounter;
    int m_frameStop;

    float m_fCounts;
    bool m_doDecay;

    bool newFrame=false;
    QDateTime m_dtInjectionTime;
//  Fusion related
    cv::Mat optical_img, xray_img;
    std::string lutFilename;
    double m_livecontrast;
    double m_img_scale_factor;
    double m_acceptance;
    double m_head_separation_distance;
    double m_projPix2mm;

};

#endif // PETSYSWORKER_H
