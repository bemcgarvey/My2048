#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <grid.h>

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

private:
    Ui::MainWindow *ui;
    Grid *grid;
};
#endif // MAINWINDOW_H
