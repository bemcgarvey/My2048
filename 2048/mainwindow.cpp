#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

//TODO implement score, high score and total moves. Save to settings(registry)
//TODO implement undo
//TODO implement save and load
//TODO about dialog and icon
//TODO remove any qDebugs
//TODO options???

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
    if (QMessageBox::question(this, QApplication::applicationName()
                              , "Are you sure you want to restart?") == QMessageBox::Yes) {
        ui->gridFrame->setGrid(new Grid);
        update();
    }
}


void MainWindow::on_actionExit_triggered()
{
    if (QMessageBox::question(this, QApplication::applicationName()
                              , "Are you sure you want to exit?") == QMessageBox::Yes) {
        close();
    }
}

