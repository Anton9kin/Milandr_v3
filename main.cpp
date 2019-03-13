#include "startupdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartUpDialog w;
    w.show();

    return a.exec();
}
