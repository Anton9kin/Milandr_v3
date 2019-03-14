#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>

#include "targetdialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_actionNew_project_triggered()
{
    on_btn_New_clicked();
}

void MainWindow::on_btn_New_clicked()
{
    TargetDialog targetDialog;
    targetDialog.setModal(true);
    targetDialog.exec();
}

void MainWindow::on_btn_Open_clicked()
{

}
