#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QGraphicsView>
#include "pin.h"
#include "../processor.h"

class CustomView : public QGraphicsView
{
    Q_OBJECT

public:
    CustomView(QWidget *parent = nullptr);
    void draw(Processor *mcu = nullptr);
    void clear();

protected:
    void wheelEvent(QWheelEvent *event) override;
    void scaleView(qreal scaleFactor);

private:
    QGraphicsScene *scene;
    QList<Pin*> listPins;
};

#endif // CUSTOMVIEW_H
