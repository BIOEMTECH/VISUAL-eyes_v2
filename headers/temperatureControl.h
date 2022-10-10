#ifndef TEMPERATURECONTROL_H
#define TEMPERATURECONTROL_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <tuple>
#include <QTime>
#include <QApplication>
#include "headers/readinputinfo.h"

class temperatureControl: public QObject
{
    Q_OBJECT
public:
    temperatureControl(ReadInputInfo* inputInfo);
    ~temperatureControl();

signals:

public slots:
    bool init_system();
    bool check_temperature();
    void close_electronics();

private slots:
    std::tuple<float,float> measure_temperature();
    std::tuple<float,float> process_sensor_output(QString);
    QString run_process(QString);
    bool temperature_ok(float);

private:
    ReadInputInfo * m_readInputInfo;

};

#endif // TEMPERATURECONTROL_H
