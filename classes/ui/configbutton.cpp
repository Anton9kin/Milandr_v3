#include "configbutton.h"

#include <QMessageBox>

ConfigButton::ConfigButton(QWidget *parent)
    : QPushButton (parent)
{
    this->setGeometry(this->x(), this->y(),this->width(),this->height()+20);
}

ConfigButton::ConfigButton(const QString &text, QWidget *parent)
    : QPushButton (text,parent)
{
    this->setGeometry(this->x(), this->y(),this->width(),this->height()+20);
}


ConfigButton::~ConfigButton()
{

}

void ConfigButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton){
        QMessageBox::information(this, text(), "You pressed me!");
    }
}

