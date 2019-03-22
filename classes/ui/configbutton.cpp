#include "configbutton.h"

#include <QMessageBox>

ConfigButton::ConfigButton(QWidget *parent)
    : QPushButton (parent)
{
}

ConfigButton::ConfigButton(const QString &text, QWidget *parent)
    : QPushButton (text,parent)
{
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

