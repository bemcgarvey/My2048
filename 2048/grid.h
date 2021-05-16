#ifndef GRID_H
#define GRID_H

#include "tile.h"
#include <QPoint>
#include <deque>
#include <memory>

using std::vector;
using std::deque;
using tilePtr = std::unique_ptr<Tile>;

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
    friend QDataStream& operator<<(QDataStream &stream, const Grid &g);
    friend QDataStream& operator>>(QDataStream &stream, Grid &g);
private:
    bool insertRandomTile();
    vector<vector<tilePtr>> grid;
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
