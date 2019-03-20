#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QString>
#include <QStringList>
#include <QStandardItemModel>
#include <QHash>

#define KEY_MCU         "MCU"
#define KEY_FREQ        "FREQ"
#define KEY_SPI         "SPI"
#define KEY_TMAX        "TMAX"
#define KEY_TMIN        "TMIN"
#define KEY_UMAX        "UccMAX"
#define KEY_UMIN        "UccMIN"
#define KEY_ADC         "ADC"
#define KEY_ADC_DIG     "ADC_DG"
#define KEY_ADC_CH      "ADC_CH"
#define KEY_PINS        "PINS"
#define KEY_ROM         "ROM"
#define KEY_RAM         "RAM"
#define KEY_DAC         "DAC"
#define KEY_DAC_DIG     "DAC_DIG"
#define KEY_DAC_CH      "DAC_CH"
#define KEY_ETH_MAC     "ETHERNET_MAC"
#define KEY_ETH_PHY     "ETHERNET_PHY"
#define KEY_PACKAGE     "PACKAGE"
#define KEY_CORE        "CORE"
#define KEY_TIM         "TIMER"
#define KEY_USART       "USART"
#define KEY_WDT         "WDT"
#define KEY_IWDT        "IWDT"
#define KEY_SYSTICK     "SYSTICK"
#define KEY_MPU         "MPU"
#define KEY_BKP         "BACKUP"
#define KEY_POWER       "POWER"
#define KEY_EBC         "EBC"
#define KEY_USB         "USB"
#define KEY_CAN         "CAN"
#define KEY_COMP        "COMP"
#define KEY_I2C         "I2C"
#define KEY_DMA         "DMA"
#define KEY_SDIO        "SDIO"
#define KEY_52070       "ГОСТ Р 52070-2003 (1553)"
#define KEY_18977       "ГОСТ 18977-79 (ARINC)"
#define KEY_28147       "ГОСТ 28147-89"
#define KEY_CACHE       "CACHE"
#define KEY_SPACE_WIRE  "SPACE_WIRE"
#define KEY_CCSDS       "CCSDS"
#define KEY_ECC         "ECC"
#define KEY_CRC         "CRC"
#define KEY_PINOUTS     "PINOUTS"

class Processor
{
private:
    QHash<QString, QString> tb_periph;
    QHash<QString, QString> tb_data;

public:
    Processor();
    ~Processor();
    Processor(QStringList);

    void takeModel(QStandardItemModel& model);
    QString getValue(QString key);

private:
    void addToData(QString key, QString value);
    void addToPeriph(QString key, QString value);
};

#endif // PROCESSOR_H
