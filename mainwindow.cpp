#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qstring.h>
#include <qfiledialog.h>
#include "renderer.h"
#include <qelapsedtimer.h>
#include <qdebug.h>
#include <opencv2/opencv.hpp>

using namespace cv;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

/*
 * Setting up the button which open the file dialog
 * and puts the path of the file selected in the
 * respective line edit
*/
void MainWindow::on_scenePathButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Images and Videos (*.png *.xpm *.jpg *.mp4)")); //Open file dialog
    ui->scenePath->setText(fileName); //Put the path in the line edit
}

/*
 * Setting up the button which open the file dialog
 * and puts the path of the file selected in the
 * respective line edit
*/
void MainWindow::on_texturesPathButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Images (*.png *.xpm *.jpg)")); //Open file dialog
    ui->texturesPath->setText(fileName); //Put the path in the line edit
}

/*
 * Setting up the button which open the file dialog
 * and puts the path of the file selected in the
 * respective line edit
*/
void MainWindow::on_objectsPathButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Images (*.png *.xpm *.jpg)")); //Open file dialog
    ui->objectsPath->setText(fileName); //Put the path in the line edit
}

/*
 * Setting up the apply button to start the algorithm
*/
void MainWindow::on_applyButton_clicked() {
    Mat object = imread(ui->objectsPath->text().toStdString());
    Mat texture = imread(ui->texturesPath->text().toStdString());
    Mat scene = imread(ui->scenePath->text().toStdString());

    cv::resize(object, object, Size(640, 480));
    cv::resize(texture, texture, Size(640, 480));

    Renderer render(texture, object);

    namedWindow("Scene", WINDOW_NORMAL);

    if (!ui->scenePath->text().endsWith(".mp4")) {
        cv::resize(scene, scene, Size(640, 480));
        render.performRender(scene, texture);
    }
    else {
        VideoCapture capture(ui->scenePath->text().toStdString());
        Mat frame;

        if(!capture.isOpened())
            throw "Error when reading " + ui->scenePath->text().toStdString();

        for( ; ; ) {
            QElapsedTimer timer;
            timer.start();
            capture >> frame;
            if(frame.empty())
                break;
            render.performRender(frame, texture);
            if (waitKey(5) >= 0)
                break;
            qDebug() << "The slow operation took" << timer.elapsed() << "milliseconds";
        }
    }
}
