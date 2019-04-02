#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QGraphicsView>

class CustomView : public QGraphicsView
{
    Q_OBJECT

public:
    CustomView(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;
    void scaleView(qreal scaleFactor);
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CUSTOMVIEW_H
