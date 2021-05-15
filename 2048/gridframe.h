#ifndef GRIDFRAME_H
#define GRIDFRAME_H

#include <QFrame>
#include "grid.h"

class GridFrame : public QFrame
{
    Q_OBJECT
public:
    GridFrame(QWidget *parent);
    ~GridFrame();
    void setGrid(Grid *grid);
    void undo();
signals:
    void scoreUpdate(int score, int moves, int largestTile);
    void lostGame();
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual QSize sizeHint() const override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
private:
    Grid *grid;
    int leftBorder;
    const int borderWidth = 4;
    int gridSize;
    int tileSize;
};

#endif // GRIDFRAME_H
