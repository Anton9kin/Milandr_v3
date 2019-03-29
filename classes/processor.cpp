#include "processor.h"
#include <QStandardItem>
#include <QString>


static void fillItem (QStandardItem *parent, QString key, const QJsonValue &value, bool checkable = true){
    auto *child = new QStandardItem();

    if (value.isString()){
        child->setText(QString("%1 - %2").arg(key).arg(value.toString()));
        child->setCheckable(checkable);
    }
    else{
        child->setText(key);
        for (QString sKey : value.toObject().keys()){
            auto *sChild = new QStandardItem();
            sChild->setText(sKey);

            const QJsonValue& sValue = value.toObject().value(sKey);
            if (sValue.isString()){
                int num = sValue.toString().toInt();
                for (int i = 0; i < num; i++){
                    auto *ssChild = new QStandardItem();
                    if (num == 1)
                        ssChild->setText(QString("%1").arg(sKey));
                    else
                        ssChild->setText(QString("%1%2").arg(sKey).arg(i));

                    ssChild->setCheckable(checkable);
                    sChild->appendRow(ssChild);
                }
            }
            else{
                QStringList sValueKeysList = sValue.toObject().keys();
                for (QString ssKey : sValueKeysList){
                    auto *ssChild = new QStandardItem();
                    if (sValueKeysList.length() == 1)
                        ssChild->setText(QString("%1").arg(sKey));
                    else
                        ssChild->setText(QString("%1%2").arg(sKey).arg(ssKey));

                    ssChild->setCheckable(checkable);
                    sChild->appendRow(ssChild);
                }
            }
            child->appendRow(sChild);
        }
    }

    parent->appendRow(child);
}

//constructors
Processor::Processor()
{
}

//deconstructor
Processor::~Processor(){

}


void Processor::Model(QStandardItemModel& model)
{
    //clear current model
    model.clear();
    //set: Name
    auto* parent = new QStandardItem();
    parent->setText(data.value("MCU_list").toObject().value("MCU").toString());

    for (QString key : data.keys()){
        if ((QString::compare(key, "Interfaces") == 0) ||
            (QString::compare(key, "Peripherals") == 0))
        {
            fillItem(parent, key, data.value(key));
        }

    }

    model.appendRow(parent);
}

void Processor::insert(QString key, QJsonValue value)
{
    data.insert(key, value);
}

