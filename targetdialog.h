#ifndef TARGETDIALOG_H
#define TARGETDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

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
    Ui::TargetDialog *ui;
    QStandardItemModel *csvModel;
};

#endif // TARGETDIALOG_H
