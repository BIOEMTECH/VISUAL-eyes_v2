#ifndef ISOTOPE_H
#define ISOTOPE_H
#include <QString>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <vector>
#include <iostream>
#include <QDebug>

class isotope
{
public:
    isotope(){};
    isotope(QString name, int modality);
    isotope(const isotope& t)
    {
        std::cout << "Copy constructor called " << std::endl;
    }

    isotope& operator=(const isotope& t)
    {
        std::cout << "Assignment operator called " << std::endl;
        return *this;
    }


    ~isotope();

    inline QString getName(){return m_qsIsotopeName;}
    inline int getId(){return m_iId;}
    inline int getModality(){return m_iModality;}
    void setActivityCurves(double,double, double, double, double, double, double, double, double);
    inline double getLimit1(){return m_dLim1;}
    inline double getLimit2(){return m_dLim2;}
    inline double getLimit3(){return m_dLim3;}
    inline double getA1(){return m_dA1;}
    inline double getB1(){return m_dB1;}
    inline double getA2(){return m_dA2;}
    inline double getB2(){return m_dB2;}
    inline double getA3(){return m_dA3;}
    inline double getB3(){return m_dB3;}



protected:


    QString m_qsIsotopeName;
    int m_iId;
    int m_iModality;
    void m_fRetrieveId();

    ///Activity curves
    double m_dLim1;
    double m_dLim2;
    double m_dLim3;
    double m_dA1;
    double m_dB1;
    double m_dA2;
    double m_dB2;
    double m_dA3;
    double m_dB3;

};

class spectIsotope : public isotope
{
public:

    spectIsotope();
    spectIsotope(QString name, int modality);

    virtual ~spectIsotope(){};




    void setType(int);
    void setEnergyPeak(double);
    void setLambda(double);
    void setVoltage(QString);

    void setEnergyX(QString);
    void setEnergyG(QString);
    void setEnergyUpScatterX(QString);
    void setEnergyLowScatterX(QString);
    void setEnergyUpScatterG(QString);
    void setEnergyLowScatterG(QString);

    void setFloodX(QString);
    void setFloodG(QString);
    void setFloodUpScatterX(QString);
    void setFloodLowScatterX(QString);
    void setFloodUpScatterG(QString);
    void setFloodLowScatterG(QString);
    void setGrid(QString);

    void setEnWinUpX(double);
    void setEnWinLowX(double);
    void setEnWinUpG(double);
    void setEnWinLowG(double);
    void setEnWinUpScatterX(double);
    void setEnWinLowScatterX(double);
    void setEnWinUpScatterG(double);
    void setEnWinLowScatterG(double);




    inline int getType(){return  m_qsType;}
    inline double getEnergyPeak(){return m_dEnergyPeak;}
    inline double getLambda(){return m_dLambda;}

    inline QString getVoltage(){return m_qsVoltageScript;}
    inline QString getEnergyX(){return m_qsEnergyX;}
    inline QString getEnergyG(){return m_qsEnergyG;}
    inline QString getEnergyUpScatterX(){return m_qsEnergyUpScatterX;}
    inline QString getEnergyLowScatterX(){return m_qsEnergyLowScatterX;}
    inline QString getEnergyUpScatterG(){return m_qsEnergyUpScatterG;}
    inline QString getEnergyLowScatterG(){return m_qsEnergyLowScatterG;}

    inline QString getFloodX(){return m_qsFloodX;}
    inline QString getFloodG(){return m_qsFloodG;}
    inline QString getFloodUpScatterX(){return m_qsFloodUpScatterX;}
    inline QString getFloodLowScatterX(){return m_qsFloodLowScatterX;}
    inline QString getFloodUpScatterG(){return m_qsFloodUpScatterG;}
    inline QString getFloodLowScatterG(){return m_qsFloodLowScatterG;}
    inline QString getGrid(){return m_qsGrid;}


    inline double getEnWinUpX(){return m_dEnWinUpX;}
    inline double getEnWinLowX(){return m_dEnWinLowX;}
    inline double getEnWinUpG(){return m_dEnWinUpG;}
    inline double getEnWinLowG(){return m_dEnWinLowG;}
    inline double getEnWinUpScatterX(){return m_dEnWinUpScatterX;}
    inline double getEnWinLowScatterX(){return m_dEnWinLowScatterX;}
    inline double getEnWinUpScatterG(){return m_dEnWinUpScatterG;}
    inline double getEnWinLowScatterG(){return m_dEnWinLowScatterG;}



private:
    enum isotopeTypes{ISO_T1, ISO_T2, ISO_T3};

    isotopeTypes m_qsType;
    QString m_qsVoltageScript;

    ///Calibration files
    QString m_qsEnergyX;
    QString m_qsEnergyG;
    QString m_qsFloodX;
    QString m_qsFloodG;
    QString m_qsEnergyUpScatterX;
    QString m_qsEnergyLowScatterX;
    QString m_qsFloodUpScatterX;
    QString m_qsFloodLowScatterX;

    QString m_qsEnergyUpScatterG;
    QString m_qsEnergyLowScatterG;
    QString m_qsFloodUpScatterG;
    QString m_qsFloodLowScatterG;

    QString m_qsGrid;

    double m_dEnWinUpX;
    double m_dEnWinLowX;
    double m_dEnWinUpG;
    double m_dEnWinLowG;
    double m_dEnWinUpScatterX;
    double m_dEnWinLowScatterX;
    double m_dEnWinUpScatterG;
    double m_dEnWinLowScatterG;

    double m_dEnergyPeak;
    double m_dLambda;

};



class petIsotope : public isotope
{
public:
    petIsotope();
    petIsotope(QString name, int modality);
    virtual ~petIsotope(){};

    void setDecayParameters(double,double);
    inline double getLambda(){return m_dLambda;}
    inline double getPreExp(){return m_dPreExp;}

private:

    double m_dLambda;
    double m_dPreExp;

};

#endif // ISOTOPE_H
