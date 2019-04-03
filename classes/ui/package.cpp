#include "package.h"
#include <QtGui>

Package::Package()
{
}

QRectF Package::boundingRect() const
{
    return QRectF(0,0,w,h);
}

void Package::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF rect = boundingRect();
    QPointF T;

    painter->setPen(Qt::blue);

    T.setX(rect.x() + 5);
    T.setY(rect.y() + 15);
    painter->drawText(T,"Package");
    painter->drawRect(rect);
}

