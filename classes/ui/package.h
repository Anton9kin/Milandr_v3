#ifndef PACKAGE_H
#define PACKAGE_H

#include <QGraphicsItem>

class Package : public QGraphicsItem
{
public:
    Package();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    const int w = 200;
    const int h = 200;
};

#endif // PACKAGE_H
