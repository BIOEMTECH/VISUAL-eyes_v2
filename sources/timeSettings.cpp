////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file timeSettings.cpp
///
///	@brief class that  changes the time format selected for the aquisition. from min to sec and the opposite.
///
///	@author Aphrodite Toufa
/// @date   Created: 07.12.2018
/// @date   Updated: 29.7.2019
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "headers/timeSettings.h"
#include "ui_timeSettings.h"

timeSettings::timeSettings(bool isBeta, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::timeSettings)
{
    ui->setupUi(this);

    bIsBeta = isBeta;
    // setAttribute(Qt::WA_DeleteOnClose);
    // setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    // setFocus();

    ui->cb_expUnit->addItem("sec",0);
    ui->cb_expUnit->addItem("min",1);

    ui->cb_frameUnit->addItem("sec",0);
    ui->cb_frameUnit->addItem("min",1);

    ui->rb_userDefined->setChecked( true );
    ui->sB_duration->setValue( 2 );
    ui->sB_duration->setEnabled( true );

    //Always is init with seconds
    ui->sB_frame->setValue( 30 );
    ui->sB_frame->setEnabled( true );

    ui->cB_expTime_2->setEnabled( false );
    ui->cb_expUnit->setCurrentIndex( 1);
    ui->cb_frameUnit->setCurrentIndex( 0);

    connect( ui->rb_studyProt, SIGNAL( toggled( bool ) ), this, SLOT( setStudyProtocol( bool ) ) );
    connect( ui->rb_userDefined, SIGNAL( toggled(bool) ), this, SLOT( setUserDefinedCase(bool) ) );


 //   connect(ui->cb_expUnit, SIGNAL(currentIndexChanged(int)),this,SLOT(cb_time_unit_currentIndex_Changed(int)));
    connect(ui->cb_frameUnit, SIGNAL(currentIndexChanged(int)),this,SLOT(cb_time_unit2_currentIndex_Changed(int)));
    connect(ui->cB_expTime_2, SIGNAL(currentIndexChanged(int)),this,SLOT(cb_expTime_2_currentIndex_Changed(int)));


    fastDynamic=false;
}

timeSettings::~timeSettings(){delete ui;}

void timeSettings::closeEvent(QCloseEvent* e){ e->ignore(); }

void timeSettings::cb_expTime_2_currentIndex_Changed(int index)
{
    if( index == 0) {
        ui->sB_duration->setValue( 60 );
        ui->sB_frame->setValue( 2 );

        ui->cb_expUnit->setCurrentIndex( 1 );
        ui->cb_frameUnit->setCurrentIndex( 1 );
        fastDynamic = false;
    }
    else if ( index == 1 ) {
        ui->sB_duration->setValue( 60 );
        ui->sB_frame->setValue( 10 );

        ui->cb_expUnit->setCurrentIndex( 1 );
        ui->cb_frameUnit->setCurrentIndex( 0 );
        fastDynamic = true;
    }
}

void timeSettings::setStudyProtocol( bool isChecked )
{
    if ( isChecked ){
        if ( ui->rb_userDefined->isChecked()  )
            ui->rb_userDefined->setChecked( false );

        ui->sB_duration->clear();
        ui->sB_frame->clear();

        ui->sB_duration->setEnabled( false );
        ui->sB_frame->setEnabled( false );
        ui->cB_expTime_2->setEnabled( true );
        ui->cB_expTime_2->clear();

        ui->cb_expUnit->setEnabled( false );
        ui->cb_frameUnit->setEnabled( false );

        QSqlQuery query;
        query.exec("SELECT * FROM TimeProtocols");

        while(query.next()) {
            QString name = query.value( 4 ).toString();
            int id = query.value( 0 ).toInt();
            ui->cB_expTime_2->addItem(name,id);
        }

        ui->sB_duration->setEnabled( false );
        ui->sB_frame->setEnabled( false );
    }
    else if ( !isChecked && !ui->rb_userDefined->isChecked() )
        ui->rb_studyProt->setChecked( true );
}

void timeSettings::setUserDefinedCase(bool isChecked)
{
    if ( isChecked ){
        if ( ui->rb_studyProt->isChecked() ) {
            ui->rb_studyProt->setChecked( false );
            ui->cB_expTime_2->setEnabled( false );
            ui->cB_expTime_2->clear();
        }

        //Clear the entries
        ui->sB_duration->clear();
        ui->sB_frame->clear();

        ui->sB_duration->setValue( 2 );
        ui->sB_frame->setValue( 30 );

        ui->cb_expUnit->setCurrentIndex( 1 );
        ui->cb_frameUnit->setCurrentIndex( 0 );

        ui->cb_expUnit->setEnabled( true );
        ui->cb_frameUnit->setEnabled( true );

        ui->sB_duration->setEnabled( true );
        ui->sB_frame->setEnabled( true );

        fastDynamic = false;
    }
    else if ( !isChecked && !ui->rb_studyProt->isChecked() )
        ui->rb_userDefined->setChecked( true );
}

void timeSettings::on_PB_prev_clicked()
{
    this->hide();
    emit previousPressed();
}

void timeSettings::mf_expFrameMesg()
{
    QMessageBox msgBox;
    msgBox.critical(nullptr, "VISUAL-eyes", tr("The frame time must be devided exactly with and be smaller or equal to the experiment time.") );
}


void timeSettings::on_PB_ok_clicked()
{
    //Check if the experiment time/frames is correct
    if(ui->sB_frame->value()==0){
        QMessageBox msgBox;// = new QMessageBox( this );
        msgBox.setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        msgBox.setStandardButtons( QMessageBox::Ok );
        msgBox.setWindowTitle( tr("Attention") );
        msgBox.setText( tr("Please provide a valid frame time before starting the aquisition.") );
        msgBox.setModal(false);
        msgBox.open( this, SIGNAL(openTimeSettings()));//re-open the time dialog to set the duration and frame time
    }else {
        if ( ui->cb_expUnit->currentText() == ui->cb_frameUnit->currentText() ) {
            if ( ui->sB_duration->value() < ui->sB_frame->value() || ( ui->sB_duration->value() )%(ui->sB_frame->value()) != 0 ){
                mf_expFrameMesg();
                return;
            }
        }
        else{
            if ( ui->cb_expUnit->currentText() == "min"){
                if ( ui->sB_duration->value()*60 < ui->sB_frame->value()  || ( ui->sB_duration->value()*60 )%( ui->sB_frame->value() ) != 0 ){
                    mf_expFrameMesg();
                    return;
                }
            }
            else if ( ui->cb_expUnit->currentText() == "sec" ){
                if ( ui->sB_duration->value() < ui->sB_frame->value()*60  || ( ui->sB_duration->value() )%( ui->sB_frame->value()*60 ) != 0 ){
                    mf_expFrameMesg();
                    return;
                }
            }
        }
        if ( bIsBeta && ui->sB_frame->value() < 10 && ui->cb_frameUnit->currentText() == "sec"){
            QMessageBox* msgBox = new QMessageBox( this );
            msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
            msgBox->setStandardButtons( QMessageBox::Ok | QMessageBox::Cancel );
            msgBox->setWindowTitle( tr("Attention") );
            msgBox->setText( tr("The frame time has been set below the recommended value of 10 sec. Continue?") );
            msgBox->setModal(false);

            if ( msgBox->exec() == QMessageBox::Cancel )
                return;
        }
        emit finishPressed();
        emit sendTimeSettings(ui->sB_duration->value(), ui->sB_frame->value(), ui->cb_expUnit->currentText(), ui->cb_frameUnit->currentText(), fastDynamic);
    }
}
