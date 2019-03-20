#ifndef PACKAGEVIEW_H
#define PACKAGEVIEW_H

#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>

class PackageView : public QGraphicsView
{
public:
    PackageView(QWidget *parent = nullptr);
protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    bool pressedKey;
};

#endif // PACKAGEVIEW_H
