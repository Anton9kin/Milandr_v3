#include "startupdialog.h"
#include "ui_startupdialog.h"

StartUpDialog::StartUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartUpDialog)
{
    ui->setupUi(this);
    mainWindow = new MainWindow();
}

StartUpDialog::~StartUpDialog()
{
    delete ui;
}

void StartUpDialog::on_pushButton_clicked()
{
    hide();
    mainWindow->show();
}

void StartUpDialog::on_pushButton_2_clicked()
{

}
