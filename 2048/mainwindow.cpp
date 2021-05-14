#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gridFrame->setGrid(new Grid);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionRestart_triggered()
{
    ui->gridFrame->setGrid(new Grid);
    update();
}

