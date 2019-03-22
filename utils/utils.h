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

    static QVector<Processor> getProcessor(const QString &filename);
};

#endif // UTILS_H
