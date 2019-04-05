#include "customview.h"

#include <QGraphicsScene>
#include <QWheelEvent>
#include <math.h>

#include "package_h16_48_1b.h"

CustomView::CustomView(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
}

void CustomView::draw(Processor *mcu)
{
    clear();

    if (mcu == nullptr)
        return;

    if (QString::compare("Н16.48-1В", mcu->Package()) == 0)
        drawPackage_H16_48(mcu);
    else{
        auto *pack = new Package();
        scene->addItem(pack);
    }

}

void CustomView::clear()
{
    listPins.clear();
}



void CustomView::wheelEvent(QWheelEvent *e){

    if (e->delta() > 0)
        scale(1.15, 1.15);
    else
        scale(1/1.15, 1/1.15);
}

void CustomView::scaleView(qreal scaleFactor){
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void CustomView::drawPackage_H16_48(Processor *mcu)
{
    auto *pack = new Package_H16_48_1B(mcu);
    scene->addItem(pack);

    for (int i = 0; i < 48; i++){
        auto *p = new Pin(QString("P%1").arg(i+1,2,10, QChar('0')), pack->getPinOrientation(i+1), pack->getPinPos(i+1));
        listPins.append(p);
    }

    for(int i =0; i < listPins.size(); i++){
        scene->addItem(listPins.at(i));
    }
}


