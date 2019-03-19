#include "processor.h"
#include <QStandardItem>
#include <QString>



static void fillItem(QStandardItem *item, QString title, QString value){
    item->setText(title);
    int iValue = 0;

    if (!value.contains('/')){
        iValue = value.toInt();

        for (int i = 0; i < iValue; i++){
            QString subTitle;
            if (iValue == 1)
                subTitle = QString("%1").arg(title);
            else
                subTitle = QString("%1%2").arg(title).arg(i);
            QStandardItem *subItem = new QStandardItem(subTitle);
            subItem->setCheckable(true);
            item->appendRow(subItem);
        }
    }else{
        QString subTitle;
        subTitle = QString("%1").arg(title);
        QStandardItem *subItem = new QStandardItem(subTitle);
        subItem->setCheckable(true);
        item->appendRow(subItem);
    }
}

//constructors
Processor::Processor()
{
    tb_data.clear();
    tb_periph.clear();
}

Processor::Processor(QStringList data){

    addToData(KEY_MCU,      data[0]);
    addToData(KEY_FREQ,     data[1]);
    addToPeriph(KEY_SPI,      data[2]);
    addToData(KEY_TMAX,     data[3]);
    addToData(KEY_TMIN,     data[4]);
    addToData(KEY_UMAX,     data[5]);
    addToData(KEY_UMIN,     data[6]);
    addToData(KEY_ADC_CH,   data[7]);
    addToData(KEY_ADC_DIG,  data[8]);
    addToData(KEY_PINS,     data[9]);
    addToData(KEY_RAM,     data[10]);
    addToData(KEY_ROM,     data[11]);
    addToData(KEY_DAC_CH,     data[12]);
    addToData(KEY_DAC_DIG,     data[13]);
    addToPeriph(KEY_ETH_MAC,     data[14]);
    addToData(KEY_ETH_PHY,     data[15]);
    addToData(KEY_PACKAGE,     data[16]);
    addToData(KEY_CORE,     data[17]);
    addToPeriph(KEY_TIM,     data[18]);
    addToPeriph(KEY_USART,     data[19]);
    addToPeriph(KEY_WDT,     data[20]);
    addToPeriph(KEY_IWDT,     data[21]);
    addToPeriph(KEY_SYSTICK,     data[22]);
    addToPeriph(KEY_MPU,     data[23]);
    addToPeriph(KEY_BKP,     data[24]);
    addToPeriph(KEY_POWER,     data[25]);
    addToPeriph(KEY_EBC,     data[26]);
    addToPeriph(KEY_USB,     data[27]);
    addToPeriph(KEY_CAN,     data[28]);
    addToPeriph(KEY_ADC,     data[29]);
    addToPeriph(KEY_DAC,     data[30]);
    addToPeriph(KEY_COMP,     data[31]);
    addToPeriph(KEY_I2C,     data[32]);
    addToPeriph(KEY_DMA,     data[33]);
    addToPeriph(KEY_SDIO,     data[34]);
    addToPeriph(KEY_52070,     data[35]);
    addToPeriph(KEY_18977,     data[36]);
    addToPeriph(KEY_28147,     data[37]);
}

void Processor::takeModel(QStandardItemModel& model)
{
    model.clear();
    QStandardItem *item;

    QHash<QString,QString>::iterator it = tb_periph.begin();

    for (;it != tb_periph.end(); ++it){
        //check what the peripheral is exist
        item = new QStandardItem();
        fillItem(item, it.key(), it.value());
        model.appendRow(item);
    }
}

QString Processor::getValue(QString key)
{
    if (tb_data.contains(key))
        return tb_data[key];

    if (tb_periph.contains(key))
        return tb_periph[key];

    return "";
}

void Processor::addToData(QString key, QString value)
{
    if (!value.isEmpty()){
        tb_data.insert(key, value);
    }
}

void Processor::addToPeriph(QString key, QString value)
{
    if (!value.isEmpty()){
        tb_periph.insert(key, value);
    }
}

//deconstructor
Processor::~Processor(){

}
