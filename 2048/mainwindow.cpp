#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    grid = new Grid();
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete grid;
}

