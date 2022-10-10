//////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file detailsDialog.cpp
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
#include "headers/detailsDialog.h"
#include "ui_detailsDialog.h"

detailsDialog::detailsDialog(ReadInputInfo * inputInfo, QString qsWhichEye, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::detailsDialog),
    m_pInputInfo(inputInfo),
    m_qsEyeName(qsWhichEye)
{

    ui->setupUi(this);
    Init();
}

detailsDialog::~detailsDialog(){ delete ui; }

void detailsDialog::Init(){
    ui->dE_studyDate->setDate(QDate::currentDate());

    QLocale locale(QLocale::English);
    QString date = locale.toString( QDateTime::currentDateTime(), "dd.MM.yyyy hh:mm:ss AP");
    ui->dTime_ingection->setDateTime( QDateTime::currentDateTime().fromString( date, "dd.MM.yyyy hh:mm:ss AP" )  );

    changeVolt = false;
    fastDynamic=false;

    ui->dSB_volume->setMaximum(10000000);
    ui->dSB_injActivity->setMaximum(10000000);

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
                }
            }while(query.next());
        }


        ui->CB_ing_path->clear();
        q.exec("SELECT * FROM InjectionPath ");
        if(q.first()) {
            do {
                QString p_name = q.value("name").toString();
                int id = q.value("path_id").toInt();
                ui->CB_ing_path->addItem(p_name,id);
            }while(q.next());
        }
    }
    else {
        QSqlQuery query,q;
        ui->lb_collimator->hide();
        ui->cB_collimator->hide();
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

        ui->CB_ing_path->clear();
        q.exec("SELECT * FROM InjectionPath ");
        if(q.first()) {
            do {
                QString p_name = q.value("name").toString();
                int id = q.value("path_id").toInt();
                ui->CB_ing_path->addItem(p_name,id);
            }while(q.next());
        }

    }
    if ( m_qsEyeName == "gammaEye"){
        connect(ui->CB_radioNuclide,SIGNAL(currentIndexChanged(int)),this,SLOT(on_CB_radionuclide_currentIndexChanged(int)));
        connect(ui->cB_collimator,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cB_collimator_currentIndexChanged(int)));
    }
}


int detailsDialog::Inventory_calculator()
{
    int inventory=0;
    QSqlQuery inv;
    QString max_inv = "select MAX(study_id) as max from Study order by deviceid ";
    inv.exec( max_inv );
    if(inv.first()) {
        int max_inv = inv.value("max").toInt();
        inventory = max_inv+1;
        ui->LE_studyID->setText(QString::number( inventory ) );
    }
    return inventory;
}

void detailsDialog::getTimeSettings(int duration,int frame, QString d_unit,QString f_unit,bool fDynamic)
{
    DURATION = duration;
    FRAME = frame;
    dur_unit = std::move(d_unit);
    frame_unit = std::move(f_unit);
    fastDynamic = fDynamic;
}

void detailsDialog::save_Session(const QString& fileDir,QString op,QString startTime,QString endTime) //Save Study's Details and selections to Database(From Study Details dialog)//
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

    ///radiobutton properties
    int gndr=-1;
    if(ui->rb_female->isChecked())
        gndr =0;
    else if(ui->rb_male->isChecked())
        gndr =1;

    int unit2;
    if(ui->rb_mBq_2->isChecked())
        unit2 =0;
    else if(ui->rb_mCi_2->isChecked())
        unit2 =1;

    int fastD=-1;
    if(fastDynamic)
        fastD=1;
    else if(!fastDynamic)
        fastD=0;

    ///LINE EDITS
    QString study_name = ui->LE_SName->text();
    QString animal_name =  ui->LE_animal_id->text();
    QString breed = ui->LE_breed->text();
    QString species = ui->LE_species->text();
    QString age = ui->LE_age->text();
    QString weight = ui->LE_weight->text();
    QString pharma = ui->LE_r_pharma->text();
    QString project = ui->LE_project->text();
    QString marking = ui->le_marking->text();
    QString comments = ui->TE_comments->toPlainText();

    /////DATES
    QDate current =  ui->dE_studyDate->date();
    QDateTime dateTime = ui->dTime_ingection->dateTime();

    ////doubleSpinBoxes
    double inj_activity = ui->dSB_injActivity->value();
    double inj_volume = ui->dSB_volume->value();
    ///from CB'S
    int pathid = ui->CB_ing_path->itemData(ui->CB_ing_path->currentIndex()).toInt();
    int nID = ui->CB_radioNuclide->itemData(ui->CB_radioNuclide->currentIndex()).toInt();
    int cID = ui->cB_collimator->itemData(ui->cB_collimator->currentIndex()).toInt();
    ///SQL QUERY//
    QSqlQuery q;
    QString session = " INSERT INTO Study(date,name,animal_name,breed,species,age,weight,gender,r_pharma,volume,activity,injection_date,path_id, ";
    session += " exp_duration,frame,start_time,fin_time,deviceid,id_modality,operator_name,nuclide_id,radioUnit,timeUnit_exp,timeUnit_frame,project,injected_activity,comments,marking,fileDirectory,fastDynamic, collimator_id) VALUES( ";
    session += " :date,:name,:animal_name,:breed,:species,:age,:weight,:gender,:r_pharma,:volume,:activity,:injection_date,:path_id,:exp_duration,:frame,:start_time,:fin_time,:deviceid,:id_modality,:operator_name,:nuclide_id,:radioUnit,:timeUnit_exp,:timeUnit_frame,:project,:injected_activity,:comments,:marking,:fileDirectory,:fastDynamic,:collimator_id) ";
    q.prepare(session);

    q.bindValue(":date",current);
    q.bindValue(":name",study_name);
    q.bindValue(":animal_name",animal_name);
    q.bindValue(":breed",breed);
    q.bindValue(":species",species);
    q.bindValue(":age",age);
    q.bindValue(":weight",weight);
    q.bindValue(":gender",gndr);
    q.bindValue(":r_pharma",pharma);
    q.bindValue(":volume",inj_volume);
    //    q.bindValue(":activity",initial_activity);
    q.bindValue(":injection_date",dateTime);
    q.bindValue(":path_id",pathid);
    q.bindValue(":exp_duration",DURATION);
    q.bindValue(":frame",FRAME);
    q.bindValue(":start_time",started);
    q.bindValue(":fin_time",ended);
    q.bindValue(":deviceid",deviceid);
    q.bindValue(":id_modality",modid);
    q.bindValue(":operator_name",devop);
    q.bindValue(":nuclide_id",nID);
    q.bindValue(":radioUnit",InitActivity_unit);
    q.bindValue(":timeUnit_exp",dur_unit );
    q.bindValue(":timeUnit_frame",frame_unit);
    q.bindValue(":project",project);
    q.bindValue(":injected_activity",inj_activity);
    q.bindValue(":comments",comments);
    q.bindValue(":marking",marking);
    q.bindValue(":fileDirectory",fileDir);
    q.bindValue(":fastDynamic",fastD);
    q.bindValue(":collimator_id", cID);

    q.exec();
    const int new_id = q.lastInsertId().toInt();
    QString msg = q.lastError().databaseText();

    if (msg.length()>0){
        QMessageBox::question(this, "Error", msg, QMessageBox::Ok);
    }else {
        newID = QString::number(new_id);
        ui->LE_studyID->setText( QString::number(Inventory_calculator() ) );
    }
}

void detailsDialog::closeEvent(QCloseEvent* e){ e->accept(); }

void detailsDialog::on_PB_previous_clicked()
{
    this->hide();
    emit previousPressed();
}

void detailsDialog::on_PB_next_clicked()
{

    if( ui->dSB_injActivity->value() == 0.0){
        QMessageBox msg;
        msg.setIcon(QMessageBox::Information);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        msg.setText("To perform decay correction a non zero value for the \"Injected activity\" and the \"Injection date/time\" that correspond to your experiment should be provided. Proceed anyway without decay correction?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No );
        qint32 ch;
        ch = msg.exec();

        switch(ch) {
        case QMessageBox::Yes:
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

            emit sendDacayInfo( ui->cB_collimator->currentText(), ui->CB_radioNuclide->currentText(),ui->CB_radioNuclide->currentText(), ui->dTime_ingection->dateTime(), ui->dSB_injActivity->value(), radioUnit );
            emit sendStudyID( ui->LE_studyID->text(), ui->LE_SName->text(), ui->LE_animal_id->text(), ui->LE_project->text() );
            break;
        }
        default:
            return;
        }
    }
    else {
        this->hide();
        emit nextPressed();
        if( changeVolt ) {
            spectIsotope chosenIsotope=m_pInputInfo->getSpectIsotope(ui->cB_collimator->currentText(),ui->CB_radioNuclide->currentText());
            emit sendNuclide(chosenIsotope.getVoltage()  );
            changeVolt = false;
        }

        QString radioUnit;
        if ( ui->rb_mBq_2->isChecked() )
            radioUnit = "MBq";
        else
            radioUnit = "uCi";

        emit sendDacayInfo( ui->cB_collimator->currentText(), ui->CB_radioNuclide->currentText(),ui->CB_radioNuclide->currentText(), ui->dTime_ingection->dateTime(), ui->dSB_injActivity->value(), radioUnit );
        emit sendStudyID( ui->LE_studyID->text(), ui->LE_SName->text(), ui->LE_animal_id->text(), ui->LE_project->text() );
    }
}

void detailsDialog::requestNewStudyID()
{
    emit sendStudyID(ui->LE_studyID->text(),ui->LE_SName->text(),ui->LE_animal_id->text(),ui->LE_project->text());
}

void detailsDialog::on_PB_clear_clicked()
{
    ui->le_marking->clear();
    ui->LE_SName->clear();
    ui->LE_age->clear();
    ui->LE_animal_id->clear();
    ui->LE_breed->clear();
    ui->LE_project->clear();
    ui->LE_r_pharma->clear();
    ui->LE_species->clear();
    ui->LE_weight->clear();
    ui->TE_comments->clear();
    ui->dSB_injActivity->clear();
    ui->dSB_volume->clear();
    Init();
}

void detailsDialog::on_CB_radionuclide_currentIndexChanged( int index )
{
    int nucl = ui->CB_radioNuclide->itemData(index).toInt();
    if (m_qsEyeName == "gammaEye"){
        nuclideID = nucl;
        changeVolt = true;
    }
}

void detailsDialog::on_cB_collimator_currentIndexChanged( int index )
{
    ui->CB_radioNuclide->clear();
    QStringList availIsotopes= m_pInputInfo->getHCollimators()[ui->cB_collimator->currentText()];
    QSqlQuery query;
    QString nuclides = "SELECT * FROM radionuclide where id_modality = 1";
    query.exec(nuclides);
    if( query.first() ) {
        do {
            QString name = query.value("nuclide_name").toString();
            int nid = query.value("nuclide_id").toInt();
            if(availIsotopes.contains(name))
                ui->CB_radioNuclide->addItem(name, nid);
        }while(query.next());
    }

}
