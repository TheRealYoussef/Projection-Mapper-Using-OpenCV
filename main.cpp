#include "mainwindow.h"
#include <QApplication>
#include "corresponder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Corresponder c;

    return a.exec();
}
