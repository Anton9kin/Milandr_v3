#ifndef PINOUTS_H
#define PINOUTS_H

#include <QWidget>
#include <QGraphicsScene>
#include "../classes/ui/pin.h"

namespace Ui {
class PinOuts;
}

class PinOuts : public QWidget
{
    Q_OBJECT

public:
    explicit PinOuts(QWidget *parent = nullptr);
    ~PinOuts();

    void draw();

private:
    Ui::PinOuts *ui;
    QGraphicsScene *scene;
    QList<Pin*> listPins;
};

#endif // PINOUTS_H
