#include "mcuconfiguration.h"
#include "ui_mcuconfiguration.h"
#include <QPixmap>

MCUConfiguration::MCUConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MCUConfiguration)
{
    ui->setupUi(this);
    connect(&treeModel, SIGNAL(itemChanged(QStandardItem*)), SLOT(onItemChanged(QStandardItem*)));
}

MCUConfiguration::~MCUConfiguration()
{
    delete ui;
}

void MCUConfiguration::setMCU(Processor mcu)
{
    this->MCU = mcu;
    updatePackageView();
    setTreeContent();
}

void MCUConfiguration::setTreeContent()
{
    MCU.takeModel(treeModel);
    ui->treeView->setModel(&treeModel);
}

void MCUConfiguration::updateModel(QStandardItem *item)
{
    int rows = treeModel.rowCount();

    for (int r = 0 ; r < rows; r++){
        QStandardItem* parent = treeModel.item(r, 0);
        int cols = parent->rowCount();
        for (int c = 0; c < cols; c++){
            QStandardItem* child = parent->child(c, 0);
            if (child == item){
                if (item->checkState() == Qt::Checked){
                    if (parent->background() != Qt::green){
                        parent->setBackground(Qt::green);
                    }
                    break;
                }else{
                    if (parent->background() != Qt::white){
                        parent->setBackground(Qt::white);
                    }
                }
            }
        }
    }
}

void MCUConfiguration::updatePackageView()
{
    QString packagePath = QString(":/package/p_%1.png").arg(MCU.getValue(KEY_PACKAGE));
    QImage image(packagePath);
    item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFocus();

    scene->addItem(item);
    item->setScale(1);
}

void MCUConfiguration::onItemChanged(QStandardItem *item)
{
    updateModel(item);
}
