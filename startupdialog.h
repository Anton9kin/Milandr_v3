#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class StartUpDialog;
}

class StartUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartUpDialog(QWidget *parent = nullptr);
    ~StartUpDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void mainWin();

private:
    Ui::StartUpDialog *ui;
    MainWindow *mainWindow;
};

#endif // STARTUPDIALOG_H
