#ifndef TARGETDIALOG_H
#define TARGETDIALOG_H

#include "classes/processor.h"

#include <QDialog>
#include <QStandardItemModel>
#include <QVector>


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
    void fillCsvModel(QString targets = "");
    void updateProcInfo(int );
    void addLabel(QString key, QString value, QString subV1 = "", QString subV2 = "");

public:
    Processor getProccessor();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_comboTargets_currentTextChanged(const QString &arg1);

private:
    int labelCounter;
    Ui::TargetDialog *ui;
    QStandardItemModel *csvModel;
    QVector<Processor> proccessorList;
    Processor curProc;
};

#endif // TARGETDIALOG_H
