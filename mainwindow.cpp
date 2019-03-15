#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>

#include "targetdialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    startUp = ui->stackedWidget->widget(0);

    ui->stackedWidget->addWidget(&MCUConfig);
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

    if (targetDialog.exec() == QDialog::Accepted){
        MCUConfig.setMCU(targetDialog.getProccessor());

        ui->stackedWidget->setCurrentWidget(&MCUConfig);
    }
}

void MainWindow::on_btn_Open_clicked()
{

}

void MainWindow::on_actionHome_triggered()
{
    ui->stackedWidget->setCurrentWidget(startUp);
}
