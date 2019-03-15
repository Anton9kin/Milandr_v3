#ifndef MCUCONFIGURATION_H
#define MCUCONFIGURATION_H

#include <QWidget>
#include "classes/processor.h"

namespace Ui {
class MCUConfiguration;
}

class MCUConfiguration : public QWidget
{
    Q_OBJECT

public:
    explicit MCUConfiguration(QWidget *parent = nullptr);
    ~MCUConfiguration();

    void setMCU(Processor mcu);

private:
    Ui::MCUConfiguration *ui;
    Processor MCU;




};

#endif // MCUCONFIGURATION_H
