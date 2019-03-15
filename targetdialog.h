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
    void updateProcInfo(int );

public:
    Processor getProccessor();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::TargetDialog *ui;
    QStandardItemModel *csvModel;
    QVector<Processor> proccessorList;
    Processor curProc;
};

#endif // TARGETDIALOG_H
