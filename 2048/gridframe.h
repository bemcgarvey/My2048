#ifndef GRIDFRAME_H
#define GRIDFRAME_H

#include <QFrame>
#include "grid.h"
#include <memory>

class GridFrame : public QFrame
{
    Q_OBJECT
public:
    GridFrame(QWidget *parent);
    ~GridFrame();
    void setGrid(Grid *grid);
    void undo();
    void saveGrid(QDataStream &out);
    void loadGrid(int size, QDataStream &in);
signals:
    void scoreUpdate(int score, int moves, int largestTile);
    void lostGame();
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual QSize sizeHint() const override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual bool event(QEvent *event) override;
private:
    std::unique_ptr<Grid> grid;
    int leftBorder;
    const int borderWidth = 4;
    int gridSize;
    int tileSize;
    void shiftGrid(Grid::Direction dir);
    void calculateSizes(int w, int h);
};

#endif // GRIDFRAME_H
