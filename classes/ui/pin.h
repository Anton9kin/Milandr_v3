#ifndef PIN_H
#define PIN_H

#include <QPainter>
#include <QGraphicsItem>
#include <QtGui>

class Pin : public QGraphicsItem
{
public:
    enum Pin_Orientation{
        Pin_Horizontal,     //horizontal    (text from west to east)
        Pin_Vertical_NS,    //vertical      (text from north to south)
        Pin_Vertical_SN,    //vertical      (text from south to north)
        Pin_Diagonal_SWNE,  //diagonal      (text from south-west to north-east)
        Pin_Diagonal_NWSE,  //diagonal      (text from north-west to south-east)
    };

    Pin(const QString &text = "", Pin_Orientation orient = Pin_Horizontal);

    bool Pressed;

    void setColor(Qt::GlobalColor color);
    void setText(const QString &t);
    void setOrientation(Pin_Orientation o);
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
    Pin_Orientation orientation;
    Qt::GlobalColor color;
};

#endif // PIN_H
