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

private:
    Ui::PinOuts *ui;
};

#endif // PINOUTS_H
