#ifndef GRID_H
#define GRID_H

#include "tile.h"
#include <QPoint>
#include <deque>

using std::deque;
class GridSnapshot;

class Grid
{
public:
    Grid(int size = 4, int startTile = 2);
    ~Grid();
    enum direction {shiftRight, shiftLeft, shiftUp, shiftDown};
    bool isLost() const;
    QList<const Tile *> tiles() const;
    bool shift(direction dir);
    int getSize() const {return size;}
    void getStats(int &score, int &moves, int &largestTile) const;
    friend class GridSnapshot;
    bool undo();
private:
    bool insertRandomTile();
    QVector<QVector<Tile *>> grid;
    QList<QPoint> available() const;
    int size;
    int score;
    int largestTile;
    int moves;
    int emptySpaces;
    unsigned int undoDepth;
    deque<GridSnapshot> undoStack;
};

#endif // GRID_H
