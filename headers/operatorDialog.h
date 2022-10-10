#ifndef OPERATORDIALOG_H
#define OPERATORDIALOG_H

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
class operatorDialog;
}

class operatorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit operatorDialog(QWidget *parent = 0);
    ~operatorDialog();

signals:
    void sendName(QString);
    void nextPressed();
    void exitToMainMenu();

public slots:
    void Init();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void closeEvent(QCloseEvent* event);

private slots:
    void addInst_pressed();
    void addOp_pressed();
    void Inst_toggled(bool checked);
    void OP_toggled(bool checked);
    void hospital_currentIndexChanged(int index);
    void on_PB_cancel_clicked();
    void on_PB_next_clicked();

private:
    Ui::operatorDialog *ui;
};

#endif // OPERATORDIALOG_H
