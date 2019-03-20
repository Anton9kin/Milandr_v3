#ifndef PACKAGEVIEW_H
#define PACKAGEVIEW_H

#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>

class PackageView : public QGraphicsView
{
public:
    PackageView(QWidget *parent = nullptr);
    ~PackageView();

    void set(QString package);
protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

private:
    const qreal SCALE = 1.15;
    bool pressedKey;
    QGraphicsScene *scene;
    QGraphicsItem *packImage;
    QGraphicsTextItem *text;
    qreal scaleFactor;
};

#endif // PACKAGEVIEW_H
