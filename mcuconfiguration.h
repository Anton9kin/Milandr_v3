#ifndef MCUCONFIGURATION_H
#define MCUCONFIGURATION_H

#include <QWidget>
#include <QStandardItemModel>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtGui>

#include "classes/processor.h"

namespace Ui {
class MCUConfiguration;
}

class MCUConfiguration : public QWidget
{
    Q_OBJECT

signals:
   void  itemChanged(QStandardItem *item);

public slots:
    void onItemChanged(QStandardItem*);

public:
    explicit MCUConfiguration(QWidget *parent = nullptr);
    ~MCUConfiguration();

    void setMCU(Processor mcu);

private:
    Ui::MCUConfiguration *ui;
    QStandardItemModel treeModel;
    Processor MCU;

    QGraphicsScene *scene;
    QGraphicsItem *item;

    void setTreeContent();
    void fillItem(QStandardItem*, QString, QString);
    void updateModel(QStandardItem*);
    void updatePackageView();
};

#endif // MCUCONFIGURATION_H
