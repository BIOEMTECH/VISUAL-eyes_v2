/////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///	@file operatorDialog.cpp
///
///	@brief dialog that handles, creates and saves the operators using the system and their institutions.
///
///	@author Aphrodite Toufa
/// @date   Created: 07.12.2018
/// @date   Updated: 29.7.2019
///
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "headers/operatorDialog.h"
#include "ui_operatorDialog.h"

operatorDialog::operatorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::operatorDialog)
{
    ui->setupUi(this);

    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    setWindowState(Qt::WindowActive);
    //setAttribute(Qt::WA_DeleteOnClose);

    Init();
    connect(ui->CB_hospital,SIGNAL(currentIndexChanged(int)),this,SLOT(hospital_currentIndexChanged(int)));
    connect(ui->pb_addInst,SIGNAL(pressed()),this,SLOT(addInst_pressed()));
    connect(ui->pb_addOp,SIGNAL(pressed()),this,SLOT(addOp_pressed()));
    connect(ui->checkbox_Inst,SIGNAL(toggled(bool)),this,SLOT(Inst_toggled(bool)));
    connect(ui->checkbox_OP,SIGNAL(toggled(bool)),this,SLOT(OP_toggled(bool)));

    ui->CB_hospital->installEventFilter(this);
    ui->CB_phycisian->installEventFilter(this);
}

operatorDialog::~operatorDialog()
{
    delete ui;
}

void operatorDialog::closeEvent(QCloseEvent* event){ event->accept(); }

void operatorDialog::Init()
{
    ui->CB_hospital->clear();
    ui->CB_phycisian->clear();
    ui->LE_op->clear();
    ui->LE_institute->clear();

    QSqlQuery query,q,q1;
    query.exec("SELECT * FROM hospital order by name");

    while (query.next()){
        int id = query.value("hospital_id").toInt();
        QString name = query.value("name").toString();
        ui->CB_hospital->addItem(name,id);
    }
    hospital_currentIndexChanged(ui->CB_hospital->currentIndex());
}

void operatorDialog::hospital_currentIndexChanged(int  /*index*/)
{
    int indx = ui->CB_hospital->itemData(ui->CB_hospital->currentIndex()).toInt();
    QString id = QString::number(indx);

    ui->CB_phycisian->clear();
    QSqlQuery query;
    QString ptr = " SELECT operator_id, name FROM operator WHERE hospital_id = " +id;
    query.exec(ptr);
    while( query.next() ){
        int op_id = query.value("operator_id").toInt();
        QString name = query.value("name").toString();
        ui->CB_phycisian->addItem(name,op_id);
    }
}

void operatorDialog::addInst_pressed()
{
    if(ui->LE_institute->text()!="" && !ui->LE_institute->text().contains(" ")){
        QSqlQuery query,q;
        QString ins_name = ui->LE_institute->text();
        bool exists=false;
        QString check =" SELECT name from hospital ";
        query.exec(check);
        while(query.next()) {
            if(ins_name == query.value("name").toString())
                exists = true;
        }

        if(!exists){
            QString hosp= " INSERT INTO hospital(name) VALUES(:name)";
            q.prepare(hosp);
            q.bindValue(":name",ins_name);
            q.exec();

            Init();
            int index = ui->CB_hospital->findText(ins_name);
            ui->CB_hospital->setCurrentIndex(index);
        }
        else
            QMessageBox::information(this,"Info","This institute already exists. Please define a different record to add.");
    }
    else if (ui->LE_institute->text().contains(" ")) {
        QMessageBox::warning(this,"Warning","Hospital's name must not contain special characters and spaces.");
    }
}

void operatorDialog::addOp_pressed()
{
    if(ui->LE_op->text()!="" && !ui->LE_op->text().contains(" "))
    {
        QString op_name = ui->LE_op->text();
        QSqlQuery q,query;
        bool exists=false;
        QString check =" SELECT name from operator where hospital_id= "+ui->CB_hospital->itemData(ui->CB_hospital->currentIndex()).toString();
        query.exec(check);
        while(query.next()){
            if(op_name == query.value("name").toString())
                exists = true;
        }

        if(!exists){
            QString op= " INSERT INTO operator(name,hospital_id) VALUES(:name,:hosp_id)";
            q.prepare(op);
            q.bindValue(":name",op_name);
            q.bindValue(":hosp_id",ui->CB_hospital->itemData(ui->CB_hospital->currentIndex()));
            q.exec();

            hospital_currentIndexChanged(ui->CB_hospital->currentIndex());
            int index =ui->CB_phycisian->findText(op_name);
            ui->CB_phycisian->setCurrentIndex(index);
        }
        else
            QMessageBox::information(this,"Info","This operator already exists. Please define a different record to add.");
    }
    else if (ui->LE_op->text().contains(" ")) {
        QMessageBox::warning(this,"Warning","Operator's name must not contain special characters and spaces.");
    }

}

void operatorDialog::Inst_toggled(bool checked)
{
    if(checked){
        ui->LE_institute->setEnabled(true);
        ui->pb_addInst->setEnabled(true);
    }
    else if(!checked){
        ui->LE_institute->setEnabled(false);
        ui->pb_addInst->setEnabled(false);
    }
}

void operatorDialog::OP_toggled(bool checked)
{

    if(checked){
        ui->LE_op->setEnabled(true);
        ui->pb_addOp->setEnabled(true);
    }
    else if(!checked){
        ui->LE_op->setEnabled(false);
        ui->pb_addOp->setEnabled(false);
    }
}

bool operatorDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress){
        auto *keyEvent = dynamic_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key::Key_Delete && keyEvent->modifiers() == Qt::ShiftModifier){
            auto combobox = dynamic_cast<QComboBox *>(obj);
            if (combobox){
                if(combobox == ui->CB_hospital){
                    QMessageBox mes;
                    int ch;
                    mes.setIcon(QMessageBox::Information);
                    mes.setText("Are you sure you want to delete the selected institute? Note tha all saved operators under this institute will also be deleted. This action is not reversible!");
                    mes.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
                    ch = mes.exec();
                    switch(ch){
                    case QMessageBox::Ok:
                    {
                        QSqlQuery q2;
                        QString str2 = " DELETE from operator where  operator_id= " +ui->CB_phycisian->itemData(ui->CB_phycisian->currentIndex()).toString();
                        bool test = q2.exec(str2);
                        if(test)
                            combobox->removeItem(combobox->currentIndex());
                    }break;

                    case QMessageBox::Cancel:
                        break;

                    default:
                        break;
                    }


                    QSqlQuery query,q;
                    QString ptr = " DELETE from operator where  hospital_id= " +ui->CB_hospital->itemData(ui->CB_hospital->currentIndex()).toString();
                    query.exec(ptr);


                    QString str = " DELETE from hospital where  hospital_id= " +ui->CB_hospital->itemData(ui->CB_hospital->currentIndex()).toString();
                    bool t2 = q.exec(str);
                    if(t2)
                        combobox->removeItem(combobox->currentIndex());
                }
                else if(combobox == ui->CB_phycisian){
                    QMessageBox mes;
                    int ch;
                    mes.setIcon(QMessageBox::Information);
                    mes.setText("Are you sure you want to delete the selected operator? This action is not reversible!");
                    mes.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
                    ch = mes.exec();
                    switch(ch){
                    case QMessageBox::Ok:
                    {
                        QSqlQuery q2;
                        QString str2 = " DELETE from operator where  operator_id= " +ui->CB_phycisian->itemData(ui->CB_phycisian->currentIndex()).toString();
                        bool test = q2.exec(str2);
                        if(test)
                            combobox->removeItem(combobox->currentIndex());
                    }break;

                    case QMessageBox::Cancel:
                        break;

                    default:
                        break;
                    }
                }
                return true;
            }
        }
    }
    // standard event processing
    return QObject::eventFilter(obj, event);
}

void operatorDialog::on_PB_cancel_clicked()
{
    emit exitToMainMenu();
    this->close();
}

void operatorDialog::on_PB_next_clicked()
{
    this->hide();
    emit nextPressed();
    QString opname = ui->CB_phycisian->currentText();
    emit sendName(ui->CB_phycisian->currentText());
}
