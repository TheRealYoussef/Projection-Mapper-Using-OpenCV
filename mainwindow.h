#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_imagePathButton_clicked();

    void on_texturesPathButton_clicked();

    void on_objectsPathButton_clicked();

    void on_applyButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
