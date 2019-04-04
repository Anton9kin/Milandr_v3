#ifndef PACKAGE_H16_48_1B_H
#define PACKAGE_H16_48_1B_H

#include "package.h"
#include "../processor.h"
class Package_H16_48_1B : public Package
{
public:
    Package_H16_48_1B(Processor *mcu = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void setPoints();

};

#endif // PACKAGE_H16_48_1B_H
