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
    connect(ui->gridFrame, &GridFrame::scoreUpdate, this, &MainWindow::onScoreUpdate);
    scoreLabel = new QLabel("0");
    movesLabel = new QLabel("0");
    ui->statusbar->addWidget(new QLabel("Score:"));
    ui->statusbar->addWidget(scoreLabel);
    ui->statusbar->addWidget(new QLabel("  "));
    ui->statusbar->addWidget(new QLabel("Moves:"));
    ui->statusbar->addWidget(movesLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onScoreUpdate(int score, int moves, int largestTile)
{
    Q_UNUSED(largestTile);
    scoreLabel->setText(QString::number(score));
    movesLabel->setText(QString::number(moves));
//    if (emptySpaces == 0) {
//        if (QMessageBox::question(this, QApplication::applicationName()
//                              , "You lose.  Do you want to start over?") == QMessageBox::Yes) {
//            ui->gridFrame->setGrid(new Grid);
//            update();
//        } else {
//            close();
//        }
//    }
}


void MainWindow::on_actionRestart_triggered()
{
    if (QMessageBox::question(this, QApplication::applicationName()
                              , "Are you sure you want to restart?") == QMessageBox::Yes) {
        ui->gridFrame->setGrid(new Grid);
        onScoreUpdate(0, 0, 0);
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

