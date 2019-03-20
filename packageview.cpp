#include "packageview.h"

PackageView::PackageView(QWidget *parent) : QGraphicsView(parent)
{
    pressedKey = false;
    scene = new QGraphicsScene();
    packImage = nullptr;
    text = nullptr;
    scaleFactor = SCALE;
}

PackageView::~PackageView()
{
    delete this->packImage;
    delete this->scene;
}

void PackageView::set(QString package)
{
    delete packImage;

    setScene(scene);
    setFocus();

    QString packagePath = QString(":/package/p_%1.png").arg(package);
    QImage image(packagePath);
    packImage = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    packImage->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(packImage);
}

void PackageView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    if (pressedKey){
        if (event->delta() > 0){
            scaleFactor *= SCALE;
            packImage->setScale(scaleFactor);
        }else {
            scaleFactor /= SCALE;
            packImage->setScale(scaleFactor);
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

void PackageView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        delete text;
        text = scene->addText(QString("x=%1, y=%2").arg(event->x()).arg(event->y()));
    }
}
