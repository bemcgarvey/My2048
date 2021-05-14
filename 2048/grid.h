#ifndef GRID_H
#define GRID_H

#include "tile.h"
#include <QPoint>

class Grid
{
public:
    Grid(int size = 4, int startTile = 2);
    ~Grid();
    enum direction {shiftRight, shiftLeft, shiftUp, shiftDown};
    bool insertRandomTile();
    bool hasAvailable() const;
    QList<const Tile *> tiles() const;
    bool shift(direction dir);
    int getSize() const {return size;}
private:
    QVector<QVector<Tile *>> grid;
    QList<QPoint> available() const;
    int size;
};

#endif // GRID_H
