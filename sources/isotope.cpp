#include "headers/isotope.h"

isotope::isotope(QString name, int modality):m_qsIsotopeName(name),m_iModality(modality)
{
    ///Retrieve isotope id from SQL database
    ///
    m_fRetrieveId();
    m_dLim1=0.0;
    m_dLim2=0.0;
    m_dLim3=0.0;
    m_dA1=0.0;
    m_dB1=0.0;
    m_dA2=0.0;
    m_dB2=0.0;
    m_dA3=0.0;
    m_dB3=0.0;
}

isotope::~isotope(){}


void isotope::m_fRetrieveId(){
    QSqlQuery query;
    QString retrieve_id = "SELECT * FROM BET.radionuclide WHERE nuclide_name='"+ m_qsIsotopeName+"'";
    query.exec(retrieve_id);
    if(query.next()){
        m_iId = query.value("nuclide_id").toInt();
    }

}

void isotope::setActivityCurves(double lim1,double lim2, double lim3, double a1, double b1, double a2, double b2, double a3, double b3){
    m_dLim1=lim1;
    m_dLim2=lim2;
    m_dLim3=lim3;
    m_dA1=a1;
    m_dB1=b1;
    m_dA2=a2;
    m_dB2=b2;
    m_dA3=a3;
    m_dB3=b3;
}




spectIsotope::spectIsotope():isotope(){}

spectIsotope::spectIsotope(QString name, int modality):isotope(name, modality)
{

    ///Retrieve isotope id from SQL database
    ///
    m_fRetrieveId();

}

void spectIsotope::setType(int type){
    if(type==0)
        m_qsType= isotopeTypes::ISO_T1;
    else if(type==1)
        m_qsType= isotopeTypes::ISO_T2;
    else
        m_qsType= isotopeTypes::ISO_T3;
}

void spectIsotope::setEnergyPeak(double peak){m_dEnergyPeak=peak;}
void spectIsotope::setLambda(double lambda){m_dLambda=lambda;}
void spectIsotope::setVoltage(QString voltage){m_qsVoltageScript=voltage;}

void spectIsotope::setEnergyX(QString energyX){m_qsEnergyX=energyX;}
void spectIsotope::setEnergyG(QString energyG){m_qsEnergyG=energyG;}
void spectIsotope::setEnergyUpScatterX(QString energyUpScatterX){m_qsEnergyUpScatterX=energyUpScatterX;}
void spectIsotope::setEnergyLowScatterX(QString energyLowScatterX){m_qsEnergyLowScatterX=energyLowScatterX;}
void spectIsotope::setEnergyUpScatterG(QString energyUpScatterG){m_qsEnergyUpScatterG=energyUpScatterG;}
void spectIsotope::setEnergyLowScatterG(QString energyLowScatterG){m_qsEnergyLowScatterG=energyLowScatterG;}

void spectIsotope::setFloodX(QString floodX){m_qsFloodX=floodX;}
void spectIsotope::setFloodG(QString floodG){m_qsFloodG=floodG;}
void spectIsotope::setFloodUpScatterX(QString floodUpScatterX){m_qsFloodUpScatterX=floodUpScatterX;}
void spectIsotope::setFloodLowScatterX(QString floodLowScatterX){m_qsFloodLowScatterX=floodLowScatterX;}
void spectIsotope::setFloodUpScatterG(QString floodUpScatterG){m_qsFloodUpScatterG=floodUpScatterG;}
void spectIsotope::setFloodLowScatterG(QString floodLowScatterG){m_qsFloodLowScatterG=floodLowScatterG;}
void spectIsotope::setGrid(QString grid){m_qsGrid=grid;}
void spectIsotope::setEnWinUpX(double enWinUpX){m_dEnWinUpX=enWinUpX;}
void spectIsotope::setEnWinLowX(double enWinLowX){m_dEnWinLowX=enWinLowX;}
void spectIsotope::setEnWinUpG(double enWinUpG){m_dEnWinUpG=enWinUpG;}
void spectIsotope::setEnWinLowG(double enWinLowG){m_dEnWinLowG=enWinLowG;}
void spectIsotope::setEnWinUpScatterX(double enWinUpScatterX){m_dEnWinUpScatterX=enWinUpScatterX;}
void spectIsotope::setEnWinLowScatterX(double enWinLowScatterX){m_dEnWinLowScatterX=enWinLowScatterX;}
void spectIsotope::setEnWinUpScatterG(double enWinUpScatterG){m_dEnWinUpScatterG=enWinUpScatterG;}
void spectIsotope::setEnWinLowScatterG(double enWinLowScatterG){m_dEnWinLowScatterG=enWinLowScatterG;}




petIsotope::petIsotope():isotope(){}

petIsotope::petIsotope(QString name, int modality):isotope(name, modality)
{

    ///Retrieve isotope id from SQL database
    ///
    m_fRetrieveId();

}

void petIsotope::setDecayParameters(double lambda, double preExp){
    m_dLambda=lambda;
    m_dPreExp=preExp;
}
