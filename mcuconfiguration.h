#ifndef MCUCONFIGURATION_H
#define MCUCONFIGURATION_H

#include <QWidget>
#include <QStandardItemModel>
#include <QGridLayout>

#include "classes/processor.h"
#include "classes/ui/configbutton.h"

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
    QVector<QString> listConfigButton;
    QGridLayout grid;

    void setTreeContent();
    void fillItem(QStandardItem*, QString, QString);
    void updateModel(QStandardItem*);
    void addConfig(QStandardItem*);
    void removeConfig(QStandardItem*);
};

#endif // MCUCONFIGURATION_H
