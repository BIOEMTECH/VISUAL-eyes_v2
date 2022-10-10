#include "headers/readinputinfo.h"

ReadInputInfo::ReadInputInfo():m_bUseExpDecay(false){}
ReadInputInfo::~ReadInputInfo(){}

void ReadInputInfo::readFile(){
    std::string homepath = getenv("HOME");
    QString qsHome = QString::fromStdString( homepath );
    QString qsFileName = qsHome + "\/.Visual-Eyes\/visualeyesinit";
    QFile inputFile(qsFileName);
    QString isoKey;
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in( &inputFile );
        while ( !in.atEnd() ) {
            QString line  = in.readLine();

            if ( line.isEmpty() ) continue;
            if ( line.startsWith("#") ) continue;

            QStringList tokens = line.split(":");

            if ( tokens[ 0 ] == "System")
                m_qsSystemName = tokens[1].trimmed();
            else if ( tokens[0]=="Collimators"){
                QString tmp=tokens[1].trimmed();
                QStringList tmpL=tmp.split(",");
                foreach (QString entry, tmpL) {
                   m_qslCollimators.append(entry.trimmed());
                }

            }
            else if ( tokens[ 0 ] == "Camera")
                m_qsCameraID = tokens[1].trimmed();
            else if ( tokens[ 0 ] == "Arduino")
                m_qsArduino = tokens[1].trimmed();
            else if ( tokens[ 0 ] == "head_A_x_param1")
                m_dHeadAxParam1 = tokens[1].toDouble();
            else if ( tokens[ 0 ] == "head_A_x_param2")
                m_dHeadAxParam2 = tokens[1].toDouble();
            else if ( tokens[ 0 ] == "head_A_y_param1")
                m_dHeadAyParam1 = tokens[1].toDouble();
            else if ( tokens[ 0 ] == "head_A_y_param2")
                m_dHeadAyParam2 = tokens[1].toDouble();
            else if ( tokens[ 0 ] == "head_B_x_param1")
                m_dHeadBxParam1 = tokens[1].toDouble();
            else if ( tokens[ 0 ] == "head_B_x_param2")
                m_dHeadBxParam2 = tokens[1].toDouble();
            else if ( tokens[ 0 ] == "head_B_y_param1")
                m_dHeadByParam1 = tokens[1].toDouble();
            else if ( tokens[ 0 ] == "head_B_y_param2")
                m_dHeadByParam2 = tokens[1].toDouble();           
            else if ( tokens[ 0 ] == "Energy_window_up")
                m_energyUp = tokens[1].toInt();
            else if ( tokens[ 0 ] == "Energy_window_low")
                m_energyLow = tokens[1].toInt();
            else if ( tokens[ 0 ] == "Raw_energy_up")
                m_rawenergy_up = tokens[1].toFloat();
            else if ( tokens[ 0 ] == "Raw_energy_low")
                m_rawenergy_low = tokens[1].toFloat();
            else if ( tokens[ 0 ] == "Time_window")
                m_time_window = tokens[1].toFloat();
            else if ( tokens[ 0 ] == "Print_raw"){
                QString tmp = tokens[1].trimmed();
                if(tmp=="ON" || tmp=="on" ||tmp=="On"){
                    m_print_mode=true;
                }else {
                    m_print_mode=false;
                }
            }
            else if ( tokens[ 0 ] == "Energies_A")
                m_qsEnergiesA = tokens[1].trimmed();
            else if ( tokens[ 0 ] == "Energies_B")
                m_qsEnergiesB = tokens[1].trimmed();
            else if ( tokens[ 0 ] == "Grid_A")
                m_qsGridA = tokens[1].trimmed();
            else if ( tokens[ 0 ] == "Grid_B")
                m_qsGridB = tokens[1].trimmed();
            else if ( tokens[ 0 ] == "Acceptance_angle")
                m_dAcceptanceAngle = tokens[1].toDouble();
            else if ( tokens[ 0 ] == "Castor_flood")
                m_qsCastorFloodFile = tokens[1].trimmed();
            else if ( tokens[ 0 ] == "Castor_meanVal")
                m_dCastorMeanVal = tokens[1].toDouble();
            else if ( tokens[ 0 ] == "Castor_thresVal")
                m_dCastorThresVal = tokens[1].toDouble();
            else if ( tokens[ 0 ] == "FPT_meanVal")
                m_dFPTMeanVal = tokens[1].toDouble();
            else if ( tokens[ 0 ] == "FPT_thresVal")
                m_dFPTThresVal = tokens[1].toDouble();
            else if ( tokens[0] == "nuclide_lim1")
                m_dNuclide_lim1 = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "nuclide_lim2")
                m_dNuclide_lim2 = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "nuclide_lim3")
                m_dNuclide_lim3 = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "nuclide_a1")
                m_dNuclide_a1 = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "nuclide_b1")
                m_dNuclide_b1 = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "nuclide_a2")
                m_dNuclide_a2 = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "nuclide_b2")
                m_dNuclide_b2 = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "nuclide_a3")
                m_dNuclide_a3 = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "nuclide_b3")
                m_dNuclide_b3 = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "deconvolution_res0")
                m_dRes0 = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "deconvolution_arg")
                m_dArg = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "deconvolution_dist1")
                m_iDist1 = tokens[ 1 ].toInt();
            else if ( tokens[0] == "deconvolution_dist2")
                m_iDist2 = tokens[ 1 ].toInt();
            else if ( tokens[0] == "deconvolution_pixelSize")
                m_dPixelSize = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "deconvolution_iterations")
                m_iIterations = tokens[ 1 ].toInt();
            else if ( tokens[0] == "deconvolution_dampar")
                m_dDampar = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "deconvolution_histAdj")
                m_dHistAdj = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "CastorSubsets")
                m_sCastorSubsets = tokens[ 1 ].trimmed();
            else if ( tokens[0] == "CastorIterations")
                m_sCastorIter = tokens[ 1 ].trimmed();
            else if ( tokens[0] == "CastorPSF"){
                if(tokens.size()>2){
                    m_sCastorPsf = tokens[ 1 ].trimmed()+"::"+tokens[3].trimmed();
                }else {
                    m_sCastorPsf = tokens[ 1 ].trimmed();
                }
            }else if (tokens[0].contains("name")){
                QStringList temp=tokens[0].split("_");
                isoKey=temp[0];
                m_qhPetIsotopesInfo[isoKey].append(tokens[1]);
            }
            else if (tokens[0]==isoKey+"_"+"lambda"){
                m_qhPetIsotopesInfo[isoKey].append(tokens[1]);

            /*
            else if ( tokens[0] == "F18_lambda")
                m_dF18_lambda = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Ga68_lambda")
                m_dGa68_lambda = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "C11_lambda")
                m_dC11_lambda = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "N13_lambda")
                m_dN13_lambda = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "O15_lambda")
                m_dO15_lambda = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Cu62_lambda")
                m_dCu62_lambda = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Cu64_lambda")
                m_dCu64_lambda = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Zr89_lambda")
                m_dZr89_lambda = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Rb82_lambda")
                m_dRb82_lambda = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "I124_lambda")
                m_dI124_lambda = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Br76_lambda")
                m_dBr76_lambda = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Tb152_lambda")
                m_dTb152_lambda = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "F18_preExp")
                m_dF18_preExp = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Ga68_preExp")
                m_dGa68_preExp = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "C11_preExp")
                m_dC11_preExp = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "N13_preExp")
                m_dN13_preExp = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "O15_preExp")
                m_dO15_preExp = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Cu62_preExp")
                m_dCu62_preExp = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Cu64_preExp")
                m_dCu64_preExp = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Zr89_preExp")
                m_dZr89_preExp = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Rb82_preExp")
                m_dRb82_preExp = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "I124_preExp")
                m_dI124_preExp = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Br76_preExp")
                m_dBr76_preExp = tokens[ 1 ].toDouble();
            else if ( tokens[0] == "Tb152_preExp")
                m_dTb152_preExp = tokens[ 1 ].toDouble();
            */

            }else if (tokens[0]==isoKey+"_"+"preExp"){
                m_qhPetIsotopesInfo[isoKey].append(tokens[1]);
            }else if ( tokens[0] == "Decay")
                m_bUseExpDecay = true;
            else if(tokens[0] == "Sensor_temperature_threshold")
                m_temp_threshold=tokens[1].toFloat();
            else if(tokens[0] == "Sensor_reference_temperature")
                m_ref_temp=tokens[1].toFloat();
            else if ( tokens[0] == "Gaussian_kernel")
                m_gaussKernel = tokens[1].toInt();
            else if ( tokens[0] == "Flip" ){
                QStringList inputFlips = tokens[ 1 ].split(",");
                foreach ( QString flip,  inputFlips){
                    m_qslFlips.append(flip.trimmed());
                }
            }
            else if ( tokens[0] == "Image_crop" ){
                QString tmp = tokens[1].trimmed();
                m_imgcrop = tmp.split(",");
            }
            else if ( tokens[0] == "Start_frame" ){
                m_startFrame= tokens[1].toInt();
            }
            else if ( tokens[0] == "End_frame" ){
                m_endFrame = tokens[1].toInt();
            }
            else if ( tokens[0] == "Step_frame" ){
                m_stepFrame = tokens[1].toInt();
            }

        }
        getPetIsotope(isoKey);
        inputFile.close();
        if(m_qsSystemName.contains("SGC")){
            readSpectCalibration(m_qslCollimators);
        }
    }
    else {
        QMessageBox::critical(0,"Visual-Eyes error","The input info file could not be open. Please contact technical suppport.");
    }

}

void ReadInputInfo::readSpectCalibration(QStringList collimators){
    QString spectFilepath=QDir::currentPath()+"/SPECT_calibration_files/";
    QString isoKey;
    foreach (QString collimator, collimators) {
        QString collimatorPath=spectFilepath+collimator+"/";
        QString isotopeFilepath=collimatorPath+collimator+"_isotopes.txt";
        QFile isotopeFile(isotopeFilepath);
        if (isotopeFile.open(QIODevice::ReadOnly)) {
            QTextStream in( &isotopeFile );
            while ( !in.atEnd() ) {
                QString line  = in.readLine();
                if ( line.isEmpty() ) continue;
                if ( line.startsWith("#") ) continue;
                QStringList tokens = line.split(":");


                if (tokens[0].contains("name")){
                   isoKey=tokens[1];
                   if (!m_qhCollimatorIsotopes[collimator].contains(isoKey))
                       m_qhCollimatorIsotopes[collimator].append(isoKey);
                }
                if (tokens[0].contains(isoKey))
                    m_qhIsotopesInfo[collimator+"_"+isoKey].append(line);


            }

        }
    }
}

spectIsotope ReadInputInfo::getSpectIsotope(QString colName, QString nuclName){
    double lim1=0.0, lim2=0.0, a1=0.0, a2=0.0, a3=0.0, b1=0.0, b2=0.0, b3=0.0;
    double peak=0.0, lambda=0.0;
    QString name, type;
    QString energyX, energyG;
    QString floodX, floodG;
    QString energyUpScatterX, energyLowScatterX;
    QString energyUpScatterG, energyLowScatterG;
    QString floodUpScatterX, floodLowScatterX;
    QString floodUpScatterG, floodLowScatterG;
    QString grid;
    QString voltage;
    double enWinUpX=0.0, enWinLowX=0.0, enWinUpG=0.0, enWinLowG=0.0, enWinUpScatterX=0.0, enWinLowScatterX=0.0, enWinUpScatterG=0.0, enWinLowScatterG=0.0;

    QStringList isotopeInfo=m_qhIsotopesInfo[colName+"_"+nuclName];
    foreach (QString attribute, isotopeInfo) {
        QStringList tokens = attribute.split(":");
        tokens[0].remove(nuclName+"_");
        if(tokens[0]=="name")
            name=tokens[1].trimmed();
        if(tokens[0].contains("type"))
            type=tokens[1].trimmed();

        ///Read energy files
        if(tokens[0]=="energies")
            energyG=tokens[1].trimmed();
        if(tokens[0]=="energies_x")
            energyX=tokens[1].trimmed();
        if(tokens[0]=="energies_g")
            energyG=tokens[1].trimmed();
        if(tokens[0]=="energies_up_x_sc")
            energyUpScatterX=tokens[1].trimmed();
        if(tokens[0]=="energies_low_x_sc")
            energyLowScatterX=tokens[1].trimmed();
        if(tokens[0]=="energies_up_g_sc")
            energyUpScatterG=tokens[1].trimmed();
        if(tokens[0]=="energies_low_g_sc")
            energyLowScatterG=tokens[1].trimmed();

        ///Read flood files
        if(tokens[0]=="flood")
            floodG=tokens[1].trimmed();
        if(tokens[0]=="flood_x")
            floodX=tokens[1].trimmed();
        if(tokens[0]=="flood_g")
            floodG=tokens[1].trimmed();
        if(tokens[0]=="flood_up_x_sc")
            floodUpScatterX=tokens[1].trimmed();
        if(tokens[0]=="flood_low_x_sc")
            floodLowScatterX=tokens[1].trimmed();
        if(tokens[0]=="flood_up_g_sc")
            floodUpScatterG=tokens[1].trimmed();
        if(tokens[0]=="flood_low_g_sc")
            floodLowScatterG=tokens[1].trimmed();

        ///Read grid
        if(tokens[0]=="grid")
            grid=tokens[1].trimmed();

        if(tokens[0]=="energy_window_up"){
            enWinUpG=tokens[1].trimmed().toDouble();
        }
        if(tokens[0]=="energy_window_low")
            enWinLowG=tokens[1].trimmed().toDouble();
        if(tokens[0]=="energy_window_up_g")
            enWinUpG=tokens[1].trimmed().toDouble();
        if(tokens[0]=="energy_window_low_g")
            enWinLowG=tokens[1].trimmed().toDouble();
        if(tokens[0]=="energy_window_up_x")
            enWinUpX=tokens[1].trimmed().toDouble();
        if(tokens[0]=="energy_window_low_x")
            enWinLowX=tokens[1].trimmed().toDouble();
        if(tokens[0]=="energy_window_up_x_sc")
            enWinUpScatterX=tokens[1].trimmed().toDouble();
        if(tokens[0]=="energy_window_low_x_sc")
            enWinLowScatterX=tokens[1].trimmed().toDouble();
        if(tokens[0]=="energy_window_up_g_sc")
            enWinUpScatterG=tokens[1].trimmed().toDouble();
        if(tokens[0]=="energy_window_low_g_sc")
            enWinLowScatterG=tokens[1].trimmed().toDouble();

        if(tokens[0]=="energy_peak")
            peak=tokens[1].trimmed().toDouble();
        if(tokens[0]=="lambda")
            lambda=tokens[1].trimmed().toDouble();
        if(tokens[0]=="arduino")
            voltage=tokens[1].trimmed();

        if(tokens[0]=="lim1")
            lim1 = tokens[1].toDouble();
        if(tokens[0]=="lim2")
            lim2 = tokens[1].toDouble();
        if( tokens[0]=="a1")
            a1 = tokens[1].toDouble();
        if(tokens[0]=="b1")
            b1 = tokens[1].toDouble();
        if(tokens[0]=="a2")
            a2 = tokens[1].toDouble();
        if(tokens[0]=="b2")
            b2 = tokens[1].toDouble();
        if(tokens[0]=="a3")
            a3 = tokens[1].toDouble();
        if(tokens[0]=="b3")
            b3 = tokens[1].toDouble();

    }
    int tid=0;
    if(type=="Type1"){
        tid=0;
    }else if (type=="Type2"){
        tid=1;
    }else{
        tid=2;
    }
    spectIsotope newIsotope(name,1);
    newIsotope.setType(tid);
    if(type=="Type1"){
        newIsotope.setEnergyG(energyG);
        newIsotope.setFloodG(floodG);

        newIsotope.setEnWinUpG(enWinUpG);
        newIsotope.setEnWinLowG(enWinLowG);

    }else if(type=="Type2"){
        newIsotope.setEnergyG(energyG);
        newIsotope.setEnergyX(energyX);
        newIsotope.setEnergyUpScatterX(energyUpScatterX);
        newIsotope.setEnergyLowScatterX(energyLowScatterX);
        newIsotope.setFloodG(floodG);
        newIsotope.setFloodX(floodX);
        newIsotope.setFloodUpScatterX(floodUpScatterX);
        newIsotope.setFloodLowScatterX(floodLowScatterX);

        newIsotope.setEnWinUpG(enWinUpG);
        newIsotope.setEnWinLowG(enWinLowG);
        newIsotope.setEnWinUpX(enWinUpX);
        newIsotope.setEnWinLowX(enWinLowX);
        newIsotope.setEnWinUpScatterX(enWinUpScatterX);
        newIsotope.setEnWinLowScatterX(enWinLowScatterX);

    }else{

        newIsotope.setEnergyG(energyG);
        newIsotope.setEnergyUpScatterG(energyUpScatterG);
        newIsotope.setEnergyLowScatterG(energyLowScatterG);
        newIsotope.setFloodG(floodG);
        newIsotope.setFloodUpScatterG(floodUpScatterG);
        newIsotope.setFloodLowScatterG(floodLowScatterG);

        newIsotope.setEnWinUpG(enWinUpG);
        newIsotope.setEnWinLowG(enWinLowG);
        newIsotope.setEnWinUpScatterG(enWinUpScatterG);
        newIsotope.setEnWinLowScatterG(enWinLowScatterG);
    }
    newIsotope.setGrid(grid);
    newIsotope.setEnergyPeak(peak);
    newIsotope.setLambda(lambda);
    newIsotope.setVoltage(voltage);
    newIsotope.setActivityCurves(lim1,lim2,0.0,a1,b1,a2,b2,a3,b3);



    return newIsotope;

}



petIsotope ReadInputInfo::getPetIsotope(QString nuclName){

    double lambda=0.0, preExp=0.0;
    QString name;


    foreach(QString isotope, m_qhPetIsotopesInfo.keys()){
        QStringList info=m_qhPetIsotopesInfo[isotope];
        if (info[0]==nuclName){
            name=info[0].trimmed();
            lambda=info[1].toDouble();
            preExp=info[2].toDouble();
        }
    }

    petIsotope newIsotope(nuclName,2);
    newIsotope.setDecayParameters(lambda,preExp);
    newIsotope.setActivityCurves(m_dNuclide_lim1,m_dNuclide_lim2,m_dNuclide_lim3,m_dNuclide_a1,m_dNuclide_b1,\
                                 m_dNuclide_a2,m_dNuclide_a2,m_dNuclide_a3,m_dNuclide_b3);

    return newIsotope;

}

