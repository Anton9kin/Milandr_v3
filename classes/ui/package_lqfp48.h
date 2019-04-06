#ifndef PACKAGE_LQFP48_H
#define PACKAGE_LQFP48_H

#include "package.h"
#include "../processor.h"

class Package_LQFP48 : public Package
{
public:
    Package_LQFP48(Processor *mcu = nullptr);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void setPoints();

};

#endif // PACKAGE_LQFP48_H
