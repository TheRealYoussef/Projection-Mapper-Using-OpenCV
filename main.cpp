#include "mainwindow.h"
#include <QApplication>
#include "corresponder.h"
#include "ccl.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Corresponder c;

    CCL ccl;

    Mat image = imread("/home/therealyoussef/Pictures/Image9.png");

    imshow("Image", image);

    ccl.applyCCL(image);

    return a.exec();
}
