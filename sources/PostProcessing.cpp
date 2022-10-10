﻿//////////////////////////////////////////////////////////////////////
///
///	@file PostProcessing.cpp
///	@brief post aquisition image editor
///
///	@author Aphrodite Toufa
/// @date   Created: 6.02.2018
///
//////////////////////////////////////////////////////////////////////

#include "headers/PostProcessing.h"
#include "headers/database_connection.h"
#include <math.h>
#include <iomanip>
#include <sstream>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QProgressDialog>
#include <QApplication>
#include <iostream>
#include <fstream>
#include <QStandardPaths>
#include <QMouseEvent>
#include <QDesktopServices>
#include <QMessageBox>
#include <QInputDialog>
#include <QDialogButtonBox>
#include "qwt_painter.h"
#include <QIntValidator>
#include <QDirIterator>
#include <QToolButton>
#include <QRegion>
#include "qwt_plot_directpainter.h"
#include <math.h>
#include <time.h>
#include "qwt_symbol.h"
#include <QtSql/qsqlquery.h>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <cv.h>
//#include <highgui.h>

#include "Includes/ExcelFormat.h"
#include "Includes/dicomEncoder.hpp"
#include "/usr/local/include/dcmtk/ofstd/offile.h"


#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <crtdbg.h>

#else // _WIN32

#define	FW_NORMAL	400
#define	FW_BOLD		700

#endif // _WIN32

using namespace cv;
using namespace ExcelFormat;

CustomMagnifier::~CustomMagnifier(){}

void CustomMagnifier::rescale_on_cursor(double factor, int x_cursor, int y_cursor, QSize parent_size)
{
    // max size of the widget
    double x_cursor_max = parent_size.width();
    double y_cursor_max = parent_size.height();

    // percentage position of the cursor in the widget
    double x_percent = (x_cursor * 100) / x_cursor_max;
    double y_percent = (y_cursor * 100) / y_cursor_max;

    // will be the new lowerBound and upperBound of the scales
    double delta_1 = 0;
    double delta_2 = 0;

    //plotScaleEngine->zoomed(true);
    bool doReplot = false;
    const bool autoReplot = mPlot->autoReplot();
    mPlot->setAutoReplot( false );

    for ( int axisId = 0; axisId < QwtPlot::axisCnt; axisId++ ) {
        const QwtScaleDiv &scaleDiv =mPlot->axisScaleDiv( axisId );
        if ( isAxisEnabled( axisId ) ) {
            double center = scaleDiv.lowerBound() + scaleDiv.range() / 2;	// Here we set the center of the scale
            const double width_2 = scaleDiv.range() / 2 * factor;			// the width wanted between lowerBound (or upper) and the center
            double interval = (scaleDiv.range() / 2) - width_2;				// the interval between the old width and the wanted width

            if (axisId == 0) { 		// y - left
                delta_1 = (center - width_2) + (((100 - y_percent) * interval) / 100) - interval;
                delta_2 = (center + width_2) - ((y_percent * interval) / 100) + interval;
            }
            else if (axisId == 2) { 	// x - bottom
                delta_1 = (center - width_2) + (((x_percent * interval) / 100)) - interval;
                delta_2 = (center + width_2) - (((100 - x_percent) * interval) / 100) + interval;
            }
            else {
                delta_1 = 0;
                delta_2 = 0;
            }
            mPlot->setAxisScale(axisId, delta_1, delta_2);
            doReplot = true;
        }
    }
    mPlot->setAutoReplot( autoReplot );
    if ( doReplot )
        mPlot->replot();
}

void CustomMagnifier::widgetWheelEvent(QWheelEvent *wheelEvent)
{
    /*
    // _plotScaleEngine->plot()->setFocus();
    QSize parent_size = this->parentWidget()->size();

    if (wheelEvent->delta() > 0) 	// unzoom
        rescale_on_cursor(0.9, wheelEvent->x(), wheelEvent->y(), parent_size);
    else 							// zoom
        rescale_on_cursor(1.1, wheelEvent->x(), wheelEvent->y(), parent_size);
    */
}

void CustomMagnifier::widgetMousePressEvent (QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        currentPos= event->pos();
}

void CustomMagnifier::widgetMouseReleaseEvent (QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        lastPos= event->pos();
        QSize parent_size = this->parentWidget()->size();
        if(((lastPos.operator -=(currentPos)).x()>(currentPos.operator -=(lastPos)).x()) || ((lastPos.operator -=(currentPos)).y() >(currentPos.operator -=(lastPos)).y())|| ((lastPos.operator -=(currentPos)).x()>(currentPos.operator -=(lastPos)).x() && (lastPos.operator -=(currentPos)).y() >(currentPos.operator -=(lastPos)).y()))
            rescale_on_cursor(0.9, event->pos().x(), event->pos().y(), parent_size);
        else if(((lastPos.operator -=(currentPos)).x()<(currentPos.operator -=(lastPos)).x()) || ((lastPos.operator -=(currentPos)).y() < (currentPos.operator -=(lastPos)).y())|| ((lastPos.operator -=(currentPos)).x()<(currentPos.operator -=(lastPos)).x() && (lastPos.operator -=(currentPos)).y() < (currentPos.operator -=(lastPos)).y()))
            rescale_on_cursor(1.1, event->pos().x(), event->pos().y(), parent_size);
    }
}

GUI_Plot::GUI_Plot(QWidget *parent, bool type):QwtPlot(parent)
{
    corMatrix1 = nullptr;
    corMatrix2 = nullptr;
    spectrogram1 = nullptr;
    rightAxis=nullptr;
    rotateValue = 0;

    if ( type == true ) {
        if( corMatrix1 == nullptr)
            corMatrix1 = new QwtMatrixRasterData();

        if(corMatrix2==nullptr)
            corMatrix2 = new QwtMatrixRasterData();
        corMatrix1->setInterval( Qt::ZAxis, QwtInterval( 0, 0) );
        corMatrix2->setInterval( Qt::ZAxis, QwtInterval( 0, 0) );

        //////// CORRECTED DATA PLOT (FRAME SUMMED)//////

        //insertLegend(new QwtLegend());

        enableAxis(QwtPlot::xBottom, false);
        enableAxis(QwtPlot::yLeft, true);
        axisWidget(QwtPlot::yRight)->setMinBorderDist(0,0);
        axisScaleDraw(QwtPlot::yLeft)->enableComponent(QwtAbstractScaleDraw::Labels, false );
        axisScaleDraw(QwtPlot::yLeft)->enableComponent(QwtAbstractScaleDraw::Ticks, false );
        axisScaleDraw(QwtPlot::yLeft)->enableComponent(QwtAbstractScaleDraw::Backbone, false );

        if( rightAxis == nullptr)
            rightAxis = new QwtScaleWidget();

        rightAxis=axisWidget(QwtPlot::yRight);

        rightAxis->setColorBarEnabled(true);
        rightAxis->setColorBarWidth(14);

        const QFontMetrics fm(axisWidget(QwtPlot::yRight)->font());
        QwtScaleDraw * sd = axisScaleDraw(QwtPlot::yRight);
        sd->setMinimumExtent(fm.width("100.00"));


        setAxisAutoScale(QwtPlot::yRight,false);




        zoom = new CustomMagnifier(this);
        canvas()->installEventFilter( this );


        // We want the focus, but no focus rect. The
        // selected point will be highlighted instead.
        //  canvas()->setFocusPolicy( Qt::StrongFocus );
#ifndef QT_NO_CURSOR
        // canvas()->setCursor( Qt::PointingHandCursor );
#endif
        QwtPlotCanvas *plot_cnv = static_cast<QwtPlotCanvas*>(canvas());
        plot_cnv->setFocusIndicator( QwtPlotCanvas::ItemFocusIndicator );
        canvas()->setFocus();

        if(spectrogram1==nullptr)
            spectrogram1 = new QwtPlotSpectrogram();

        ///spectrogram1->setColorMap(cM);
        spectrogram1->setRenderThreadCount(0);
        setFixedHeight(292);
        setFixedWidth(620);


    }
    else if(type==false) {
        curve = new QwtPlotCurve();
        curve->setPen(QColor(Qt::yellow),1);
        curve->setRenderThreadCount(0);

        QPalette p;
        p.setColor(QPalette::Background,QRgb(0xf5f5f5));
        canvas()->setPalette(p);
        QwtLegend *legend = new QwtLegend;
        legend->setFrameStyle(QFrame::Box|QFrame::Sunken);

        insertLegend(legend, QwtPlot::RightLegend);
        setFont(QFont("Arial", 12,QFont::Thin));
        setAxisFont(QwtPlot::xBottom,QFont("Arial", 12,QFont::Thin));
        setAxisFont(QwtPlot::yLeft,QFont("Arial", 12,QFont::Thin));
        setAxisTitle(QwtPlot::xBottom,QwtText("Time (min)"));
        setAxisScale(QwtPlot::xBottom,0,0,0);
        setAxisScale(QwtPlot::yLeft,0,0,0);



    }

    QSizePolicy qsp(QSizePolicy::Preferred,QSizePolicy::Preferred);
    qsp.setHeightForWidth(true);
    setSizePolicy(qsp);

    ItemCounter =1;
    labelCounter = 2;
    savedItems = 0;
    savedLabels=0;
    currItemIndex = -1;
    EllipseItemCounter=0;
    freeItemCounter = 0;
    GeneralItemsCounter = 0;

    drawing = false;
    drawStarted = false;
    ResetROIS = false;
    moveSelection = false;
    resizeSelection=false;

    accepted = false;
    canvas()->setAttribute(Qt::WA_Hover);
    canvas()->setMouseTracking(true);
    replot();

    currItem = nullptr;
}


void GUI_Plot::setYAxisTitle( QString nameY )
{
    setAxisTitle(QwtPlot::yLeft,QwtText( nameY ));
}

void GUI_Plot::construct_picker_machine(Type val)
{
    value = val;

    switch (val) {
    case RectROI:
    {
        rect_picker = new QwtPlotPicker(canvas());
        rect_machine = new QwtPickerDragRectMachine();
        rect_machine->setState(QwtPickerMachine::RectSelection);
        rect_picker->setStateMachine(rect_machine);

//        rect_picker->setTrackerMode(QwtPlotPicker::ActiveOnly);
//        rect_picker->setTrackerPen(QColor(Qt::white));

        break;
    }
    case EllipseROI:
    {

        ellipse_picker = new QwtPlotPicker(canvas());
        ellipse_machine = new QwtPickerDragRectMachine();
        ellipse_machine->setState(QwtPickerMachine::RectSelection);
        ellipse_picker->setStateMachine(ellipse_machine);
//        ellipse_picker->setTrackerMode(QwtPlotPicker::ActiveOnly);
//        ellipse_picker->setTrackerPen(QColor(Qt::white));

        break;
    }
    case FreeDrawROI:
    {
        free_picker = new QwtPlotPicker(canvas());
        free_machine = new QwtPickerDragPointMachine();
        free_machine->setState(QwtPickerMachine::PointSelection);
        free_picker->setStateMachine(free_machine);
        // free_picker->setTrackerMode(QwtPlotPicker::ActiveOnly);
        // free_picker->setTrackerPen(QColor(Qt::white));
        break;
    }
    default:
        break;
    }
}

void GUI_Plot::destruct_picker_machine(Type val)
{
    switch(val) {
    case RectROI:
    {
        if ( rect_machine != nullptr && rect_picker != nullptr) {

            rect_machine->setState(QwtPickerMachine::NoSelection);
            rect_machine->reset();
            rect_machine = nullptr;
            delete rect_picker;
        }
        break;
    }
    case EllipseROI:
    {
        if(ellipse_machine!=nullptr && ellipse_picker!=nullptr) {
            ellipse_machine->setState(QwtPickerMachine::NoSelection);
            ellipse_machine->reset();
            ellipse_machine = nullptr;
            delete ellipse_picker;
        }
        break;
    }
    case FreeDrawROI:
    {
        if(free_machine!=nullptr && free_picker!=nullptr) {
            free_machine->setState(QwtPickerMachine::NoSelection);
            free_machine->reset();
            free_machine = nullptr;
            delete free_picker;
        }
        break;
    }
    default:
        break;
    }
}

void GUI_Plot::clearROIS()
{

    if(mPlotItemsList.empty()) {
        detachItems(QwtPlotItem::Rtti_PlotShape, true);
        detachItems(QwtPlotItem::Rtti_PlotMarker,true);

        ItemCounter = 0;
        labelCounter = 1;
    }
    else {
        detachItems(QwtPlotItem::Rtti_PlotShape, false);
        detachItems(QwtPlotItem::Rtti_PlotMarker,false);

        for(int j=0;j<mPlotItemsList.count();j++) {
            mPlotItemsList.at(j)->attach(this);
        }

        int currentItems = itemList().count()-1;
        ItemCounter= currentItems;
        labelCounter = currentItems+1;
    }
    replot();
}

void GUI_Plot::addItem()
{
    if(currItem!=nullptr) {
        mPlotItemsList.append(currItem);

        savedLabels++;
        savedItems++;
        labelText.setFont(QFont("Ubuntu",11, QFont::AllLowercase));
        labelText.setText(QString::number(savedItems));
        labelText.setColor(QColor(Qt::white));
        //if(value==RectROI)
        // {
        textMarker->setLabel(labelText);
        mItemLabels.append(textMarker);
        enableAddButton(false);
    }
}

bool GUI_Plot::eventFilter( QObject *object, QEvent *event )
{
    if (object != canvas() )
        return false;

    switch( event->type())
    {
    case QEvent::MouseMove:
    {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);
        QwtPlotShapeItem *item;
        item = static_cast<QwtPlotShapeItem*>(itemAtEdge(e->pos()));
        if(item!=nullptr) {
            const QwtScaleMap xMap = canvasMap( item->xAxis() );
            const QwtScaleMap yMap = canvasMap( item->yAxis() );
            const QPointF p1 = QwtScaleMap::invTransform( xMap, yMap, e->pos() );

            qreal adjust = 10;

            QString type = item->title().text();

            if(type=="rect") { //i set this item attribute to rects in order to differenciate between the plot items

                if((p1.x() > item->boundingRect().right() - adjust) && (p1.x() < item->boundingRect().right() + adjust) && \
                        (p1.y() < item->boundingRect().bottom() + adjust) && (p1.y() > item->boundingRect().bottom() - adjust)) {

                    canvas()->setCursor(Qt::SizeBDiagCursor);
                    break;
                }


                if((p1.x() > item->boundingRect().left() - adjust) && (p1.x() < item->boundingRect().left() + adjust) && \
                        (p1.y() > item->boundingRect().top() - adjust) && (p1.y() < item->boundingRect().top() + adjust)) {
                    canvas()->setCursor(Qt::SizeBDiagCursor);
                    break;
                }

                if((p1.x() > item->boundingRect().left() - adjust) && (p1.x() < item->boundingRect().left() + adjust) && \
                        (p1.y() <  item->boundingRect().bottom() + adjust) && (p1.y() > item->boundingRect().bottom() - adjust)) {
                    canvas()->setCursor(Qt::SizeBDiagCursor);
                    break;
                }

                if((p1.x() < item->boundingRect().right() + adjust) && (p1.x() > item->boundingRect().right() - adjust) && \
                        (p1.y() < item->boundingRect().top() + adjust) && (p1.y() > item->boundingRect().top() - adjust)) {
                    canvas()->setCursor(Qt::SizeBDiagCursor);
                    break;

                }

                if(p1.x() < item->boundingRect().center().x()+adjust&&(p1.x() > item->boundingRect().center().x()-adjust) && \
                        (p1.y() < item->boundingRect().center().y()+adjust)&&(p1.y() > item->boundingRect().y()-adjust)){
                    canvas()->setCursor(Qt::OpenHandCursor);
                    break;


                }
                else if (!(p1.x() < item->boundingRect().center().x()+adjust&&(p1.x() > item->boundingRect().center().x()-adjust) && \
                           (p1.y() < item->boundingRect().center().y()+adjust)&&(p1.y() > item->boundingRect().y()-adjust))) {
                    canvas()->setCursor(Qt::ArrowCursor);
                    break;
                }
            }
            else if(type=="ellipse") // item attribute for ellipses
            {
                adjust = 20;

                if((p1.x() > item->shape().boundingRect().right() - adjust) && (p1.x() < item->shape().boundingRect().right() + adjust) && \
                        (p1.y() < item->shape().boundingRect().bottom() + adjust) && (p1.y() > item->shape().boundingRect().bottom() - adjust)) {
                    canvas()->setCursor(Qt::SizeBDiagCursor);
                    break;
                }

                if((p1.x() > item->shape().boundingRect().left() - adjust) && (p1.x() < item->shape().boundingRect().left() + adjust) && \
                        (p1.y() > item->shape().boundingRect().top() - adjust) && (p1.y() < item->shape().boundingRect().top() + adjust)) {

                    canvas()->setCursor(Qt::SizeBDiagCursor);
                    break;
                }

                if((p1.x() > item->shape().boundingRect().left() - adjust) && (p1.x() < item->shape().boundingRect().left() + adjust) && \
                        (p1.y() <  item->shape().boundingRect().bottom() + adjust) && (p1.y() > item->shape().boundingRect().bottom() - adjust)) {
                    canvas()->setCursor(Qt::SizeBDiagCursor);
                    break;
                }

                if((p1.x() < item->shape().boundingRect().right() + adjust) && (p1.x() > item->shape().boundingRect().right() - adjust) && \
                        (p1.y() < item->shape().boundingRect().top() + adjust) && (p1.y() > item->shape().boundingRect().top() - adjust))  {
                    canvas()->setCursor(Qt::SizeBDiagCursor);
                    break;
                }

                if((p1.x() < item->shape().boundingRect().center().x()+adjust)&&(p1.x() > item->shape().boundingRect().center().x()-adjust) && \
                        (p1.y() < item->shape().boundingRect().center().y()+adjust)&&(p1.y() > item->shape().boundingRect().y()-adjust)) {
                    canvas()->setCursor(Qt::OpenHandCursor);
                    break;
                }
                else if(!(p1.x() < item->boundingRect().center().x()+adjust&&(p1.x() > item->boundingRect().center().x()-adjust) && \
                          (p1.y() < item->boundingRect().center().y()+adjust)&&(p1.y() > item->boundingRect().y()-adjust))){
                    canvas()->setCursor(Qt::ArrowCursor);
                    break;
                }

            }
            else if(type=="free")
            {
                if(p1.x() < item->boundingRect().center().x()+adjust&&(p1.x() > item->boundingRect().center().x()-adjust) && \
                        (p1.y() < item->boundingRect().center().y()+adjust)&&(p1.y() > item->boundingRect().y()-adjust)) {
                    canvas()->setCursor(Qt::OpenHandCursor);
                    break;
                }
                else if(!(p1.x() < item->boundingRect().center().x()+adjust&&(p1.x() > item->boundingRect().center().x()-adjust) && \
                          (p1.y() < item->boundingRect().center().y()+adjust)&&(p1.y() > item->boundingRect().y()-adjust))) {
                    canvas()->setCursor(Qt::ArrowCursor);
                    break;
                }
            }
            item=nullptr;
        }
        else
            canvas()->setCursor(Qt::ArrowCursor);

        break;
    }
    case QEvent::HoverMove:
    {
        break;
    }
    case QEvent::FocusOut:
    {
        break;
    }
    default:
        break;
    }

    return QObject::eventFilter( object, event );
}

QwtPlotItem *GUI_Plot::itemAt( const QPoint& pos ) const
{
    // translate pos into the plot coordinates
    double xCoord,yCoord;
    xCoord = canvasMap(QwtPlot::xBottom).invTransform(pos.x());
    yCoord = canvasMap( QwtPlot::yLeft ).invTransform( pos.y() );

    QwtPlotItemList items = itemList();
    for ( int i = itemList().size() - 1; i >= 0; i-- ) {
        QwtPlotItem *item = items[ i ];
        if ( item->isVisible() &&  item->rtti() == QwtPlotItem::Rtti_PlotShape ) {
            QwtPlotShapeItem *shapeItem = static_cast<QwtPlotShapeItem *>( item );
            const QPointF p( xCoord, yCoord );

            if ( shapeItem->boundingRect().center() == p )
                return shapeItem;
        }
    }
    return nullptr;
}

QwtPlotItem *GUI_Plot::itemAtEdge( const QPoint& pos ) const
{
    // translate pos into the plot coordinates
    double xCoord,yCoord;
    xCoord = canvasMap(QwtPlot::xBottom).invTransform(pos.x());
    yCoord = canvasMap( QwtPlot::yLeft ).invTransform( pos.y() );

    QwtPlotItemList items = itemList();
    // QwtPlotItemList selected;
    for ( int i = itemList().size() - 1; i >= 0; i-- ){
        QwtPlotItem *item = items[ i ];
        if ( item->isVisible() &&
             item->rtti() == QwtPlotItem::Rtti_PlotShape ) {
            QwtPlotShapeItem *shapeItem = static_cast<QwtPlotShapeItem *>( item );
            const QPointF p( xCoord, yCoord );

            if ( shapeItem->shape().contains(p))
                return shapeItem;
        }
    }

    return nullptr;
}

bool GUI_Plot::pressed( const QPoint& pos )
{
    QwtPlotItem *resized;
    resized = itemAtEdge(pos);

    if (resized!=nullptr)
    {
        d_currentPos = pos;
        QPointF p(pos);

        if(!mPlotItemsList.contains(resized)) {
            d_editedItem =  static_cast<QwtPlotShapeItem*>(resized);
            currItemIndex = itemList().indexOf(resized)-1;

            accepted = true;
            return true;
        }
        else
        {
            initialItem =  static_cast<QwtPlotShapeItem*>(resized);
            currItemIndex = itemList().indexOf(resized)-1;

            if(currItemIndex<mItemLabels.count()){
                if(mItemLabels.at(currItemIndex)->isVisible())
                    mItemLabels.at(currItemIndex)->detach();
            }

            QString tst = initialItem->title().text();
            d_editedItem = new QwtPlotShapeItem(tst);
            d_editedItem->setPen(QColor(Qt::yellow));

            if(tst == "rect"){
                d_editedItem->setRect(initialItem->boundingRect());
                d_editedItem->attach(this);
                setItemVisible( d_editedItem, true );
                initialItem->detach();
                accepted = true;
                return true;
            }

            if(tst == "ellipse"){
                QPainterPath  upShape;
                upShape.addEllipse(initialItem->boundingRect());
                d_editedItem->setShape(upShape);
                d_editedItem->attach(this);
                setItemVisible( d_editedItem, true );
                initialItem->detach();
                accepted = true;
                return true;
            }

            if(tst == "free"){
                d_editedItem->setShape(initialItem->shape());
                d_editedItem->attach(this);
                setItemVisible( d_editedItem, true );
                initialItem->detach();
                accepted = true;
                return true;
            }
        }
    }
    else{
        accepted = false;
        return false;
    }
}

void GUI_Plot::released( const QPoint& pos )
{
    Q_UNUSED( pos );
    if (!accepted)
        return ;
    else{
        raiseItem(d_editedItem );
        setItemVisible(d_editedItem, true );
    }
}

void GUI_Plot::raiseItem( QwtPlotShapeItem *shapeItem )
{
    const QwtPlot *plot = this;
    if ( plot == nullptr || shapeItem == nullptr )
        return;

    const QwtPlotItemList items = plot->itemList();
    for ( int i = items.size() - 1; i >= 0; i-- ) {
        QwtPlotItem *item = items[ i ];
        if ( shapeItem == item )
            return;

        if ( item->isVisible() &&
             item->rtti() == QwtPlotItem::Rtti_PlotShape )
        {
            shapeItem->setZ( item->z() + 1 );
            return;
        }
    }
}

void GUI_Plot::setItemVisible( QwtPlotShapeItem *item, bool on )
{
    if (item == nullptr || item->isVisible() == on )
        return;

    // const bool doAutoReplot = autoReplot();
    // setAutoReplot( );

    item->setVisible( on);

    //  setAutoReplot( true );

    /*
      Avoid replot with a full repaint of the canvas.
      For special combinations - f.e. using the
      raster paint engine on a remote display -
      this makes a difference.
     */

    QwtPlotCanvas *canvas =
            qobject_cast<QwtPlotCanvas *>( this->canvas() );
    if ( canvas )
        canvas->invalidateBackingStore();
}

void GUI_Plot::mousePressEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton) && value == RectROI) {
        if ( !pressed( event->pos() ) ) {
            clearROIS();
            enableAddButton(false);
            if(moveSelection||resizeSelection){
                canvas()->setCursor(Qt::CrossCursor);
                construct_picker_machine(RectROI);
                moveSelection=false;
            }

            rect_picker->setRubberBandPen(QPen(Qt::yellow, 1, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
            rect_picker->setRubberBand(QwtPicker::RectRubberBand);
            connect(rect_picker,SIGNAL(selected(QRectF)),this,SLOT(selected_RECT_ROI(QRectF)),Qt::UniqueConnection);
        }
        else {
            moveSelection = true;
            destruct_picker_machine(RectROI);
        }
    }
    else if ( (event->button() == Qt::LeftButton) && value==EllipseROI ) {
        if(!pressed(event->pos())) {
            clearROIS();
            enableAddButton(false);

            if(moveSelection||resizeSelection) {
                canvas()->setCursor(Qt::CrossCursor);
                construct_picker_machine(EllipseROI);
                moveSelection=false;
            }

            if ( ellipse_picker ){
                ellipse_picker->setRubberBandPen((QPen(Qt::yellow, 1, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin)));
                ellipse_picker->setRubberBand(QwtPicker::EllipseRubberBand);
                connect(ellipse_picker,SIGNAL(selected(QRectF)),this,SLOT(selected_ELLIPSE_ROI(QRectF)),Qt::UniqueConnection);
            }
        }
        else {
            moveSelection = true;
            destruct_picker_machine(EllipseROI);
        }
    }
    else if(event->button() == Qt::LeftButton && value==FreeDrawROI ) {
        if(!pressed(event->pos())) {

            clearROIS();
            enableAddButton(false);
            if(moveSelection||resizeSelection) {
                canvas()->setCursor(Qt::CrossCursor);
                construct_picker_machine(FreeDrawROI);
                moveSelection=false;
            }

            mCurrentPath = QPainterPath();
            currItem = new QwtPlotShapeItem("free");

            double xCoord,yCoord;
            xCoord = canvasMap(QwtPlot::xBottom).invTransform(event->pos().x());
            yCoord = canvasMap( QwtPlot::yLeft ).invTransform(event->pos().y() );
            QPointF point(xCoord,yCoord);
            startPoint = point;
            lastPoint = point;
            drawing = true;
            drawStarted = true;
        }
        else {
            moveSelection = true;
            destruct_picker_machine(FreeDrawROI);
        }
    }
    else
        event->ignore();
}

void GUI_Plot::moved( const QPoint& pos )
{
    if (!accepted)
        return ;

    const QwtScaleMap xMap = canvasMap( d_editedItem->xAxis() );
    const QwtScaleMap yMap = canvasMap( d_editedItem->yAxis() );

    const QPointF p1 = QwtScaleMap::invTransform( xMap, yMap, d_currentPos );
    const QPointF p2 = QwtScaleMap::invTransform( xMap, yMap, pos);

    QPainterPath shape = d_editedItem->shape().translated( p2 - p1 );
    QRect r(p1.toPoint(),p2.toPoint());
    qreal adjust = 10;

    QString type = d_editedItem->title().text();


    if(type=="rect") { //i set this item attribute to rects in order to differenciate between the plot items
        if((p1.x() > d_editedItem->boundingRect().right() - adjust) && (p1.x() < d_editedItem->boundingRect().right() + adjust) && \
                (p1.y() < d_editedItem->boundingRect().bottom() + adjust) && (p1.y() > d_editedItem->boundingRect().bottom() - adjust)) {

            canvas()->setCursor(Qt::SizeBDiagCursor);
#ifdef QT_DEBUG
            qDebug()<<"bottom right";
#endif
            QRectF t(d_editedItem->boundingRect().topLeft(),p2);

            d_editedItem->setRect(t);
        }

        if((p1.x() > d_editedItem->boundingRect().left() - adjust) && (p1.x() < d_editedItem->boundingRect().left() + adjust) && \
                (p1.y() > d_editedItem->boundingRect().top() - adjust) && (p1.y() < d_editedItem->boundingRect().top() + adjust)) {

            canvas()->setCursor(Qt::SizeBDiagCursor);
#ifdef QT_DEBUG
            qDebug()<<"top left";
#endif
            QRectF t(d_editedItem->boundingRect().bottomRight(),p2);

            d_editedItem->setRect(t);
        }


        if((p1.x() > d_editedItem->boundingRect().left() - adjust) && (p1.x() < d_editedItem->boundingRect().left() + adjust) && \
                (p1.y() <  d_editedItem->boundingRect().bottom() + adjust) && (p1.y() > d_editedItem->boundingRect().bottom() - adjust)) {
            canvas()->setCursor(Qt::SizeBDiagCursor);
#ifdef QT_DEBUG
            qDebug()<<"bottom left";
#endif

            QRectF t(d_editedItem->boundingRect().topRight(),p2);
            d_editedItem->setRect(t);
        }

        if((p1.x() < d_editedItem->boundingRect().right() + adjust) && (p1.x() > d_editedItem->boundingRect().right() - adjust) && \
                (p1.y() < d_editedItem->boundingRect().top() + adjust) && (p1.y() > d_editedItem->boundingRect().top() - adjust))
        {
            canvas()->setCursor(Qt::SizeBDiagCursor);
#ifdef QT_DEBUG
            qDebug()<<"top right";
#endif
            QRectF t(d_editedItem->boundingRect().bottomLeft(),p2);

            d_editedItem->setRect(t);
        }

        if(p1.x() < d_editedItem->boundingRect().center().x()+adjust&&(p1.x() > d_editedItem->boundingRect().center().x()-adjust) && \
                (p1.y() < d_editedItem->boundingRect().center().y()+adjust)&&(p1.y() > d_editedItem->boundingRect().y()-adjust)) {
            canvas()->setCursor(Qt::ClosedHandCursor);
            QPainterPath shape = d_editedItem->shape().translated( p2 - p1 );
            d_editedItem->setShape(shape);
        }
    }
    else if(type=="ellipse") // item attribute for ellipses
    {
        if((p1.x() > d_editedItem->shape().boundingRect().right() - adjust) && (p1.x() < d_editedItem->shape().boundingRect().right() + adjust) && \
                (p1.y() < d_editedItem->shape().boundingRect().bottom() + adjust) && (p1.y() > d_editedItem->shape().boundingRect().bottom() - adjust)) {
            canvas()->setCursor(Qt::SizeBDiagCursor);
#ifdef QT_DEBUG
            qDebug()<<"bottom right";
#endif
            QRectF t(d_editedItem->boundingRect().topLeft(),p2);

            QPainterPath el;
            el.addEllipse(t);

            d_editedItem->setShape(el);
        }

        if((p1.x() > d_editedItem->shape().boundingRect().left() - adjust) && (p1.x() < d_editedItem->shape().boundingRect().left() + adjust) && \
                (p1.y() > d_editedItem->shape().boundingRect().top() - adjust) && (p1.y() < d_editedItem->shape().boundingRect().top() + adjust)) {
            canvas()->setCursor(Qt::SizeBDiagCursor);
#ifdef QT_DEBUG
            qDebug()<<"top left";
#endif

            QRectF t(d_editedItem->boundingRect().bottomRight(),p2);
            QPainterPath el;
            el.addEllipse(t);

            d_editedItem->setShape(el);
        }

        if((p1.x() > d_editedItem->shape().boundingRect().left() - adjust) && (p1.x() < d_editedItem->shape().boundingRect().left() + adjust) && \
                (p1.y() <  d_editedItem->shape().boundingRect().bottom() + adjust) && (p1.y() > d_editedItem->shape().boundingRect().bottom() - adjust)) {
            canvas()->setCursor(Qt::SizeBDiagCursor);
#ifdef QT_DEBUG
            qDebug()<<"bottom left";
#endif
            QRectF t(d_editedItem->boundingRect().topRight(),p2);
            QPainterPath el;
            el.addEllipse(t);

            d_editedItem->setShape(el);
        }

        if((p1.x() < d_editedItem->shape().boundingRect().right() + adjust) && (p1.x() > d_editedItem->shape().boundingRect().right() - adjust) && \
                (p1.y() < d_editedItem->shape().boundingRect().top() + adjust) && (p1.y() > d_editedItem->shape().boundingRect().top() - adjust)) {
            canvas()->setCursor(Qt::SizeBDiagCursor);
#ifdef QT_DEBUG
            qDebug()<<"top right";
#endif

            QRectF t(d_editedItem->boundingRect().bottomLeft(),p2);
            QPainterPath el;
            el.addEllipse(t);

            d_editedItem->setShape(el);
        }

        if((p1.x() < d_editedItem->shape().boundingRect().center().x()+adjust)&&(p1.x() > d_editedItem->shape().boundingRect().center().x()-adjust) && \
                (p1.y() < d_editedItem->shape().boundingRect().center().y()+adjust)&&(p1.y() > d_editedItem->shape().boundingRect().y()-adjust)) {
            canvas()->setCursor(Qt::ClosedHandCursor);
            QPainterPath shape = d_editedItem->shape().translated( p2 - p1 );
            d_editedItem->setShape(shape);
        }
    }
    else if(type=="free") {
        if(p1.x() < d_editedItem->boundingRect().center().x()+adjust&&(p1.x() > d_editedItem->boundingRect().center().x()-adjust) && \
                (p1.y() < d_editedItem->boundingRect().center().y()+adjust)&&(p1.y() > d_editedItem->boundingRect().y()-adjust)) {
            canvas()->setCursor(Qt::ClosedHandCursor);
            QPainterPath shape = d_editedItem->shape().translated( p2 - p1 );
            d_editedItem->setShape(shape);
        }
    }
    replot();
    d_currentPos = pos;
}

void GUI_Plot::resize(const QPoint& pos )
{
    if (!accepted)
        return ;

    canvas()->setCursor(Qt::DragMoveCursor);

    const QwtScaleMap xMap = canvasMap( d_editedItem->xAxis() );
    const QwtScaleMap yMap = canvasMap( d_editedItem->yAxis() );
    const QPointF p1 = QwtScaleMap::invTransform( xMap, yMap, d_currentPos );
    const QPointF p2 = QwtScaleMap::invTransform( xMap, yMap, pos);
    const QPainterPath shape = d_editedItem->shape().translated( p2 + p1 );
    d_editedItem->setShape( shape );
    replot();
    d_currentPos = pos;
}

void GUI_Plot::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton && drawing && value == FreeDrawROI)
        drawLineTo(event->pos());
    else if(event->buttons() == Qt::LeftButton && moveSelection)
        moved(event->pos());
    else if(event->buttons() == Qt::LeftButton && resizeSelection)
        moved(event->pos());
}


bool GUI_Plot::cmpd(double a, double b, double epsilon) { return std::abs(a - b) < epsilon; }

void GUI_Plot:: mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && drawing && value == FreeDrawROI) {
        if(!cmpd(mCurrentPath.boundingRect().height(),0)&&!cmpd(mCurrentPath.boundingRect().width(),0)) {
            drawing = false;
            moveSelection = false;
            //lastPoint = event->pos();
            drawLineTo(event->pos());
            //endDraw(event->pos());

        }
        else
            currItem = nullptr;
    }
    else if(event->button() == Qt::LeftButton && moveSelection) {
        released(event->pos());
        moveSelection = true;
    }
}

void GUI_Plot::drawLineTo(QPointF endPoint)
{
    double xCoord,yCoord,x2,y2;
    xCoord = canvasMap(QwtPlot::xBottom).invTransform(endPoint.x());
    yCoord = canvasMap( QwtPlot::yLeft ).invTransform(endPoint.y() );

    QPointF p( xCoord, yCoord ), p2( x2, y2 );

    if(drawing) {
        if(drawStarted) {
            mCurrentPath.moveTo(lastPoint);
            drawStarted = false;
        }
        else if(!drawStarted)
            mCurrentPath.lineTo(p);

        currItem->setPen(QPen(Qt::yellow,1, Qt::SolidLine, Qt::RoundCap,
                              Qt::RoundJoin));
        currItem->setShape(mCurrentPath);
        currItem->setItemAttribute(QwtPlotItem::Legend,true);
        currItem->attach(this);

        int rad = (1 / 2) + 2;
        update(QRect(p2.toPoint(), endPoint.toPoint()).normalized()
               .adjusted(-rad, -rad, +rad, +rad));
        lastPoint = p;
        replot();
    }
    else if ( !drawing ){
        mCurrentPath.moveTo(startPoint);
        mCurrentPath.lineTo(p);

        currItem->setShape(mCurrentPath);
        currItem->attach(this);

        int rad = (1 / 2) + 2;
        update(QRect(p2.toPoint(), endPoint.toPoint()).normalized()
               .adjusted(-rad, -rad, +rad, +rad));

        ItemCounter++;

        QRectF free_area = mCurrentPath.boundingRect();
        QPointF c = free_area.center();
        textMarker = new QwtPlotMarker();
        textMarker->setValue(c);

        textMarker->setLinePen(QColor(Qt::white),1,Qt::NoPen);
        poly_stat = mCurrentPath.toFillPolygon();

        QPolygonF poly = poly_stat;

        replot();
        enableAddButton(true);
    }
}

void GUI_Plot::selected_RECT_ROI(QRectF pol)
{
    if(!cmpd(pol.width(),0)&& !cmpd(pol.height(),0)) {

        currItem = nullptr;

        currItem = new QwtPlotShapeItem("rect");
        currItem->setPen(QColor(Qt::yellow));

        QPointF p;
        p = pol.center();

        QPainterPath rectPath;
        rectPath.addRect(pol);
        currItem->setRect(pol);

        poly_rect = rectPath.toFillPolygon();

        currItem->setItemAttribute(QwtPlotItem::Margins,true);
        currItem->attach(this);
        ItemCounter++;

        textMarker = new QwtPlotMarker();
        textMarker->setValue(p);
        textMarker->setLinePen(QColor(Qt::white),1,Qt::NoPen);
        replot();
        enableAddButton(true);
    }
    else
        currItem = nullptr;
}

void GUI_Plot::selected_ELLIPSE_ROI(QRectF pol)
{
    if(!cmpd(pol.width(),0)&& !cmpd(pol.height(),0)){
        currItem = nullptr;
        currItem = new QwtPlotShapeItem("ellipse");
        currItem->setPen(QColor(Qt::yellow));

        QPainterPath path ;
        path.addEllipse(pol);

        currItem->setShape(path);
        currItem->setItemAttribute(QwtPlotItem::AutoScale,true);
        currItem->attach(this);

        ItemCounter++;

        QPointF p;
        p = pol.center();

        textMarker = new QwtPlotMarker();
        textMarker->setValue(p);
        textMarker->setLinePen(QColor(Qt::white),1,Qt::NoPen);
        moveSelection = false;

        replot();
        enableAddButton(true);
    }
    else
        currItem = nullptr;
}


///////////// Model for measurements table /////////////
NumberFormatDelegate::NumberFormatDelegate(QObject *parent) :
    QStyledItemDelegate(parent){}

QString NumberFormatDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    QString formattedNum = locale.toString(value.toDouble(), 'f', 2);
    return formattedNum;
}

PostProcessing::PostProcessing(ReadInputInfo* readInfo, QWidget *parent) : QMainWindow(parent),
    ui(new Ui::PostProcessing ), m_plotSelector( new Ui::PlotSelector ),
    m_qDialogPlotSelect( nullptr ), m_pReadInfo( nullptr ), m_bIsBeta( false )
{
//    maxCor = 0.0;

    ui->setupUi(this);
    m_pReadInfo = readInfo;

    if ( m_pReadInfo->getSystemName().contains("SCC") ) {
        m_bIsBeta = true;
        ui->label_3->setGeometry( 630, 0, 31, 31);
        ui->label_4->setGeometry( 630, 260, 31, 31);
    }

    ui->radioButtonCountsPerROI->setChecked( true );
    m_isFirstPlotted = true;

    connect( ui->radioButtonAcivityPerROI, SIGNAL( clicked( bool ) ), this, SLOT( selectActivityPerROI( bool ) ) );
    connect( ui->radioButtonCountsPerROI, SIGNAL( clicked( bool ) ), this, SLOT( selectCountsPerROI( bool ) ) );

    connect( ui->cB_fusion, SIGNAL(clicked()),this, SLOT(setCheckstateOptical()));
    connect( ui->cB_xray, SIGNAL(clicked()),this, SLOT(setCheckstateXray()));


    this->layout()->setMenuBar(ui->menubar);
    ui->menubar->show();
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    rectButtonActive = false;
    ellipseButtonActive = false;
    freeDrawButtonActivel = false;
    from_load = false;
    fastDynamic=false;
    ui->PB_plot_excel->setEnabled(false);
    ui->PB_pdfReport->setEnabled(false);

    ui->PB_updatePos->setEnabled(false);
    ui->PB_deleteRoi->setEnabled(false);
    ui->PB_renameRoi->setEnabled(false);
    ui->PB_refArea->setEnabled(false);
    ui->PB_refArea->hide();
    ui->PB_measure->hide();

    ui->L_InitActivity->hide();
    ui->dSB_activity->hide();
    ui->rb_mBq_2->hide();
    ui->rb_mCi->hide();

    ui->horizontalScrollBar_2->setEnabled(false);
    updated = false;
    ui->tB_playStack->setVisible(false);

    m_bOpticalSet = false;
    central_Plot = nullptr;
    graphs = nullptr;
    cM = nullptr;
    col = nullptr;
    row = nullptr;

    view = new QGraphicsView();
    scene1= new QGraphicsScene(view);

    if ( central_Plot == nullptr )
        central_Plot = new GUI_Plot(this,true);

    central_Plot->corMatrix1->setResampleMode(central_Plot->corMatrix1->BilinearInterpolation);

    if ( graphs == nullptr )
        graphs = new GUI_Plot(this,false);

    QDialog* diag = new QDialog( graphs );
    m_plotSelector->setupUi( diag );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setXAxis(QwtPlot::xBottom);
    grid->setPen(QColor(Qt::lightGray));

    graphs->setAxisScale( QwtPlot::yLeft, -1, 1e+7, 1e+7/5 ); //Scale the y-axis0
    graphs->setAxisScale( QwtPlot::xBottom,-1, 1e+7, 1e+7/5 ); //Scale the x-axis
    graphs->plotLayout()->setAlignCanvasToScales(true);
    grid->attach(graphs);

    ui->horizontalLayout_3->addWidget(central_Plot);
    ui->horizontalLayout_2->addWidget(graphs);

    /// Plots' size policy
    //////////////////////////////////////////////////
    ui->PB_showRois->setCheckable(true);
    ui->PB_ShowLabels->setCheckable(true);
    ui->ROI_list->setSelectionMode(QAbstractItemView::SingleSelection);

    if(cM == nullptr)
        cM = new ColorMap();
    cM->BlackBased(1);

    cM2 = new ColorMap();
    cM2->BlackBased(1);

    central_Plot->spectrogram1->setColorMap(cM);



    ui->CB_colormaps->setCurrentIndex(1);


    bFromLastStudy = false;
    connect(ui->action_loadStudy, SIGNAL( triggered(bool) ), this, SLOT( LoadStudy_triggered() ), Qt::UniqueConnection);
    connect(ui->CB_colormaps,SIGNAL( currentIndexChanged(int)),this,SLOT(combobox_currentIndexChanged(int)));
    connect(ui->actionLoad_Last_Study_2, SIGNAL( triggered(bool) ), this, SLOT( loadLastStudy() ), Qt::UniqueConnection);

    QIcon icon;
    icon.addPixmap(QPixmap(":/logos/media-playback-start.png"),QIcon::Normal,QIcon::Off);
    icon.addPixmap(QPixmap(":/logos/chronometer.png"),QIcon::Normal,QIcon::On);
    ui->tB_playStack->setIcon(icon);
    ui->tB_playStack->setCheckable(true);
    ui->PB_merge->setDisabled(true);
    ui->pb_rectROI->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->pb_rectROI, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(ShowContextMenu(const QPoint&)));

    ui->pb_ellipseROI->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->pb_ellipseROI, SIGNAL( customContextMenuRequested(const QPoint&)),
            this, SLOT(ShowContextMenu2(const QPoint&)));
    connect(ui->horizontalScrollBar_2,SIGNAL( sliderMoved(int) ),SLOT(ImageSlider(int)));
    connect(ui->horizontalScrollBar_2,SIGNAL( valueChanged(int) ),SLOT(ImageSlider(int)));

    connect(ui->pb_rectROI,SIGNAL(clicked()),this,SLOT(on_pb_rectROI_clicked(bool)),Qt::UniqueConnection);
    connect(ui->pb_ellipseROI,SIGNAL(clicked()),this,SLOT(on_pb_ellipseROI_clicked(bool)),Qt::UniqueConnection);
    connect(ui->pb_freeROI,SIGNAL(clicked()),this,SLOT(on_pb_freeROI_clicked(bool)),Qt::UniqueConnection);
    connect(central_Plot,SIGNAL(enableAddButton(bool)),ui->PB_addRoi,SLOT(setEnabled(bool)));
    connect(central_Plot,SIGNAL(disableAddButton(bool)),ui->PB_addRoi,SLOT(setEnabled(bool)));
    connect(ui->PB_addRoi,SIGNAL(pressed()),central_Plot,SLOT(addItem()));
    connect(ui->PB_addRoi,SIGNAL(pressed()),this,SLOT(addROItoList()));
    connect(ui->PB_showRois,SIGNAL(clicked()),this,SLOT(on_PB_showRois_clicked(bool)),Qt::UniqueConnection);
    connect(ui->PB_ShowLabels,SIGNAL(clicked()),this,SLOT(on_PB_ShowLabels_toggled(bool)));

    connect(ui->PB_deleteRoi,SIGNAL(pressed()),this,SLOT(delete_roi()));
    connect(ui->ROI_list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(on_ROI_list_itemClicked(QListWidgetItem*)),Qt::UniqueConnection);
    connect(ui->ROI_list,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(on_ROI_list_itemDoubleClicked(QListWidgetItem*)),Qt::UniqueConnection);
    connect(ui->PB_renameRoi,SIGNAL(pressed()),this,SLOT(on_PB_renameRoi_pressed()),Qt::UniqueConnection);
    connect(ui->ROI_list->itemDelegate(), &QAbstractItemDelegate::commitData, this, &PostProcessing::OnItemsCommitData);
    connect(ui->PB_plotRois, SIGNAL(pressed()), this, SLOT( plotROIS() ) );
    connect(ui->PB_refArea,SIGNAL(pressed()),this,SLOT(set_reference_area()));
    connect(ui->PB_saveAs,SIGNAL(pressed()),this,SLOT( saveImageAs()));
    connect(ui->PB_saveAllFrames,SIGNAL(pressed()),this,SLOT(saveAllFrames()));
    connect(ui->PB_savePlot,SIGNAL(pressed()),this,SLOT(savePlotAsImage()));
    connect(ui->pb_reset_4,SIGNAL(pressed()),this,SLOT(clearAll() ) );
    connect(ui->PB_merge, SIGNAL(clicked()), this, SLOT(on_PB_merge()));
    connect(ui->PB_pdfReport, SIGNAL(clicked()), this, SLOT(on_PB_pdfReport()));


    ui->horizontalSlider_contrast->setFocusPolicy(Qt::StrongFocus);
    ui->horizontalSlider_contrast->setRange(0,100);
    ui->horizontalSlider_contrast->setTickPosition(QSlider::TicksBothSides);
    ui->horizontalSlider_contrast->setValue(100);
    ui->horizontalSlider_contrast->setTickInterval(10);
    ui->horizontalSlider_contrast->setSingleStep(10);
    ui->horizontalSlider_contrast->setEnabled(false);

    connect(ui->horizontalSlider_contrast, SIGNAL(valueChanged(int)),this,SLOT(sliderValueChanged(int)));

    ui->horizontalSlider_contrast_min->setFocusPolicy(Qt::StrongFocus);
    ui->horizontalSlider_contrast_min->setRange(0,100);
    ui->horizontalSlider_contrast_min->setTickPosition(QSlider::TicksBothSides);
    ui->horizontalSlider_contrast_min->setValue(0);
    ui->horizontalSlider_contrast_min->setTickInterval(10);
    ui->horizontalSlider_contrast_min->setSingleStep(10);
    ui->horizontalSlider_contrast_min->setEnabled(false);

    connect( ui->horizontalSlider_contrast_min, SIGNAL(valueChanged(int)), this, SLOT( ms_sliderValueChangedMin(int) ) );


    connect(ui->sB_max,SIGNAL(valueChanged(double)),this,SLOT(sB_max_changed(double)),Qt::UniqueConnection);
    connect(ui->sB_min,SIGNAL(valueChanged(double)),this,SLOT(sB_min_changed(double)),Qt::UniqueConnection);



    ui->opacitySlider->setFocusPolicy(Qt::StrongFocus);
    ui->opacitySlider->setRange(0,255);
    ui->opacitySlider->setTickPosition(QSlider::TicksBothSides);
    ui->opacitySlider->setValue(150);
    ui->opacitySlider->setTickInterval(10);
    ui->opacitySlider->setSingleStep(5);
    ui->opacitySlider->setEnabled(false);

    connect(ui->opacitySlider, SIGNAL(valueChanged(int)), this, SLOT( opacityValueChanged(int)));

    ///////Pop-up measurment table///
    diaTable = new QDialog(this);

    diaTable->setWindowTitle("ROI Measurements");
    gLayout = new QGridLayout;
    diaTable->setLayout(gLayout);

    measurement_table = new QTableWidget(this);
    tableHeader<<"#"<<"mean"<<"std"<<"total counts";

    //measurement_table->verticalHeader()->setVisible(false);
    measurement_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    measurement_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    measurement_table->setSelectionMode(QAbstractItemView::SingleSelection);
    measurement_table->setShowGrid(true);
    measurement_table->setStyleSheet("QTableView {selection-background-color: blue;}");
    measurement_table->setGeometry(500,500,500,500);
    measurement_table->setDragEnabled(true);
    measurement_table->setWindowTitle("ROI Measurements");
    measurement_table->setColumnCount(4);
    measurement_table->setItemDelegateForColumn(1, new NumberFormatDelegate(this));
    measurement_table->setItemDelegateForColumn(2, new NumberFormatDelegate(this));
    measurement_table->setItemDelegateForColumn(3, new NumberFormatDelegate(this));
    measurement_table->setItemDelegateForColumn(4, new NumberFormatDelegate(this));
    measurement_table->setHorizontalHeaderLabels(tableHeader);
    diaTable->layout()->addWidget(measurement_table);
    connect(diaTable,SIGNAL(finished(int)),this,SLOT(closeDialog(int)));

    QString local= QDir::currentPath().append("/colormap/royal.lut");
    m_sLutFilename = local.toStdString();
}

void PostProcessing::selectActivityPerROI( bool isActSel )
{
    if ( !isActSel ){
        ui->radioButtonAcivityPerROI->setChecked( true );
        return;
    }

    ui->radioButtonAcivityPerROI->setChecked( isActSel );
    if ( isActSel ){
        ui->radioButtonCountsPerROI->setChecked( false );
    }

    m_isFirstPlotted = false;
    multi_measure();
}

void PostProcessing::selectCountsPerROI( bool isCountsSel )
{
    if ( !isCountsSel ){
        ui->radioButtonCountsPerROI->setChecked( true );
        return;
    }

    ui->radioButtonCountsPerROI->setChecked( isCountsSel );
    if ( isCountsSel )
        ui->radioButtonAcivityPerROI->setChecked( false );

    m_isFirstPlotted = false;
    multi_measure();
}

void PostProcessing::mf_loadOpticalImage()
{
    // row col is always the same since it does not change
    if ( col && row ){
        QString OptDir = POST_PROC_path;

        QStringList dirList=OptDir.split("/");
        foreach(QString dir, dirList){
                if( dir.contains("FINAL") )
                    dirList.removeAll(dir);

                if( dir.contains("CORRECTED") )
                    dirList.removeAll(dir);

                if(dir.contains("POST_PROCESSING") )
                    dirList.removeAll(dir);

                if(dir.contains("Merged"))
                    dirList.removeAll(dir);

                if(dir.contains("IMAGES") )
                    dirList.removeAll(dir);

                if(dir.contains("RAW") )
                    dirList.removeAll(dir);

                if(dir.isEmpty())
                    dirList.removeAll(dir);

        }
        OptDir=dirList.join("/");
        OptDir.push_front("/");


       qDebug() << "Reached here .....   " << endl ;

        QString opticalImgPath=OptDir + "/optical.png";
        QString xrayImgPath=OptDir + "/Xray.png";
        OptDir.append("/optical.png");

        if ( !QFile::exists( OptDir ) ) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("VISUAL-eyes");
            msgBox.setText("Could not find optical image in its default position: " + OptDir + "\nPress OK to select a file with the optical image from another location otherwise fussion will not be possible.");
            msgBox.setStandardButtons(QMessageBox::Cancel);
            msgBox.addButton(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);

            if( msgBox.exec() == QMessageBox::Ok){
                OptDir = QFileDialog::getOpenFileName(this, tr("Select Optical Image "), OptDir.remove("/optical.png"), tr("Portable Network Graphics file (*.png)"));
                m_bOpticalSet = true;
            }
            else
                return;
        }

        m_cvOpticalImage= cv::imread(opticalImgPath.toStdString(),cv::IMREAD_GRAYSCALE);
        m_cvXrayImage=cv::imread(xrayImgPath.toStdString(),cv::IMREAD_GRAYSCALE);

        /**
            Perform image flips
       **/
        QMap< QString, int > qmFlips;
        qmFlips.insert( "x", 0 );
        qmFlips.insert( "y", 1 );

        cv::rotate(m_cvOpticalImage, m_cvOpticalImage, cv::ROTATE_90_CLOCKWISE);
        cv::rotate( m_cvXrayImage,  m_cvXrayImage, cv::ROTATE_90_CLOCKWISE);
        if(m_pReadInfo->getFlips().size() >0){
            foreach ( QString flip,  m_pReadInfo->getFlips()){
                if(flip!=""){
                    cv::flip(m_cvOpticalImage, m_cvOpticalImage, qmFlips[ flip ] );
                    cv::flip(m_cvXrayImage,  m_cvXrayImage, qmFlips[ flip ] );
                }
           }
        }


        /**
            Convert images to CV_8U and resize for plotting
       **/


        cv::normalize( m_cvOpticalImage, m_cvOpticalImage, 0, 255, cv::NORM_MINMAX);
        cv::normalize(m_cvXrayImage,  m_cvXrayImage, 0, 255, cv::NORM_MINMAX);

        m_cvOpticalImage.convertTo(m_cvOpticalImage, CV_8U);
        m_cvXrayImage.convertTo(m_cvXrayImage, CV_8U);

        m_bOpticalSet = true;
    }
}

PostProcessing::~PostProcessing()
{
    m_cvOpticalImage.release();
    m_cvXrayImage.release();

    this->close();
    emit closedWindow();
    if(ui)
        delete ui;
}

void PostProcessing::loadLastStudy(){
    bFromLastStudy = true;
    int inventory = 0;
    QSqlQuery inv;
    QString max_inv = "select MAX(study_id) as max from Study order by deviceid ";
    inv.exec( max_inv );
    if ( inv.first() )
        inventory = inv.value("max").toInt();

    ui->horizontalSlider_contrast->setValue(100);
    ui->horizontalSlider_contrast_min->setValue(0);
    Init( QString::number( inventory ) );
}

void PostProcessing::Init( QString ID )
{
    m_iCurrentImage=0;
    m_iImageNum=0;
    fussedSize=0;
    frame_duration=0;
    if (!framesList.empty())
        framesList.clear();
    m_imgMin = 0.0;
    m_imgMax = 0.0;
    roi_counter = 0;
    numList=0;
    itemIndex = -1;
    labelIndex = -1;
    m_iNucliedID = 0;
    //item =0;
    counter = 0;

    if ( !central_Plot->itemList().isEmpty() )
        clearAll(); //when loading between studies discard previous ROI work

    central_Plot->enableAxis(QwtPlot::yRight, true);
    iterations = 8;
    contrast_percentage =0.00;
    StudyID = ID;

    ui->CB_ing_path->clear();
    ui->CB_radioNuclide->clear();

    QSqlQuery q,q1,query,qm;
    QString inj_pathID;
    QString nuclideID;
    int modID = 0;
    int fastD = 0;
    // float frameDurationInit = 0;
    frameDurationInit = 0;
    expDurationInit =0;

    ui->PB_merge->setDisabled(false);
    ui->PB_pdfReport->setDisabled(true);
    ui->radioButtonCountsPerROI->setChecked( true );
    ui->radioButtonAcivityPerROI->setChecked( false );
    QString load;

    if (m_bIsBeta){
        load ="SELECT * FROM Study WHERE study_id = " + StudyID;
    }else{
        load="SELECT * FROM Study JOIN Collimator ON Collimator.collimator_id LIKE Study.collimator_id JOIN radionuclide ON radionuclide.nuclide_id = Study.nuclide_id WHERE study_id ="+StudyID;
    }

    q.exec(load);
    //Nikos: Cannot load the files here
    if( q.next() ){
        ui->LE_studyID->setText( StudyID );
        ui->LE_SName->setText( q.value("name").toString());
        ui->LE_project->setText( q.value("project").toString());
        ui->LE_age->setText( q.value("age").toString());
        ui->le_marking->setText( q.value("marking").toString());
        ui->LE_p_name->setText( q.value("animal_name").toString());
        inj_pathID = q.value("path_id").toString();
        ui->LE_r_pharma->setText( q.value("r_pharma").toString());
        ui->LE_strain->setText( q.value("breed").toString());
        ui->LE_species->setText( q.value("species").toString());
        ui->TE_comments->setText( q.value("comments").toString());
        ui->dE_studyDate->setDate( q.value("date").toDate());
        ui->dTime_ingection->setDateTime( q.value("injection_date").toDateTime());
        ui->dSB_activity->setValue( q.value("activity").toDouble());
        ui->dSB_volume->setValue( q.value("volume").toDouble());
        m_iCollimatorId=q.value("collimator_id").toInt();
        ///radiobutton properties
        if  ( q.value("gender").toInt() == 0 ){
            ui->rb_female->setCheckable(false);
            ui->rb_female->setCheckable(true);
            ui->rb_female->setChecked(true);
        }
        else if ( q.value("gender").toInt() == 1 ) {
            ui->rb_male->setCheckable(false);
            ui->rb_male->setCheckable(true);
            ui->rb_male->setChecked(true);
        }

        if ( q.value("radioUnit").toInt() == 0 )
            m_sNuclideUnit = "MBq";
        else
            m_sNuclideUnit = "uCi";

        ui->dSB_injActivity->setText( q.value("injected_activity").toString() + " " + m_sNuclideUnit );

        nuclideID = q.value("nuclide_id").toString();

        // For Aileen info
        ui->l_StudID->setText( StudyID );
        if ( !q.value("animal_name").toString().isEmpty() )
            ui->l_AnimalID->setText( q.value("animal_name").toString() );

        if ( !q.value("name").toString().isEmpty() )
            ui->l_Name->setText(q.value("name").toString() );

        if ( !q.value("injected_activity").toString().isEmpty() )
            ui->l_InjectAct->setText( QString::number(q.value("injected_activity").toDouble() ) + " " + m_sNuclideUnit );

        if ( !q.value("injection_date").toDateTime().toString("dd.MM.yyyy hh:mm:ss").isEmpty() )
            ui->l_InjectDateTime->setText( q.value("injection_date").toDateTime().toString("MM/dd/yyyy hh:mm:ss") );

        m_iNucliedID = nuclideID.toInt();
        m_qsNuclideName=q.value("nuclide_name").toString();
        ui->l_Radio->setText(m_qsNuclideName);
        m_qsCollimator=q.value("coll_name").toString();
        frameDurationInit = q.value( "frame" ).toInt();
        m_sFrameUnit = q.value( "timeUnit_frame" ).toString();
        m_sExpUnit = q.value( "timeUnit_exp" ).toString();

        exp_duration = q.value( "exp_duration" ).toInt();
        expDurationInit=exp_duration;
        ui->LE_expDuration->setText( QString::number(exp_duration) + " " + m_sExpUnit );

        modID =q.value("id_modality").toInt();

        QString st = q.value("start_time").toString();
        QDateTime stdtime = QDateTime::fromString(st,"dd.MM.yyyy hh:mm:ss AP");
        st=stdtime.toString("MM/dd/yyyy hh:mm:ss AP");
        ui->dTE_aqTime->setText( st );
        ui->LE_weight->setText( q.value("weight").toString() + " gr");
        fileDirectory = q.value("fileDirectory").toString();
        fastD = q.value("fastDynamic").toInt();

    }
    else {
        //Go back and read the study info in order to store it in the data base
        //Here we must enter the code to read the data if it is not stored in the data base

        //Find the file containing the study info, namely: "StudyInfo.txt" and read the info
#ifdef QT_DEBUG
        qDebug() << "Study info path: " << qsStudyInfoPath;
#endif

        if ( qsStudyInfoPath.contains("/IMAGES/RAW/CORRECTED") )
            qsStudyInfoPath.remove( "/IMAGES/RAW/CORRECTED" );

        QFile studyInfoFile;
        studyInfoFile.setFileName("StudyInfo.txt");
        QDir::setCurrent( qsStudyInfoPath );

        if(!studyInfoFile.open(QIODevice::ReadOnly))
            QMessageBox::information(0,"error",studyInfoFile.errorString());

        QTextStream in(&studyInfoFile);
        while(!in.atEnd()) {
            QString line = in.readLine();
            if ( line.isEmpty() ) continue;

#ifdef QT_DEBUG
            qDebug() << line;
#endif

            QString simpleLine = line.simplified();
            QStringList fields = simpleLine.split(":");


            if ( fields[ 0 ].compare("ID") == 0 && !fields[ 1 ].isEmpty() ){
                if ( fields.size() >= 2 ){
                    StudyID = fields[ 1 ];
                    ui->LE_studyID->setText( StudyID );
                    ui->l_StudID->setText(StudyID);
                }
            }


            if ( fields[ 0 ].compare("Device") == 0 && !fields[ 1 ].isEmpty() ){
                if ( fields[1].trimmed() == "2" ){
                    m_device=2;
                    m_bIsBeta=true;
                    ui->label_3->setGeometry( 630, 0, 31, 31);
                    ui->label_4->setGeometry( 630, 260, 31, 31);
                }
                else{
                    m_device=1;
                    m_bIsBeta=false;
                    ui->label_3->setGeometry( 630, 260, 31, 31);
                    ui->label_4->setGeometry( 630, 0, 31, 31);
                }
            }
            if ( fields[ 0 ].compare("Fast Dynamic") == 0 ){
                if (fields[ 1 ].trimmed()=="Yes")
                    fastD =1;
            }

            if (fields[ 0 ].compare("Image Flip") == 0){
                QString temp = fields[ 1 ].trimmed();
                m_Flips = temp.split(",");
            }


            if ( fields[ 0 ].compare("Experiment Duration") == 0 ){
                if ( fields.size() >= 2 && !fields[ 1 ].isEmpty()  ){
                    QString trimFields = fields[ 1 ].trimmed();
                    QStringList ValUnit = trimFields.split(" ");

                    QString trimmedValUnit = ValUnit[0].trimmed();
                    expDurationInit = trimmedValUnit.toFloat();
                    m_sExpUnit = ValUnit[1].trimmed();
                }
            }

            if ( fields[ 0 ].compare("Frame Duration") == 0 ){
                if ( fields.size() >= 2 && !fields[ 1 ].isEmpty() ){
                    QString trimFields;
                    QStringList ValUnit;
                    if (fastD==1){
                        QString temp  = fields[2].trimmed();
                        QStringList tempL= temp.split(",");
                        trimFields=tempL[0].remove("sec");
                        frameDurationInit=trimFields.toFloat();
                        m_sFrameUnit ="sec";
                    }else {
                        trimFields = fields[ 1 ].trimmed();
                        ValUnit = trimFields.split(" ");
                        QString trimmedValUnit = ValUnit[0].trimmed();
                        frameDurationInit = trimmedValUnit.toFloat();
                        m_sFrameUnit = ValUnit[1].trimmed();
                    }


                }
            }




            if ( fields[ 0 ].compare("Gender") == 0 ){
                if ( fields[1].trimmed() == "F" ){
                    ui->rb_female->setCheckable(false);
                    ui->rb_female->setCheckable(true);
                    ui->rb_female->setChecked(true);
                }
                else {
                    ui->rb_male->setCheckable(false);
                    ui->rb_male->setCheckable(true);
                    ui->rb_male->setChecked(true);
                }
            }
            if ( fields [0].compare("Project") == 0)
                ui->LE_project->setText(fields[1].trimmed());
            if ( fields[0].compare("Name") == 0 ){
               ui->l_Name->setText(fields[1].trimmed());
               ui->LE_SName->setText(fields[1].trimmed());
            }
            if ( fields [0].compare("Age") == 0 )
                ui->LE_age->setText( fields[1].trimmed());
            if ( fields [0].compare("Marking") == 0 )
                ui->le_marking->setText(fields[1].trimmed());
            if ( fields[0].compare("Species") == 0 )
                ui->LE_species->setText(fields[1].trimmed());
            if ( fields[0].compare("Weight") == 0 )
                ui->LE_weight->setText(fields[1].trimmed() + " gr");
            if (  fields[0].compare("Injection date") == 0 ){
                if (fields.size()==4){
                    QString str=fields[1].trimmed()+":"+fields[2].trimmed()+":"+fields[3].trimmed();
                    QDateTime ijDate = QDateTime::fromString(str,"dd.MM.yyyy hh:mm:ss AP");
                    ui->l_InjectDateTime->setText( ijDate.toString("MM/dd/yyyy hh:mm:ss") );
                    ui->dTime_ingection->setDateTime( ijDate );
                }
            }
            if ( fields[0].compare("Animal name") == 0 ){
                ui->LE_p_name->setText(fields[1].trimmed());
                ui->l_AnimalID->setText(fields[1].trimmed());
            }
            if ( fields[0].compare("Breed") == 0 )
                ui->LE_strain->setText(fields[1].trimmed());
            if ( fields[0].compare("Comments") == 0 )
                ui->TE_comments->setText(fields[1].trimmed());
            if ( fields[0].compare("Collimator") == 0 ){
                m_qsCollimator=fields[1].trimmed();
            }
            if ( fields[0].compare("Radionuclide") == 0 ){
                ui->l_Radio->setText( fields[1].trimmed() );
                ui->CB_radioNuclide->addItem(fields[1].trimmed());
                m_qsNuclideName=fields[1].trimmed();
            }
            if ( fields[0].compare("Radiopharmaceutical") == 0 )
                ui->LE_r_pharma->setText( fields[1].trimmed() );
            if ( fields[0].compare("Volume") == 0 )
                ui->dSB_volume->setValue( fields[1].trimmed().toDouble() );
            if ( fields[0].compare("Radio unit") == 0 )
                m_sNuclideUnit=fields[1].trimmed();
            if ( fields[ 0 ].compare("Injected activity") == 0 ){
                ui->dSB_injActivity->setText( fields[1].trimmed()+" "+m_sNuclideUnit);
                ui->l_InjectAct->setText( fields[ 1].trimmed() +" " +m_sNuclideUnit) ;
            }
            if ( fields[0].compare("Date") == 0)
                ui->dE_studyDate->setDate(QDate::fromString(fields[1].trimmed(),"yyyy-MM-dd"));
            if ( fields[0].compare("Start Time")==0){
                if (fields.size()==4){
                    QString str=fields[1].trimmed()+":"+fields[2].trimmed()+":"+fields[3].trimmed();
                    QDateTime ijDate = QDateTime::fromString(str,"dd.MM.yyyy hh:mm:ss AP");
                    ui->dTE_aqTime->setText(ijDate.toString("MM/dd/yyyy hh:mm:ss AP"));
                }
            }
            if ( fields[0].compare("Injection path") == 0){
                if (fields[1].trimmed()=="Intravenous")
                    ui->CB_ing_path->addItem(fields[1].trimmed(),1);
                else if (fields[1].trimmed()=="Intraperitoneal")
                    ui->CB_ing_path->addItem(fields[1].trimmed(),2);
                else if (fields[1].trimmed()=="Inhalation")
                    ui->CB_ing_path->addItem(fields[1].trimmed(),3);
                else if (fields[1].trimmed()=="Intramuscular")
                    ui->CB_ing_path->addItem(fields[1].trimmed(),4);
                else if (fields[1].trimmed()=="Ingestion")
                    ui->CB_ing_path->addItem(fields[1].trimmed(),5);
                else if (fields[1].trimmed()=="Intratracheal")
                    ui->CB_ing_path->addItem(fields[1].trimmed(),6);
            }


        }


    }

    //frame duration is always in minutes
    if(m_sFrameUnit=="sec" && m_sExpUnit=="min"){
        float div = float( frameDurationInit/60 );
        frame_duration = div;
        exp_duration=expDurationInit;
        ui->LE_frame->setText(QString::number( frame_duration ) + " " + "min" );
        ui->LE_expDuration->setText( QString::number( exp_duration ) +" "+ "min");
    }
    else if(m_sFrameUnit=="sec" && m_sExpUnit=="sec"){
        float div1 = float( frameDurationInit/60 );
        float div2 = float( expDurationInit/60 );
        frame_duration = div1;
        exp_duration=div2;
        ui->LE_frame->setText(QString::number( frame_duration ) + " " +  "min" );
        ui->LE_expDuration->setText( QString::number( exp_duration ) +" "+ "min");
    }
    else{
        frame_duration = frameDurationInit;
        exp_duration=expDurationInit;
        ui->LE_frame->setText(QString::number( frame_duration ) + " " +  "min" );
        ui->LE_expDuration->setText( QString::number( exp_duration ) +" "+ "min");
    }

    if(fastD==1){
        fastDynamic=true;
        ui->rB_fDynamic->setChecked(true);
    }
    else{
        fastDynamic=false;
        ui->rB_fDynamic->setChecked(false);
    }


    QString str = "select * from InjectionPath where path_id = " + inj_pathID;
    q1.exec(str);
    while(q1.next()) {
        QString name = q1.value("name").toString();
        int index = inj_pathID.toInt();
        ui->CB_ing_path->addItem(name,index);
    }

    QString ptr = "select * from radionuclide where nuclide_id = " + nuclideID;
    query.exec(ptr);
    while(query.next()) {
        QString nucl_name = query.value("nuclide_name").toString();
        int idx  = nuclideID.toInt();
        ui->CB_radioNuclide->addItem(nucl_name,idx);
    }

    QString mod = "select * from modality where id_modality = " + QString::number(modID);
    qm.exec(mod);
    if(qm.next()){
        QString m_name = qm.value("mod_name").toString();
        ui->LE_mod->setText(m_name);
    }


    //Hide these info since they are not needed
    ui->LE_mod->hide();
    ui->label->hide();

    if ( !from_load || bFromLastStudy ){
        if ( !fileDirectory.isEmpty() )
            directFileLoader( fileDirectory );

        from_load = false;
        bFromLastStudy = false;
    }
}

void PostProcessing::clearAll()
{
    central_Plot->clearROIS();
    central_Plot->detachItems(QwtPlotItem::Rtti_PlotShape, true);
    central_Plot->detachItems(QwtPlotItem::Rtti_PlotMarker,true);
    central_Plot->mPlotItemsList.clear();
    central_Plot->mItemLabels.clear();

    for(int i=1;i<central_Plot->mPlotItemsList.count();i++)
        delete  central_Plot->mPlotItemsList.takeAt(i);

    central_Plot->mPlotItemsList.clear();
    central_Plot->savedItems=0;
    central_Plot->savedLabels=0;

    for(int i=0;i<ui->ROI_list->count();i++)
        delete  ui->ROI_list->takeItem(i);

    ui->ROI_list->clear();

    multi_measure();
}

void PostProcessing::memory_dealloc()
{
    for(int s=0; s < m_iImageNum; s++){
        for(int i=0; i<row[s]; i++)
            delete [] m_qrImage[s][i];
        delete [] m_qrImage[s];
    }
    delete cM;
    delete cM2;
    delete central_Plot;
    delete graphs;
}

void PostProcessing::combobox_currentIndexChanged(int val)
{
    if(val!=2){
        cM->BlackBased(val);
        cM2->BlackBased(val);
    }
    else{
        cM->BlueBased(val);
        cM2->BlueBased(val);
    }

    QwtInterval zInterval=central_Plot->spectrogram1->data()->interval(Qt::ZAxis);
    central_Plot->rightAxis->setColorMap(zInterval,cM2);
    central_Plot->spectrogram1->setColorMap(cM);
    central_Plot->replot();
}

void PostProcessing::ShowContextMenu(const QPoint & pos)
{
    QPoint globalPos = ui->pb_rectROI->mapToGlobal(pos);
    QMenu myMenu;
    myMenu.addAction("Rounded Rectangle");

    // ...

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        ui->pb_rectROI->setText("Round RectROI");
        central_Plot->sVal = RoundedRect;
        ui->pb_rectROI->click();
    }
    else{
        ; // nothing was chosen
    }
}

void PostProcessing::ShowContextMenu2(const QPoint & pos)
{
    QPoint globalPos = ui->pb_ellipseROI->mapToGlobal( pos );
    QMenu menu;
    menu.addAction("Angled EllipseROI");
    // ...

    QAction* selectedItem = menu.exec(globalPos);
    if (selectedItem){
        ui->pb_ellipseROI->setText("Angled EllipseROI");
        central_Plot->sVal=AngledEllipse;
        ui->pb_ellipseROI->click();
    }
    else{
        // nothing was chosen
    }
}

void PostProcessing::on_pb_rectROI_clicked(bool checked)
{
    if(checked){
        if(ui->pb_ellipseROI->isChecked()){
            ui->pb_ellipseROI->setChecked(false);
            central_Plot->destruct_picker_machine(EllipseROI);
        }

        if(ui->pb_freeROI->isChecked()){
            ui->pb_freeROI->setChecked(false);
            central_Plot->destruct_picker_machine(FreeDrawROI);
        }
        central_Plot->construct_picker_machine(RectROI);
    }
}

void PostProcessing::on_pb_ellipseROI_clicked(bool checked)
{
    if(checked){
        if(ui->pb_rectROI->isChecked()){
            ui->pb_rectROI->setChecked(false);
            central_Plot->destruct_picker_machine(RectROI);
        }

        if(ui->pb_freeROI->isChecked()){
            ui->pb_freeROI->setChecked(false);
            central_Plot->destruct_picker_machine(FreeDrawROI);
        }

        central_Plot->construct_picker_machine(EllipseROI);
    }
}

void PostProcessing::on_pb_freeROI_clicked(bool checked)
{
    if(checked){
        if(ui->pb_rectROI->isChecked()){
            ui->pb_rectROI->setChecked(false);
            central_Plot->destruct_picker_machine(RectROI);
        }

        if(ui->pb_ellipseROI->isChecked()){
            ui->pb_ellipseROI->setChecked(false);
            central_Plot->destruct_picker_machine(EllipseROI);
        }

        central_Plot->construct_picker_machine(FreeDrawROI);
    }
}

void PostProcessing::sliderValueChanged( int )
{
    int val = ui->horizontalSlider_contrast->value();
    val = 100 - val;
    contrastMax = static_cast<double>(val)/static_cast<double>(100);

    double con_percentage = (m_imgMax-m_imgMin) * contrastMax;
    m_tempMax = m_imgMax- con_percentage;

    if ( m_tempMax - m_tempMin > 0.0  && m_maxBool == false) {
        ui->sB_max->setValue(m_tempMax);
    }
}

void PostProcessing::ms_sliderValueChangedMin( int ){

    int val = ui->horizontalSlider_contrast_min->value();
    contrastMin = static_cast<double>(val)/static_cast<double>(100);
    double con_percentage = (m_imgMax-m_imgMin)*contrastMin;
    m_tempMin = m_imgMin + con_percentage;

    if ( m_tempMax - m_tempMin > 0  && m_minBool == false){
        ui->sB_min->setValue(m_tempMin);
    }


}

void PostProcessing::sB_max_changed(double maxRange){

    int item = m_iCurrentImage;
    Mat matIn( row[item], col[item], CV_64F);
    double InputImage[ row[item]*col[item] ];

    QVector< qreal > corVMatrix1; //<== This matrix is what is shown after the  contrast is adjusted //NIKOS
    QVector<double> tempInputImg = central_Plot->corMatrix1->valueMatrix();

    for (int i =0; i < tempInputImg.size(); i++)
        InputImage[ i ] = tempInputImg[ i ];

     memcpy( matIn.data, InputImage, static_cast<ulong>(row[item]*col[item]) * sizeof(InputImage[0]) );


    for (int m=0; m<row[item]; m++){
         for(int j=0;j<col[item];j++){
            corVMatrix1.append(matIn.at<double>(m,j));
        }
    }

    central_Plot->corMatrix1->setInterval( Qt::XAxis, QwtInterval( 0,col[item]));
    central_Plot->corMatrix1->setInterval( Qt::YAxis, QwtInterval( 0,row[item]));
    central_Plot->plotLayout()->setAlignCanvasToScales(true);
    central_Plot->setAxisScale( QwtPlot::xBottom, 0.0,col[item],0 );
    central_Plot->setAxisScale( QwtPlot::yLeft,row[item],0.0,0 );
    central_Plot->corMatrix1->setValueMatrix( corVMatrix1, col[item] );


    double minMValue= ui->sB_min->value();
    double maxMValue= maxRange;

    double contrast = m_imgMax - maxMValue;
    double diff=m_imgMax-m_imgMin;
    double percentage = 100 - (contrast/diff)*100;
    //double percentage = 100 - contrastMax*100;

    m_maxBool=true;
    ui->horizontalSlider_contrast->setValue(percentage);

    m_maxBool=false;

    central_Plot->corMatrix1->setInterval( Qt::ZAxis, QwtInterval( minMValue, maxMValue ) );
    central_Plot->rightAxis->setColorMap(QwtInterval(  minMValue,maxMValue ),cM2);
    central_Plot->setAxisScale(QwtPlot::yRight, minMValue, maxMValue );

    central_Plot->spectrogram1->setData(central_Plot->corMatrix1);
    central_Plot->spectrogram1->setColorMap(cM);
    central_Plot->replot();

    corVMatrix1.clear();
}

void PostProcessing::sB_min_changed(double minRange){
    int item = m_iCurrentImage;
    Mat matIn( row[item], col[item], CV_64F);
    double InputImage[ row[item]*col[item] ];

    QVector< qreal > corVMatrix1; //<== This matrix is what is shown after the  contrast is adjusted //NIKOS
    QVector<double> tempInputImg = central_Plot->corMatrix1->valueMatrix();

    for (int i =0; i < tempInputImg.size(); i++)
        InputImage[ i ] = tempInputImg[ i ];

    memcpy( matIn.data, InputImage, static_cast<ulong>(row[item]*col[item]) * sizeof(InputImage[0]) );



    for (int m=0; m<row[item]; m++){
         for(int j=0;j<col[item];j++){
            corVMatrix1.append(matIn.at<double>(m,j));
        }
    }

    central_Plot->corMatrix1->setInterval( Qt::XAxis, QwtInterval( 0,col[item]));
    central_Plot->corMatrix1->setInterval( Qt::YAxis, QwtInterval( 0,row[item]));
    central_Plot->plotLayout()->setAlignCanvasToScales(true);
    central_Plot->setAxisScale( QwtPlot::xBottom, 0.0,col[item],0 );
    central_Plot->setAxisScale( QwtPlot::yLeft,row[item],0.0,0 );
    central_Plot->corMatrix1->setValueMatrix( corVMatrix1, col[item] );

    double minMValue = minRange;
    double maxMValue = ui->sB_max->value();

    double contrast = minMValue-m_imgMin ;
    double diff=m_imgMax-m_imgMin;
    double percentage = (contrast/diff)*100;
    //double percentage = contrastMin*100;

    m_minBool=true;
    ui->horizontalSlider_contrast_min->setValue(percentage);

    m_minBool=false;



    central_Plot->corMatrix1->setInterval( Qt::ZAxis, QwtInterval( minMValue, maxMValue ) );
    central_Plot->rightAxis->setColorMap(QwtInterval(  minMValue,maxMValue ),cM2);
    central_Plot->setAxisScale(QwtPlot::yRight, minMValue, maxMValue );

    central_Plot->spectrogram1->setData(central_Plot->corMatrix1);
    central_Plot->spectrogram1->setColorMap(cM);

    central_Plot->replot();
}

void PostProcessing::ImageSlider(int item)
{

    mutex.lock();
    m_iCurrentImage = item;


    double tempSum=0;
    for(int i=0; i < item +1; i++){
        tempSum+=framesList[i];
    }
    double dTimeFrame = tempSum;

    if ( item < m_iImageNum - 1)
        ui->cB_selection->setText( "frame " + QString::number( item + 1 ) + " (t = " + QString::number( dTimeFrame ) + " " + "min)"  );
    else
        ui->cB_selection->setText( "Summed frame" );

    ui->cB_selection->setChecked(false);
    if ( selectedSlices.contains( m_iCurrentImage ) )
        ui->cB_selection->setChecked(true);


    QVector< qreal > corVMatrix1; //<== This matrix is what is shown after the  contrast is adjusted //NIKOS

    Mat matIn( row[item], col[item], CV_64F);
    double InputImage[ row[item]*col[ item ] ];

    for ( int m=0; m < row[item]; m++)
        for( int j=0; j < col[item]; j++)
            InputImage[m*col[item]+j] = m_qrImage[item][m][j];

    memcpy( matIn.data, InputImage, static_cast<ulong>( row[item] * col[item]) * sizeof(InputImage[0]) );

    double imgMin, imgMax;
    cv::minMaxLoc(matIn,&imgMin,&imgMax,NULL,NULL);

    for (int m=0; m<row[item]; m++){
        for(int j=0;j<col[item];j++){

            corVMatrix1.append(matIn.at<double>(m,j));
         }
    }

    m_imgMin=imgMin;
    m_imgMax=imgMax;
    ui->sB_min->setRange(m_imgMin,m_imgMax);
    ui->sB_max->setRange(m_imgMin,m_imgMax);


    central_Plot->corMatrix1->setInterval( Qt::XAxis, QwtInterval( 0,col[item]));
    central_Plot->corMatrix1->setInterval( Qt::YAxis, QwtInterval( 0,row[item]));

    central_Plot->plotLayout()->setAlignCanvasToScales(true);
    central_Plot->setAxisScale( QwtPlot::xBottom, 0.0,col[item],0 );
    central_Plot->setAxisScale( QwtPlot::yLeft,row[item],0.0,0 );
    central_Plot->corMatrix1->setValueMatrix( corVMatrix1, col[item] );


    double percentMin= (imgMax-imgMin)*contrastMin;
    imgMin+=percentMin;
    double percentMax= (imgMax-imgMin)*contrastMax;
    imgMax-=percentMax;




    central_Plot->corMatrix1->setInterval( Qt::ZAxis, QwtInterval(imgMin, imgMax) );

    central_Plot->rightAxis->setColorMap(QwtInterval(  imgMin,imgMax ),cM2);
    central_Plot->setAxisScale(QwtPlot::yRight, imgMin, imgMax );

    central_Plot->spectrogram1->setData(central_Plot->corMatrix1);
    central_Plot->spectrogram1->setColorMap(cM);
    central_Plot->spectrogram1->attach(central_Plot);
    central_Plot->replot();
    m_qvrCorMatrix = corVMatrix1;
    corVMatrix1.clear();

    ui->horizontalSlider_contrast->setValue(100-contrastMax*100);
    ui->horizontalSlider_contrast_min->setValue(contrastMin*100);
//    ui->sB_min->setValue(imgMin);
//    ui->sB_max->setValue(imgMax);

    if(ui->cB_fusion->isChecked()){
        addOpticalBackground();
    }else if (ui->cB_xray->isChecked()) {
        addXrayBackground();
    }

    mutex.unlock();
}

void PostProcessing::directFileLoader( QString directory )
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    if ( buttonSender )
        if ( buttonSender->text() == "Cancel") return;

    QStringList filter,pngFilter;
    filter<<"*.txt";
    pngFilter << "*.png";

    POST_PROC_path = directory;
    qDebug() << POST_PROC_path << endl;

    if ( POST_PROC_path.contains("CORRECTED")){
        POST_PROC_path.remove("/IMAGES/CORRECTED");
        POST_PROC_path.append("/POST_PROCESSING");
    }
    else if ( POST_PROC_path.contains("FINAL") ){
        POST_PROC_path.remove("/IMAGES/FINAL");
        POST_PROC_path.append("/POST_PROCESSING");
    }

    QDir dir( directory );


    QString copyForFusion = directory;
    QString copyForXray = directory;

    copyForFusion.append("/FUSION");
    copyForXray.append("/XRAY");

    QDir fusionDir(copyForFusion);
    QDir xrayDir(copyForXray);

    fusionDir.setNameFilters(pngFilter);
    xrayDir.setNameFilters(pngFilter);

    //Check from here --> //NIKOS
    QString copyForFusionDeconv = directory;
    copyForFusionDeconv.append("/FUSION");
    QDir fusionDeconvDir(copyForFusion);
    fusionDeconvDir.setNameFilters(pngFilter);
    //<-- to here


    QStringList images = dir.entryList(filter, QDir::Files );

    m_iImageNum = images.size();

    float mean=0,stdev=0;
    int item = 0;
    m_iCurrentImage=0;


    if( m_iImageNum != 0 && directory != ""){
        reference_img_area_counts = new float[m_iImageNum];
        copy_ref_counts = new float[m_iImageNum];
        ui->horizontalScrollBar_2->setRange(0,m_iImageNum-1);
        ui->horizontalScrollBar_2->setEnabled(true);
        m_qrImage = new  qreal**[m_iImageNum];

        selectedSlices.reserve(m_iImageNum);

        row= new int[m_iImageNum];
        col= new int[m_iImageNum];
        foreach(QString FileName, images){
            QString cp = directory;
            cp.append("/");
            QByteArray byteArray;
            QFile File(cp.append(FileName));

            //  File.open(QFile::ReadOnly);
            QTextStream textStream(&byteArray,QIODevice::ReadOnly);
            if( File.exists() && File.open( QIODevice::ReadOnly ) ){
                byteArray= File.readAll();
                File.close();
                //return 0;
            }
            else{
#ifdef QT_DEBUG
                qDebug("Failed to open file for reading.");
                break;
#endif
            }

            int row_num=0,col_num=0,cnt=0;
            QString line;
            QStringList fields;
            QStringList list_item;
            QLocale c (QLocale::C);
            bool ok;

            while( !textStream.atEnd() ){
                line = textStream.readLine();
                fields = line.split(" ");

                col_num = fields.size();
                for(int i =0; i< col_num;i++)
                    list_item.append(fields.at(i));

                row_num++;
            }

            col[item] = col_num;
            row[item] = row_num;

            m_qrImage[item] = new  qreal*[row_num];
            for(int i=0;i<row_num;i++)
                m_qrImage[item][i] = new qreal[col_num];

            for(int i=0;i<row_num;i++){
                for(int j=0;j<col_num;j++){
                    m_qrImage[item][i][j] = c.toDouble(list_item.at(cnt),&ok);
                    cnt++;
                }
            }

            std::tie(mean,stdev,reference_img_area_counts[item]) = ROI_statistics(QRectF(0,0,col_num,row_num),item);
            copy_ref_counts[item] =  reference_img_area_counts[item];
            item++;
        }

        //Always load image unfussed
        ui->cB_fusion->setChecked( false );
        ui->cB_xray->setChecked( false );

        for(int i=0;i<m_iImageNum;i++){
            if(fastDynamic){
                if( i<6){
                    framesList.append(10.0/60.0);
                }
                else if(i>=6 && i<14){
                    framesList.append(30.0/60.0);
                }
                else if(i>=14 && i<19){
                    framesList.append(60.0/60.0);
                }
                else if(i>=19 && i<45){
                    framesList.append(120.0/60.0);
                }
            }else {
                framesList.append(frame_duration);
            }
            ImageSlider( i );
        }
        ui->horizontalSlider_contrast->setEnabled(true);
        ui->horizontalSlider_contrast_min->setEnabled( true );
        ImageSlider(0);

        mf_loadOpticalImage();
    }
}

void PostProcessing::addROItoList()
{
    QListWidgetItem *list_roi;
    if(!central_Plot->mPlotItemsList.empty()){
        if(central_Plot->currItem != nullptr){
            int num = central_Plot->savedItems;
            QString str = QString::number(num)+"."+"roi_"+QString::number(num);
            if(ui->ROI_list->count()!=0){
                if(numList!=num){
                    list_roi = new QListWidgetItem(str);
                    list_roi->setData(Qt::UserRole,num);

                    ui->ROI_list->addItem(list_roi);
                    numList++;
                }
            }
            else{
                list_roi = new QListWidgetItem(str);
                list_roi->setData(Qt::UserRole,num);

                ui->ROI_list->addItem(list_roi);
                numList++;
            }
        }


        if ( ui->ROI_list->count() != 0){
            ui->PB_plot_excel->setEnabled(true);
            ui->PB_pdfReport->setEnabled(true);
        }
        else{
            ui->PB_plot_excel->setEnabled(false);
            ui->PB_pdfReport->setEnabled(false);
        }
    }

    ui->PB_updatePos->setEnabled(true);
    multi_measure();
}

void PostProcessing::on_PB_ShowLabels_toggled(bool checked)
{
    if(checked){
        for(int i=0;i<central_Plot->mItemLabels.count();i++)
            central_Plot->mItemLabels.at(i)->attach(central_Plot);
        central_Plot->replot();
    }
    else{
        for(int i=0;i<central_Plot->mItemLabels.count();i++)
            central_Plot->mItemLabels.at(i)->detach();
        central_Plot->replot();

    }
}

void PostProcessing::on_PB_showRois_clicked(bool checked)
{
    if(checked){
        central_Plot->detachItems(QwtPlotItem::Rtti_PlotShape,false);
        central_Plot->detachItems(QwtPlotItem::Rtti_PlotMarker,false);
        central_Plot->replot();
    }
    else{
        central_Plot->detachItems(QwtPlotItem::Rtti_PlotMarker,false);

        for(int j=0;j<central_Plot->mPlotItemsList.count();j++)
            central_Plot->mPlotItemsList.at(j)->attach(central_Plot);

        central_Plot->replot();
    }
}

void PostProcessing::on_ROI_list_itemClicked(QListWidgetItem *item)
{
    bool ok = true;

    itemIndex = item->data(Qt::UserRole).toInt(&ok)-1;
    if(itemIndex !=-1)
    {
        central_Plot->clearROIS();
        if(!central_Plot->itemList().contains(central_Plot->mPlotItemsList.at(itemIndex)))
        {
            central_Plot->mPlotItemsList.at(itemIndex)->attach(central_Plot);
            central_Plot->replot();

        }
        central_Plot->mItemLabels.at(itemIndex)->setValue(central_Plot->mPlotItemsList.at(itemIndex)->boundingRect().center());
        central_Plot->mItemLabels.at(itemIndex)->attach(central_Plot);
        central_Plot->replot();
    }

    central_Plot->moveSelection=true;
    ui->PB_updatePos->setEnabled(true);
    ui->PB_deleteRoi->setEnabled(true);
    if(ui->ROI_list->count() != 0)
        ui->PB_renameRoi->setEnabled(true);
    ui->PB_refArea->setEnabled(true);
}

void PostProcessing::delete_roi()
{
    int i=0;
    int index = -1;
    QList<QListWidgetItem*> selectedItems = ui->ROI_list->selectedItems();

    if(!selectedItems.isEmpty()){
        QListWidgetItem* item = selectedItems.at(0);
        index = item->data(Qt::UserRole).toInt()-1;
        int foo = central_Plot->mPlotItemsList.count();

        if ( itemIndex==index && item->text() != "Reference Area"){
            for ( i=0; i<foo; i++ ){
                if ( i == itemIndex ){
                    central_Plot->mPlotItemsList.at(i)->detach();
                    delete central_Plot->mPlotItemsList.takeAt(i);

                    delete central_Plot->mItemLabels.takeAt(i);
                    central_Plot->savedItems--;

                    delete ui->ROI_list->takeItem(itemIndex);

                    for(int k=0;k<ui->ROI_list->count();k++){
                        QString prev_data = ui->ROI_list->item(k)->data(Qt::UserRole).toString();
                        ui->ROI_list->item(k)->setData(Qt::UserRole,k+1);
                        QString curr_data = ui->ROI_list->item(k)->data(Qt::UserRole).toString();
                        QString whole_name = ui->ROI_list->item(k)->text();
                        whole_name.replace(prev_data,curr_data);
                        central_Plot->labelText.setText(QString::number(k+1));
                        if((central_Plot->mItemLabels.at(k)!=nullptr) && (k<central_Plot->mItemLabels.count()))
                            central_Plot->mItemLabels.at(k)->setLabel(central_Plot->labelText);

                        ui->ROI_list->item(k)->setText(whole_name);
                        ui->ROI_list->item(k)->setSelected(false);
                    }

                    if(ui->ROI_list->count()==0){
                        ui->PB_showRois->setChecked(false);
                        ui->PB_renameRoi->setEnabled(false);
                    }
                }
            }

            multi_measure();
            central_Plot->replot();
            ui->PB_deleteRoi->setEnabled(false);

            if ( ui->ROI_list->count() != 0){
                ui->PB_plot_excel->setEnabled(true);
                ui->PB_pdfReport->setEnabled(true);
            }
            else{
                ui->PB_plot_excel->setEnabled(false);
                ui->PB_pdfReport->setEnabled(false);
            }

        }
        else
            QMessageBox::information(this, "info","Cannot delete Reference Area ROI please select another ROI from the list or reset reference area to default.");

    }
}

void PostProcessing::on_ROI_list_itemDoubleClicked(QListWidgetItem *item)
{
    item->setFlags (item->flags() | Qt::ItemIsEditable);
}

void PostProcessing::on_PB_renameRoi_pressed()
{
    if(ui->ROI_list->count()!=0){
        QListWidgetItem *item = ui->ROI_list->currentItem();
        QString curr_data = ui->ROI_list->currentItem()->data(Qt::UserRole).toString();

        bool ok;
        QLabel *textLabel;

        int frameStyle = QFrame::Sunken | QFrame::Panel;
        textLabel = new QLabel;
        textLabel->setFrameStyle(frameStyle);

        QString text = QInputDialog::getText(this, tr("Rename ROI as :"),
                                             tr("Name :"), QLineEdit::Normal,
                                             item->text(), &ok);

        if (ok && !text.isEmpty())
            textLabel->setText(text);
        else
            textLabel->setText(item->text());

        item->setText(curr_data+"."+textLabel->text());
        ui->PB_renameRoi->setEnabled(false);
    }
}

void PostProcessing::OnItemsCommitData(QWidget *pLineEdit)
{
    QString new_name = reinterpret_cast<QLineEdit*>(pLineEdit)->text();
    QString data = ui->ROI_list->currentItem()->data(Qt::UserRole).toString();

    if(new_name.contains(data+"."))
        ui->ROI_list->currentItem()->setText(new_name);
    else if(new_name.contains(data)&&!new_name.contains("."))
    {
        new_name.remove(data);
        ui->ROI_list->currentItem()->setText(data+"."+new_name);
    }
    else if(new_name.contains(".")&&!(new_name.contains(data)))
    {
        new_name.remove(".");
        ui->ROI_list->currentItem()->setText(data+"."+new_name);
    }
    else
        ui->ROI_list->currentItem()->setText(data+"."+new_name);
}

std::tuple<float, float, float> PostProcessing::ROI_statistics(QPolygonF poly , int image)
{
    vector<Point > points;
    int32_t x,y;
    int32_t InputImage[row[image]*col[image]];
    float mean=0 , stdev=0 , total_counts=0;

    for (int m=0; m<poly.count(); m++){
        x = static_cast<int32_t>(poly.at(m).x());
        y = static_cast<int32_t>(poly.at(m).y());
        points.push_back(Point(x, y));
    }

    for (int m=0; m<row[image]; m++)
        for(int j=0;j<col[image];j++)
            InputImage[m*col[image]+j] = static_cast<int32_t>(m_qrImage[image][m][j]);

    Mat inputImageMat(row[image], col[image], CV_32S);
    memcpy(inputImageMat.data, InputImage, row[image] * col[image] * sizeof(InputImage[0]));


    bioemtec::roiManager::roiStatistics(inputImageMat,points,mean,stdev,total_counts, m_bIsBeta );


#ifdef QT_DEBUG
    cout << "mean=" << mean << endl;
    cout << "std=" << stdev << endl;
    cout << "total counts=" << total_counts << endl;
#endif

    return std::make_tuple(mean,stdev,total_counts);
}


std::tuple<float,float,float> PostProcessing::ROI_statistics(QRectF rectM, int image)
{
    QRectF rect = rectM; //ROI bounding rectangle
    int32_t InputImage[row[image]*col[image]];
    float mean=0, stdev=0, total_counts=0; //stats

    //// load current frame to array from which we construct the input Mat
    for (int m=0; m<row[image]; m++)
        for(int j=0;j<col[image];j++)
            InputImage[m*col[image]+j] = static_cast<int32_t>(m_qrImage[image][m][j]);

    Mat inputImageMat(row[image], col[image], CV_32S); //Mat construction


    /// fill input Mat with image data
    memcpy(inputImageMat.data, InputImage, row[image] * col[image] * sizeof(InputImage[0]));
    //double min,max;

    /////// Get ROI'S rectangle up and bottom corners////

    qreal upperLeftX =rect.topLeft().y(), upperLeftY = rect.topLeft().x(), lowerRightX = rect.bottomRight().y(), lowerRightY = rect.bottomRight().x();

    int upLx = static_cast<int>(upperLeftX);
    int upLy = static_cast<int>(upperLeftY);
    int botRx = static_cast<int>(lowerRightX);
    int botRy = static_cast<int>(lowerRightY);

    Point upperLeft = Point(upLy, upLx);
    Point lowerRight = Point(botRy, botRx);

    /////////////////////////////////////////////////////

    bioemtec::roiType rt = bioemtec::RECTANGLE;  //set ROI selection type to rect
    bioemtec::roiManager::roiStatistics(inputImageMat,upperLeft,lowerRight,mean,stdev,total_counts, rt, m_bIsBeta); // compute statistics for the specified ROI on the image



    /////////////////////////////////////////

#ifdef QT_DEBUG
    cout << "mean=" << mean << endl;
    cout << "std=" << stdev << endl;
    cout << "total counts=" << total_counts << endl;
#endif

    return std::make_tuple(mean,stdev,total_counts);
}

void PostProcessing::on_PB_measure_pressed()
{
    ///differenciate between RECT ROI item and FreeDraw ROI item and call the corrected overloaded measure function
    QPolygonF p ;//= central_Plot->poly_stat;
    int index = -1;
    int img;
    float mean=0,stdev=0,counts=0;
    //ROI list is enabled to have only one item as a selection. In the selection list we have the selected item from the list.
    QList<QListWidgetItem*> selItems = ui->ROI_list->selectedItems();


    if(!selItems.isEmpty()) {
        index = selItems.at(0)->data(Qt::UserRole).toInt()-1;
        if(index!=-1) {
            // rois added to plot have a title repsecting their shape when added to plot. Grab this title and measure respecting the area shape.
            QwtPlotItem * item = central_Plot->mPlotItemsList.at(index);
            QString roi_type= item->title().text();
            if(roi_type=="free") {
                QwtPlotShapeItem *it =  static_cast<QwtPlotShapeItem*>(central_Plot->mPlotItemsList.at(index));
                p = it->shape().toFillPolygon(); //points polygon
                img = ui->horizontalScrollBar_2->value();

                std::tie(mean,stdev,counts)=ROI_statistics(p,img);

            }
            else{
                QRectF rectM = central_Plot->mPlotItemsList.at(index)->boundingRect(); //roi's bounding rect
                img = ui->horizontalScrollBar_2->value();

                std::tie(mean,stdev,counts)=ROI_statistics(rectM,img);
            }

            counter++;

            //// Show each measurment to a pop up table, that increments a row every time the function is called, collumns are fixed
            measurement_table->setRowCount(counter);

            // add measurements stat items to the table
            QTableWidgetItem *it0 =  new QTableWidgetItem();/// row count
            QTableWidgetItem *it1 =  new QTableWidgetItem();// mean
            QTableWidgetItem *it2 =  new QTableWidgetItem();// std
            QTableWidgetItem *it3 =  new QTableWidgetItem();// total counts

            it0->setData(counter-1,counter);// set incremental row
            it0->setText(ui->ROI_list->currentItem()->text() );/// row value

            it1->setData(1,mean); // mean value
            it1->setText(it1->data(1).toString());

            it2->setData(2,stdev);// std value
            it2->setText(it2->data(2).toString());

            it3->setData(3,counts);// tot counts value
            it3->setText(it3->data(3).toString());

            measurement_table->setItem(counter-1, 0, it0);
            measurement_table->setItem(counter-1, 1, it1);
            measurement_table->setItem(counter-1, 2, it2);
            measurement_table->setItem(counter-1, 3, it3);

            ///show first time and then just add the table's new contents
            if(!diaTable->isVisible()) {
                measurement_table->setHorizontalHeaderLabels(tableHeader);
                diaTable->show();
                ui->ROI_list->currentItem()->setSelected(false);
                ui->ROI_list->clearSelection();
            }
        }
    }
    else
        QMessageBox::information(this, "info","Please select a ROI from the list first to measure.");
}


void PostProcessing::writeImage(Mat outputImage, string outputFileName) {
    FILE * this_file;
    this_file = fopen(outputFileName.c_str(), "w+");
    rewind(this_file);

    if (this_file != NULL) {
        cout << "Output file " << outputFileName << " successfully saved" << endl;

        for (int i = 0; i < outputImage.rows; i++) {
            for (int j = 0; j < outputImage.cols; j++) {
                fprintf(this_file, "%f ", outputImage.at<float> (i, j));
            }
            fprintf(this_file, "\n");
        }
    }
    else {
        std::cerr << "Error opening output file" << endl;
        exit(0);
    }
    fclose(this_file);
}

void PostProcessing::plotROIS()
{
    multi_measure();
}

float PostProcessing::set_reference_area()
{

    if ( ui->ROI_list->count() != 0 ){
        QPolygonF p;
        int indx = -1;
        int img;
        float mean,stdev;
        QList<QListWidgetItem*> selItems = ui->ROI_list->selectedItems();//can only have one item because the selection policy in the list is one item.

        if( !selItems.isEmpty() ){
            indx = selItems.at(0)->data(Qt::UserRole).toInt()-1;

            if( indx != -1 ) {
                initRefItem = new QListWidgetItem();
                initRefItem =  ui->ROI_list->currentItem();
                initName = initRefItem->text();
                initRefItem->setText("Reference Area");
                QwtPlotItem* item = central_Plot->mPlotItemsList.at(indx);
                QString roi_type = item->title().text();

                if(roi_type=="free"){
                    QwtPlotShapeItem *it =  static_cast<QwtPlotShapeItem*>(central_Plot->mPlotItemsList.at(indx));
                    p = it->shape().toFillPolygon(); //points polygon
                    img = ui->horizontalScrollBar_2->value();
                    std::tie(mean,stdev,reference_img_area_counts[m_iCurrentImage]) =  ROI_statistics(p,img);
                }
                else {
                    QRectF rectM = central_Plot->mPlotItemsList.at(indx)->boundingRect(); //roi's bounding rect
                    img = ui->horizontalScrollBar_2->value();
                    std::tie(mean,stdev,reference_img_area_counts[m_iCurrentImage]) =  ROI_statistics(rectM,img);
                }

                ui->ROI_list->clearSelection();
            }
        }
        else{
            img = ui->horizontalScrollBar_2->value();
            std::tie(mean,stdev,reference_img_area_counts[m_iCurrentImage]) = ROI_statistics(QRectF(central_Plot->canvas()->geometry()),img);

            if(ui->ROI_list->row(initRefItem) < ui->ROI_list->count()){ //NIKOS: Crash here
                int count = ui->ROI_list->row(initRefItem) + 1;
                initRefItem->setText(QString::number(count)+".roi_"+QString::number(count));
            }
            else{
                int count = ui->ROI_list->count()+1;
                initRefItem->setText(QString::number(count)+".roi_"+QString::number(count));
            }

            ui->PB_refArea->setEnabled(false);
        }

        //Enable/Disable storing in Excel since saving the data with reference area is a mess...
        if( ui->ROI_list->findItems("Reference Area", Qt::MatchExactly).isEmpty())
            ui->PB_plot_excel->setEnabled(true);
        else
            ui->PB_plot_excel->setEnabled(false);

    }

    multi_measure();
}

void PostProcessing::multi_measure()
{
    mean_table.clear();
    std_table.clear();
    totCounts_table.clear();
    plot_values.clear();
    energy_values.clear();

    graphs->detachItems(QwtPlotItem::Rtti_PlotItem,true);
    graphs->detachItems(QwtPlotItem::Legend,true);

    float meanVal=0,stdev=0,counts=0,c=0;
    float max=0.0;
    //graphs->clearROIS();


    double golden_ratio = 0.618033988749895;
    double h;
    int index = -1;

    for(int i=0;i<ui->ROI_list->count();i++){
        QPolygonF points;
        for(int j=0;j < (m_iImageNum-1); j++){ //NIKOS: -1 Since the last one is the cumulative and we do not want to plot it

            QPolygonF p ;//= central_Plot->poly_stat;

            index = ui->ROI_list->item(i)->data(Qt::UserRole).toInt()-1;
            if(ui->ROI_list->item(i)->text() != "Reference Area" && index!=-1) {
                QwtPlotItem* item = central_Plot->mPlotItemsList.at(index);
                QString type = item->title().text();

                if(type=="free") {
                    QwtPlotShapeItem *it =  static_cast<QwtPlotShapeItem*>(central_Plot->mPlotItemsList.at(index));
                    p = it->shape().toFillPolygon(); //points polygon
                    //mean_table.append(ROI_statistics(p,j)/reference_img_area_counts);
                    //float ref = reference_img_area_counts[j];
                    std::tie(meanVal,stdev,c) = ROI_statistics(p,j);
                    counts = c;// / (ref)*100;

                    totCounts_table.append(c);
                    mean_table.append(meanVal);
                    std_table.append(stdev);
                    plot_values.append(counts);

                    energy_values.append( convertCountsToEnergy( counts/framesList[j] ) );

                    if ( ui->radioButtonCountsPerROI->isChecked() || m_isFirstPlotted ){
                        graphs->setYAxisTitle("Counts/min in ROIs");
                        if( counts/framesList[j] > max)
                             max = counts/framesList[j];
                        points << QPointF(static_cast<float>( (j*framesList[j])+framesList[j]), counts/framesList[j]);
                        m_isFirstPlotted = false;
                    }
                    else if ( ui->radioButtonAcivityPerROI->isChecked() ) { // We first plot the activity by dafault but for some reason it cannot take m_plotSelector->radioButtonEnergetic->isChecked()
                        graphs->setYAxisTitle("Activity [KBq]");
                        if ( convertCountsToEnergy( counts/framesList[j] ) > max)
                            max = convertCountsToEnergy( counts/framesList[j] );
                        points << QPointF(static_cast<float>( (j*framesList[j]) + framesList[j]), convertCountsToEnergy( counts/framesList[j] ) );
                    }
                }
                else {
                    QRectF rectM = central_Plot->mPlotItemsList.at(index)->boundingRect(); //roi's bounding rect
                    //float ref = reference_img_area_counts[j];

                    std::tie(meanVal,stdev,c) = ROI_statistics(rectM,j);
                    counts = c; // / (ref)*100;

                    totCounts_table.append(c);
                    mean_table.append(meanVal);
                    std_table.append(stdev);
                    plot_values.append(counts);
                    energy_values.append( convertCountsToEnergy( counts/framesList[j] ) );

                    if ( ui->radioButtonCountsPerROI->isChecked() || m_isFirstPlotted ){
                        graphs->setYAxisTitle("Counts/min in ROIs");
                        if( counts/framesList[j] > max)
                            max = counts/framesList[j];
                        points << QPointF(static_cast<float>( (j*framesList[j])+framesList[j]), counts/framesList[j]);
                        m_isFirstPlotted = false;
                    }
                    else if ( ui->radioButtonAcivityPerROI->isChecked() ) {
                        graphs->setYAxisTitle("Activity per ROI [KBq]");
                        if ( convertCountsToEnergy( counts/framesList[j] ) > max)
                            max = convertCountsToEnergy( counts/framesList[j] );
                        points << QPointF(static_cast<float>( (j*framesList[j]) + framesList[j]), convertCountsToEnergy( counts/framesList[j] ) );
                    }
                }
            }
        }

        ///////// curve dynamic coloring /////////
        h =  static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
        h += golden_ratio;
        h = std::fmod(h,1);
        color_generator(h,0.99,0.99);
        QColor color(red,green,blue);
        ////////// scale to max value and add grid ////////
        QwtPlotGrid *grid = new QwtPlotGrid();
        grid->setXAxis(QwtPlot::xBottom);
        grid->setPen(QColor(Qt::lightGray));

        graphs->setAxisScale(QwtPlot::yLeft,0,(max+0.1*max),0); //Scale the y-axis
        if(fastDynamic){
            graphs->setAxisScale(QwtPlot::xBottom, -10, 60,10);
        }
        else{
            graphs->setAxisScale( QwtPlot::xBottom, -0.2, m_iImageNum*frame_duration, 0 ); //Scale the x-axis
        }
        graphs->plotLayout()->setAlignCanvasToScales(true);
        grid->attach(graphs);

        /// construct a new curve and attach it to the plot ///
        QwtPlotCurve *curveP = new QwtPlotCurve();
        curveP->setPen(color,1);
        curveP->setSamples(points);
        QwtSymbol *s;
        s = randomCurveSymbolGenerator();
        s->setColor(color);

        if ( ui->ROI_list->item(i)->text() != "Reference Area" ){
            curveP->setSymbol(s);
            curveP->setCurveAttribute(QwtPlotCurve::Fitted,true);
            curveP->setLegendAttribute(QwtPlotCurve::LegendShowSymbol);
            curveP->setTitle( ui->ROI_list->item(i)->text() );
        }
        else {
            curveP->setItemAttribute(QwtPlotItem::Legend, false );
        }

        curveP->attach( graphs );
        graphs->replot();
    }

    if ( ui->ROI_list->count() == 0 ){
        if ( graphs == nullptr )
            graphs = new GUI_Plot(this,false);

        QwtPlotGrid *grid = new QwtPlotGrid();
        grid->setXAxis(QwtPlot::xBottom);
        grid->setPen(QColor(Qt::lightGray));

        graphs->plotLayout()->setAlignCanvasToScales(true);
        grid->attach(graphs);
        ui->horizontalLayout_2->addWidget(graphs);
        graphs->replot();
    }
}

void PostProcessing::color_generator(double h,double s,double v) //conversion from HSV to RGB, generates RGB values
{
    int h_i;
    double f,p,q,t;
    double r,g,b;

    h_i = static_cast<int>(h*6);
    f = h*6 - h_i;
    p = v * (1 - s);
    q = v * (1 - f*s);
    t = v * (1 - (1 - f) * s);

    if( h_i == 0 ){
        r = v;
        g = t;
        b = p;
    }
    else if ( h_i == 1 ){
        r = q;
        g = v;
        b = p;
    }
    else if ( h_i==2 ){
        r = p;
        g = v;
        b = t;

    }
    else if( h_i == 3 ){
        r = p;
        g = q;
        b = v;
    }
    else if ( h_i == 4 ){
        r = t;
        g = p;
        b = v;
    }
    else if( h_i == 5 ){
        r = v;
        g = p;
        b = q;
    }

    red = static_cast<int>(r*256);
    green = static_cast<int>(g*256);
    blue = static_cast<int>(b*256);
}


QwtSymbol* PostProcessing::randomCurveSymbolGenerator()
{
    int randN = rand()%9;
    QwtSymbol *sym;
    sym = new QwtSymbol(QwtSymbol::NoSymbol);
    sym->setSize(5);
    switch (randN) {
    case 0:
        sym->setStyle(QwtSymbol::Ellipse);
        break;
    case 1:
        sym->setStyle(QwtSymbol::Rect);
        break;
    case 2:
        sym->setStyle(QwtSymbol::Diamond);
        break;
    case 3:
        sym->setStyle(QwtSymbol::Triangle);
        break;
    case 4:
        sym->setStyle(QwtSymbol::DTriangle);
        break;

    case 5:
        sym->setStyle(QwtSymbol::UTriangle);
        break;
    case 6:
        sym->setStyle(QwtSymbol::LTriangle);
        break;
    case 7:
        sym->setStyle(QwtSymbol::RTriangle);
        break;
    case 8:
        sym->setStyle(QwtSymbol::Cross);
        break;
    case 9:
        sym->setStyle(QwtSymbol::XCross);
        break;
    default:
        break;
    }
    return sym;
}

void PostProcessing::saveImageAs()
{
    QPixmap qPix;
    qPix = central_Plot->grab();

    if( qPix.isNull() )
        return;

    QString types(	"Portable Network Graphics file (*.png);;"
                    "Bitmap file (*.bmp)");

    QString filter;							// Type of filter
    QString pngExt=".png", bmpExt=".bmp";		// Suffix for the files
    QString suggestedName;
    QString report_images = POST_PROC_path;
    QString fn;

    if( !POST_PROC_path.contains("Report_Images") ){
        QDir dir;
        dir.mkdir(report_images.append("/Report_Images"));
    }

    suggestedName = report_images + "/frame";

    fn = QFileDialog::getSaveFileName(this,tr("Save Image"),
                                      suggestedName,types,&filter);

    if ( !fn.isEmpty() ) {						// If filename is not a null
        if (fn.contains(pngExt))
            fn.remove(pngExt);
        else if (fn.contains(bmpExt))
            fn.remove(bmpExt);

        if (filter.contains(pngExt)) {			// OR, Test to see if png and save
            fn+=pngExt;
            qPix.save( fn, "PNG" );
        }
        else if (filter.contains(bmpExt)) {			// OR, Test to see if bmp and save
            fn+=bmpExt;
            qPix.save( fn, "BMP" );
        }

        QMessageBox msgBox;
        msgBox.setText("Image saved in " + fn);
        msgBox.exec();
    }
}

void PostProcessing::saveImageAs(QString str)
{
    QPixmap qPix;
    qPix = central_Plot->grab();

    if(qPix.isNull())
        return;

    QString types("Portable Network Graphics file (*.png);;");
    QString filter;							// Type of filter
    QString pngExt=".png", bmpExt=".bmp";		// Suffix for the files
    QString suggestedName;
    QString report_images = POST_PROC_path;
    QString fn;

    if(!POST_PROC_path.contains("Report_Images")){
        QDir dir;
        dir.mkdir(report_images.append("/Report_Images"));
    }

    suggestedName = report_images + "/" + str;
    fn = suggestedName;

    if ( !fn.isEmpty() ) {						// If filename is not a null
        if (fn.contains( pngExt ) )
            fn.remove( pngExt );

        fn += pngExt;
        qPix.save( fn, "PNG" );
        if ( str == "summed" )//&&!(selectedNames.contains(fn)))
            selectedNames.append(fn);
    }

    QMessageBox msgBox;
    msgBox.setText("Image saved in " + fn);
    msgBox.exec();

}

void PostProcessing::saveAllFrames()
{

    QString types(	"Portable Network Graphics file (*.png);;"
                    "Bitmap file (*.bmp)");


    QString filter;							// Type of filter
    QString pngExt=".png", bmpExt=".bmp",dcmExt=".dcm";		// Suffix for the files
    QString suggestedName;
    QString report_images = POST_PROC_path;
    QString fn;

    if(!POST_PROC_path.contains("Report_Images")){
        QDir dir;
        dir.mkdir(report_images.append("/Report_Images"));
    }

    suggestedName=report_images+"/frame";
    fn = QFileDialog::getSaveFileName(this,tr("Save Image"),
                                      suggestedName, types, &filter);
    QString fn_copy = fn;
    QStringList list =  fn_copy.split("/");
    QString file;

    if(!fn.isEmpty()){
        int counter=1;
        //Loop over all frames
        for(int i=0; i<m_iImageNum; i++) {
            ImageSlider(i);

            QPixmap qPixmap;
            qPixmap = central_Plot->grab();

            if( qPixmap.isNull() )
                return;

            if ( !fn.isEmpty() ) {						// If filename is not a null
                if (fn.contains(pngExt))
                    fn.remove(pngExt);
                else if (fn.contains(bmpExt))
                    fn.remove(bmpExt);


                if ( filter.contains(pngExt) ) { 			// OR, Test to see if png and save
                    qPixmap.save( fn + QString::number( counter ) + pngExt, "PNG" );
                }
                else if (filter.contains(bmpExt) ) { 			// OR, Test to see if bmp and save
                    qPixmap.save( fn + QString::number( counter ) + bmpExt, "BMP" );
                }

            }
            counter++;
        }
        ImageSlider( m_iCurrentImage );

        int pos = fn.lastIndexOf(QChar('/'));
        QMessageBox msgBox;

        msgBox.setText("Frames saved." + fn.left(pos) );
        msgBox.exec();
    }
}

void PostProcessing::savePlotAsImage()
{
    QPixmap qPix;
    qPix = graphs->grab();

    if(qPix.isNull())
        return;

    QString types(	"Portable Network Graphics file (*.png)");

    QString filter;							// Type of filter
    QString pngExt=".png", bmpExt=".bmp";		// Suffix for the files

    QString suggestedName;
    QString report_images = POST_PROC_path;
    QString fn;
    QDir dir;

    if(!POST_PROC_path.contains("Plot"))
    {
        dir.mkdir(report_images.append("/Plot"));
    }
    else
        dir.mkdir(report_images.append("/Plot"));

    suggestedName=report_images + "/plot";
    fn = QFileDialog::getSaveFileName(this,tr("Save Image"),
                                      suggestedName,types,&filter);

    if ( !fn.isEmpty() ){
        if (fn.contains(pngExt)) {
            fn.remove(pngExt);
        }

        if (filter.contains(pngExt)) {
            fn+=pngExt;
            qPix.save( fn, "PNG" );
        }

        QMessageBox msgBox;
        msgBox.setText("Plot saved in " + fn);
        msgBox.exec();
    }
}


void PostProcessing::savePlotAsImage(QString p)
{
    QPixmap qPix;
    qPix = graphs->grab();

    if(qPix.isNull())
        return;

    QString types("Portable Network Graphics file (*.png)");
    QString filter;							// Type of filter
    QString pngExt=".png";		// Suffix for the files

    QString suggestedName;
    QString report_images = POST_PROC_path;
    QString fn;


    if(!POST_PROC_path.contains("Report_Images"))
    {
        QDir dir;
        dir.mkdir(report_images.append("/Report_Images"));
    }

    suggestedName=report_images+"/"+p;
    fn = suggestedName;

    if ( !fn.isEmpty() )
    {
        if (fn.contains(pngExt))
            fn.remove(pngExt);

        fn+=pngExt;
        qPix.save( fn, "PNG" );
        if(p=="Report_plot")//!selectedNames.contains(fn))
            selectedNames.append(fn);

        QMessageBox msgBox;
        msgBox.setText("Plot saved in " + fn);
        msgBox.exec();
    }
}

void PostProcessing::closeDialog(int)
{
    measurement_table->clear();
    int rows = measurement_table->rowCount();

    counter = counter-rows;
    ui->ROI_list->clearSelection();
}

void PostProcessing::on_PB_updatePos_pressed()
{
    if(!central_Plot->mPlotItemsList.empty() && central_Plot->mPlotItemsList.contains(central_Plot->initialItem)) {
        if(central_Plot->d_editedItem->title().text()=="rect") {
            central_Plot->initialItem->setRect(central_Plot->d_editedItem->boundingRect());
            central_Plot->initialItem->attach(central_Plot);

            if(central_Plot->currItemIndex<central_Plot->mItemLabels.count())
                central_Plot->mItemLabels.at(central_Plot->currItemIndex)->setValue(central_Plot->initialItem->boundingRect().center());
        }
        if(central_Plot->d_editedItem->title().text()=="ellipse"){
            central_Plot->initialItem->setShape(central_Plot->d_editedItem->shape());
            central_Plot->initialItem->attach(central_Plot);

            if(central_Plot->currItemIndex<central_Plot->mItemLabels.count())
                central_Plot->mItemLabels.at(central_Plot->currItemIndex)->setValue(central_Plot->initialItem->boundingRect().center());
        }

        if(central_Plot->d_editedItem->title().text()=="free"){
            central_Plot->initialItem->setShape(central_Plot->d_editedItem->shape());
            central_Plot->initialItem->attach(central_Plot);

            if(central_Plot->currItemIndex<central_Plot->mItemLabels.count())
                central_Plot->mItemLabels.at(central_Plot->currItemIndex)->setValue(central_Plot->initialItem->boundingRect().center());
        }

        central_Plot->d_editedItem->detach();
        central_Plot->replot();
    }
}

void PostProcessing::on_PB_plot_excel_pressed()
{
    //QDateTime date_time;
    QString Filepath;

    //// file dialog for the user to select name for the exported excel file

    QString report_plot = POST_PROC_path;
    QDir dir;

    if(!POST_PROC_path.contains("Plot")){
        dir.mkdir(report_plot.append("/Plot"));
    }
    else
        dir.mkdir(report_plot.append("/Plot"));
    report_plot.append("/data");

    Filepath = QFileDialog::getSaveFileName(this,"Save file",report_plot ,tr("XLS(*.xls)"));  // save directory is the current user's documents
    if(!Filepath.isNull()){
        //////////////// library code   /////////////////
        BasicExcel xls;
        xls.New(1);

        BasicExcelWorksheet* sheet = xls.GetWorksheet(0);
        XLSFormatManager fmt_mgr(xls);
        CellFormat fmt(fmt_mgr);
        CellFormat foo(fmt_mgr);
        CellFormat op(fmt_mgr);
        op.set_font(ExcelFont().set_weight(FW_BOLD));

        //TEST

        ExcelFont font_header;
        font_header.set_weight(FW_NORMAL);
        font_header.set_font_name(L"Calibri");  // font face "Times New Roman"
        font_header.set_height(380);

        font_header.set_color_index(EGA_BLACK);
        CellFormat fmt_header(fmt_mgr, font_header);

        //
        // Create a table containing an header row in bold and four rows below.
        BasicExcelCell* cell;


        sheet->MergeCells(0,0,2,2);
        cell = sheet->Cell( 0, 0);
        cell->SetFormat( fmt_header );
        cell->SetString("BIOEMTECH ");




        cell = sheet->Cell( 2, 0);
        cell->SetFormat( op );
        cell->SetString("System ");

        cell = sheet->Cell( 2, 1 );
        cell->SetFormat( foo );
        cell->SetString( m_pReadInfo->getSystemName().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");


        //Save Study ID
        cell = sheet->Cell( 0, 3);
        cell->SetFormat( op );
        cell->SetString("Study ID ");

        cell = sheet->Cell( 0, 4 );
        cell->SetFormat( foo );
        cell->SetString( StudyID.toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Study name
        cell = sheet->Cell( 1, 3);
        cell->SetFormat( op );
        cell->SetString("Study name ");

        cell = sheet->Cell( 1, 4 );
        cell->SetFormat( foo );
        cell->SetString( ui->LE_SName->text().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Project name
        cell = sheet->Cell( 2, 3);
        cell->SetFormat( op );
        cell->SetString("Project name ");

        cell = sheet->Cell( 2, 4 );
        cell->SetFormat( foo );
        cell->SetString( ui->LE_project->text().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Animal Info
        //Name
        cell = sheet->Cell( 0, 6);
        cell->SetFormat( op );
        cell->SetString("Animal name ");

        cell = sheet->Cell( 0, 7 );
        cell->SetFormat( foo );
        cell->SetString( ui->LE_p_name->text().toStdString().c_str());
        if ( !cell->GetString() )
            cell->Set("-");

        //Breed
        cell = sheet->Cell( 1, 6);
        cell->SetFormat( op );
        cell->SetString("Breed ");

        cell = sheet->Cell( 1, 7 );
        cell->SetFormat( foo );
        cell->SetString( ui->LE_strain->text().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Species
        cell = sheet->Cell( 2, 6);
        cell->SetFormat( op );
        cell->SetString("Species");

        cell = sheet->Cell( 2, 7 );
        cell->SetFormat( foo );
        cell->SetString( ui->LE_species->text().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Age
        cell = sheet->Cell( 3, 6);
        cell->SetFormat( op );
        cell->SetString("Age");

        cell = sheet->Cell( 3, 7 );
        cell->SetFormat( foo );
        cell->SetString( ui->LE_age->text().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Marking
        cell = sheet->Cell( 4, 6);
        cell->SetFormat( op );
        cell->SetString("Marking");

        cell = sheet->Cell( 4, 7 );
        cell->SetFormat( foo );
        cell->SetString( ui->le_marking->text().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Weight
        cell = sheet->Cell( 5, 6);
        cell->SetFormat( op );
        cell->SetString("Weight");

        cell = sheet->Cell( 5, 7 );
        cell->SetFormat( foo );
        cell->SetString( ui->LE_weight->text().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Gender
        cell = sheet->Cell( 6, 6);
        cell->SetFormat( op );
        cell->SetString("Gender");

        cell = sheet->Cell( 6, 7 );
        cell->SetFormat( foo );

        if ( ui->rb_female->isChecked() )
            cell->SetString( "Female" );
        else if ( ui->rb_male->isChecked() )
            cell->SetString( "Male" );
        else
            cell->SetString( "-" );

        //Radionuclide info
        //Name
        cell = sheet->Cell( 0, 9);
        cell->SetFormat( op );
        cell->SetString("Radionuclide");

        cell = sheet->Cell( 0, 10 );
        cell->SetFormat( foo );
        cell->SetString( ui->CB_radioNuclide->currentText().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Activity
        cell = sheet->Cell( 1, 9);
        cell->SetFormat( op );
        cell->SetString("Injected activity");

        cell = sheet->Cell( 1, 10 );
        cell->SetFormat( foo );
        cell->SetString( ui->dSB_injActivity->text().toStdString().c_str()  );
        if ( !cell->GetString() )
            cell->Set("-");

        //Date
        cell = sheet->Cell( 2, 9);
        cell->SetFormat( op );
        cell->SetString("Injection date-time");

        cell = sheet->Cell( 2, 10 );
        cell->SetFormat( foo );
        cell->SetString( ui->dTime_ingection->dateTime().toString("dd.MM.yyyy hh:mm:ss").toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Path
        cell = sheet->Cell( 3, 9);
        cell->SetFormat( op );
        cell->SetString("Injection path");

        cell = sheet->Cell( 3, 10 );
        cell->SetFormat( foo );
        cell->SetString( ui->CB_ing_path->currentText().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Experimental info ]
        //Date
        cell = sheet->Cell( 0, 12 );
        cell->SetFormat( op );
        cell->SetString("Acquisition date-time");

        cell = sheet->Cell( 0, 13 );
        cell->SetFormat( foo );
        cell->SetString( ui->dTE_aqTime->text().toStdString().c_str() );
        //        cell->SetString( ui->dTE_aqTime->dateTime().toString("dd.MM.yyyy hh:mm:ss").toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Experiment duration
        cell = sheet->Cell( 1, 12 );
        cell->SetFormat( op );
        cell->SetString("Experiment duration");

        cell = sheet->Cell( 1, 13 );
        cell->SetFormat( foo );
        cell->SetString( ui->LE_expDuration->text().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Frame duration
        cell = sheet->Cell( 2, 12 );
        cell->SetFormat( op );
        cell->SetString("Frame duration");

        cell = sheet->Cell( 2, 13 );
        cell->SetFormat( foo );
        cell->SetString( ui->LE_frame->text().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        //Commnents
        cell = sheet->Cell( 0, 15 );
        cell->SetFormat( op );
        cell->SetString("Comments");

        cell = sheet->Cell( 0, 16 );
        cell->SetFormat( foo );
        cell->SetString( ui->TE_comments->toPlainText().toStdString().c_str() );
        if ( !cell->GetString() )
            cell->Set("-");

        int rowsAfter = 9; //Because we do not want to write in the above data!
        //m_iImageNum are the frames
        ushort col=ui->ROI_list->count() + 3, row = m_iImageNum;
        for(int i=0;i < col-1; i++){ //because it crashes  NIKOS
            if ( i == 0 ){
                cell = sheet->Cell(1 + rowsAfter, 0);
                cell->SetFormat(op);
                cell->SetString("Time (min)");
            }
            else if ( i==1 ) {
                cell = sheet->Cell( 1 + rowsAfter,i );
                cell->SetFormat(op);
                cell->SetString("Image Total Counts");
            }
            else{
                cell = sheet->Cell(1 + rowsAfter,i);
                cell->SetFormat(op);
                QString roi_name = ui->ROI_list->item(i-2)->text();
                roi_name.append(" (counts)");
                QByteArray ba = roi_name.toLatin1();
                char *str = ba.data();
                cell->SetString( str );
            }
        }

        foo.set_font(ExcelFont().set_weight( FW_NORMAL ) );
        foo.set_alignment(EXCEL_HALIGN_RIGHT);

        for(int j=1; j <= row; j++ ){
            cell = sheet->Cell( j + 1 + rowsAfter, 0 );
            cell->SetFormat(foo);
            cell->SetDouble( j*frame_duration );

            //if ( j == row ){
            //    cell->SetFormat(fmt);
            //    cell->SetString("Cumulative");
            //}
        }

        //Total counts in the entire image
        float fSum = 0.0;
        for(int j=1; j <= row; j++ ){
            cell = sheet->Cell( j + 1 + rowsAfter, 1 );
            std::stringstream stream;
            stream << std::fixed << setprecision(3) << reference_img_area_counts[j-1];

            if (j != row )
                fSum = fSum + reference_img_area_counts[j-1];
            else {
                //Clear the stream before the last value
                stream.str( std::string() );
                stream << std::fixed << setprecision(3) << fSum;
            }

            std::string s = stream.str();
            QString f_point = QString::fromStdString(s);
            cell->SetDouble( f_point.toDouble()  );
        }

        //Total counts per roi
        fSum = 0.;
        int count = 0;
        for(int i = 0; i < m_iImageNum*ui->ROI_list->count(); i++) {
            for(int j=2; j < col-1; j++){
                for(int p=1; p <= row; p++){
                    cell = sheet->Cell( p + 1 + rowsAfter, j );
                    cell->SetFormat(foo);

                    if ( count < totCounts_table.size() ){
                        if ( p != row ){
                            std::stringstream stream;
                            stream << std::fixed << setprecision(3) << totCounts_table.at( count );
                            fSum += totCounts_table.at( count );
                            std::string s = stream.str();
                            QString f_point = QString::fromStdString(s);
                            cell->SetDouble( f_point.toDouble() );
                        }
                        /*else if ( p == row ){
                            std::stringstream stream;
                            stream << std::fixed << setprecision(3) << fSum;
                            std::string s = stream.str();
                            QString f_point = QString::fromStdString(s);
                            cell->SetDouble( f_point.toDouble() );
                            fSum = 0.;
                            continue;
                        }*/
                    }
                    else if ( count == totCounts_table.size() && p == row   ){
                        std::stringstream stream;
                        stream << std::fixed << setprecision(3) << fSum;
                        std::string s = stream.str();
                        QString f_point = QString::fromStdString(s);
                        cell->SetDouble( f_point.toDouble() );
                        fSum = 0.;
                        continue;
                    }

                    count++;
                }
            }
        }

        //Counts per min
        count = 0;
        fSum = 0.;
        int k = 0;
        for(int i=0; i < m_iImageNum*ui->ROI_list->count(); i++){
            for(int p=col-1; p< 2*col; p++){
                for (int j=1; j<= row; j++){
                    if( j==1 ){
                        cell = sheet->Cell(j + rowsAfter, p );
                        cell->SetFormat(op);
                        if( k < ui->ROI_list->count() )
                        {
                            QString roi_name = ui->ROI_list->item(k)->text();
                            roi_name.append(" (counts/min)");
                            QByteArray ba = roi_name.toLatin1();
                            char *str = ba.data();
                            cell->SetString(str);
                        }
                        k++;
                    }

                    cell = sheet->Cell( j + 1 + rowsAfter,p);
                    cell->SetFormat(foo);

                    if( count < plot_values.size() ){
                        if ( j != row ){
                            std::stringstream stream;
//                            stream << std::fixed << setprecision(2) << plot_values.at(count)/frame_duration;
                            stream << std::fixed << setprecision(2) << plot_values.at(count)/framesList[j];
                            fSum += plot_values.at( count );
                            std::string s = stream.str();
                            QString f_point = QString::fromStdString(s);
                            cell->SetDouble( f_point.toDouble());
                        }
                        /*else if ( j == row ){
                            std::stringstream stream;
//                            stream << std::fixed << setprecision(3) << fSum/( (j-1)*frame_duration );
                            stream << std::fixed << setprecision(3) << fSum/( (j-1)*framesList[j-1] );
                            std::string s = stream.str();
                            QString f_point = QString::fromStdString(s);
                            cell->SetDouble( f_point.toDouble() );
                            fSum = 0.;
                            continue;
                        }*/
                    }
                    else if ( count == plot_values.size() && j == row  ){
                        std::stringstream stream;
//                        stream << std::fixed << setprecision(3) << fSum/( (j-1)*frame_duration );
                        stream << std::fixed << setprecision(3) << fSum/( (j-1)*framesList[j-1] );
                        std::string s = stream.str();
                        QString f_point = QString::fromStdString(s);
                        cell->SetDouble( f_point.toDouble() );
                        fSum = 0.;
                        continue;
                    }

                    count++;
                }
            }
        }

        //Activity
        count =0;
        fSum = 0.;
        k=0;
        for(int i=count;i<m_iImageNum*ui->ROI_list->count();i++){
            for(int p = 2*col-4; p< 3*col; p++){ //If we include more data that depend on the rois 3 should be increased to 4, 5 etc. and 2 to 3, 4 etc.
                for (int j=1; j<= row;j++){

                    if( j==1 ){
                        cell = sheet->Cell(j + rowsAfter, p );
                        cell->SetFormat(op);
                        if( k<ui->ROI_list->count())
                        {
                            QString roi_name = ui->ROI_list->item(k)->text();
                            roi_name.append("(Activity [kBq])");
                            QByteArray ba = roi_name.toLatin1();
                            char *str = ba.data();
                            cell->SetString(str);
                        }
                        k++;
                    }

                    cell = sheet->Cell( j + 1 + rowsAfter,p);
                    cell->SetFormat(foo);

                    if( count < energy_values.size() ){
                        if ( j != row ){
                            std::stringstream stream;
                            stream << std::fixed << setprecision(2) << energy_values.at( count );
                            fSum += plot_values.at( count ); //Because we want at the following steps to calculate the activity of the cummulative
                            std::string s = stream.str();
                            QString f_point = QString::fromStdString(s);
                            cell->SetDouble( f_point.toDouble());
                        }
                        /*else if ( j == row ){
                            std::stringstream stream;
 //                           stream << std::fixed << setprecision(3) << convertCountsToEnergy( fSum/( (j-1)*frame_duration ) );
                            stream << std::fixed << setprecision(3) << convertCountsToEnergy( fSum/( (j-1)*framesList[j-1]) );
                            std::string s = stream.str();
                            QString f_point = QString::fromStdString(s);
                            cell->SetDouble( f_point.toDouble() );
                            fSum = 0.;
                            continue;
                        }*/
                    }
                    else if ( count == energy_values.size() && j == row  ){
                        std::stringstream stream;
//                        stream << std::fixed << setprecision(3) << convertCountsToEnergy( fSum/( (j-1)*frame_duration ) );
                        stream << std::fixed << setprecision(3) << convertCountsToEnergy( fSum/( (j-1)*framesList[j-1] ) );
                        std::string s = stream.str();
                        QString f_point = QString::fromStdString(s);
                        cell->SetDouble( f_point.toDouble() );
                        fSum = 0.;
                        continue;
                    }

                    count++;
                }
            }
        }

        if(!Filepath.contains(".xls"))
            Filepath.append(".xls");
        QByteArray conv = Filepath.toLatin1();
        const char* c_Filepath = conv.data();
        xls.SaveAs(c_Filepath);
        xls.Close();
        QDesktopServices::openUrl(QUrl::fromLocalFile(Filepath));

        QMessageBox msgBox;
        msgBox.setText("Excel data saved in " + Filepath);
        msgBox.exec();
    }
}


void PostProcessing::on_PB_saveSelected_clicked()
{
    if(selectedSlices.isEmpty()){
        QMessageBox::warning(0,"","No frames have been selected!");
    }
    else{
        QString types(	"Portable Network Graphics file (*.png);;"
                        "Bitmap file (*.bmp)");

        QString filter;							// Type of filter
        QString pngExt=".png", bmpExt=".bmp";		// Suffix for the files

        QString suggestedName;
        QString report_images = POST_PROC_path;
        QString fn;

        if(!POST_PROC_path.contains("Report_Images")){
            QDir dir;
            dir.mkdir(report_images.append("/Report_Images"));
        }

        suggestedName=report_images+"/Report_frame_";
        fn = QFileDialog::getSaveFileName(this,tr("Save Image"),
                                          suggestedName,types,&filter);

        int numberOfSelected =selectedSlices.count();
        if(!fn.isEmpty()){
            for(int i=0;i<numberOfSelected;i++){
                int idx = selectedSlices.at(i);


                ImageSlider(idx);

                QPixmap qPixmap;
                qPixmap = central_Plot->grab();

                if(qPixmap.isNull())
                    return;



                if ( !fn.isEmpty() ) {
                    if (fn.contains(pngExt))
                        fn.remove(pngExt);
                    else if (fn.contains(bmpExt))
                        fn.remove(bmpExt);
                    if ( filter.contains(pngExt) ) {
                         if ( idx < m_iImageNum - 1 ) {
                             qPixmap.save(fn + QString::number(idx + 1) + pngExt, "PNG" );
                             selectedNames.append("Report_frame_" + QString::number(idx + 1) + pngExt);
                         }
                         else {
                             qPixmap.save(fn + "summed" + pngExt, "PNG" );
                             selectedNames.append("Report_frame_" + QString::number(idx + 1) + pngExt);
                         }
                    }else if (filter.contains(bmpExt)) {
                        if ( idx < m_iImageNum - 1 ) {
                            qPixmap.save(fn + QString::number(idx + 1) + bmpExt, "BMP" );
                            selectedNames.append("Report_frame_" + QString::number(idx + 1) + bmpExt);
                        }
                        else {
                            qPixmap.save(fn + "summed" + bmpExt, "BMP" );
                            selectedNames.append("Report_frame_" + QString::number(idx + 1) + bmpExt);
                        }
                    }
                }


            }


        }
        ImageSlider(m_iCurrentImage);
    }

}

void PostProcessing::on_cB_selection_toggled(bool checked)
{
    if ( checked )
        selectedSlices.append( m_iCurrentImage );
    else
        if ( selectedSlices.contains(m_iCurrentImage) )
            selectedSlices.at(selectedSlices.indexOf(m_iCurrentImage,0));
}


void PostProcessing::mf_PB_saveAsDICOM( QString fn, int idx )
{
    QString types("DICOM Files(*.dcm)");
    QString filter;							// Type of filter
    QString dcmExt=".dcm";		// Suffix for the files

    uint16_t InputImage[ row[idx]*col[idx] ];
    for ( int m = 0; m < row[idx]; m++)
        for(int j = 0; j < col[idx]; j++)
            InputImage[ m*col[idx] + j ] = static_cast<uint16_t>(m_qrImage[idx][m][j]);

    std::vector<std::string> stringList;
    double pixel_size = 1.7;
    QString pix = QString::number(pixel_size);
    stringList.push_back(ui->le_marking->text().toStdString());
    stringList.push_back(ui->LE_p_name->text().toStdString());
    stringList.push_back(ui->dE_studyDate->date().toString("yyyyMMdd").toStdString());
    QStringList spl = ui->dTE_aqTime->text().split(" ");
    QString h_only;
    QString hour;

    for ( int i =0;i < spl.count(); i++ ) {
        if( i == 1 )
            h_only = spl.at(1);
    }

    stringList.push_back( h_only.toStdString() );
    stringList.push_back("");
    QString gender;
    if(ui->rb_female->isChecked())
        gender = "F";
    else if(ui->rb_male->isChecked())
        gender = "M";

    stringList.push_back(gender.toStdString());
    stringList.push_back(ui->TE_comments->toPlainText().toStdString());
    stringList.push_back(ui->dSB_injActivity->text().toStdString());
    stringList.push_back(ui->LE_weight->text().toStdString());

    std::string str;
    if(ui->LE_mod->text()=="Planar SPECT")
        str.append("ST");
    else if(ui->LE_mod->text()=="Planar PET")
        str.append("PT");

    // We do not need this since it is an info that is not send
    ui->LE_mod->hide();
    ui->label->hide();

    stringList.push_back(str);
    stringList.push_back(pix.toStdString());

    if ( !fn.isEmpty() ) {
        if (!fn.contains(dcmExt))
            fn.append(dcmExt);
        //    selectedNames.append("frame"+QString::number(idx)+dcmExt);
        std::vector<float> dimensions;
        dimensions.push_back(row[idx]);
        dimensions.push_back(col[idx]);
        bioemtec::dicomEncoder enc;
        enc.encoder(fn.toStdString(), stringList, dimensions, InputImage );
    }
}

void PostProcessing::PB_saveAsDICOM_pressed( QString fn )
{
    //    int counter=0;
    QString types("DICOM Files(*.dcm)");

    QString filter;							// Type of filter
    QString dcmExt=".dcm";		// Suffix for the files

    int idx = m_iCurrentImage;

    uint16_t InputImage[ row[idx]*col[idx] ];

    for ( int m = 0; m < row[idx]; m++)
        for(int j = 0; j < col[idx]; j++)
            InputImage[ m*col[idx] + j ] = static_cast<uint16_t>(m_qrImage[idx][m][j]);

    std::vector<std::string> stringList;
    double pixel_size = 1.7;
    QString pix = QString::number(pixel_size);
    stringList.push_back(ui->le_marking->text().toStdString());
    stringList.push_back(ui->LE_p_name->text().toStdString());
    stringList.push_back(ui->dE_studyDate->date().toString("yyyyMMdd").toStdString());
    // QStringList spl = ui->dTE_aqTime->dateTime().toString("yyyyMMdd hhmmss").split(" ");
    QStringList spl = ui->dTE_aqTime->text().split(" ");
    QString h_only;
    QString hour;

    for ( int i =0;i < spl.count(); i++ ) {
        if( i == 1 )
            h_only = spl.at(1);
        //    }

        /*        for(int i=0;i<spl.count();i++)
        {
            if(i==3)
            {
                hour = spl.at(i);
                QString spl2 = hour.remove(":");
                h_only = spl2;

                for(int j =0 ;j<spl2.count();j++)
                {
                    if(j=0)
                        h_only = spl2.at(j);
                    if(j=1)
                        h_only.append(spl2.at(j));
                }
            }
        }*/
    }

    stringList.push_back( h_only.toStdString() );
    stringList.push_back("");
    QString gender;
    if(ui->rb_female->isChecked())
        gender = "F";
    else if(ui->rb_male->isChecked())
        gender = "M";

    stringList.push_back(gender.toStdString());
    stringList.push_back(ui->TE_comments->toPlainText().toStdString());
    stringList.push_back(ui->dSB_injActivity->text().toStdString());
    stringList.push_back(ui->LE_weight->text().toStdString());

    std::string str;
    if(ui->LE_mod->text()=="Planar SPECT")
        str.append("ST");
    else if(ui->LE_mod->text()=="Planar PET")
        str.append("PT");

    // We do not need this since it is an info that is not send
    ui->LE_mod->hide();
    ui->label->hide();

    stringList.push_back(str);
    stringList.push_back(pix.toStdString());

    if ( !fn.isEmpty() ) {
        if (!fn.contains(dcmExt))
            fn.append(dcmExt);
        //    selectedNames.append("frame"+QString::number(idx)+dcmExt);
        std::vector<float> dimensions;
        dimensions.push_back(row[idx]);
        dimensions.push_back(col[idx]);
        bioemtec::dicomEncoder enc;
        enc.encoder(fn.toStdString(), stringList, dimensions, InputImage);
    }
    //    counter++;
}

void PostProcessing::actionExit_triggered()
{
    this->close();
    emit closedWindow();
}

void PostProcessing::on_actionExit_to_Main_Menu_triggered()
{
    this->close();
    emit closedWindow();
}

void PostProcessing::LoadStudy_triggered()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    QString buttonText;
    if ( buttonSender &&  buttonSender->text() == "Cancel" ) return;

    QStringList filter,pngFilter;
    filter<<"*.txt";
    pngFilter << "*.png";

    QString pathName = QStandardPaths::locate(QStandardPaths::DocumentsLocation,"VISUAL-eyes",QStandardPaths::LocateDirectory);
    from_load = true;
/*    qDebug() << " CHECK STUDY " << pathName <<endl;
    if ( !POST_PROC_path.isNull() ){

        QString sPath = POST_PROC_path;
        qDebug() << "START "<< sPath << endl ;
        if (sPath.contains("/CORRECTED") ){
            sPath.remove("/IMAGES/CORRECTED");
            POST_PROC_path.remove("/IMAGES/CORRECTED");
        }
        if (sPath.contains("/FINAL") ){
            sPath.remove("/IMAGES/FINAL");
            POST_PROC_path.remove("/IMAGES/FINAL");
        }
        if(sPath.contains("/POST_PROCESSING")){
            sPath.remove("/POST_PROCESSING");
            POST_PROC_path.remove("/POST_PROCESSING");
        }
        if(sPath.contains("/MERGED")){
            QStringList tempList=sPath.split("/");
            foreach(QString dir, tempList){
                if (dir=="IMAGES")
                    tempList.removeAll(dir);
                if(dir.contains("MERGED")){
                    tempList.removeAll(dir);
                }
                if(dir.isEmpty()){
                    tempList.removeAll(dir);
                }
            }
            sPath=tempList.join("/");
            sPath.push_front("/");
            POST_PROC_path = sPath;
        }
        if(sPath.contains("/Merged")){
            QString path =sPath;
            QStringList tempList=path.split("/");
            foreach(QString dir, tempList){
                if (dir=="POST_PROCESSING")
                    tempList.removeAll(dir);
                if(dir.contains("Merged")){
                    tempList.removeAll(dir);
                }
                if(dir.isEmpty()){
                    tempList.removeAll(dir);
                }
            }
            path=tempList.join("/");
            path.push_front("/");
            sPath=path;
            POST_PROC_path = sPath;
        }

        qsStudyInfoPath = POST_PROC_path;
        qDebug() << "POST PROC PATH " << POST_PROC_path << endl;

        directory = QFileDialog::getExistingDirectory(this, ("Select Output Folder"), sPath,QFileDialog::DontResolveSymlinks);
        QString path = directory;
        if ( path.contains("/CORRECTED")) {
            POST_PROC_path = path.remove("/IMAGES/CORRECTED");
            POST_PROC_path.append("/POST_PROCESSING");
        }
        else if ( path.contains("/FINAL")) {
            POST_PROC_path = path.remove("/IMAGES/FINAL");
            POST_PROC_path.append("/POST_PROCESSING");
        }
        else if ( path.contains("/MERGED")) {
            QString fNo;
            QStringList tempList=path.split("/");
            foreach(QString dir, tempList){
                if (dir=="IMAGES")
                    tempList.removeAll(dir);
                if(dir.contains("MERGED")){
                    tempList.removeAll(dir);
                    QStringList tempList2=dir.split("_");
                    fNo=tempList2[1];
                }
                if(dir.isEmpty()){
                    tempList.removeAll(dir);
                }
            }
            path=tempList.join("/");
            POST_PROC_path = path;
            POST_PROC_path.append("/POST_PROCESSING/Merged_"+fNo);
        }
        else if ( path.contains("DICOM") ){
            QMessageBox::warning(0,"","Please use a DICOM viewer to open DICOM files.");
        }

    }
    else { */
        POST_PROC_path.clear();
        directory = QFileDialog::getExistingDirectory(this, ("Select Output Folder"), pathName,QFileDialog::DontResolveSymlinks);
        QString path;
        path = directory;//QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        if ( path.contains("CORRECTED") ){
            POST_PROC_path = path.remove("/IMAGES/CORRECTED");
            qsStudyInfoPath = POST_PROC_path;
            POST_PROC_path.append("/POST_PROCESSING");
        }
        else if ( path.contains("FINAL") ){
            POST_PROC_path = path.remove("/IMAGES/FINAL");
            qsStudyInfoPath = POST_PROC_path;
            POST_PROC_path.append("/POST_PROCESSING");
        }
        else if ( path.contains("MERGED") ){
            QString fNo;
            QString tempInfoPath;
            QStringList tempList=path.split("/");
            foreach(QString dir, tempList){
                if (dir=="IMAGES")
                    tempList.removeAll(dir);
                if(dir.contains("MERGED")){
                    tempList.removeAll(dir);
                    QStringList tempList2=dir.split("_");
                    fNo=tempList2[1];
                }
                if(dir.isEmpty()){
                    tempList.removeAll(dir);
                }
            }
            qsStudyInfoPath = path;
            path=tempList.join("/");
            path.push_front("/");
            POST_PROC_path = path;
//            qsStudyInfoPath = POST_PROC_path;
            POST_PROC_path.append("/POST_PROCESSING/Merged_"+fNo);
        }
        else if ( path.contains("DICOM") ){
            QMessageBox::warning(0,"","Please use a DICOM viewer to open DICOM files.");
        }
    if( directory != "" && !directory.contains("DICOM")) {
        QString copy = directory;
        QRegExp sep("(\/)");
        QStringList pieces =  copy.split(sep);
        int indx =0;
        if( copy.contains("CORRECTED") || copy.contains("FINAL") )
            indx = pieces.count()-3;
        else if(copy.contains("POST_PROCESSING"))
            indx = pieces.count()-2;

        QString folder_name =  pieces.at(indx);
        StudyID = folder_name;

        Init( StudyID );
        QDir dir(directory);
        if (directory.contains("MERGED")){
           ui->PB_merge->setDisabled(true);
           m_merged=true;
        }else{
           ui->PB_merge->setDisabled(false);
           m_merged=false;
        }


        QString copyForFusion = directory;
        QString copyForXray = directory;
        copyForFusion.append("/FUSION");
        copyForXray.append("/XRAY");

        QDir fusionDir(copyForFusion);
        QDir xrayDir(copyForXray);
        fusionDir.setNameFilters(pngFilter);
        xrayDir.setNameFilters(pngFilter);

        QStringList fussedImages =fusionDir.entryList(pngFilter,QDir::Files|QDir::NoSymLinks);
        QStringList xrayImages =xrayDir.entryList(pngFilter,QDir::Files|QDir::NoSymLinks);
        QStringList images = dir.entryList(filter, QDir::Files );
        if (images.contains("StudyInfo.txt"))
            images.removeAll("StudyInfo.txt");

        m_qslImagesNames = images;

        m_iImageNum = images.size();
        fussedSize = fussedImages.size();
        xraySize = xrayImages.size();

        QProgressDialog fileLoadProgress("Loading study ...",nullptr,0,3*m_iImageNum,this);

        float mean=0,stdev=0;
        int item = 0;

        m_iCurrentImage=0;


        if ( m_iImageNum != 0 && directory != "" ){
            reference_img_area_counts = new float[m_iImageNum];
            copy_ref_counts = new float[m_iImageNum];
            ui->horizontalScrollBar_2->setRange(0,m_iImageNum-1);
            m_qrImage = new qreal**[m_iImageNum];

            selectedSlices.reserve(m_iImageNum);
            ui->horizontalScrollBar_2->setEnabled(true);

            row= new int[m_iImageNum];
            col= new int[m_iImageNum];

            foreach(QString FileName, images){
                QString cp = directory;
                cp.append("/");
                QByteArray byteArray;
                QFile File(cp.append(FileName));

                //  File.open(QFile::ReadOnly);
                QTextStream textStream(&byteArray,QIODevice::ReadOnly);
                if( File.exists() && File.open(QIODevice::ReadOnly)){
                    byteArray= File.readAll();
                    File.close();
                    //return 0;
                }
                else {
#ifdef QT_DEBUG
                    qDebug("Failed to open file for reading.");
                    break;
#endif
                }

                int row_num=0,col_num=0,cnt=0;
                QString line;
                QStringList fields;
                QStringList list_item;
                QLocale c (QLocale::C);
                bool ok;

                while(!textStream.atEnd()){
                    line = textStream.readLine();
                    fields = line.split(QRegExp("[\t ]+"));
                    col_num = fields.size();
                    for(int i =0; i< col_num;i++)
                        list_item.append(fields.at(i));

                    row_num++;
                }

                col[item] = col_num;
                row[item] = row_num;

                m_qrImage[item] = new  qreal*[row_num];
                for(int i=0;i<row_num;i++)
                    m_qrImage[item][i] = new qreal[col_num];

                for(int i=0;i<row_num;i++){
                    for(int j=0;j<col_num;j++){
                        m_qrImage[item][i][j] = c.toDouble(list_item.at(cnt),&ok);
                        cnt++;
                    }
                }

                std::tie(mean,stdev,reference_img_area_counts[item]) = ROI_statistics(QRectF(0,0,col_num,row_num),item);
                copy_ref_counts[item] =  reference_img_area_counts[item];
                item++;
                fileLoadProgress.setValue(item);
                QApplication::processEvents();
            }

            fileLoadProgress.setValue(3*m_iImageNum);

            for( int i=0; i < m_iImageNum; i++){
                if(fastDynamic){
                    if( i<6){
                        framesList.append(10.0/60.0);
                    }
                    else if(i>=6 && i<14){
                        framesList.append(30.0/60.0);
                    }
                    else if(i>=14 && i<19){
                        framesList.append(60.0/60.0);
                    }
                    else if(i>=19 && i<45){
                        framesList.append(120.0/60.0);
                    }
                }else {
                    framesList.append(frame_duration);
                }
                ImageSlider( i );
            }
            ImageSlider( 0 );
            ui->horizontalSlider_contrast->setEnabled( true );
            ui->horizontalSlider_contrast_min->setEnabled( true );
            ui->horizontalSlider_contrast->setValue(100 );
            ui->horizontalSlider_contrast_min->setValue(0);
        }


    }
    mf_loadOpticalImage();
    if (ui->cB_fusion->isChecked()){
        addOpticalBackground();
    }else if(ui->cB_xray->isChecked()){
        addXrayBackground();
    }
}

void PostProcessing::on_PB_dicomViewer_clicked() { QProcess::startDetached("/usr/bin/amide"); }

//This is for showing the fussed images.
void PostProcessing::on_cB_fusion(bool checked) //NIKOS
{
    if( checked) {
        if (m_cvOpticalImage.empty()){
            central_Plot->setCanvasBackground(QBrush(QColor(53,53,53)));
            central_Plot->replot();
         }else{
            ui->opacitySlider->setEnabled(true);
            addOpticalBackground();
         }
    }
    else {
        removeBackground();
        central_Plot->setCanvasBackground(QBrush(QColor(53,53,53)));
        central_Plot->replot();
    }
}


//This is for showing the fussed images.
void PostProcessing::on_cB_xray(bool checked) //NIKOS
{
    if( checked) {

        if (m_cvXrayImage.empty()){
            central_Plot->setCanvasBackground(QBrush(QColor(53,53,53)));
            central_Plot->replot();
         }else{
            ui->opacitySlider->setEnabled(true);
            addXrayBackground();
            central_Plot->replot();
         }
    }
    else {
        removeBackground();
        central_Plot->setCanvasBackground(QBrush(QColor(53,53,53)));
        central_Plot->replot();
    }
}

void PostProcessing::removeBackground(){

    central_Plot->spectrogram1->setAlpha(255);
    ui->opacitySlider->setDisabled(true);
}

void PostProcessing::addXrayBackground(){
    if (m_cvXrayImage.empty()){
        central_Plot->setCanvasBackground(QBrush(QColor(53,53,53)));
        central_Plot->replot();
    }else{
        QPalette palette;

        cv::Mat centralWindow=cv::Mat::zeros(central_Plot->height(),central_Plot->width(), CV_8U);
        cv::Mat tempXray=m_cvXrayImage.clone();
        int paddingY=(central_Plot->height()-central_Plot->canvas()->height())/2;
        cv::resize(tempXray, tempXray, cv::Size(central_Plot->canvas()->width(),central_Plot->canvas()->height()), 0, 0, cv::INTER_CUBIC);
        cv::Rect roi(0, paddingY,tempXray.size().width, tempXray.size().height);
        tempXray.copyTo(centralWindow( roi ));

        QImage xrayQImg(static_cast<const uchar *>(centralWindow.data), centralWindow.cols, centralWindow.rows, QImage::Format_Grayscale8);
        palette.setBrush(central_Plot->canvas()->backgroundRole(), QBrush(xrayQImg));

        central_Plot->canvas()->setPalette(palette);
        central_Plot->spectrogram1->setAlpha(ui->opacitySlider->value());
        central_Plot->replot();
    }

}

void PostProcessing::addOpticalBackground(){

    if (m_cvOpticalImage.empty()){
        central_Plot->setCanvasBackground(QBrush(QColor(53,53,53)));
        central_Plot->replot();
    }else{
        QPalette palette;

        cv::Mat centralWindow=cv::Mat::zeros(central_Plot->height(),central_Plot->width(), CV_8U);
        cv::Mat tempOptical=m_cvOpticalImage.clone();
        int paddingY=(central_Plot->height()-central_Plot->canvas()->height())/2;
        cv::resize(tempOptical, tempOptical, cv::Size(central_Plot->canvas()->width(),central_Plot->canvas()->height()), 0, 0, cv::INTER_CUBIC);
        cv::Rect roi(0, paddingY, tempOptical.size().width,tempOptical.size().height);
        tempOptical.copyTo(centralWindow( roi ));
        QImage opticalQImg(static_cast<const uchar *>(centralWindow.data), centralWindow.cols, centralWindow.rows, QImage::Format_Grayscale8);
        palette.setBrush(central_Plot->canvas()->backgroundRole(), QBrush(opticalQImg));

        central_Plot->canvas()->setPalette(palette);
        central_Plot->spectrogram1->setAlpha(ui->opacitySlider->value());
        central_Plot->replot();
    }


}

void PostProcessing::opacityValueChanged(int){
    int val = ui->opacitySlider->value();
    central_Plot->spectrogram1->setAlpha(val);
    central_Plot->replot();
}

void PostProcessing::setCheckstateOptical(){
    if( m_isOpticalChecked ){
       ui->cB_fusion->setCheckable(false);
       ui->cB_fusion->setChecked(false);
       m_isOpticalChecked = false;
       on_cB_fusion(false);
    }
    else {
       ui->cB_fusion->setCheckable(true);
       ui->cB_fusion->setChecked(true);
       m_isOpticalChecked = true;
       on_cB_fusion(true);

       ui->cB_xray->setChecked(false);
       m_isXrayChecked = false;
    }
}

void PostProcessing::setCheckstateXray(){
    if( m_isXrayChecked ){
      ui->cB_xray->setCheckable(false);
      ui->cB_xray->setChecked(false);
      m_isXrayChecked = false;
      on_cB_xray(false);
    }
    else {
      ui->cB_xray->setCheckable(true);
      ui->cB_xray->setChecked(true);
      m_isXrayChecked = true;
      on_cB_xray(true);

      ui->cB_fusion->setChecked(false);
      m_isOpticalChecked = false;
    }
}


void PostProcessing::on_PB_merge()
{

    QString startupDir, frameDir, destPath, postProcPath, opticalPath, xrayPath;
    startupDir = POST_PROC_path;

    destPath=startupDir;
    postProcPath=startupDir;
    startupDir.remove("/POST_PROCESSING");
    destPath.remove("/POST_PROCESSING");
    destPath.append("/IMAGES");
    frameDir=destPath;
    frameDir.append("/FINAL");

    QDir destDir(destPath);
    QDir postProcDir(postProcPath);
    QStringList filters, mergedDirs;
    filters << "MERGED*" ;
    mergedDirs =destDir.entryList(filters,QDir::Dirs|QDir::NoSymLinks);
    destPath.append("/MERGED_"+ QString::number(mergedDirs.size()));
    destDir.mkdir(destPath);
    postProcPath.append("/Merged_"+ QString::number(mergedDirs.size()));
    postProcDir.mkdir(postProcPath);



    opticalPath=startupDir;
    xrayPath=startupDir;
    opticalPath.append("/optical.png");
    xrayPath.append("/Xray.png");

    mergeDialog * mergeWindow = new mergeDialog(m_pReadInfo, nullptr,frameDir, opticalPath, xrayPath, postProcPath, destPath, StudyID, m_bIsBeta);
    mergeWindow->resize(300, 50);
    mergeWindow->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mergeWindow->show();
}


float PostProcessing::convertCountsToEnergy( float counts_per_min )
{
    if ( counts_per_min > 0.0 ){
        if(m_bIsBeta){
            if ( counts_per_min <= ( m_pReadInfo->getNuclide_lim1() - m_pReadInfo->getNuclide_b1() )/m_pReadInfo->getNuclide_a1() )
                return  1e3*m_pReadInfo->getNuclide_a1()*counts_per_min + m_pReadInfo->getNuclide_b1();
            else if ( ( m_pReadInfo->getNuclide_lim1() - m_pReadInfo->getNuclide_b1() )/m_pReadInfo->getNuclide_a1() < counts_per_min
                      && counts_per_min <=  ( m_pReadInfo->getNuclide_lim2() - m_pReadInfo->getNuclide_b2() )/m_pReadInfo->getNuclide_a2() )
                return  1e3*m_pReadInfo->getNuclide_a2()*counts_per_min + m_pReadInfo->getNuclide_b2();
            else if ( ( m_pReadInfo->getNuclide_lim2() - m_pReadInfo->getNuclide_b2() )/m_pReadInfo->getNuclide_a2() < counts_per_min
                      && counts_per_min <=  ( m_pReadInfo->getNuclide_lim3() - m_pReadInfo->getNuclide_b3() )/m_pReadInfo->getNuclide_a3() )
                return  1e3*m_pReadInfo->getNuclide_a3()*counts_per_min + m_pReadInfo->getNuclide_b3();
            else
                return 0.0;

         }else{
            spectIsotope chosenIsotope=m_pReadInfo->getSpectIsotope(m_qsCollimator,m_qsNuclideName);
            if (  counts_per_min <= chosenIsotope.getLimit1() )
                return  chosenIsotope.getA1()*counts_per_min + chosenIsotope.getB1();
            else if ( chosenIsotope.getLimit1() < counts_per_min &&  counts_per_min <=  chosenIsotope.getLimit2() )
                return  chosenIsotope.getA2()*counts_per_min +chosenIsotope.getB2();
            else if ( counts_per_min >  chosenIsotope.getLimit2() )
                return  chosenIsotope.getA3()*counts_per_min + chosenIsotope.getB3();
            else
                return 0.0;
        }
    }
    else
        return 0.0;
}



void PostProcessing::on_PB_pdfReport()
{


    ///// open file dialog for the user to name the expoted report
    QString report_filepath = POST_PROC_path+"/StudyReport"; /// store directory is the users documents every time
    //QString report_name="/StudyReport";
    QString types("Portable Document Format file (*.pdf)");
    QString filter=".pdf";

    QString fn = QFileDialog::getSaveFileName(this,tr("Save pdf report"),
                                     report_filepath, types, &filter);


    if(!fn.isEmpty()){

            QPdfWriter writer(fn.append(".pdf"));
            writer.setPageSize(QPagedPaintDevice::A4);
            writer.setPageMargins(QMargins(30, 30, 30, 30));

            QPainter painter(&writer);
            painter.setPen(Qt::black);
            painter.setFont(QFont("Times", 18));
            QPixmap logo;
            logo.load(":icons/BIOEMTECH_GREY.png");
            logo.scaled(2700,726,Qt::KeepAspectRatio);

            painter.drawPixmap(QRect(0,0,2700,726), logo);

            QString title = "Study Report";


            int begin_text_h=700;



            painter.drawText(QRect(0,begin_text_h,8917,350), Qt::AlignCenter, title);


            painter.setPen(Qt::black);
            painter.setFont(QFont("Times", 10));
            painter.drawText(QRect(0,begin_text_h+600,8917,200), Qt::AlignLeft, "Study Info");

            painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
            painter.drawLine(0,begin_text_h+850,8917,begin_text_h+860);




            ///
            int position_x=0;
            int position_y=begin_text_h+950;
            int position_y_start=begin_text_h+950;
            int position_x_start=0;
            int y_step=200;
            int x_step=2200;
            ///
            /// \brief date

            painter.setPen(Qt::black);
            painter.setFont(QFont("Times", 7));


            QString system = "System: ";
            system.append(m_pReadInfo->getSystemName()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, system);


            position_y+=y_step;
            QString study_id = "Study ID: ";
            study_id.append(StudyID+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, study_id);

            position_y+=y_step;
            QString study_name = "Study name: ";
            study_name.append(ui->LE_SName->text()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, study_name);

            position_y+=y_step;
            QString project_name="Project name: ";
            project_name.append(ui->LE_project->text()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, project_name);

            position_y+=y_step;
            QString animal_name = "Animal name: ";
            animal_name.append(ui->LE_p_name->text()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, animal_name);


            ///Section 2
            ///
            ///
            ///
            position_x+=x_step;
            position_y=position_y_start;
            QString breed = "Breed: ";
            breed.append(ui->LE_strain->text()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, breed);

            position_y+=y_step;
            QString species = "Species: ";
            species.append(ui->LE_species->text()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, species);

            position_y+=y_step;
            QString marking = "Marking: ";
            marking.append(ui->le_marking->text()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, marking);

            position_y+=y_step;
            QString weight = "Weight: ";
            weight.append(ui->LE_weight->text()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft,weight);


            position_y+=y_step;
            QString gender = "Gender: ";
            if(ui->rb_female->isChecked())
               gender.append("Female\n");
            else if ( ui->rb_male->isChecked() )
               gender.append("Male\n");
            else
               gender.append(ui->LE_weight->text()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft,gender);



            ///Section 3
            ///
            ///
            ///
            position_x+=x_step;
            position_y=position_y_start;
            QString radionuclide = "Radionuclide: ";
            radionuclide.append(ui->CB_radioNuclide->currentText()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, radionuclide);

            position_y+=y_step;
            QString activity = "Injected activity: ";
            activity.append(ui->dSB_injActivity->text()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, activity);

            position_y+=y_step;
            QString activity_date = "Injection date-time: ";
            activity_date.append(ui->dTime_ingection->dateTime().toString("dd.MM.yyyy hh:mm:ss")+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, activity_date);

            position_y+=y_step;
            QString inpection_path = "Injection path: ";
            inpection_path.append(ui->CB_ing_path->currentText()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, inpection_path);

            position_y+=y_step;
            QString acq_date = "Acquisition date: ";
            acq_date.append(ui->dTE_aqTime->text()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, acq_date);


            ///Right column
            ///
            ///
            ///
            position_x+=x_step;
            position_y=position_y_start;
            QString duration = "Experiment duration: ";
            duration.append(ui->LE_expDuration->text()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, duration);

            position_y+=y_step;
            QString frame = "Frame duration: ";
            frame.append(ui->LE_frame->text()+"\n");
            painter.drawText(QRect(position_x,position_y,3000,200), Qt::AlignLeft, frame);



            //// SECTION ACTIVITY-TIME CURVES
            ///
            ///


            qDebug()<< "**"<<position_y <<" " << begin_text_h<< endl;
            position_y+=900;
            painter.setPen(Qt::black);
            painter.setFont(QFont("Times", 10));
            painter.drawText(QRect(0,position_y,8917,200), Qt::AlignLeft, "Time-Activity curves");
            painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
            position_y+=y_step;
            painter.drawLine(0,position_y,8917,position_y+10);




            QPixmap time_activity_img=graphs->grab();
            qDebug()<<time_activity_img.height()<<" "<< time_activity_img.width()<<endl;
            position_y+=y_step;
            time_activity_img.scaled(time_activity_img.width()*7,time_activity_img.height()*7);
            painter.drawPixmap(QRect(position_x_start,position_y,time_activity_img.width()*7,time_activity_img.height()*7),time_activity_img);

            position_y+=time_activity_img.height()*7 +900;
            painter.setPen(Qt::black);
            painter.setFont(QFont("Times", 10));
            painter.drawText(QRect(0,position_y,8917,200), Qt::AlignLeft, "Images");
            painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
            position_y+=y_step;
            painter.drawLine(0,position_y,8917,position_y+10);


            //Loop over all frames

            y_step=300;
            x_step=1200;
            position_y+=y_step;
            qDebug() << "current image " << m_iCurrentImage<<endl;
            painter.setFont(QFont("Times", 9));
            int current_index=m_iCurrentImage;
            position_x=position_x_start;
            for(int i=0; i<m_iImageNum-1; i+=2) {
                int index1=i+1;
                ImageSlider(i);
                QPixmap frame1 = central_Plot->grab();
                int index2=i+2;

                ImageSlider(i+1);
                QPixmap frame2 = central_Plot->grab();

                int img_width=frame1.width()*6;
                int img_height=frame1.height()*6;
                position_x=position_x_start;
                painter.drawText(QRect(position_x,position_y,300,300), Qt::AlignLeft, QString::number(index1)+".");
                frame1.scaled(img_width,img_height);
                painter.drawPixmap(QRect(position_x+300,position_y,img_width,img_height),frame1);

                position_x=position_x+img_width+x_step;
                painter.drawText(QRect(position_x,position_y,300,300), Qt::AlignLeft, QString::number(index2)+".");
                frame2.scaled(img_width,img_height);
                painter.drawPixmap(QRect(position_x+300,position_y,img_width,img_height),frame2);
                qDebug() << position_y << endl;
                if (position_y >10000){
                    writer.newPage();
                    position_y=0;
                }else{
                    position_y+=img_height+y_step;
                }

            }
            if(m_iImageNum%2!=0){
                ImageSlider(m_iImageNum-1);
                QPixmap frame1 = central_Plot->grab();
                int index1=m_iImageNum;

                int img_width=frame1.width()*6;
                int img_height=frame1.height()*6;
                if(position_x==0)
                    position_x=position_x+img_width+x_step;
                else
                    position_x=position_x_start;
                position_y+=y_step;
                painter.drawText(QRect(position_x,position_y,300,300), Qt::AlignLeft, QString::number(index1)+".");
                frame1.scaled(img_width,img_height);
                painter.drawPixmap(QRect(position_x+300,position_y,img_width,img_height),frame1);
            }
            ImageSlider(current_index);
            painter.end();

            QMessageBox msgBox;
            msgBox.setText("Report saved in " + fn);
            msgBox.exec();
    }


}




