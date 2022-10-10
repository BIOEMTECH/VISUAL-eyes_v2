#ifndef CALIBRATIONDIALOG_H
#define CALIBRATIONDIALOG_H

#include <QDialog>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QDate>
#include <QDateTime>
#include <QMessageBox>
#include <QKeyEvent>
#include <QRect>
#include <QDesktopWidget>
#include "readinputinfo.h"
#include "isotope.h"

namespace Ui {
class calibrationDialog;
}

class calibrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit calibrationDialog(ReadInputInfo * inputInfo, QString qsWhichEye, QWidget *parent = 0);
    ~calibrationDialog();
    int DURATION{},FRAME{};
    QString dur_unit,frame_unit;
    QString started,ended;
    QString newID;
    int nuclideID{};

signals:
    void previousPressed();
    void nextPressed();
    void sendCalibrationID(QString,bool);
    void sendNuclide(QString);
    void sendDacayInfo(QString, QString,QString, QDateTime, double, QString);
    void sendNuclideName( QString );

public slots:
    void getTimeSettings(int,int,QString, QString,bool);
    void save_Session(const QString&, QString,QString,QString);
    void requestNewStudyID();

protected:
    void closeEvent(QCloseEvent* e);

private slots:
    void Init();
    int Inventory_calculator();
    void on_PB_previous_clicked();
    void on_PB_next_clicked();
    void on_PB_clear_clicked();
    void on_CB_radionuclide_currentIndexChanged(int);
    void on_cB_collimator_currentIndexChanged(int);
    void on_cb_validation(bool);
    void on_cb_calibration(bool);
    void setCheckstateValidation();
    void setCheckstateCalibration();

private:
    Ui::calibrationDialog *ui;
    bool changeVolt{};
    bool fastDynamic;
    QString m_qsEyeName;
    bool m_isValidationChecked, m_isCalibrationChecked;
    ReadInputInfo * m_pInputInfo;
};


#endif // calibrationDialog_H
