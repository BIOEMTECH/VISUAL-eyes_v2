#ifndef CONTINUESTUDY_H
#define CONTINUESTUDY_H

#include <QDialog>

namespace Ui {
class continueStudy;
}

class continueStudy : public QDialog
{
    Q_OBJECT

public:
    explicit continueStudy(QWidget *parent = 0);
    ~continueStudy();

signals:
    void followUp();
    void restartStudy();
    void exit();

private slots:
    void on_PB_InitiateStudy_clicked();
    void on_PB_restart_clicked();
    void on_PB_Exit_clicked();

private:
    Ui::continueStudy *ui;
};

#endif // CONTINUESTUDY_H
