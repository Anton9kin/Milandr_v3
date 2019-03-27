#ifndef UTILS_H
#define UTILS_H

#include <QJsonValue>
#include <QString>


class Utils
{
public:
    Utils();
    ~Utils();

    static QJsonObject getProcessorFromJson(const QString &filename);
};

#endif // UTILS_H
