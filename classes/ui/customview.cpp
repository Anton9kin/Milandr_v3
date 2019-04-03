#include "customview.h"

#include <QGraphicsScene>
#include <QWheelEvent>
#include <math.h>

#include "package.h"

CustomView::CustomView(QWidget *parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
}

void CustomView::draw()
{
    clear();

    qreal hPack = 200;

    Package *pack = new Package;
    scene->addItem(pack);

    auto *p01 = new Pin("P01", Utils::View_Horizontal);
    auto *p02 = new Pin("P02", Utils::View_Vertical_SN);
    auto *p03 = new Pin("P03", Utils::View_Horizontal);
    auto *p04 = new Pin("P04", Utils::View_Vertical_NS);

    p01->setPos(-p01->width(), hPack/2 - p01->height()/2);
    p02->setPos(hPack/2 - p02->height()/2, 0);

    p03->setPos(hPack, hPack/2 - p03->height()/2);

    p04->setPos(hPack/2 + p04->height()/2, hPack);

    listPins.append(p01);
    listPins.append(p02);
    listPins.append(p03);
    listPins.append(p04);

    for(int i =0; i < listPins.size(); i++){
        scene->addItem(listPins.at(i));
    }
}

void CustomView::clear()
{
    while (!listPins.isEmpty()) {
        Pin *pin = listPins.first();
        delete pin;
    }
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


