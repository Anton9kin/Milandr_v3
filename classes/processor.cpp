#include "processor.h"
#include <QStandardItem>
#include <QString>

#define TITLE_SPI   "SPI"
#define TITLE_ADC   "ADC"
#define TITLE_DAC   "DAC"
#define TITLE_TIM   "TIMER"
#define TITLE_USART   "USART"
#define TITLE_WDT   "WDT"
#define TITLE_IWDT   "IWDT"
#define TITLE_SYSTICK   "SYSTICK"
#define TITLE_MPU   "MPU"
#define TITLE_BKP   "BackUp"
#define TITLE_POWER   "Power"
#define TITLE_EBC   "EBC"
#define TITLE_USB   "USB"
#define TITLE_CAN   "CAN"
#define TITLE_COMP   "COMP"
#define TITLE_I2C   "I2C"
#define TITLE_DMA   "DMA"
#define TITLE_ETH_MAC   "Ethernet"

static void fillItem(QStandardItem *item, QString title, QString value){
    item->setText(title);
    int iValue = value.toInt();
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
}

//constructors
Processor::Processor()
{

}

Processor::Processor(QStringList data){
    MCU = data[0];
    Freq = data[1];
    SPI = data[2];
    Tmax = data[3];
    Tmin = data[4];
    Ucc_max = data[5];
    Ucc_min = data[6];
    ADC_channels = data[7];
    ADC_digits = data[8];
    Pins = data[9];
    RAM = data[10];
    ROM = data[11];
    DAC_channels = data[12];
    DAC_digits = data[13];
    Ethernet_MAC = data[14];
    Ethernet_PHY = data[15];
    Package = data[16];
    Core = data[17];
    Timer = data[18];
    Usart = data[19];
    WDT = data[20];
    IWDT = data[21];
    SysTick = data[22];
    MPU = data[23];
    BackUP = data[24];
    Power = data[25];
    EBC = data[26];
    USB = data[27];
    CAN = data[28];
    ADC = data[29];
    DAC = data[30];
    COMP = data[31];
    I2C = data[32];
    DMA = data[33];
}

void Processor::takeModel(QStandardItemModel& model)
{
    model.clear();
    QStandardItem *item;

    if (QString::compare(SPI,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_SPI, SPI);
        model.appendRow(item);
    }

    if (QString::compare(ADC,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_ADC, ADC);
        model.appendRow(item);
    }

    if (QString::compare(DAC,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_DAC, DAC);
        model.appendRow(item);
    }

    if (QString::compare(Timer,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_TIM, Timer);
        model.appendRow(item);
    }

    if (QString::compare(Usart,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_USART, Usart);
        model.appendRow(item);
    }

    if (QString::compare(WDT,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_WDT, WDT);
        model.appendRow(item);
    }

    if (QString::compare(IWDT,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_IWDT, IWDT);
        model.appendRow(item);
    }

    if (QString::compare(SysTick,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_SYSTICK, SysTick);
        model.appendRow(item);
    }

    if (QString::compare(MPU,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_MPU, MPU);
        model.appendRow(item);
    }

    if (QString::compare(BackUP,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_BKP, BackUP);
        model.appendRow(item);
    }

    if (QString::compare(Power,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_POWER, Power);
        model.appendRow(item);
    }

    if (QString::compare(EBC,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_EBC, EBC);
        model.appendRow(item);
    }

    if (QString::compare(USB,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_USB, USB);
        model.appendRow(item);
    }

    if (QString::compare(CAN,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_CAN, CAN);
        model.appendRow(item);
    }

    if (QString::compare(COMP,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_COMP, COMP);
        model.appendRow(item);
    }

    if (QString::compare(I2C,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_I2C, I2C);
        model.appendRow(item);
    }

    if (QString::compare(DMA,"-") != 0){
        item = new QStandardItem();
        fillItem(item, TITLE_DMA, DMA);
        model.appendRow(item);
    }

    if (QString::compare(Ethernet_MAC,"-") != 0){
        model.appendRow(new QStandardItem(TITLE_ETH_MAC));
    }

}

//deconstructor
Processor::~Processor(){

}
