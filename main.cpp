#include "mainwindow.h"
#include <QApplication>
#include "corresponder.h"
#include "ccl.h"
#include "boundingboxescreator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Corresponder c;

    CCL ccl;
    BoundingBoxesCreator boundingBoxesCreator;

    Mat image = imread("Images/Image10.png");

    imshow("Image", image);

    ccl.applyCCL(image);
    boundingBoxesCreator.createBoundingBoxes(ccl.getLabels(), ccl.getNumberOfLabels(), image);

    vector<Mat> objects = boundingBoxesCreator.getObjects();

    for (int i = 0; i < (int)objects.size(); ++i) {
        imshow(to_string(i), objects[i]);
    }

    return a.exec();
}
