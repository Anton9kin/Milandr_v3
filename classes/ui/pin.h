#ifndef PIN_H
#define PIN_H

#include <QPainter>
#include <QGraphicsItem>
#include <QtGui>

class Pin : public QGraphicsTextItem
{
public:
    enum Pin_Orientation{
        Pin_Horizontal,
        Pin_Vertical,
        Pin_Diagonal_SWNE,
        Pin_Diagonal_NWSE,
    };

    Pin(const QString &text = "", Pin_Orientation orient = Pin_Horizontal);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool Pressed;

    void setColor(Qt::GlobalColor color);
    void setText(const QString &t);
    void setOrientation(Pin_Orientation o);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QString text;
    Pin_Orientation orientation;
    Qt::GlobalColor color;
};

#endif // PIN_H
