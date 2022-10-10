#include "headers/DAQcounter.h"

DAQcounter::DAQcounter(int DAQduration, int frameDuration, bool DynamicFrame)
{
    frame_time = frameDuration;
    duration_time = DAQduration;
    fastDynamic = DynamicFrame;
}

DAQcounter::~DAQcounter(){ mTimer->deleteLater(); }

void DAQcounter::Initiate()
{
    DAQprogress = 0;
    frameProgress=0;
    frameCount=0;
    mTimer = new QTimer(this);
    mTimer->setInterval(1000);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(DAQ()));
    connect(this,SIGNAL(sendFrameStop()),this,SLOT(frameReplot()));
    mTimer->start();
}

void DAQcounter::stopTimer()
{
    mTimer->stop();
    frameProgress=0;
    frame_time=0;
    duration_time=0;
    frameCount=0;
    emit finished();
}

void DAQcounter::DAQ()
{
    DAQprogress++;
    frameProgress++;
    emit DAQprogressBarValueChanged(DAQprogress);
    emit frameProgressBarValueChanged(frameProgress);
    emit displayProgress();

    if(!fastDynamic)
    {
        if(frameProgress==frame_time)
            emit sendFrameStop();
        if(DAQprogress==duration_time)
            emit stopEverthing();
    }
    else if(fastDynamic){
        if(frameProgress==frame_time){
            frameCount++;
            emit sendFrameStop();
        }

        if(DAQprogress==duration_time){
            emit stopEverthing();
            frameProgress=0;
            frame_time=0;
            duration_time=0;
            frameCount=0;
        }
    }
}

void DAQcounter::DynamicAquisition()
{  
    if(frameCount==6){
        frame_time = 30;
        frameProgress=0;
        emit sendNewFrameTime(frame_time);
    }
    else if(frameCount==14){
        frame_time = 60;
        frameProgress=0;
        emit sendNewFrameTime(frame_time);
    }
    else if(frameCount==19){
        frame_time = 120;
        frameProgress=0;
        emit sendNewFrameTime(frame_time);
    }
}

void DAQcounter::frameReplot()
{
    DynamicAquisition();
    frameProgress=0;
    emit replotFrame();
}

