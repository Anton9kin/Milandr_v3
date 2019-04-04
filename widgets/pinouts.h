#ifndef PINOUTS_H
#define PINOUTS_H

#include <QWidget>
#include <QGraphicsScene>
#include "../classes/ui/pin.h"
#include "../classes/processor.h"
namespace Ui {
class PinOuts;
}

class PinOuts : public QWidget
{
    Q_OBJECT

public:
    explicit PinOuts(QWidget *parent = nullptr);
    ~PinOuts();

    void setMCU(Processor *mcu = nullptr);

private:
    Ui::PinOuts *ui;
};

#endif // PINOUTS_H
