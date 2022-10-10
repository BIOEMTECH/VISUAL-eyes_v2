#ifndef ColorMap_H
#define ColorMap_H
#include "qwt_color_map.h"
class ColorMap: public QwtLinearColorMap
{
public:

    ColorMap(){}

    void BlackBased(int val)
    {
        this->setColorInterval(Qt::black,Qt::white);
        switch (val) {
        case 1:
            addColorStop( 0, Qt::black);
            addColorStop( 0.1, Qt::darkBlue);
            addColorStop( 0.2, Qt::blue);
            addColorStop( 0.3, Qt::darkCyan);
            addColorStop( 0.4, Qt::cyan);
            addColorStop( 0.5, Qt::green);
            addColorStop( 0.6, Qt::yellow);
            addColorStop( 0.7, Qt::darkYellow);
            addColorStop( 0.8, Qt::red);
            addColorStop( 0.9, Qt::lightGray);
            addColorStop( 1, Qt::white);
            break;
        case 3:
            addColorStop( 0, Qt::black);
            addColorStop( 0.1, QColor(85,9,0));
            addColorStop( 0.2, Qt::darkRed);
            addColorStop( 0.3, QColor(204,0,0));
            addColorStop( 0.4, Qt::red);
            addColorStop( 0.5, QColor(255,128,0));
            addColorStop( 0.6, QColor(255,239,0));
            addColorStop( 0.7, Qt::yellow);
            addColorStop( 0.8, QColor(255,255,65));
            addColorStop( 0.9, QColor(255,255,204));
            addColorStop( 1, Qt::white);
            break;
        case 4:
            addColorStop( 0, Qt::black);
            addColorStop( 0.1, QColor(32,32,32));
            addColorStop( 0.2, QColor(64,64,64));
            addColorStop( 0.3, Qt::darkGray);
            addColorStop( 0.4,  Qt::darkRed);
            addColorStop( 0.5,  QColor(204,0,0));
            addColorStop( 0.6,  Qt::red);
            addColorStop( 0.7,QColor(240,120,0));
            addColorStop( 0.8, QColor(255,255,65));
            addColorStop( 0.9, QColor(255,255,204));
            addColorStop( 1, Qt::white);
            break;
        default:
            break;
        }

    }

    void BlueBased(int val)
    {
        this->setColorInterval(Qt::darkBlue,Qt::white);
        switch (val) {
        case 2:
            QwtLinearColorMap(Qt::darkBlue,Qt::white);
            addColorStop( 0, Qt::darkBlue);
            addColorStop( 0.1, Qt::blue);
            addColorStop( 0.2, Qt::blue);
            addColorStop( 0.3, Qt::cyan);
            addColorStop( 0.4, Qt::cyan);
            addColorStop( 0.5, Qt::green);
            addColorStop( 0.6, Qt::yellow);
            addColorStop( 0.7, QColor(255,128,0));
            addColorStop( 0.8, QColor(246,61,15));
            addColorStop( 0.9, Qt::red);
            addColorStop( 1, Qt::darkRed);
            break;
        default:
            break;
        }
    }
};



#endif // ColorMap_H
