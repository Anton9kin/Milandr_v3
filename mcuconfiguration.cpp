#include "mcuconfiguration.h"
#include "ui_mcuconfiguration.h"

MCUConfiguration::MCUConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MCUConfiguration)
{
    ui->setupUi(this);
    connect(&treeModel, SIGNAL(itemChanged(QStandardItem*)), SLOT(onItemChanged(QStandardItem*)));
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
    MCU.takeModel(treeModel);
    ui->treeView->setModel(&treeModel);
}

void MCUConfiguration::onItemChanged(QStandardItem *item)
{
    QFont font;
    if (item->checkState() == Qt::Checked){
        font.setBold(true);
        item->setFont(font);
    }else {
        font.setBold(false);
        item->setFont(font);
    }
}
