#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QString>
#include <QStringList>

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


public:
    Processor();
    ~Processor();
    Processor(QStringList);


};

#endif // PROCESSOR_H
