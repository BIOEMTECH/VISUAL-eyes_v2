#ifndef BETAEYE_H
#define BETAEYE_H

#include <QMainWindow>
#include <QMainWindow>
#include <QMenu>
#include <QMutex>
#include <QSqlError>
#include <fstream>
#include <iostream>
#include <QFileDialog>
#include <QProgressDialog>
#include <QProcess>
#include <QStandardPaths>
#include <QSemaphore>
#include <QScreen>
#include <QMessageBox>
#include <QRect>
#include <QThread>


#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgcodecs.hpp>

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

#include "readinputinfo.h"
#include "ColorMap.h"
#include "boost/circular_buffer.hpp"
#include "timeSettings.h"
#include "continueStudy.h"
#include "PETsysConnection.h"
#include "petsysDAQ.h"
#include "readRawDataPipe.h"
#include "DAQcounter.h"
#include "PETsysWorker.h"
#include "arduino.h"
#include <QList>
#include "operatorDialog.h"
#include "detailsDialog.h"
#include "calibrationDialog.h"
#include "calibrationTime.h"
#include "calibrationExit.h"
#include "veyesutils.h"
#include "headers/temperatureControl.h"
#include "Includes/dicomEncoder.hpp"

#include <TH1F.h>
#include <TSpectrum.h>
#include <TF1.h>
#include <TGraphErrors.h>

#include <QTextEdit>
#include <QPrinter>
#include <QDesktopServices>
#include <QPdfWriter>

namespace Ui {
class betaEye;
}

/**
 * @brief Main interface for PET live data aquisition
 * @include betaEye.h
 * Main aquisition class with plots for b-eye(PET), that handles the live data aquisition and imaging.
 * All major parallel threads that are resposible for PET aquisition and reconstruction start from here.
 */
class betaEye : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief beta_eye constructor
     * @param parent set to null
     */
    explicit betaEye(ReadInputInfo*, bool, QWidget *parent = nullptr);
    /**
     * @brief ~beta_eye class destructor
    */
    ~betaEye();

    static const int output_size_y_PET = 1024; //1024;
    static const int output_size_x_PET =512;// 512;
    static const int image_SIZE_X = 72;
    static const int image_SIZE_Y = 144;
    static const int image_SIZE_X_Castor = 60;
    static const int image_SIZE_Y_Castor = 120;


    /** @brief
     *  BUFFER this is boost's circular buffer that is used by the threads in a producer-consumer model
     */
    boost::circular_buffer<EventMsg> *BUFFER;

    PETsysConnection *PETsys;
    QThread *PETsysThread;
    QThread * rawDataThread;

    /** @name Energy Plots
     */
    ///@{
    /**  qwt's scientfic plot where we represent the energy spectrum data for the first crystal head */
    QwtPlot  *energyPlot1;
    /**  qwt's scientfic plot where we represent the energy spectrum data for the second crystal head */
    QwtPlot *energyPlot2;
    ///@}

    /** @brief
     *  graph component for @ref energyPlot1.
     */
    QwtPlotCurve *curve1;

    /** @brief
     *  graph component for @ref energyPlot2.
     */
    QwtPlotCurve *curve2;


    /** @name Raw Plots */
    /**  qwt's scientfic plot where we represent the raw reconstructed for the first crystal head */
    QwtPlot *RawPlot1;
    /**  qwt's scientfic plot where we represent the raw reconstructed for the second crystal head */
    QwtPlot *RawPlot2;

    /** @name Corrected Plots
     */
    ///@{
    /** qwt's scientfic plot where we represent the true coincidencies/events derived from the PET reconstruction/correction of the recieved data as an image  */
    QwtPlot *correctedPlot, *summedCorrectedPlot;

    /** @name Raster Data*/
    /** raw  matrix raster data for @ref rawPlot1_spectrogram */
    QwtMatrixRasterData *rawMatrix1,*rawMatrix2;



    /** @name Qwt Spectrograms*/
    /** raw plot spectrogram, this is where we apply our colormaps and set the data values */
    QwtPlotSpectrogram *rawPlot1_spectrogram,*rawPlot2_spectrogram;

    /** corrected matrix raster data for @ref rawPlot2_spectrogram */
    QwtMatrixRasterData *liveMatrix,*summedMatrix;

    /** corrected plot spectrogram, this is where we apply our colormaps and set the data values */
   QwtPlotSpectrogram *correctedPlot_spectrogram, *summedCorrectedPlot_spectrogram;



   /** @name Validation Plots
    */
   ///@{
   /**  Raw energy Head 1 & 2 */
   QwtPlot  *rawHead1, *rawHead2;

   /**  Corrected energy Head 1 */
   QwtPlot  *correctedHead1, *correctedHead2;

   /**  Average Energy Resolution energy Head 1 */
   QwtPlot  *resolutionHead1, *resolutionHead2;

   /** graph component for @ref rawHead1.*/
   QwtPlotCurve *rawCurve1,  *rawCurve2;

   /** graph component for @ref correctedHead1.*/
   QwtPlotCurve *correctedCurve1, *correctedCurve2;

   /** graph component for @ref resolutionHead1.*/
   QwtPlotCurve *resolutionCurve1, *resolutionCurve2;


    /** @brief
     *  colormap class instance, each colormap dictates how to represent a spesific value
     */
    ColorMap *cM;    

    /**
     * @brief operator dialog class instance
     */
    operatorDialog *opDialog;

    /** @brief
     * time settings dialog class instance
     */
    timeSettings *time;

    /** @brief
     * time settings dialog class for calibration
     */
    calibrationTime * calibTime;

    /** @brief
     * study details class dialog instance
     */
    detailsDialog *study_details;

    /** @brief
     * study details class dialog instance
     */
    calibrationDialog *calibDetails;

    /**
     * @brief Holds the current user. Foreign key to Study table in database.
     */
    QString deviceOPerator;

    /**
     * @brief Holds unique study's ID. Primary key in Study table in the database.
     */
    QString StudyID;

    /** @name Strings*/
    ///@{
    /** Study parameter */
    QString studyName,animal,project;
    ///@}

    int deviceOPeratorID;

    /**
     * @brief After study progression-dialog instance
     */
    continueStudy *nextStudy;

    /**
     * @brief After calibration is finished
     */
    calibrationExit * exitCalib;


    /** @brief
     *  arduino handler class instance
     */
    arduino *bed;


    /** @brief
     *  temperature control class instance
     */
    temperatureControl * sensor_temperature;

    /** Aquisition's duration time and frame interval time variables. These are our timing parameters and we base the whole live aquisition scheme based on these.  */
    int duration_time,frame_time, frame_time_sec;

    /** @brief
     * percentage variable based on it's value we can change the contrast on the received images by changing the image's min-max value range
     */
    double contrastPercentage, contrastPercentageSummed;
    /** @name Thread Variables.
     */
    ///@{
    /** Counts the frame intervals completed.
     */
    int counter;
    int frameProgress;
    ///@}

    /** @name Threads.
     */
    ///@{
    /** Producer thread */
    QThread *daqThread;
    QThread * pprocThread;
    /** PET reconstruction worker. Consumer thread */
    QThread * CastorSummedThread;
    QThread * CastorFrameThread;



    QThread *PETthread;
    /** Thread that handles the timing and sychronization of the other two threads and handles the gui plots update in the main thread.
     */
    QThread *counterThread;

    /** @name Directories */
    ///@{
    /** General study directory */
    QDir Storage;
    /** General directory where the images from the aqusition are stored */
    QDir img;
    /** Raw data sub-directory for every image frame */
    QDir rawdataDir;
    QDir raw;
    /** Corrected images sub-directory, here we store the reconstructed/corrected images as well as the fussed ones */
    QDir corrected;
    /** General directory for the post aquisition processing. Here we store all the exports from the post processing */
    QDir post;

    /** Castor directory where the images are stored */
    QDir  castorDir;
    ///@}

    /** @name Paths*/
    ///@{
    /** The absolute path names of the directories created. */
    QString rawD, corrD, postD, qsCastorDir;
    ///@}

    bool fastDynamic; /** dynamic timing protocol mode */
    bool noTimeSettings; /** time settings fail state */

    int frameCount; /** frame interval image counter */



signals:
    /**
     * @brief Sends the required ids and informarion in order to save the study in the database after the aquisition is finished/stopped.
     */
    void saveStudyToDatabase(QString,QString,QString,QString);
    /**
     * @brief Emit signal to close the time settings dialog after duration time and frame time interval is set.
     */
    void closeTimeSettings();
    /**
     * @brief Emit signal to terminate fpga handling and kill the QProcess running in the background.
     */
     void terminatePETsysCon();
    /**
     * @brief Emit signal to stop the aquisition. The actions to stop the aquisition and the thread starts from here.
     */
    void onPressedStop();
    /**
     * @brief Emit signal when the user changes the constrast percenrage from the gui.
     */
    void sendContrast(double);
    /**
     * @brief Send global path names to create the direcotries needed.
     */
    void sendFileDirectory(QString,QString);
    /**
     * @brief Emit signal to exit to the main program's dialog and close the interface.
     */
    void exitToMainWindow();
    /**
     * @brief Inform the reconstuction worker thread when a frame interval is due.
     */
    void sendTimeToframe();
    /**
     * @brief Signal to open the time settings dialog.
     */
    void openTimeSettings();
    /**
     * @brief Signal to close all background processes and return to the program's welcome dialog.
     */
    void exit();


    void exitProgram();
    /**
     * @brief Send the general study directory in the file system in order to create the subdirectories needed.
     */
    void sendStudyDir(QString);

    void bedInsertSignal(bool);

public slots:
     /**
     * @brief Closes the main dialog and exit the mouse bed to retrieve mouse before exiting.
     */
    void closeWin();
    /**
     * @brief Gets the current operator/user.
     * @param name is the name of the operator and it is stored in a global string
     */
    void getOperator(QString);

    /**
     * @brief Gets the study ID from the database and other fields' values.
     * @param ID is the database study id
     * @param name is the name of the study
     * @param patient the name of the animal used
     * @param proj is the project the study belong to
     */
    void getStudyID(QString,QString,QString,QString);

    void getCalibrationID(QString, bool);

    /**
     * @brief This function gathers all the aquisition related data, sets the information needed for the user to see, checks if the time parameter are correct or present
     * and at last ejects the bed out when ready to initiate the capture procedure.
     * @param duration is the aquisition duration
     * @param frame is the time frame interval
     * @param d_unit is the time unit in sec or min for the duration
     * @param f_unit is the time unit in sec or min for the frame interval
     * @param fDynamic holds the info if we use the fast dynamic time protocol
     */
    void acquisitionData(int, int, QString, QString, bool);

    /**
     * @brief Resets gui after an aquisition has finished. It clears the plot of the old data by calling update one last time with empty matices as parameters,
     * clears the information from the QLabels and resets the progress bars.
     */
    void reset();

    /**
     * @brief Checks weither the FPGA is correctly programmed and an optical image is created. If both reqirements are met it enables the start button.
     */
    void disableStartButton();

    void startAquisition();

    void stopAquisition();
    void stopWithError();

    /**
     * @brief The main multithread part of the program. This function creates,initiates and connects the secondary threads to the main thread with signals and slots.
     * The whole communication with the threads is structured here well as the cleanup and release of the threads.
     */
    void initiateThreads();
    void plotsUpdate(QVector<qreal>, QVector<qreal>,QVector<qreal>, QPolygonF, QPolygonF,double,double,double,int,int);
    void sliderValueChanged(int);
    void sliderSummedValueChanged(int);
    void cb_ColorMap_currentIndexChanged(int);
    void frameReplot();
    void directoryCreation();
    void infoFileGenerator();
    void calibrationInfoGenerator();
    void getNewFrameTime(int);
    void RestartApplication();
    void fpgaErrorMsg(int);
    /**
     * @brief This function shows a message when the mouse bed is fully out and informs the user to set the mouse on the bed before continuing.When the message closes it opens
     * a second confirmation message.
     */
    void insertCapture();

    /**
     * @brief This function sends the relative info i.e. the injection time and name of the nucleid in order to perform the decay correction in the PETworker
     */
    void setDecayInfo( const QString, const QString, const QString, QDateTime, const double, QString );

    /**
     * @brief Checks if the video capture in the @ref CamerWorker thread was completed and an optical reconstructed image has been created
     *  and aslo checks if the FPGA is programmed.If both reqirements are met it enables the start button.
     */
    void getCameraFeedback();
    void insertNoCapture();
    void exitBedDialog();
    void arduino_State();
    void sensors_state();
    void fpga_state();
    void timeFinishedPressed();
    void arduinoSocketState();
    void bedEjectState();
    void updateSummedImgPlot(QVector<qreal>);

    void errorMsg(int);

    void configureArduino();

    /** Update the summed image **/
    //void updateSummedImgPlot(  QVector<qreal>);

private slots:
    /**
     * @brief Initialisation function. Initializes the global variables and child classes instances and sets up the gui components .The study cycle starts from here and so everything
     * starts from here.
     */
    void initilization();

    /**
     * @brief Construction of the qwt plots and other qwt components in order to represent the aquired data.
     */
    void qwt_plots();


    void qwt_validation_plots();

    /**
     * @brief This is a cleanup function. After everything is finished and we exit the main dialog we have to delete all the heap allocated variables
     */
    void delete_qwt_plots_and_globals();

    void delete_qwt_validation_plots();


    /**
     * @brief This function is responsible for the initiation of the whole logical flow of an aqusition study. Everything starts from here.
     */
    void studyCycle();

    /**
     * @brief This function is responsible for the initiation of the whole logical flow of a calibration study.
     */
    void calibrationCycle();


    /**
     * @brief This function enables starting acquisition after PETsys DAQ connection has been established and initialized successufully.
     */
    void enableStartButton();

    /**
     * @brief From the dialogs main actions, this exits the main interface dialog by stopping the background
     */
    void on_actionExit_to_Main_Menu_triggered();

    /**
     * @brief Eject the bed from the corresponding button. These buttons are for the control of the bed and for troubleshooting purposes.
     * When the bed is out the user will be presented with the confirmation message and inser it back inside.
     * This function will only move the bed put and wont initiate the video capture.
     */
    void on_PB_eject_clicked();

    /**
     * @brief This function provides a second confirmation message to the user. When this is closed, the bed is inserted and the video recording starts
     */
    void msgBoxClosed(QAbstractButton*);

    /**
     * @brief This function moves the bed inside and informs the camera thread to start recording
     */
    void msgBox2Closed(QAbstractButton*);



    /**
     * @brief This function starts the aquisition by issuing start in the xmd in the fpga process. Consecutively the fpga starts the threads and the whole DAQ procedure.
     * It also checks one last time if our time settings are set, so if they are not it opens the time dialog again to set them.
     */
    void PB_startDAQ_clicked();
    /**
     * @brief Convert acuired images to DICOM
     */
    void saveDICOM();

    /**
     * @brief If we get a camera bind error we have to exit the program completely and then start it again.
     */
    void CameraErrorMsgAction(QAbstractButton*);


    void on_cb_fusion(bool checked);

    void on_cb_xray(bool checked);

    void setCheckstateOptical();

    void setCheckstateXray();

    void setBackgroundImages();

    void msgBoxBedIn(QAbstractButton*);

    void addOpticalBackground();

    void addXrayBackground();

    void removeBackground();

    void opacityValueChanged(int);



private:
    void betaEvaluation();
    void pdf_report(double, double);

    bool firstSummed2;
    bool arduinoConfigured;
    bool timeFinishBtnPressed,bedMoved;
    QMessageBox* msgInBox;
    bool aboutToExit;
    std::vector<std::string> m_stringList;

    QString m_qsNuclideName;

    QDateTime m_qdtInjectionDateTime;

    double m_dActivity;
    QString m_sActivityUnit;
    ReadInputInfo* m_pReadInputInfoBeta;

    QString m_qsNuclidedFolder;
    QString m_opticalImagePath, m_xrayImagePath;
    cv::Mat m_opticalImageMat, m_xrayImageMat;
    bool m_isOpticalChecked = false, m_isXrayChecked = false;

    QMessageBox initMessage;


    petIsotope  m_newIsotope;
    double m_dMaxCor;
    castor * m_castorFrame;
    bool m_bCastorSummedFinished;
    QVector<qreal> m_summedImg;
    Ui::betaEye *ui;
    bool m_calibrationMode;
    bool m_validationOn;
    bool m_bedCalibrated;
};

#endif // BETAEYE_H
