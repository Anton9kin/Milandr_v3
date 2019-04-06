#include "pin.h"
#include <QMenu>
/**
 * @brief Pin::Pin
 *
 * @details
 *  Use next options for next:
 *          - Set rectangle area - painter->drawRect()
 *          - Set text in rectagle area - painter->drawText()
 *          - Rotate - painter->rotate(), after that you have to paint something
 */

#define COLOR_DEFAULT   Qt::lightGray
#define COLOR_SELECTED   Qt::green
#define COLOR_SIMPLE   Qt::yellow

Pin::Pin(const QString &text, Utils::View_Orientation orient, QPointF pos)
{
    Pressed = false;
    this->text = text;
    this->initText = text;
    this->orientation = orient;
    this->color = COLOR_DEFAULT;
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
    QRectF Tv;

    //draw pin
    //fill background and draw border
    painter->fillRect(rect,brush);
    painter->drawRect(rect);
    //set point and draw pin text
    T.setX(rect.x() + 5);
    T.setY(rect.y() + 15);
    painter->drawText(T,text);
    //set point and draw value

    //set orientation
    switch(orientation){
    case Utils::View_Horizontal:
        matrix.rotate(0);
        Tv.setX(rect.x()-w);
        Tv.setY(rect.y());
        break;
    case Utils::View_Horizontal_Right:
        matrix.rotate(0);
        Tv.setX(rect.x()+w+5);
        Tv.setY(rect.y());
        break;
    case Utils::View_Vertical_NS:
        matrix.rotate(90);
        Tv.setX(rect.x()+w+5);
        Tv.setY(rect.y());
        break;
    case Utils::View_Vertical_SN:
        matrix.rotate(-90);
        Tv.setX(rect.x()+w+5);
        Tv.setY(rect.y());
        break;
    case Utils::View_Diagonal_NWSE:
        matrix.rotate(45);
        break;
    case Utils::View_Diagonal_SWNE:
        matrix.rotate(-45);
        break;
    }

    Tv.setWidth(w);
    Tv.setHeight(h);
    //painter->eraseRect(Tv);
    //painter->drawText(Tv,text);

    this->setMatrix(matrix);
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

void Pin::addToValueList(QString value)
{
    valueList.append(value);
}

void Pin::addToValueList(QList<QString> list)
{
    valueList.append(list);
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

void Pin::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (valueList.isEmpty())
        return;

    QMenu menu;
    menu.setTitle(initText);
    for (QString value : valueList)
        menu.addAction(value);

    QAction *act = menu.exec(event->screenPos());

    if (act != nullptr){
        if (QString::compare(act->text(), valueList.at(0)) == 0){
            color = COLOR_DEFAULT;
            this->text = "";
        }
        else{
            color = COLOR_SELECTED;
            this->text = act->text();
        }

        update();
    }
}
