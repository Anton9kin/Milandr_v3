#ifndef CHOOSEPROCESSOR_H
#define CHOOSEPROCESSOR_H

#include <QMainWindow>

namespace Ui {
class ChooseProcessor;
}

class ChooseProcessor : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseProcessor(QWidget *parent = nullptr);
    ~ChooseProcessor();

    virtual void closeEvent(QCloseEvent *e);

signals:
    void mainWin();

private:
    Ui::ChooseProcessor *ui;

};

#endif // CHOOSEPROCESSOR_H
