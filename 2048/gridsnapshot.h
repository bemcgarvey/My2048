#ifndef GRIDSNAPSHOT_H
#define GRIDSNAPSHOT_H

#include <tile.h>
#include <QVector>

class Grid;

class GridSnapshot
{
public:
    GridSnapshot(Grid *g);
    friend class Grid;
private:
    int size;
    int score;
    int largestTile;
    int moves;
    int emptySpaces;
    QVector<Tile> tiles;
};

#endif // GRIDSNAPSHOT_H
