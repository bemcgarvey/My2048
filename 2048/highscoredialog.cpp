#include "highscoredialog.h"
#include "ui_highscoredialog.h"
#include <QMessageBox>

HighScoreDialog::HighScoreDialog(QWidget *parent) :
    QDialog(parent, Qt::MSWindowsFixedSizeDialogHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint),
    ui(new Ui::HighScoreDialog)
{
    ui->setupUi(this);
}

HighScoreDialog::~HighScoreDialog()
{
    delete ui;
}

void HighScoreDialog::setScores(int highScore, int mostMoves, int largestTile)
{
    ui->highScoreLabel->setText(QString::number(highScore));
    ui->mostMovesLabel->setText(QString::number(mostMoves));
    ui->largestTileLabel->setText(QString::number(largestTile));
}

void HighScoreDialog::on_pushButton_clicked()
{
    close();
}


void HighScoreDialog::on_clearScoresPushButton_clicked()
{
    if (QMessageBox::question(this, QApplication::applicationName()
                              , "Are you sure you want to clear high scores?") == QMessageBox::Yes) {
        emit clearScores();
        setScores(0, 0, 2);
    }
}

