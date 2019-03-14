#include "targetdialog.h"
#include "ui_targetdialog.h"

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

    //open resource file
    //and read it
    QFile file(":/data/micros.csv");
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "File isn't exists";
    }
    //fill table view
    else {
        //create stream
        QTextStream in(&file);
        bool header = true;
        //read for end file
        while(!in.atEnd()){
            //line by line
            QString line = in.readLine();
            //add model to line
            QList<QStandardItem *> standartItemList;
            QStringList headerList;
            //means that line split with ;
            for (QString item : line.split(";")){
                //create string list for table header
                if (header)
                    headerList << item;
                else
                    standartItemList.append(new QStandardItem(item));
            }
            //for header
            if (header){
                header = false;
                csvModel->setHorizontalHeaderLabels(headerList);
            }else{
                csvModel->insertRow(csvModel->rowCount(), standartItemList);
            }
        }
        file.close();
    }

    //set width header column by content
    QHeaderView *header = ui->tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);

    //resize mainwindow
    int w = ui->tableView->verticalHeader()->width() + 6;
    for (int i =0; i < ui->tableView->model()->columnCount(); i++) {
        w += ui->tableView->columnWidth(i);
    }
    int h = ui->tableView->horizontalHeader()->height() + 6;
    for (int i = 0; i < ui->tableView->model()->rowCount(); i++){
        h += ui->tableView->rowHeight(i);
    }

    ui->tableView->setMaximumSize(w, h);
    ui->tableView->setMinimumSize(w, h);

    this->resize(w, h);
}

TargetDialog::~TargetDialog()
{
    delete ui;
}
