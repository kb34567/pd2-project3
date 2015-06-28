#include "mainwindow.h"
#include <QApplication>
#include <QLCDNumber>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(100, 100, 700, 700);
    w.show();

    return a.exec();
}
