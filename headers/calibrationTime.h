#ifndef CALIBRATIONTIME_H
#define CALIBRATIONTIME_H

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
class calibrationTime;
}

class calibrationTime : public QDialog
{
    Q_OBJECT

public:
    explicit calibrationTime(QWidget *parent = 0);
    ~calibrationTime();

signals:
void previousPressed();
void finishPressed();
void sendTimeSettings(int,int,QString,QString,bool);

protected:
void closeEvent(QCloseEvent* e);

private slots:
void cb_expTime_2_currentIndex_Changed(int);
void on_PB_prev_clicked();
void on_PB_ok_clicked();

private:
    Ui::calibrationTime *ui;
};

#endif // CALIBRATIONTIME_H
