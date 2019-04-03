#ifndef PIN_H
#define PIN_H

#include <QPainter>
#include <QGraphicsItem>
#include <QtGui>
#include "../../utils/utils.h"

class Pin : public QGraphicsItem
{
public:


    Pin(const QString &text = "", Utils::View_Orientation orient = Utils::View_Horizontal);

    bool Pressed;

    void setColor(Qt::GlobalColor color);
    void setText(const QString &t);
    void setOrientation(Utils::View_Orientation o);
    int width();
    int height();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    const int w = 60;
    const int h = 20;
    QString text;
    Utils::View_Orientation orientation;
    Qt::GlobalColor color;
};

#endif // PIN_H
