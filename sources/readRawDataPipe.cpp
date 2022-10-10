#include "headers/readRawDataPipe.h"
#include <QDebug>

readRawDataPipe::readRawDataPipe(boost::circular_buffer<EventMsg> * circularBuffer){
    m_circularBuffer=circularBuffer;


}

readRawDataPipe::~readRawDataPipe(){
   qDebug() << "exiting rawDataPipe " << endl;
}




void readRawDataPipe::postProc(){

    qDebug() << "Starting filling buffer " << endl;

    m_fd = open("/tmp/hitfifo", O_RDONLY);
    struct EventMsg newMsg;
    while(true){

       read(m_fd,&newMsg,sizeof(newMsg));
       if(newMsg.dummy1 == 0){
           emit post_finished();
           break;
       }
       if((newMsg.energy1 > 0 && newMsg.energy2 > 0)){
           m_circularBuffer->push_back(newMsg);
           emit sendEvent();
       }

    }
    close(m_fd);
    emit post_finished();

}


