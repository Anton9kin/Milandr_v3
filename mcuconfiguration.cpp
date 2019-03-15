#include "mcuconfiguration.h"
#include "ui_mcuconfiguration.h"

MCUConfiguration::MCUConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MCUConfiguration)
{
    ui->setupUi(this);
}

MCUConfiguration::~MCUConfiguration()
{
    delete ui;
}

void MCUConfiguration::setMCU(Processor mcu)
{
    this->MCU = mcu;
    QString message = "You chose " + MCU.MCU;
    ui->label->setText(message);
}
