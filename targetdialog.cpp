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
        standartList.append(new QStandardItem(proc.MCU));
        standartList.append(new QStandardItem(proc.Package));
        standartList.append(new QStandardItem(proc.RAM));
        standartList.append(new QStandardItem(proc.ROM));
        standartList.append(new QStandardItem(proc.Pins));

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
    ui->F_label->setText(curProc.Freq);
    ui->SPI_label->setText(curProc.SPI);
    ui->Tmax_label->setText(curProc.Tmax);
    ui->Tmin_label->setText(curProc.Tmin);
    ui->Uccmax_label->setText(curProc.Ucc_max);
    ui->Uccmin_label->setText(curProc.Ucc_min);
    ui->ADCch_label->setText(curProc.ADC_channels);
    ui->ADCdig_label->setText(curProc.ADC_digits);
    ui->DACch_label->setText(curProc.DAC_channels);
    ui->DACdig_label->setText(curProc.DAC_digits);
    ui->EthMAC_label->setText(curProc.Ethernet_MAC);
    ui->EthPHY_label->setText(curProc.Ethernet_PHY);
    ui->Core_label->setText(curProc.Core);

}

Processor TargetDialog::getProccessor(){
    return curProc;
}
