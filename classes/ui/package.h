#ifndef PACKAGE_H
#define PACKAGE_H

#include <QGraphicsItem>
#include <QPointF>
#include "pin.h"

class Package : public QGraphicsItem
{
public:
    Package();
    int getSide();

    QPointF getPinPos(int pin);
    Utils::View_Orientation getPinOrientation(int pin);
    void setMCUName(const QString &name);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QString packageName;
    QString MCUName;
    int w = 200;
    int h = 200;
    int pinW;
    int pinH;
    int stepPin;
    QList<QPointF> pinPosList;
    QList<Utils::View_Orientation> pinOrientationList;



private:

};

#endif // PACKAGE_H
