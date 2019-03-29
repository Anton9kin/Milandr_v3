#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QMessageBox>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
    QImage image(":images/logo_Milandr.jpg");
    if (!image.isNull()){
        ui->imageLabel->setPixmap(QPixmap::fromImage(image));
        ui->imageLabel->setScaledContents(true);
    }

}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_pushButton_clicked()
{
    accept();
}
