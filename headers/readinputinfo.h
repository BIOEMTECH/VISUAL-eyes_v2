#ifndef READINPUTINFO_H
#define READINPUTINFO_H

/* This class read the file located in .Visual-Eyes which contains information about the system. In particular:
 * \The name of the system, for each nucleid the name of the files and the camera id. */
#include <QString>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QHash>
#include "headers/isotope.h"

class ReadInputInfo
{
public:
    ReadInputInfo();
    ~ReadInputInfo();

    void readFile();
    void readSpectCalibration(QStringList);

    inline QString getSystemName(){return m_qsSystemName; }

    //---> For gamma

    inline double getDeconvRes0(){ return m_dRes0; }
    inline double getDeconvArg(){ return m_dArg; }
    inline int getDeconvDist1(){ return m_iDist1; }
    inline int getDeconvDist2(){ return m_iDist2; }
    inline double getDeconvPixelSize(){ return m_dPixelSize; }
    inline int getDeconvIterations(){ return m_iIterations; }
    inline double getDeconvDampar(){ return m_dDampar; }
    inline double getDeconvHistAdj(){ return m_dHistAdj; }//<----

    //---> For beta
    inline double getHeadAxParam1(){ return m_dHeadAxParam1; }
    inline double getHeadAxParam2(){ return m_dHeadAxParam2; }

    inline double getHeadAyParam1(){ return m_dHeadAyParam1; }
    inline double getHeadAyParam2(){ return m_dHeadAyParam2; }

    inline double getHeadBxParam1(){ return m_dHeadBxParam1; }
    inline double getHeadBxParam2(){ return m_dHeadBxParam2; }

    inline double getHeadByParam1(){ return m_dHeadByParam1; }
    inline double getHeadByParam2(){ return m_dHeadByParam2; }

    inline QString getEnergiesAFileName(){ return m_qsEnergiesA; }
    inline QString getEnergiesBFileName(){ return m_qsEnergiesB; }

    inline QString getGridAFileName(){ return m_qsGridA; }
    inline QString getGridBFileName(){ return m_qsGridB; }
    inline QString getFloodFileName(){ return m_qsFlood; }

    inline double getAcceptanceAngle(){ return m_dAcceptanceAngle; }

    inline double getFPTMeanVal(){ return m_dFPTMeanVal; }
    inline double getFPTThresVal(){ return m_dFPTThresVal; }

    inline QString getCastorFloodFileName(){ return m_qsCastorFloodFile; }
    inline double getCastorMeanVal(){ return m_dCastorMeanVal; }
    inline double getCastorThresVal(){ return m_dCastorThresVal; }

    inline QString getCastorIter(){ return m_sCastorIter; }
    inline QString getCastorSubsets(){ return m_sCastorSubsets; }
    inline QString getCastorPsf(){ return m_sCastorPsf; }

    inline double getNuclide_lim1(){ return m_dNuclide_lim1; }
    inline double getNuclide_lim2(){ return m_dNuclide_lim2; }
    inline double getNuclide_lim3(){ return m_dNuclide_lim3; }

    inline double getNuclide_a1(){ return m_dNuclide_a1; }
    inline double getNuclide_b1(){ return m_dNuclide_b1; }

    inline double getNuclide_a2(){ return m_dNuclide_a2; }
    inline double getNuclide_b2(){ return m_dNuclide_b2; }

    inline double getNuclide_a3(){ return m_dNuclide_a3; }
    inline double getNuclide_b3(){ return m_dNuclide_b3; }
    /*
    inline double getF18_lambda()  { return m_dF18_lambda; }
    inline double getGa68_lambda() { return m_dGa68_lambda; }
    inline double getC11_lambda()  { return m_dC11_lambda; }
    inline double getN13_lambda()  { return m_dN13_lambda; }
    inline double getO15_lambda()  { return m_dO15_lambda; }
    inline double getCu62_lambda() { return m_dCu62_lambda; }
    inline double getCu64_lambda() { return m_dCu64_lambda; }
    inline double getZr89_lambda() { return m_dZr89_lambda; }
    inline double getRb82_lambda() { return m_dRb82_lambda; }
    inline double getI124_lambda() { return m_dI124_lambda; }
    inline double getBr76_lambda() { return m_dBr76_lambda; }
    inline double getTb152_lambda() { return m_dTb152_lambda; }


    inline double getF18_preExp()  { return m_dF18_preExp; }
    inline double getGa68_preExp() { return m_dGa68_preExp; }
    inline double getC11_preExp()  { return m_dC11_preExp; }
    inline double getN13_preExp()  { return m_dN13_preExp; }
    inline double getO15_preExp()  { return m_dO15_preExp; }
    inline double getCu62_preExp() { return m_dCu62_preExp; }
    inline double getCu64_preExp() { return m_dCu64_preExp; }
    inline double getZr89_preExp() { return m_dZr89_preExp; }
    inline double getRb82_preExp() { return m_dRb82_preExp; }
    inline double getI124_preExp() { return m_dI124_preExp; }
    inline double getBr76_preExp() { return m_dBr76_preExp; }
    inline double getTb152_preExp() { return m_dTb152_preExp; }
    */

    inline bool useExpDecay() { return m_bUseExpDecay; }
    inline int getGaussKernel(){ return m_gaussKernel; }

    inline int getEnergyWindowUp(){ return m_energyUp; }
    inline int getEnergyWindowLow(){ return m_energyLow; }
    inline float getTemperatureThreshold(){ return m_temp_threshold; }
    inline float getReferenceTemperature(){ return m_ref_temp; }

    inline float getRawEnergyUp(){ return m_rawenergy_up; }
    inline float getRawEnergyLow(){ return m_rawenergy_low; }
    inline float getTimeWindow(){ return m_time_window; }
    inline bool getPrintMode(){ return m_print_mode; }


    inline QHash<QString,QStringList> getHCollimators(){return m_qhCollimatorIsotopes;}
    inline QHash<QString,QStringList> getIsotopesInfo(){return  m_qhIsotopesInfo;}
    spectIsotope getSpectIsotope(QString,QString);
    petIsotope getPetIsotope(QString);


    //For both
    inline QStringList getFlips(){ return m_qslFlips; }
    inline QStringList getCrop(){ return m_imgcrop; }
    inline int getOpticalStart(){ return m_startFrame; }
    inline int getOpticalEnd(){ return m_endFrame; }
    inline int getOpticalStep(){ return m_stepFrame; }
    inline QString getCameraID(){return m_qsCameraID; }
    inline QString getArduinoCom(){return m_qsArduino; }
    inline QStringList getCollimators(){return m_qslCollimators;}



private:
    QString m_qsSystemName;

    QString m_qsCameraID;
    QString m_qsArduino;

    //For Beta where we do not have a specific nuclide
    QString m_qsGridA;
    QString m_qsGridB;

    QString m_qsEnergiesA;
    QString m_qsEnergiesB;

    QString m_qsFlood;

    QStringList m_qslFlips;
    QString m_qsCastorFloodFile;


    double m_dHeadAxParam1;
    double m_dHeadAxParam2;

    double m_dHeadAyParam1;
    double m_dHeadAyParam2;

    double m_dHeadBxParam1;
    double m_dHeadBxParam2;

    double m_dHeadByParam1;
    double m_dHeadByParam2;

    double m_dAcceptanceAngle;

    double m_dFPTMeanVal;
    double m_dFPTThresVal;

    double m_dCastorMeanVal;
    double m_dCastorThresVal;

    double m_dRes0; //: 2.2
    double m_dArg; //: 0.025;
    int m_iDist1; //: 10;
    int m_iDist2; //: 30;
    double m_dPixelSize; //: 1.2;
    int m_iIterations; //: 8;
    double m_dDampar; //: 4;
    double m_dHistAdj; //: 0.002;

    QString m_sCastorSubsets;
    QString m_sCastorIter;
    QString m_sCastorPsf;


    double m_dNuclide_lim1;
    double m_dNuclide_lim2;
    double m_dNuclide_lim3;

    double m_dNuclide_a1;
    double m_dNuclide_b1;

    double m_dNuclide_a2;
    double m_dNuclide_b2;

    double m_dNuclide_a3;
    double m_dNuclide_b3;
    /*
    double m_dF18_lambda;
    double m_dGa68_lambda;
    double m_dC11_lambda;
    double m_dN13_lambda;
    double m_dO15_lambda;
    double m_dCu62_lambda;
    double m_dCu64_lambda;
    double m_dZr89_lambda;
    double m_dRb82_lambda;
    double m_dI124_lambda;
    double m_dBr76_lambda;
    double m_dTb152_lambda;

    double m_dF18_preExp;
    double m_dGa68_preExp;
    double m_dC11_preExp;
    double m_dN13_preExp;
    double m_dO15_preExp;
    double m_dCu62_preExp;
    double m_dCu64_preExp;
    double m_dZr89_preExp;
    double m_dRb82_preExp;
    double m_dI124_preExp;
    double m_dBr76_preExp;
    double m_dTb152_preExp;
    */
    int m_energyUp;
    int m_energyLow;
    float m_temp_threshold;
    float m_ref_temp;
    float m_time_window;
    float m_rawenergy_up;
    float m_rawenergy_low;
    bool m_print_mode;

    bool m_bUseExpDecay;
    int m_gaussKernel;
    QStringList m_imgcrop;
    QStringList m_qslCollimators;
    int m_startFrame, m_endFrame,m_stepFrame;
    QHash<QString,QStringList> m_qhCollimatorIsotopes;
    QHash<QString,QStringList> m_qhIsotopesInfo;

    QHash<QString,QStringList> m_qhPetIsotopesInfo;

};

#endif // READINPUTINFO_H
