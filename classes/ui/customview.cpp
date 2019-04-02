#include "customview.h"

#include <QGraphicsScene>
#include <QWheelEvent>
#include <math.h>

#include "pin.h"

CustomView::CustomView(QWidget *parent)
    : QGraphicsView(parent)
{

}



void CustomView::wheelEvent(QWheelEvent *e){

    if (e->delta() > 0)
        scale(1.15, 1.15);
    else
        scale(1/1.15, 1/1.15);
}

void CustomView::scaleView(qreal scaleFactor){
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void CustomView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

