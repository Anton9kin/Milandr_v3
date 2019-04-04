#include "pinouts.h"
#include "ui_pinouts.h"
#include "../classes/ui/package.h"


PinOuts::PinOuts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PinOuts)
{
    ui->setupUi(this);

    ui->packageView->draw();
}

PinOuts::~PinOuts()
{
    delete ui;
}

void PinOuts::setMCU(Processor *mcu)
{
    ui->packageView->draw(mcu);
}


