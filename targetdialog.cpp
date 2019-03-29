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
#define JSON_KEY_MEMORY     "Memory [kb]"
#define JSON_KEY_PINS       "Pins"
#define JSON_KEY_PARAMS     "Parameters"
#define JSON_KEY_PACKAGE    "Package"


TargetDialog::TargetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TargetDialog)
{
    ui->setupUi(this);

    labelCounter = 0;
    selectTarget = selectPackage = "";

    //create model
    csvModel = new QStandardItemModel(this);
    ui->tableView->setModel(csvModel);

    procSeriesList = Utils::getProcessorFromJson(":/data/info.json");

    //set data to comboTarget
    ui->comboTargets->addItems(procSeriesList.keys());

    //set data to comboPackage
    {
        QStringList packList;
        for (QString keyS : procSeriesList.keys()){
            const QJsonArray &mcuList = procSeriesList.value(keyS).toObject().value(JSON_KEY_MCU_LIST).toArray();
            for (int i = 0; i < mcuList.count(); i++){
                QString package = mcuList.at(i).toObject().value(JSON_KEY_PACKAGE).toString();
                if (!packList.contains(package) && (QString::compare(package, "none")!=0))
                    packList.append(package);
            }
        }
        ui->comboPackage->addItems(packList);
        ui->comboPackage->addItem("none");
    }

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

static void appendHeader(QStringList &header, QString key, const QJsonValue& value){
    if (value.isString())
        header.append(key);
    else{
        const QJsonObject &subVal = value.toObject();
        QStringList sL = subVal.keys();
        QString str = key;
        str += "\n";
        for (int i = 0; i < sL.length(); i++){
            str += sL[i];
            if ((i+1) < sL.length()){
                str += "/";
            }
        }

        header.append(str);
    }
}

static void appendList(QList<QStandardItem*> &list, const QJsonValue &value){
    if (value.isString())
        list.append(new QStandardItem(value.toString()));
    else{
        const QJsonObject &subVal = value.toObject();
        QStringList sL = subVal.keys();
        QString str;
        for (int i = 0; i < sL.length(); i++){
            str += subVal.value(sL[i]).toString();
            if ((i+1) < sL.length()){
                str += "/";
            }
        }
        list.append(new QStandardItem(str));
    }
}

void TargetDialog::fillCsvModel()
{
    csvModel->clear();
    //set model header
    QStringList headerModel;
    const QJsonObject &seria = procSeriesList.value(procSeriesList.keys().at(0)).toObject();
    const QJsonObject &mcu = seria.value(JSON_KEY_MCU_LIST).toArray().at(0).toObject();

    //get headet data from MCU_list and append it to table header
    for (QString key : mcu.keys()){
        appendHeader(headerModel, key, mcu.value(key));
    }

    //add pins and memory
    appendHeader(headerModel, JSON_KEY_PINS, seria.value(JSON_KEY_PARAMS).toObject().value(JSON_KEY_PINS));
    appendHeader(headerModel, JSON_KEY_MEMORY, seria.value(JSON_KEY_PARAMS).toObject().value(JSON_KEY_MEMORY));

    csvModel->setHorizontalHeaderLabels(headerModel);

    //clear all labels in left gridlayout
    QLayoutItem *item;
    while((item = ui->gridLayout->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }

    //filter by series
    QStringList list;
    if (selectTarget.isEmpty())
        list = procSeriesList.keys();
    else
        list.append(selectTarget);

    for (QString seria : list){
        //take seria
        const QJsonObject &obj = procSeriesList.value(seria).toObject();
        //take mcu_list
        const QJsonArray &mcuList = obj.value(JSON_KEY_MCU_LIST).toArray();

        //fill table
        for (int i = 0; i < mcuList.count(); i++){

            const QJsonObject &mcu = mcuList.at(i).toObject();
            QList<QStandardItem *> standartList;

            //filter by package
            if (!selectPackage.isEmpty() && QString::compare(mcu.value(JSON_KEY_PACKAGE).toString(),selectPackage)){
                continue;
            }

            for (QString headKey : mcu.keys()){
                appendList(standartList, mcu.value(headKey));
            }

            //add pins and memory
            appendList(standartList, obj.value(JSON_KEY_PARAMS).toObject().value(JSON_KEY_PINS));
            appendList(standartList, obj.value(JSON_KEY_PARAMS).toObject().value(JSON_KEY_MEMORY));

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

                if ((QString::compare(key, JSON_KEY_MEMORY) == 0) ||
                        (QString::compare(key, JSON_KEY_PINS) == 0)){
                    continue;
                }

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
    selectTarget = arg1;

    if (QString::compare(arg1, "All") == 0)
        selectTarget = "";

    fillCsvModel();
}

void TargetDialog::on_comboPackage_currentIndexChanged(const QString &arg1)
{
    selectPackage = arg1;

    if (QString::compare(arg1, "All") == 0)
        selectPackage = "";

    fillCsvModel();
}
