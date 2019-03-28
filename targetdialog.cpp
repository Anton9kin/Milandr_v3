#include "targetdialog.h"
#include "ui_targetdialog.h"
#include "utils/utils.h"

#include <QFile>
#include <QDebug>
#include <QLabel>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#define JSON_KEY_MCU_LIST   "MCU_list"

TargetDialog::TargetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TargetDialog)
{
    ui->setupUi(this);

    labelCounter = 0;

    //create model
    csvModel = new QStandardItemModel(this);
    ui->tableView->setModel(csvModel);

    procSeriesList = Utils::getProcessorFromJson(":/data/info.json");

    ui->comboTargets->addItems(procSeriesList.keys());

    //set model content
    fillCsvModel();

    //set width header column by content
    QHeaderView *header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);

    //resize mainwindow
    int w = ui->tableView->verticalHeader()->width();
    for (int i =0; i < ui->tableView->model()->columnCount(); i++) {
        w += ui->tableView->columnWidth(i);
    }
    w += ui->tableView->columnWidth(ui->tableView->model()->columnCount() - 1);
    int h = ui->tableView->horizontalHeader()->height()*2;
    for (int i = 0; i < ui->tableView->model()->rowCount(); i++){
        h += ui->tableView->rowHeight(i);
    }

    //ui->tableView->setMaximumSize(w, h);
    //ui->tableView->setMinimumSize(w, h);

    ui->tableView->setMaximumWidth(w);
    ui->tableView->setMinimumWidth(w);

    ui->tableView->selectRow(0);
    updateProcInfo(0);
}

TargetDialog::~TargetDialog()
{
    delete ui;
}

void TargetDialog::fillCsvModel(QString targets)
{
    csvModel->clear();
    //set model header
    QStringList headerModel;
    const QJsonObject &seria = procSeriesList.value(procSeriesList.keys().at(0)).toObject();
    const QJsonObject &mcu = seria.value(JSON_KEY_MCU_LIST).toArray().at(0).toObject();

    for (QString key : mcu.keys()){
        const QJsonValue &val = mcu.value(key);
        if (val.isString())
            headerModel.append(key);
        else{
            const QJsonObject &subVal = val.toObject();
            QStringList sL = subVal.keys();
            QString str = key;
            str += "\n";
            for (int i = 0; i < sL.length(); i++){
                str += sL[i];
                if ((i+1) < sL.length()){
                    str += "/";
                }
            }

            headerModel.append(str);
        }
    }

    csvModel->setHorizontalHeaderLabels(headerModel);

    //clear all labels in left gridlayout
    QLayoutItem *item;
    while((item = ui->gridLayout->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }

    //define list of series
    QStringList list;
    if (targets.isEmpty())
        list = procSeriesList.keys();
    else
        list.append(targets);

    for (QString seria : list){
        //take seria
        const QJsonObject &obj = procSeriesList.value(seria).toObject();
        //take mcu_list
        const QJsonArray &mcuList = obj.value(JSON_KEY_MCU_LIST).toArray();

        //fill table
        for (int i = 0; i < mcuList.count(); i++){

            const QJsonObject &mcu = mcuList.at(i).toObject();
            QList<QStandardItem *> standartList;

            for (QString headKey : mcu.keys()){
                const QJsonValue &val = mcu.value(headKey);
                if (val.isString())
                    standartList.append(new QStandardItem(val.toString()));
                else{
                    const QJsonObject &subVal = val.toObject();
                    QStringList sL = subVal.keys();
                    QString str;
                    for (int i = 0; i < sL.length(); i++){
                        str += subVal.value(sL[i]).toString();
                        if ((i+1) < sL.length()){
                            str += "/";
                        }
                    }
                    standartList.append(new QStandardItem(str));
                }
            }
            csvModel->insertRow(csvModel->rowCount(), standartList);
        }
    }

    if (csvModel->rowCount() != 0){
        ui->tableView->selectRow(0);
        updateProcInfo(0);
    }
}

void TargetDialog::on_tableView_clicked(const QModelIndex &index)
{
    int row_index = index.row();
    updateProcInfo(row_index);
}

void TargetDialog::updateProcInfo(int i){

    labelCounter = 0;
    QLayoutItem *item;
    while((item = ui->gridLayout->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }

    QStandardItem *row_mcu = csvModel->item(i, 0);
    selectedMCU = row_mcu->text();

    //searching proc name in list
    QStringList keySeries = procSeriesList.keys();
    QString foundSeria = "none";
    for (QString ser : keySeries){
        const QJsonObject &targets = procSeriesList.value(ser).toObject();
        const QJsonArray &mcuArray = targets.value(JSON_KEY_MCU_LIST).toArray();
        for (int i = 0; i < mcuArray.count(); i++){
            const QJsonValue mcuName = mcuArray.at(i).toObject().value("MCU");
            if (QString::compare(mcuName.toString(),selectedMCU) == 0){
                foundSeria = ser;
                break;
            }
        }
        if (QString::compare(foundSeria,"none") != 0)
            break;
    }

    //fill tree view
    selectedSeria = procSeriesList.value(foundSeria).toObject();

    for (QString key : selectedSeria.keys()){

        if (QString::compare(JSON_KEY_MCU_LIST, key) == 0)
            continue;

        const QJsonValue &jsValue = selectedSeria.value(key);
        if (jsValue.isString()){
            addLabel(key, jsValue.toString());
        }
        else{
            const QJsonObject &obj = jsValue.toObject();
            addLabel(key, "");
            for (QString key : obj.keys()){
                const QJsonValue &v = obj.value(key);
                if (v.isString())
                    addLabel(key,v.toString());
                else{
                    addLabel(key, QString::number(v.toObject().keys().length()));
                }
            }
        }
    }

}

void TargetDialog::addLabel(QString key, QString value, QString subV1, QString subV2)
{
    int h = 15;
    QFont font;
    font.setBold(true);

    QLabel *lKey = new QLabel(key);
    lKey->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lKey->setMaximumSize(100, h);
    lKey->setMinimumSize(100, h);
    lKey->setFont(font);

    if (value.isEmpty()){
        font.setItalic(true);
        font.setBold(false);
        lKey->setFont(font);
    }
    QLabel *lValue = new QLabel();
    lValue->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lValue->setMaximumSize(150, h);
    lValue->setMinimumSize(150, h);

    if (!subV1.isEmpty() || !subV2.isEmpty()){
        value += " [ ";
        if (!subV1.isEmpty())
            value += subV1;
        if (!subV2.isEmpty())
            value += ", " + subV2;
        value += " ]";
    }
    lValue->setText(value);

    ui->gridLayout->addWidget(lKey, labelCounter, 0);
    ui->gridLayout->addWidget(lValue, labelCounter, 1);
    ++labelCounter;
}

Processor TargetDialog::getProccessor(){

    Processor mcu;

    for (QString key : selectedSeria.keys()){
        if (QString::compare(key, "MCU_list") == 0)
            continue;

        mcu.insert(key, selectedSeria.value(key));
    }

    const QJsonArray &mcuList = selectedSeria.value("MCU_list").toArray();
    for (int i = 0; i < mcuList.count(); i++){
        const QJsonObject& obj = mcuList.at(i).toObject();
        QString name = obj.value("MCU").toString();
        if (QString::compare(name, selectedMCU) == 0){
            mcu.insert("MCU_list", obj);
            break;
        }
    }

    return mcu;
}

void TargetDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    on_tableView_clicked(index);
    accept();
}


void TargetDialog::on_comboTargets_currentTextChanged(const QString &arg1)
{
    QString targets = arg1;

    if (QString::compare(arg1, "All") == 0)
        targets = "";

    fillCsvModel(targets);
}
