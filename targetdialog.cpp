#include "targetdialog.h"
#include "ui_targetdialog.h"
#include "utils/utils.h"

#include <QFile>
#include <QDebug>
#include <QLabel>
#include <QSpacerItem>

TargetDialog::TargetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TargetDialog)
{
    ui->setupUi(this);

    labelCounter = 0;

    //create model
    csvModel = new QStandardItemModel(this);
    ui->tableView->setModel(csvModel);

    proccessorList = Utils::getProcessor(":/data/micros.csv");

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
    headerModel << "MCU" << "Package" << "RAM" << "ROM" << "IO";
    csvModel->setHorizontalHeaderLabels(headerModel);

    QLayoutItem *item;
    while((item = ui->gridLayout->takeAt(0)) != nullptr){
        delete item->widget();
        delete item;
    }

    for (Processor proc : proccessorList){

        if (proc.getValue(KEY_MCU).contains(targets) || targets.isEmpty()){
            QList<QStandardItem *> standartList;

            standartList.append(new QStandardItem(proc.getValue(KEY_MCU)));
            standartList.append(new QStandardItem(proc.getValue(KEY_PACKAGE)));
            standartList.append(new QStandardItem(proc.getValue(KEY_RAM)));
            standartList.append(new QStandardItem(proc.getValue(KEY_ROM)));
            standartList.append(new QStandardItem(proc.getValue(KEY_PINS)));

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

    //QList<QStandardItem*> row = csvModel->item(i, 0);
    QStandardItem *row_mcu = csvModel->item(i, 0);
    QString mcu = row_mcu->text();


    for (Processor p : proccessorList){
        if (QString::compare(p.getValue(KEY_MCU), mcu) == 0)
        {
            curProc = p;
            break;
        }
    }

    addLabel("F [MHz]:", curProc.getValue(KEY_FREQ));
    addLabel(QString("%1 [C]:").arg(KEY_TMAX), curProc.getValue(KEY_TMAX));
    addLabel(QString("%1 [C]:").arg(KEY_TMIN), curProc.getValue(KEY_TMIN));
    addLabel(QString("%1 [V]:").arg(KEY_UMAX), curProc.getValue(KEY_UMAX));
    addLabel(QString("%1 [V]:").arg(KEY_UMIN), curProc.getValue(KEY_UMIN));
    addLabel(QString("%1:").arg(KEY_PINOUTS), curProc.getValue(KEY_PINOUTS));
    addLabel(QString("%1:").arg(KEY_CORE), curProc.getValue(KEY_CORE));
    addLabel(QString("%1 [ch, dig]:").arg(KEY_ADC), curProc.getValue(KEY_ADC), curProc.getValue(KEY_ADC_CH), curProc.getValue(KEY_ADC_DIG));
    addLabel(QString("%1 [ch, dig]:").arg(KEY_DAC), curProc.getValue(KEY_DAC), curProc.getValue(KEY_DAC_CH), curProc.getValue(KEY_DAC_DIG));
    addLabel(QString("%1:").arg(KEY_ETH_MAC), curProc.getValue(KEY_ETH_MAC));
    addLabel(QString("%1:").arg(KEY_ETH_PHY), curProc.getValue(KEY_ETH_PHY));

    addLabel(QString("%1:").arg(KEY_SPI), curProc.getValue(KEY_SPI));
    addLabel(QString("%1:").arg(KEY_USART), curProc.getValue(KEY_USART));
    addLabel(QString("%1:").arg(KEY_USB), curProc.getValue(KEY_USB));
    addLabel(QString("%1:").arg(KEY_CAN), curProc.getValue(KEY_CAN));
    addLabel(QString("%1:").arg(KEY_I2C), curProc.getValue(KEY_I2C));
    addLabel(QString("%1:").arg(KEY_SDIO), curProc.getValue(KEY_SDIO));
    addLabel(QString("%1:").arg(KEY_EBC), curProc.getValue(KEY_EBC));
    addLabel(QString("%1:").arg(KEY_52070), curProc.getValue(KEY_52070));
    addLabel(QString("%1:").arg(KEY_18977), curProc.getValue(KEY_18977));
    addLabel(QString("%1:").arg(KEY_28147), curProc.getValue(KEY_28147));
    addLabel(QString("%1:").arg(KEY_CACHE), curProc.getValue(KEY_CACHE));
    addLabel(QString("%1:").arg(KEY_SPACE_WIRE), curProc.getValue(KEY_SPACE_WIRE));
    addLabel(QString("%1:").arg(KEY_CCSDS), curProc.getValue(KEY_CCSDS));
    addLabel(QString("%1:").arg(KEY_ECC), curProc.getValue(KEY_ECC));
    addLabel(QString("%1:").arg(KEY_CRC), curProc.getValue(KEY_CRC));

    addLabel(QString("%1:").arg(KEY_TIM), curProc.getValue(KEY_TIM));
    addLabel(QString("%1:").arg(KEY_SYSTICK), curProc.getValue(KEY_SYSTICK));
    addLabel(QString("%1:").arg(KEY_WDT), curProc.getValue(KEY_WDT));
    addLabel(QString("%1:").arg(KEY_IWDT), curProc.getValue(KEY_IWDT));
    addLabel(QString("%1:").arg(KEY_MPU), curProc.getValue(KEY_MPU));
    addLabel(QString("%1:").arg(KEY_COMP), curProc.getValue(KEY_COMP));
    addLabel(QString("%1:").arg(KEY_BKP), curProc.getValue(KEY_BKP));
    addLabel(QString("%1:").arg(KEY_POWER), curProc.getValue(KEY_POWER));
    addLabel(QString("%1:").arg(KEY_DMA), curProc.getValue(KEY_DMA));

}

void TargetDialog::addLabel(QString key, QString value, QString subV1, QString subV2)
{
    int h = 15;

    if (!value.isEmpty()){
        QLabel *lKey = new QLabel(key);
        lKey->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        lKey->setMaximumSize(100, h);
        lKey->setMinimumSize(100, h);
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
}

Processor TargetDialog::getProccessor(){
    return curProc;
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
    else {
        targets = arg1.mid(1, arg1.length()-2);
    }

    fillCsvModel(targets);
}
