#include "utils.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Utils::Utils()
{

}

Utils::~Utils(){

}

QJsonObject Utils::getProcessorFromJson(const QString &filename)
{
    QJsonValue procSeriesList;
    QJsonObject root;
    QString byteArray;
    //open resource file
    //and read it
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "File isn't exists";
    }
    //fill
    else {
        byteArray = file.readAll();
        file.close();

        QJsonDocument document = QJsonDocument::fromJson(byteArray.toUtf8());
        //get root object
        root = document.object();
        QStringList keyRoot = root.keys();
        procSeriesList = root.value(keyRoot.at(0));
    }

    return procSeriesList.toObject();
}
