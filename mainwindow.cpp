#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>

static bool chooseProc = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //init windows with choose processor
    chProcWindow = new ChooseProcessor();
    connect(chProcWindow, &ChooseProcessor::mainWin, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *e){
    //if close by show another windows
    if (chooseProc){
        e->accept();
    }
    //if close programm
    else{
        e->ignore();
        on_actionExit_triggered();
    }
}

void MainWindow::on_actionExit_triggered()
{
    chooseProc = false;
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Attention", "Do you really want to exit from programm?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
        QApplication::quit();
}

void MainWindow::showChooseProcessorWindow(){
    chProcWindow->show();
    chooseProc = true;
    this->close();
}

void MainWindow::on_btn_newProject_clicked()
{
    showChooseProcessorWindow();
}

void MainWindow::on_actionNew_project_triggered()
{
    showChooseProcessorWindow();
}
