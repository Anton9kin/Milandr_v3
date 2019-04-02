#include "pin.h"

/**
 * @brief Pin::Pin
 *
 * @details
 *  Use next options for next:
 *          - Set rectangle area - painter->drawRect()
 *          - Set text in rectagle area - painter->drawText()
 *          - Rotate - painter->rotate(), after that you have to paint something
 */

Pin::Pin(const QString &text, Pin::Pin_Orientation orient)
{
    Pressed = false;
    this->text = text;
    this->orientation = orient;
    this->color = Qt::gray;
}

QRectF Pin::boundingRect() const
{
    return QRectF(this->x(),this->y(),60,20);
}

void Pin::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QRectF rect = boundingRect();
    QBrush brush(color);
    QPointF T;
    qreal angle = 0;

    switch(orientation){
    case Pin_Horizontal: angle = 0; break;
    case Pin_Vertical: angle = 90; break;
    case Pin_Diagonal_NWSE: angle = 45; break;
    case Pin_Diagonal_SWNE: angle = -45; break;
    }

    if (Pressed){
        brush.setColor(Qt::red);
    }
    else {
        brush.setColor(color);
    }

    painter->rotate(angle);
    painter->fillRect(rect,brush);
    T.setX(rect.x() + 5);
    T.setY(rect.y() + 15);
    painter->drawText(T,text);
    painter->drawRect(rect);

}

void Pin::setColor(Qt::GlobalColor color)
{
    this->color = color;
    update();
}

void Pin::setText(const QString &t)
{
    this->text = t;
    update();
}

void Pin::setOrientation(Pin::Pin_Orientation o)
{
    this->orientation = o;
    update();
}

void Pin::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Pin::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
