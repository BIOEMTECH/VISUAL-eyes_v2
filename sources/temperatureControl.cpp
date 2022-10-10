#include "headers/temperatureControl.h"

temperatureControl::temperatureControl(ReadInputInfo* inputInfo):m_readInputInfo(inputInfo){}
temperatureControl::~temperatureControl(){}

bool temperatureControl::init_system(){
    QString init_sys_output=run_process("init_system");
    if(init_sys_output.contains("4 active ASICs")){
       return true;
    }
    return false;
}


bool temperatureControl::check_temperature(){
    if(init_system()){
        float st0=0,st1=0;
        float mean_t0=0, mean_t1=0;
        int measurements=2;
        for(int i=0; i < measurements ;i++){
            std::tie(st0,st1)=measure_temperature();
            QTime delay = QTime::currentTime().addSecs(1);
            while( QTime::currentTime() < delay)
                QCoreApplication::processEvents(QEventLoop::AllEvents);

            mean_t0+=st0;
            mean_t1+=st1;

        }

        mean_t0=mean_t0/float(measurements);
        mean_t1=mean_t1/float(measurements);
        bool result= temperature_ok(mean_t0)&&temperature_ok(mean_t1);
        return result;
    }
    return false;
}

std::tuple<float,float> temperatureControl::measure_temperature(){
    float sensor0=0,sensor1=0;
    QString sensor_output=run_process("read_temperature_sensors");
    if (!sensor_output.isEmpty()){
        std::tie(sensor0,sensor1)=process_sensor_output(sensor_output);
    }
    return std::make_tuple(sensor0,sensor1);
}


void temperatureControl::close_electronics(){
    qDebug() << run_process("set_fem_power --power off") << endl;
}

std::tuple<float,float> temperatureControl::process_sensor_output(QString output){
    float sensor0=0,sensor1=0;
    QStringList string_list = output.split("\n");
    if(string_list.size()> 4){
        QStringList line3=string_list[3].split(" ");
        QStringList line4=string_list[4].split(" ");
        line3.removeAll("");
        line4.removeAll("");
        sensor0 = (line3.size()>8)  ? line3[7].toFloat() : 0;
        sensor1 = (line4.size()>8)  ? line4[7].toFloat() : 0;
    }
    return std::make_tuple(sensor0,sensor1);
}

bool temperatureControl::temperature_ok(float current_temperature){
    float tolerance=m_readInputInfo->getTemperatureThreshold();
    float temp_high= m_readInputInfo->getReferenceTemperature() + tolerance;
    float temp_low= m_readInputInfo->getReferenceTemperature() - tolerance;
    qDebug() << "temp high " <<temp_high << " temp low "<< temp_low<< " current " << current_temperature << endl;
    bool result= (current_temperature > temp_low && current_temperature < temp_high) ? true : false;
    return result;
}

QString temperatureControl::run_process(QString input_command){
    QProcess proc;
    QString command=input_command;
    proc.setProcessChannelMode(QProcess::MergedChannels);
    proc.start(command,QIODevice::ReadWrite);
    proc.waitForFinished();
    return proc.readAll().data();;
}

