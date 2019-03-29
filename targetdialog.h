#ifndef TARGETDIALOG_H
#define TARGETDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QVector>
#include <QJsonObject>
#include "classes/processor.h"

namespace Ui {
class TargetDialog;
}

class TargetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TargetDialog(QWidget *parent = nullptr);
    ~TargetDialog();

private:
    void fillCsvModel();
    void updateProcInfo(int );
    void addLabel(QString key, QString value, QString subV1 = "", QString subV2 = "");

public:
    Processor getProccessor();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_comboTargets_currentTextChanged(const QString &arg1);

    void on_comboPackage_currentIndexChanged(const QString &arg1);

private:
    int labelCounter;
    Ui::TargetDialog *ui;
    QStandardItemModel *csvModel;
    QJsonObject procSeriesList;
    QJsonObject selectedSeria;
    QString selectedMCU;
    QString selectTarget;
    QString selectPackage;

};

#endif // TARGETDIALOG_H
