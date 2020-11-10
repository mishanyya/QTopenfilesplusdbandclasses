#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QtGui>//для
#include <QFileDialog>//для диалоговых окон



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //не работает
    //getOpenFileName или getSaveFileName или getExistingDirectory изучить
    QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), QDir::currentPath(), "Images (*.png *.xpm *.jpg);;All files (*.*)");

}

MainWindow::~MainWindow()
{
    delete ui;
}

//не работает
//getOpenFileName или getSaveFileName или getExistingDirectory изучить
//QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), QDir::currentPath(), "Images (*.png *.xpm *.jpg);;All files (*.*)");

