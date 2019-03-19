#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QString>
#include <QStringList>
#include <QStandardItemModel>

class Processor
{
public:
    QString MCU;
    QString Freq;
    QString SPI;
    QString Tmax;
    QString Tmin;
    QString Ucc_max;
    QString Ucc_min;
    QString ADC_channels;
    QString ADC_digits;
    QString Pins;
    QString RAM;
    QString ROM;
    QString DAC_channels;
    QString DAC_digits;
    QString Ethernet_MAC;
    QString Ethernet_PHY;
    QString Package;
    QString Core;
    QString Timer;
    QString Usart;
    QString WDT;
    QString IWDT;
    QString SysTick;
    QString MPU;
    QString BackUP;
    QString Power;
    QString EBC;
    QString USB;
    QString CAN;
    QString ADC;
    QString DAC;
    QString COMP;
    QString I2C;
    QString DMA;


public:
    Processor();
    ~Processor();
    Processor(QStringList);

    void takeModel(QStandardItemModel& model);

};

#endif // PROCESSOR_H
