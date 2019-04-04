#include "package.h"
#include <QtGui>

Package::Package()
{
    Pin pin;
    pinW = pin.width();
    pinH = pin.height();

    packageName = "Unknown package";
    MCUName = "Unknown MCU";
}

int Package::getSide()
{
    return w;
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
    painter->eraseRect(rect);

    //set font and point for packahe and MCU names
    QPointF T(w/3, h*2/3);
    QFont font;
    font.setBold(true);
    font.setItalic(true);
    font.setPointSize(font.pointSize() + 2);
    painter->setFont(font);

    //drawing MCU name
    painter->drawText(T,MCUName);

    //drawing packageName
    T.setY(T.y() + h*0.1);
    painter->drawText(T,packageName);


    //drawing package
    painter->drawRoundRect(rect, 3,3);

    //drawing inside rectangle
    int side = 40;
    int r = 10;
    painter->drawRoundRect(side, side, w-2*side, h-2*side, r, r);

    //painting logo
    qreal logo_side_w = 70;
    qreal logo_side_h = 60;
    qreal logo_x = w/2 - logo_side_w/2;
    qreal logo_y = h*0.3;
    qreal offset_small =  h*0.005;
    qreal offset_big =    h*0.01;
    qreal offset_side_x = logo_side_w*0.33;
    qreal offset_side_y = logo_side_h*0.45;

    QRectF backLogo(logo_x,logo_y,logo_side_w,logo_side_h);
    painter->setBrush(Qt::black);
    painter->drawRect(backLogo);

    QVector<QPointF> polyVector;
    polyVector.append(QPointF(logo_x + logo_side_w/2,      logo_y + offset_small));
    polyVector.append(QPointF(logo_x + logo_side_w - offset_small,    logo_y + logo_side_h - offset_big));

    polyVector.append(QPointF(logo_x + logo_side_w - offset_side_x,    logo_y + logo_side_h - offset_big));
    polyVector.append(QPointF(logo_x + logo_side_w - offset_side_x,    logo_y + logo_side_h - offset_side_y));
    polyVector.append(QPointF(logo_x + logo_side_w/2,      logo_y + logo_side_h - offset_big));
    polyVector.append(QPointF(logo_x + offset_side_x,      logo_y + logo_side_h - offset_side_y));
    polyVector.append(QPointF(logo_x + offset_side_x,      logo_y + logo_side_h - offset_big));

    polyVector.append(QPointF(logo_x + offset_small,                logo_y + logo_side_h - offset_big));
    painter->setBrush(Qt::white);
    QPolygonF polygon(polyVector);

    painter->drawPolygon(polygon);
    painter->setBrush(Qt::black);
}

QPointF Package::getPinPos(int pin)
{
    return pinPosList.at(pin-1);
}

Utils::View_Orientation Package::getPinOrientation(int pin)
{
    return pinOrientationList.at(pin-1);
}

void Package::setMCUName(const QString &name)
{
    MCUName = name;
}


