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

Pin::Pin(const QString &text, Utils::View_Orientation orient, QPointF pos)
{
    Pressed = false;
    this->text = text;
    this->orientation = orient;
    this->color = Qt::gray;
    this->setPos(pos);
}

QRectF Pin::boundingRect() const
{
    return QRectF(0,0,w,h);
}

void Pin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rect = boundingRect();
    painter->eraseRect(rect);

    QBrush brush(color);
    QPointF T;
    QMatrix matrix;

    //set orientation
    switch(orientation){
    case Utils::View_Horizontal: matrix.rotate(0); break;
    case Utils::View_Vertical_NS: matrix.rotate(90); break;
    case Utils::View_Vertical_SN: matrix.rotate(-90); break;
    case Utils::View_Diagonal_NWSE: matrix.rotate(45); break;
    case Utils::View_Diagonal_SWNE: matrix.rotate(-45); break;
    }
    this->setMatrix(matrix);

    //for debug - change color then pressing
    if (Pressed){
        brush.setColor(Qt::red);
    }
    else {
        brush.setColor(color);
    }

    //draw pin
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

void Pin::setOrientation(Utils::View_Orientation o)
{
    this->orientation = o;
    update();
}

int Pin::width()
{
    return this->w;
}

int Pin::height()
{
    return this->h;
}

void Pin::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    Q_UNUSED(event);
}

void Pin::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    update();
    Q_UNUSED(event);
}
