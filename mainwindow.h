#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

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

private:
    Ui::MainWindow *ui;
    QStandardItemModel *csvModel;

    virtual void closeEvent(QCloseEvent *e);


};

#endif // MAINWINDOW_H
