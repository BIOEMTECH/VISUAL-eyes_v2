////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file timeSettings.cpp
///
///	@brief class that  changes the time format selected for the aquisition. from min to sec and the opposite.
///
///	@author Christina-Anna Gatsiou
/// @date   Created: 31.08.2022
/// @date   Updated: 31.08.2022
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QDebug>
#include "headers/calibrationTime.h"
#include "ui_calibrationTime.h"

calibrationTime::calibrationTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calibrationTime)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    ui->cb_expUnit->addItem("min",0);
    ui->cb_expUnit->addItem("hr",1);

    ui->sB_duration->setValue( 4 );
    ui->sB_duration->setEnabled( true );


    ui->cb_expUnit->setCurrentIndex(1);

    connect(ui->cb_expUnit, SIGNAL(currentIndexChanged(int)),this,SLOT(cb_time_unit_currentIndex_Changed(int)));
}

calibrationTime::~calibrationTime(){delete ui;}

void calibrationTime::closeEvent(QCloseEvent* e){ e->ignore(); }

void calibrationTime::cb_expTime_2_currentIndex_Changed(int index)
{
    if( index == 0) {
        ui->sB_duration->setValue(60);
        ui->cb_expUnit->setCurrentIndex(1);
        ui->sB_duration->setMinimum(2);
        ui->sB_duration->setSingleStep(10);
    }
    else if ( index == 1 ) {
        ui->sB_duration->setValue(5);
        ui->cb_expUnit->setCurrentIndex(1);
        ui->sB_duration->setSingleStep(1);
    }
}


void calibrationTime::on_PB_prev_clicked()
{
    this->hide();
    emit previousPressed();
}


void calibrationTime::on_PB_ok_clicked()
{
    //Check if the experiment time/frames is correct
    if(ui->sB_duration->value()==0){
        QMessageBox* msgBox = new QMessageBox( this );
        msgBox->setAttribute( Qt::WA_DeleteOnClose ); //makes sure the msgbox is deleted automatically when closed
        msgBox->setStandardButtons( QMessageBox::Ok );
        msgBox->setWindowTitle( tr("Attention") );
        msgBox->setText( tr("Please provide a valid duration time before starting the aquisition.") );
        msgBox->setModal(false);
        msgBox->open( this, SIGNAL(openTimeSettings()));//re-open the time dialog to set the duration and frame time
    }else {
        qDebug() << ui->cb_expUnit->currentText() << endl;
        emit finishPressed();
        emit sendTimeSettings(ui->sB_duration->value(), ui->sB_duration->value(), ui->cb_expUnit->currentText(), ui->cb_expUnit->currentText(), false);
    }
}
