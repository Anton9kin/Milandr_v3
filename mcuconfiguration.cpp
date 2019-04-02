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
    ui->tabWidget->addTab(&pinWidget, "PinWindget");
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

    if (item->checkState() == Qt::Checked)
        addConfig(item);
    else
        removeConfig(item);

    //if one of the children is selected the set color for parent
    if (childrenIsChecked){
        parent->setBackground(SELECTED);
        //addConfig(parent);
    }
    else{
        parent->setBackground(UNSELECTED);
        //removeConfig(parent);
    }
}

void MCUConfiguration::addConfig(QStandardItem *config)
{
    QString text = config->text();
    int row = 0;
    ConfigButton *but;

    for(QString conf : listConfigButton){
        if (QString::compare(text.left(text.length()-1), conf.left(conf.length()-1)) == 0){
            break;
        }
        ++row;
    }

    if (!listConfigButton.contains(text)){
        listConfigButton.append(text);

        for (int i = 0; i < grid.columnCount(); i++){
            QLayoutItem *item = grid.itemAtPosition(row, i);
            if (item == nullptr)
            {
                but = new ConfigButton(text);
                grid.addWidget(but, row, i);
                return;
            }
        }

        but = new ConfigButton(text);
        grid.addWidget(but, row, grid.columnCount());
    }
}

void MCUConfiguration::removeConfig(QStandardItem *config)
{
    QString text = config->text();
    if (listConfigButton.contains(text)){
        listConfigButton.remove(listConfigButton.indexOf(text));

        for (int i = 0; i < grid.count(); i++){
            ConfigButton *but = qobject_cast<ConfigButton*>(grid.itemAt(i)->widget());

            if ( QString::compare(but->text(),text) == 0){
                but->hide();
                delete but;
            }
        }
    }
}



void MCUConfiguration::onItemChanged(QStandardItem *item)
{
    if (item->isCheckable())
        updateModel(item);
}
