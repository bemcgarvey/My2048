#ifndef HIGHSCOREDIALOG_H
#define HIGHSCOREDIALOG_H

#include <QDialog>

namespace Ui {
class HighScoreDialog;
}

class HighScoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HighScoreDialog(QWidget *parent = nullptr);
    ~HighScoreDialog();
    void setScores(int highScore, int mostMoves, int largestTile);
private slots:
    void on_pushButton_clicked();
    void on_clearScoresPushButton_clicked();
private:
    Ui::HighScoreDialog *ui;
signals:
    void clearScores();
};

#endif // HIGHSCOREDIALOG_H
