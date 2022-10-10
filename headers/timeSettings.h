#ifndef TIMESETTINGS_H
#define TIMESETTINGS_H

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

namespace Ui {
class timeSettings;
}

class timeSettings : public QDialog
{
    Q_OBJECT

public:
    explicit timeSettings( bool isBeta = false, QWidget *parent = 0);
    ~timeSettings();
    bool fastDynamic;

signals:
void previousPressed();
void finishPressed();
void sendTimeSettings(int,int,QString,QString,bool);

protected:
void closeEvent(QCloseEvent* e);

private slots:
void cb_expTime_2_currentIndex_Changed(int);
void setStudyProtocol(bool);
void setUserDefinedCase(bool);

void on_PB_prev_clicked();

void on_PB_ok_clicked();

private:
    Ui::timeSettings *ui;
    void mf_expFrameMesg();
    bool bIsBeta;
};

#endif // TIMESETTINGS_H
