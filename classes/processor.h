#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QString>
#include <QStringList>
#include <QStandardItemModel>
#include <QHash>
#include <QJsonObject>

class Processor
{
private:
    QJsonObject data;

public:
    Processor();
    ~Processor();

    void Model(QStandardItemModel& model);

    void insert(QString key, QJsonValue value);

    QString Name();
    QString Package();
private:
};

#endif // PROCESSOR_H
