#include "chooseprocessor.h"
#include "ui_chooseprocessor.h"
#include <QCloseEvent>

ChooseProcessor::ChooseProcessor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseProcessor)
{
    ui->setupUi(this);
}

ChooseProcessor::~ChooseProcessor()
{
    delete ui;
}

void ChooseProcessor::closeEvent(QCloseEvent *e){
    e->accept();
    emit mainWin();
}
