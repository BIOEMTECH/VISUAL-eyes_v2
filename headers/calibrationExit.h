#ifndef CALIBRATIONEXIT_H
#define CALIBRATIONEXIT_H

#include <QDialog>

namespace Ui {
class calibrationExit;
}

class calibrationExit : public QDialog
{
    Q_OBJECT

public:
    explicit calibrationExit(QWidget *parent = 0);
    ~calibrationExit();
    void setTypeOfStudy(bool);

signals:
    void exit();

private slots:
    void on_PB_Exit_clicked();

private:
    Ui::calibrationExit *ui;
    bool m_validationOn=false;
};

#endif // CALIBRATIONEXIT_H
