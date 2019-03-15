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
    setTreeContent();
}

void MCUConfiguration::setTreeContent()
{
    treeModel.clear();
    QStandardItem *item;

    if (MCU.SPI != "-"){
        item = new QStandardItem();
        fillItem(item, "SPI", MCU.SPI);
        treeModel.appendRow(item);
    }

    if (MCU.ADC_channels != "-"){
        item = new QStandardItem();
        fillItem(item, "ADC", MCU.ADC_channels);
        treeModel.appendRow(item);
    }

    if (MCU.DAC_channels != "-"){
        item = new QStandardItem();
        fillItem(item, "DAC", MCU.DAC_channels);
        treeModel.appendRow(item);
    }

    if (MCU.Ethernet_MAC != "-"){
        treeModel.appendRow(new QStandardItem("Ethernet"));
    }

    ui->treeView->setModel(&treeModel);
}

void MCUConfiguration::fillItem(QStandardItem *item, QString title, QString data)
{
    item->setText(title);
    int number = data.toInt();
    for (int i = 0; i < number; i++){
        QStandardItem *subItem = new QStandardItem(title+QString::number(i));
        subItem->setCheckable(true);
        item->appendRow(subItem);
    }
}


