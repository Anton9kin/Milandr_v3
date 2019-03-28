#include "mcuconfiguration.h"
#include "ui_mcuconfiguration.h"
#include <QPixmap>

#define SELECTED     Qt::green
#define UNSELECTED   Qt::white

MCUConfiguration::MCUConfiguration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MCUConfiguration)
{
    ui->setupUi(this);
    connect(&treeModel, SIGNAL(itemChanged(QStandardItem*)), SLOT(onItemChanged(QStandardItem*)));
    ui->widget->setLayout(&grid);
}

MCUConfiguration::~MCUConfiguration()
{
    delete ui;
}

void MCUConfiguration::setMCU(const Processor &mcu)
{
    //set current model
    this->MCU = mcu;
    //set left tree view
    setTreeContent();
}

void MCUConfiguration::setTreeContent()
{
    //get view model from processor
    MCU.Model(treeModel);
    //set model to tree
    ui->treeView->setModel(&treeModel);
    ui->treeView->setHeaderHidden(true);
    ui->treeView->expandAll();
}

void MCUConfiguration::updateModel(QStandardItem *item)
{
    bool childrenIsChecked = false;

    //find parent
    QStandardItem *parent = item->parent();
    if (parent == nullptr)
        return;

    //Is one of the children checked?
    int cols = parent->rowCount();
    for (int c = 0; c < cols; c++){
        QStandardItem* child = parent->child(c, 0);
        if (child->checkState() == Qt::Checked){
            childrenIsChecked = true;
        }
    }

    //if one of the children is selected the set color for parent
    if (childrenIsChecked){
        parent->setBackground(SELECTED);
        addConfig(parent);
    }
    else{
        parent->setBackground(UNSELECTED);
        removeConfig(parent);
    }
}

void MCUConfiguration::addConfig(QStandardItem *config)
{
    if (!listConfigButton.contains(config->text())){
        listConfigButton.append(config->text());

        auto *but = new ConfigButton(config->text());
        grid.addWidget(but);
    }
}

void MCUConfiguration::removeConfig(QStandardItem *config)
{
    if (listConfigButton.contains(config->text())){
        listConfigButton.remove(listConfigButton.indexOf(config->text()));

        for (int i = 0; i < grid.count(); i++){
            ConfigButton *but = qobject_cast<ConfigButton*>(grid.itemAt(i)->widget());

            if (but->text() == config->text()){
                but->hide();
                delete but;
            }
        }
    }
}



void MCUConfiguration::onItemChanged(QStandardItem *item)
{
    updateModel(item);
}
