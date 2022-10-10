#ifndef DAQCOUNTER_H
#define DAQCOUNTER_H

#include <QObject>
#include <QTimer>

class DAQcounter:public QObject
{
    Q_OBJECT
public:
    explicit DAQcounter(int=0,int=0,bool=false);

    ~DAQcounter();
    int DAQprogress,frameProgress,frameCount;
    int frame_time,duration_time;
    bool fastDynamic;

signals:
  void DAQprogressBarValueChanged(int);
  void frameProgressBarValueChanged(int);
  void stopEverthing();
  void sendFrameStop();
  void sendNewFrameTime(int);
  void replotFrame();
  void displayProgress();
  void finished();

public slots:
  void DAQ();
  void DynamicAquisition();
  void frameReplot();
  void Initiate();
  void stopTimer();

private:
  QTimer *mTimer{};
};

#endif // DAQCOUNTER_H
