#include "packageview.h"

PackageView::PackageView(QWidget *parent) : QGraphicsView(parent)
{
    pressedKey = false;
}

void PackageView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.15;

    if (pressedKey){
        if (event->delta() > 0){
            scale(scaleFactor, scaleFactor);
        }else {
            scale(1/scaleFactor, 1/scaleFactor);
        }
    }

}

void PackageView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
        pressedKey = true;
}

void PackageView::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
        pressedKey = false;
}
