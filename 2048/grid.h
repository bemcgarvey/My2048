#ifndef GRID_H
#define GRID_H

#include "tile.h"
#include <QPoint>

class Grid
{
public:
    Grid(int size = 4, int startTile = 2);
    enum direction {shiftRight, shiftLeft, shiftUp, shiftDown};
    bool insertRandomTile();
    bool hasAvailable() const;
    QList<const Tile *> tiles() const;
    bool shift(direction dir);
private:
    QVector<QVector<Tile *>> grid;
    QList<QPoint> available() const;
    int size;
};

#endif // GRID_H
