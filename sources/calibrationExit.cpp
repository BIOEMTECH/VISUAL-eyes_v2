///////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file calibrationExit.cpp
///
///	@brief help dialog that provides the available options after an aquisition is finished.
///
///
///
///	@author Aphrodite Toufa
/// @date   Created: 07.12.2018
/// @date   Updated: 29.7.2019
///
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "headers/calibrationExit.h"
#include "ui_calibrationExit.h"

calibrationExit::calibrationExit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calibrationExit)
{
    ui->setupUi(this);
}

calibrationExit::~calibrationExit()
{
    delete ui;
}

void calibrationExit::setTypeOfStudy(bool validOn){
    m_validationOn=validOn;
    if(m_validationOn){
        ui->label->setText("System validation finished! Please press exit.");
    }else{
        ui->label->setText("Calibration files have been updated successfully! Please press exit.");
    }
}

void calibrationExit::on_PB_Exit_clicked()
{
    this->close();
    emit exit();
}
