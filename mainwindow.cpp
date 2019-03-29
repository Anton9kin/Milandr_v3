#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>

#include "targetdialog.h"
#include "aboutdialog.h"

#define ADD_WIDTH   300
#define ADD_HEIGHT  100

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

    if (targetDialog.exec() == QDialog::Accepted){
        MCUConfig.setMCU(targetDialog.getProccessor());

        ui->stackedWidget->setCurrentWidget(&MCUConfig);
        this->setGeometry(this->x()-ADD_WIDTH/2, this->y()-ADD_HEIGHT/2, this->width()+ADD_WIDTH, this->height()+ADD_HEIGHT);
    }
}

void MainWindow::on_btn_Open_clicked()
{

}

void MainWindow::on_actionHome_triggered()
{
    ui->stackedWidget->setCurrentWidget(startUp);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog about;
    about.exec();
}
