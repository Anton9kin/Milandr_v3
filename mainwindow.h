#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "chooseprocessor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_btn_newProject_clicked();

    void on_actionNew_project_triggered();

private:
    Ui::MainWindow *ui;
    ChooseProcessor *chProcWindow;

    void showChooseProcessorWindow();
    virtual void closeEvent(QCloseEvent *e);
};

#endif // MAINWINDOW_H
