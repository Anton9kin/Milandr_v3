#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFile>
#include <QDebug>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    } else {
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
/*
    for (int i = 0; i < 18; i++){
        ui->tableView->setColumnWidth(i, QHeaderView::ResizeToContents);
    }
    */
}

MainWindow::~MainWindow()
{
    delete ui;
    delete csvModel;
}

void MainWindow::closeEvent(QCloseEvent *e){
    e->ignore();
    on_actionExit_triggered();
}

void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Attention", "Do you really want to exit from programm?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
        QApplication::quit();
}
