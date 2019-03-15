#include "processor.h"

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
}

//deconstructor
Processor::~Processor(){

}
