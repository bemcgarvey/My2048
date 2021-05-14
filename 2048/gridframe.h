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
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual QSize sizeHint() const override;
    virtual void resizeEvent(QResizeEvent *event) override;
private:
    Grid *grid;
    int leftBorder;
    const int borderWidth = 4;
    int gridSize;
    int tileSize;

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // GRIDFRAME_H
