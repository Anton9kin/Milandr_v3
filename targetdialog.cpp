#include "targetdialog.h"
#include "ui_targetdialog.h"
#include "utils/utils.h"

#include <QFile>
#include <QDebug>

TargetDialog::TargetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TargetDialog)
{
    ui->setupUi(this);

    //create model
    csvModel = new QStandardItemModel(this);
    ui->tableView->setModel(csvModel);

    proccessorList = Utils::getProcessor(":/data/micros.csv");

    //set model header
    QStringList headerModel;
    headerModel << "MCU" << "Package" << "RAM" << "ROM" << "IO";
    csvModel->setHorizontalHeaderLabels(headerModel);

    //set model content
    for (Processor proc : proccessorList){
        QList<QStandardItem *> standartList;
        standartList.append(new QStandardItem(proc.getValue(KEY_MCU)));
        standartList.append(new QStandardItem(proc.getValue(KEY_PACKAGE)));
        standartList.append(new QStandardItem(proc.getValue(KEY_RAM)));
        standartList.append(new QStandardItem(proc.getValue(KEY_ROM)));
        standartList.append(new QStandardItem(proc.getValue(KEY_PINS)));

        csvModel->insertRow(csvModel->rowCount(), standartList);
    }

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

    ui->tableView->selectRow(0);
    updateProcInfo(0);
}

TargetDialog::~TargetDialog()
{
    delete ui;
}

void TargetDialog::on_tableView_clicked(const QModelIndex &index)
{
    int row_index = index.row();
    updateProcInfo(row_index);
}

void TargetDialog::updateProcInfo(int i){

    curProc = proccessorList.at(i);
    ui->F_label->       setText(curProc.getValue(KEY_FREQ));
    ui->SPI_label->     setText(curProc.getValue(KEY_SPI));
    ui->Tmax_label->    setText(curProc.getValue(KEY_TMAX));
    ui->Tmin_label->    setText(curProc.getValue(KEY_TMIN));
    ui->Uccmax_label->  setText(curProc.getValue(KEY_UMAX));
    ui->Uccmin_label->  setText(curProc.getValue(KEY_UMIN));
    ui->ADCch_label->   setText(curProc.getValue(KEY_ADC_CH));
    ui->ADCdig_label->  setText(curProc.getValue(KEY_ADC_DIG));
    ui->DACch_label->   setText(curProc.getValue(KEY_DAC_CH));
    ui->DACdig_label->  setText(curProc.getValue(KEY_DAC_DIG));
    ui->EthMAC_label->  setText(curProc.getValue(KEY_ETH_MAC));
    ui->EthPHY_label->  setText(curProc.getValue(KEY_ETH_PHY));
    ui->Core_label->    setText(curProc.getValue(KEY_CORE));

}

Processor TargetDialog::getProccessor(){
    return curProc;
}

void TargetDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    on_tableView_clicked(index);
    accept();
}

