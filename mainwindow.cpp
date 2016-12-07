#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qstring.h>
#include <qfiledialog.h>

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
void MainWindow::on_imagePathButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Images (*.png *.xpm *.jpg)")); //Open file dialog
    ui->imagePath->setText(fileName); //Put the path in the line edit
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
void MainWindow::on_applyButton_clicked()
{

}
