///////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file continueStudy.cpp
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

#include "headers/continueStudy.h"
#include "ui_continueStudy.h"

continueStudy::continueStudy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::continueStudy)
{
    ui->setupUi(this);
   // setAttribute(Qt::WA_DeleteOnClose);
}

continueStudy::~continueStudy()
{
    delete ui;
}

void continueStudy::on_PB_InitiateStudy_clicked()
{
    this->close();
    emit followUp();
}

void continueStudy::on_PB_restart_clicked()
{
    this->close();
    emit restartStudy();
}

void continueStudy::on_PB_Exit_clicked()
{
    this->close();
    emit exit();
}
