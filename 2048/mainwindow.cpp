#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSettings>
#include "aboutdialog.h"
#include "highscoredialog.h"
#include "optionsdialog.h"

//TODO implement save and load
//TODO remove any qDebugs

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), winningTile(2048), hasBeenWon(false)
    , highScore(0), mostMoves(0), largestTile(2)
{
    QSettings settings;
    highScore = settings.value("High Score", 0).toInt();
    mostMoves = settings.value("Most Moves", 0).toInt();
    largestTile = settings.value("Largest Tile", 2).toInt();
    ui->setupUi(this);
    ui->gridFrame->setGrid(new Grid);
    connect(ui->gridFrame, &GridFrame::scoreUpdate, this, &MainWindow::onScoreUpdate);
    connect(ui->gridFrame, &GridFrame::lostGame, this, &MainWindow::onLostGame);
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
    if (score > highScore) {
        highScore = score;
    }
    if (moves > mostMoves) {
        mostMoves = moves;
    }
    if (largestTile > this->largestTile) {
        this->largestTile = largestTile;
    }
    scoreLabel->setText(QString::number(score));
    movesLabel->setText(QString::number(moves));
    if (!hasBeenWon && largestTile >= winningTile) {
        if (QMessageBox::question(this, QApplication::applicationName()
                                  , "You Win.  Do you want to keep playing?") == QMessageBox::Yes) {
            hasBeenWon = true;
        } else {
            close();
        }
    }
}

void MainWindow::onLostGame()
{
    if (QMessageBox::question(this, QApplication::applicationName()
                              , "You lose.  Do you want to start over?") == QMessageBox::Yes) {
        restartGame();
    } else {
        close();
    }
}

void MainWindow::onClearScores()
{
    QSettings settings;
    settings.clear();
    highScore = 0;
    mostMoves = 0;
    largestTile = 2;
    closeEvent(nullptr);
}


void MainWindow::on_actionRestart_triggered()
{
    if (QMessageBox::question(this, QApplication::applicationName()
                              , "Are you sure you want to restart?") == QMessageBox::Yes) {
        restartGame();
    }
}


void MainWindow::on_actionExit_triggered()
{
    if (QMessageBox::question(this, QApplication::applicationName()
                              , "Are you sure you want to exit?") == QMessageBox::Yes) {
        close();
    }
}

void MainWindow::restartGame()
{
    ui->gridFrame->setGrid(new Grid);
    onScoreUpdate(0, 0, 0);
    hasBeenWon = false;
    update();
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    QSettings settings;
    settings.setValue("High Score", highScore);
    settings.setValue("Most Moves", mostMoves);
    settings.setValue("Largest Tile", largestTile);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog *dlg = new AboutDialog(this);
    dlg->exec();
    delete dlg;
}


void MainWindow::on_actionOptions_triggered()
{
    OptionsDialog *dlg = new OptionsDialog(this);
    dlg->exec();
    delete dlg;
}


void MainWindow::on_actionHigh_Score_triggered()
{
    HighScoreDialog *dlg = new HighScoreDialog(this);
    dlg->setScores(highScore, mostMoves, largestTile);
    connect(dlg, &HighScoreDialog::clearScores, this, &MainWindow::onClearScores);
    dlg->exec();
    delete dlg;
}


void MainWindow::on_actionUndo_triggered()
{
    ui->gridFrame->undo();
}

