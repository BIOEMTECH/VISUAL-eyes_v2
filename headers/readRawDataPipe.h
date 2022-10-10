#ifndef READRAWDATAPIPE_H
#define READRAWDATAPIPE_H
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QSemaphore>
#include <boost/circular_buffer.hpp>
#include <vector>
#include <string>
#include <QList>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

struct EventMsg {
    uint8_t dummy1;
    float x_cog1;
    float y_cog1;
    float energy1;
    float x_cog2;
    float y_cog2;
    float energy2;
}__attribute__((__packed__));

struct rawEvent {
    float x_cog1;
    float y_cog1;
    float energy1;
    float x_cog2;
    float y_cog2;
    float energy2;
}__attribute__((__packed__));


class readRawDataPipe : public QObject
{
    Q_OBJECT
public:
    explicit readRawDataPipe(boost::circular_buffer<EventMsg> *);
    ~readRawDataPipe();
    boost::circular_buffer<EventMsg> *m_circularBuffer;

signals:
    void sendEvent();
    void post_finished();


public slots:
    void postProc();

private:
    int m_fd;
};

#endif // READRAWDATAPIPE_H



