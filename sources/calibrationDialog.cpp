//////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file calibrationDialog.cpp
///
///	@brief dialog with aquisition related details for the user to fill in and save to database.
///
///	@author Aphrodite Toufa
/// @date   Created: 07.12.2018
/// @date   Updated: 29.7.2019
///
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QLocale>
#include <QDebug>
#include "headers/calibrationDialog.h"
#include "ui_calibrationDialog.h"

calibrationDialog::calibrationDialog(ReadInputInfo * inputInfo, QString qsWhichEye, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calibrationDialog),
    m_pInputInfo(inputInfo),
    m_qsEyeName(qsWhichEye)
{
    ui->setupUi(this);

    m_isValidationChecked=true;
    m_isCalibrationChecked=false;
    connect(ui->cb_validation,SIGNAL(clicked()),this,SLOT(setCheckstateValidation()),Qt::UniqueConnection);
    connect(ui->cb_calibration,SIGNAL(clicked()),this,SLOT(setCheckstateCalibration()),Qt::UniqueConnection);

    Init();
}

calibrationDialog::~calibrationDialog(){ delete ui; }



void calibrationDialog::Init(){
    QLocale locale(QLocale::English);
    QString date = locale.toString( QDateTime::currentDateTime(), "dd.MM.yyyy hh:mm:ss AP");
    ui->dTime_ingection->setDateTime( QDateTime::currentDateTime().fromString( date, "dd.MM.yyyy hh:mm:ss AP" )  );

    changeVolt = false;
    fastDynamic=false;

    ui->dSB_volume->setMaximum(10000000);
    ui->dSB_activity->setMaximum(10000000);
    ui->cb_validation->setCheckable(true);
    ui->cb_validation->setCheckState( Qt::Checked );

    ui->cb_calibration->setCheckable(true);
    ui->cb_calibration->setCheckState( Qt::Unchecked );


    if ( m_qsEyeName == "gammaEye"){        
        QSqlQuery query,q;
        ui->LE_studyID->setText( QString::number( Inventory_calculator() ) );
        ui->CB_radioNuclide->clear();
        ui->cB_collimator->clear();
        QString find_collimators = "SELECT * FROM Collimator";
        query.exec(find_collimators);
        if( query.first() ) {
            do {
                QString name = query.value("coll_name").toString();
                int cid = query.value("collimator_id").toInt();
                if (m_pInputInfo->getCollimators().contains(name)){

                    ui->cB_collimator->addItem(name, cid);
                    ui->cB_collimator->setItemData(cid, "Low energy, high resolution", Qt::ToolTipRole);

                }
            }while(query.next());
        }


    }
    else {
        QSqlQuery query,q;
        ui->LE_studyID->setText( QString::number( Inventory_calculator() ) );
        ui->CB_radioNuclide->clear();
        QString nuclides = "SELECT * FROM radionuclide where id_modality = 2";
        query.exec(nuclides);
        if( query.first() ) {
            do {
                QString name = query.value("nuclide_name").toString();
                int nid = query.value("nuclide_id").toInt();
                ui->CB_radioNuclide->addItem(name, nid);
            }while(query.next());
        }

        ui->CB_radioNuclide->setCurrentIndex( 1 );

    }
    if ( m_qsEyeName == "gammaEye"){
        connect(ui->CB_radioNuclide,SIGNAL(currentIndexChanged(int)),this,SLOT(on_CB_radionuclide_currentIndexChanged(int)));
        connect(ui->cB_collimator,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cB_collimator_currentIndexChanged(int)));
    }
}

int calibrationDialog::Inventory_calculator()
{
    int inventory=0;
    QSqlQuery inv;
    QString max_inv = "select MAX(study_id) as max from Calibration order by deviceid ";
    inv.exec( max_inv );
    if(inv.first()) {
        int max_inv = inv.value("max").toInt();
        inventory = max_inv+1;
        ui->LE_studyID->setText(QString::number( inventory ) );
    }
    return inventory;
}

void calibrationDialog::getTimeSettings(int duration,int frame, QString d_unit,QString f_unit,bool fDynamic)
{
    DURATION = duration;
    FRAME = frame;
    dur_unit = std::move(d_unit);
    frame_unit = std::move(f_unit);
    fastDynamic = fDynamic;
}

void calibrationDialog::on_cb_validation(bool checked)
{

     if (m_qsEyeName=="gammaEye"&&checked)
          on_cB_collimator_currentIndexChanged(ui->cB_collimator->currentIndex());

}

void calibrationDialog::on_cb_calibration(bool checked)
{
      if (m_qsEyeName=="gammaEye"&&checked)
            on_cB_collimator_currentIndexChanged(ui->cB_collimator->currentIndex());
}


void calibrationDialog::setCheckstateValidation(){
    if( m_isValidationChecked ){
       ui->cb_validation->setCheckable(false);
       ui->cb_validation->setChecked(false);
       m_isValidationChecked = false;
       on_cb_validation(false);
    }
    else {
       ui->cb_validation->setCheckable(true);
       ui->cb_validation->setChecked(true);
       m_isValidationChecked = true;
       m_isCalibrationChecked = false;
       on_cb_validation(true);
       ui->cb_calibration->setChecked(false);

    }
}

void calibrationDialog::setCheckstateCalibration(){
    if( m_isCalibrationChecked ){
      ui->cb_calibration->setCheckable(false);
      ui->cb_calibration->setChecked(false);
      m_isCalibrationChecked = false;
      on_cb_calibration(false);
    }
    else {
      ui->cb_calibration->setCheckable(true);
      ui->cb_calibration->setChecked(true);
      m_isCalibrationChecked = true;
      m_isValidationChecked = false;
      on_cb_calibration(true);
      ui->cb_validation->setChecked(false);

    }
}


void calibrationDialog::save_Session(const QString& fileDir,QString op,QString startTime,QString endTime) //Save Study's Details and selections to Database(From Study Details dialog)//
{
    ////get global variables properties from Study Details dialog
    int deviceid, modid;
    if (m_qsEyeName == "gammaEye"){
      deviceid=1;
      modid=1;
    }else {
      deviceid = 2;
      modid = 2;
    }


    const QString& devop=std::move(op);
    int InitActivity_unit=0;
    started = std::move(startTime);
    ended = std::move(endTime);



    ///LINE EDITS
    ///
    QString study_name = "Flood experiment";
    QString comments = ui->TE_comments->toPlainText();

    /////DATES
    QDateTime dateTime = ui->dTime_ingection->dateTime();

    ////doubleSpinBoxes
    double activity = ui->dSB_activity->value();
    double volume = ui->dSB_volume->value();
    ///from CB'S
    int nID = ui->CB_radioNuclide->itemData(ui->CB_radioNuclide->currentIndex()).toInt();

    ///SQL QUERY//
    QSqlQuery q;
    QString session = " INSERT INTO Calibration(date_time,name,operator_name,volume,activity,exp_duration,timeUnit_exp,frame,timeUnit_frame,";
    session += " start_time,fin_time, deviceid, id_modality,nuclide_id,radioUnit,comments,fileDirectory) VALUES( ";
    session += " :date_time,:name,:operator_name,:volume,:activity,:exp_duration,:timeUnit_exp,:frame,:timeUnit_frame,:start_time,:fin_time,:deviceid,:id_modality,:nuclide_id,:radioUnit,:comments,:fileDirectory) ";
    q.prepare(session);

    q.bindValue(":date_time",dateTime);
    q.bindValue(":name",study_name);
    q.bindValue(":operator_name",devop);
    q.bindValue(":volume",volume);
    q.bindValue(":activity",activity);
    q.bindValue(":exp_duration",DURATION);
    q.bindValue(":timeUnit_exp",dur_unit );
    q.bindValue(":frame",FRAME);
    q.bindValue(":timeUnit_frame",frame_unit);
    q.bindValue(":start_time",started);
    q.bindValue(":fin_time",ended);
    q.bindValue(":deviceid",deviceid);
    q.bindValue(":id_modality",modid);
    q.bindValue(":nuclide_id",nID);
    q.bindValue(":radioUnit",InitActivity_unit);
    q.bindValue(":comments",comments);
    q.bindValue(":fileDirectory",fileDir);

    q.exec();
    const int new_id = q.lastInsertId().toInt();
    QString msg = q.lastError().databaseText();

    if (msg.length()>0)
        QMessageBox::question(this, "Error", msg, QMessageBox::Ok);
    else {
        newID = QString::number(new_id);
        ui->LE_studyID->setText( QString::number(Inventory_calculator() ) );
    }
}

void calibrationDialog::closeEvent(QCloseEvent* e){ e->accept(); }

void calibrationDialog::on_PB_previous_clicked()
{
    this->hide();
    emit previousPressed();
}

void calibrationDialog::on_PB_next_clicked()
{

    this->hide();
    emit nextPressed();
    if( changeVolt ) {
        spectIsotope chosenIsotope=m_pInputInfo->getSpectIsotope(ui->cB_collimator->currentText(),ui->CB_radioNuclide->currentText());
        emit sendNuclide( chosenIsotope.getVoltage() );
        changeVolt = false;
    }

    QString radioUnit;
    if ( ui->rb_mBq_2->isChecked() )
        radioUnit = "MBq";
    else
        radioUnit = "uCi";


    qDebug() << "Valid " << m_isValidationChecked << endl;
    emit sendDacayInfo( ui->cB_collimator->currentText(), ui->CB_radioNuclide->currentText(), ui->CB_radioNuclide->currentText(), ui->dTime_ingection->dateTime(), ui->dSB_activity->value(), radioUnit );
    emit sendCalibrationID( ui->LE_studyID->text(),m_isValidationChecked);

    return;
}

void calibrationDialog::requestNewStudyID()
{
    emit sendCalibrationID(ui->LE_studyID->text(),ui->cb_validation->isChecked());
}

void calibrationDialog::on_PB_clear_clicked()
{
    ui->TE_comments->clear();
    ui->dSB_activity->clear();
    ui->dSB_volume->clear();
    Init();
}

void calibrationDialog::on_CB_radionuclide_currentIndexChanged( int index )
{
    int nucl = ui->CB_radioNuclide->itemData(index).toInt();
    if (m_qsEyeName == "gammaEye"){
        nuclideID = nucl;
        changeVolt = true;
    }
}
void calibrationDialog::on_cB_collimator_currentIndexChanged( int index )
{
    ui->CB_radioNuclide->clear();
    QStringList availIsotopes= m_pInputInfo->getHCollimators()[ui->cB_collimator->currentText()];
    QSqlQuery query;
    QString nuclides = "SELECT * FROM radionuclide where id_modality = 1";
    qDebug() << "Changing now "<<   m_isValidationChecked << " " << m_isCalibrationChecked<< endl;
    query.exec(nuclides);
    if( query.first() ) {
        do {
            QString name = query.value("nuclide_name").toString();
            int nid = query.value("nuclide_id").toInt();
            spectIsotope newIsotope=m_pInputInfo->getSpectIsotope(ui->cB_collimator->currentText(),name);
            if(availIsotopes.contains(name) && m_isValidationChecked && newIsotope.getType()==0){
                ui->CB_radioNuclide->addItem(name, nid);
            }else if (availIsotopes.contains(name) && m_isCalibrationChecked){
                ui->CB_radioNuclide->addItem(name, nid);
            }
        }while(query.next());
    }

}
