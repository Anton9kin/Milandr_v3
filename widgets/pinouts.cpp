#include "pinouts.h"
#include "ui_pinouts.h"

PinOuts::PinOuts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PinOuts)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    draw();
}

PinOuts::~PinOuts()
{
    delete ui;
    delete scene;
}

void PinOuts::draw()
{
    auto *pa0 = new Pin("PA0", Pin::Pin_Horizontal);
    auto *pa1 = new Pin("PA1", Pin::Pin_Vertical);
    auto *pa2 = new Pin("PA2", Pin::Pin_Diagonal_NWSE);
    auto *pa3 = new Pin("PA3", Pin::Pin_Diagonal_SWNE);

    pa0->setPos(0,0);
    pa1->setPos(0,40);
    pa2->setPos(0,60);
    pa3->setPos(0,80);

    listPins.append(pa0);
    listPins.append(pa1);
    listPins.append(pa2);
    listPins.append(pa3);

    for(int i =0; i < listPins.size(); i++){
        scene->addItem(listPins.at(i));
    }
}

