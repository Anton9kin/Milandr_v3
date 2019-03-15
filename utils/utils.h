#ifndef UTILS_H
#define UTILS_H

#include <QVector>
#include <QString>
#include "../classes/processor.h"


class Utils
{
public:
    Utils();
    ~Utils();

    static QVector<Processor> getProcessor(QString);
};

#endif // UTILS_H
