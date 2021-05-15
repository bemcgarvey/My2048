#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <grid.h>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionRestart_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionOptions_triggered();
    void on_actionHigh_Score_triggered();
    void onScoreUpdate(int score, int moves, int largestTile);
    void onLostGame();
    void onClearScores();
    void on_actionUndo_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *scoreLabel;
    QLabel *movesLabel;
    int winningTile;
    bool hasBeenWon;
    void restartGame();
    int highScore;
    int mostMoves;
    int largestTile;
protected:
    virtual void closeEvent(QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
