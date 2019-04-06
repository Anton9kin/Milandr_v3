#ifndef PIN_H
#define PIN_H

#include <QPainter>
#include <QGraphicsItem>
#include <QtGui>
#include <QGraphicsSceneContextMenuEvent>
#include "../../utils/utils.h"

class Pin : public QGraphicsItem
{
public:


    Pin(const QString &text = "", Utils::View_Orientation orient = Utils::View_Horizontal, QPointF pos = QPointF(0,0));

    bool Pressed;

    void setText(const QString &t);
    void setOrientation(Utils::View_Orientation o);
    void addToValueList(QString initText);
    void addToValueList(QList<QString> list);
    int width();
    int height();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    const int w = 50;
    const int h = 20;
    QString text;
    QString initText;
    Utils::View_Orientation orientation;
    Qt::GlobalColor color;
    QList<QString> valueList;
};

#endif // PIN_H
