#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "classes/processor.h"
#include "mcuconfiguration.h"

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

    void on_actionNew_project_triggered();

    void on_btn_New_clicked();

    void on_btn_Open_clicked();

    void on_actionHome_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    MCUConfiguration MCUConfig;
    QWidget *startUp;

    virtual void closeEvent(QCloseEvent *e);



};

#endif // MAINWINDOW_H
