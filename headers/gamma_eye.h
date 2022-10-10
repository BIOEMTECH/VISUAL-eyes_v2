#ifndef GAMMA_EYE_H
#define GAMMA_EYE_H

#include <QMainWindow>
#include <QMenu>
#include <QSqlError>
#include <fstream>
#include <iostream>
#include <QFileDialog>
#include <QProgressDialog>
#include <QProcess>
#include <QStandardPaths>
#include <QMessageBox>
#include <QScrollArea>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QScroller>

/////Qwt Plot header files//////
#include "qwt_plot.h"
#include "qwt_plot_histogram.h"
#include "qwt_plot_spectrogram.h"
#include "qwt_plot_zoomer.h"
#include "qwt_plot_panner.h"
#include "qwt_plot_layout.h"
#include "qwt_plot_renderer.h"
#include "qwt_plot_canvas.h"
#include "qwt_legend.h"
#include "qwt_plot_curve.h"
#include "qwt_scale_widget.h"
#include "qwt_scale_draw.h"
#include "qwt_matrix_raster_data.h"

////////////////////////////////

#include "boost/format.hpp"
#include "ColorMap.h"
#include "boost/circular_buffer.hpp"
#include "operatorDialog.h"
#include "detailsDialog.h"
#include "timeSettings.h"
#include "continueStudy.h"
#include "fpga.h"
#include "udpServer.h"
#include "SPECTworker.h"
#include "arduino.h"
#include "DAQcounter.h"
#include "readinputinfo.h"
#include "Includes/dicomEncoder.hpp"

#include "calibrationDialog.h"
#include "calibrationTime.h"
#include "calibrationExit.h"
#include "isotope.h"

#include <TH1F.h>
#include <TSpectrum.h>
#include <TF1.h>
#include <TGraphErrors.h>

#include <QPdfWriter>

namespace Ui {
class gamma_eye;
}

class gamma_eye:public QMainWindow
{
    Q_OBJECT
public:
    explicit gamma_eye( ReadInputInfo*, bool, QWidget *parent = nullptr );
    ~gamma_eye();

    static const int output_size_x = 512;
    static const int output_size_y = 1024;
    static const int crystal_pixels_x = 29;
    static const int crystal_pixels_y = 58;

    QSemaphore *freeBytes;
    QSemaphore *usedBytes;
    QMutex *globalMutex;

    boost::circular_buffer<quint32> *BUFFER;
    QwtPlot  *energyPlot;
    QwtPlot *RawPlot, *correctedPlot, *summedCorrectedPlot;
    QwtPlotCurve *curve;
    QwtPlotSpectrogram *rawPlot_spectrogram, *correctedPlot_spectrogram, *summedCorrectedPlot_spectrogram;
    QwtMatrixRasterData  *rawMatrix, *corMatrix, *static_corMatrix, *sumCorMatrix;


    /** @name Validation Plots
    /**  Corrected energy Head **/
    QwtPlot  *correctedHead;

    /** graph component for @ref correctedHead.*/
    QwtPlotCurve *correctedCurve;


    ColorMap *cM;

    operatorDialog *opDialog;
    timeSettings *time;
    calibrationTime * calibTime;
    detailsDialog *study_details;

    /** @brief
     * study details class dialog instance
     */
    calibrationDialog *calibDetails;

    QString deviceOPerator,StudyID,studyName,animal,project;
    int deviceOPeratorID;

    continueStudy *nextStudy;
    calibrationExit * exitCalib;
    int duration_time,frame_time;
    double contrastPercentage;
    fpga *FPGA;
    arduino *bed;
    int DAQdurationProgress,counter,frameProgress;

    QThread *udpThread,*SPECTthread,*counterThread;

    QDir Storage,img,raw,rawdata,corrected,deconvoluted,post;

    QString rawD,corrD,postD;
    QString m_qsDeconvDir;

    bool fastDynamic, noTimeSettings;
    int frameCount;

signals:
    void saveStudyToDatabase(QString,QString,QString,QString);
    void closeTimeSettings();
    void terminate_fpga();
    void onPressedStart();
    void onPressedStop();
    void updateSummed();
    void sendContrast(double);
    void exitToMainWindow();
    void sendFrameStop();
    void openTimeSettings();
    void exit();
    void exitProgram();
    void sendStudyDir(QString);
    void deleteSPECTarrays();
    void bedInsertSignal(bool);

public slots:
    void Initiate();
    void closeWin();
    void StudyCycle();
    void calibrationCycle();
    void getOperator(QString);
    void getStudyID(QString, QString, QString, QString);
    void getCalibrationID(QString, bool);
    void AquisitionData(int,int,QString,QString,bool);
    void reset();
    void saveDICOM();
    void fpgaErrorMsg(int);
    void disableStartButton();
    void startAquisition();
    void stopAquisition();
    void stopWithError();
    void InitiateThreads();
    void plotsUpdate(QVector<qreal>, QVector<qreal>, QVector<qreal>, QPolygonF, double, double, double, int);
    void sliderValueChanged(int);
    void cb_ColorMap_currentIndexChanged(int);
    void frameReplot();
    void directoryCreation();
    void infoFileGenerator();
    void calibrationInfoGenerator();
    void getNewFrameTime(int);
    void RestartApplication();
    void insertCapture();
    void changeVoltage(QString);
    void getCameraFeedback();
    void insertNoCapture();
    void exitBedDialog();
    void FPGA_initState();
    void arduino_initState();
    void timeFinishedPressed();
    void arduinoSocketState();
    void bedEjectState();
    void setDecayInfo( const QString, const QString, const QString, QDateTime, double, QString);
    void sliderSummedValueChanged(int);
    void configureArduino();

private slots:
    void gammaEvaluation();
    void pdf_report(double);
    void PB_startDAQ_clicked();
    void qwt_plots();
    void qwt_validation_plots();
    void delete_qwt_plots_and_globals();
    void delete_qwt_validation_plots();
    void on_actionGo_back_to_main_menu_triggered();
    void on_actionInsert_Bed_triggered();
    void on_actionEject_Bed_triggered();
    void on_actionCalibrate_Bed_Position_triggered();
    void on_PB_eject_clicked();
    void on_cb_fusion(bool checked);
    void on_cb_xray(bool checked);
    void setCheckstateOptical();
    void setCheckstateXray();
    void msgBoxClosed(QAbstractButton*);
    void msgBox2Closed(QAbstractButton*);
    void errorMsgAction(QAbstractButton*);
    void CameraErrorMsgAction(QAbstractButton*);
    void msgBoxBedIn(QAbstractButton*);

    void addOpticalBackground();
    void addXrayBackground();
    void removeBackground();
    void opacityValueChanged(int);
    void setBackgroundImages();
    float searchPhotopeak_T1(TH1F*,float);

private:
    Ui::gamma_eye *ui;
    QMutex mutex;
    spectIsotope  m_newIsotope;
    bool okFromCam,okFromFPGA,PlotItemsAttached;
    bool arduinoConfigured,FPGAconfigured;
    bool timeFinishBtnPressed,bedMoved;
    QMessageBox* msgInBox;
    bool aboutToExit;
    QString m_qsNuclidedFolder;
    QString m_qsNuclideName;
    QString m_qsCollimator;
    QDateTime m_qdtInjectionDateTime;
    double m_dActivity;
    QString m_sActivityUnit;
    ReadInputInfo* m_pReadInputInfoGamma;

    double m_dMaxCor;
    QVector<qreal> m_qvrSummedImg;
    cv::Mat m_cvmSummedFusedImg;


    QString m_opticalImagePath, m_xrayImagePath;
    cv::Mat m_opticalImageMat, m_xrayImageMat;

    double m_dContrastPercentageSummed;
    bool m_isOpticalChecked = false, m_isXrayChecked = false;
    bool m_calibrationMode;
    bool m_validationOn;
    bool m_bedCalibrated;

};

#endif // GAMMA_EYE_H
