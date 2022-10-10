#include "headers/clickablelabel.h"
#include <QMouseEvent>

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags):QLabel(parent) {}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent( QMouseEvent* event) {
    if ( event->buttons() & Qt::LeftButton )
        emit clicked();
}

void ClickableLabel::enterEvent(QEvent *)
{
    setStyleSheet("border: 4px solid red");
}

void ClickableLabel::leaveEvent(QEvent *)
{
    setStyleSheet("");
}
